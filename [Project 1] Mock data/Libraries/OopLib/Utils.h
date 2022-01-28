#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include <locale> 
#include <codecvt>
#include<algorithm>
#pragma warning(disable : 4996)

using namespace std;

typedef map<wchar_t, vector<wchar_t>> map_wc_vecWc;

map_wc_vecWc getAccentVietnameseLetters();
//convert standard Vietnamese characters to non-accent ones
wstring toNonAccentVietnamese(wstring);
//convert all characters in a wstring to lowercase
wstring toLower(wstring);

void printMap(map_wc_vecWc m);

template <typename T>
void printVec(vector<T> v, wstring sep = L"\n") {
	for (int i = 0; i < v.size() - 1; ++i)
		wcout << v[i] << sep;
	wcout << v.back();
}
