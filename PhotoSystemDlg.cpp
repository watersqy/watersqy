// PhotoSystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "PhotoSystem.h"
#include "PhotoSystemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


void CPhotoSystemDlg::AppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CPhotoSystemDlg 对话框

CPhotoSystemDlg::CPhotoSystemDlg(CWnd* pParent /*=nullptr*/): CDialog(IDD_PHOTOSYSTEM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	flag = FALSE;
	zoom_value = 0;
	brightness_value = 0;
	contrast_value = 0;
	saturation_value = 0;
	view_value = 0;
	highlight_value = 0;
	shadow_value = 0;
	red_value = 0;
	green_value = 0;
	blue_value = 0;
}

void CPhotoSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ZOOM_VALUE, zoom_value);
	DDV_MinMaxInt(pDX, zoom_value, -99, 100);
	DDX_Text(pDX, IDC_BRIGHTNESS_VALUE, brightness_value);
	DDV_MinMaxInt(pDX, brightness_value, -100, 100);
	DDX_Text(pDX, IDC_CONTRAST_VALUE, contrast_value);
	DDV_MinMaxInt(pDX, contrast_value, -100, 100);
	DDX_Text(pDX, IDC_SATURATION_VALUE, saturation_value);
	DDV_MinMaxInt(pDX, saturation_value, 0, 100);
	DDX_Text(pDX, IDC_VIEW_VALUE, view_value);
	DDV_MinMaxInt(pDX, view_value, -100, 100);
	DDX_Text(pDX, IDC_HIGHLIGHT_VALUE, highlight_value);
	DDV_MinMaxInt(pDX, highlight_value, 0, 100);
	DDX_Text(pDX, IDC_SHADOW_VALUE, shadow_value);
	DDV_MinMaxInt(pDX, shadow_value, 0, 100);
	DDX_Text(pDX, IDC_RED_VALUE, red_value);
	DDV_MinMaxInt(pDX, red_value, -255, 255);
	DDX_Text(pDX, IDC_GREEN_VALUE, green_value);
	DDV_MinMaxInt(pDX, green_value, -255, 255);
	DDX_Text(pDX, IDC_BLUE_VALUE, blue_value);
	DDV_MinMaxInt(pDX, blue_value, -255, 255);
}

