// PlaneGameView.h : CPlaneGameView 类的接口
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

protected: // 仅从序列化创建
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

// 属性 分数 关卡
public:
	CPlaneGameDoc* GetDocument() const;
	CString str = _T("Game Over!");
	//玩家最终分数
	int finalfen;
	//卡关
	int guan;
	//无敌
	bool wudi;
	 
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//内存DC
	CDC*        m_pMemDC;
	//设备DC
	CClientDC*  m_pDC;
	//内存位图
	CBitmap*    m_pMemBitmap;


protected:
	//初始化游戏
	BOOL InitGame();
	//结束游戏
	void StopGame();

	//刷新游戏的帧画面
	void UpdateFrame(CDC* pMemDC);
	void AI();
	//最终章
	void XUpdateFrame(CDC* pMemDC);
	void XAI();
	void kaishi();
	//游戏状态是否暂停
	bool ifz;
	//重新开始
	void restart();
	//获得盾牌状态
	void statedun();
	//移动战机
	void move();
	//产生战机导弹
	void meshot();
	//plane受到伤害
	void gethurt();
	//绘制ui
	void paintui(CDC* pMemDC);
	void xpaintui(CDC* pMemDC);
	//获得键的状态1->down
	int GetKey(int nVirtKey)
	{
		return (GetKeyState(nVirtKey) & 0x8000)? 1 : 0;
	}
	
	CMyPlane*  m_pMe;
	

	CObList    m_ObjList[8];



// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	
};

#ifndef _DEBUG  // PlaneGameView.cpp 中的调试版本
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

