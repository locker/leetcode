#include <iostream>
#include <string>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<string>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ", ";
		out << '"' << *it << '"';
	}
	out << ']';
	return out;
}

class Solution {
public:
	vector<string> generateParenthesis(int n) {
		if (n == 0)
			return {};

		// Array of found permutations.
		vector<string> result;
		// Size of a permutation.
		int size = n * 2;
		// Number of opening parentheses in the current
		// permutation.
		int count = 0;
		// Buffer storing current permutation.
		string buf;
		buf.reserve(size);

		do {
			// Generate a permutation; prefer opening
			// parentheses over closing ones - this
			// guarantees that the expression will be
			// valid (balance is 0 when we are done).
			for (int i = buf.size(); i < size; ++i) {
				if (count < n) {
					buf.push_back('(');
					++count;
				} else {
					buf.push_back(')');
				}
			}
			result.push_back(buf);
			// Replace the rightmost opening parenthesis
			// with a closing one unless it violates the
			// parentheses balance, then retry.
			int balance = 0;
			for (int i = size - 1; i >= 0; --i) {
				char c = buf.back();
				buf.pop_back();
				if (c == '(') {
					--count;
					if (--balance > 0) {
						buf.push_back(')');
						break;
					}
				}
				if (c == ')')
					++balance;
			}
		} while (!buf.empty());

		return result;
	}
};

int main()
{
	Solution solution;
	for (int n = 0; n < 4; ++n)
		cout << n << " => " << solution.generateParenthesis(n) << endl;
	return 0;
}
