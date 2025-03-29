#include <gtest.h>
#define TEST_MODE
#include "myAVLtree.h"

static AVLtree<polinom> table;

static polinom foo() {
	polinom v;
	std::string s = "123 * x1 y2 z3 + 1 * x0 y1 z0 - 10 * x3 y2 z0 - 12 * x1 y2 z3";
	std::istringstream sl;
	sl.str(s);
	sl >> v;
	return v;
}

TEST(AVLtree, can_create_unsorted_array)
{
	ASSERT_NO_THROW(AVLtree<polinom>());
}

void AVLtreeInterface::test_can_create_node() {
	node n(Data<polinom>(stringToMyvec("test_polynom"), foo()));
}
TEST(AVLtree, can_create_node)
{
	AVLtreeInterface iface;
	ASSERT_NO_THROW(iface.test_can_create_node());
}

void AVLtreeInterface::test_can_right_rotation() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	n->left = new node{ Data<polinom>(stringToMyvec("pol1"), foo()) };
	n->right = new node{ Data<polinom>(stringToMyvec("pol2"), foo()) };
	node* newn = rightRotation(n);
}
TEST(AVLtree, can_right_rotation)
{
	AVLtreeInterface iface;
	ASSERT_NO_THROW(iface.test_can_right_rotation());
}

void AVLtreeInterface::test_cant_right_rotation_nullptr_root() {
	node* n = AVLtree::root;
	node* newn = rightRotation(n);
}
TEST(AVLtree, cant_right_rotation_nullptr_root)
{
	AVLtreeInterface iface;
	ASSERT_ANY_THROW(iface.test_cant_right_rotation_nullptr_root());
}

void AVLtreeInterface::test_cant_right_rotation_nullptr_left_son() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	n->right = new node{ Data<polinom>(stringToMyvec("pol2"), foo()) };
	node* newn = rightRotation(n);
}
TEST(AVLtree, cant_right_rotation_nullptr_left_son)
{
	AVLtreeInterface iface;
	ASSERT_ANY_THROW(iface.test_cant_right_rotation_nullptr_left_son());
}

bool AVLtreeInterface::test_right_rotation_only_two_elements_correct() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	n->left = new node{ Data<polinom>(stringToMyvec("pol1"), foo()) };
	node* tmpleft = n->left;
	n->h = 2;
	node* newn = rightRotation(n);
	if ( 
		newn == tmpleft &&
		newn->right == n && 
		newn->h == 2 &&
		newn->right->h == 1 &&
		newn->left == nullptr &&
		newn->right->right == nullptr &&
		newn->right->left == nullptr
		) return true;
	return false;
}
TEST(AVLtree, right_rotation_only_two_elements_correct)
{
	AVLtreeInterface iface;
	EXPECT_EQ(true, iface.test_right_rotation_only_two_elements_correct());
}

bool AVLtreeInterface::test_right_rotation_correctly_interact_with_other_elements() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	n->left = new node{ Data<polinom>(stringToMyvec("pol1"), foo()) };
	node* tmpleft = n->left;
	n->right = new node{ Data<polinom>(stringToMyvec("pol2"), foo()) };
	node* tmpright = n->right;
	n->right->left = new node{ Data<polinom>(stringToMyvec("pol3"), foo()) };
	node* tmprleft = n->right->left;
	n->right->right = new node{ Data<polinom>(stringToMyvec("pol4"), foo()) };
	node* tmprright = n->right->right;
	n->h = 3;
	n->right->h = 2;
	node* newn = rightRotation(n->right);
	if (
		newn == tmprleft &&
		newn->right == tmpright &&
		newn->h == 2 &&
		newn->right->h == 1 &&
		newn->left == nullptr &&
		newn->right->right == tmprright &&
		newn->right->left == nullptr &&
		n->left == tmpleft
		) return true;
	return false;
}
TEST(AVLtree, right_rotation_correctly_interact_with_other_elements)
{
	AVLtreeInterface iface;
	EXPECT_EQ(true, iface.test_right_rotation_correctly_interact_with_other_elements());
}

void AVLtreeInterface::test_can_left_rotation() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	n->left = new node{ Data<polinom>(stringToMyvec("pol1"), foo()) };
	n->right = new node{ Data<polinom>(stringToMyvec("pol2"), foo()) };
	node* newn = leftRotation(n);
}
TEST(AVLtree, can_left_rotation)
{
	AVLtreeInterface iface;
	ASSERT_NO_THROW(iface.test_can_left_rotation());
}

