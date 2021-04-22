#include "pch.h"

#include "huffman_coder.h"

// 获得初始码表 与 根节点
void huffman_coder::get_initialCode(char *inSymbol, string *inCode, int num)
{
	// 获得码表
	numSymbol = num;
	for (int i = 0; i < numSymbol; i++) {
		symbol.push_back(inSymbol[i]); // 输入初始码表
		initialCode.push_back(inCode[i]);
		isFirst.push_back(1); // 未发送字符
	}
	cout << endl << "==========编码器载入码表：";
	for (int i = 0; i < numSymbol; i++) {
		cout << symbol[i] << " ";
	}
	cout << endl;

	// 初始化根结点
	root.id = 0;
	root.weight = 0;
	root.parent = nullptr;
	root.left = nullptr;
	root.right = nullptr;
	new_node = &root; // NEW初始在根
}

// 输入code，进行哈夫曼编码
vector<string> huffman_coder::get_huffmanCode(string encode)
{
	cout << "==========开始编码：" << encode << endl;
	cout << "长度：" << encode.length() << endl;

	vector<string> out_code; // 输出编码序列

	for (int i = 0; i < encode.length(); i++) { // 遍历待编码字符串
		cout << endl << "输入 第" << i + 1 << "个字符：" << encode[i] << endl;
		int index = getIndex_symbol(encode[i]); // 当前字符在symbol的下标
		Node *this_node; // 当前字符指针

		// 是否首次发送
		if (is_FirstSend(encode[i])) { // 首次发送
			cout << " 首次编码" << endl;
			
			// 更新输出序列字符串
			out_code.push_back(initialCode[0]); // 加入new
			out_code.push_back(initialCode[index]); // 加入对应初始码
			
			// 遍历树，更新结点编号 每个结点编号+2
			renew_id_huffmanTree(&root);
			// 更新哈夫曼树 原NEW结点分支，左孩子为新NEW，右孩子为首次发送字符
			new_node->left = new Node;
			new_node->left->parent = new_node;
			new_node->right = new Node;
			new_node->right->parent = new_node;
			// this 指向右孩子 更新值 权重 编号
			this_node = new_node->right;
			this_node->character = encode[i];
			this_node->id = 1;
			this_node->weight = 1; // 之后从其根开始遍历权值+1
			// new 指向左孩子
			new_node = new_node->left;
			new_node->character = symbol[0];
			new_node->id = 0;
			new_node->weight = 0;
			// 从被输出结点父节点开始，每结点权重+1，并置换
			renew_weight_huffmanTree(this_node->parent);
		}
		else { // 不是首次发送
			// 输出哈夫曼编码
			out_code.push_back(initialCode[index]); // 加入对应编码
			this_node = getNode_character_huffamanTree(&root, encode[i]); // 获得该结点指针
			cout << " 获得指针：" << this_node->character << endl;
			// 从被输出结点开始，向父节点走，每结点权重+1，并置换
			renew_weight_huffmanTree(this_node);
		}

		// 根据哈夫曼树更新编码表
		renew_initialCode(&root, "");

		cout << "   输出序列:";
		for (int n = 0; n < out_code.size(); n++) {
			cout << out_code[n] << " ";
		}
		cout << endl;
	}
	return out_code;
}

// 获取ch在symbol的下标
int huffman_coder::getIndex_symbol(char ch)
{
	int i;
	for (i = 0; i < numSymbol; i++) { // 0为NEW位
		if (symbol[i] == ch) {
			//cout << "码表位：" << i << endl;
			break;
		}
	}
	return i;
}

// 判断ch是否为第一次发送
bool huffman_coder::is_FirstSend(char ch)
{
	// 获得ch在symbol的下标
	int i = getIndex_symbol(ch);
	// 根据下标查找isFirst对应位置是否为0
	if (isFirst[i] == 0) { // 不为第一次
		return false;
	}
	else { // 为第一次
		isFirst[i] = 0;
		return true;
	}
}

// 更新结点编号
void huffman_coder::renew_id_huffmanTree(Node *node)
{
	// 编号+2
	node->id = node->id + 2;
	// 递归左右子树
	if (node->left)
		renew_id_huffmanTree(node->left);
	if (node->right)
		renew_id_huffmanTree(node->right);
}

