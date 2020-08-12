#pragma once
#include <iostream>

template<class T>
class Singleton
{
public:
	static T& getInstance()
	{
		static T inst;
		return inst;
	}
};