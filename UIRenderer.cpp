#include "stdafx.h"
#include "UIRenderer.h"

UIRenderer::UIRenderer()
{
}

UIRenderer::~UIRenderer()
{
}

void UIRenderer::Init(string clipName)
{
	AnimationClip* targetClip = CLIPMANAGER->FindClip(clipName);
	if (targetClip == nullptr)
	{
		throw("UIrenderer Init error. Invalid AnimationClip");
	}
	_clipName = clipName;
	_targetBitmap = targetClip->GetBitmap();
	_frameWidth = targetClip->GetFrameWidth();
	_frameHeight = targetClip->GetFrameHeight();
	_curFrameX = 0;
	_curFrameY = 0;
	_clipX = 0;
	_clipY = 0;
	_alpha = 1.f;
	_rc = RectMakePivot(transform->position, Vector2(_frameWidth * transform->GetScaleX(), _frameHeight * transform->GetScaleX()), Pivot::Center);
}

void UIRenderer::Init(float width, float height)
{
	_clipName = "";
	_frameWidth = width;
	_frameHeight = height;
	_curFrameX = 0;
	_curFrameY = 0;
	_clipX = 0;
	_clipY = 0;
	_alpha = 1.f;
	_rc = RectMakePivot(transform->position, Vector2(_frameWidth * transform->GetScaleX(), _frameHeight * transform->GetScaleX()), Pivot::Center);
}

void UIRenderer::Update()
{
	_rc = RectMakePivot(transform->position, Vector2(_frameWidth * transform->GetScaleX(), _frameHeight * transform->GetScaleX()), Pivot::Center);
}

void UIRenderer::Render()
{
	int startX = transform->GetX() - _frameWidth / 2;
	int startY = transform->GetY() - _frameHeight / 2;
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		D2DRENDERER->DrawRectangleUI(_rc, D2DRenderer::DefaultBrush::Gray);
	}
	if (_targetBitmap == nullptr)
	{
		return;
	}
	D2D1_SIZE_F bitmapSize = _targetBitmap->GetSize();
	//그려질 영역
	D2D1_RECT_F clipArea =
		D2D1::RectF
		(
			_curFrameX * _frameWidth + _clipX, 
			_curFrameY * _frameHeight + _clipY, 
			(_curFrameX + 1) * _frameWidth,
			(_curFrameY + 1) * _frameHeight
		);
	//그릴 영역
	D2D1_RECT_F backbufferArea
		= D2D1::RectF
		(
			startX + _clipX,			// 이미지의 시작점X 부터 clipX만큼 이미지 렌더X
			startY + _clipY,			// 이미지의 시작점Y 부터 clipY만큼 이미지 렌더X
			startX + _frameWidth,
			startY + _frameHeight
		);

	D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(
		transform->angle,
		D2D1::Point2F(transform->GetX(), transform->GetY())
	);

	D2D1_MATRIX_3X2_F scale = D2D1::Matrix3x2F::Scale(
		transform->GetScaleX(),
		transform->GetScaleY(),
		D2D1::Point2F(transform->GetX(), transform->GetY())
	);
	D2DRENDERER->GetRenderTarget()->SetTransform(scale * rotation);


	D2DRENDERER->GetRenderTarget()->DrawBitmap(_targetBitmap, backbufferArea, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, clipArea);
	D2DRENDERER->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
}

/***********************************************
렌더러의 대상 비트맵을 변경(클립변경)
프레임 인덱스를 0으로 초기화
newBitmap : 새로운 대상 비트맵
frameWidth : 새로운 비트맵의 프레임당 넓이
frameHeight : 새로운 비트맵의 새로운 높이
***********************************************/
void UIRenderer::ChangeTargetBitmap(string newClipName)
{
	AnimationClip* targetClip = CLIPMANAGER->FindClip(newClipName);
	if (targetClip == nullptr)
	{
		throw("uiRenderer error");
	}
	_clipName = newClipName;
	_targetBitmap = targetClip->GetBitmap();
	_frameWidth = targetClip->GetFrameWidth();
	_frameHeight = targetClip->GetFrameHeight();
	_curFrameX = 0;
}

/***********************************************
렌더러의 대상 비트맵을 변경(클립변경)
newBitmap : 새로운 대상 비트맵
frameWidth : 새로운 비트맵의 프레임당 넓이
frameHeight : 새로운 비트맵의 새로운 높이
inInitFrmae : true면 프레임 인덱스를 0으로 초기화
***********************************************/
void UIRenderer::ChangeTargetBitmap(string newClipName, int startFrame)
{
	AnimationClip* targetClip = CLIPMANAGER->FindClip(newClipName);
	if (targetClip == nullptr)
	{
		throw("renderer error");
	}
	_clipName = newClipName;
	_targetBitmap = targetClip->GetBitmap();
	_frameWidth = targetClip->GetFrameWidth();
	_frameHeight = targetClip->GetFrameHeight();
	_curFrameX = startFrame;
}
