#include <pch.h>
#include <cmath>
#include <chrono>
#include <omp.h>
#include <iomanip>
#include <iostream>
const int n = 10000000;
double s, s2, h;
using namespace std;
double f(double a)
{
	return 0;
}
double g(double a)
{
	return 4.0/(1+a*a);
}
int main()
{
	system("chcp 1251>nul");
	double a, b, S; double t1 = omp_get_wtime();

	cin >> a; cin >> b;
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
	cout << "S=" << (s + s2)*h << "\n";

	double t2 = omp_get_wtime();
	cout << "Время выполнения " << setprecision(3) << t2 - t1 << "sec";
	system("pause>nul");
	return 0;
}

