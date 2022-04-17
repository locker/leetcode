#include <cassert>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>
#include <utility>

using namespace std;

class Solution {
private:
	enum Type { PLUS, MINUS, MULT, DIV, VALUE, END };

	struct Token {
		Type type;
		int value;
		int prio;

		Token(Type t, int v) : type(t), value(v) {
			switch (t) {
			case PLUS:
			case MINUS:
				prio = 1;
				break;
			case MULT:
			case DIV:
				prio = 2;
				break;
			default:
				prio = 0;
				break;
			}
		}

		Token(Type t) : Token(t, 0) {}
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
		case '*': ++*pos; return Token(MULT);
		case '/': ++*pos; return Token(DIV);
		default:
			  char *end;
			  int value = strtol(s.c_str() + *pos, &end, 10);
			  assert(end - s.c_str() > *pos);
			  *pos = end - s.c_str();
			  return Token(VALUE, value);
		}
	}
public:
	int calculate(const string& s) {
		stack<Token> tokens;
		int pos = 0;
		Token t = nextToken(s, &pos);
		while (true) {
			if (t.type == VALUE) {
				tokens.push(t);
				t = nextToken(s, &pos);
				continue;
			}
			if (tokens.size() == 1) {
				if (t.type == END)
					break;
				tokens.push(t);
				t = nextToken(s, &pos);
				continue;
			}
			assert(tokens.size() >= 3);
			Token right = tokens.top();
			assert(right.type == VALUE);
			tokens.pop();
			Token op = tokens.top();
			if (op.prio < t.prio) {
				tokens.push(right);
				tokens.push(t);
				t = nextToken(s, &pos);
				continue;
			}
			tokens.pop();
			Token left = tokens.top();
			assert(left.type == VALUE);
			tokens.pop();
			switch (op.type) {
			case PLUS:
				tokens.emplace(VALUE, left.value + right.value);
				break;
			case MINUS:
				tokens.emplace(VALUE, left.value - right.value);
				break;
			case MULT:
				tokens.emplace(VALUE, left.value * right.value);
				break;
			case DIV:
				tokens.emplace(VALUE, left.value / right.value);
				break;
			default:
				assert(false);
				break;
			}
		}
		assert(tokens.size() == 1);
		assert(tokens.top().type == VALUE);
		return tokens.top().value;
	}
};

int main()
{
	pair<string, int> test_data[] = {
		{"0", 0},
		{" 0 ", 0},
		{"1+1", 2},
		{" 2 + 3 ", 5},
		{"5 - 1 ", 4},
		{"5 - 7 ", -2},
		{"2 + 3 - 4", 1},
		{" 2 * 2", 4},
		{" 2 / 2", 1},
		{" 2 / 5", 0},
		{"5/ 2" , 2},
		{"5 * 2 / 5", 2},
		{"5 + 5 * 2", 15},
		{"5 - 5 / 2", 3},
		{" 1 + 2 * 2 / 4 - 2 / 2 * 3", -1},
	};
	bool success = true;
	Solution solution;
	for (const auto& [s, expected] : test_data) {
		int result = solution.calculate(s);
		cout << s << " = " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
