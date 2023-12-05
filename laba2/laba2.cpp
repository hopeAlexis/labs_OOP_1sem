#include <iostream>
using namespace std;

class Fraction
{
private:
	int p, q;	// fraction p/q
public:
	Fraction(int p = 0, int q = 1) : p(p), q(q) {}

	int nod(int p, int q) 
	{
		if (q == 0)	return p;
		else return nod(q, p % q);
	}

	void simplify()
	{
		int n = abs(nod(p, q)); //for "-" to stay in the numerator
		p /= n;
		q /= n;
	}

	double decimal()
	{
		double dec = static_cast<double>(p) / q;
		return dec;
	}

	Fraction operator+(const Fraction& other) {
		Fraction sum;
		sum.p = (p * other.q) + (other.p * q);
		sum.q = q * other.q;
		sum.simplify();
		return sum;
	}

	Fraction operator-(const Fraction& other)
	{
		Fraction sub;
		sub.p = (p * other.q) - (other.p * q);
		sub.q = q * other.q;
		sub.simplify();
		return sub;
	}

	Fraction operator*(const Fraction& other) {
		Fraction mult;
		mult.p = p * other.p;
		mult.q = q * other.q;
		mult.simplify();
		return mult;
	}

	Fraction operator/(const Fraction& other) {
		Fraction mult;
		mult.p = p * other.q;
		mult.q = q * other.p;
		mult.simplify();
		return mult;
	}

	friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction)
	{
		out << fraction.p << "/" << fraction.q;
		return out;
	}

};

int main()
{
	Fraction x(5, 6);
	Fraction y(1, 2);
	std::cout << x + y << "\n";
	std::cout << x - y << "\n";
	std::cout << x * y << "\n";
	std::cout << x / y << "\n";
	Fraction z(-3, 9);
	std::cout << z.decimal() << "\n";
	z.simplify();
	std::cout << z << "\n";

	return 0;
}
