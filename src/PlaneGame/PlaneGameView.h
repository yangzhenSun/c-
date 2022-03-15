// PlaneGameView.h : CPlaneGameView ��Ľӿ�
//
#include <atlimage.h>

#pragma once

class CMyPlane;
class CPlaneGameView : public CView
{
	static	CBitmap xue;
	static  CBitmap nengliang;
	static	CImage gunbj;
	enum ObjType{enEnemy, enEnemy2, enEnemy3, enBomb,enBall,enExplosion,enBuji,enNewball};

protected: // �������л�����
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

// ���� ���� �ؿ�
public:
	CPlaneGameDoc* GetDocument() const;
	CString str = _T("Game Over!");
	//������շ���
	int finalfen;
	//����
	int guan;
	//�޵�
	bool wudi;
	 
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//�ڴ�DC
	CDC*        m_pMemDC;
	//�豸DC
	CClientDC*  m_pDC;
	//�ڴ�λͼ
	CBitmap*    m_pMemBitmap;


protected:
	//��ʼ����Ϸ
	BOOL InitGame();
	//������Ϸ
	void StopGame();

	//ˢ����Ϸ��֡����
	void UpdateFrame(CDC* pMemDC);
	void AI();
	//������
	void XUpdateFrame(CDC* pMemDC);
	void XAI();
	void kaishi();
	//��Ϸ״̬�Ƿ���ͣ
	bool ifz;
	//���¿�ʼ
	void restart();
	//��ö���״̬
	void statedun();
	//�ƶ�ս��
	void move();
	//����ս������
	void meshot();
	//plane�ܵ��˺�
	void gethurt();
	//����ui
	void paintui(CDC* pMemDC);
	void xpaintui(CDC* pMemDC);
	//��ü���״̬1->down
	int GetKey(int nVirtKey)
	{
		return (GetKeyState(nVirtKey) & 0x8000)? 1 : 0;
	}
	
	CMyPlane*  m_pMe;
	

	CObList    m_ObjList[8];



// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	
};

#ifndef _DEBUG  // PlaneGameView.cpp �еĵ��԰汾
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

