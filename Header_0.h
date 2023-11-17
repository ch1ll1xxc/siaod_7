#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct lz77 {
	int offset;
	int length;
	char nextChar;
};

namespace siaod_7 {
	namespace fano {
		map<char, int> count_freq(string s);
		vector<char> sort_by_freq(map<char, int> freq);
		pair<vector<char>, vector<char>> split(vector<char> chars, map<char, int> freq);
		void build_tree(map<char, string>& codes, vector<char> chars, map<char, int> freq, string prefix);
		string encode(string s);
		string decode(string s, map<char, int> freq);
		int help();
	}
	namespace LZ77 {
		vector<lz77> encode(string input);
		string decode(const vector<lz77>& tokens);
		int help();
	}
	namespace LZ78 {
		vector<pair<int, wchar_t>> encode(const wstring& input);
		wstring decode(const vector<pair<int, wchar_t>>& encodedData);
		int help();
	}
}