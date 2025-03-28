#include "commonHeader.h"
#include <random>
#include <sstream>

polinom generatePolinom() {
	int len = 10;
	polinom v;
	std::random_device r;
	std::default_random_engine e(r());
	std::uniform_int_distribution<unsigned int> degree_gen(0, MAX_POWER - 1);
	std::uniform_real_distribution<double> coef_gen(-1.0, 1.0);
	std::string str;
	double coef;
	for (size_t _ = 0; _ < len; ++_) {
		coef = coef_gen(e);
		if (coef < 0) {
			str += '-';
			coef *= -1.0;
		}
		else {
			if (str.length() > 0) str += '+';
		}
		str += ' ';
		str += std::to_string(coef);
		str += " * ";
		str += 'x';
		str += std::to_string(degree_gen(e));
		str += ' ';
		str += 'y';
		str += std::to_string(degree_gen(e));
		str += ' ';
		str += 'z';
		str += std::to_string(degree_gen(e));
		str += ' ';
	}
	std::istringstream sl;
	sl.str(str);
	sl >> v;
	return v;
}

myVector<char> stringToMyvec(const std::string& str) {
	myVector<char> vec(str.length());
	for (size_t i = 0; i < str.length(); ++i) vec[i] = str[i];
	return vec;
}

bool keycmpeq(const myVector<char>& v1, const myVector<char>& v2) {
	if (v1.size() != v2.size()) return false;
	for (size_t i = 0; i < v2.size(); ++i)
		if (v1[i] != v2[i]) return false;
	return true;
}

bool keycmple(const myVector<char>& v1, const myVector<char>& v2) {
	for (size_t i = 0; i < std::min(v1.size(), v2.size()); ++i) {
		if (v1[i] < v2[i]) return true;
		if (v1[i] > v2[i]) return false;
	}
	return v1.size() < v2.size();
}