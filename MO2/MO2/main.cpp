#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

double f(double x1, double x2, double x3)
{
	double y = 0;
	y = 7 * x1*x1 + 4 * x2*x2 + 6 * x3*x3 - 3 * x1*x2 + x1*x3 - x2*x3 + x1 - x2 + x3;
	return y;
}

double x1d(double x1, double x2, double x3)
{
	double y = 0;
	y = 14 * x1 - 3 * x2 + x3 + 1;
	return y;
}

double x2d(double x1, double x2, double x3)
{
	double y = 0;
	y = 8 * x2 - 3 * x1 - x3 - 1;
	return y;
}

double x3d(double x1, double x2, double x3)
{
	double y = 0;
	y = 12 * x3 + x1 - x2 + 1;
	return y;
}

int main() //17,141 f(x)=7*x1*x1+4*x2*x2+6*x3*x3-3*x1*x2+x1*x3-x2*x3+x1-x2+x3
{
	cout << "f(x) = 7*x1^2+4*x2^2+6*x3^2-3*x1*x2+x1*x3-x2*x3+x1-x2+x3" << endl;
	cout << "eps = 0.01, del = 0.5, alpha = 0.5" << endl << endl;

	double x10 = 1, x20 = 1, x30 = 1;//x0
	double eps0 = 0.01, del0 = 0.5, alpha0 = 0.5;

	int k = 0;//kolichestvo vychislenii
	bool stop = false;//kriterii ostanovki
					  
	//1 -- method pokoordinatnogo spuska s drobleniem shaga
	unsigned int start_time = clock();

	double x1 = x10, x2 = x20, x3 = x30;
	double x11 = x1, x21 = x2, x31 = x3;
	double alpha = alpha0;

	while (stop == false)
	{
		if (f(x1 + alpha, x2, x3) < f(x1, x2, x3))
			x11 = x1 + alpha;
		if (f(x1 - alpha, x2, x3) < f(x1, x2, x3))
			x11 = x1 - alpha;
		if ((f(x1 - alpha, x2, x3) >= f(x1, x2, x3)) && (f(x1 + alpha, x2, x3) >= f(x1, x2, x3)))
			x11 = x1;

		if (f(x11, x2 + alpha, x3) < f(x11, x2, x3))
			x21 = x2 + alpha;
		if (f(x11, x2 - alpha, x3) < f(x11, x2, x3))
			x21 = x2 - alpha;
		if ((f(x11, x2 - alpha, x3) >= f(x11, x2, x3)) && (f(x11, x2 + alpha, x3) >= f(x11, x2, x3)))
			x21 = x2;

		if (f(x11, x21, x3 + alpha) < f(x11, x21, x3))
			x31 = x3 + alpha;
		if (f(x11, x21, x3 - alpha) < f(x11, x21, x3))
			x31 = x3 - alpha;
		if ((f(x11, x21, x3 - alpha) >= f(x11, x21, x3)) && (f(x11, x21, x3 + alpha) >= f(x11, x21, x3)))
			x31 = x3;

		if (x1 == x11 || x2 == x21 || x3 == x31)
			alpha = alpha / 2;//droblenie shaga

		k += 7;

		if ((sqrt((x11 - x1)*(x11 - x1) + (x21 - x2)*(x21 - x2) + (x31 - x3)*(x31 - x3))) < eps0)
			stop = true;

		x1 = x11, x2 = x21, x3 = x31;
	}

	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;

	cout << "Method pokoordinatnogo spuska s drobleniem shaga:" << endl;
	cout << "xmin = (" << x11 << ", " << x21 << ", " << x31 << "), f(xmin) = " << f(x11, x21, x31) << endl;
	cout << "Kolichestvo vychisleniy: " << k << endl;
	cout << "Vremya vypolneniya: " << search_time << endl << endl;
	//1

	//2 -- method gradientnyi s drobleniem shaga
	start_time = clock();

	x1 = x10, x2 = x20, x3 = x30;
	double x12 = x1, x22 = x2, x32 = x3;
	alpha = alpha0;

	k = 0;//kolichestvo vychislenii
	stop = false;//kriterii ostanovki

	while (stop == false)
	{
		x12 = x1 - alpha * x1d(x1, x2, x3);
		x22 = x2 - alpha * x2d(x1, x2, x3);
		x32 = x3 - alpha * x3d(x1, x2, x3);

		k++; //f(x)

		if ((f(x12, x22, x32) - f(x1, x2, x3)) <= -1 * alpha * eps0 * (x1*x1 + x2*x2 + x3*x3))
		{
			if (sqrt(x1d(x12, x22, x32)*x1d(x12, x22, x32) + x2d(x12, x22, x32)*x2d(x12, x22, x32) + x3d(x12, x22, x32)*x3d(x12, x22, x32)) < del0)//kriterii ostanovki
			{
				k++;//(f(x0))
				stop = true;
			}
		}
		else
			alpha = alpha * 0.5;

		x1 = x12, x2 = x22, x3 = x32;
	}

	end_time = clock();
	search_time = end_time - start_time;

	cout << "Method gradientnyi s drobleniem shaga:" << endl;
	cout << "xmin = (" << x12 << ", " << x22 << ", " << x32 << "), f(xmin) = " << f(x12, x22, x32) << endl;
	cout << "Kolichestvo vychisleniy: " << k << endl;
	cout << "Vremya vypolneniya: " << search_time << endl << endl;
	//2

	system("pause");
	return 0;
}