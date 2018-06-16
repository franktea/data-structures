/*
 * test.cpp
 *
 *  Created on: Jun 16, 2018
 *      Author: frank
 */
#include <iostream>
#include "binary-tree.h"

using namespace std;

int main()
{
	using int_node = std::shared_ptr<Node<int>>;
	int_node root = std::make_shared<Node<int>>(1);
	root->left = std::make_shared<Node<int>>(2);
	root->right = std::make_shared<Node<int>>(6);
	root->left->left = std::make_shared<Node<int>>(3);
	root->left->right = std::make_shared<Node<int>>(4);
	root->right->left = std::make_shared<Node<int>>(7);
	root->right->right = std::make_shared<Node<int>>(8);
	root->left->left->right = std::make_shared<Node<int>>(5);
	root->left->left->right->right = std::make_shared<Node<int>>(11);
	root->left->left->right->right->right = std::make_shared<Node<int>>(12);
	root->left->right->right = std::make_shared<Node<int>>(9);
	root->left->right->right->right = std::make_shared<Node<int>>(10);
	root->left->right->right->right->right = std::make_shared<Node<int>>(13);

	cout<<"density: "<<Density(root)<<"\n";

	Save(root, "./tmp.dot");

	int_node root2 = std::make_shared<Node<int>>(1);
	root2->left = std::make_shared<Node<int>>(2);
	root2->right = std::make_shared<Node<int>>(6);
	root2->left->left = std::make_shared<Node<int>>(3);
	root2->left->right = std::make_shared<Node<int>>(4);
	root2->right->left = std::make_shared<Node<int>>(7);
	root2->right->right = std::make_shared<Node<int>>(8);
	root2->left->left->right = std::make_shared<Node<int>>(5);
	root2->left->left->right->right = std::make_shared<Node<int>>(11);
	root2->left->left->right->right->right = std::make_shared<Node<int>>(12);
	root2->left->right->right = std::make_shared<Node<int>>(90);
	root2->left->right->right->right = std::make_shared<Node<int>>(10);
	root2->left->right->right->right->right = std::make_shared<Node<int>>(13);

	cout<<"eq:"<<Equal(root, root2)<<"\n";

	return 0;
}



