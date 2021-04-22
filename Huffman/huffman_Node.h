// 结构体 哈夫曼树结点
struct Node {
	int id = -1; // 结点编号
	char character; // 字符值
	int weight = -1; // 权重 字符出现个数

	Node *left = nullptr; // 子节点
	Node *right = nullptr;
	Node *parent = nullptr; // 父节点
};

#pragma once
