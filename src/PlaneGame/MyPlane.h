#pragma once
#include "GameObject.h"

class CMyPlane :public CGameObject
{
public:
	CMyPlane(void);
	~CMyPlane(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	void SetHorMotion(int nMotion)
	{
		m_nHorMotion = nMotion;
	}
	int GetHorMotion() const
	{
		return m_nHorMotion;
	}

	void SetVerMotion(int nMotion)
	{
		m_nVerMotion = nMotion;
	}
	int GetVerMotion() const
	{
		return m_nVerMotion;
	}

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+PLANE_WIDTH,m_ptPos.y+PLANE_HEIGHT));
	}

	//�Ƿ���Կ����䵼��
	BOOL Fired();
	//����̬
	void bian(void);

public:
	static const int PLANE_WIDTH=140;
	static const int PLANE_HEIGHT=120;
private:
	
	static CImageList m_Images;
	static CImageList dun;
	static CImageList xingtai;
	//static CImageList xue;
	int    m_nHorMotion;//�ɻ�ˮƽ���з���0->��ֹ��1->�� -1->��
	int    m_nVerMotion;//�ɻ���ֱ���з���0->��ֹ��1->�� -1->��
	int    m_nWait;//������ʱ
public:
	//��״̬
	bool ifdun;
	//ս��״̬
	int xueliang,nengliang,fenshu;
	//��̬
	bool ifyuan;
	//���ս��λ��
	/* CPoint getmep() {
		return  m_ptPos;
	}*/
	
};
