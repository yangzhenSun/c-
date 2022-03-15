#include "StdAfx.h"
#include "NewBall.h"
#include "resource.h"

CImageList CNewBall::m_Images;

CNewBall::CNewBall(int x, int y) :CGameObject(x, y)
{
	bx = 0; by = 0;
}

CNewBall::~CNewBall(void)
{
}
BOOL CNewBall::Draw(CDC* pDC, BOOL bPause,CPoint mep)
{
	if (mep.x+37 - m_ptPos.x > 0)bx = 1; else bx = -1;
	if (mep.y+26 - m_ptPos.y > 0)by = 1; else by = -1;
	
	if (!bPause)
	{
		m_ptPos.x += bx * 5;
		m_ptPos.y += by * 5;
	}

	
	
	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL CNewBall::LoadImage()
{
	return CGameObject::LoadImage(m_Images, newball, RGB(255, 255, 255), 45, 45, 1);
}