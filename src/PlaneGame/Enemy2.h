#pragma once

#include "gameobject.h"

class CEnemy2 :public CGameObject
{
public:
	CEnemy2(void);
	~CEnemy2(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + ENEMY2_WEIGHT, m_ptPos.y + ENEMY2_HEIGHT));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
		
public:
	static const int ENEMY2_HEIGHT = 50, ENEMY2_WEIGHT = 240;
	static CImageList m_Images;
	int    m_nMotion;//方向 1->向下 0->停止 -1->向上	
	//速度
	int m_V;
	
};
