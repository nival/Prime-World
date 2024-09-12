#include "foo.h"

char* Foo1()
{
	return "Test!";
}

void Foo2()
{
	std::cout << Foo1();
}