// 获取哈夫曼树中对应字符的结点指针
Node * huffman_coder::getNode_character_huffamanTree(Node *node, char ch)
{
	// 判断该结点是否为ch
	if (node->character == ch)
		return node;
	else { // 递归到左右子结点
		if (node->left)
			if (getNode_character_huffamanTree(node->left, ch)) { // 要先判断是否获取到，否则返回null
				return getNode_character_huffamanTree(node->left, ch);
			}
		if (node->right)
			if (getNode_character_huffamanTree(node->right, ch)) {
				return getNode_character_huffamanTree(node->right, ch);
			}
	}
	return nullptr; // 不做判断与null处理，ch不在树内则出错
}

// 从输出结点开始更新权重
void huffman_coder::renew_weight_huffmanTree(Node * this_code)
{
	if (this_code == &root) { // 如果递归到根 返回
		root.weight = root.weight + 1;
		return;
	}

	// 获得对应权重最大编号结点指针
	Node *node_maxid = getNode_maxID_huffmanTree(&root, this_code->weight);
	//cout << "  权重：" << this_code->weight << " 最大编号：" << node_maxid->id << endl;
	// 该节点是否为同权重中编号最大的结点
	if (this_code == node_maxid || this_code->parent == node_maxid) { // 该节点同权重编号最大
		// 或者同权重最大编号为其父，即连续添加2个新值
		this_code->weight = this_code->weight + 1;
		renew_weight_huffmanTree(this_code->parent); // 递归父节点
	}
	else { // 不是
		// 与maxid交换位置
		change_2nodes(this_code, node_maxid); // 交换位置，再交换id
		this_code->weight = this_code->weight + 1;
		renew_weight_huffmanTree(this_code->parent); // 递归父节点
	}
}

// 获得对应权重的最大id结点
Node * huffman_coder::getNode_maxID_huffmanTree(Node * node, int weight)
{
	// 判断该结点是否为ch
	if (node->weight == weight)
		return node;
	else { // 递归到左右子结点
		// 先查右孩子（id值较大）
		if (node->right)
			if (getNode_maxID_huffmanTree(node->right, weight)) { // 要先判断是否获取到，否则返回null
				return getNode_maxID_huffmanTree(node->right, weight);
			}
		if (node->left)
			if (getNode_maxID_huffmanTree(node->left, weight)) {
				return getNode_maxID_huffmanTree(node->left, weight);
			}
	}
	return nullptr; // 不做判断与null处理，ch不在树内则出错
}
// 交换两结点位置，交换位置，再交换id
void huffman_coder::change_2nodes(Node * A, Node * B)
{
	// 复制a位置和id
	Node *copyA = new Node;
	copyA->parent = A->parent;
	copyA->id = A->id;
	if (is_leftSon(A))
		A->parent->left = copyA;
	else
		A->parent->right = copyA;
	// a结点移动到b位置，id置为Bid
	A->parent = B->parent;
	A->id = B->id;
	if (is_leftSon(B))
		B->parent->left = A;
	else
		B->parent->right = A;
	// b结点移动到a之前位置，id置为Aid
	B->parent = copyA->parent;
	B->id = copyA->id;
	if (is_leftSon(copyA))
		copyA->parent->left = B;
	else
		copyA->parent->right = B;
}
// 判断node是父节点的左孩子还是右孩子
bool huffman_coder::is_leftSon(Node * node)
{
	if (node->parent->left == node)
		return true;
	else
		return false;
}

// 根据哈夫曼树更新编码表
void huffman_coder::renew_initialCode(Node *node, string code)
{
	// 从根结点开始遍历，储存字符串
	if (node->left) { // 有左孩子
		//cout << " 进入左孩子" << code + "0" << endl;
		renew_initialCode(node->left, code + "0");
	}
	if (node->right) { // 有右孩子
		//cout << " 进入右孩子" << code + "1" << endl;
		renew_initialCode(node->right, code + "1");
	}
	if (node->left == nullptr && node->right == nullptr) {// 若为非new叶子
		// 将initialCode对应叶子字符更新为code
		int i = getIndex_symbol(node->character);
		cout << "  到达叶子：" << node->character <<
			" 更新值：" << initialCode[i] << "->" << code << endl;
		initialCode[i] = code;
	}
}
