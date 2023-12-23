#include "pch.h"
#define _USE_MATH_DEFINES
#include "Signal.h"
#include <math.h>

signal::signal(double* A, double* stok, double* mat, double FD, int otN)
{
	N = otN;
	fd = FD;
	int num_kupol = 5;
	for (int i = 0; i < N; i++)
	{
		sig.push_back(0.);
		for (int j = 0; j < num_kupol; j++)
		{
			sig[i] += A[j] * exp(-(i / fd - mat[j]) * (i / fd - mat[j]) / (stok[j] * stok[j]));
		}
	}
}

void signal::fft(vector<base>& a, bool invert)
{
	int n = (int)a.size();
	if (n == 1)  return;

	vector<base> a0(n / 2), a1(n / 2);
	for (int i = 0, j = 0; i < n; i += 2, ++j) {
		a0[j] = a[i];
		a1[j] = a[i + 1];
	}
	fft(a0, invert);
	fft(a1, invert);

	double ang = 2 * M_PI / n * (invert ? -1 : 1);
	base w(1), wn(cos(ang), sin(ang));
	for (int i = 0; i < n / 2; ++i) {
		a[i] = a0[i] + w * a1[i];
		a[i + n / 2] = a0[i] - w * a1[i];
		if (invert)
			a[i] /= 2, a[i + n / 2] /= 2;
		w *= wn;
	}
}

double signal::Es(vector<double> func)
{
	double Esig(0);
	for (int i = 0; i < func.size(); i++)
	{
		Esig += func[i] * func[i];
	}
	return Esig;
}

vector<double> signal::GetSig()
{
	return sig;
}

void signal::Set_ampl_spectr(vector<double> a)
{
	ampl_spec = a;
}

void signal::Fienup(vector<double>& s, double TAU, Drawer& d, MSG& msg)
{
	curS.clear();
	curSig.clear();
	lateSig.clear();
	fi.clear();
	double re, im, mera;
	int counter(0);
	base num;
	for (int i = 0; i < N; i++)
	{
		fi.push_back((double)rand() / RAND_MAX * 2 * M_PI);
		re = ampl_spec[i] * cos(fi[i]);
		im = ampl_spec[i] * sin(fi[i]);
		num = base(re, im);
		curS.push_back(num);
	}

	while (1)
	{
		counter++;

		fft(curS, false);
		for (int i = 0; i < N; i++)
		{
			if (curS[i].real() >= 0) curSig.push_back(curS[i].real());
			else
			{
				curSig.push_back(0.);
			}
			re = curSig[i];
			//im = curS[i].imag();
			im = 0.;
			num = base(re, im);
			curS[i] = num;
		}

		if (counter % 100) d.DrawTwoSig(sig, curSig, L"t", L"A", N / fd, 1 / fd);

		if (!lateSig.empty())
		{
			mera = 0.;
			for (int i = 0; i < N; i++)
			{
				mera += (curSig[i] - lateSig[i]) * (curSig[i] - lateSig[i]);
			}
			if (mera < TAU * TAU)
			{
				s = curSig;
				return;
			}

			//for (int i = 0; i < N; i++)
			//{
			//	if (abs(curSig[i] - lateSig[i]) < TAU) mera++;
			//}
			//if (mera == N)
			//{
			//	s = curSig;
			//	return;
			//}
		}

		fft(curS, true);
		for (int i = 0; i < N; i++)
		{
			fi[i] = arg(curS[i]);
			re = ampl_spec[i] * cos(fi[i]);
			im = ampl_spec[i] * sin(fi[i]);
			num = base(re, im);
			curS[i] = num;
		}

		lateSig = curSig;
		curSig.clear();
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.lParam == (LPARAM("PAUSE")))
			{
				s = lateSig;
				return;
			}
		}
	}
}

void signal::Sdvig(vector<double>& newS)
{
	double work;
	work = newS[0];
	newS.erase(newS.begin());
	newS.push_back(work);
}

double signal::Srav(vector<double> newS)
{
	double work(0.);
	for (int i = 0; i < N; i++) work += (sig[i] - newS[i]) * (sig[i] - newS[i]);
	return work;
}
