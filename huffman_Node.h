// �ṹ�� �����������
struct Node {
	int id = -1; // �����
	char character; // �ַ�ֵ
	int weight = -1; // Ȩ�� �ַ����ָ���

	Node *left = nullptr; // �ӽڵ�
	Node *right = nullptr;
	Node *parent = nullptr; // ���ڵ�
};

#pragma once
