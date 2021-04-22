
#include <iostream>
#include <string>
#include <vector>

#include "huffman_Node.h"

using namespace std;

/* 解码器 */
class huffman_decoder
{
private:
	// 初始码表
	int numSymbol;
	vector<char> symbol;
	vector<string> initialCode;
	// 储存是否已经发送该种符号，1为是，0不是
	vector<int> isFirst;

	Node root; // 根节点
	Node * new_node; // 指向NEW结点的指针

public:
	void get_initialCode(char *inSymbol, string *inCode, int num); // 获得初始码表
	string get_huffmanDecode(vector<string> encode); // 哈夫曼解码

private:
	int getIndex_initialCode(string str); // 获取str在initialCode表的下标

	void renew_id_huffmanTree(Node *node); // 更新结点编号 
	Node* getNode_character_huffamanTree(Node *node, char ch); // 获取哈夫曼树中对应字符的结点指针

	void renew_weight_huffmanTree(Node *this_code); // 从输出结点开始更新权重
	Node* getNode_maxID_huffmanTree(Node *node, int weight); // 获得对应权重的最大id结点
	void change_2nodes(Node *A, Node *B); // 交换两结点位置，再交换id
	bool is_leftSon(Node *node); // 判断node是父节点的左孩子还是右孩子

	int getIndex_symbol(char ch); // 获取ch在symbol表的下标
	void renew_initialCode(Node *node, string code); // 根据哈夫曼树更新编码表
};


#pragma once
