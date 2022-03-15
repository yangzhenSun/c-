#include "StdAfx.h"
#include "Ball.h"
#include "resource.h"

CImageList CBall::m_Images;

CBall::CBall(int x,int y,int nMontion,int zy):CGameObject(x,y),m_nMotion(nMontion),zuoyou(zy)
{

}

CBall::~CBall(void)
{
}
BOOL CBall::Draw(CDC* pDC,BOOL bPause)
{
	if(!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * 8;
	}

	if(m_ptPos.y > GAME_HEIGHT+BALL_HEIGHT )
		return FALSE;
	if(m_ptPos.y < -BALL_HEIGHT)
		return FALSE;
	m_ptPos.x += zuoyou * 3;
	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);
	
	return TRUE;
}

BOOL CBall::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_BALL,RGB(255,255,255),33,33,1);
}