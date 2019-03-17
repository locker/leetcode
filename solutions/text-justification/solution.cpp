#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void printStrings(const vector<string>& v, bool one_per_line = false)
{
	cout << '[';
	if (one_per_line)
		cout << endl;
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (one_per_line)
			cout << "  ";
		cout << '"' << *it << '"';
		if (it != v.end() - 1)
			cout << ',';
		if (one_per_line)
			cout << endl;
	}
	cout << ']';
	if (one_per_line)
		cout << endl;
}

class Solution {
public:
	vector<string> fullJustify(const vector<string>& words, int max_width) {
		vector<string> result;
		auto end = words.begin();
		while (end != words.end()) {
			auto begin = end++;
			int width = begin->length();
			for (; end != words.end(); ++end) {
				int new_width = width + end->length() + 1;
				if (new_width > max_width)
					break;
				width = new_width;
			}
			int word_count = end - begin;
			int space_count = word_count - 1;
			int delim_width = 1;
			int delim_remain = 0;
			int padding = max_width - width;
			if (padding > 0 && space_count > 0 && end != words.end()) {
				delim_width += padding / space_count;
				delim_remain = padding % space_count;
				if (delim_remain > 0)
					++delim_width;
				padding = 0;
			}
			string line;
			line.reserve(max_width);
			for (auto it = begin; it != end; ++it) {
				if (it != begin) {
					line.append(delim_width, ' ');
					if (--delim_remain == 0)
						--delim_width;
				}
				line.append(*it);
			}
			if (padding > 0)
				line.append(padding, ' ');
			result.push_back(move(line));
		}
		return result;
	}
};

int main()
{
	pair<vector<string>, int> input[] = {
		{{}, 10},
		{{"This", "is", "an", "example", "of", "text", "justification."}, 16},
		{{"What", "must", "be", "acknowledgment", "shall", "be"}, 16},
		{{"Science", "is", "what", "we", "understand", "well", "enough",
		  "to", "explain",  "to", "a", "computer.", "Art", "is", "everything",
		  "else", "we", "do"}, 20},
	};
	Solution solution;
	for (auto& p: input) {
		cout << "Input:" << endl;
		cout << "words = ";
		printStrings(p.first);
		cout << endl;
		cout << "max_width = " << p.second << endl;
		cout << "Output:" << endl;
		printStrings(solution.fullJustify(p.first, p.second), true);
		cout << endl;
	}
	return 0;
}
