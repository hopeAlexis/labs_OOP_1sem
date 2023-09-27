#include <iostream>
using namespace std;

class fraction
{
private:
	int n, d;
public:
	fraction(int n, int d) : n(n), d(d) {}
	int sum()
	{

	}

	int sub()
	{

	}

	int mult()
	{

	}

	int div()
	{

	}

	void simplify()
	{
		while (n != 0 && d != 0)
		{	
			if (n > d) n = n % d;
			else d = d % n;
		}
		
	}

	void print()
	{
		cout << n << "/" << d;
	}

};

int main()
{

}