
// PhaseProblemDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "PhaseProblem.h"
#include "PhaseProblemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CPhaseProblemDlg



CPhaseProblemDlg::CPhaseProblemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PHASEPROBLEM_DIALOG, pParent)
	, A1(4)
	, A2(2)
	, A3(3.5)
	, stok1(3)
	, stok2(3)
	, stok3(3)
	, mat1(150)
	, mat2(380)
	, mat3(600)
	, fd(1)
	, N(1024)
	, A4(2.5)
	, A5(3.5)
	, stok4(3)
	, stok5(3)
	, mat4(800)
	, mat5(920)
	, TAU(0.000001)
	, end(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPhaseProblemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT9, A1);
	DDX_Text(pDX, IDC_EDIT4, A2);
	DDX_Text(pDX, IDC_EDIT6, A3);
	DDX_Text(pDX, IDC_EDIT10, stok1);
	DDX_Text(pDX, IDC_EDIT3, stok2);
	DDX_Text(pDX, IDC_EDIT7, stok3);
	DDX_Text(pDX, IDC_EDIT11, mat1);
	DDX_Text(pDX, IDC_EDIT8, mat2);
	DDX_Text(pDX, IDC_EDIT5, mat3);
	DDX_Text(pDX, IDC_EDIT2, fd);
	DDX_Text(pDX, IDC_EDIT1, N);
	DDX_Text(pDX, IDC_EDIT12, A4);
	DDX_Text(pDX, IDC_EDIT16, A5);
	DDX_Text(pDX, IDC_EDIT13, stok4);
	DDX_Text(pDX, IDC_EDIT17, stok5);
	DDX_Text(pDX, IDC_EDIT15, mat4);
	DDX_Text(pDX, IDC_EDIT18, mat5);
	DDX_Text(pDX, IDC_EDIT20, TAU);
	DDX_Text(pDX, IDC_EDIT21, end);
}

BEGIN_MESSAGE_MAP(CPhaseProblemDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FINDPHASE, &CPhaseProblemDlg::OnBnClickedFindphase)
	ON_BN_CLICKED(IDC_STOP, &CPhaseProblemDlg::OnBnClickedStop)
END_MESSAGE_MAP()


// Обработчики сообщений CPhaseProblemDlg

BOOL CPhaseProblemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	drwSig.Create(GetDlgItem(IDC_SIGNAL)->GetSafeHwnd());
	drwAmpl.Create(GetDlgItem(IDC_ASPECTR)->GetSafeHwnd());
	canDraw = false;

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CPhaseProblemDlg::OnPaint()
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
		if (canDraw)
		{
			drwSig.ReDraw();
			drwAmpl.ReDraw();
		}
		canDraw = true;
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CPhaseProblemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPhaseProblemDlg::OnBnClickedFindphase()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(TRUE);
	double A[] = { A1, A2, A3, A4, A5 };
	double stok[] = { stok1, stok2, stok3, stok4, stok5 };
	double mat[] = { mat1, mat2, mat3, mat4, mat5 };
	signal s(A, stok, mat, fd, N);
	UpdateData(FALSE);
	auto kupola = s.GetSig();
	drwSig.DrawPoints(kupola, L"t", L"A", N / fd, 1 / fd);
	vector<double> newsig, srav;
	vector<base> spectr;
	spectr.insert(spectr.end(), kupola.begin(), kupola.end());
	s.fft(spectr, true);
	vector<double> ampl_spectr;
	for (int i = 0; i < spectr.size(); i++) ampl_spectr.push_back(sqrt(spectr[i].real() * spectr[i].real() + spectr[i].imag() * spectr[i].imag()));
	s.Set_ampl_spectr(ampl_spectr);
	drwAmpl.DrawPoints(ampl_spectr, L"f", L"A", N / fd, 1 / fd);
	s.Fienup(newsig, TAU, drwSig, msg);
	
	bool flag = false;
	int count(0);
	double a;
	while (1)
	{
		if (flag) break;
		
		for (int i = 0; i < N; i++)
		{
			srav.push_back(abs(newsig[i] - kupola[i]));
		}

		a = 100 * s.Es(srav) / s.Es(kupola);
		end.Format(L"%.2f", a);
		end += L" %";
		UpdateData(FALSE);
		if (a < 2) break;
		count++;
		s.Sdvig(newsig);
		
		if (count == 2 * N + 1)
		{
			/*MessageBox(L"Не найдено", L"Error", NULL);
			break; */
			s.Fienup(newsig, TAU, drwSig, msg);
			count = 0;
		}

		if (count == N + 1)
		{
			reverse(newsig.begin(), newsig.end());
		}
		drwSig.DrawTwoSig(kupola, newsig, L"t", L"A", N / fd, 1 / fd);
		srav.clear();
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.lParam == (LPARAM("PAUSE")))
			{
				flag = true;
			}
		}
	}
}


void CPhaseProblemDlg::OnBnClickedStop()
{
	// TODO: добавьте свой код обработчика уведомлений
	WPARAM F = WPARAM("PAUSE");
	LPARAM O = LPARAM("PAUSE");
	PostThreadMessageA(GetCurrentThreadId(), 12345, F, O);
}
