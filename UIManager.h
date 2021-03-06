#pragma once
#include "singletonBase.h"
class UIBase;
class UIManager : public singletonBase<UIManager>
{
private:
	UIBase* _focusUI;
public:
	HRESULT Init();
	void Release();
	void OnKeyDown(WCHAR input);
	void SetFocusUI(UIBase* focusUI);
	void SetActiveUI(UIBase* targetUI, bool isActive);
	void SetActiveUI(UIBase* targetUI, bool isActive, Vector2 position);

};

