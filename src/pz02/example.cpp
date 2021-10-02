#include "example.h"
#include <iostream>

int sum(int a, int b)
{
    if (a==0 && b==0) throw std::runtime_error("Example throw");
	return a + b;
}