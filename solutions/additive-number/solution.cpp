#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <utility>

using namespace std;

class Solution {
	bool isAdditiveOne(string_view num1, string_view num2,
			   string_view rem, int* len) {
		int l1 = num1.length();
		int l2 = num2.length();
		if ((num1[0] == '0' && l1 != 1) || (num2[0] == '0' && l2 != 1))
			return false;
		int rl = rem.length();
		if (rl < max(l1, l2))
			return false;
		string sum;
		bool carry = false;
		for (int i = 0; i < max(l1, l2); ++i) {
			int d1 = i < l1 ? (num1[l1 - i - 1] - '0') : 0;
			int d2 = i < l2 ? (num2[l2 - i - 1] - '0') : 0;
			int d = d1 + d2 + (carry ? 1 : 0);
			if (d >= 10) {
				d -= 10;
				carry = true;
			} else {
				carry = false;
			}
			sum.push_back(d + '0');
		}
		if (carry)
			sum.push_back('1');
		*len = sum.length();
		if (rl < *len)
			return false;
		if (!equal(sum.rbegin(), sum.rend(), rem.begin()))
			return false;
		return true;
	}
	bool isAdditiveRemaining(string_view num1, string_view num2,
				 string_view rem) {
		while (!rem.empty()) {
			int len;
			if (!isAdditiveOne(num1, num2, rem, &len))
				return false;
			num1 = num2;
			num2 = rem.substr(0, len);
			rem = rem.substr(len);
		}
		return true;
	}
public:
	bool isAdditiveNumber(const string& num) {
		int l = num.length();
		for (int l1 = 1; l1 < l; ++l1) {
			for (int l2 = 1; l1 + l2 < l; ++l2) {
				auto p = num.data();
				if (isAdditiveRemaining(string_view(p, l1),
							string_view(p + l1, l2),
							string_view(p + l1 + l2, l - l1 - l2)))
					return true;
			}
		}
		return false;
	}
};

int main()
{
	const pair<string, bool> test_data[] = {
		{"1", false},
		{"11", false},
		{"101", true},
		{"112", true},
		{"113", false},
		{"123", true},
		{"1234", false},
		{"1203", false},
		{"1023", false},
		{"1235", true},
		{"12356", false},
		{"12315", true},
		{"112358", true},
		{"199100199", true},
	};
	bool success = true;
	Solution solution;
	for (const auto& [num, expected] : test_data) {
		bool result = solution.isAdditiveNumber(num);
		cout << num << (result ? " is " : " is not ") << "additive" << endl;
		if (result != expected) {
			cout << "  ERROR: wrong!" << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
