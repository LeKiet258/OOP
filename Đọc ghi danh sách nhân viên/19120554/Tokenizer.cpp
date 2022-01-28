#include "Tokenizer.h"

vector<string> Tokenizer::split(string haystack, string seperator){
	vector<string> tokens;
	int startPos = 0;
	int sepPos = 0;
	string token;

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

string Tokenizer::substr(string line, int from, int to) {
	if(to < 0)
		to = line.length() + to;
	return line.substr(from, to - from + 1);
}