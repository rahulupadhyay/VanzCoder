#include "field_static.h"
#include <iostream>

using namespace std;

MyClass::MyClass(int fooValue)
{
	_fooValue = fooValue;
}

void MyClass::foo()
{
	cout << "_fooValue = " << MyClass::_fooValue << endl;
}

int main(int argc, char** argv)
{
	MyClass* obj = new MyClass(9);
	obj->foo();

	delete obj;
	return 0;
}
