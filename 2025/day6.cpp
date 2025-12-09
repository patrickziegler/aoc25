#include <cmath>
#include <stack>
#include <fstream>

#include <gtest/gtest.h>

auto read_worksheet_simple(std::istream& input) {
    std::vector<size_t> added;
    std::vector<size_t> multiplied;
    std::string line, item;
    size_t i, tmp, result = 0;
    while (std::getline(input, line)) {
        std::stringstream ss{line};
        i = 0;
        while (std::getline(ss, item, ' ')) {
            if (item.empty()) {
                continue;
            }
            if (added.size() <= i) {
                added.emplace_back(0);
            }
            if (multiplied.size() <= i) {
                multiplied.emplace_back(1);
            }
            if (item == "+") {
                result += added[i];
            } else if (item == "*") {
                result += multiplied[i];
            } else {
                tmp = std::stoull(item);
                added[i] += tmp;
                multiplied[i] *= tmp;
            }
            ++i;
        }
    }
    return result;
}

auto read_worksheet_advanced(std::istream& input) {
    size_t result = 0;
    std::vector<std::string> lines;
    std::string item;
    while (std::getline(input, item)) {
        lines.emplace_back(std::move(item));
    }
    const size_t height = lines.size() - 1; // without last line
    const size_t width = lines[0].size();
    std::stack<size_t> nums, parts;
    size_t num;
    for (size_t col = width; col-- > 0; ) {
        for (size_t row = height; row-- > 0; ) {
            if (lines[row][col] == ' ') {
                continue;
            }
            parts.push(lines[row][col] - '0');
        }
        if (parts.empty()) { // column was empty
            continue;
        }
        num = 0;
        while (!parts.empty()) {
            num += parts.top() * static_cast<size_t>(std::pow(10, parts.size() - 1));
            parts.pop();
        }
        nums.push(num);
        if (lines[height][col] == '+') {
            num = 0;
            while (!nums.empty()) {
                num += nums.top();
                nums.pop();
            }
            result += num;
        } else if (lines[height][col] == '*') {
            num = 1;
            while (!nums.empty()) {
                num *= nums.top();
                nums.pop();
            }
            result += num;
        }
    }
    return result;
}

class Aoc25Day6 : public testing::Test {
};

TEST_F(Aoc25Day6, Example1) {
    std::stringstream input{"123 328  51 64 \n 45 64  387 23 \n  6 98  215 314\n*   +   *   +  "};
    size_t result = read_worksheet_simple(input);
    ASSERT_EQ(result, 4277556ULL);
}

TEST_F(Aoc25Day6, Example2) {
    std::stringstream input{"123 328  51 64 \n 45 64  387 23 \n  6 98  215 314\n*   +   *   +  "};
    size_t result = read_worksheet_advanced(input);
    ASSERT_EQ(result, 3263827ULL);
}

TEST_F(Aoc25Day6, Challenge1) {
    std::ifstream input{"day6_input_worksheet.txt"};
    size_t result = read_worksheet_simple(input);
    ASSERT_EQ(result, 4364617236318ULL);
}

TEST_F(Aoc25Day6, Challenge2) {
    // attention: take care of trailing spaces in the input file, all lines need to be of the same length
    std::ifstream input{"day6_input_worksheet.txt"};
    size_t result = read_worksheet_advanced(input);
    ASSERT_EQ(result, 9077004354241ULL);
}
