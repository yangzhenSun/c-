#include "StdAfx.h"
#include "Explosion.h"
#include "resource.h"

CImageList CExplosion::m_Images;

CExplosion::CExplosion(int x,int y):CGameObject(x,y),m_nProcess(0)
{
}

CExplosion::~CExplosion(void)
{
}

BOOL CExplosion::Draw(CDC* pDC,BOOL bPause)
{
	
	//ֻ��15��ͼƬ
	if(m_nProcess==23)
	{
		m_nProcess=0;
		return FALSE;
	}
	
	//����λ�û���ͼ��
	m_Images.Draw(pDC,m_nProcess,m_ptPos,ILD_TRANSPARENT);
	m_nProcess++;
	return true;
}

BOOL CExplosion::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_EXPLOSION2,RGB(0,0,0),80,80,8);
}