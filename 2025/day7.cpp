#include <fstream>

#include <gtest/gtest.h>

const auto track_tachyon_beams(std::istream& input) {
    std::string line;
    std::getline(input, line);
    std::vector<size_t> stats(line.size());
    stats[line.find("S")]++;
    size_t n_splits = 0;
    size_t row = 0;
    while (std::getline(input, line)) {
        ++row;
        if (row % 2) {
            continue;
        }
        for (size_t pos = 0; pos < stats.size(); ++pos) {
            if (stats[pos] > 0 && line[pos] == '^') {
                if (pos - 1 >= 0) {
                    stats[pos-1] += stats[pos];
                }
                if (pos + 1 < stats.size()) {
                    stats[pos+1] += stats[pos];
                }
                stats[pos] = 0;
                ++n_splits;
            }
        }
    }
    size_t n_timelines = 0;
    for (const auto& n : stats) {
        n_timelines += n;
    }
    return std::make_pair(n_splits, n_timelines);
}

class Aoc25Day7 : public testing::Test {
};

TEST_F(Aoc25Day7, Example1) {
    std::stringstream input{".......S.......\n...............\n.......^.......\n...............\n......^.^......\n...............\n.....^.^.^.....\n...............\n....^.^...^....\n...............\n...^.^...^.^...\n...............\n..^...^.....^..\n...............\n.^.^.^.^.^...^.\n..............."};
    const auto& [n, _] = track_tachyon_beams(input);
    ASSERT_EQ(n, 21ULL);
}

TEST_F(Aoc25Day7, Example2) {
    std::stringstream input{".......S.......\n...............\n.......^.......\n...............\n......^.^......\n...............\n.....^.^.^.....\n...............\n....^.^...^....\n...............\n...^.^...^.^...\n...............\n..^...^.....^..\n...............\n.^.^.^.^.^...^.\n..............."};
    const auto& [_, n] = track_tachyon_beams(input);
    ASSERT_EQ(n, 40ULL);
}

TEST_F(Aoc25Day7, Challenge1) {
    std::ifstream input{"day7_input_manifold.txt"};
    const auto& [n, _] = track_tachyon_beams(input);
    ASSERT_EQ(n, 1642ULL);
}

TEST_F(Aoc25Day7, Challenge2) {
    std::ifstream input{"day7_input_manifold.txt"};
    const auto& [_, n] = track_tachyon_beams(input);
    ASSERT_EQ(n, 47274292756692ULL);
}
