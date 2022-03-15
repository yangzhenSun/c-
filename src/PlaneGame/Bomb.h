#pragma once
#include "gameobject.h"

class CBomb :
	public CGameObject
{
public:
	CBomb(int x,int y,bool qh,int zy);
	~CBomb(void);
	bool qian;
	//zuoyou
	int zuoyou;
	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+26,m_ptPos.y+BOMB_HEIGHT));
	}
private:
	static const int BOMB_HEIGHT = 79;
	static CImageList m_Images;

};
