#pragma once

#include "commonHeader.h"
#include "myVector.h"
#include <exception>
#include <stdexcept>

template<typename T>
class unsortedArray {
public:
	int operationsCount;
#ifdef TEST_MODE
public:
#endif 
	myVector<Data<T>> data;
public:
	unsortedArray(): operationsCount(0) {}
	Data<T> find(const myVector<char>& key) const {
		if (key.size() == 0) throw std::runtime_error("Invalid key");
		int i;
		for (i = 0; i < data.size(); ++i) {
			if (keycmpeq(data[i].key, key)) return data[i];
		}
		return Data<T>();
	}
	int findOnIndex(const myVector<char>& key) const {
		if (key.size() == 0) throw std::runtime_error("Invalid key");
		int i;
		for (i = 0; i < data.size(); ++i) {
			if (keycmpeq(data[i].key, key)) return i;
		}
		return -1;
	}
	void ins(const Data<T>& _data) {
		if (_data.key.size() == 0) throw std::runtime_error("Invalid key");
		if (data.size() >= MAX_SIZE) throw std::runtime_error("Table is too big");
		data.push_back(_data);
	}
	void del(int ind) {
		if (ind < 0 || ind >= data.size()) throw std::runtime_error("Invalid index");
		dataswap(data[ind], data[data.size() - 1]);
		data.resize(data.size() - 1);
	}

	void del(const myVector<char>& key) {
		int ind = findOnIndex(key);
		if (ind < 0 || ind >= data.size()) return;
		dataswap(data[ind], data[data.size() - 1]);
		data.resize(data.size() - 1);
	}
};