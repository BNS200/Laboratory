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

std::vector<int> findAllOccurrence(const std::string& text, const std::string& pattern) {
    std::vector<int> occurrence;
    int sizeText = text.size();
    int sizePattern = pattern.size();

    if (sizePattern == 0 || sizeText < sizePattern) {
        return occurrence;
    }

    std::vector<int> badCharTable = createBadCharTable(pattern);

    int shift = 0;
    while (shift <= sizeText - sizePattern) {
        int j = sizePattern - 1;

        while (j >= 0 && pattern[j] == text[shift + j]) {
            --j;
        }

        if (j < 0) {
            occurrence.push_back(shift);
            if (shift + sizePattern < sizeText) {
                shift += sizePattern;
            } else {
                shift += 1;
            }
        } else {
            int badChar = text[shift + j];
            shift += badCharTable[badChar];
        }
    }
    return occurrence;
}

std::vector<int> findAllIndexOccurrence(const std::string& text, const std::string& pattern, int start, int end) {
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
            if (shift + sizePattern <= end) {
                shift += sizePattern;
            } else {
                shift += 1;
            }
        } else {
            int badChar = text[shift + j];
            shift += badCharTable[badChar];
        }
    }
    return occurrence;
}

int main() {
    std::string text = "ababcabcabababdababdabcdbdababd";
    std::string pattern = "ababd";

    int firstOccurrence = findFirstPattern(text, pattern);
    std::cout << "First occurrence: " << firstOccurrence << std::endl;

    
    std::vector<int> allOccurrences = findAllOccurrence(text, pattern);
    std::cout << "All occurrences: ";
    for (int pos : allOccurrences) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;

    int start = 11;
    int end = text.size() - 1;
    std::vector<int> rangeOccurrences = findAllIndexOccurrence(text, pattern, start, end);

    std::cout << "Occurrences in the range: ";
    for (int pos : rangeOccurrences) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;

    return 0;
}

