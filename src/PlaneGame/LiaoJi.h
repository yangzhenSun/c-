#pragma once

#include "GameObject.h"

class CLiaoJi :public CGameObject
{
public:
	CLiaoJi(void);
	~CLiaoJi(void);

	BOOL Draw(CDC* pDC, BOOL bPause, CPoint mep);
	BOOL Draw(CDC* a, BOOL b) { return false; }

	static BOOL LoadImage();
	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + LiaoJi_HEIGHT, m_ptPos.y + LiaoJi_HEIGHT));
	}
	
private:
	static const int LiaoJi_HEIGHT = 75;
	static CImageList m_Images;
	double bx, by;

};
