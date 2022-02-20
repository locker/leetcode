#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <tuple>

using namespace std;

class Solution {
public:
	string fractionToDecimal(int numerator_, int denominator_) {
		assert(denominator_ != 0);
		long long numerator = numerator_;
		long long denominator = denominator_;
		string result;
		if (numerator == 0) {
			result.push_back('0');
			return result;
		}
		bool negative = false;
		if (numerator < 0) {
			numerator = -numerator;
			negative = !negative;
		}
		if (denominator < 0) {
			denominator = -denominator;
			negative = !negative;
		}
		if (negative)
			result.push_back('-');
		result.append(to_string(numerator / denominator));
		long long remainder = numerator % denominator;
		if (remainder == 0)
			return result;
		result.push_back('.');
		// Map: remainder -> position in the result.
		// Used for detecting recurring fractions.
		unordered_map<int, int> seen;
		seen[remainder] = result.size();
		while (true) {
			remainder *= 10;
			int digit = remainder / denominator;
			assert(digit <= 9);
			result.push_back('0' + digit);
			remainder -= digit * denominator;
			assert(remainder >= 0);
			if (remainder == 0)
				break;
			auto it = seen.find(remainder);
			if (it != seen.end()) {
				int index = it->second;
				result.insert(index, 1, '(');
				result.push_back(')');
				break;
			}
			seen[remainder] = result.size();
		}
		return result;
	}
};

int main()
{
	tuple<int, int, string> test_data[] {
		{1, 2, "0.5"},
		{2, 1, "2"},
		{0, 3, "0"},
		{0, -3, "0"},
		{-3, 2, "-1.5"},
		{5, -2, "-2.5"},
		{-9, -2, "4.5"},
		{7, 6, "1.1(6)"},
		{-1, 3, "-0.(3)"},
		{10, -3, "-3.(3)"},
		{4, 333, "0.(012)"},
	};
	bool success = true;
	Solution solution;
	for (const auto& [numerator, denominator, expected] : test_data) {
		string result = solution.fractionToDecimal(numerator,
							   denominator);
		cout << numerator << " / " << denominator << " = " <<
			result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
