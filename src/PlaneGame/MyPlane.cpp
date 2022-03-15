#include "StdAfx.h"
#include "MyPlane.h"
#include "resource.h"

CImageList CMyPlane::m_Images;
CImageList CMyPlane::dun;
CImageList CMyPlane::xingtai;
CMyPlane::~CMyPlane(void)
{
	
}
CMyPlane::CMyPlane(void):m_nHorMotion(0),m_nVerMotion(0)
{
	m_nWait = 0;
	m_ptPos.x = 315;
	m_ptPos.y = 1000;
	ifdun = 0;
	xueliang = 200;
	nengliang = 200;
	fenshu = 0;
	ifyuan = 1;
}

BOOL CMyPlane::Fired()
{
	if(m_nWait==0)
		return TRUE;
	else
		return FALSE;

}
BOOL CMyPlane::LoadImage()
{
	CGameObject::LoadImage(xingtai, xinfeiji2, RGB(255, 255, 255), 120, 99, 1);
	CGameObject::LoadImage(dun, hudun, RGB(255, 255, 255), 160, 174, 1);
	return CGameObject::LoadImage(m_Images,xinfeiji,RGB(255,255,255),120,99,1);
}
BOOL CMyPlane::Draw(CDC* pDC,BOOL bPause)
{
	m_nWait++;
	if(m_nWait>5)
		m_nWait=0;


	if(!bPause)
	{
		m_ptPos.x = m_ptPos.x + m_nHorMotion*3;
		m_ptPos.y = m_ptPos.y - m_nVerMotion*3;
	}

	if(m_ptPos.x>=GAME_WIDTH-PLANE_WIDTH)
		m_ptPos.x =GAME_WIDTH-PLANE_WIDTH;
	if(m_ptPos.x<=0)
		m_ptPos.x=0;

	if(m_ptPos.y<=0)
		m_ptPos.y =0;

	if(m_ptPos.y>=GAME_HEIGHT-PLANE_HEIGHT)
		m_ptPos.y=GAME_HEIGHT-PLANE_HEIGHT;

	POINT pdun = m_ptPos; pdun.x -=20;
	POINT pxue = { 500,5 };
	pdun.y -= 27;
	
	if(ifyuan==1)
	m_Images.Draw(pDC,0, m_ptPos,ILD_TRANSPARENT);
	else 
	xingtai.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	if (ifdun == 1) dun.Draw(pDC, 0, pdun, ILD_TRANSPARENT);
	return TRUE;
}
void CMyPlane::bian() {
	if (ifyuan == 1)ifyuan = 0;
	else ifyuan = 1;
}