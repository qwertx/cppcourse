#include <iostream>
using namespace std;
class Complex
{
friend ostream& operator<<(ostream& os, const Complex& c);
friend istream& operator>>(istream& is, Complex& c);
private:
  	double real;
  	double image;
public:
  	Complex(const Complex& complex) :real{ complex.real }, image{ complex.image } {

  	}
  	Complex(double Real=0, double Image=0) :real{ Real }, image{ Image } {

  	}
	// 成员函数有this指针, 因此只有一个参数, 或者写在外面
  	Complex operator+(const Complex& rhs) const { 
		return Complex{this->real + rhs.real, this->image + rhs.image};
	}
	Complex operator-(const Complex& rhs) const { 
		return Complex{this->real - rhs.real, this->image - rhs.image};
	}
	Complex operator*(const Complex& rhs) const { 
		auto a = this->real;
		auto b = this->image;
		auto c = rhs.real;
		auto d = rhs.image;
		return Complex{a*c-b*d, b*c+a*d};
	}
	Complex operator/(const Complex& rhs) const {
		auto a = this->real;
		auto b = this->image;
		auto c = rhs.real;
		auto d = rhs.image;
		return Complex{(a*c+b*d)/(c*c+d*d), (b*c-a*d)/(c*c+d*d)};
	}
	
};

// 输入输出必须是非成员函数, 如果是成员函数, 第一个参数就变成this了
ostream& operator<<(ostream& os, const Complex& c) {
	// 或者用?:判断
	return os << "(" << noshowpos << c.real << showpos << c.image << "i)";
}
istream& operator>>(istream& is, Complex& c) {
	return is >> c.real >> c.image;
}


int main() {
  	Complex z1, z2;
  	cin >> z1;
  	cin >> z2;
  	cout << z1 << " " << z2 << endl;
  	cout << z1 + z2 << endl;
  	cout << z1 - z2 << endl;
  	cout << z1 * z2 << endl;
  	cout << z1 / z2 << endl;
  	return 0;
}