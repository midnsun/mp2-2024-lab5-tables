#include <gtest.h>
#define TEST_MODE
#include "unsortedArray.h"

static unsortedArray<polinom> table;

static polinom foo() {
	polinom v;
	std::string s = "123 * x1 y2 z3 + 1 * x0 y1 z0 - 10 * x3 y2 z0 - 12 * x1 y2 z3";
	std::istringstream sl;
	sl.str(s);
	sl >> v;
	return v;
}

TEST(unsortedArray, can_create_unsorted_array)
{
	ASSERT_NO_THROW(unsortedArray<polinom>());
}

TEST(unsortedArray, can_single_insert)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"),foo());

	ASSERT_NO_THROW(arr.ins(d));
}

TEST(unsortedArray, cant_insert_empty_data)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec(""), foo());

	ASSERT_ANY_THROW(arr.ins(d));
}

TEST(unsortedArray, can_single_find_existing_data)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	ASSERT_NO_THROW(arr.find(stringToMyvec("test_polynom")));
}

TEST(unsortedArray, can_single_find_non_existing_data)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	ASSERT_NO_THROW(arr.find(stringToMyvec("test_polynom1")));
}

TEST(unsortedArray, cant_single_find_empty_data)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	ASSERT_ANY_THROW(arr.find(stringToMyvec("")));
}

TEST(unsortedArray, single_find_has_correct_keys)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	d = arr.find(stringToMyvec("test_polynom"));

	EXPECT_EQ(true, keycmpeq(stringToMyvec("test_polynom"), d.key));
}

TEST(unsortedArray, single_find_has_correct_polynoms)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	d = arr.find(stringToMyvec("test_polynom"));

	std::string s1, s2;
	std::ostringstream os1;
	std::ostringstream os2;
	s1.clear();
	os1.str(s1);
	os1 << foo();
	s2.clear();
	os2.str(s2);
	os2 << d.pol;

	EXPECT_EQ(os1.str(), os2.str());
}

TEST(unsortedArray, single_find_non_existing_data_is_correct)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	d = arr.find(stringToMyvec("test_polynom1"));

	EXPECT_EQ(0, d.key.size());
}

TEST(unsortedArray, can_find_on_index)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	ASSERT_NO_THROW(arr.findOnIndex(stringToMyvec("test_polynom")));
}

TEST(unsortedArray, can_find_on_index_non_existing_data)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	ASSERT_NO_THROW(arr.findOnIndex(stringToMyvec("test_polynom1")));
}

TEST(unsortedArray, cant_find_on_index_empty_data)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	ASSERT_ANY_THROW(arr.findOnIndex(stringToMyvec("")));
}

TEST(unsortedArray, find_on_index_non_existing_data_is_correct)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	EXPECT_EQ(-1, arr.findOnIndex(stringToMyvec("test_polynom1")));
}

TEST(unsortedArray, find_on_index_has_correct_keys)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	int ind = arr.findOnIndex(stringToMyvec("test_polynom"));

	EXPECT_EQ(true, keycmpeq(stringToMyvec("test_polynom"), arr.data[ind].key));
}

TEST(unsortedArray, find_on_index_has_correct_polynoms)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	int ind = arr.findOnIndex(stringToMyvec("test_polynom"));

	std::string s1, s2;
	std::ostringstream os1;
	std::ostringstream os2;
	s1.clear();
	os1.str(s1);
	os1 << foo();
	s2.clear();
	os2.str(s2);
	os2 << arr.data[ind].pol;

	EXPECT_EQ(os1.str(), os2.str());
}

TEST(unsortedArray, can_single_delete)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	ASSERT_NO_THROW(arr.del(stringToMyvec("test_polynom")));
}

TEST(unsortedArray, single_delete_is_correct)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);
	arr.del(stringToMyvec("test_polynom"));
	d = arr.find(stringToMyvec("test_polynom"));
	EXPECT_EQ(0, d.key.size());
}

