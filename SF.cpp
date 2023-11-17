#include "Header_0.h"

using namespace siaod_7;

// Counting frequences of letters
map<char, int> fano::count_freq(string s) {
    map<char, int> freq;
    for (char c : s) { freq[c]++; }
    return freq;
}

// Sorting by decreasing of freq
vector<char> fano::sort_by_freq(map<char, int> freq) {
    vector<pair<int, char>> pairs;
    for (auto elem : freq) { pairs.push_back({ elem.second, elem.first }); }
    sort(pairs.rbegin(), pairs.rend());

    vector<char> chars;
    for (auto elem : pairs) { chars.push_back(elem.second); }

    return chars;
}

// Dividing vector to halfs w equal summ of freq
pair<vector<char>, vector<char>> fano::split(vector<char> chars, map<char, int> freq) {
    int total = 0;
    for (char c : chars) { total += freq[c]; }

    int half = total / 2;
    int sum = 0;
    int i = 0;

    while (sum < half) { sum += freq[chars[i++]]; }

    vector<char> left(chars.begin(), chars.begin() + i);
    vector<char> right(chars.begin() + i, chars.end());

    return { left, right };
}

// Building coding tree ShannonFano`s method
void fano::build_tree(map<char, string>& codes, vector<char> chars, map<char, int> freq, string prefix) {
    if (chars.size() == 1) {
        codes[chars[0]] = prefix;
        return;
    }

    auto parts = split(chars, freq);
    build_tree(codes, parts.first, freq, prefix + "0");
    build_tree(codes, parts.second, freq, prefix + "1");
}

// Coding ShannonFano`s method
string fano::encode(string s) {
    map<char, int> freq = count_freq(s);
    vector<char> chars = sort_by_freq(freq);
    map<char, string> codes;
    build_tree(codes, chars, freq, "");

    string encoded = "";
    for (char c : s) { encoded += codes[c]; }

    return encoded;
}

// Функция для декодирования строки методом Шеннон-Фано
string fano::decode(string s, map<char, int> freq) { // Добавил параметр freq
    vector<char> chars = sort_by_freq(freq); // Использую те же частоты
    map<char, string> codes;
    build_tree(codes, chars, freq, "");

    map<string, char> reverse_codes;
    for (auto p : codes) {
        reverse_codes[p.second] = p.first;
    }

    string decoded = "";

    string code = "";

    for (char c : s) {
        code += c;
        // Check to have code in reversed dictionary
        if (reverse_codes.count(code) && reverse_codes[code] != '\0') {
            decoded += reverse_codes[code];
            code = "";
        }
    }

    return decoded;
}


int fano::help() {
    setlocale(0, "rus");
    cout << "[ S h a n n o n - F a n o ]" << endl;
    string s1 = "Цветом мой зайчишка – белый, А ещё, он очень смелый! Не боится он лисицы, Льва он тоже не боится.";
    string encoded = fano::encode(s1);
    map<char, int> freq = fano::count_freq(s1); // Добавил эту строку
    string decoded = fano::decode(encoded, freq); // Передал параметр freq
    cout << "Original phrase:  " << s1 << endl;
    cout << "Encoded phrase: " << encoded << endl;
    cout << "Decoded phrase: " << decoded << endl;
    cout << endl;

    return 0;
}