void AVLtreeInterface::test_cant_left_rotation_nullptr_root() {
	node* n = AVLtree::root;
	node* newn = leftRotation(n);
}
TEST(AVLtree, cant_left_rotation_nullptr_root)
{
	AVLtreeInterface iface;
	ASSERT_ANY_THROW(iface.test_cant_left_rotation_nullptr_root());
}

void AVLtreeInterface::test_cant_left_rotation_nullptr_right_son() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	n->left = new node{ Data<polinom>(stringToMyvec("pol1"), foo()) };
	node* newn = leftRotation(n);
}
TEST(AVLtree, cant_left_rotation_nullptr_right_son)
{
	AVLtreeInterface iface;
	ASSERT_ANY_THROW(iface.test_cant_left_rotation_nullptr_right_son());
}

bool AVLtreeInterface::test_left_rotation_only_two_elements_correct() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	n->right = new node{ Data<polinom>(stringToMyvec("pol1"), foo()) };
	node* tmpright = n->right;
	n->h = 2;
	node* newn = leftRotation(n);
	if (
		newn == tmpright &&
		newn->left == n &&
		newn->h == 2 &&
		newn->left->h == 1 &&
		newn->right == nullptr &&
		newn->left->right == nullptr &&
		newn->left->left == nullptr
		) return true;
	return false;
}
TEST(AVLtree, left_rotation_only_two_elements_correct)
{
	AVLtreeInterface iface;
	EXPECT_EQ(true, iface.test_left_rotation_only_two_elements_correct());
}

bool AVLtreeInterface::test_left_rotation_correctly_interact_with_other_elements() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	n->left = new node{ Data<polinom>(stringToMyvec("pol1"), foo()) };
	node* tmpleft = n->left;
	n->right = new node{ Data<polinom>(stringToMyvec("pol2"), foo()) };
	node* tmpright = n->right;
	n->left->left = new node{ Data<polinom>(stringToMyvec("pol3"), foo()) };
	node* tmplleft = n->left->left;
	n->left->right = new node{ Data<polinom>(stringToMyvec("pol4"), foo()) };
	node* tmplright = n->left->right;
	n->h = 3;
	n->left->h = 2;
	node* newn = leftRotation(n->left);
	if (
		newn == tmplright &&
		newn->left == tmpleft &&
		newn->h == 2 &&
		newn->left->h == 1 &&
		newn->right == nullptr &&
		newn->left->left == tmplleft &&
		newn->left->right == nullptr &&
		tmpright == n->right
		) return true;
	return false;
}
TEST(AVLtree, left_rotation_correctly_interact_with_other_elements)
{
	AVLtreeInterface iface;
	EXPECT_EQ(true, iface.test_left_rotation_correctly_interact_with_other_elements());
}

void AVLtreeInterface::test_can_balance() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	n->left = new node{ Data<polinom>(stringToMyvec("pol1"), foo()) };
	n->right = new node{ Data<polinom>(stringToMyvec("pol2"), foo()) };
	node* newn = balance(n);
}
TEST(AVLtree, can_balance)
{
	AVLtreeInterface iface;
	ASSERT_NO_THROW(iface.test_can_balance());
}

void AVLtreeInterface::test_can_balance_nullptr() {
	node* n = AVLtree::root;
	node* newn = balance(n);
}
TEST(AVLtree, can_balance_nullptr)
{
	AVLtreeInterface iface;
	ASSERT_NO_THROW(iface.test_can_balance_nullptr());
}

bool AVLtreeInterface::test_correctly_balancing_one_small_left_disbalance() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	n->left = new node{ Data<polinom>(stringToMyvec("pol1"), foo()) };
	node* tmpl = n->left;
	n->right = new node{ Data<polinom>(stringToMyvec("pol2"), foo()) };
	node* tmpr = n->right;
	n->left->right = new node{ Data<polinom>(stringToMyvec("pol4"), foo()) };
	node* tmplr = n->left->right;
	n->left->right->right = new node{ Data<polinom>(stringToMyvec("pol5"), foo()) };
	node* tmplrr = n->left->right->right;
	n->h = 4;
	tmpl->h = 3;
	tmplr->h = 2;
	node* newn = balance(n->left);
	if (
		newn == tmplr &&
		newn->left == tmpl &&
		newn->h == 2 &&
		newn->left->h == 1 &&
		newn->right == tmplrr &&
		newn->left->left == nullptr &&
		newn->left->right == nullptr &&
		tmpr == n->right
		) return true;
	return false;
}
TEST(AVLtree, correctly_balancing_one_small_left_disbalance)
{
	AVLtreeInterface iface;
	EXPECT_EQ(true, iface.test_correctly_balancing_one_small_left_disbalance());
}

