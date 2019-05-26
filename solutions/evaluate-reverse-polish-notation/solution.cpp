#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	int evalRPN(const vector<string>& tokens) {
		stack<int> operands;
		enum Operator { PLUS, MINUS, MUL, DIV };
		for (const auto& token: tokens) {
			Operator op;
			if (token == "+") {
				op = PLUS;
			} else if (token == "-") {
				op = MINUS;
			} else if (token == "*") {
				op = MUL;
			} else if (token == "/") {
				op = DIV;
			} else {
				operands.push(stoi(token));
				continue;
			}
			int val2 = operands.top();
			operands.pop();
			int val1 = operands.top();
			operands.pop();
			int result;
			switch (op) {
			case PLUS:
				result = val1 + val2;
				break;
			case MINUS:
				result = val1 - val2;
				break;
			case MUL:
				result = val1 * val2;
				break;
			case DIV:
				result = val1 / val2;
				break;
			}
			operands.push(result);
		}
		return operands.top();
	}
};

int main()
{
	vector<string> input[] = {
		{"1", "1", "+"}, // 2
		{"1", "1", "-"}, // 0
		{"2", "2", "*"}, // 4
		{"5", "2", "/"}, // 2
		{"2", "1", "+", "3", "*"}, // 9
		{"4", "13", "5", "/", "+"}, // 6
		{"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"}, // 22
	};
	Solution solution;
	for (const auto& tokens: input)
		cout << tokens << " => " << solution.evalRPN(tokens) << endl;
	return 0;
}
