#pragma once
#include "GameObject.h"

class CBoss :public CGameObject
{
public:
	CBoss(void);
	~CBoss(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BOSS_WEIGHT, m_ptPos.y + BOSS_HEIGHT));
	}
	static const int BOSS_HEIGHT = 166, BOSS_WEIGHT = 310;
	int xueliang;
private:
	
	static CImageList m_Images;
	
	int m_v;
	//ÒÆ¶¯·½Ïò
	bool ifyou;
};