bool AVLtreeInterface::test_correctly_balancing_one_big_left_disbalance() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	n->left = new node{ Data<polinom>(stringToMyvec("pol1"), foo()) };
	node* tmpl = n->left;
	n->right = new node{ Data<polinom>(stringToMyvec("pol2"), foo()) };
	node* tmpr = n->right;
	n->right->right = new node{ Data<polinom>(stringToMyvec("pol4"), foo()) };
	node* tmprr = n->right->right;
	n->right->left = new node{ Data<polinom>(stringToMyvec("pol5"), foo()) };
	node* tmprl = n->right->left;
	n->right->left->right = new node{ Data<polinom>(stringToMyvec("pol6"), foo()) };
	node* tmprlr = n->right->left->right;
	n->right->left->left = new node{ Data<polinom>(stringToMyvec("pol7"), foo()) };
	node* tmprll = n->right->left->left;
	n->h = 4;
	tmpr->h = 3;
	tmprl->h = 2;
	node* newn = balance(n);
	if (
		newn == tmprl &&
		newn->left == n &&
		newn->right == tmpr &&
		newn->right->right == tmprr &&
		newn->right->left == tmprlr &&
		newn->left->right == tmprll &&
		newn->left->left == tmpl &&
		tmprl->h == 3 &&
		n->h == 2 &&
		tmpr->h == 2 &&
		tmprr->h == 1 &&
		tmprlr->h == 1 &&
		tmprll->h == 1 &&
		tmpl->h == 1
		) return true;
	return false;
}
TEST(AVLtree, correctly_balancing_one_big_left_disbalance)
{
	AVLtreeInterface iface;
	EXPECT_EQ(true, iface.test_correctly_balancing_one_big_left_disbalance());
}

bool AVLtreeInterface::test_correctly_balancing_one_small_right_disbalance() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	n->right = new node{ Data<polinom>(stringToMyvec("pol1"), foo()) };
	node* tmpr = n->right;
	n->left = new node{ Data<polinom>(stringToMyvec("pol2"), foo()) };
	node* tmpl = n->left;
	n->right->left = new node{ Data<polinom>(stringToMyvec("pol4"), foo()) };
	node* tmprl = n->right->left;
	n->right->left->left = new node{ Data<polinom>(stringToMyvec("pol5"), foo()) };
	node* tmprll = n->right->left->left;
	n->h = 4;
	tmpr->h = 3;
	tmprl->h = 2;
	node* newn = balance(n->right);
	if (
		newn == tmprl &&
		newn->right == tmpr &&
		newn->h == 2 &&
		newn->right->h == 1 &&
		newn->left == tmprll &&
		newn->right->right == nullptr &&
		newn->right->left == nullptr &&
		tmpl == n->left
		) return true;
	return false;
}
TEST(AVLtree, correctly_balancing_one_small_right_disbalance)
{
	AVLtreeInterface iface;
	EXPECT_EQ(true, iface.test_correctly_balancing_one_small_right_disbalance());
}

bool AVLtreeInterface::test_correctly_balancing_one_big_right_disbalance() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	n->left = new node{ Data<polinom>(stringToMyvec("pol1"), foo()) };
	node* tmpl = n->left;
	n->right = new node{ Data<polinom>(stringToMyvec("pol2"), foo()) };
	node* tmpr = n->right;
	n->left->right = new node{ Data<polinom>(stringToMyvec("pol4"), foo()) };
	node* tmplr = n->left->right;
	n->left->left = new node{ Data<polinom>(stringToMyvec("pol5"), foo()) };
	node* tmpll = n->left->left;
	n->left->right->right = new node{ Data<polinom>(stringToMyvec("pol6"), foo()) };
	node* tmplrr = n->left->right->right;
	n->left->right->left = new node{ Data<polinom>(stringToMyvec("pol7"), foo()) };
	node* tmplrl = n->left->right->left;
	n->h = 4;
	tmpl->h = 3;
	tmplr->h = 2;
	node* newn = balance(n);
	if (
		newn == tmplr &&
		newn->right == n &&
		newn->left == tmpl &&
		newn->left->left == tmpll &&
		newn->left->right == tmplrl &&
		newn->right->left == tmplrr &&
		newn->right->right == tmpr &&
		tmplr->h == 3 &&
		n->h == 2 &&
		tmpl->h == 2 &&
		tmpll->h == 1 &&
		tmplrl->h == 1 &&
		tmplrr->h == 1 &&
		tmpr->h == 1
		) return true;
	return false;
}
TEST(AVLtree, correctly_balancing_one_big_right_disbalance)
{
	AVLtreeInterface iface;
	EXPECT_EQ(true, iface.test_correctly_balancing_one_big_right_disbalance());
}

