#include <iostream>
#include <string>

using namespace std;

class Solution {
	bool isSpace(char c) { return c == ' '; }
	bool isSign(char c) { return c == '+' || c == '-'; }
	bool isDot(char c) { return c == '.'; }
	bool isExp(char c) { return c == 'e' || c == 'E'; }
	bool isDigit(char c) { return c >= '0' && c <= '9'; }
public:
	bool isNumber(const string& s) {
		enum {
			INITIAL,
			MANTISSA_SIGN,
			MANTISSA_INT,
			MANTISSA_FRAC,
			EXPONENT_SYMBOL,
			EXPONENT_SIGN,
			EXPONENT_VALUE,
			FINAL,
		} state = INITIAL;

		bool has_mantissa = false;

		for (int i = 0; i < static_cast<int>(s.length()); ++i) {
			char c = s[i];
			switch (state) {
			case INITIAL:
				if (isSign(c)) {
					state = MANTISSA_SIGN;
				} else if (isDigit(c)) {
					has_mantissa = true;
					state = MANTISSA_INT;
				} else if (isDot(c)) {
					state = MANTISSA_FRAC;
				} else if (!isSpace(c)) {
					return false;
				}
				break;
			case MANTISSA_SIGN:
				if (isDigit(c)) {
					has_mantissa = true;
					state = MANTISSA_INT;
				} else if (isDot(c)) {
					state = MANTISSA_FRAC;
				} else {
					return false;
				}
				break;
			case MANTISSA_INT:
				if (isDot(c))
					state = MANTISSA_FRAC;
				else if (isExp(c) && has_mantissa)
					state = EXPONENT_SYMBOL;
				else if (isSpace(c) && has_mantissa)
					state = FINAL;
				else if (isDigit(c))
					has_mantissa = true;
				else
					return false;
				break;
			case MANTISSA_FRAC:
				if (isExp(c) && has_mantissa)
					state = EXPONENT_SYMBOL;
				else if (isSpace(c) && has_mantissa)
					state = FINAL;
				else if (isDigit(c))
					has_mantissa = true;
				else
					return false;
				break;
			case EXPONENT_SYMBOL:
				if (isSign(c))
					state = EXPONENT_SIGN;
				else if (isDigit(c))
					state = EXPONENT_VALUE;
				else
					return false;
				break;
			case EXPONENT_SIGN:
				if (isDigit(c))
					state = EXPONENT_VALUE;
				else
					return false;
				break;
			case EXPONENT_VALUE:
				if (isSpace(c))
					state = FINAL;
				else if (!isDigit(c))
					return false;
				break;
			case FINAL:
				if (!isSpace(c))
					return false;
				break;
			}
		}
		if (has_mantissa && (state == MANTISSA_INT || state == MANTISSA_FRAC))
			return true;
		if (state == EXPONENT_VALUE)
			return true;

		return state == FINAL;
	}
};

int main()
{
	auto solution = Solution();
	const char* input[] = {
		".", // false
		". ", // false
		".e1", // false
		"0", // true
		" 0.1 ", // true
		"abc", // false
		"1 a", // false
		"2e10", // true
		" -90e3   ", // true
		" 1e", // false
		"e3", // false
		" 6e-1", // true
		" 99e2.5 ", // false
		"53.5e93", // true
		" --6 ", // false
		"-+3", // false
		"95a54e53", // false
	};
	for (auto s: input)
		cout << "\"" << s << "\" => " <<
			(solution.isNumber(s) ? "true" : "false") << endl;
	return 0;
}
