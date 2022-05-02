#include <cassert>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Solution {
private:
	string numberLessThanTwentyToWord(int num) {
		assert(num >= 0);
		assert(num < 20);
		static const char *numToWord[] = {
			[0]  = "Zero",
			[1]  = "One",
			[2]  = "Two",
			[3]  = "Three",
			[4]  = "Four",
			[5]  = "Five",
			[6]  = "Six",
			[7]  = "Seven",
			[8]  = "Eight",
			[9]  = "Nine",
			[10] = "Ten",
			[11] = "Eleven",
			[12] = "Twelve",
			[13] = "Thirteen",
			[14] = "Fourteen",
			[15] = "Fifteen",
			[16] = "Sixteen",
			[17] = "Seventeen",
			[18] = "Eighteen",
			[19] = "Nineteen",
		};
		return numToWord[num];
	}
	string numberLessThanHundredToWords(int num) {
		assert(num >= 0);
		assert(num < 100);
		if (num < 20)
			return numberLessThanTwentyToWord(num);
		static const char *tensToWord[] = {
			[0] = nullptr,
			[1] = nullptr,
			[2] = "Twenty",
			[3] = "Thirty",
			[4] = "Forty",
			[5] = "Fifty",
			[6] = "Sixty",
			[7] = "Seventy",
			[8] = "Eighty",
			[9] = "Ninety",
		};
		string result = tensToWord[num / 10];
		num %= 10;
		if (num != 0)
			result += ' ' + numberLessThanTwentyToWord(num);
		return result;
	}
	string numberLessThanThousandToWords(int num) {
		assert(num >= 0);
		assert(num < 1000);
		if (num < 100)
			return numberLessThanHundredToWords(num);
		string result = numberLessThanTwentyToWord(num / 100) + " Hundred";
		num %= 100;
		if (num != 0)
			result += ' ' + numberLessThanHundredToWords(num);
		return result;
	}
public:
	string numberToWords(int num) {
		assert(num >= 0);
		string result;
		int milliards = num / 1000000000;
		if (milliards != 0)
			result += numberLessThanThousandToWords(milliards) + " Billion";
		num %= 1000000000;
		int millions = num / 1000000;
		if (millions != 0) {
			if (!result.empty())
				result += ' ';
			result += numberLessThanThousandToWords(millions) + " Million";
		}
		num %= 1000000;
		int thousands = num / 1000;
		if (thousands != 0) {
			if (!result.empty())
				result += ' ';
			result += numberLessThanThousandToWords(thousands) + " Thousand";
		}
		num %= 1000;
		if (num != 0 || result.empty()) {
			if (!result.empty())
				result += ' ';
			result += numberLessThanThousandToWords(num);
		}
		return result;
	}
};

int main()
{
	pair<int, string> test_data[] = {
		{0, "Zero"},
		{1, "One"},
		{2, "Two"},
		{10, "Ten"},
		{15, "Fifteen"},
		{42, "Forty Two"},
		{123, "One Hundred Twenty Three"},
		{12345, "Twelve Thousand Three Hundred Forty Five"},
		{1234567, "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"},
	};
	bool success = true;
	Solution solution;
	for (const auto& [num, expected] : test_data) {
		string result = solution.numberToWords(num);
		cout << num << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
