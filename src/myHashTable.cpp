#include "myHashTable.h"
#include <exception>
#include <stdexcept>

uint32_t myHashTable::murmurHash(const myVector<char>& key) const {
	uint32_t m = 0x5bd1e995;
	uint32_t r = 24;
	uint32_t seed = 0;
	uint32_t len = key.size();
	uint32_t h = seed ^ len;
	uint32_t k;
	uint32_t i = 0;
	while (len >= 4) {
		k = key[i];
		k |= key[i + 1] << 8;
		k |= key[i + 2] << 16;
		k |= key[i + 3] << 24;
		k *= m;
		k ^= k >> r;
		r *= m;
		h *= m;
		h ^= k;
		i += 4;
		len -= 4;
	}
	switch (len)
	{
	case 3:
		h ^= key[i + 2] << 16;
	case 2:
		h ^= key[i + 1] << 8;
	case 1:
		h ^= key[i];
		h *= m;
	default:
		break;
	}
	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;
	return h;
}
uint32_t myHashTable::hash2(const myVector<char>& key) const {
	uint32_t k = 0;
	for (size_t i = 0; i < key.size(); ++i) {
		k += uint32_t(key[i]);
	}
	return k % (data.size() - 1) + 1;
}
myHashTable::myHashTable() : data(MAX_SIZE) {
	for (size_t i = 0; i < MAX_SIZE; ++i) {
		data[i].second = 0;
	}
}
Data myHashTable::find(const myVector<char>& key) const {
	if (key.size() == 0) throw std::runtime_error("Invalid key");
	uint32_t step;
	uint32_t ind;
	uint32_t h1 = murmurHash(key);
	uint32_t h2 = hash2(key);
	for (step = 0; step < MAX_SIZE; ++step) {
		ind = (h1 + step * h2) % data.size();
		if (data[ind].second == 0) return Data();
		else if (data[ind].second == 1 && keycmpeq(data[ind].first.key, key)) return data[ind].first;
	}
	return Data();
}
int myHashTable::findOnIndex(const myVector<char>& key) const {
	if (key.size() == 0) throw std::runtime_error("Invalid key");
	uint32_t step;
	uint32_t ind;
	uint32_t h1 = murmurHash(key);
	uint32_t h2 = hash2(key);
	for (step = 0; step < MAX_SIZE; ++step) {
		ind = (h1 + step * h2) % data.size();
		if (data[ind].second == 0) return -1;
		else if (data[ind].second == 1 && keycmpeq(data[ind].first.key, key)) return ind;
	}
	return -1;
}
void myHashTable::ins(const Data& _data) {
	if (_data.key.size() == 0) throw std::runtime_error("Invalid key");
	std::pair<Data, char> _pdata;
	_pdata.first = _data;
	_pdata.second = 1;

	uint32_t step;
	uint32_t ind;
	uint32_t h1 = murmurHash(_data.key);
	uint32_t h2 = hash2(_data.key);
	for (step = 0; step < MAX_SIZE; ++step) {
		ind = (h1 + step * h2) % data.size();
		if (data[ind].second == 0 || data[ind].second == 2) {
			data[ind] = _pdata;
			return;
		}
		else if (data[ind].second == 1 && keycmpeq(data[ind].first.key, _data.key)) throw std::runtime_error("Element already exists");
	}
	throw std::runtime_error("Table is full");
}
void myHashTable::del(int ind) {
	if (ind < 0 || ind >= data.size()) throw std::runtime_error("Invalid index");
	data[ind].second = 2;
}
void myHashTable::del(const myVector<char>& key) {
	int ind = findOnIndex(key);
	if (ind < 0 || ind >= data.size()) return;
	data[ind].second = 2;
}