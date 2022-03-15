#include "StdAfx.h"
#include "Bomb.h"
#include "resource.h"

CImageList CBomb::m_Images;
CBomb::CBomb(int x, int y, bool qh,int zy) :CGameObject(x, y), qian(qh),zuoyou(zy)
{
}
CBomb::~CBomb(void)
{
}
BOOL CBomb::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_BOMB,RGB(255,255,255),26,79,1);
}
BOOL CBomb::Draw(CDC* pDC,BOOL bPause)
{
	if(!bPause)
	{
		if(qian==true)m_ptPos.y = m_ptPos.y - 15;
		else m_ptPos.y = m_ptPos.y + 15;
	}

	if(m_ptPos.y < -BOMB_HEIGHT|| m_ptPos.y >GAME_HEIGHT)
		return FALSE;
	m_ptPos.x += zuoyou * 5;
	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);
	return TRUE;
}