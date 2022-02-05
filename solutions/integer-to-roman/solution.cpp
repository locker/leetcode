#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

class Solution {
private:
	void convert_digit(ostringstream& out, int digit,
			   char c1, char c5, char c10) {
		assert(digit >= 0 && digit < 10);
		if (digit == 9) {
			out << c1 << c10;
		} else if (digit >= 5) {
			out << c5 << string(digit - 5, c1);
		} else if (digit == 4) {
			out << c1 << c5;
		} else {
			out << string(digit, c1);
		}
	}
public:
	string intToRoman(int num) {
		assert(num >= 0);
		ostringstream out;
		out << string(num / 1000, 'M');
		num %= 1000;
		convert_digit(out, num / 100, 'C', 'D', 'M');
		num %= 100;
		convert_digit(out, num / 10, 'X', 'L', 'C');
		num %= 10;
		convert_digit(out, num, 'I', 'V', 'X');
		return out.str();
	}
};

int main()
{
	pair<int, string> test_data[] = {
		{3, "III"},
		{58, "LVIII"},
		{1994, "MCMXCIV"},
	};
	bool success = true;
	Solution solution;
	for (const auto& [num, roman] : test_data) {
		auto result = solution.intToRoman(num);
		cout << num << " -> " << result << endl;
		if (result != roman) {
			cout << "  ERROR: expected " << roman << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
