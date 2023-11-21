#include <charconv>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace {

class NestedInteger {
private:
	bool is_integer_;
	int value_;
	vector<NestedInteger> children_;
public:
	// Constructor initializes an empty nested list.
	NestedInteger() : is_integer_(false), value_(0) {}

	// Constructor initializes a single integer.
	NestedInteger(int value) : is_integer_(true), value_(value) {}

	// Return true if this NestedInteger holds a single integer, rather than a nested list.
	bool isInteger() const { return is_integer_; }

	// Return the single integer that this NestedInteger holds, if it holds a single integer
	// The result is undefined if this NestedInteger holds a nested list
	int getInteger() const { return value_; }

	// Set this NestedInteger to hold a single integer.
	void setInteger(int value) {
		is_integer_ = true;
		value_ = value;
		children_.clear();
	}

	// Set this NestedInteger to hold a nested list and adds a nested integer to it.
	void add(const NestedInteger &ni) {
		is_integer_ = false;
		value_ = 0;
		children_.push_back(ni);
	}

	// Return the nested list that this NestedInteger holds, if it holds a nested list
	// The result is undefined if this NestedInteger holds a single integer
	const vector<NestedInteger> &getList() const {
		return children_;
	}

	string toString() const {
		if (is_integer_)
			return to_string(value_);
		string ret;
		ret += '[';
		bool first = true;
		for (const auto& ni : children_) {
			if (!first)
				ret += ',';
			ret += ni.toString();
			first = false;
		}
		ret += ']';
		return ret;
	};
};

class Solution {
private:
	NestedInteger helper(const char **ptr) {
		if (**ptr != '[') {
			int value;
			auto res = from_chars(*ptr, nullptr, value);
			*ptr = res.ptr;
			return NestedInteger(value);
		}
		NestedInteger ni;
		while (true) {
			++*ptr;
			if (**ptr == ']')
				break;
			ni.add(helper(ptr));
			if (**ptr == ']')
				break;
		}
		++*ptr;
		return ni;
	}
public:
	NestedInteger deserialize(const string& s) {
		const char *ptr = s.data();
		return helper(&ptr);
	}
};

} // namespace

int main()
{
	string test_data[] = {
		"324",
		"-324",
		"[]",
		"[123]",
		"[-123]",
		"[123,456]",
		"[123,-456]",
		"[123,[456,[789]]]",
		"[123,456,[788,799,833],[[]],10,[]]",
	};
	bool success = true;
	Solution solution;
	for (const auto& s : test_data) {
		cout << s << endl;
		auto ni = solution.deserialize(s);
		auto s2 = ni.toString();
		if (s != s2) {
			cout << "  ERROR: got " << s2 << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
