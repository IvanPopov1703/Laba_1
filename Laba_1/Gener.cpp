#include "pch.h"
#include "Gener.h"
#include <iostream>


Gener::Gener(int range) : range(range), M((range * 2) + 1){}

int Gener::operator()()
{
	return rand() % M - range;
}