void AVLtreeInterface::test_can_recursive_insert() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol1"), foo()) };
	n->left = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	n->right = new node{ Data<polinom>(stringToMyvec("pol2"), foo()) };
	node* newn = recIns( n, Data<polinom>(stringToMyvec("pol3"), foo()) );
}
TEST(AVLtree, can_recursive_insert)
{
	AVLtreeInterface iface;
	ASSERT_NO_THROW(iface.test_can_recursive_insert());
}

void AVLtreeInterface::test_can_recursive_insert_nullptr() {
	node* n = AVLtree::root;
	node* newn = recIns(n, Data<polinom>(stringToMyvec("pol3"), foo()));
}
TEST(AVLtree, can_recursive_insert_nullptr)
{
	AVLtreeInterface iface;
	ASSERT_NO_THROW(iface.test_can_recursive_insert_nullptr());
}

bool AVLtreeInterface::test_recursive_insert_nullptr_is_correct() {
	node* n = AVLtree::root;
	node* newn = recIns(n, Data<polinom>(stringToMyvec("pol3"), foo()));
	if (
		keycmpeq(newn->data.key, stringToMyvec("pol3"))
		) return true;
	return false;
}
TEST(AVLtree, recursive_insert_nullptr_is_correct)
{
	AVLtreeInterface iface;
	EXPECT_EQ(true, iface.test_recursive_insert_nullptr_is_correct());
}

bool AVLtreeInterface::test_recursive_insert_is_correct() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol1"), foo()) };
	n->left = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	n->right = new node{ Data<polinom>(stringToMyvec("pol2"), foo()) };
	node* newn = recIns(n->left, Data<polinom>(stringToMyvec("pol3"), foo()));
	if (
		keycmpeq(n->left->right->data.key, stringToMyvec("pol3")) &&
		n->left->left == nullptr
		) return true;
	return false;
}
TEST(AVLtree, recursive_insert_is_correct)
{
	AVLtreeInterface iface;
	EXPECT_EQ(true, iface.test_recursive_insert_is_correct());
}

void AVLtreeInterface::test_can_recursive_delete() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol1"), foo()) };
	n->left = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	n->right = new node{ Data<polinom>(stringToMyvec("pol2"), foo()) };
	node* newn = recDel(n, stringToMyvec("pol1"));
}
TEST(AVLtree, can_recursive_delete)
{
	AVLtreeInterface iface;
	ASSERT_NO_THROW(iface.test_can_recursive_delete());
}

void AVLtreeInterface::test_can_recursive_delete_nullptr() {
	node* n = AVLtree::root;
	node* newn = recDel(n, stringToMyvec("pol1"));
}
TEST(AVLtree, can_recursive_delete_nullptr)
{
	AVLtreeInterface iface;
	ASSERT_NO_THROW(iface.test_can_recursive_delete_nullptr());
}

bool AVLtreeInterface::test_recursive_delete_nullptr_is_correct() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol1"), foo()) };
	n->left = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	node* tmpl = n->left;
	n->right = new node{ Data<polinom>(stringToMyvec("pol2"), foo()) };
	node* tmpr = n->right;
	node* newn = recDel(nullptr, stringToMyvec("pol1"));
	node* tmp = n;
	if (
		newn == nullptr &&
		n == tmp &&
		n->left == tmpl &&
		n->right == tmpr
		) return true;
	return false;
}
TEST(AVLtree, recursive_delete_is_nullptr_correct)
{
	AVLtreeInterface iface;
	EXPECT_EQ(true, iface.test_recursive_delete_nullptr_is_correct());
}

bool AVLtreeInterface::test_recursive_delete_is_correct_0() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol1"), foo()) };
	n->left = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	node* tmpl = n->left;
	n->right = new node{ Data<polinom>(stringToMyvec("pol2"), foo()) };
	node* tmpr = n->right;
	node* newn = recDel(n, stringToMyvec("pol1"));
	if (
		newn->right == nullptr &&
		newn->h == 2 &&
		newn->left->h == 1 && 
		newn->left == tmpl &&
		newn == n &&
		keycmpeq( newn->data.key, stringToMyvec("pol2") ) &&
		keycmpeq( newn->left->data.key, stringToMyvec("pol0") )
		) return true;
	return false;
}
TEST(AVLtree, recursive_delete_is_correct_0)
{
	AVLtreeInterface iface;
	EXPECT_EQ(true, iface.test_recursive_delete_is_correct_0());
}