BEGIN_MESSAGE_MAP(CPhotoSystemDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	//关于对话框
	ON_COMMAND(ID_APP_ABOUT, &CPhotoSystemDlg::AppAbout)
	ON_COMMAND(ID_ADD_GRAIN, &CPhotoSystemDlg::RankDlg)

	//按钮
	ON_BN_CLICKED(IDC_COMPARE, &CPhotoSystemDlg::ComparePhoto)
	ON_BN_CLICKED(IDC_REIMG, &CPhotoSystemDlg::RePhoto)
	ON_BN_CLICKED(IDC_ROTATE, &CPhotoSystemDlg::RotatePhoto)
	ON_BN_CLICKED(IDC_SYMMETRY, &CPhotoSystemDlg::SymmetryPhoto)
	ON_BN_CLICKED(IDC_CUT, &CPhotoSystemDlg::PhotoCut)
	ON_BN_CLICKED(IDC_CLOSE, &CPhotoSystemDlg::ClosePhoto)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CPhotoSystemDlg::ButtonSave)
	
	//silder
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()

	//数值框
	ON_EN_CHANGE(IDC_ZOOM_VALUE, &CPhotoSystemDlg::ChangeZoomValue)
	ON_EN_CHANGE(IDC_BRIGHTNESS_VALUE, &CPhotoSystemDlg::ChangeBrightnessValue)
	ON_EN_CHANGE(IDC_CONTRAST_VALUE, &CPhotoSystemDlg::ChangeContrastValue)
	ON_EN_CHANGE(IDC_VIEW_VALUE, &CPhotoSystemDlg::ChangeViewValue)
	ON_EN_CHANGE(IDC_HIGHLIGHT_VALUE, &CPhotoSystemDlg::ChangeHighlightValue)
	ON_EN_CHANGE(IDC_SHADOW_VALUE, &CPhotoSystemDlg::ChangeShadowValue)
	ON_EN_CHANGE(IDC_RED_VALUE, &CPhotoSystemDlg::ChangeRedValue)
	ON_EN_CHANGE(IDC_GREEN_VALUE, &CPhotoSystemDlg::ChangeGreenValue)
	ON_EN_CHANGE(IDC_BLUE_VALUE, &CPhotoSystemDlg::ChangeBlueValue)

	//菜单功能
	ON_COMMAND(ID_OPEN, &CPhotoSystemDlg::OpenPhoto)
	ON_COMMAND(ID_OPEN_GRAY, &CPhotoSystemDlg::OpenPhotoGray)
	ON_COMMAND(ID_SAVE, &CPhotoSystemDlg::SavePhoto)
	ON_COMMAND(ID_GRAYTORGB, &CPhotoSystemDlg::GraytoRGB)
	ON_COMMAND(ID_RGBTOGRAY, &CPhotoSystemDlg::RGBtoGray)
	ON_COMMAND(ID_LINE_TRANS, &CPhotoSystemDlg::LineTransform)
	ON_COMMAND(ID_PART_TRANS, &CPhotoSystemDlg::PartTransform)
	ON_COMMAND(ID_LOG_TRANS, &CPhotoSystemDlg::LogTransform)
	ON_COMMAND(ID_SHOW_HISTOGRAM1, &CPhotoSystemDlg::ShowHistogram1)
	ON_COMMAND(ID_SHOW_HISTOGRAM2, &CPhotoSystemDlg::ShowHistogram2)
	ON_COMMAND(ID_HISTOGRAM_EQUALIZATION, &CPhotoSystemDlg::HistogramEqualization)
	ON_COMMAND(ID_HISTOGRAM_MATCH, &CPhotoSystemDlg::HistogramMatch)
	ON_COMMAND(ID_ADD_SALTPEPPER, &CPhotoSystemDlg::AddSaltpepper)
	ON_COMMAND(ID_ADD_GAUSSIAN, &CPhotoSystemDlg::AddGaussian)
	ON_COMMAND(ID_MEDIANBLUR, &CPhotoSystemDlg::MedianBlur)
	ON_COMMAND(ID_GAUSSIAN, &CPhotoSystemDlg::Gaussian)
	ON_COMMAND(ID_ILPF, &CPhotoSystemDlg::ILpf)
	ON_COMMAND(ID_PIC_UP, &CPhotoSystemDlg::Pic_up)
	ON_COMMAND(ID_PIC_DOWN, &CPhotoSystemDlg::Pic_down)
	ON_COMMAND(ID_PIC_LEFT, &CPhotoSystemDlg::Pic_left)
	ON_COMMAND(ID_PIC_RIGHT, &CPhotoSystemDlg::Pic_right)
	ON_COMMAND(ID_TOLINE, &CPhotoSystemDlg::ToLine)
	ON_COMMAND(ID_INVERTED, &CPhotoSystemDlg::Invert)
	ON_COMMAND(ID_RELIEF, &CPhotoSystemDlg::Relief)
	ON_COMMAND(ID_WATER, &CPhotoSystemDlg::Water)
END_MESSAGE_MAP()


// CPhotoSystemDlg 消息处理程序

