#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
	int minDistance(const string& word1, const string& word2) {
		int word1_len = word1.length();
		int word2_len = word2.length();
		// Map of distances between sub-words of word1 and word2.
		// Element (i, j) stores minimal distance between words
		// &word1[i] and &word2[j].
		vector<vector<int>> distances;
		distances.resize(word1_len + 1);
		// Fill elements corresponding to an empty word1 or word2.
		// It's trivial: to turn word1 into word2, we need to either
		// insert all characters of word2 into word1 (in case word1
		// is empty) or delete all characters from word1 (in case
		// word2 is empty).
		for (int i = 0; i <= word1_len; ++i) {
			distances[i].resize(word2_len + 1, -1);
			distances[i][word2_len] = word1_len - i;
		}
		for (int j = 0; j <= word2_len; ++j) {
			distances[word1_len][j] = word2_len - j;
		}
		// Fill elements neighboring already filled ones. Pick the
		// minimal distance among right, bottom, and bottom-right
		// neighbors after transition to this neighbor. For the
		// right and the bottom neighbor transition means insertion
		// and removal of a character, respectively, hence we need
		// to increase the distance. For the bottom-right neighbor
		// transition means either modification of the character,
		// in which case we need to increase the distance, or, if
		// word1[i] == word2[j], no op, in which case we simply
		// copy the distance.
		for (int i = word1_len - 1; i >= 0; --i) {
			for (int j = word2_len - 1; j >= 0; --j) {
				int right = distances[i + 1][j] + 1;
				int bottom = distances[i][j + 1] + 1;
				int bottom_right = distances[i + 1][j + 1];
				if (word1[i] != word2[j])
					++bottom_right;
				distances[i][j] = min({right, bottom, bottom_right});
			}
		}
		return distances[0][0];
	}
};

int main()
{
	pair<const char*, const char*> input[] = {
		{"", ""}, // 0
		{"", "ab"}, // 2
		{"abc", ""}, // 3
		{"he", "he"}, // 0
		{"he", "she"}, // 1
		{"horse", "ros"}, // 3
		{"intention", "execution"}, // 5
	};
	Solution solution;
	for (auto& p: input) {
		cout << '"' << p.first << "\", \"" << p.second << "\" => " <<
			solution.minDistance(p.first, p.second) << endl;
	}
	return 0;
}
