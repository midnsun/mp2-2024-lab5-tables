#pragma once

#define LOG
#define MAX_SIZE 1000003

#include "polinom.h"
#include "myVector.h"
#include <string>

template <typename T>
struct Data { // If key.size() == 0 than data not existing
	myVector<char> key;
	T pol;
	Data() {}
	Data(myVector<char> _key, T _pol) : key(_key), pol(_pol) {}
};

polinom generatePolinom();
myVector<char> stringToMyvec(const std::string& str);
bool keycmpeq(const myVector<char>& v1, const myVector<char>& v2);
bool keycmple(const myVector<char>& v1, const myVector<char>& v2);

template <typename T>
void dataswap(Data<T>& left, Data<T>& right) {
	Data<T> tmp = left;
	left = right;
	right = tmp;
}