#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <set>
#include <tuple>
#include <variant>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	bool first = true;
	for (const auto& x : v) {
		if (!first)
			out << ',';
		out << x;
		first = false;
	}
	out << ']';
	return out;
}

class Solution {
private:
	enum Operator {
		PLUS,
		MINUS,
		MULT,
	};

	struct Number {
		long long value;
		// Result of the whole expression up to and including this number.
		long long result;
		// Result of the last multiplication that includes this number.
		long long intermediate_result;
		// Position in the input string.
		int pos;
		// Number of digits.
		int len;

		Number(const string& s, int p) {
			assert(p < static_cast<int>(s.size()));
			pos = p;
			len = 1;
			result = intermediate_result = value = s[p] - '0';
		}
	};

	typedef variant<Operator, Number> Token;
	typedef vector<Token> Expression;

	void computeLastResult(Expression& expr) {
		Number& last = get<Number>(expr.back());
		if (expr.size() == 1) {
			last.result = last.intermediate_result = last.value;
			return;
		}
		assert(expr.size() > 2);
		const Operator& op = get<Operator>(*(expr.rbegin() + 1));
		const Number& prev = get<Number>(*(expr.rbegin() + 2));
		last.result = prev.result;
		switch (op) {
		case PLUS:
			last.intermediate_result = last.value;
			break;
		case MINUS:
			last.intermediate_result = -last.value;
			break;
		case MULT:
			last.result -= prev.intermediate_result;
			last.intermediate_result =
				prev.intermediate_result * last.value;
			break;
		}
		last.result += last.intermediate_result;
	}

	void fillExpression(const string& s, Expression& expr) {
		const int size = s.size();
		assert(size > 0);
		if (expr.empty())
			expr.push_back(Number(s, 0));
		if (holds_alternative<Operator>(expr.back())) {
			assert(expr.size() > 1);
			const Number& prev = get<Number>(*(expr.rbegin() + 1));
			expr.push_back(Number(s, prev.pos + prev.len));
			computeLastResult(expr);
		}
		while (true) {
			const Number& prev = get<Number>(expr.back());
			int pos = prev.pos + prev.len;
			if (pos >= size)
				break;
			expr.push_back(PLUS);
			expr.push_back(Number(s, pos));
			computeLastResult(expr);
		}
	}

	bool nextNumber(const string& s, Expression& expr) {
		const int size = s.size();
		assert(!expr.empty());
		Number& last = get<Number>(expr.back());
		assert(last.len >= 1);
		assert(last.pos + last.len <= size);
		if (last.pos + last.len < size && last.value != 0) {
			last.value *= 10;
			last.value += s[last.pos + last.len] - '0';
			++last.len;
			computeLastResult(expr);
			return true;
		}
		return false;
	}

	bool nextExpression(const string& s, Expression& expr) {
		const int size = s.size();
		assert(size > 0);
		while (true) {
			assert(!expr.empty());
			if (nextNumber(s, expr))
				break;
			if (expr.size() == 1)
				return false;
			assert(expr.size() > 2);
			expr.pop_back();
			Operator& op = get<Operator>(expr.back());
			switch (op) {
			case PLUS:
				op = MINUS;
				break;
			case MINUS:
				op = MULT;
				break;
			case MULT:
				expr.pop_back();
				continue;
			}
			break;
		}
		fillExpression(s, expr);
		return true;
	}

	string expressionToString(const string& s, const Expression& expr) {
		string ret;
		for (const Token& t : expr) {
			if (holds_alternative<Number>(t)) {
				const Number& num = get<Number>(t);
				ret.append(s.begin() + num.pos,
					   s.begin() + num.pos + num.len);
			} else {
				const Operator& op = get<Operator>(t);
				switch (op) {
				case PLUS:
					ret.push_back('+');
					break;
				case MINUS:
					ret.push_back('-');
					break;
				case MULT:
					ret.push_back('*');
					break;
				}
			}
		}
		return ret;
	}

public:
	vector<string> addOperators(const string& s, const int target) {
		vector<string> ret;
		Expression expr;
		fillExpression(s, expr);
		do {
			if (get<Number>(expr.back()).result == target)
				ret.push_back(expressionToString(s, expr));
		} while (nextExpression(s, expr));
		return ret;
	}
};

int main()
{
	tuple<string, int, vector<string>> test_data[] = {
		{"0", 0, {"0"}},
		{"1", 1, {"1"}},
		{"1", 2, {}},
		{"00", 0, {"0+0", "0-0", "0*0"}},
		{"01", 0, {"0*1"}},
		{"07", 7, {"0+7"}},
		{"07", -7, {"0-7"}},
		{"105", 5, {"1*0+5", "10-5"}},
		{"007", 5, {}},
		{"007", 7, {"0+0+7", "0-0+7", "0*0+7"}},
		{"012", 3, {"0+1+2"}},
		{"012", 2, {"0+1*2", "0*1+2"}},
		{"012", -1, {"0+1-2"}},
		{"123", 6, {"1*2*3", "1+2+3"}},
		{"232", 8, {"2*3+2", "2+3*2"}},
		{"3456237490", 9191, {}},
	};
	bool success = true;
	Solution solution;
	for (const auto& [num, target, expected] : test_data) {
		vector<string> result = solution.addOperators(num, target);
		cout << "num=" << num << ", target=" << target << " -> " << result << endl;
		if (set<string>(result.begin(), result.end()) !=
		    set<string>(expected.begin(), expected.end())) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
