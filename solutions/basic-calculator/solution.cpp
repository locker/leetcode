#include <cassert>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>
#include <utility>

using namespace std;

class Solution {
private:
	enum TokenType {
		PLUS,
		MINUS,
		OPEN_PAREN,
		CLOSE_PAREN,
		VALUE,
		END,
	};

	struct Token {
		TokenType type;
		int value;
		Token(TokenType t, int v) : type(t), value(v) {}
		Token(TokenType t) : type(t), value(0) {}
	};

	Token nextToken(const string& s, int *pos) {
		const int len = s.length();
		while (*pos < len && s[*pos] == ' ')
			++*pos;
		if (*pos == len)
			return Token(END);
		switch (s[*pos]) {
		case '+': ++*pos; return Token(PLUS);
		case '-': ++*pos; return Token(MINUS);
		case '(': ++*pos; return Token(OPEN_PAREN);
		case ')': ++*pos; return Token(CLOSE_PAREN);
		default:
			char *end;
			long val = strtol(s.c_str() + *pos, &end, 10);
			assert(end > s.c_str());
			*pos = end - s.c_str();
			return Token(VALUE, val);
		};
	}
public:
	int calculate(const string& s) {
		int pos = 0;
		stack<Token> tokens;
		Token t = nextToken(s, &pos);
		while (t.type != END) {
			switch (t.type) {
			case PLUS:
			case MINUS:
			case OPEN_PAREN:
				tokens.push(t);
				t = nextToken(s, &pos);
				break;
			case CLOSE_PAREN:
				assert(tokens.size() >= 2);
				t = tokens.top();
				tokens.pop();
				assert(t.type == VALUE);
				assert(tokens.top().type == OPEN_PAREN);
				tokens.pop();
				break;
			case VALUE: {
				if (tokens.empty() ||
				    tokens.top().type == OPEN_PAREN) {
					tokens.push(t);
					t = nextToken(s, &pos);
					break;
				}
				Token op = tokens.top();
				tokens.pop();
				assert(op.type == PLUS || op.type == MINUS);
				if (tokens.empty() ||
				    tokens.top().type != VALUE) {
					if (op.type == MINUS)
						t.value = -t.value;
					break;
				}
				Token other = tokens.top();
				tokens.pop();
				if (op.type == MINUS) {
					t.value = other.value - t.value;
				} else {
					t.value = other.value + t.value;
				}
				break;
			}
			default:
				assert(false);
				break;
			};
		}
		assert(tokens.size() == 1);
		assert(tokens.top().type == VALUE);
		return tokens.top().value;
	}
};

int main()
{
	const pair<string, int> test_data[] = {
		{"1", 1},
		{"+5", 5},
		{"-5", -5},
		{"  +  10  ", 10},
		{"  -  10  ", -10},
		{"1 + 1", 2},
		{" -2 - -1", -1},
		{" 2-1 + 2 ", 3},
		{"(123)", 123},
		{"( - 123 )", -123},
		{" - ( - 123 )", 123},
		{"(1+(4+5+2)-3)+(6+8)", 23},
	};
	bool success = true;
	Solution solution;
	for (const auto& [expr, expected] : test_data) {
		int result = solution.calculate(expr);
		cout << expr << " = " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
