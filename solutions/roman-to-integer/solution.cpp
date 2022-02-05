#include <cassert>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
	int romanToInt(const string& s) {
		int num = 0;
		for (auto it = s.begin(); it != s.end(); ++it) {
			switch (*it) {
			case 'I':
				num += 1;
				break;
			case 'V':
			case 'X':
				num += *it == 'V' ? 5 : 10;
				if (it != s.begin() && *(it - 1) == 'I')
					num -= 2;
				break;
			case 'L':
			case 'C':
				num += *it == 'L' ? 50 : 100;
				if (it != s.begin() && *(it - 1) == 'X')
					num -= 20;
				break;
			case 'D':
			case 'M':
				num += *it == 'D' ? 500 : 1000;
				if (it != s.begin() && *(it - 1) == 'C')
					num -= 200;
				break;
			default:
				assert(false);
			}
		}
		return num;
	}
};

int main()
{
	pair<string, int> test_data[] = {
		{"III", 3},
		{"LVIII", 58},
		{"MCMXCIV", 1994},
	};
	bool success = true;
	Solution solution;
	for (const auto& [roman, num] : test_data) {
		auto result = solution.romanToInt(roman);
		cout << roman << " -> " << result << endl;
		if (result != num) {
			cout << "  ERROR: expected " << num << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
