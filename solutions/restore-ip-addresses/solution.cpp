#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<string> &v)
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
	vector<string> restoreIpAddresses(const string& s) {
		int len = s.length();
		vector<string> result;

		// Positions in the string before which dots are placed,
		// including a virtual dot at the end of the string.
		// We first try to span as many characters as we can and
		// then backtrack reducing the number.
		int dots[4];
		int dot_count = 0;
		int target_dot_count = sizeof(dots) / sizeof(dots[0]);

		int pos = 0;
		do {
			while (pos < len && dot_count < target_dot_count) {
				int val = 0;
				for (; pos < len; ++pos) {
					int digit = s[pos] - '0';
					if (digit == 0 && val == 0) {
						// Double zero makes no sense.
						++pos;
						break;
					}
					val = val * 10 + digit;
					if (val > 255) {
						// Component is too big.
						break;
					}
				}
				dots[dot_count++] = pos;
			}
			if (pos == len && dot_count == target_dot_count) {
				// Found a combination. Append it to
				// the result.
				string addr;
				addr.reserve(len + dot_count - 1);
				int prev = 0;
				for (int i = 0; i < dot_count; ++i) {
					if (i != 0)
						addr.push_back('.');
					addr.append(s, prev, dots[i] - prev);
					prev = dots[i];
				}
				result.push_back(move(addr));
			}
			// Backtrack.
			while (dot_count > 0) {
				int prev = dot_count > 1 ?
					dots[dot_count - 2] : 0;
				pos = --dots[dot_count - 1];
				if (pos > prev)
					break;
				--dot_count;
			}
		} while (dot_count > 0);

		return result;
	}
};

int main()
{
	string input[] = {
		"",
		"111",
		"1111",
		"0000",
		"10000",
		"21111",
		"2552551",
		"172162541",
		"25525511135",
		"11111111111111",
	};
	Solution solution;
	for (const auto& s: input)
		cout << s << " => " << solution.restoreIpAddresses(s) << endl;
	return 0;
}
