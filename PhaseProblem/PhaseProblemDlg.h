
// PhaseProblemDlg.h: файл заголовка
//

#pragma once
#include <algorithm> 
#include "Drawer.h"
#include "Signal.h"

// Диалоговое окно CPhaseProblemDlg
class CPhaseProblemDlg : public CDialogEx
{
// Создание
public:
	CPhaseProblemDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHASEPROBLEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	double A1;
	double A2;
	double A3;
	double stok1;
	double stok2;
	double stok3;
	double mat1;
	double mat2;
	double mat3;
	double fd;
	int N;
	afx_msg void OnBnClickedFindphase();
	Drawer drwSig;
	Drawer drwAmpl;
	bool canDraw;
	double A4;
	double A5;
	double stok4;
	double stok5;
	double mat4;
	double mat5;
	double TAU;
	afx_msg void OnBnClickedStop();
	MSG msg;
	CString end;
};
