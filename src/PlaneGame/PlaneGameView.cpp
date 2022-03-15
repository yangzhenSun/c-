// PlaneGameView.cpp : CPlaneGameView 类的实现
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Bomb.h"
#include "Ball.h"
#include "Explosion.h"
#include"Boss.h"
#include"buji.h"
#include"NewBall.h"
#include"Enemy2.h"
#include"Enemy3.h"
#include"LiaoJi.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CBitmap CPlaneGameView:: xue;
CBitmap CPlaneGameView::nengliang;
CImage  CPlaneGameView::gunbj;
CBoss* Boss;
CLiaoJi* Liaoji;
// CPlaneGameView
IMPLEMENT_DYNCREATE(CPlaneGameView, CView)
BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CPlaneGameView 构造/析构
CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: 在此处添加构造代码
	ifz = 0; guan = 1; wudi = 0;
}
CPlaneGameView::~CPlaneGameView()
{
}
BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView 绘制
void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}
// CPlaneGameView 打印
BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}
void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}
void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}
// CPlaneGameView 诊断
#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}
void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CPlaneGameDoc* CPlaneGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG
// CPlaneGameView 消息处理程序
void CPlaneGameView::OnInitialUpdate()
{
	InitGame();
	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	//初始化游戏
	//InitGame();
}
void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
}
//初始化， 更新进程，画面
BOOL CPlaneGameView::InitGame()
{
 xue.LoadBitmapW(xuetiao);
 nengliang.LoadBitmapW(nengliangtiao);
	CRect rc;
	GetClientRect(rc);

	//产生随机数种子
	srand( (unsigned)time( NULL ) );

	//建立设备DC
	m_pDC = new CClientDC(this);
	
	//建立内存DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//建立内存位图
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//将位图选入内存DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	CBomb::LoadImage();
	CBall::LoadImage();
	CExplosion::LoadImage();
	CBuji::LoadImage();
	CBoss::LoadImage();
	CNewBall::LoadImage();
	CEnemy2::LoadImage();
	CEnemy3::LoadImage();
	CLiaoJi::LoadImage();
	//产生主角(战机)
	m_pMe = new CMyPlane;
	Liaoji = new CLiaoJi;
	Boss = new CBoss;
	//加载背景
	gunbj.Load(L"..//backview//xinbeijing.bmp");
	PlaySound(_T("..//backview//chuchang.wav"), NULL, SND_FILENAME | SND_ASYNC| SND_LOOP);
	MessageBox( _T("1 发射和展开护盾消耗能量，第二形态射击消耗的能量更多\n2 一共有四种血量不同的敌人，单射的，乱射的，追踪的。\n3 一共7关，最后一关出现BOOS，打死BOSS获胜\n4 K键无敌\n5 窗口上方菜单有控制说明"), L"游戏说明", NULL);
	//启动游戏,
	SetTimer(1, 25, NULL);
	//关卡时间线
	SetTimer(2, 15000, NULL);
	
	return TRUE;
}
void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	//背景
	static int pbj=0;
	pbj += 20; if (pbj >= 3989)pbj = 0;
	gunbj.Draw(pMemDC->m_hDC, 0, -3989+pbj, 803, 5039);
	//绘制 导弹、爆炸、敌机、子弹、补给
	for (int i = 0; i < 8; i++)
	{
			POSITION pos1, pos2;
			for (pos1 = m_ObjList[i].GetHeadPosition(); (pos2 = pos1) != NULL; )
			{
				
				if (i < 7) {
					CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext(pos1);
					if (!pObj->Draw(pMemDC, FALSE))
					{
						m_ObjList[i].RemoveAt(pos2);
						delete pObj;
					}
				}
				else {
					if (m_pMe == NULL)break;
		           
					CNewBall* nball = (CNewBall*)m_ObjList[i].GetNext(pos1);
					if (!nball->Draw(pMemDC,false, m_pMe->GetPoint()))
					{
						m_ObjList[i].RemoveAt(pos2);
						delete nball;
					}
					
				}
			}		
	}
	
	//绘制我方战机以及状态 分数 关卡
	paintui(m_pMemDC);

	//复制内存DC到设备DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	static int nCreator = rand() %5+50;
	//随机产生敌机
	if(nCreator<=0)
	{
		nCreator = rand()%5+40-guan*5;
		m_ObjList[enEnemy].AddTail(new CEnemy);	
		if(nCreator%5==3)m_ObjList[enBuji].AddTail(new CBuji);
		if (nCreator % 10 == 3)m_ObjList[enEnemy2].AddTail(new CEnemy2);
		if (nCreator % 10 == 4)m_ObjList[enEnemy3].AddTail(new CEnemy3);
	}
	nCreator--;
	//重新开始
	restart();
	if (m_pMe == NULL)
		return;
	//获得盾牌 状态
	statedun();
	//检测四个方向键，移动战机
	move();
	//产生战机导弹
	meshot();
	//敌机发射子弹
	CPoint PlanePt = m_pMe->GetPoint();
	for(POSITION ePos=m_ObjList[enEnemy].GetHeadPosition();ePos!=NULL;)
	{
          CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		  if(!pEnemy->Fired())
			  continue;
		  CPoint  ePt = pEnemy->GetPoint();

		  BOOL by=FALSE;

		  //敌机在战机前面
		  if(pEnemy->GetMontion()==1 && ePt.y<PlanePt.y)
		         by=  TRUE;
		  //敌机在战机后面
		  if(pEnemy->GetMontion()==-1 && ePt.y>PlanePt.y)
				 by=  TRUE;	

		  if(by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt.x+CEnemy::ENEMY_HEIGHT/2-15,ePt.y+70,pEnemy->GetMontion(),0));
		  }
	}
	//敌人2发射子弹
	for (POSITION ePos = m_ObjList[enEnemy2].GetHeadPosition(); ePos != NULL;)
	{
		CEnemy2* pEnemy = (CEnemy2*)m_ObjList[enEnemy2].GetNext(ePos);
		CPoint  ePt = pEnemy->GetPoint();
		for (int i = 1; i <=5; i++) {
			if (rand() % 120 == 1)
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 100, ePt.y + CEnemy2::ENEMY2_HEIGHT-50, pEnemy->GetMontion(), -3+i));
		}				
	}
	// 敌人3发射子弹
	for (POSITION ePos = m_ObjList[enEnemy3].GetHeadPosition(); ePos != NULL;)
	{
		CEnemy3* pEnemy = (CEnemy3*)m_ObjList[enEnemy3].GetNext(ePos);
		CPoint  ePt = pEnemy->GetPoint();		
			if (rand() % 100 == 1)
			m_ObjList[enNewball].AddTail(new CNewBall(ePt.x + 100, ePt.y + CEnemy3::ENEMY3_HEIGHT - 50 ));
		
	}
	//战机导弹炸掉敌机
	POSITION mPos1 = NULL, mPos2 = NULL;
	 for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
			CRect bRect = pBomb->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (int i = 0; i < 3; i++) {
				bool ifzha=0;
				for (ePos1 = m_ObjList[i].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
				{
					CGameObject* pem;
					CRect mRect; 
					if(i==0){
						pem = (CEnemy*)m_ObjList[i].GetNext(ePos1);
										
					}
					if (i == 1) {
						pem = (CEnemy2*)m_ObjList[i].GetNext(ePos1);
						 
					}if (i ==2) {
						pem = (CEnemy3*)m_ObjList[i].GetNext(ePos1);
											
					}	
					mRect = pem->GetRect();
					CRect tmpRect;
					if (tmpRect.IntersectRect(&bRect, mRect))
					{
						ifzha = 1;
						PlaySound(_T("..//backview//baozha.wav"), NULL, SND_FILENAME | SND_ASYNC);
						pem->shengming--;
						//打中添加爆炸效果
						m_ObjList[enExplosion].AddTail(
							new CExplosion(bRect.left, bRect.top)
						);
						//删除导弹
						m_ObjList[enBomb].RemoveAt(mPos2);
						delete pBomb;/////////////////////
						
						if (pem->shengming <= 0) {
							//添加爆炸效果
							m_ObjList[enExplosion].AddTail(
								new CExplosion(bRect.left, bRect.top)
							);
							//fenshu
							if (m_pMe != NULL)
								m_pMe->fenshu += 110;
							//删除敌机
							m_ObjList[i].RemoveAt(ePos2);
							delete pem;
							break;
						}
						break;
					}
				}
				if (ifzha == 1)break;
			}		
		}
	//敌机子弹炸掉战机
	gethurt();
	//吃血包
	if (m_pMe != NULL) {
		POSITION bPos1 = NULL, bPos2 = NULL;
		CRect mRect = m_pMe->GetRect();	
		if (m_pMe != NULL) {
			for (bPos1 = m_ObjList[enBuji].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
			{
				CBuji* pBuji = (CBuji*)m_ObjList[enBuji].GetNext(bPos1);
				CRect bRect = pBuji->GetRect();

				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//添加加血效果
					m_pMe->xueliang += 50;
					if (m_pMe->xueliang >= 200)m_pMe->xueliang = 200;
					PlaySound(_T("..//backview//huifu.wav"), NULL, SND_FILENAME | SND_ASYNC);
					//删除子弹
					m_ObjList[enBuji].RemoveAt(bPos2);
					delete pBuji;
					break;
				}
			}
		}
	}	
}
void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{	
		switch (nIDEvent) {
		case 1:if (ifz == 0) {
			if (guan <= 6) {
				UpdateFrame(m_pMemDC);
				AI();
			}
			else {
				XUpdateFrame(m_pMemDC);
				XAI();
			}
			return;
		}
			  return;
		case 2:if (m_pMe != NULL&&ifz==0) {
			guan++;
			if (guan >= 7)guan = 7;
		}
			  return;
		default: return;
		}
	
	
}
//暂停 开始游戏 变形态
void CPlaneGameView::OnKeyUp(UINT a, UINT nRepCnt, UINT nFlags) {
	if (a == 0x5A) {
		if (ifz == 1) { ifz = 0; return; }
		if (ifz == 0) {
			ifz = 1;
			m_pDC->SetBkMode(TRANSPARENT);
			m_pDC->SetTextAlign(TA_CENTER);
			m_pDC->SetTextColor(RGB(255, 255, 255));
			m_pDC->TextOutW(GAME_WIDTH / 2 , GAME_HEIGHT / 3 + 50, L"已暂停！");
			PlaySound(_T("..//backview//chuchang.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
	}
	if (a == 0x42&&m_pMe!=NULL) {
		m_pMe->bian();
	}	
	if (a == 0x4B) {
		if (wudi == 0)wudi = 1;
		else wudi = 0;
	}
}
//最终章！
void CPlaneGameView::XUpdateFrame(CDC* pMemDC)
{
	if (Boss != NULL) {
		//绘制天空
		CBitmap back;
		back.LoadBitmapW(xbackview);

		pMemDC->SelectObject(back);
		//画Boss
		Boss->Draw(pMemDC, false);

		//绘制 导弹、爆炸、敌机、子弹
		for (int i = 0; i < 6; i++)
		{
			POSITION pos1, pos2;
			for (pos1 = m_ObjList[i].GetHeadPosition(); (pos2 = pos1) != NULL; )
			{
				CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext(pos1);
				if (!pObj->Draw(pMemDC, FALSE))
				{
					m_ObjList[i].RemoveAt(pos2);
					delete pObj;
				}
			}
		}
		//绘制我方战机以及状态(boss) 分数 关卡
		xpaintui( pMemDC);
		//复制内存DC到设备DC
		m_pDC->BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, m_pMemDC, 0, 0, SRCCOPY);
	}
	else {
		//绘制胜利画面
		CBitmap back;
		back.LoadBitmapW(xbackview);
		pMemDC->SelectObject(back);
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(255, 0, 0));
		CString pingjia;
		pingjia.Format(L"您最终得分：%d", finalfen);
		pMemDC->TextOut(GAME_WIDTH / 2 - 15, GAME_HEIGHT / 3, pingjia);
		pMemDC->TextOut(GAME_WIDTH / 2 - 15, GAME_HEIGHT / 3 -25, L"游戏结束\n您取得了胜利！");
		PlaySound(_T("..//backview//shengli.wav"), NULL, SND_FILENAME | SND_ASYNC| SND_LOOP);
		m_pDC->BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, m_pMemDC, 0, 0, SRCCOPY);
		KillTimer(1); KillTimer(2);
	}
}
void CPlaneGameView::XAI()
{

	//重新开始
	restart();
	if (m_pMe == NULL)
		return;
	//获得盾牌 状态
	statedun();


	//检测四个方向键，移动战机
	move();

	//产生战机导弹
	meshot();


	//Boss发射子弹
	if (Boss != NULL) {
		CPoint PlanePt = m_pMe->GetPoint();
		CPoint BossPt = Boss->GetPoint();

		if (BossPt.x <= PlanePt.x + CMyPlane::PLANE_WIDTH / 2 && BossPt.x + Boss->BOSS_WEIGHT > PlanePt.x + CMyPlane::PLANE_WIDTH / 2)
		{
			for (int i = 1; i <= 5; i++) {
				if (rand() % 15 == 1)
					m_ObjList[enBall].AddTail(new CBall(BossPt.x -30 + i * 60, BossPt.y + 166, 1,0));
			}

		}

	}
	//boss子弹炸掉战机

	gethurt();


	//战机导弹射中boss
	if (Boss != NULL) {
		POSITION mPos1 = NULL, mPos2 = NULL;
		for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
			CRect bRect = pBomb->GetRect();
			CRect mRect = Boss->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				Boss->xueliang-=1;
				//添加爆炸效果				
				m_ObjList[enExplosion].AddTail(
					new CExplosion(bRect.left -23, bRect.top)
				);
				PlaySound(_T("..//backview//baozha.wav"), NULL, SND_FILENAME | SND_ASYNC);
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;
				//fenshu
				if (m_pMe != NULL)
					m_pMe->fenshu += 99;
				if (Boss->xueliang <= 0)Boss = NULL;


				break;

			}

		}

	}

}
//重新开始
void CPlaneGameView::restart() {
	if (GetKey(0x41) && m_pMe == NULL) {
		m_pMe = new CMyPlane;
		Boss = new CBoss;
		guan = 1;
		for (int i = 0; i < 8; i++) {
			m_ObjList[i].RemoveAll();
		}
	}
}
//获得盾牌状态
void CPlaneGameView::statedun() {
	if (m_pMe != NULL) {
		m_pMe->ifdun = 0;
		m_pMe->nengliang+=2;
		if (m_pMe->nengliang >= 200)m_pMe->nengliang = 200;
		if (GetKey(0x46) && m_pMe->nengliang > 4) {
			m_pMe->ifdun = 1;
			m_pMe->nengliang -= 3;
			if (m_pMe->nengliang <= 3)m_pMe->nengliang = 3;
		}
	}
}
//移动战机
void CPlaneGameView::move() {
	for (int i = 0; i < 4; i++)
	{
		int nMeMotion = 0;
		m_pMe->SetVerMotion(0);
		m_pMe->SetHorMotion(0);

		nMeMotion = GetKey(VK_UP);
		if (nMeMotion == 1)
			m_pMe->SetVerMotion(3);

		nMeMotion = GetKey(VK_DOWN);
		if (nMeMotion == 1)
			m_pMe->SetVerMotion(-3);

		nMeMotion = GetKey(VK_RIGHT);
		if (nMeMotion == 1)
			m_pMe->SetHorMotion(3);

		nMeMotion = GetKey(VK_LEFT);
		if (nMeMotion == 1)
			m_pMe->SetHorMotion(-3);
	}
}
//产生战机导弹
void CPlaneGameView::meshot() {
	
	if (GetKey(VK_SPACE) == 1 && m_pMe != NULL)//按下了空格键
	{
		CPoint pt = m_pMe->GetPoint();
		if (m_pMe->Fired() && m_pMe->nengliang > 4)
		{			
			if (m_pMe->ifyuan == 1) {
				for (int i = 0; i < 3; i++) {
					m_ObjList[enBomb].AddTail(new CBomb(pt.x + i * 50 - 3, pt.y - 5, 1, 0));
				}
				for (int i = 0; i < 3; i++) {
					m_ObjList[enBomb].AddTail(new CBomb(pt.x + i * 50 - 3, pt.y + 100, 0, 0));
				}
				PlaySound(_T("..//backview//shot.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			else {
				for (int i = 0; i < 5; i++) {
					m_ObjList[enBomb].AddTail(new CBomb(pt.x + i * 24, pt.y - 5, 1, -2 + i));
				}
				for (int i = 0; i < 5; i++) {
					m_ObjList[enBomb].AddTail(new CBomb(pt.x + i * 24, pt.y + 100, 0, -2 + i));
				}
				PlaySound(_T("..//backview//shot.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
		}if (m_pMe->ifyuan == 1)
			m_pMe->nengliang -= 3;
		else m_pMe->nengliang -= 4;
		if (m_pMe->nengliang <= 1)m_pMe->nengliang = 1;
	}
	//宠物僚机随机发射
	if (rand() % 25 == 1) {
		CPoint pt = Liaoji->GetPoint();
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 25, pt.y - 5, 1, 0));
	}
}
//plane受伤
void CPlaneGameView::gethurt() {
	POSITION bPos1 = NULL, bPos2 = NULL;
	CRect mRect = m_pMe->GetRect();
	for (bPos1 = m_ObjList[enBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//添加爆炸效果
			m_ObjList[enExplosion].AddTail(
				new CExplosion(bRect.left, bRect.top)
			);
			//删除子弹
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;
			//删除战机
			//delete m_pMe;
			if (m_pMe->ifdun == false&&wudi==0) {
				m_pMe->xueliang -= 19;
				if (m_pMe->xueliang <= 0)m_pMe = NULL;
			}
			break;
		}
	}
	//NewBall
	for (bPos1 = m_ObjList[enNewball].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CNewBall* pBall = (CNewBall*)m_ObjList[enNewball].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//添加爆炸效果
			m_ObjList[enExplosion].AddTail(
				new CExplosion(bRect.left, bRect.top)
			);
			//删除子弹
			m_ObjList[enNewball].RemoveAt(bPos2);
			delete pBall;
			//删除战机
			//delete m_pMe;
			if (m_pMe->ifdun == false&&wudi==0) {
				m_pMe->xueliang -= 20;
				if (m_pMe->xueliang <= 0)m_pMe = NULL;
			}
			break;
		}
	}
}
//绘制ui
void CPlaneGameView::paintui(CDC* pMemDC) {
	if (m_pMe != NULL)
	{
		Liaoji->Draw(m_pMemDC, false, m_pMe->GetPoint());
		m_pMe->Draw(m_pMemDC, FALSE);
		CSize csm(0, 20); CSize csn(0, 20);
		csm.cx = m_pMe->xueliang;
		csn.cx = m_pMe->nengliang;
		pMemDC->DrawState(POINT{ 500,10 }, csm, xue, DST_BITMAP, NULL);
		pMemDC->DrawState(POINT{ 500,40 }, csn, nengliang, DST_BITMAP, NULL);
		//分数
		CString fenshu;
		CString xueliang;
		CString nengliang;
		CString guanqia;
		fenshu.Format(L"分数：%d", finalfen = m_pMe->fenshu);
		xueliang.Format(L"%d%%", m_pMe->xueliang / 2);
		nengliang.Format(L"%d%%", m_pMe->nengliang / 2);
		guanqia.Format(L"当前关卡：%d /7 关 ", guan);
		pMemDC->TextOut(350, 10, fenshu);
		pMemDC->TextOut(720, 10, xueliang);
		pMemDC->TextOut(720, 40, nengliang);
		pMemDC->TextOut(80, 10, guanqia);
	}
	else
	{   //Game Over
		CString pingjia;
		pingjia.Format(L"您最终得分：%d", finalfen);
		pMemDC->TextOut(GAME_WIDTH / 2 - 15, GAME_HEIGHT / 3 - 25, str);
		pMemDC->TextOut(GAME_WIDTH / 2 - 10, GAME_HEIGHT / 3, pingjia);
		pMemDC->TextOut(GAME_WIDTH / 2 - 3, GAME_HEIGHT / 3 + 30, L"按A键重新开始>>");
	}
	//绘制状态
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 255, 255));
	pMemDC->TextOut(480, 10, L"生命：");
	pMemDC->TextOut(480, 40, L"能量：");
	if(wudi==1)pMemDC->TextOut(120, 50, L"已经进入开发者（无敌)模式");
}
void CPlaneGameView::xpaintui(CDC* pMemDC) {
	if (m_pMe != NULL)
	{
		Liaoji->Draw(m_pMemDC, false, m_pMe->GetPoint());
		m_pMe->Draw(m_pMemDC, FALSE);
		CSize csm(0, 20); CSize csn(0, 20); CSize csb(0, 20);
		csm.cx = m_pMe->xueliang;
		csn.cx = m_pMe->nengliang;
		csb.cx = Boss->xueliang;
		pMemDC->DrawState(POINT{ 500,10 }, csm, xue, DST_BITMAP, NULL);
		pMemDC->DrawState(POINT{ 500,40 }, csn, nengliang, DST_BITMAP, NULL);
		pMemDC->DrawState(POINT{ 200,40 }, csb, xue, DST_BITMAP, NULL);
		//分数
		CString fenshu;
		CString xueliang;
		CString nengliang;
		CString guanqia;
		fenshu.Format(L"分数：%d", finalfen = m_pMe->fenshu);
		xueliang.Format(L"%d%%", m_pMe->xueliang / 2);
		nengliang.Format(L"%d%%", m_pMe->nengliang / 2);
		guanqia.Format(L"当前关卡：终章！");
		pMemDC->TextOut(350, 10, fenshu);
		pMemDC->TextOut(720, 10, xueliang);
		pMemDC->TextOut(720, 40, nengliang);
		pMemDC->TextOut(80, 10, guanqia);
	}
	else
	{   //Game Over
		CString pingjia;
		pingjia.Format(L"您最终得分：%d", finalfen);
		pMemDC->TextOut(GAME_WIDTH / 2 - 15, GAME_HEIGHT / 3 - 25, str);
		pMemDC->TextOut(GAME_WIDTH / 2 - 10, GAME_HEIGHT / 3, pingjia);
		pMemDC->TextOut(GAME_WIDTH / 2 - 3, GAME_HEIGHT / 3 + 30, L"按A键重新开始>>");
	}
	//绘制状态
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 255, 255));
	pMemDC->TextOut(480, 10, L"生命：");
	pMemDC->TextOut(480, 40, L"能量：");
	pMemDC->TextOut(180, 40, L"BOSS：");
	if (wudi == 1)pMemDC->TextOut(120, 65, L"已经进入开发者（无敌)模式");
}