TEST(unsortedArray, can_delete_non_existing_data)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);
	ASSERT_NO_THROW(arr.del(stringToMyvec("test_polynom1")));
}

TEST(unsortedArray, delete_non_existing_data_is_correct)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);
	arr.del(stringToMyvec("test_polynom1"));
	d = arr.find(stringToMyvec("test_polynom"));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("test_polynom"), d.key));
}

TEST(unsortedArray, can_delete_on_index)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);
	int ind = arr.findOnIndex(stringToMyvec("test_polynom"));

	ASSERT_NO_THROW(arr.del(ind));
}

TEST(unsortedArray, cant_delete_on_invalid_index_0)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	ASSERT_ANY_THROW(arr.del(-1));
}

TEST(unsortedArray, cant_delete_on_invalid_index_1)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	ASSERT_ANY_THROW(arr.del(10000000));
}

TEST(unsortedArray, delete_on_index_is_correct)
{
	unsortedArray<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);
	int ind = arr.findOnIndex(stringToMyvec("test_polynom"));
	arr.del(ind);
	d = arr.find(stringToMyvec("test_polynom"));
	EXPECT_EQ(0, d.key.size());
}

TEST(unsortedArray, multiple_insert_and_find)
{
	table.ins(Data<polinom>(stringToMyvec("pol0"), generatePolinom()));
	table.ins(Data<polinom>(stringToMyvec("pol1"), generatePolinom()));
	table.ins(Data<polinom>(stringToMyvec("pol2"), generatePolinom()));
	table.ins(Data<polinom>(stringToMyvec("pol3"), generatePolinom()));
	table.ins(Data<polinom>(stringToMyvec("pol4"), generatePolinom()));
	table.ins(Data<polinom>(stringToMyvec("pol5"), generatePolinom()));
	table.ins(Data<polinom>(stringToMyvec("pol6"), generatePolinom()));
	table.ins(Data<polinom>(stringToMyvec("pol7"), generatePolinom()));
	table.ins(Data<polinom>(stringToMyvec("pol8"), generatePolinom()));
	table.ins(Data<polinom>(stringToMyvec("pol9"), generatePolinom()));

	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol0"), table.find(stringToMyvec("pol0")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol1"), table.find(stringToMyvec("pol1")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol2"), table.find(stringToMyvec("pol2")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol3"), table.find(stringToMyvec("pol3")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol4"), table.find(stringToMyvec("pol4")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol5"), table.find(stringToMyvec("pol5")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol6"), table.find(stringToMyvec("pol6")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol7"), table.find(stringToMyvec("pol7")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol8"), table.find(stringToMyvec("pol8")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol9"), table.find(stringToMyvec("pol9")).key));
}

TEST(unsortedArray, multiple_delete_0)
{
	table.del(stringToMyvec("pol0"));
	EXPECT_EQ(0, table.find(stringToMyvec("pol0")).key.size());
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol1"), table.find(stringToMyvec("pol1")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol2"), table.find(stringToMyvec("pol2")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol3"), table.find(stringToMyvec("pol3")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol4"), table.find(stringToMyvec("pol4")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol5"), table.find(stringToMyvec("pol5")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol6"), table.find(stringToMyvec("pol6")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol7"), table.find(stringToMyvec("pol7")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol8"), table.find(stringToMyvec("pol8")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol9"), table.find(stringToMyvec("pol9")).key));
}

TEST(unsortedArray, multiple_delete_1) {
	table.del(stringToMyvec("pol1"));
	EXPECT_EQ(0, table.find(stringToMyvec("pol0")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol1")).key.size());
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol2"), table.find(stringToMyvec("pol2")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol3"), table.find(stringToMyvec("pol3")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol4"), table.find(stringToMyvec("pol4")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol5"), table.find(stringToMyvec("pol5")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol6"), table.find(stringToMyvec("pol6")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol7"), table.find(stringToMyvec("pol7")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol8"), table.find(stringToMyvec("pol8")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol9"), table.find(stringToMyvec("pol9")).key));
}

