#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include "Map.h"

// Read next lowercase word (letters only)
static std::string next_word(std::ifstream& in) {
    char c;
    std::string w;
    while (in.get(c)) {
        if (std::isalpha(c)) {
            w += std::tolower(c);
        }
        else if (!w.empty()) {
            break;
        }
    }
    return w;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: wordcounter <filename> [top_n]\n";
        return 1;
    }
    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "Failed to open " << argv[1] << "\n";
        return 1;
    }
    int top_n = 10;
    if (argc >= 3) top_n = std::stoi(argv[2]);

    Map<std::string, int> freq;
    std::string w;
    while (!(w = next_word(in)).empty()) {
        freq[w]++;
    }

    std::vector<std::pair<std::string, int>> vec;
    for (auto& p : freq) {
        vec.emplace_back(p.first, p.second);
    }
    std::sort(vec.begin(), vec.end(), [](auto& a, auto& b) {
        return a.second > b.second;
        });

    for (int i = 0; i < top_n && i < (int)vec.size(); ++i) {
        std::cout << vec[i].first << ": " << vec[i].second << "\n";
    }
    return 0;
}