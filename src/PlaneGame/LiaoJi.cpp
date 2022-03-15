#include "StdAfx.h"
#include "LiaoJi.h"
#include "resource.h"

CImageList CLiaoJi::m_Images;

CLiaoJi::CLiaoJi(void)
{
	m_ptPos.x = 315;
	m_ptPos.y = 1000;
}

CLiaoJi::~CLiaoJi(void)
{
}
BOOL CLiaoJi::Draw(CDC* pDC, BOOL bPause, CPoint mep)
{
	static int zhuangtai = 0, time = 80, timex=30, timey=30;
	if (time <= 0) {
		time = 120;
		zhuangtai = rand() % 2;
	}

	if (zhuangtai == 0) {
		if (mep.x + 120 - m_ptPos.x > 0)bx = 1; else bx = -1;
		if (mep.y + 26 - m_ptPos.y > 0)by = 1; else by = -1;
	}
	if (zhuangtai == 1) {
		if (timex <= 0) { timex = rand() % 20 + 20; bx = rand() % 3; bx -= 1; }
		if (timey <= 0) { timey = rand() % 20 + 20; by = rand() % 3; by -= 1; }

		timex--; timey--;
	}
	if (m_ptPos.x >= GAME_WIDTH - LiaoJi_HEIGHT)
		m_ptPos.x = GAME_WIDTH - LiaoJi_HEIGHT;
	if (m_ptPos.x <= 0)
		m_ptPos.x = 0;

	if (m_ptPos.y <= 0)
		m_ptPos.y = 0;

	if (m_ptPos.y >= GAME_HEIGHT - LiaoJi_HEIGHT)
		m_ptPos.y = GAME_HEIGHT - LiaoJi_HEIGHT;

	time--; 

	if (!bPause)
	{
		m_ptPos.x += bx * 5;
		m_ptPos.y += by * 5;
	}



	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL CLiaoJi::LoadImage()
{
	return CGameObject::LoadImage(m_Images, liaoji, RGB(255, 255, 255), 75, 73, 1);
}