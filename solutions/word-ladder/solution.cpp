#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<string>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << '"' << *it << '"';
	}
	out << ']';
	return out;
}

class Solution {
public:
	int ladderLength(const string& begin_word, const string& end_word,
			 const vector<string>& word_list) {
		// Length of an input word.
		int word_len = begin_word.length();

		// Word dictionary.
		unordered_set<string> word_dict(word_list.begin(),
						word_list.end());

		// End of level marker for BFS.
		const string empty;

		// BFS queue.
		queue<string> todo;
		todo.push(begin_word);
		todo.push(empty);

		// Length of the shortest path from begin_word to end_word.
		// The path includes at least two elements: begin_word and
		// end_word themselves.
		int path_len = 2;

		while (true) {
			string s = todo.front();
			todo.pop();
			if (s == empty) {
				// End of BFS level. Increment the path
				// length and proceed to the next level.
				if (todo.empty())
					return 0;
				++path_len;
				todo.push(empty);
				continue;
			}
			// Look up all possible transformations of the
			// current word in the dictionary and add them
			// to the BFS queue.
			for (int i = 0; i < word_len; ++i) {
				char c0 = s[i];
				for (int c = 'a'; c <= 'z'; ++c) {
					if (c == c0)
						continue;
					s[i] = c;
					auto it = word_dict.find(s);
					if (it != word_dict.end()) {
						if (*it == end_word)
							return path_len;
						todo.push(*it);
						word_dict.erase(it);
					}
				}
				s[i] = c0;
			}
		}
	}
};

int main()
{
	tuple<string, string, vector<string>> input[] = {
		{"hot", "lot", {"hot"}}, // 0
		{"dot", "hot", {"hot"}}, // 2
		{"dog", "hot", {"hot", "log"}}, // 0
		{"hot", "dog", {"dot", "dog"}}, // 3
		{"hit", "cog", {"hot", "dot", "dog", "lot", "log"}}, // 0
		{"hit", "cog", {"hot", "hit", "cog", "dot", "dog"}}, // 5
		{"hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}}, // 5
	};
	Solution solution;
	for (const auto& t: input) {
		const auto& beginWord = get<0>(t);
		const auto& endWord = get<1>(t);
		const auto& wordList = get<2>(t);
		auto len = solution.ladderLength(beginWord, endWord, wordList);
		cout << "Input:" << endl <<
			"beginWord = \"" << beginWord << '"' << endl <<
			"endWord = \"" << endWord << '"' << endl <<
			"wordList = " << wordList << endl <<
			"Output: " << len << endl << endl;
	}
	return 0;
}