BOOL CPhotoSystemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_Menu.LoadMenu(IDR_MENU); //IDR_MENU1是菜单资源ID
	SetMenu(&m_Menu); //将菜单加入到对话框。
	
	//slider初始化
	//缩放
	my_zoom = (CSliderCtrl*)GetDlgItem(IDC_ZOOM);//绑定
	my_zoom->SetRange(-99, 100, TRUE);//设置范围，防止缩放值变为0
	my_zoom->SetPos(0);//设置初始位置
	my_zoom->SetTicFreq(10);//刻度
	//亮度
	my_brightness = (CSliderCtrl*)GetDlgItem(IDC_BRIGHTNESS);
	my_brightness->SetRange(-100, 100, TRUE);
	my_brightness->SetPos(0);
	//对比度
	my_contrast = (CSliderCtrl*)GetDlgItem(IDC_CONTRAST);
	my_contrast->SetRange(-100, 100, TRUE);
	my_contrast->SetPos(0);
	//饱和度
	my_saturation = (CSliderCtrl*)GetDlgItem(IDC_SATURATION);
	my_saturation->SetRange(0, 100, TRUE);
	my_saturation->SetPos(0);
	//清晰度
	my_view = (CSliderCtrl*)GetDlgItem(IDC_VIEW);
	my_view->SetRange(-100, 100, TRUE);
	my_view->SetPos(0);
	//高光
	my_highlight = (CSliderCtrl*)GetDlgItem(IDC_HIGHLIGHT);
	my_highlight->SetRange(0, 100, TRUE);
	my_highlight->SetPos(0);
	//阴影
	my_shadow = (CSliderCtrl*)GetDlgItem(IDC_SHADOW);
	my_shadow->SetRange(0, 100, TRUE);
	my_shadow->SetPos(0);
	//红
	my_red = (CSliderCtrl*)GetDlgItem(IDC_RED);
	my_red->SetRange(-255, 255, TRUE);
	my_red->SetPos(0);
	//绿
	my_green = (CSliderCtrl*)GetDlgItem(IDC_GREEN);
	my_green->SetRange(-255, 255, TRUE);
	my_green->SetPos(0);
	//蓝
	my_blue = (CSliderCtrl*)GetDlgItem(IDC_BLUE);
	my_blue->SetRange(-255, 255, TRUE);
	my_blue->SetPos(0);
	

	//绑定窗口
	pWnd1 = GetDlgItem(IDC_STATIC_PIC);//CWnd是MFC窗口类的基类,提供了微软基础类库中所有窗口类的基本功能。
	pWnd1->GetClientRect(&rect);//GetClientRect为获得控件相自身的坐标大小
	Init(pWnd1, &rect);
	namedWindow("pic", WINDOW_AUTOSIZE);//设置窗口名
	HWND hWndl = (HWND)cvGetWindowHandle("pic");//hWnd 表示窗口句柄,获取窗口句柄
	HWND hParent1 = ::GetParent(hWndl);//GetParent函数一个指定子窗口的父窗口句柄
	::SetParent(hWndl, pWnd1->m_hWnd);
	::ShowWindow(hParent1, SW_HIDE);
	Mat back = imread("back.png");
	resize(back, back, Size(rect.Width(), rect.Height()));
	imshow("pic", back);
	ScreenToClient(&rect);//屏幕坐标转换为窗口坐标
    
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPhotoSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPhotoSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPhotoSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//按钮

//比较原图
void CPhotoSystemDlg::ComparePhoto()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	namedWindow("原图");
	imshow("原图", image);
}

//重置图片
void CPhotoSystemDlg::RePhoto()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	image.copyTo(img);

	NumInit();
	Init(pWnd1, &rect);
	imshow("pic", img);
}

//旋转
void CPhotoSystemDlg::RotatePhoto()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	Rotate(img, 90).copyTo(img);
	
	Init(pWnd1, &rect);
	imshow("pic", img);
}

//翻转
void CPhotoSystemDlg::SymmetryPhoto()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	flip(img, img, 1);
	
	Init(pWnd1, &rect);
	imshow("pic", img);
}

//图像裁剪
void CPhotoSystemDlg::PhotoCut()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}

	Rect pic = selectROI("选择区域", img, FALSE);
	destroyWindow("选择区域");
	if (!pic.empty())
		img(pic).copyTo(img);
	Init(pWnd1, &rect);
	imshow("pic", img);
}

//关闭图片
void CPhotoSystemDlg::ClosePhoto()
{
	Init(pWnd1, &rect);
	flag = FALSE;
}

