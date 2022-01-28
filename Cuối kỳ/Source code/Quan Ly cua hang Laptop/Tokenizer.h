#pragma once
#include<string>
#include<vector>

using namespace std;

class Tokenizer {
public:
	static vector<wstring> split(wstring haystack, wstring seperator) {
		vector<wstring> tokens;
		int startPos = 0;
		int sepPos = 0;
		wstring token;

		while (1) {
			sepPos = haystack.find(seperator, startPos);

			if (sepPos != string::npos) {
				token = haystack.substr(startPos, sepPos - startPos);
				tokens.push_back(token);

				startPos = seperator.length() + sepPos;
			}
			//the remaining word
			else {
				token = haystack.substr(startPos, haystack.length() - startPos);
				tokens.push_back(token);
				break;
			}
		}

		return tokens;
	}
};
