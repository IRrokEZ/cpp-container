#include <iostream>
#include <string>
#include "cpp-container.hpp"

using namespace std;

template <typename T>
void PrintContainer(Container<T>& container) {
	size_t size{ container.Size() };
	cout << "Size: "s << size << endl;
	cout << "--------------------------------"s << endl;
	for (size_t index{ 0 }; index < size; ++index) {
		cout << '<' << (index+1) << "> "s << container[index] << endl;
	}
	cout << "--------------------------------"s << endl;
}

int main()
{

 	Container<string> s1{ "hello","world" };
	cout << "Container S1: " << endl;
	PrintContainer(s1);
	Container<string> s2;
	s1[0] = "Hi";
	cout << "Container S1: " << endl;
	PrintContainer(s1);
	cout << "Container S2: " << endl;
	PrintContainer(s2);
	Container<string> s3 = { "one","two","three" };
	cout << "Container S3: " << endl;
	PrintContainer(s3);
	s2 = s3;
	cout << "Container S2: " << endl;
	PrintContainer(s2);
	s2.Resize(1);
	cout << "Container S2: " << endl;
	PrintContainer(s2);	
	s3 = s1;
	cout << "Container S3: " << endl;
	PrintContainer(s3);
	s3 = {};
	cout << "Container S3: " << endl;
	PrintContainer(s3);	

	cout << "***********************************************" << endl;
	
	Container<int> a{ 1,2,3,4 };
	Container<int> b;
	Container<int> c = { 20,30,40 };
	Container d({ 1,2,3,4 });
	Container e(c);
	c[0] = 100;
	b = a;
	a[0] = 1000;

	cout << "Container B: " << endl;
	PrintContainer(b);
	cout << "Container A: " << endl;
	PrintContainer(a);
	cout << "Container D: " << endl;
	PrintContainer(d);
	cout << "Container E: " << endl;
	PrintContainer(e);

 
	return 0;
}
