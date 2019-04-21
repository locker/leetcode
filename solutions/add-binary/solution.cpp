#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
	string addBinary(const string& a, const string& b) {
		string result;
		result.reserve(max(a.length(), b.length()) + 1);
		auto it1 = a.rbegin();
		auto it2 = b.rbegin();
		bool carry = false;
		while (it1 != a.rend() && it2 != b.rend()) {
			if (*it1 == *it2) {
				result.push_back(carry ? '1' : '0');
				carry = (*it1 == '1');
			} else {
				result.push_back(carry ? '0' : '1');
			}
			++it1;
			++it2;
		}
		auto it = it1 != a.rend() ? it1 : it2;
		auto end = it1 != a.rend() ? a.rend() : b.rend();
		while (it != end) {
			if (*it == '0') {
				result.push_back(carry ? '1' : '0');
				carry = false;
			} else {
				result.push_back(carry ? '0' : '1');
			}
			++it;
		}
		if (carry)
			result.push_back('1');
		reverse(result.begin(), result.end());
		return result;
	}
};

int main()
{
	pair<string, string> input[] = {
		{"0", "0"},
		{"0", "1"},
		{"1", "0"},
		{"10", "01"},
		{"101", "1111"},
		{"1010", "1011"},
	};
	Solution solution;
	for (const auto& p: input) {
		cout << p.first << " + " << p.second << " = " <<
			solution.addBinary(p.first, p.second) << endl;
	}
	return 0;
}
