// Tetris2Dlg.h : ͷ�ļ�
//

#pragma once
#include "MyStatic.h"
#include <vector>
using namespace std;

// CTetris2Dlg �Ի���
class CTetris2Dlg : public CDialog
{
// ����
public:
	CTetris2Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CTetris2Dlg();

// �Ի�������
	enum { IDD = IDD_TETRIS2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	//CShapeX m_shapex;
	void Draw(CPaintDC& dc);
	void OnMenuGame(UINT nID);

private:

	//�˶���
	CMyStatic* m_pStt1;
	CMyStatic* m_pStt2;
	CMyStatic* m_pStt3;
	CMyStatic* m_pStt4;

	//Ԥ��ʾ��
	CMyStatic m_sttA;
	CMyStatic m_sttB;
	CMyStatic m_sttC;
	CMyStatic m_sttD;

	COLORREF m_col1;
	COLORREF m_col2;
	COLORREF m_col3;
	COLORREF m_col4;

	CBrush m_brush1;
	CBrush m_brush2;
	CBrush m_brush3;
	CBrush m_brush4;

	enum TURN_DIRECTION m_iTurnDirect;
	bool m_bIsStop;

	int m_iShape;
	int m_iTurnCnt;			//��ת����0, 1, 2 ,3

	vector< CMyStatic* > m_vecSttStop;
public:	
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void MoveWindowOffSet(CWnd* pWnd, int iXOffSet, int iYOffSet);
	void Move4SttOffSet(int iXOffSet, int iYOffSet);
	bool IsWindowCanMove(CWnd* pWnd, int iXOffSet, int iYOffSet);
	bool Is4SttCanMove(int iXOffSet, int iYOffSet);
	void OnMenuStart();
	void GenerateDiamond();
	void SttStop();
	void ClearStt();

	bool TouchDiamond(const CRect& rectDiamond, const vector< CMyStatic* >& vecSttStop);
	int TurnPoint(CRect rect1, CRect rect2, CRect rect3, CRect rect4);
	void Turn();
	void ShapeITurn();
	void ShapeLTurn();
	void ShapeOTurn();
	void ShapeKTurn();
	void ShapeZTurn();
	void EatPerLine();
	void AfterEatDown(int iYPos,const vector< CMyStatic* >& vecSttStop);
	void DestoyDiamond(vector< CMyStatic* >& vecPerLine, vector< CMyStatic* >& vecSttStop);

};





