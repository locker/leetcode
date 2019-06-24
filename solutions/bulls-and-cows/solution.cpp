#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
	string getHint(string secret, string guess) {
		int bulls = 0;
		int cows = 0;

		int digit_count[10] = {0, };
		for (char c: secret) {
			int d = c - '0';
			++digit_count[d];
		}

		for (int i = 0; i < static_cast<int>(secret.length()); ++i) {
			int guess_digit = guess[i] - '0';
			int secret_digit = secret[i] - '0';
			if (guess_digit == secret_digit) {
				if (digit_count[guess_digit] > 0)
					--digit_count[guess_digit];
				else
					--cows;
				++bulls;
			} else if (digit_count[guess_digit] > 0) {
				--digit_count[guess_digit];
				++cows;
			}
		}

		ostringstream out;
		out << bulls << "A" << cows << "B";
		return out.str();
	}
};

int main()
{
	pair<string, string> input[] = {
		{"1", "0"}, // 0A0B
		{"1", "1"}, // 1A0B
		{"11", "25"}, // 0A0B
		{"21", "11"}, // 1A0B
		{"21", "12"}, // 0A2B
		{"11", "11"}, // 2A0B
		{"1807", "7810"}, // 1A3B
		{"1123", "0111"}, // 1A1B
	};
	Solution solution;
	for (const auto& p: input) {
		const auto& secret = p.first;
		const auto& guess = p.second;
		string hint = solution.getHint(secret, guess);
		cout << "Input: secret = " << secret <<
			", guess = " << guess << endl <<
			"Output: " << hint << endl;
	}
	return 0;
}
