#include <pch.h>
#include <iostream>
#include <cmath>
const int n = 10000000;
double s, s2, h;
using namespace std;
double f(double a)
{
	return 0;
}
double g(double a)
{
	return 4 / (1 + a * a);
}
int main()
{
	double a, b;
	cout << "a=", cin >> a;
	cout << "b=", cin >> b;
	
#pragma omp parallel default (none) private (s) shared (n,h) reduction(+:s)
	{
#pragma omp parallel for private () reduction(+: s)
		s = 0.0;
		double x, f1, g1;
		h = (b - a) / n;
		for (int i = 1; i <= n - 1; i += 2)
		{
			x = a + ((i - 1) * h);
			f1 = f(x); g1 = g(x);
			if ((f1 > 0) && (g1 > 0)) { s += abs(f1 - g1); }
			else if (f1 > 0) s += f1 - g1;
			else s += g1 - f1;
		}}
#pragma omp parallel default (none) private (s2) shared (n,h) reduction(+:s2)
	{
#pragma omp parallel for private () reduction(+: s2)
		s2 = 0.0;
		double x, f1, g1;
		h = (b - a) / n;
		for (int i = 2; i <= n - 1; i += 2)
		{
			x = a + ((i - 1) * h);
			f1 = f(x); g1 = g(x);
			if ((f1 > 0) && (g1 > 0)) { s2 += abs(f1 - g1); }
			else if (f1 > 0) s2 += f1 - g1;
			else s2 += g1 - f1;
		}}
	double S = h * (s + s2);
	cout << "S=" << S;
	system("pause>nul");
	return 0;
}

