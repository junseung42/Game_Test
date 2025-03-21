#pragma once
#include "Scene.h"

class Stage : public Scene
{
	virtual void Init() override;
	virtual void Update() override;
public:
	int block_x;//블럭의 x좌표
	int block_y;//블럭의 y좌표
	int block_shape[7][4][4][4];//블럭 모양
	int block_random;//블럭의 7가지 모양
	int block_value;//블럭의 모양상태
	int blocK_count;//벽 밖으로 나간 블럭의 갯수 체크
	int block_point;//테트리스 점수
	int block_pointcount;//1줄에 몇개의 블럭이 차있는지 체크
	bool block_neednext;//새로운 블럭이 필요한 경우 1 = 필요, 0 = 불필요
public:
	//블럭이 벽, 블럭화된곳 에 충돌이 일어났는지 체크
	bool CheckCrash(int x, int y);
	//블럭의 모양을 바꿀때 블럭의 도형이 얼마나 벽 밖으로 나갔는지 체크
	void CheckCount(int x, int y);
};

