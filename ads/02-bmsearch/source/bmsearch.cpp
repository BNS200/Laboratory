#include <iostream>
#include <string>
#include <vector>

std::vector<int> createBadCharTable(const std::string& pattern) {
    const int maxSizeChar = 256;
    std::vector<int> badCharTable(maxSizeChar, pattern.size());
    int m = pattern.size();
    for (int i = 0; i < m - 1; ++i) {
        badCharTable[pattern[i]] = m - i - 1;
    }
    return badCharTable;
}

int findFirstPattern(const std::string& text, const std::string& pattern) {
    int sizeText = text.size();
    int sizePattern = pattern.size();

    if (sizePattern == 0 || sizeText < sizePattern) {
        return -1;
    }

    std::vector<int> badCharTable = createBadCharTable(pattern);
    int shift = 0;
    while (shift <= sizeText - sizePattern) {
        int j = sizePattern - 1;

        while (j >= 0 && pattern[j] == text[shift + j]) {
            --j;
        }
        if (j < 0) {
            return shift;
        } else {
            int badChar = text[shift + j];
            shift += badCharTable[badChar];
        }
    }

    return -1;
}

std::vector<int> findAllOccurrence (const std::string& text, const std::string& pattern){
    std::vector<int> occurrence;
    int sizeText = text.size();
    int sizePattern = pattern.size();

    if (sizePattern == 0 || sizeText < sizePattern) {
        return occurrence;
    }

    std::vector<int> badCharTable = createBadCharTable(pattern);

    int shift = 0;
    while (shift <= sizeText - sizePattern){
        int j = sizePattern - 1;

        while (j >= 0 && pattern[j] == text[shift + j]) {
            --j;
        }

        if (j < 0) {
            occurrence.push_back(shift);
            if (shift + sizePattern < sizeText) {
                int badCharIndex = badCharTable[text[shift + sizePattern]];
                shift += sizePattern - badCharIndex;
            } else {
                int badChar = text[shift + j];
                shift += badCharTable[badChar];
                }
        }
    }
    return occurrence;
}

std::vector<int> findAllInRange(const std::string& text, const std::string& pattern, int start, int end) {
    std::vector<int> occurrence;
    int sizeText = text.size();
    int sizePattern = pattern.size();


    if (sizePattern == 0 || sizeText < sizePattern || start < 0 || end >= sizeText || start > end) {
        return occurrence;
    }
    std::vector<int> badCharTable = createBadCharTable(pattern);

    int shift = start;
    while (shift <= end - sizePattern + 1) {
        int j = sizePattern - 1;

        while (j >= 0 && pattern[j] == text[shift + j]) {
            --j;
        }

        if (j < 0) {
            occurrence.push_back(shift);
            if (shift + sizePattern < sizeText) {
                int badCharIndex = badCharTable[text[shift + sizePattern]];
                shift += sizePattern - badCharIndex;
            } else {
                int badChar = text[shift + j];
                shift += badCharTable[badChar];
                }
        }
    }
    return occurrence;
}
