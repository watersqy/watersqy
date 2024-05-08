
// PhotoSystemDlg.h: 头文件
//

#pragma once

#include "Functions.h"
#include "SliderSet.h"

// CPhotoSystemDlg 对话框
class CPhotoSystemDlg : public CDialog
{
// 构造
public:
	CPhotoSystemDlg(CWnd* pParent = nullptr);	// 标准构造函数
	CMenu m_Menu;//菜单
	CWnd* pWnd1;//主窗口句柄
	CRect rect;//坐标
	Mat img;//图片
	Mat image;//原图片备份
	BOOL flag;//是否打开图片
	
	CSliderCtrl* my_zoom;//缩放
	int zoom_value;
	CSliderCtrl* my_brightness;//亮度
	int brightness_value;
	CSliderCtrl* my_contrast;//对比度
	float contrast_value;
	CSliderCtrl* my_saturation;//饱和度
	float saturation_value;
	CSliderCtrl* my_view;//清晰度
	int view_value;
	CSliderCtrl* my_highlight;//高光
	int highlight_value;
	CSliderCtrl* my_shadow;//阴影
	int shadow_value;
	CSliderCtrl* my_red;//红色调
	int red_value;
	CSliderCtrl* my_green;//绿色调
	int green_value;
	CSliderCtrl* my_blue;//蓝色调
	int blue_value;

	int rank;

	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHOTOSYSTEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	void NumInit();

	afx_msg void AppAbout();
	afx_msg void RankDlg();

	afx_msg void ComparePhoto();
	afx_msg void RePhoto();
	afx_msg void RotatePhoto();
	afx_msg void SymmetryPhoto();
	afx_msg void PhotoCut();
	afx_msg void ClosePhoto();
	afx_msg void ButtonSave();
	
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	
	afx_msg void ChangeZoomValue();
	afx_msg void ChangeBrightnessValue();
	afx_msg void ChangeContrastValue();
	afx_msg void ChangeViewValue();
	afx_msg void ChangeHighlightValue();
	afx_msg void ChangeShadowValue();
	afx_msg void ChangeRedValue();
	afx_msg void ChangeGreenValue();
	afx_msg void ChangeBlueValue();

	afx_msg void OpenPhoto();
	afx_msg void OpenPhotoGray();
	afx_msg void SavePhoto();

	afx_msg void GraytoRGB();
	afx_msg void RGBtoGray();
	afx_msg void LineTransform();
	afx_msg void PartTransform();
	afx_msg void LogTransform();

	afx_msg void ShowHistogram1();
	afx_msg void ShowHistogram2();
	afx_msg void HistogramEqualization();
	afx_msg void HistogramMatch();

	afx_msg void AddSaltpepper();
	afx_msg void AddGaussian();
	afx_msg void MedianBlur();
	afx_msg void Gaussian();
	afx_msg void ILpf();
	
	afx_msg void Pic_up();
	afx_msg void Pic_down();
	afx_msg void Pic_left();
	afx_msg void Pic_right();
	afx_msg void ToLine();
	afx_msg void Invert();
	afx_msg void Relief();
	afx_msg void Water();
};
