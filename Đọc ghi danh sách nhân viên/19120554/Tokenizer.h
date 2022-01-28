#pragma once
#include<string>
#include<vector>

using namespace std;

class Tokenizer {
public:
	static vector<string> split(string haystack, string seperator);
	
	//take the substring in range [from, to]
	static string substr(string, int from, int to);
};
