// Huffman.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

/** 自适应huffman编码
* 杨博文
* 数媒1803
* 1359195435@qq.com
* 2020.11.3
*/
#include "pch.h"

#include <iostream>
#include <string>
#include <vector>

#include "huffman_coder.h"
#include "huffman_decoder.h"

int main()
{
	char symbol[5] = { '*','A','B','C','D' }; // 初始码表
	string initial_code[5] = { "0","00001","00010","00011","00100" }; // 首位为NEW与0
	string encode = "AADCCDD"; // 待编码字符串

	// 编码
	huffman_coder coder;
	coder.get_initialCode( symbol, initial_code, 5); // 载入初始码表 初始化根
	vector<string> out_huffman_code = coder.get_huffmanCode( encode); // 编码字符串

	// 解码
	huffman_decoder decoder;
	decoder.get_initialCode(symbol, initial_code, 5); // // 载入初始码表 初始化根
	string out_huffman_decode = decoder.get_huffmanDecode( out_huffman_code); // 解码字符串
	
	system("pause");
	return 0;
}

