#pragma once
#include "GameObject.h"

class CBall :public CGameObject
{
public:
	CBall(int x,int y,int nMontion,int zuoyou);
	~CBall(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+BALL_HEIGHT,m_ptPos.y+BALL_HEIGHT));
	}
private:
	static const int BALL_HEIGHT=33;
	static CImageList m_Images;
	int    m_nMotion;
	int zuoyou;
};
