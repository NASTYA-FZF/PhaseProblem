#pragma once
#define _SILENCE_AMP_DEPRECATION_WARNINGS
#include <afxwin.h>
#include <vector>
#include <amp_graphics.h>
//#include "Analys.h"

using namespace std;

class Drawer
{
	// ������������� ������� ���������.
	CRect frame;
	// ��������� �� ������ ����, ������� ���������.
	CWnd * wnd;
	// �������� ���������, ����������� � ������� ���������.
	CDC * dc;
	CDC* dc_forOnPaint;
	// �������� ���������, ����������� � ������.
	CDC memDC;
//	CDC memDC_forOnPaint;
	// ������ ��� ��������� ��������� memDC.
	CBitmap bmp;
//	CBitmap bmp_forOnPaint;
	// ���� ��� ������������ ��������� ������������� ������.
	bool init;
public:
	// ������������������� ������ ������ �� ������ HWND.
	void Create(HWND hWnd);

	vector<double> convert_range(vector <double>& data, double outmax, double outmin, double inmax, double inmin);

	double convert_range_d(double data, double outmax, double outmin, double inmax, double inmin);

	// ���������� ������.
	void DrawPoints(vector<double>& data, CString Ox, CString Oy, double data_x_max, double step_x/*, CDC* mem*/);

	double MaxF(vector<double> y);

	double MinF(vector<double> y);

	void DrawTwoSig(vector<double>& data, vector<double>& data1, CString Ox, CString Oy, double data_x_max, double step_x);

	void ReDraw();
	//void DrawSr(vector<double>& data, signal s, CString Ox, CString Oy, double data_x_min, double data_x_max, double step_x);
};

