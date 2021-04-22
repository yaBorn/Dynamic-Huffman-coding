#include "pch.h"

#include "huffman_decoder.h"

// ��ó�ʼ���
void huffman_decoder::get_initialCode(char * inSymbol, string * inCode, int num)
{
	// ������
	numSymbol = num;
	for (int i = 0; i < numSymbol; i++) {
		symbol.push_back(inSymbol[i]); // �����ʼ���
		initialCode.push_back(inCode[i]);
		isFirst.push_back(1); // δ�����ַ�
	}
	cout << endl << "==========�������������";
	for (int i = 0; i < numSymbol; i++) {
		cout << symbol[i] << " ";
	}
	cout << endl;

	// ��ʼ�������
	root.id = 0;
	root.weight = 0;
	root.parent = nullptr;
	root.left = nullptr;
	root.right = nullptr;
	new_node = &root; // NEW��ʼ�ڸ�
}

// ����������
string huffman_decoder::get_huffmanDecode(vector<string> encode)
{
	cout << "==========��ʼ���룺";
	for (int n = 0; n < encode.size(); n++) {
		cout << encode[n] << " ";
	}
	cout << endl;
	cout << "���ȣ�" << encode.size() << endl;

	string out_code = ""; // ��������ַ�

	for (int i = 0; i < encode.size(); i++) { // ��������������
		cout << endl << "���� ��" << i + 1 << "���ַ���" << encode[i] << endl;
		int index = getIndex_initialCode(encode[i]); // ��ǰ�ַ���initialCode���±�
		Node *this_node; // ��ǰ�ַ�ָ�루��NEW���ֵܣ�

		if (index == 0) { // ����ΪNEWλ
			cout << " ΪNEWλ" << endl;

			// ��ȡnew�ַ������½����ַ���
			i++;
			index = getIndex_initialCode(encode[i]); // ��ǰ�ַ���initialCode���±�
			out_code = out_code + symbol[index]; // �����ַ�
			cout << endl << "���� ��" << i + 1 << "���ַ���" << encode[i] << endl;
			cout << " ��Ӧ�ַ�Ϊ��" << symbol[index] << endl;

			// �����������½���� ÿ�������+2
			renew_id_huffmanTree(&root);
			// ���¹������� ԭNEW����֧������Ϊ��NEW���Һ���Ϊ��һ�ַ�
			new_node->left = new Node;
			new_node->left->parent = new_node;
			new_node->right = new Node;
			new_node->right->parent = new_node;
			// this ָ���Һ��� ����ֵ Ȩ�� ���
			this_node = new_node->right;
			this_node->character = symbol[index];
			this_node->id = 1;
			this_node->weight = 1; // ֮��������ʼ����Ȩֵ+1
			// new ָ������
			new_node = new_node->left;
			new_node->character = symbol[0];
			new_node->id = 0;
			new_node->weight = 0;
			// �ӱ������㸸�ڵ㿪ʼ��ÿ���Ȩ��+1�����û�
			renew_weight_huffmanTree(this_node->parent);
		}
		else { // ����NEWλ
			// ���½����ַ���
			out_code = out_code + symbol[index]; // �����ַ�
			this_node = getNode_character_huffamanTree(&root, symbol[index]); // ��øý��ָ��
			cout << " ���ָ�룺" << this_node->character << endl;
			// �ӱ������㿪ʼ���򸸽ڵ��ߣ�ÿ���Ȩ��+1�����û�
			renew_weight_huffmanTree(this_node);
		}

		// ���ݹ����������±����
		renew_initialCode(&root, "");

		cout << "   �����ַ�����" << out_code << endl;
	}

	return out_code;
}

// ��ȡstr��initialCode����±�
int huffman_decoder::getIndex_initialCode(string str)
{
	int i;
	for (i = 0; i < numSymbol; i++) { // 0ΪNEWλ
		if (initialCode[i] == str) {
			//cout << "���λ��" << i << endl;
			break;
		}
	}
	return i;
}

// ���½���� 
void huffman_decoder::renew_id_huffmanTree(Node * node)
{
	// ���+2
	node->id = node->id + 2;
	// �ݹ���������
	if (node->left)
		renew_id_huffmanTree(node->left);
	if (node->right)
		renew_id_huffmanTree(node->right);
}

