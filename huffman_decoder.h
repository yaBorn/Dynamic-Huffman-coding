
#include <iostream>
#include <string>
#include <vector>

#include "huffman_Node.h"

using namespace std;

/* ������ */
class huffman_decoder
{
private:
	// ��ʼ���
	int numSymbol;
	vector<char> symbol;
	vector<string> initialCode;
	// �����Ƿ��Ѿ����͸��ַ��ţ�1Ϊ�ǣ�0����
	vector<int> isFirst;

	Node root; // ���ڵ�
	Node * new_node; // ָ��NEW����ָ��

public:
	void get_initialCode(char *inSymbol, string *inCode, int num); // ��ó�ʼ���
	string get_huffmanDecode(vector<string> encode); // ����������

private:
	int getIndex_initialCode(string str); // ��ȡstr��initialCode����±�

	void renew_id_huffmanTree(Node *node); // ���½���� 
	Node* getNode_character_huffamanTree(Node *node, char ch); // ��ȡ���������ж�Ӧ�ַ��Ľ��ָ��

	void renew_weight_huffmanTree(Node *this_code); // �������㿪ʼ����Ȩ��
	Node* getNode_maxID_huffmanTree(Node *node, int weight); // ��ö�ӦȨ�ص����id���
	void change_2nodes(Node *A, Node *B); // ���������λ�ã��ٽ���id
	bool is_leftSon(Node *node); // �ж�node�Ǹ��ڵ�����ӻ����Һ���

	int getIndex_symbol(char ch); // ��ȡch��symbol����±�
	void renew_initialCode(Node *node, string code); // ���ݹ����������±����
};


#pragma once
