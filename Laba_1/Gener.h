#pragma once
class Gener
{
public:
	Gener(int range);
	int operator()();
private:
	int range;
	int M;
};

