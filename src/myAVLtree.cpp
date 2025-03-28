#include "myAVLtree.h"
#include "myQueue.h"
#include <exception>
#include <stdexcept>

#include <iostream> ////////////////
#include <iomanip>

AVLtree::node::node(Data d) : data(d), h(1), left(nullptr), right(nullptr) {}

AVLtree::node* AVLtree::leftRotation(node* n) {
	if (n == nullptr) throw std::runtime_error("Invalid left rotation argument: root nullptr");
	if (n->right == nullptr) throw std::runtime_error("Invalid left rotation argument: right nullptr");
	AVLtree::node* newn = n->right;
	n->right = newn->left;
	newn->left = n;

	n->h = 1 + ((n->right == nullptr) ? 0 : n->right->h); // right subtree is higher than left 
	newn->h = 1 + n->h;

	return newn;
}

AVLtree::node* AVLtree::rightRotation(node* n) {
	if (n == nullptr) throw std::runtime_error("Invalid right rotation argument: root nullptr");
	if (n->left == nullptr) throw std::runtime_error("Invalid right rotation argument: left nullptr");
	AVLtree::node* newn = n->left;
	n->left = newn->right;
	newn->right = n;

	n->h = 1 + ((n->left == nullptr) ? 0 : n->left->h);  // left subtree is higher than left 
	newn->h = 1 + n->h;

	return newn;
}

AVLtree::node* AVLtree::balance(node* n) {
	if (n == nullptr) return n;
	int32_t lefth = (n->left == nullptr) ? 0 : n->left->h;
	int32_t righth = (n->right == nullptr) ? 0 : n->right->h;
	n->h = 1 + ((lefth > righth) ? lefth : righth);

//	std::cout << "balancing: " << n->data.key[3] << " " << n->h << " " << lefth << " " << righth << std::endl;

	if (lefth - righth == 2) {
		lefth = (n->left->left == nullptr) ? 0 : n->left->left->h; // n->left cannot be nullptr because if is 2 vertex higher than n->right
		righth = (n->left->right == nullptr) ? 0 : n->left->right->h;
		if (lefth - righth == -1) {
			n->left = leftRotation(n->left);
		}
		n = rightRotation(n);
	}
	else if (lefth - righth == -2) {
		lefth = (n->right->left == nullptr) ? 0 : n->right->left->h;
		righth = (n->right->right == nullptr) ? 0 : n->right->right->h;
		if (lefth - righth == 1) {
			n->right = rightRotation(n->right);
		}
		n = leftRotation(n);
	}

	return n;
}

AVLtree::AVLtree() : root(nullptr) {}

Data AVLtree::find(const myVector<char>& key) const {
	if (key.size() == 0) throw std::runtime_error("Invalid key");
	AVLtree::node* currentRoot = root;
	while (currentRoot != nullptr) {
		if (keycmpeq(currentRoot->data.key, key))
			return currentRoot->data;
		if (keycmple(currentRoot->data.key, key)) currentRoot = currentRoot->right;
		else currentRoot = currentRoot->left;
	}
	return Data();
}

AVLtree::node* AVLtree::recIns(node* n, const Data& _data) {
	if (_data.key.size() == 0) throw std::runtime_error("Invalid key");

	if (n == nullptr) {
		n = new node{ _data };
		return n;
	}
	else if (keycmpeq(n->data.key, _data.key)) {
		throw std::runtime_error("Cannot insert duplicates");
	}
	else if (keycmple(n->data.key, _data.key)) {
		n->right = recIns(n->right, _data);
	}
	else {
		n->left = recIns(n->left, _data);
	}

	return balance(n);
}

AVLtree::node* AVLtree::recDel(node* n, const myVector<char>& key) {
	node* tmp = nullptr;

	if (n == nullptr) return nullptr; // no element
	else if (keycmpeq(n->data.key, key)) { // found element
		if (n->left == nullptr || n->right == nullptr) { // has only 1 son
			tmp = (n->left == nullptr) ? n->right : n->left;
			delete n;
			return tmp;
		}
		tmp = n->right;
		while (tmp->left != nullptr) tmp = tmp->left; // the next element
		n->data = tmp->data; // swap data
		n->right = recDel(n->right, tmp->data.key);
	}
	else if (keycmple(root->data.key, key)) {
		n->right = recDel(n->right, key);
	}
	else {
		n->left = recDel(n->left, key);
	}

	return balance(n);
}

void AVLtree::ins(const Data& _data) {
	root = recIns(root, _data);
}

void AVLtree::del(const myVector<char>& key) {
	if (key.size() == 0) throw std::runtime_error("Invalid key");
	root = recDel(root, key);
}

AVLtree::~AVLtree() {
	myQueue<node*> nodes;
	if (root != nullptr) nodes.push(root);
	while (!nodes.isEmpty()) {
		node* tmp = nodes.back();
		if (tmp->left != nullptr) nodes.push(tmp->left);
		if (tmp->right != nullptr) nodes.push(tmp->right);
		delete tmp;
	}
}

void AVLtree::print() const { /////////////////////////////////////
//	postorder(root, 0);
	printBT("", root, false);
	return;
	myQueue<node*> q;
	if (root != nullptr)q.push(root);
	else std::cout << "Null";
	while (!q.isEmpty()) {
		node* tmp = q.back();
		std::cout << tmp->data.key[3] << " ";
		if (tmp->left != nullptr) q.push(tmp->left);
		if (tmp->right != nullptr) q.push(tmp->right);
	}
	std::cout << std::endl << std::endl;
}

void AVLtree::postorder(node* p, int indent) const { /////////////////////////////////////
	if (p != nullptr) {
		if (p->left) postorder(p->left, indent + 4);
		if (p->right) postorder(p->right, indent + 4);
		if (indent) {
			std::cout << std::setw(indent) << ' ';
		}
		std::cout << p->data.key[3] << " " << p->h << "\n ";
	}
}

void AVLtree::printBT(const std::string& prefix, const node* node, bool isLeft) const 
{
	if (node != nullptr)
	{
		std::cout << prefix;

		std::cout << (isLeft ? "|--" : "^--");

		// print the value of the node
		std::cout << node->data.key[3] << "+" << node->h << std::endl;

		// enter the next tree level - left and right branch
		printBT(prefix + (isLeft ? "|   " : "    "), node->left, true);
		printBT(prefix + (isLeft ? "|   " : "    "), node->right, false);
	}
}