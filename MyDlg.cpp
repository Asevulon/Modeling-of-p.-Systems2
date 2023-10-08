
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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void MyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, drw);
}

BEGIN_MESSAGE_MAP(MyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &MyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &MyDlg::OnBnClickedButton1)
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
	drw.SetTitle(L"Тестим рунге-кутту");
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
	double Na = 1e-3;
	double N0 = 1e-4;
	double fi0 = 0.026;
	double Ld = sqrt(300 * 11.68 * 8.85418781762039 * 1e-12 * 1.380649 * 1e-23 / (-1.602176634 * 1e-19 * -1.602176634 * 1e-19 * Na));
	rg.psy0 = 1e-5 / fi0;
	rg.na = 1e-3 / N0;
	rg.L = 1e-6 / Ld;
	rg.SetH(rg.L / 20);

	rg.prevVals = rg.MakeStartVals();
	rg.dy = -rg.psy0 / rg.L;
	rg.SetXYZ(0, 1, 0);
	rg.dyb = rg.dy;
	rg.yb = 0.1;
	/*while (!rg.stop)
	{
		rg.DoMainJob();
		drw.SetData(rg.prevVals, rg.keys);
		drw.Invalidate();
	}*/
}


void MyDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	if (todo)
	{
		rg.test1();
		drw.SetData(rg.alpha, rg.keys);
		drw.SetTitle(L"alpha");
		drw.Invalidate();
		todo = !todo;
	}
	else
	{
		rg.test2();
		drw.SetData(rg.valsY, rg.keys);
		drw.SetTitle(L"y(x)");
		drw.Invalidate();
		todo = !todo;
	}
}