//一系列数值改变确认（防止图片在变换过程中信息越来越少）
void CPhotoSystemDlg::ButtonSave()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	UpdateData(TRUE);
	if (zoom_value != 0)
	{
		Zoom(img, zoom_value).copyTo(img);
		zoom_value = 0;
		my_zoom->SetPos(0);
	}
	if (brightness_value != 0)
	{
		Bright_Contrast(img, brightness_value, contrast_value).copyTo(img);
		brightness_value = 0;
		my_brightness->SetPos(0);
		contrast_value = 0;//防止对比度在下一个if中再叠加一次
		my_contrast->SetPos(0);
	}
	if (contrast_value != 0)
	{
		Bright_Contrast(img, brightness_value, contrast_value).copyTo(img);
		brightness_value = 0;
		my_brightness->SetPos(0);
		contrast_value = 0;
		my_contrast->SetPos(0);
	}
	if (saturation_value != 0)
	{
		Saturation(img, saturation_value).copyTo(img);
		saturation_value = 0;
		my_saturation->SetPos(0);
	}
	if (view_value != 0)
	{
		View(img, view_value).copyTo(img);
		view_value = 0;
		my_view->SetPos(0);
	}
	if (highlight_value != 0)
	{
		HighLight_shadow(img, highlight_value, 0).copyTo(img);
		highlight_value = 0;
		my_highlight->SetPos(0);
	}
	if (shadow_value != 0)
	{
		HighLight_shadow(img, shadow_value, 1).copyTo(img);
		shadow_value = 0;
		my_shadow->SetPos(0);
	}
	if (red_value != 0)
	{
		Color(img, red_value, 2).copyTo(img);
		red_value = 0;
		my_red->SetPos(0);
	}
	if (green_value != 0)
	{
		Color(img, green_value, 1).copyTo(img);
		green_value = 0;
		my_green->SetPos(0);
	}
	if (blue_value != 0)
	{
		Color(img, blue_value, 0).copyTo(img);
		blue_value = 0;
		my_blue->SetPos(0);
	}
	Invalidate();
	Init(pWnd1, &rect);
	imshow("pic", img);
}


//silder

//初始化
void CPhotoSystemDlg::NumInit()
{
	zoom_value = 0;
	my_zoom->SetPos(0);
	brightness_value = 0;
	my_brightness->SetPos(0);
	contrast_value = 0;
	my_contrast->SetPos(0);
	saturation_value = 0;
	my_saturation->SetPos(0);
	view_value = 0;
	my_view->SetPos(0);
	highlight_value = 0;
	my_highlight->SetPos(0);
	shadow_value = 0;
	my_shadow->SetPos(0);
	red_value = 0;
	my_red->SetPos(0);
	green_value = 0;
	my_green->SetPos(0);
	blue_value = 0;
	my_blue->SetPos(0);
}

//竖直
void CPhotoSystemDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
	
	//缩放
	if (pScrollBar == (CWnd*)(my_zoom))
	{
		zoom_value = my_zoom->GetPos();
		if (flag)
		{
			Zoom(img, zoom_value);
			Init(pWnd1, &rect);
		}
	}

	UpdateData(FALSE);
}

//水平
void CPhotoSystemDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	if (pScrollBar == (CWnd*)(my_brightness))
	{
		brightness_value = my_brightness->GetPos();
		if (flag)
		{
			Bright_Contrast(img, brightness_value, contrast_value);
			Init(pWnd1, &rect);
		}
	}
	else if (pScrollBar == (CWnd*)(my_contrast))
	{
		contrast_value = my_contrast->GetPos();
		if (flag)
		{
			Bright_Contrast(img, brightness_value, contrast_value);
			Init(pWnd1, &rect);
		}
	}
	else if (pScrollBar == (CWnd*)(my_saturation))
	{
		saturation_value = my_saturation->GetPos();
		if (flag && saturation_value != 0)
		{
			Saturation(img, saturation_value);
		}
	}
	else if (pScrollBar == (CWnd*)(my_view))
	{
		view_value = my_view->GetPos();
		if (flag && my_view != 0)
		{
			View(img, view_value);
		}
	}
	else if (pScrollBar == (CWnd*)(my_highlight))
	{
		highlight_value = my_highlight->GetPos();
		if (flag && highlight_value != 0)
		{
			HighLight_shadow(img, highlight_value, 0);
		}
	}
	else if (pScrollBar == (CWnd*)(my_shadow))
	{
		shadow_value = my_shadow->GetPos();
		if (flag && shadow_value != 0)
		{
			HighLight_shadow(img, shadow_value, 1);
		}
	}
	else if (pScrollBar == (CWnd*)(my_red))
	{
		red_value = my_red->GetPos();
		if (flag && red_value != 0)
		{
			Color(img, red_value, 2);
		}
	}
	else if (pScrollBar == (CWnd*)(my_green))
	{
		green_value = my_green->GetPos();
		if (flag && green_value != 0)
		{
			Color(img, green_value, 1);
		}
	}
	else if (pScrollBar == (CWnd*)(my_blue))
	{
		blue_value = my_blue->GetPos();
		if (flag && blue_value != 0)
		{
			Color(img, blue_value, 0);
		}
	}

	UpdateData(FALSE);
}


