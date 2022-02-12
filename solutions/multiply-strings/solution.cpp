#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <tuple>

using namespace std;

class Solution {
private:
	int charToDigit(char c) {
		assert(c >= '0' && c <= '9');
		return c - '0';
	}
	char digitToChar(int d) {
		assert(d >= 0 && d <= 9);
		return d + '0';
	}
	string add(const string& num1, const string& num2) {
		const int l1 = static_cast<int>(num1.length());
		const int l2 = static_cast<int>(num2.length());
		assert(l1 > 0);
		assert(l2 > 0);
		string result;
		int carry = 0;
		for (int i = 0; i < max(l1, l2); ++i) {
			int d1 = i < l1 ? charToDigit(num1[l1 - i - 1]) : 0;
			int d2 = i < l2 ? charToDigit(num2[l2 - i - 1]) : 0;
			int r = d1 + d2 + carry;
			result.push_back(digitToChar(r % 10));
			carry = r / 10;
		}
		if (carry > 0)
			result.push_back(digitToChar(carry));
		reverse(result.begin(), result.end());
		return result;
	}
	string multiplyByDigit(const string &num, int digit) {
		const int l = static_cast<int>(num.length());
		assert(l > 0);
		assert(digit >= 0 && digit <= 9);
		if (digit == 0)
			return "0";
		if (digit == 1)
			return num;
		string result;
		int carry = 0;
		for (int i = 0; i < l; ++i) {
			int d = charToDigit(num[l - i - 1]);
			int r = d * digit + carry;
			result.push_back(digitToChar(r % 10));
			carry = r / 10;
		}
		if (carry > 0)
			result.push_back(digitToChar(carry));
		reverse(result.begin(), result.end());
		return result;
	}
public:
	string multiply(const string& num1, const string& num2) {
		const int l1 = static_cast<int>(num1.length());
		assert(l1 > 0);
		string result = "0";
		for (int i = 0; i < l1; ++i) {
			int d = charToDigit(num1[l1 - i - 1]);
			string v = multiplyByDigit(num2, d);
			if (v != "0") {
				v.append(i, '0');
				result = add(result, v);
			}
		}
		return result;
	}
};

int main()
{
	tuple<string, string, string> test_data[] = {
		{"2", "3", "6"},
		{"0", "123", "0"},
		{"123", "0", "0"},
		{"123", "456", "56088"},
	};
	bool success = true;
	Solution solution;
	for (const auto &[num1, num2, expected] : test_data) {
		auto result = solution.multiply(num1, num2);
		cout << num1 << " * " << num2 << " = " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
