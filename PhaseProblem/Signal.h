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
	//конструктор
	signal(double* A, double* stok, double* mat, double FD, int otN);
	//БПФ
	void fft(vector<base>& a, bool invert);
	//энергия сигнала
	double Es(vector<double> func);
	//получение сигнала
	vector<double> GetSig();
	//установить амплитудный спектр
	void Set_ampl_spectr(vector<double> a);
	//алгоритм Фиенупа
	void Fienup(vector<double>& s, double TAU, Drawer& d, MSG& msg);
	//циклический сдвиг
	void Sdvig(vector<double>& newS);
	//сравнение сигналов
	double Srav(vector<double> newS);
};