//数值框

//缩放
void CPhotoSystemDlg::ChangeZoomValue()
{
	UpdateData(TRUE);
	my_zoom->SetPos(zoom_value);
	Invalidate();
	if (flag)
	{
		Init(pWnd1, &rect);
		Zoom(img, zoom_value);
	}
}

//亮度
void CPhotoSystemDlg::ChangeBrightnessValue()
{
	UpdateData(TRUE);
	my_brightness->SetPos(brightness_value);
	Invalidate();
	if (flag)
	{
		Init(pWnd1, &rect);
		Bright_Contrast(img, brightness_value, contrast_value);
	}
}

//对比度
void CPhotoSystemDlg::ChangeContrastValue()
{
	UpdateData(TRUE);
	my_contrast->SetPos(contrast_value);
	Invalidate();
	if (flag)
	{
		Init(pWnd1, &rect);
		Bright_Contrast(img, brightness_value, contrast_value);
	}
}

//饱和度
void CPhotoSystemDlg::ChangeViewValue()
{
	UpdateData(TRUE);
	my_view->SetPos(view_value);
	Invalidate();
	if (flag)
	{
		Init(pWnd1, &rect);
		View(img, view_value);
	}
}

//清晰度
void CPhotoSystemDlg::ChangeHighlightValue()
{
	UpdateData(TRUE);
	my_highlight->SetPos(highlight_value);
	Invalidate();
	if (flag)
	{
		Init(pWnd1, &rect);
		HighLight_shadow(img, highlight_value, 0);
	}
}

//阴影
void CPhotoSystemDlg::ChangeShadowValue()
{
	UpdateData(TRUE);
	my_shadow->SetPos(shadow_value);
	Invalidate();
	if (flag)
	{
		Init(pWnd1, &rect);
		HighLight_shadow(img, shadow_value, 1);
	}
}

//红
void CPhotoSystemDlg::ChangeRedValue()
{
	UpdateData(TRUE);
	my_red->SetPos(red_value);
	Invalidate();
	if (flag)
	{
		Init(pWnd1, &rect);
		Color(img, red_value, 2);
	}
}

//绿
void CPhotoSystemDlg::ChangeGreenValue()
{
	UpdateData(TRUE);
	my_green->SetPos(green_value);
	Invalidate();
	if (flag)
	{
		Init(pWnd1, &rect);
		Color(img, green_value, 1);
	}
}

//蓝
void CPhotoSystemDlg::ChangeBlueValue()
{
	UpdateData(TRUE);
	my_blue->SetPos(blue_value);
	Invalidate();
	if (flag)
	{
		Init(pWnd1, &rect);
		Color(img, blue_value, 0);
	}
}

//菜单

//打开图片
void CPhotoSystemDlg::OpenPhoto()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "bmp文件(*.bmp)|*.bmp|JPEG文件(*.jpg)|*.jpg|所有文件(*.*)|*.*|", NULL);

	if (dlg.DoModal() == IDOK)
	{
		CString filepath = dlg.GetPathName();
		img = imread(filepath.GetBuffer());
		flag = TRUE;
		img.copyTo(image);
		
		while (img.rows > rect.Width() || img.cols > rect.Height())
		{
			resize(img, img, Size(),0.95,0.95);//调整图片大小
		}

		NumInit();
		Init(pWnd1,&rect);
		imshow("pic", img);
	}
}

//打开为灰度图
void CPhotoSystemDlg::OpenPhotoGray()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "bmp文件(*.bmp)|*.bmp|JPEG文件(*.jpg)|*.jpg|所有文件(*.*)|*.*|", NULL);

	if (dlg.DoModal() == IDOK)
	{
		CString filepath = dlg.GetPathName();
		img = imread(filepath.GetBuffer(), 0);
		flag = TRUE;
		img.copyTo(image);

		while (img.rows > rect.Width() || img.cols > rect.Height())
		{
			resize(img, img, Size(), 0.95, 0.95);//调整图片大小
		}

		NumInit();
		Init(pWnd1, &rect);
		imshow("pic", img);
	}
}

