#include "StdAfx.h"
#include "Enemy3.h"
#include "resource.h"

CImageList CEnemy3::m_Images;

CEnemy3::CEnemy3(void)
{
	//随机确定X位置
	m_ptPos.x = rand() % (GAME_WIDTH - ENEMY3_WEIGHT) + 1;

	
	
	m_nMotion = 1;
	m_ptPos.y = -ENEMY3_HEIGHT;
	
	//随机确定速度
	m_V = 2;
	CGameObject::shengming = 16;
	
}

CEnemy3::~CEnemy3(void)
{
}
BOOL CEnemy3::LoadImage()
{
	return CGameObject::LoadImage(m_Images, enemy3, RGB(255, 255, 255), 240, 180, 2);
}
BOOL CEnemy3::Draw(CDC* pDC, BOOL bPause)
{
	

	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if (m_ptPos.y > GAME_HEIGHT + ENEMY3_HEIGHT)
		return FALSE;
	

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
