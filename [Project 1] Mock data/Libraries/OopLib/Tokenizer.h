#pragma once
#include<string>
#include<vector>

using namespace std;

class Tokenizer {
public:
	static vector<wstring> split(wstring haystack, wstring seperator);
	//take the substring in range [from, to]
	static wstring substr(wstring, int from, int to);
};
