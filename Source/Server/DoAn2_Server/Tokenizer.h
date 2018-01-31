#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Tokenizer
{
public:
	static vector<string> Split(const string& s, const char delim);
};