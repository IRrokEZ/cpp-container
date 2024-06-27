#include <iostream>
#include <string>
#include "cpp-container.hpp"

int main()
{
	using std::cout, std::endl, std::literals::string_literals::operator""s, std::string;

	Container<string> s1{ "hello","world" };
	cout << "Container S1: " << '\n' << s1 << '\n';
	Container<string> s2;
	s1[0] = "Hi";
	cout << "Container S1: " << '\n' << s1 << '\n';
	cout << "Container S2: " << '\n' << s2 << '\n';
	Container<string> s3 = { "one","two","three" };
	cout << "Container S3: " << '\n' << s3 << '\n';
	s2 = s3;
	cout << "Container S2: " << '\n' << s2 << '\n';
	s2.Resize(1);
	cout << "Container S2: " << '\n' << s2 << '\n';
	s3 = s1;
	cout << "Container S3: " << '\n' << s3 << '\n';
	s3 = {};
	cout << "Container S3: " << '\n' << s3 << '\n';

	cout << "***********************************************" << '\n';
	
	Container<int> a{ 1,2,3,4 };
	Container<int> b;
	Container<int> c = { 20,30,40 };
	Container d({ 1,2,3,4 });
	Container e(c);
	c[0] = 100;
	b = a;
	a[0] = 1000;

	cout << "Container B: " << '\n' << b << '\n';
	cout << "Container A: " << '\n' << a << '\n';
	cout << "Container D: " << '\n' << d << '\n';
	cout << "Container E: " << '\n' << e << endl;
 
	return 0;
}
