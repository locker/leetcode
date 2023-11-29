#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>

using namespace std;

namespace {

class Solution {
public:
	string addStrings(string num1, string num2) {
		reverse(num1.begin(), num1.end());
		reverse(num2.begin(), num2.end());
		const int size = max(num1.size(), num2.size());
		num1.resize(size, '0');
		num2.resize(size, '0');
		bool carry = false;
		for (int i = 0; i < size; ++i) {
			int d1 = num1[i] - '0';
			int d2 = num2[i] - '0';
			d1 += d2;
			if (carry)
				++d1;
			if (d1 >= 10) {
				d1 -= 10;
				carry = true;
			} else {
				carry = false;
			}
			num1[i] = d1 + '0';
		}
		if (carry)
			num1.push_back('1');
		reverse(num1.begin(), num1.end());
		return num1;
	}
};

} // namespace

int main()
{
	const tuple<string, string, string> test_data[] = {
		{"0", "0", "0"},
		{"0", "123", "123"},
		{"123", "0", "123"},
		{"11", "123", "134"},
		{"456", "77", "533"},
	};
	bool success = true;
	Solution solution;
	for (const auto& [num1, num2, expected] : test_data) {
		string result = solution.addStrings(num1, num2);
		cout << num1 << " + " << num2 << " = " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
