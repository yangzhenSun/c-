#pragma once

#include "gameobject.h"

class CEnemy3 :public CGameObject
{
public:
	CEnemy3(void);
	~CEnemy3(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + ENEMY3_WEIGHT, m_ptPos.y + ENEMY3_HEIGHT));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
	//�Ƿ���Կ������ӵ�
	BOOL Fired();
public:
	static const int ENEMY3_HEIGHT = 50, ENEMY3_WEIGHT = 240;
	static CImageList m_Images;
	int    m_nMotion;//���� 1->���� 0->ֹͣ -1->����
	
	//�ٶ�
	int m_V;
	
};
