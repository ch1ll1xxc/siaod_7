#include "Header_0.h"

using namespace siaod_7;

vector<pair<int, wchar_t>> LZ78::encode(const wstring& input) {
    vector<pair<int, wchar_t>> output;
    map<wstring, int> dictionary;

    wstring curr;
    int index = 0;

    for (wchar_t symbol : input) {
        curr += symbol;
        if (dictionary.find(curr) == dictionary.end()) {
            // New combination - add in dictionary and write previous combination in output
            dictionary[curr] = ++index;
            output.push_back(make_pair(dictionary[curr.substr(0, curr.size() - 1)], curr.back()));
            curr = L"";
        }
    }

    // Adding last symbol in output
    if (!curr.empty()) {
        output.push_back(make_pair(dictionary[curr], L'\0'));
    }

    return output;
}

wstring LZ78::decode(const vector<pair<int, wchar_t>>& encodedData) {
    map<int, wstring> dictionary;
    wstring output;

    int index = 0;
    for (const auto& entry : encodedData) {
        int pref_ind = entry.first;
        wchar_t suffix = entry.second;

        wstring curr;
        if (pref_ind == 0) {
            // prefixIndex == 0, it`s first symbol in decoded string

            curr = suffix;
        }
        else {
            // else getting current combination from dictionary
            curr = dictionary[pref_ind];
            // Adding current suffix to this combination
            curr += suffix;
        }

        // Adding current combination to dictionary
        dictionary[++index] = curr;

        // Adding current combination in decoded string
        output += curr;
    }

    return output;
}

int LZ78::help() {
    cout << "[ L Z 7 8 ]" << endl;
    wcout.imbue(locale(""));
    wstring s3 = L"commercommecommerce";
    vector<pair<int, wchar_t>> encodedLZ78 = encode(s3);

    wstring decodedLZ78 = decode(encodedLZ78);
    cout << "Origin string: ";
    wcout << s3 << endl;
    cout << "Encoded string: ";
    for (const auto& entry : encodedLZ78) {
        cout << "(" << entry.first << ", ";
        wcout << entry.second << ") ";
    }
    wcout << endl;
    cout << "Decoded string: ";
    wcout << decodedLZ78 << endl;

    return 0;
}