//保存图片
void CPhotoSystemDlg::SavePhoto()
{
	if (!flag)
	{
		AfxMessageBox("无可保存图片！");
		return;
	}
	SaveImage(img);
}

//灰度图变RGB模式
void CPhotoSystemDlg::GraytoRGB()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	ToRGB(img).copyTo(img);
	
	Init(pWnd1, &rect);
	imshow("pic", img);
}

//RGB模式变灰度图
void CPhotoSystemDlg::RGBtoGray()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	ToGray(img).copyTo(img);
	
	Init(pWnd1, &rect);
	imshow("pic", img);
}

//灰度线性变换
void CPhotoSystemDlg::LineTransform()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	LineTrans(img, 50, 200).copyTo(img);
	
	Init(pWnd1, &rect);
	imshow("pic", img);
}

//灰度分段变换
void CPhotoSystemDlg::PartTransform()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	PartTrans(img, 100, 150, 50, 200).copyTo(img);

	Init(pWnd1, &rect);
	imshow("pic", img);
}

//灰度对数变换
void CPhotoSystemDlg::LogTransform()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	LogTrans(img, 50, 0.8, 1.05).copyTo(img);

	Init(pWnd1, &rect);
	imshow("pic", img);
}

//显示当前灰度直方图
void CPhotoSystemDlg::ShowHistogram1()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	Show_Histogram(img, "当前图像灰度直方图");
}

//显示当前原图直方图
void CPhotoSystemDlg::ShowHistogram2()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	Show_Histogram(image, "原图像灰度直方图");
}

//直方图均衡化
void CPhotoSystemDlg::HistogramEqualization()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}

	if (img.channels() == 3)
	{
		cvtColor(img, img, COLOR_RGB2GRAY);
	}
	equalizeHist(img, img);
	Init(pWnd1, &rect);
	imshow("pic", img);
	Show_Histogram(img, "当前图像灰度直方图");
}

//直方图规格化
void CPhotoSystemDlg::HistogramMatch()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "bmp文件(*.bmp)|*.bmp|JPEG文件(*.jpg)|*.jpg|所有文件(*.*)|*.*|", NULL);

	if (dlg.DoModal() == IDOK)
	{
		CString filepath = dlg.GetPathName();
		Mat img2 = imread(filepath.GetBuffer());
		Histogram_Match(img, img2).copyTo(img);
		Init(pWnd1, &rect);
		imshow("pic", img);
		Show_Histogram(img, "当前图像灰度直方图");
		Show_Histogram(img2, "选择图像灰度直方图");
	}
}

//添加椒盐噪声
void CPhotoSystemDlg::AddSaltpepper()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	
	Add_Saltpepper(img, img.rows * img.cols / 20).copyTo(img);
	Init(pWnd1, &rect);
	imshow("pic", img);
}

//添加高斯噪声
void CPhotoSystemDlg::AddGaussian()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}

	Add_Gaussian(img, 10, 20).copyTo(img);
	Init(pWnd1, &rect);
	imshow("pic", img);
}

//中值滤波(常用于去除椒盐噪声)
void CPhotoSystemDlg::MedianBlur()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}

	Mat img2;
	img.copyTo(img2);
	//输入图像，输出图像，卷积核大小，
	medianBlur(img2, img, 5);
	Init(pWnd1, &rect);
	imshow("pic", img);
}

//高斯滤波/模糊
void CPhotoSystemDlg::Gaussian()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}

	Mat img2;
	img.copyTo(img2);
	//输入图像，输出图像，卷积核大小，x、y方向的标准差,像素外插法(有默认值)
	//如果sigmaY为0，则函数会自动根据kernel大小来计算sigmaY
	//如果sigmaX和sigmaY都为0，那么这两个参数都会被设置为cv::DBL_MAX
	//如果sigmaY不为0而sigmaX为0，那么sigmaX会被设置为等于sigmaY
	GaussianBlur(img2, img, Size(5, 5), 1, 1);
	Init(pWnd1, &rect);
	imshow("pic", img);
}

//低通滤波
void CPhotoSystemDlg::ILpf()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	ILPF(img).copyTo(img);
	
	Init(pWnd1, &rect);
	imshow("pic", img);
}

