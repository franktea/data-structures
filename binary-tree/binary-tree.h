/*
 * binary-tree.h
 *
 *  Created on: Jun 16, 2018
 *      Author: frank
 */

#ifndef BINARY_TREE_BINARY_TREE_H_
#define BINARY_TREE_BINARY_TREE_H_

#include <memory>
#include <algorithm>
#include <queue>
#include <fstream>
#include <vector>
#include <string>

template<class T>
struct Node
{
	T value;
	std::shared_ptr<Node<T>> left, right;
	explicit Node(T v, std::shared_ptr<Node<T>> l = nullptr, std::shared_ptr<Node<T>> r = nullptr):
			value(v), left(l), right(r) {}
};

template<class T>
using node_ptr = std::shared_ptr<Node<T>>;

// 高度
template<class T>
int Height(std::shared_ptr<Node<T>> root)
{
	return root ? std::max(Height(root->left), Height(root->right)) : 0;
}

// 密度
template<class T>
double Density(std::shared_ptr<Node<T>> root)
{
	if(!root)
		return 0;

	std::function<std::pair<int, int>(std::shared_ptr<Node<T>>)> f;
	f = [&f](std::shared_ptr<Node<T>> n)
			-> std::pair<int, int> // size, height
	{
		if(! n)
			return {0, 0};

		std::pair<int, int> p1 = f(n->left);
		std::pair<int, int> p2 = f(n->right);
		return {1 + p1.first + p2.first, 1 + std::max(p1.second, p2.second)};
	};

	auto p = f(root);
	return 1.0 * p.first / p.second;
}

// (子节点中的)最近叶子节点
template<class T>
std::shared_ptr<Node<T>> NearestLeaf(std::shared_ptr<Node<T>> root)
{
	if(! root)
		return nullptr;

	auto is_leaf = [](std::shared_ptr<Node<T>> n) -> bool {
		return !n->left && !n->right;
	};

	// 广度优先
	std::queue<std::shared_ptr<Node<T>>> queue;
	queue.push(root);
	while(! queue.empty())
	{
		std::shared_ptr<Node<T>> n = queue.front();
		queue.pop();
		if(is_leaf(n))
			return n;

		if(!n->left)
			queue.push(n->left);
		if(!n->right)
			queue.push(n->right);
	}
}

// 根据节点的值判断两棵二叉树是否相等
template<class T>
bool Equal(std::shared_ptr<Node<T>> lhs, std::shared_ptr<Node<T>> rhs)
{
	std::function<bool(std::shared_ptr<Node<T>> lhs, std::shared_ptr<Node<T>> rhs)> f;
	f = [&f](std::shared_ptr<Node<T>> lhs, std::shared_ptr<Node<T>> rhs) -> bool {
		if((!lhs) ^ (!rhs)) // (lhs && !rhs) || (!lhs && rhs)
			return false;

		if(! lhs)
			return true;

		if(lhs->value != rhs->value)
			return false;

		return f(lhs->left, rhs->left) && f(lhs->right, rhs->right);
	};
	return f(lhs, rhs);
}

// 镜像
template<class T>
void Mirror(std::shared_ptr<Node<T>> root)
{
	if(root)
	{
		std::swap(root->left, root->right);
		Mirror(root->left);
		Mirror(root->right);
	}
}

// 保存为graphviz的dot文件
template<class T>
void Save(std::shared_ptr<Node<T>> root, const char* file_name);

template<>
void Save(std::shared_ptr<Node<int>> root, const char* file_name)
{
	std::vector<std::string> null_nodes; // 每个null必须定义一个别名，否则dot的图形中只显示一个节点
	auto next_null = [&null_nodes]() -> std::string {
		std::string s("null_");
		s += std::to_string(null_nodes.size());
		null_nodes.push_back(s);
		return s;
	};
	std::ofstream fs;
	fs.open(file_name);
	fs<<"digraph G {\n";
	std::function<void(std::shared_ptr<Node<int>> n)> f;
	f = [&f, &null_nodes, &fs, &next_null](std::shared_ptr<Node<int>> n) {
		if(!n || (!n->left && !n->right))
			return;

		if(! n->left)
		{
			fs<<n->value<<" -> "<<next_null()<<"\n";
		}
		else
		{
			fs<<n->value<<" -> "<<n->left->value<<"\n";
			f(n->left);
		}

		if(! n->right)
		{
			fs<<n->value<<" -> "<<next_null()<<"\n";
		}
		else
		{
			fs<<n->value<<" -> "<<n->right->value<<"\n";
			f(n->right);
		}
	};
	f(root);

	for(auto& s: null_nodes)
	{
		fs<<s<<" [label= \"null\"];\n";
	}

	fs<<"}\n";
	fs.flush();
	fs.close();
	std::cout<<"-----------\n";
}


#endif /* BINARY_TREE_BINARY_TREE_H_ */
