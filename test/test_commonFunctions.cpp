#include <gtest.h>
#include "commonHeader.h"

static polinom foo() {
	polinom v;
	std::string s = "123 * x1 y2 z3 + 1 * x0 y1 z0 - 10 * x3 y2 z0 - 12 * x1 y2 z3";
	std::istringstream sl;
	sl.str(s);
	sl >> v;
	return v;
}

TEST(commonFunctions, can_generate_polinom) 
{
	polinom p;
	ASSERT_NO_THROW(p = generatePolinom());
}

TEST(commonFunctions, can_convert_string_to_myVec)
{
	myVector<char> v;
	std::string str = "Hello, world!\n";
	ASSERT_NO_THROW(v = stringToMyvec(str));
}

TEST(commonFunctions, convert_string_to_myVec_has_correct_size)
{
	myVector<char> v;
	std::string str = "Hello, world!\n";
	v = stringToMyvec(str);

	EXPECT_EQ(str.length(), v.size());
}

TEST(commonFunctions, convert_string_to_myVec_is_correct)
{
	myVector<char> v;
	std::string str = "Hello, world!\n";
	v = stringToMyvec(str);

	for (size_t i = 0; i < v.size(); ++i) {
		EXPECT_EQ(str[i], v[i]);
	}
}

TEST(commonFunctions, can_cmpeq_keys)
{
	myVector<char> k1 = stringToMyvec("key1");
	myVector<char> k2 = stringToMyvec("key2");

	ASSERT_NO_THROW(keycmpeq(k1, k2));
}

TEST(commonFunctions, cmpeq_keys_correct_not_equal)
{
	myVector<char> k1 = stringToMyvec("key1");
	myVector<char> k2 = stringToMyvec("key2");

	EXPECT_EQ(false, keycmpeq(k1, k2));
}

TEST(commonFunctions, cmpeq_keys_correct_are_equal)
{
	myVector<char> k1 = stringToMyvec("key1");
	myVector<char> k2 = stringToMyvec("key1");

	EXPECT_EQ(true, keycmpeq(k1, k2));
}


TEST(commonFunctions, can_cmple_keys)
{
	myVector<char> k1 = stringToMyvec("key1");
	myVector<char> k2 = stringToMyvec("key2");

	ASSERT_NO_THROW(keycmple(k1, k2));
}

TEST(commonFunctions, cmpeq_keys_correct_are_less)
{
	myVector<char> k1 = stringToMyvec("key1");
	myVector<char> k2 = stringToMyvec("key2");

	EXPECT_EQ(true, keycmple(k1, k2));
}

TEST(commonFunctions, cmpeq_keys_correct_not_less)
{
	myVector<char> k1 = stringToMyvec("key1");
	myVector<char> k2 = stringToMyvec("key1");

	EXPECT_EQ(false, keycmple(k1, k2));
}

TEST(commonFunctions, can_create_data_with_no_operand)
{
	ASSERT_NO_THROW(Data<polinom>());
}

TEST(commonFunctions, can_create_data_with_operand)
{
	ASSERT_NO_THROW(Data<polinom>(stringToMyvec("key"), generatePolinom()));
}

TEST(commonFunctions, can_get_key)
{
	Data<polinom> data(stringToMyvec("key"), generatePolinom());
	ASSERT_NO_THROW(data.key);
}

TEST(commonFunctions, can_get_polynom)
{
	Data<polinom> data(stringToMyvec("key"), generatePolinom());
	ASSERT_NO_THROW(data.pol);
}

TEST(commonFunctions, key_is_correct)
{
	Data<polinom> data(stringToMyvec("key"), generatePolinom());
	EXPECT_EQ(true, keycmpeq(stringToMyvec("key"), data.key));
}

TEST(commonFunctions, polynom_is_correct)
{
	polinom p = foo();
	Data<polinom> data(stringToMyvec("key"), p);
	
	std::string s1, s2;
	std::ostringstream os1;
	std::ostringstream os2;
	s1.clear();
	os1.str(s1);
	os1 << p;
	s2.clear();
	os2.str(s2);
	os2 << data.pol;
	
	EXPECT_EQ(os1.str(), os2.str());
}