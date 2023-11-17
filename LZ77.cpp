#include "Header_0.h"

using namespace siaod_7;

vector<lz77> LZ77::encode(string input) {
    vector<lz77> tokens;
    int window_size = 12;  // Window`s size for searching coincidence
    int lookaheadBufferSize = 5;  // Buffer`s size for watching forward

    int curr_ind = 0;
    while (curr_ind < input.size()) {
        int bestMatchOffset = 0;
        int bestMatchLength = 0;

        for (int i = 1; i <= window_size && curr_ind - i >= 0; ++i) {
            int match_len = 0;
            while (match_len < lookaheadBufferSize && curr_ind + match_len < input.size() &&
                input[curr_ind - i + match_len] == input[curr_ind + match_len]) {
                match_len++;
            }
            if (match_len > bestMatchLength) {
                bestMatchOffset = i;
                bestMatchLength = match_len;
            }
        }
        lz77 token;
        // Changed condition for [0] element
        if (input[curr_ind + bestMatchLength] != '\0')
            token = { bestMatchOffset, bestMatchLength, input[curr_ind + bestMatchLength] };
        else
            token = { bestMatchOffset, bestMatchLength, '\0' }; // "0" instead of space
        tokens.push_back(token);
        curr_ind += (bestMatchLength + 1);
    }

    return tokens;
}

string LZ77::decode(const vector<lz77>& tokens) {
    string decoded;
    for (const lz77& token : tokens) {
        for (int i = 0; i < token.length; ++i) { decoded += decoded[decoded.size() - token.offset]; }
        decoded += token.nextChar;
    }
    decoded.pop_back();
    return decoded;
}

int LZ77::help() {
    cout << "[ L Z 7 7 ]" << endl;
    string s2 = "0001001010101001101";
    std::vector<lz77> tokens = encode(s2);

    string decodedLZ77 = decode(tokens);
    cout << "Origin string: " << s2 << endl;
    cout << "Encoded string: ";
    for (const lz77& token : tokens) {
        std::cout << "(" << token.offset << ", " << token.length << ", " << token.nextChar << ") ";
    }
    cout << endl << "Decoded string: " << decodedLZ77 << endl << endl;

    return 0;
}