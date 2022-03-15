#include "StdAfx.h"
#include "Enemy2.h"
#include "resource.h"

CImageList CEnemy2::m_Images;

CEnemy2::CEnemy2(void)
{
	//随机确定X位置
	m_ptPos.x = rand() % (GAME_WIDTH - ENEMY2_WEIGHT) + 1;

	
	//根据图像索引确定方向
	m_nMotion = 1;
	m_ptPos.y = -ENEMY2_HEIGHT;
	
	//随机确定速度
	m_V = 2;
	CGameObject::shengming = 16;
	
}

CEnemy2::~CEnemy2(void)
{
}
BOOL CEnemy2::LoadImage()
{
	return CGameObject::LoadImage(m_Images, enemy2, RGB(255, 255, 255), 240, 182, 2);
}
BOOL CEnemy2::Draw(CDC* pDC, BOOL bPause)
{
	
	

	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if (m_ptPos.y > GAME_HEIGHT + ENEMY2_HEIGHT)
		return FALSE;
	

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
