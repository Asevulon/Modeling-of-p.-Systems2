
// MyDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Modeling of p. Systems2.h"
#include "MyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно MyDlg



MyDlg::MyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODELING_OF_P_SYSTEMS2_DIALOG, pParent)
	, m_Na(0)
	, m_Dots(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void MyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, drw);
	DDX_Text(pDX, IDC_EDIT1, m_Na);
	DDX_Text(pDX, IDC_EDIT2, m_L);
	DDX_Text(pDX, IDC_EDIT3, m_V);
	DDX_Text(pDX, IDC_EDIT4, m_Dots);
}

BEGIN_MESSAGE_MAP(MyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &MyDlg::OnBnClickedOk)
	ON_MESSAGE(MS_DO_ITERATION,&MyDlg::OnDoIteration)
END_MESSAGE_MAP()


// Обработчики сообщений MyDlg

BOOL MyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	drw.SetPadding(10, 5, 22, 22);
	drw.SetTitle(L"Расчет напряжения в легированном полупроводнике");
	rg.parent = GetSafeHwnd();

	m_V = 5;
	m_Na = 50;
	m_L = 2e-6;
	m_Dots = 500;
	UpdateData(FALSE);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void MyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR MyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void MyDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	//rg.Na = 0.5e23;
	UpdateData();
	rg.Na = m_Na;
	rg.N0 = 1e15;
	rg.fi0 = 1;
	rg.Ld = sqrt(300 * 11.68 * 8.85418781762039 * 1e-12 * 1.380649 * 1e-23 / (1.602176634 * 1e-19 * 1.602176634 * 1e-19 * rg.Na * rg.N0));
	//rg.psy0 = 1e-7 / rg.fi0;
	rg.psy0 = m_V / rg.fi0;
	rg.na = rg.Na;
	//rg.L = 2e-6 / rg.Ld;
	rg.L = m_L / rg.Ld;
	rg.SetH(rg.L / (m_Dots - 1));

	rg.prevVals = rg.MakeStartVals();

	rg.stop = false;
	PostMessage(MS_DO_ITERATION);
}


void MyDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
		rg.test1();
		rg.test2();
		drw.SetData(rg.valsOut, rg.keys);
		drw.Invalidate();
		if (rg.stop)MessageBox(L"STOP", L"STOP", MB_OK);
}


LRESULT MyDlg::OnDoIteration(WPARAM wParam, LPARAM lParam)
{
	rg.test1();
	rg.test2();
	drw.SetData(rg.valsOut, rg.keys);
	drw.Invalidate();
	if (rg.stop)MessageBox(L"STOP", L"STOP", MB_ICONHAND);
	else PostMessage(MS_DO_ITERATION);

	return NULL;
}