TEST(unsortedArray, multiple_delete_2) {
	table.del(stringToMyvec("pol2"));
	EXPECT_EQ(0, table.find(stringToMyvec("pol0")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol1")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol2")).key.size());
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol3"), table.find(stringToMyvec("pol3")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol4"), table.find(stringToMyvec("pol4")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol5"), table.find(stringToMyvec("pol5")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol6"), table.find(stringToMyvec("pol6")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol7"), table.find(stringToMyvec("pol7")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol8"), table.find(stringToMyvec("pol8")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol9"), table.find(stringToMyvec("pol9")).key));
}

TEST(unsortedArray, multiple_delete_3) {
	table.del(stringToMyvec("pol3"));
	EXPECT_EQ(0, table.find(stringToMyvec("pol0")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol1")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol2")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol3")).key.size());
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol4"), table.find(stringToMyvec("pol4")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol5"), table.find(stringToMyvec("pol5")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol6"), table.find(stringToMyvec("pol6")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol7"), table.find(stringToMyvec("pol7")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol8"), table.find(stringToMyvec("pol8")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol9"), table.find(stringToMyvec("pol9")).key));
}

TEST(unsortedArray, multiple_delete_4) {
	table.del(stringToMyvec("pol4"));
	EXPECT_EQ(0, table.find(stringToMyvec("pol0")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol1")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol2")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol3")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol4")).key.size());
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol5"), table.find(stringToMyvec("pol5")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol6"), table.find(stringToMyvec("pol6")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol7"), table.find(stringToMyvec("pol7")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol8"), table.find(stringToMyvec("pol8")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol9"), table.find(stringToMyvec("pol9")).key));
}

TEST(unsortedArray, multiple_delete_5) {
	table.del(stringToMyvec("pol5"));
	EXPECT_EQ(0, table.find(stringToMyvec("pol0")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol1")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol2")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol3")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol4")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol5")).key.size());
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol6"), table.find(stringToMyvec("pol6")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol7"), table.find(stringToMyvec("pol7")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol8"), table.find(stringToMyvec("pol8")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol9"), table.find(stringToMyvec("pol9")).key));
}

TEST(unsortedArray, multiple_delete_6) {
	table.del(stringToMyvec("pol6"));
	EXPECT_EQ(0, table.find(stringToMyvec("pol0")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol1")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol2")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol3")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol4")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol5")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol6")).key.size());
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol7"), table.find(stringToMyvec("pol7")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol8"), table.find(stringToMyvec("pol8")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol9"), table.find(stringToMyvec("pol9")).key));
}

TEST(unsortedArray, multiple_delete_7) {
	table.del(stringToMyvec("pol7"));
	EXPECT_EQ(0, table.find(stringToMyvec("pol0")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol1")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol2")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol3")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol4")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol5")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol6")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol7")).key.size());
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol8"), table.find(stringToMyvec("pol8")).key));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol9"), table.find(stringToMyvec("pol9")).key));
}

TEST(unsortedArray, multiple_delete_8) {
	table.del(stringToMyvec("pol8"));
	EXPECT_EQ(0, table.find(stringToMyvec("pol0")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol1")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol2")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol3")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol4")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol5")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol6")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol7")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol8")).key.size());
	EXPECT_EQ(true, keycmpeq(stringToMyvec("pol9"), table.find(stringToMyvec("pol9")).key));
}

TEST(unsortedArray, multiple_delete_9) {
	table.del(stringToMyvec("pol9"));
	EXPECT_EQ(0, table.find(stringToMyvec("pol0")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol1")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol2")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol3")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol4")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol5")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol6")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol7")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol8")).key.size());
	EXPECT_EQ(0, table.find(stringToMyvec("pol9")).key.size());
}