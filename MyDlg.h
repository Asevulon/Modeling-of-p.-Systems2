
// MyDlg.h: файл заголовка
//

#pragma once
#include"Drawer.h"
#include"RG.h"




// Диалоговое окно MyDlg
class MyDlg : public CDialogEx
{
// Создание
public:
	MyDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODELING_OF_P_SYSTEMS2_DIALOG };
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
	Drawer drw;
	bool todo = true;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	RG rg;

	double m_Na;
	double m_L;
	double m_V;

	LRESULT OnDoIteration(WPARAM wParam, LPARAM lParam);
	int m_Dots;
};



/*
Параметры для L = 2 мкм
	Na = 0.5e23
	V = 1e-7



*/