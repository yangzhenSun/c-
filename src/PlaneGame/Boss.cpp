#include "StdAfx.h"
#include "Boss.h"
#include "resource.h"

CImageList CBoss::m_Images;

CBoss::CBoss(void)
{
	m_ptPos.x = rand() % (GAME_WIDTH - BOSS_WEIGHT) + 1;
	m_ptPos.y = 5;
	m_v = 5;
	
	xueliang = 200;
	ifyou = 1;
}

CBoss::~CBoss(void)
{
}
BOOL CBoss::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		if (ifyou == 1) {
			m_ptPos.x += 3;
			if (m_ptPos.x > GAME_WIDTH - BOSS_WEIGHT + 2)ifyou = 0;
		}
		if (ifyou == 0) {
			m_ptPos.x -= 3;
			if (m_ptPos.x <1)ifyou = 1;
		}
	}


	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL CBoss::LoadImage()
{
	return CGameObject::LoadImage(m_Images, boss, RGB(255, 255, 255), 312, 166, 1);
}