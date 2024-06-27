#include <iostream>
#include <string>
#include "cpp-container.hpp"

using namespace std;

int main()
{

 	Container<string> s1{ "hello","world" };
	cout << "Container S1: " << endl << s1 << endl;
	Container<string> s2;
	s1[0] = "Hi";
	cout << "Container S1: " << endl << s1 << endl;
	cout << "Container S2: " << endl << s2 << endl;
	Container<string> s3 = { "one","two","three" };
	cout << "Container S3: " << endl << s3 << endl;
	s2 = s3;
	cout << "Container S2: " << endl << s2 << endl;
	s2.Resize(1);
	cout << "Container S2: " << endl << s2 << endl;
	s3 = s1;
	cout << "Container S3: " << endl << s3 << endl;
	s3 = {};
	cout << "Container S3: " << endl << s3 << endl;

	cout << "***********************************************" << endl;
	
	Container<int> a{ 1,2,3,4 };
	Container<int> b;
	Container<int> c = { 20,30,40 };
	Container d({ 1,2,3,4 });
	Container e(c);
	c[0] = 100;
	b = a;
	a[0] = 1000;

	cout << "Container B: " << endl << b << endl;
	cout << "Container A: " << endl << a << endl;
	cout << "Container D: " << endl << d << endl;
	cout << "Container E: " << endl << e << endl;
 
	return 0;
}
