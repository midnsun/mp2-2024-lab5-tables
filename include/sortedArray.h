#pragma once

#include "commonHeader.h"
#include "myVector.h"
#include <exception>
#include <stdexcept>

template<typename T>
class sortedArray {
public:
	int operationsCount;
#ifdef TEST_MODE
public:
#endif 
	myVector<Data<T>> data;
public:
	sortedArray(): operationsCount(0) {}
	Data<T> find(const myVector<char>& key) const {
		if (key.size() == 0) throw std::runtime_error("Invalid key");
		int low = 0, high = data.size() - 1, mid;
		while (low <= high) {
			mid = low + (high - low) / 2;
			if (keycmpeq(data[mid].key, key)) return data[mid];
			if (keycmple(data[mid].key, key)) low = mid + 1;
			else high = mid - 1;
		}
		return Data<T>();
	}
	int findOnIndex(const myVector<char>& key) const {
		if (key.size() == 0) throw std::runtime_error("Invalid key");
		int low = 0, high = data.size() - 1, mid;
		while (low <= high) {
			mid = low + (high - low) / 2;
			if (keycmpeq(data[mid].key, key)) return mid;
			if (keycmple(data[mid].key, key)) low = mid + 1;
			else high = mid - 1;
		}
		return -1;
	}
	void ins(const Data<T>& _data) {
		if (_data.key.size() == 0) throw std::runtime_error("Invalid key");
		if (data.size() >= MAX_SIZE) throw std::runtime_error("Table is too big");
		data.push_back(_data);
		int ind = data.size() - 1;
		while (ind > 0 && keycmple(data[ind].key, data[ind - 1].key)) {
			dataswap(data[ind], data[ind - 1]);
			--ind;
		}
	}
	void del(int ind) {
		if (ind < 0 || ind >= data.size()) throw std::runtime_error("Invalid index");
		while (ind < data.size() - 1) {
			dataswap(data[ind], data[ind + 1]);
			++ind;
		}
		data.resize(data.size() - 1);
	}
	void del(const myVector<char>& key) {
		int ind = findOnIndex(key);
		if (ind < 0 || ind >= data.size()) return;
		while (ind < data.size() - 1) {
			dataswap(data[ind], data[ind + 1]);
			++ind;
		}
		data.resize(data.size() - 1);
	}
};