bool AVLtreeInterface::test_recursive_delete_is_correct_1() {
	node* n = AVLtree::root;
	n = new node{ Data<polinom>(stringToMyvec("pol1"), foo()) };
	n->left = new node{ Data<polinom>(stringToMyvec("pol0"), foo()) };
	node* tmpl = n->left;
	n->right = new node{ Data<polinom>(stringToMyvec("pol2"), foo()) };
	node* tmpr = n->right;
	node* newn = recDel(n->left, stringToMyvec("pol1"));
	node* tmp = n;
	if (
		newn == n->left &&
		n == tmp &&
		n->left == tmpl &&
		n->right == tmpr
		) return true;
	return false;
}
TEST(AVLtree, recursive_delete_is_correct_1)
{
	AVLtreeInterface iface;
	EXPECT_EQ(true, iface.test_recursive_delete_is_correct_1());
}

TEST(AVLtree, can_single_insert)
{
	AVLtree<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());

	ASSERT_NO_THROW(arr.ins(d));
}

TEST(AVLtree, cant_single_insert_existing_data)
{
	AVLtree<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());

	arr.ins(d);
	ASSERT_ANY_THROW(arr.ins(d));
}

TEST(AVLtree, cant_insert_empty_data)
{
	AVLtree<polinom> arr;
	Data<polinom> d(stringToMyvec(""), foo());

	ASSERT_ANY_THROW(arr.ins(d));
}

TEST(AVLtree, can_single_find_existing_data)
{
	AVLtree<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	ASSERT_NO_THROW(arr.find(stringToMyvec("test_polynom")));
}

TEST(AVLtree, can_single_find_non_existing_data)
{
	AVLtree<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	ASSERT_NO_THROW(arr.find(stringToMyvec("test_polynom1")));
}

TEST(AVLtree, cant_single_find_empty_data)
{
	AVLtree<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	ASSERT_ANY_THROW(arr.find(stringToMyvec("")));
}

TEST(AVLtree, single_find_has_correct_keys)
{
	AVLtree<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	d = arr.find(stringToMyvec("test_polynom"));

	EXPECT_EQ(true, keycmpeq(stringToMyvec("test_polynom"), d.key));
}

TEST(AVLtree, single_find_has_correct_polynoms)
{
	AVLtree<polinom> arr;
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

TEST(AVLtree, single_find_non_existing_data_is_correct)
{
	AVLtree<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	d = arr.find(stringToMyvec("test_polynom1"));

	EXPECT_EQ(0, d.key.size());
}

TEST(AVLtree, can_single_delete)
{
	AVLtree<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);

	ASSERT_NO_THROW(arr.del(stringToMyvec("test_polynom")));
}

TEST(AVLtree, single_delete_is_correct)
{
	AVLtree<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);
	arr.del(stringToMyvec("test_polynom"));
	d = arr.find(stringToMyvec("test_polynom"));
	EXPECT_EQ(0, d.key.size());
}

TEST(AVLtree, can_delete_non_existing_data)
{
	AVLtree<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);
	ASSERT_NO_THROW(arr.del(stringToMyvec("test_polynom1")));
}

TEST(AVLtree, delete_non_existing_data_is_correct)
{
	AVLtree<polinom> arr;
	Data<polinom> d(stringToMyvec("test_polynom"), foo());
	arr.ins(d);
	arr.del(stringToMyvec("test_polynom1"));
	d = arr.find(stringToMyvec("test_polynom"));
	EXPECT_EQ(true, keycmpeq(stringToMyvec("test_polynom"), d.key));
}

TEST(AVLtree, multiple_insert_and_find)
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

TEST(AVLtree, multiple_delete_0)
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

TEST(AVLtree, multiple_delete_1) {
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

TEST(AVLtree, multiple_delete_2) {
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

TEST(AVLtree, multiple_delete_3) {
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

TEST(AVLtree, multiple_delete_4) {
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

TEST(AVLtree, multiple_delete_5) {
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

TEST(AVLtree, multiple_delete_6) {
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

TEST(AVLtree, multiple_delete_7) {
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

TEST(AVLtree, multiple_delete_8) {
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

TEST(AVLtree, multiple_delete_9) {
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