
// FigureDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Figure.h"
#include "FigureDlg.h"
#include "afxdialogex.h"
#include "CPopup.h" // 추가

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFigureDlg 대화 상자



CFigureDlg::CFigureDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FIGURE_DIALOG, pParent)
	, m_radio(0)
	, m_edit(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFigureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_ctlList);
	DDX_Radio(pDX, IDC_RADIO_CIRCLE, m_radio);
	DDX_Text(pDX, IDC_EDIT, m_edit);
}

BEGIN_MESSAGE_MAP(CFigureDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTT_DRAW, &CFigureDlg::OnBnClickedButtDraw)
	ON_COMMAND(ID_EXIT, &CFigureDlg::OnExit)
	ON_WM_TIMER()
	ON_COMMAND(ID_TIME, &CFigureDlg::OnTime)
	ON_COMMAND(ID_STOP, &CFigureDlg::OnStop)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


// CFigureDlg 메시지 처리기

BOOL CFigureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_ctlList.AddString(_T("회색"));
	m_ctlList.AddString(_T("하얀색"));
	m_ctlList.AddString(_T("연한 빨간색"));
	m_ctlList.AddString(_T("하늘색"));
	m_ctlList.AddString(_T("초록색"));
	m_radio = -1;// 안적으면 원이 그냥 실행시 출력..
	rgb = RGB(255, 255, 255);//하얀색
	m_edit = 1;
	i = 100;
	m_point.x = 200;
	m_point.y = 300;
	m_isCreate = FALSE;
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CFigureDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CFigureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
			CClientDC dc(this);
			CPen pEn;
			pEn.CreatePen(PS_SOLID, m_edit, RGB(0, 0, 0));//선 굵기 확인을 위해 색은 검정색으로 고정
			CPen* oldPen = dc.SelectObject(&pEn);
			CBrush brush;//내부색상
			brush.CreateSolidBrush(rgb);
			CBrush* oldBrush = dc.SelectObject(&brush);
			if (m_radio == 0) { //원 선택시
				if (m_isClicked == TRUE) {
					dc.Ellipse(m_point.x - i, m_point.y - i, m_point.x + i, m_point.y + i);
				}
				else {
					dc.Ellipse(m_point.x - i, m_point.y - i, m_point.x + i, m_point.y + i);
				}
				if (value != 1) {
					if (bools == TRUE) {
						i += 10;
						if (i >= 190) bools = FALSE;
					}
					else if (bools == FALSE) {
						i -= 10;
						if (i <= 0) bools = TRUE;
					}
				}
			}
			else if (m_radio == 1) {//사각형 선택시
				if (m_isClicked == TRUE) {
					dc.Rectangle(m_point.x - i, m_point.y - i, m_point.x + i, m_point.y + i);
				}
				else {
					dc.Rectangle(m_point.x - i, m_point.y - i, m_point.x + i, m_point.y + i);
				}
				if (value != 1) {
					if (bools == TRUE) {
						i += 10;
						if (i >= 190) bools = FALSE;
					}
					else if (bools == FALSE) {
						i -= 10;
						if (i <= 0) bools = TRUE;
					}
				}
			}
			dc.SelectObject(oldPen);
			dc.SelectObject(oldBrush);
			pEn.DeleteObject();
			brush.DeleteObject();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CFigureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFigureDlg::OnBnClickedButtDraw()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;
	UpdateData(TRUE);
	m_isCreate = TRUE;
	value = 1;
	i = m_ctlList.GetCurSel();
	if (i == 0) {
		rgb = RGB(192, 192, 192);//회색
	}
	else if (i == 1) {
		rgb = RGB(255, 255, 255);//하얀색
	}
	else if (i == 2) {
		rgb = RGB(255, 102, 102);//연한 빨간색
	}
	else if (i == 3) {
		rgb = RGB(154, 204, 255);//하늘색
	}
	else if (i == 4) {
		rgb = RGB(0, 255, 0);//초록색
	}
	Invalidate(TRUE);
	UpdateData(FALSE);
}


void CFigureDlg::OnExit()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnOK();
}


void CFigureDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Invalidate(TRUE);
	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}


void CFigureDlg::OnTime()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_isCreate) {
		value = 0;
		bools = TRUE;
		CPopup popupDialog;
		if (popupDialog.DoModal() == IDOK) {//다이어로그 실행
			SetTimer(0, popupDialog.m_dEdit * 100, NULL);
		}
	}
	else {
		MessageBox(_T("먼저 도형을 만들어주세요!"));
	}
}


void CFigureDlg::OnStop()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	value = 1;
	KillTimer(0);
}

void CFigureDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_isClicked == TRUE) {
		m_point = point;
		Invalidate(TRUE);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CFigureDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_isClicked = TRUE;
	m_point = point;
	Invalidate(TRUE);
	CDialogEx::OnRButtonDown(nFlags, point);
}


void CFigureDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_isClicked = FALSE;
	Invalidate(TRUE);
	CDialogEx::OnRButtonUp(nFlags, point);
}
