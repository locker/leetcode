#include <iostream>
#include <limits>
#include <string>

using namespace std;

class Solution {
public:
	int myAtoi(const string& str) {
		const int min = numeric_limits<int>::min();
		const int max = numeric_limits<int>::max();

		int i;
		for (i = 0; i < static_cast<int>(str.length()); i++) {
			if (str[i] != ' ')
				break;
		}

		bool negative = false;
		if (str[i] == '-') {
			negative = true;
			i++;
		} else if (str[i] == '+') {
			i++;
		}

		int result = 0;
		while (i < static_cast<int>(str.length()) &&
				str[i] >= '0' && str[i] <= '9') {
			int digit = str[i] - '0';

			if (negative && result < min / 10)
				return min;
			if (!negative && result > max / 10)
				return max;
			result *= 10;

			if (negative && result < min + digit)
				return min;
			if (!negative && result > max - digit)
				return max;
			if (negative)
				result -= digit;
			else
				result += digit;
			i++;
		}
		return result;
	}
};

int main()
{
	auto solution = Solution();
	const char* input[] = {
		"42",
		"+42",
		"   -42",
		"4193 with words",
		"words and 987",
		"-2147483648",
		"2147483647",
		"91283472332",
		"-91283472332",
	};
	for (auto s: input)
		cout << "\"" << s << "\" -> " << solution.myAtoi(s) << endl;
	return 0;
}
