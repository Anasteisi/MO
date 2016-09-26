#include <iostream>
#include <cmath>

using namespace std;

double f(double x)
{
	double y = 0;
	y = x*x + 3 * x*(log(x) - 1);
	return y;
}

double fdx(double x)
{
	double ydx = 0;
	ydx = 2 * x + 3 * log(x);
	return ydx;
}

double fdxdx(double x)
{
	double ydxdx = 0;
	ydxdx = 2 + (3 / x);
	return ydxdx;
}

int Fibonacci(int n) //Fn
{
	int F = 0;
	if (n == 1 || n == 2)
	{
		F = 1;
		return F;
	}
	F = Fibonacci(n - 1) + Fibonacci(n - 2);
	return F;
}

int main() //17,57 f(x)=x^2+3x(ln(x)-1); [0,5; 1], eps=0,05, del = 0,01
{
	cout << "f(x) = x^2 + 3*x*(ln(x)-1)" << endl;
	cout << "a = 0.5, b = 1, eps = 0.05, del = 0.01" << endl << endl;

	double a = 0, b = 0, eps = 0, del = 0;
	int k = 0;//kolichestvo vychislenii
	a = 0.5; b = 1; eps = 0.05; del = 0.01;

	double xmin1 = 0, xmin2 = 0, xmin3 = 0, xmin4 = 0, xmin5 = 0, xmin6 = 0;

	//1 -- method passivnogo poiska
	double a1 = 0;

	a1 = a;
	xmin1 = a1;

	while (a1 <= b)
	{
		if (f(a1) < f(xmin1))
			xmin1 = a1;
		a1 += del;
		k++;
	}

	cout << "Method passivnogo poiska: " << "x=" << xmin1 << ", f(x)=" << f(xmin1) << endl;
	cout << "Kolichestvo vychisleniy: " << k << endl << endl;

	//2 -- method dihotomii
	k = 0;
	a1 = 0;
	double b1 = 0, c1 = 0, d1 = 0;
	a1 = a; b1 = b;//kraya otrezka

	while ((b1 - a1) / 2 > eps)//kriterij ostanovki
	{
		c1 = (a1 + b1 - del) / 2;
		d1 = (a1 + b1 + del) / 2;

		if (f(c1) <= f(d1))
			b1 = d1;
		else
			a1 = c1;
		k += 2;//f(c1) f(d1)
	}

	xmin2 = (a1 + b1) / 2;//seredina [a1; b1]

	cout << "Method dihotomii: " << "x=" << xmin2 << ", f(x)=" << f(xmin2) << endl;
	cout << "Kolichestvo vychisleniy: " << k << endl << endl;

	//3 -- method zolotogo secheniya
	a1 = 0, b1 = 0, c1 = 0, d1 = 0; k = 0;
	a1 = a; b1 = b;//kraya otrezka
	c1 = a1 + (3 - sqrt(5))*(b1 - a1) / 2;
	d1 = a1 + (sqrt(5) - 1)*(b1 - a1) / 2;
	k++;//f(c1)

	while ((b1 - a1) / 2 > eps)//kriterii ostanovki
	{
		if (f(c1) <= f(d1))
		{
			b1 = d1;
			d1 = c1;
			c1 = a1 + (3 - sqrt(5))*(b1 - a1) / 2;
		}
		else
		{
			a1 = c1;
			c1 = d1;
			d1 = a1 + (sqrt(5) - 1)*(b1 - a1) / 2;
		}
		k++;//f(c1) ili f(d1)
	}

	xmin3 = (a1 + b1) / 2;//seredina [a1; b1]

	cout << "Method zolotogo secheniya: " << "x=" << xmin3 << ", f(x)=" << f(xmin3) << endl;
	cout << "Kolichestvo vychisleniy: " << k << endl << endl;

	//4 -- method Fibonacci
	k = 0;
	a1 = 0, b1 = 0, c1 = 0, d1 = 0;
	double del1 = 0;
	a1 = a; b1 = b;//kraya otrezka

	double Fnpl1 = (11 / 10)*(b - a) / (2 * eps);
	int n = 0, npl1 = 1, m = 0;
	while (m < Fnpl1)//poisk n
	{
		m = Fibonacci(npl1);
		npl1++;
	}
	n = npl1 - 1;

	del1 = (b - a) / (10 * Fibonacci(n + 1));

	c1 = a1 + (b1 - a1)*(Fibonacci(n - 1)) / Fibonacci(n + 1);
	d1 = a1 + (b1 - a1)*(Fibonacci(n)) / Fibonacci(n + 1);
	k++; //f(c1)

	for (int i = 2; i < n; i++)
	{
		if (c1 == d1)
			c1 -= del1;

		if (f(c1) <= f(d1))
		{
			b1 = d1;
			d1 = c1;
			c1 = a1 + (b1 - a1)*(Fibonacci(n - i)) / Fibonacci(n - i + 2);
		}
		else
		{
			a1 = c1;
			c1 = d1;
			d1 = a1 + (b1 - a1)*(Fibonacci(n - i + 1)) / Fibonacci(n - i + 2);
		}

		k++;//f(c1) or f(d1)
	}

	xmin4 = (a1 + b1) / 2;

	cout << "Method Fibonacci: " << "x=" << xmin4 << ", f(x)=" << f(xmin4) << endl;
	cout << "Kolichestvo vychisleniy: " << k << endl << endl;

	//5 -- method kasatel'nyh
	k = 0;
	a1 = 0, b1 = 0, c1 = 0, d1 = 0;
	a1 = a; b1 = b;//kraya otrezka

	c1 = (a1 * fdx(a1) - b1 * fdx(b1) - f(a1) + f(b1)) / (fdx(a1) - fdx(b1));
	k++;//fdx(c1)

	while (abs(fdx(c1)) > eps)
	{
		if (fdx(c1) > 0)
			b1 = c1;
		if (fdx(c1) < 0)
			a1 = c1;
		if (fdx(c1) == 0)
			break;
		c1 = (a1 * fdx(a1) - b1 * fdx(b1) - f(a1) + f(b1)) / (fdx(a1) - fdx(b1));
		k++;
	}

	xmin5 = (a1 + b1) / 2;

	cout << "Method kasatel'nyh: " << "x=" << xmin5 << ", f(x)=" << f(xmin5) << endl;
	cout << "Kolichestvo vychisleniy: " << k << endl << endl;

	//6 -- method Njutona-Rafsona
	k = 0;
	a1 = 0, b1 = 0, c1 = 0, d1 = 0;
	a1 = a; b1 = b;//kraya otrezka
	c1 = a1;
	k++;//fdx(c1)

	while (abs(fdx(c1)) > eps)
	{
		c1 = c1 - fdx(c1) / fdxdx(c1);
		k += 2;//fdx fdxdx
	}

	xmin6 = c1;

	cout << "Method Njutona-Rafsona: " << "x=" << xmin6 << ", f(x)=" << f(xmin6) << endl;
	cout << "Kolichestvo vychisleniy: " << k << endl << endl;

	system("pause");
	return 0;
}