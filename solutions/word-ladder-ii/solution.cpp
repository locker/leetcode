#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
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

template<typename T>
ostream& operator<<(ostream& out, const vector<vector<T>>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << endl << "  " << *it;
	}
	out << endl << ']';
	return out;
}

class Solution {
public:
	vector<vector<string>> findLadders(const string& begin_word,
					   const string& end_word,
					   const vector<string>& word_list) {
		// Length of an input word.
		int word_len = begin_word.length();

		// Word dictionary.
		unordered_set<string> word_dict(word_list.begin(),
						word_list.end());

		// Maps a word to a set of words leading to it in a path
		// from begin word to end word.
		unordered_map<string, vector<string>> prev;

		// Set of words to examine on the current and the next
		// BFS iteration.
		unordered_set<string> todo, todo_next;
		todo.insert(begin_word);

		// Length of paths examined at the current BFS iteration.
		unsigned path_len = 1;

		// Execute the BFS algorithm until a path is found or
		// there's nowhere to go. BFS first iterates over nodes
		// that are closer to the starting point so if we've
		// found a path, it must be a shortest one.
		bool found = false;
		while (!found && !todo.empty()) {
			auto it = todo.begin();
			auto s = *it;
			todo.erase(it);

			// Look up all possible transformations of the
			// current word in the dictionary and add them to
			// the set of words to examine on the next BFS
			// iteration.
			for (int i = 0; i < word_len; ++i) {
				for (int c = 'a'; c <= 'z'; ++c) {
					char c0 = s[i];
					if (c == c0)
						continue;
					s[i] = c;
					auto it = word_dict.find(s);
					s[i] = c0;
					if (it == word_dict.end())
						continue;
					prev[*it].push_back(s);
					todo_next.insert(*it);
				}
			}

			if (!todo.empty())
				continue;

			// End of a BFS iteration.
			++path_len;

			if (todo_next.find(end_word) != todo_next.end())
				found = true;

			// Used words are out of interest as they can't be
			// a part of a shortest path. Remove them from the
			// dictionary.
			for (const auto& s: todo_next)
				word_dict.erase(s);

			swap(todo, todo_next);
		}

		if (!found)
			return {};

		// Extract all found paths from the prev map.
		vector<vector<string>> result;

		// Backtracking state: each entry stores a pointer to
		// a chosen word and a pointer to the end of the list
		// storing available words.
		vector<pair<vector<string>::iterator,
			    vector<string>::iterator>> state;

		vector<string> path;
		path.push_back(end_word);
		do {
			// Append words until the starting point is reached.
			while (path.size() < path_len) {
				auto it = prev.find(path.back());
				state.emplace_back(it->second.begin(),
						   it->second.end());
				path.push_back(*state.back().first);
			}
			// Add the path to the result set. Note, we need to
			// reverse it, because we build paths starting from
			// the target node.
			result.push_back(path);
			reverse(result.back().begin(), result.back().end());
			// Backtrack until we find a forking point.
			while (!state.empty()) {
				path.pop_back();
				auto& p = state.back();
				if (++p.first != p.second) {
					path.push_back(*p.first);
					break;
				}
				state.pop_back();
			}
		} while (!state.empty());

		return result;
	}
};

int main()
{
	tuple<string, string, vector<string>> input[] = {
		{"dot", "hot", {"hot"}},
		{"dog", "hot", {"hot", "log"}},
		{"hot", "dog", {"dot", "hog", "dog"}},
		{"hit", "cog", {"hot", "hit", "cog", "dot", "dog"}},
		{"hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}},
		{"red", "tax", {"ted", "tex", "red", "tax", "tad", "den", "rex", "pee"}},
	};
	Solution solution;
	for (const auto& t: input) {
		const auto& beginWord = get<0>(t);
		const auto& endWord = get<1>(t);
		const auto& wordList = get<2>(t);
		auto ladders = solution.findLadders(beginWord, endWord, wordList);
		cout << "Input:" << endl <<
			"beginWord = \"" << beginWord << '"' << endl <<
			"endWord = \"" << endWord << '"' << endl <<
			"wordList = " << wordList << endl <<
			"Output: " << ladders << endl << endl;
	}
	return 0;
}
