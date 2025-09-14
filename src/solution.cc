#include "solution.hpp"
#include "comment_stats.hpp"
#include <cctype>
#include <vector>
#include <string>
#include <map>
#include <set>

// helper to lowercase a string
std::string ToLower(const std::string &s) {
    std::string result = s;
    for (char &c : result) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return result;
}

CommentStats GenerateCommentStats(const std::vector<std::string>& comments) {
    CommentStats stats;

    if (comments.empty()) {
        return stats; // empty
    }

    // characters that terminate a username
    std::set<char> terminators = {' ', '\t', '\n', '!', '?', ',', '.', '\'', '@'};

    for (const std::string &comment : comments) {
        for (size_t i = 0; i < comment.size(); ++i) {
            if (comment[i] == '@') {
                size_t j = i + 1;

                // collect username until terminator
                while (j < comment.size() && terminators.find(comment[j]) == terminators.end()) {
                    j++;
                }

                if (j > i + 1) { // ensure at least 1 character after '@'
                    std::string mention = comment.substr(i, j - i);
                    mention = ToLower(mention);
                    stats.mention_frequencies[mention]++;
                }

                i = j - 1; // continue after processed username
            }
        }
    }

    // find popular mentions
    for (const auto &entry : stats.mention_frequencies) {
        if (entry.second >= 2) {
            stats.popular_mentions.push_back(entry.first);
        }
    }

    return stats;
}
