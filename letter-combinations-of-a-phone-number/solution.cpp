#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, vector<T> v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ", ";
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	vector<string> letterCombinations(const string& digits) {
		const int size = digits.size();
		if (size == 0)
			return {};

		// digit idx => letters
		const string map[] = {
			"abc",  // 2
			"def",  // 3
			"ghi",  // 4
			"jkl",  // 5
			"mno",  // 6
			"pqrs", // 7
			"tuv",  // 8
			"wxyz", // 9
		};
		auto digit_to_idx = [](char c) { return c - '2'; };

		vector<string> result;
		vector<int> combination(size, 0);

		while (true) {
			// Append the current combination to the result.
			string s;
			s.reserve(size);
			for (int k = 0; k < size; ++k) {
				int idx = digit_to_idx(digits[k]);
				s.push_back(map[idx][combination[k]]);
			}
			result.push_back(move(s));

			// Generate the next combination.
			bool found = false;
			for (int k = size - 1; k >= 0; --k) {
				int idx = digit_to_idx(digits[k]);
				int n_combinations = map[idx].length();
				if (++combination[k] < n_combinations) {
					found = true;
					break;
				}
				combination[k] = 0;
			}
			if (!found)
				break;
		}
		return result;
	}
};

int main()
{
	const char *input[] = {
		"",
		"2",
		"7",
		"23",
		"99",
		"234",
	};
	Solution solution;
	for (auto s: input) {
		cout << '"' << s << "\" => " <<
			solution.letterCombinations(s) << endl;
	}
	return 0;
}
