#include <iostream>
using namespace std;

namespace numbers

{
	class complexNumber
	{
	private:
		double mReal, mImaginary;
	public:
		complexNumber(double real = 0, double imaginary = 0) : mReal(real), mImaginary(imaginary) {}
		complexNumber(const complexNumber& number) : complexNumber(number.mReal, number.mImaginary) {}

		virtual ~complexNumber() = default;

		double const getReal() { return mReal; }
		void setReal(double real) { mReal = real; }

		double const getImaginary() { return mImaginary; }
		void setImaginary(double imaginary) { mImaginary = imaginary; }

		friend bool operator==(const complexNumber& number1, const complexNumber& number2)
		{

		}

		friend ostream& operator<<(ostream& out, const complexNumber& number)
		{
			out << "( " << number.mReal << ", " << number.mImaginary << " )";
			return out;
		}
	};
}

int main()
{
	using namespace numbers;

	auto number1 = complexNumber{ 10. };
	auto number2 = complexNumber{ 11. };
	cout << number1;
}