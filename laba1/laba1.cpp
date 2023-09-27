#include <iostream>

class ICalcer
{
public:
	double f(double x)
	{
		return 4 * x * x * x;
	}
	virtual double calcInt(double a, double b) = 0;
};

class Trapezoid : public ICalcer
{
private:
	int points;
public:
	Trapezoid(int points) : points(points) {}
	double calcInt(double a, double b) override
	{
		double sum = 0.0;
		double dx = (b - a) / (this->points - 1);
		double x = a;
		for (int i = 1; i < this->points; i++)
		{
			sum += f(x);
			x += dx;
		}
		sum += f(a) / 2 + f(b) / 2;
		sum *= dx;
		return sum;
	}
};

class Simpson : public ICalcer
{
private:
	int points;
public:
	Simpson(int points) : points(points) {}
	double calcInt(double a, double b) override
	{
		double sum = f(a) + f(b);
		double dx = (b - a) / (this->points - 1);
		double x = a;
		for (int i = 1; i < this->points; i++)
		{
			if (i % 2 == 0)
				sum += 2*f(x);
			else 
				sum += 4*f(x);
			x += dx;
		}
		sum *= dx/3;
		return sum;
	}
};

int main()
{
	double a = 1;
	double b = 10;
	int points = 1000;
	double trapSum, simpSum, integralSum = 9999;

	Trapezoid trap(points);
	Simpson simp(points);
	trapSum = trap.calcInt(a, b);
	simpSum = simp.calcInt(a, b);

	std::cout << "Trapezoidal sum = " << trapSum;
	std::cout << "\nSimpson sum = " << simpSum;
	std::cout << "\nIntegral sum = " << integralSum;
}