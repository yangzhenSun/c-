#include "StdAfx.h"
#include "buji.h"
#include "resource.h"

CImageList CBuji::m_Images;

CBuji::CBuji(void) 
{
	m_ptPos.x = rand() % (GAME_WIDTH - BUJI_HEIGHT) + 1;
	m_ptPos.y = -BUJI_HEIGHT;
	m_v = 5;
	m_nMotion = 1;
	
}

CBuji::~CBuji(void)
{
}
BOOL CBuji::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * 8;
	}

	if (m_ptPos.y > GAME_HEIGHT + BUJI_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BUJI_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL CBuji::LoadImage()
{
	return CGameObject::LoadImage(m_Images, buji, RGB(255, 255, 255), 50, 50, 1);
}