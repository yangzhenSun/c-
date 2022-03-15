#pragma once

#include "GameObject.h"

class CNewBall :public CGameObject
{
public:
	CNewBall(int x, int y);
	~CNewBall(void);

	BOOL Draw(CDC* pDC, BOOL bPause,CPoint mep);
	BOOL Draw(CDC* a, BOOL b) { return false; }

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + NewBALL_HEIGHT, m_ptPos.y + NewBALL_HEIGHT));
	}
private:
	static const int NewBALL_HEIGHT = 33;
	static CImageList m_Images;
	double bx,by;

};