// ��ȡ���������ж�Ӧ�ַ��Ľ��ָ��
Node * huffman_decoder::getNode_character_huffamanTree(Node * node, char ch)
{
	// �жϸý���Ƿ�Ϊch
	if (node->character == ch)
		return node;
	else { // �ݹ鵽�����ӽ��
		if (node->left)
			if (getNode_character_huffamanTree(node->left, ch)) { // Ҫ���ж��Ƿ��ȡ�������򷵻�null
				return getNode_character_huffamanTree(node->left, ch);
			}
		if (node->right)
			if (getNode_character_huffamanTree(node->right, ch)) {
				return getNode_character_huffamanTree(node->right, ch);
			}
	}
	return nullptr; // �����ж���null����ch�������������
}

// �������㿪ʼ����Ȩ��
void huffman_decoder::renew_weight_huffmanTree(Node * this_code)
{
	if (this_code == &root) { // ����ݹ鵽�� ����
		root.weight = root.weight + 1;
		return;
	}

	// ��ö�ӦȨ������Ž��ָ��
	Node *node_maxid = getNode_maxID_huffmanTree(&root, this_code->weight);
	//cout << "  Ȩ�أ�" << this_code->weight << " ����ţ�" << node_maxid->id << endl;
	// �ýڵ��Ƿ�ΪͬȨ���б�����Ľ��
	if (this_code == node_maxid || this_code->parent == node_maxid) { // �ýڵ�ͬȨ�ر�����
		// ����ͬȨ�������Ϊ�丸�����������2����ֵ
		this_code->weight = this_code->weight + 1;
		renew_weight_huffmanTree(this_code->parent); // �ݹ鸸�ڵ�
	}
	else { // ����
		// ��maxid����λ��
		change_2nodes(this_code, node_maxid); // ����λ�ã��ٽ���id
		this_code->weight = this_code->weight + 1;
		renew_weight_huffmanTree(this_code->parent); // �ݹ鸸�ڵ�
	}
}
// ��ö�ӦȨ�ص����id���
Node * huffman_decoder::getNode_maxID_huffmanTree(Node * node, int weight)
{
	// �жϸý���Ƿ�Ϊch
	if (node->weight == weight)
		return node;
	else { // �ݹ鵽�����ӽ��
		// �Ȳ��Һ��ӣ�idֵ�ϴ�
		if (node->right)
			if (getNode_maxID_huffmanTree(node->right, weight)) { // Ҫ���ж��Ƿ��ȡ�������򷵻�null
				return getNode_maxID_huffmanTree(node->right, weight);
			}
		if (node->left)
			if (getNode_maxID_huffmanTree(node->left, weight)) {
				return getNode_maxID_huffmanTree(node->left, weight);
			}
	}
	return nullptr; // �����ж���null����ch�������������
}
// ���������λ�ã�����λ�ã��ٽ���id
void huffman_decoder::change_2nodes(Node * A, Node * B)
{
	// ����aλ�ú�id
	Node *copyA = new Node;
	copyA->parent = A->parent;
	copyA->id = A->id;
	if (is_leftSon(A))
		A->parent->left = copyA;
	else
		A->parent->right = copyA;
	// a����ƶ���bλ�ã�id��ΪBid
	A->parent = B->parent;
	A->id = B->id;
	if (is_leftSon(B))
		B->parent->left = A;
	else
		B->parent->right = A;
	// b����ƶ���a֮ǰλ�ã�id��ΪAid
	B->parent = copyA->parent;
	B->id = copyA->id;
	if (is_leftSon(copyA))
		copyA->parent->left = B;
	else
		copyA->parent->right = B;
}
// �ж�node�Ǹ��ڵ�����ӻ����Һ���
bool huffman_decoder::is_leftSon(Node * node)
{
	if (node->parent->left == node)
		return true;
	else
		return false;
}

// ���ݹ����������±����
void huffman_decoder::renew_initialCode(Node *node, string code)
{
	// �Ӹ���㿪ʼ�����������ַ���
	if (node->left) { // ������
		//cout << " ��������" << code + "0" << endl;
		renew_initialCode(node->left, code + "0");
	}
	if (node->right) { // ���Һ���
		//cout << " �����Һ���" << code + "1" << endl;
		renew_initialCode(node->right, code + "1");
	}
	if (node->left == nullptr && node->right == nullptr) {// ��Ϊ��newҶ��
		// ��initialCode��ӦҶ���ַ�����Ϊcode
		int i = getIndex_symbol(node->character);
		cout << "  ����Ҷ�ӣ�" << node->character <<
			" ����ֵ��" << initialCode[i] << "->" << code << endl;
		initialCode[i] = code;
	}
}
// ��ȡch��symbol���±�
int huffman_decoder::getIndex_symbol(char ch)
{
	int i;
	for (i = 0; i < numSymbol; i++) { // 0ΪNEWλ
		if (symbol[i] == ch) {
			//cout << "���λ��" << i << endl;
			break;
		}
	}
	return i;
}