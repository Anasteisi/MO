#include <iostream>
#include <cmath>

using namespace std;

double f(double x)
{
	double y = 0;
	y = x*x + 3 * x*(log(x) - 1);
	return y;
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

	double xmin1 = 0, xmin2 = 0, xmin3 = 0, xmin4 = 0;

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
	a1 = 0; k = 0;
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

	xmin2 = (b1 + a1) / 2;//seredina [a1; b1]
	k++;//(f(xmin))

	cout << "Method dihotomii: " << "x=" << xmin2 << ", f(x)=" << f(xmin2) << endl;
	cout << "Kolichestvo vychisleniy: " << k << endl << endl;

	//3-- method zolotogo secheniya
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

	xmin3 = (b1 + a1) / 2;//seredina [a1; b1]
	k++;//(f(xmin))

	cout << "Method zolotogo secheniya: " << "x=" << xmin3 << ", f(x)=" << f(xmin3) << endl;
	cout << "Kolichestvo vychisleniy: " << k << endl << endl;
	k = 0;


	//4-- method Fibonacci

	a1 = 0, b1 = 0, c1 = 0, d1 = 0;
	a1 = a; b1 = b;//kraya otrezka

	int Fnpl2 = (b - a) / eps + 1;//F(n+2) >= (b-a)/eps
	int n = 0, npl2 = 1, m = 0;
	while (m < Fnpl2)//poisk n
	{
		m = Fibonacci(npl2);
		npl2++;
	}
	n = npl2 - 2;

	c1 = a1 + (b1 - a1)*(Fibonacci(n)) / Fibonacci(n + 2);
	d1 = a1 + (b1 - a1)*(Fibonacci(n + 1)) / Fibonacci(n + 2);
	k++; //f(c1)

	for (int i = 2; i < n + 1; i++)
	{
		if (f(c1) <= f(d1))
		{
			b1 = d1;
			d1 = c1;
			c1 = a1 + (b1 - a1)*(Fibonacci(n + 1 - i)) / Fibonacci(n + 3 - i);
		}
		else
		{
			a1 = c1;
			c1 = d1;
			d1 = a1 + (b1 - a1)*(Fibonacci(n + 2 - i)) / Fibonacci(n + 3 - i);
		}
		k++;//f(c1) ili f(d1)
	}


	xmin4 = c1; // = d1
	k++; //f(c1)

	cout << "Method Fibonacci: " << "x=" << xmin4 << ", f(x)=" << f(xmin4) << endl;
	cout << "Kolichestvo vychisleniy: " << k << endl << endl;

	system("pause");
	return 0;
}