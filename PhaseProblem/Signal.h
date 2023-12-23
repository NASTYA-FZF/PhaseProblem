#pragma once
#include <vector>
#include <complex>
#include "Drawer.h"
using namespace std;

typedef complex<double> base;

class signal
{
	double fd;
	int N;
	vector<double> sig, ampl_spec, fi, lateSig, curSig;
	vector<base> curS;

public:
	//�����������
	signal(double* A, double* stok, double* mat, double FD, int otN);
	//���
	void fft(vector<base>& a, bool invert);
	//������� �������
	double Es(vector<double> func);
	//��������� �������
	vector<double> GetSig();
	//���������� ����������� ������
	void Set_ampl_spectr(vector<double> a);
	//�������� �������
	void Fienup(vector<double>& s, double TAU, Drawer& d, MSG& msg);
	//����������� �����
	void Sdvig(vector<double>& newS);
	//��������� ��������
	double Srav(vector<double> newS);
};