//图像拼接
void CPhotoSystemDlg::Pic_up()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "bmp文件(*.bmp)|*.bmp|JPEG文件(*.jpg)|*.jpg|所有文件(*.*)|*.*|", NULL);

	if (dlg.DoModal() == IDOK)
	{
		CString filepath = dlg.GetPathName();
		Mat img2 = imread(filepath.GetBuffer());

		Add_Photo(img2, img, 1).copyTo(img);
		while (img.rows > rect.Width() || img.cols > rect.Height())
		{
			resize(img, img, Size(), 0.95, 0.95);//调整图片大小
		}
		Init(pWnd1, &rect);
		imshow("pic", img);
	}
	
}
void CPhotoSystemDlg::Pic_down()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "bmp文件(*.bmp)|*.bmp|JPEG文件(*.jpg)|*.jpg|所有文件(*.*)|*.*|", NULL);

	if (dlg.DoModal() == IDOK)
	{
		CString filepath = dlg.GetPathName();
		Mat img2 = imread(filepath.GetBuffer());

		Add_Photo(img, img2, 1).copyTo(img);
		while (img.rows > rect.Width() || img.cols > rect.Height())
		{
			resize(img, img, Size(), 0.95, 0.95);//调整图片大小
		}
		Init(pWnd1, &rect);
		imshow("pic", img);
	}
}
void CPhotoSystemDlg::Pic_left()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "bmp文件(*.bmp)|*.bmp|JPEG文件(*.jpg)|*.jpg|所有文件(*.*)|*.*|", NULL);

	if (dlg.DoModal() == IDOK)
	{
		CString filepath = dlg.GetPathName();
		Mat img2 = imread(filepath.GetBuffer());

		Add_Photo(img2, img, 0).copyTo(img);
		while (img.rows > rect.Width() || img.cols > rect.Height())
		{
			resize(img, img, Size(), 0.95, 0.95);//调整图片大小
		}
		Init(pWnd1, &rect);
		imshow("pic", img);
	}
}
void CPhotoSystemDlg::Pic_right()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "bmp文件(*.bmp)|*.bmp|JPEG文件(*.jpg)|*.jpg|所有文件(*.*)|*.*|", NULL);

	if (dlg.DoModal() == IDOK)
	{
		CString filepath = dlg.GetPathName();
		Mat img2 = imread(filepath.GetBuffer());

		Add_Photo(img, img2, 0).copyTo(img);
		while (img.rows > rect.Width() || img.cols > rect.Height())
		{
			resize(img, img, Size(), 0.95, 0.95);//调整图片大小
		}
		Init(pWnd1, &rect);
		imshow("pic", img);
	}
}

//线条化
void CPhotoSystemDlg::ToLine()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	To_Line(img).copyTo(img);
	imshow("pic", img);
}

// 用于设置颗粒强度的对话框

class CRankDlg : public CDialog
{
public:
	CRankDlg();
	int rank;

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RANK_DIALOG};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()	
public:
	afx_msg void OnBnClickedOk();
};

CRankDlg::CRankDlg() : CDialog(IDD_RANK_DIALOG), rank(1)
{
	
}

void CRankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RANK, rank);
}

BEGIN_MESSAGE_MAP(CRankDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CRankDlg::OnBnClickedOk)
END_MESSAGE_MAP()

//颗粒效果
void CPhotoSystemDlg::RankDlg()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	CRankDlg rankDlg;
	rankDlg.DoModal();
	Add_Grain(img, rankDlg.rank).copyTo(img);
	imshow("pic", img);
}

void CRankDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialog::OnOK();
}

//反色
void CPhotoSystemDlg::Invert()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	Inverted_Color(img).copyTo(img);
	imshow("pic", img);
}

//浮雕
void CPhotoSystemDlg::Relief()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	Photo_Relief(img).copyTo(img);
	imshow("pic", img);
}

//水中倒影
void CPhotoSystemDlg::Water()
{
	if (!flag)
	{
		AfxMessageBox("图片未打开！");
		return;
	}
	InWater(img).copyTo(img);
	while (img.rows > rect.Width() || img.cols > rect.Height())
	{
		resize(img, img, Size(), 0.95, 0.95);//调整图片大小
	}
	Init(pWnd1, &rect);
	imshow("pic", img);
}
