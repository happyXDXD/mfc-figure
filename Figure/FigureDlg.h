
// FigureDlg.h: 헤더 파일
//

#pragma once


// CFigureDlg 대화 상자
class CFigureDlg : public CDialogEx
{
// 생성입니다.
public:
	CFigureDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIGURE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ctlList;
	COLORREF rgb;
	afx_msg void OnBnClickedButtDraw();
	int m_radio;
	int m_edit;
	int i;
	BOOL bools;
	int value;
	afx_msg void OnExit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTime();
	afx_msg void OnStop();
	BOOL m_isClicked; //마우스 누른상태확인
	CPoint m_point;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	BOOL m_isCreate; //도형이 그려졌는지
};
