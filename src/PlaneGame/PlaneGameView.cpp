// PlaneGameView.cpp : CPlaneGameView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CPlaneGameView ����/����
CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: �ڴ˴���ӹ������
	ifz = 0; guan = 1; wudi = 0;
}
CPlaneGameView::~CPlaneGameView()
{
}
BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView ����
void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}
// CPlaneGameView ��ӡ
BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}
void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}
void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}
// CPlaneGameView ���
#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}
void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CPlaneGameDoc* CPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG
// CPlaneGameView ��Ϣ�������
void CPlaneGameView::OnInitialUpdate()
{
	InitGame();
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	//��ʼ����Ϸ
	//InitGame();
}
void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
}
//��ʼ���� ���½��̣�����
BOOL CPlaneGameView::InitGame()
{
 xue.LoadBitmapW(xuetiao);
 nengliang.LoadBitmapW(nengliangtiao);
	CRect rc;
	GetClientRect(rc);

	//�������������
	srand( (unsigned)time( NULL ) );

	//�����豸DC
	m_pDC = new CClientDC(this);
	
	//�����ڴ�DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//�����ڴ�λͼ
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//��λͼѡ���ڴ�DC
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
	//��������(ս��)
	m_pMe = new CMyPlane;
	Liaoji = new CLiaoJi;
	Boss = new CBoss;
	//���ر���
	gunbj.Load(L"..//backview//xinbeijing.bmp");
	PlaySound(_T("..//backview//chuchang.wav"), NULL, SND_FILENAME | SND_ASYNC| SND_LOOP);
	MessageBox( _T("1 �����չ�����������������ڶ���̬������ĵ���������\n2 һ��������Ѫ����ͬ�ĵ��ˣ�����ģ�����ģ�׷�ٵġ�\n3 һ��7�أ����һ�س���BOOS������BOSS��ʤ\n4 K���޵�\n5 �����Ϸ��˵��п���˵��"), L"��Ϸ˵��", NULL);
	//������Ϸ,
	SetTimer(1, 25, NULL);
	//�ؿ�ʱ����
	SetTimer(2, 15000, NULL);
	
	return TRUE;
}
void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	//����
	static int pbj=0;
	pbj += 20; if (pbj >= 3989)pbj = 0;
	gunbj.Draw(pMemDC->m_hDC, 0, -3989+pbj, 803, 5039);
	//���� ��������ը���л����ӵ�������
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
	
	//�����ҷ�ս���Լ�״̬ ���� �ؿ�
	paintui(m_pMemDC);

	//�����ڴ�DC���豸DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	static int nCreator = rand() %5+50;
	//��������л�
	if(nCreator<=0)
	{
		nCreator = rand()%5+40-guan*5;
		m_ObjList[enEnemy].AddTail(new CEnemy);	
		if(nCreator%5==3)m_ObjList[enBuji].AddTail(new CBuji);
		if (nCreator % 10 == 3)m_ObjList[enEnemy2].AddTail(new CEnemy2);
		if (nCreator % 10 == 4)m_ObjList[enEnemy3].AddTail(new CEnemy3);
	}
	nCreator--;
	//���¿�ʼ
	restart();
	if (m_pMe == NULL)
		return;
	//��ö��� ״̬
	statedun();
	//����ĸ���������ƶ�ս��
	move();
	//����ս������
	meshot();
	//�л������ӵ�
	CPoint PlanePt = m_pMe->GetPoint();
	for(POSITION ePos=m_ObjList[enEnemy].GetHeadPosition();ePos!=NULL;)
	{
          CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		  if(!pEnemy->Fired())
			  continue;
		  CPoint  ePt = pEnemy->GetPoint();

		  BOOL by=FALSE;

		  //�л���ս��ǰ��
		  if(pEnemy->GetMontion()==1 && ePt.y<PlanePt.y)
		         by=  TRUE;
		  //�л���ս������
		  if(pEnemy->GetMontion()==-1 && ePt.y>PlanePt.y)
				 by=  TRUE;	

		  if(by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt.x+CEnemy::ENEMY_HEIGHT/2-15,ePt.y+70,pEnemy->GetMontion(),0));
		  }
	}
	//����2�����ӵ�
	for (POSITION ePos = m_ObjList[enEnemy2].GetHeadPosition(); ePos != NULL;)
	{
		CEnemy2* pEnemy = (CEnemy2*)m_ObjList[enEnemy2].GetNext(ePos);
		CPoint  ePt = pEnemy->GetPoint();
		for (int i = 1; i <=5; i++) {
			if (rand() % 120 == 1)
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 100, ePt.y + CEnemy2::ENEMY2_HEIGHT-50, pEnemy->GetMontion(), -3+i));
		}				
	}
	// ����3�����ӵ�
	for (POSITION ePos = m_ObjList[enEnemy3].GetHeadPosition(); ePos != NULL;)
	{
		CEnemy3* pEnemy = (CEnemy3*)m_ObjList[enEnemy3].GetNext(ePos);
		CPoint  ePt = pEnemy->GetPoint();		
			if (rand() % 100 == 1)
			m_ObjList[enNewball].AddTail(new CNewBall(ePt.x + 100, ePt.y + CEnemy3::ENEMY3_HEIGHT - 50 ));
		
	}
	//ս������ը���л�
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
						//������ӱ�ըЧ��
						m_ObjList[enExplosion].AddTail(
							new CExplosion(bRect.left, bRect.top)
						);
						//ɾ������
						m_ObjList[enBomb].RemoveAt(mPos2);
						delete pBomb;/////////////////////
						
						if (pem->shengming <= 0) {
							//��ӱ�ըЧ��
							m_ObjList[enExplosion].AddTail(
								new CExplosion(bRect.left, bRect.top)
							);
							//fenshu
							if (m_pMe != NULL)
								m_pMe->fenshu += 110;
							//ɾ���л�
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
	//�л��ӵ�ը��ս��
	gethurt();
	//��Ѫ��
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
					//��Ӽ�ѪЧ��
					m_pMe->xueliang += 50;
					if (m_pMe->xueliang >= 200)m_pMe->xueliang = 200;
					PlaySound(_T("..//backview//huifu.wav"), NULL, SND_FILENAME | SND_ASYNC);
					//ɾ���ӵ�
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
//��ͣ ��ʼ��Ϸ ����̬
void CPlaneGameView::OnKeyUp(UINT a, UINT nRepCnt, UINT nFlags) {
	if (a == 0x5A) {
		if (ifz == 1) { ifz = 0; return; }
		if (ifz == 0) {
			ifz = 1;
			m_pDC->SetBkMode(TRANSPARENT);
			m_pDC->SetTextAlign(TA_CENTER);
			m_pDC->SetTextColor(RGB(255, 255, 255));
			m_pDC->TextOutW(GAME_WIDTH / 2 , GAME_HEIGHT / 3 + 50, L"����ͣ��");
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
//�����£�
void CPlaneGameView::XUpdateFrame(CDC* pMemDC)
{
	if (Boss != NULL) {
		//�������
		CBitmap back;
		back.LoadBitmapW(xbackview);

		pMemDC->SelectObject(back);
		//��Boss
		Boss->Draw(pMemDC, false);

		//���� ��������ը���л����ӵ�
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
		//�����ҷ�ս���Լ�״̬(boss) ���� �ؿ�
		xpaintui( pMemDC);
		//�����ڴ�DC���豸DC
		m_pDC->BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, m_pMemDC, 0, 0, SRCCOPY);
	}
	else {
		//����ʤ������
		CBitmap back;
		back.LoadBitmapW(xbackview);
		pMemDC->SelectObject(back);
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(255, 0, 0));
		CString pingjia;
		pingjia.Format(L"�����յ÷֣�%d", finalfen);
		pMemDC->TextOut(GAME_WIDTH / 2 - 15, GAME_HEIGHT / 3, pingjia);
		pMemDC->TextOut(GAME_WIDTH / 2 - 15, GAME_HEIGHT / 3 -25, L"��Ϸ����\n��ȡ����ʤ����");
		PlaySound(_T("..//backview//shengli.wav"), NULL, SND_FILENAME | SND_ASYNC| SND_LOOP);
		m_pDC->BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, m_pMemDC, 0, 0, SRCCOPY);
		KillTimer(1); KillTimer(2);
	}
}
void CPlaneGameView::XAI()
{

	//���¿�ʼ
	restart();
	if (m_pMe == NULL)
		return;
	//��ö��� ״̬
	statedun();


	//����ĸ���������ƶ�ս��
	move();

	//����ս������
	meshot();


	//Boss�����ӵ�
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
	//boss�ӵ�ը��ս��

	gethurt();


	//ս����������boss
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
				//��ӱ�ըЧ��				
				m_ObjList[enExplosion].AddTail(
					new CExplosion(bRect.left -23, bRect.top)
				);
				PlaySound(_T("..//backview//baozha.wav"), NULL, SND_FILENAME | SND_ASYNC);
				//ɾ������
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
//���¿�ʼ
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
//��ö���״̬
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
//�ƶ�ս��
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
//����ս������
void CPlaneGameView::meshot() {
	
	if (GetKey(VK_SPACE) == 1 && m_pMe != NULL)//�����˿ո��
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
	//�����Ż��������
	if (rand() % 25 == 1) {
		CPoint pt = Liaoji->GetPoint();
		m_ObjList[enBomb].AddTail(new CBomb(pt.x + 25, pt.y - 5, 1, 0));
	}
}
//plane����
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
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(bRect.left, bRect.top)
			);
			//ɾ���ӵ�
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;
			//ɾ��ս��
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
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(bRect.left, bRect.top)
			);
			//ɾ���ӵ�
			m_ObjList[enNewball].RemoveAt(bPos2);
			delete pBall;
			//ɾ��ս��
			//delete m_pMe;
			if (m_pMe->ifdun == false&&wudi==0) {
				m_pMe->xueliang -= 20;
				if (m_pMe->xueliang <= 0)m_pMe = NULL;
			}
			break;
		}
	}
}
//����ui
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
		//����
		CString fenshu;
		CString xueliang;
		CString nengliang;
		CString guanqia;
		fenshu.Format(L"������%d", finalfen = m_pMe->fenshu);
		xueliang.Format(L"%d%%", m_pMe->xueliang / 2);
		nengliang.Format(L"%d%%", m_pMe->nengliang / 2);
		guanqia.Format(L"��ǰ�ؿ���%d /7 �� ", guan);
		pMemDC->TextOut(350, 10, fenshu);
		pMemDC->TextOut(720, 10, xueliang);
		pMemDC->TextOut(720, 40, nengliang);
		pMemDC->TextOut(80, 10, guanqia);
	}
	else
	{   //Game Over
		CString pingjia;
		pingjia.Format(L"�����յ÷֣�%d", finalfen);
		pMemDC->TextOut(GAME_WIDTH / 2 - 15, GAME_HEIGHT / 3 - 25, str);
		pMemDC->TextOut(GAME_WIDTH / 2 - 10, GAME_HEIGHT / 3, pingjia);
		pMemDC->TextOut(GAME_WIDTH / 2 - 3, GAME_HEIGHT / 3 + 30, L"��A�����¿�ʼ>>");
	}
	//����״̬
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 255, 255));
	pMemDC->TextOut(480, 10, L"������");
	pMemDC->TextOut(480, 40, L"������");
	if(wudi==1)pMemDC->TextOut(120, 50, L"�Ѿ����뿪���ߣ��޵�)ģʽ");
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
		//����
		CString fenshu;
		CString xueliang;
		CString nengliang;
		CString guanqia;
		fenshu.Format(L"������%d", finalfen = m_pMe->fenshu);
		xueliang.Format(L"%d%%", m_pMe->xueliang / 2);
		nengliang.Format(L"%d%%", m_pMe->nengliang / 2);
		guanqia.Format(L"��ǰ�ؿ������£�");
		pMemDC->TextOut(350, 10, fenshu);
		pMemDC->TextOut(720, 10, xueliang);
		pMemDC->TextOut(720, 40, nengliang);
		pMemDC->TextOut(80, 10, guanqia);
	}
	else
	{   //Game Over
		CString pingjia;
		pingjia.Format(L"�����յ÷֣�%d", finalfen);
		pMemDC->TextOut(GAME_WIDTH / 2 - 15, GAME_HEIGHT / 3 - 25, str);
		pMemDC->TextOut(GAME_WIDTH / 2 - 10, GAME_HEIGHT / 3, pingjia);
		pMemDC->TextOut(GAME_WIDTH / 2 - 3, GAME_HEIGHT / 3 + 30, L"��A�����¿�ʼ>>");
	}
	//����״̬
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 255, 255));
	pMemDC->TextOut(480, 10, L"������");
	pMemDC->TextOut(480, 40, L"������");
	pMemDC->TextOut(180, 40, L"BOSS��");
	if (wudi == 1)pMemDC->TextOut(120, 65, L"�Ѿ����뿪���ߣ��޵�)ģʽ");
}