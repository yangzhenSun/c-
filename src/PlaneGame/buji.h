
#pragma once
#include "GameObject.h"

class CBuji :public CGameObject
{
public:
	CBuji(void);
	~CBuji(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BUJI_HEIGHT, m_ptPos.y + BUJI_HEIGHT));
	}
private:
	static const int BUJI_HEIGHT = 50;
	static CImageList m_Images;
	int    m_nMotion;
	int m_v;
};
