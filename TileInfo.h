#pragma once

#define TILESIZE 32						//타일 조각 크기

#define TILENUMX 100						//1행 타일 개수
#define TILENUMY 100						//1열 타일 개수

#define TILESIZEX TILESIZE * TILENUMX		//타일 맵의 가로 크기
#define TILESIZEY TILESIZE * TILENUMY		//타일 맵의 세로 크기

//타일셋 정렬
#define TILESETX 4 //필요에 따라 늘립시다
#define TILESETY 9 //추후 늘립시다


//비트필드
#define ATTR_UNMOVE 0x00000001			//못가는 타일


//환경
/*환경 이름
모래, 물, 바위, 돌, 눈
*/
enum ENVIRONMENT
{
	ENV_WATER, ENV_DEEPWATER, ENV_SAND1, ENV_SAND2, ENV_SAND3, ENV_DARKSAND, 
	ENV_DIRT1, ENV_DIRT2, ENV_DIRT3, ENV_STONE1, ENV_STONE2, ENV_STONE3, 
	ENV_BASALT1, ENV_BASALT2, ENV_BASALT3, ENV_SNOW1, ENV_SNOW2, ENV_SNOW3,
	ENV_ICE1, ENV_ICE2, ENV_ICE3, ENV_ICE_WALL1, ENV_ICE_WALL2,
	ENV_NONE
};

//자원
/*자원 이름
구리, 납, 고철
*/
enum RESOURCES
{
	RES_COPPER1, RES_COPPER2, RES_COPPER3,
	RES_LEAD1, RES_LEAD2, RES_LEAD3,
	RES_SCRAP1, RES_SCRAP2, RES_SCRAP3,
	RES_NONE
};

//타일 조각 구조체
struct tagTile
{
	ENVIRONMENT		environment;
	RESOURCES		resources;
};

struct tagTileSet
{
	Rect rcTile;
	int TileX;
	int TileY;
};
