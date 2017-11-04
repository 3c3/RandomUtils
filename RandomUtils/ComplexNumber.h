#pragma once
#include <iostream>

class ComplexNumber
{
public:
	double real, imaginary;	

	void Input()
	{
		std::cin >> real >> imaginary;
	}

	void Print()
	{
		std::cout << real << " ";
		if (imaginary < 0) std::cout << "- " << -imaginary << 'i';
		else std::cout << "+ " << imaginary << 'i';
	}
};

ComplexNumber operator+(const ComplexNumber& a, const ComplexNumber& b)
{
	ComplexNumber result = { a.real + b.real, a.imaginary + b.imaginary };
	return result;
}

ComplexNumber operator-(const ComplexNumber& a, const ComplexNumber& b)
{
	ComplexNumber result = { a.real - b.real, a.imaginary - b.imaginary };
	return result;
}

ComplexNumber operator*(const ComplexNumber& a, const ComplexNumber& b)
{
	ComplexNumber result = { a.real*b.real - a.imaginary*b.imaginary, a.real*b.imaginary + a.imaginary*b.real };
	return result;
}

ComplexNumber operator/(const ComplexNumber& a, const ComplexNumber& b)
{
	ComplexNumber result = { a.real*b.real + a.imaginary*b.imaginary, -a.real*b.imaginary + a.imaginary*b.real };
	double mod = sqrt(b.real*b.real + b.imaginary*b.imaginary);
	result.real /= mod;
	result.imaginary /= mod;
	return result;
}