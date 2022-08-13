#include <cassert>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

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

class NestedInteger {
private:
	bool is_integer = false;
	int integer_value = 0;
	vector<NestedInteger> list;
public:
	NestedInteger(string s) {
		assert(!s.empty());
		if (s.front() != '[') {
			is_integer = true;
			integer_value = atoi(s.c_str());
			return;
		}
		assert(s.back() == ']');
		string::size_type pos = 1;
		while (pos != s.length()) {
			if (s[pos] == ']' || s[pos] == ',') {
				++pos;
				continue;
			}
			string::size_type next_pos;
			if (s[pos] == '[') {
				next_pos = pos;
				int count = 0;
				do {
					assert(next_pos < s.length());
					switch (s[next_pos++]) {
					case '[': ++count; break;
					case ']': --count; break;
					default: break;
					}
				} while (count != 0);
			} else {
				next_pos = s.find(',', pos);
				if (next_pos == string::npos)
					next_pos = s.length();
				else
					++next_pos;
			}
			list.emplace_back(s.substr(pos, next_pos - pos));
			pos = next_pos;
		}
	}

	// Return true if this NestedInteger holds a single integer, rather
	// than a nested list.
	bool isInteger() const {
		return is_integer;
	}

	// Return the single integer that this NestedInteger holds, if it holds
	// a single integer. The result is undefined if this NestedInteger
	// holds a nested list.
	int getInteger() const {
		assert(is_integer);
		return integer_value;
	}

	// Return the nested list that this NestedInteger holds, if it holds a
	// nested list. The result is undefined if this NestedInteger holds a
	// single integer.
	const vector<NestedInteger> &getList() const {
		assert(!is_integer);
		return list;
	}
};

class NestedIterator {
private:
	stack<pair<reference_wrapper<const vector<NestedInteger>>,
		   vector<NestedInteger>::const_iterator>> todo;

	int next_val;
	bool has_next;

	void updateNext() {
		next_val = 0;
		has_next = false;
		while (!todo.empty()) {
			auto& [list_ref, pos] = todo.top();
			auto& list = list_ref.get();
			if (pos == list.cend()) {
				todo.pop();
				continue;
			}
			if (pos->isInteger()) {
				next_val = pos->getInteger();
				has_next = true;
				++pos;
				break;
			} else {
				auto& next_list = pos->getList();
				++pos;
				todo.emplace(next_list, next_list.cbegin());
			}
		}
	}
public:
	NestedIterator(const vector<NestedInteger> &list) {
		todo.emplace(list, list.cbegin());
		updateNext();
	}

	int next() {
		assert(has_next);
		int val = next_val;
		updateNext();
		return val;
	}

	bool hasNext() {
		return has_next;
	}
};

vector<int> test(string s) {
	NestedInteger val(s);
	assert(!val.isInteger());
	NestedIterator it(val.getList());
	vector<int> result;
	while (it.hasNext()) 
		result.push_back(it.next());
	return result;
}

int main()
{
	const pair<string, vector<int>> test_data[] = {
		{"[]", {}},
		{"[[]]", {}},
		{"[1]", {1}},
		{"[[1]]", {1}},
		{"[[1,2]]", {1, 2}},
		{"[[1],[2]]", {1, 2}},
		{"[-1,[-2]]", {-1, -2}},
		{"[1,[4,[6]]]", {1, 4, 6}},
		{"[[1,1],2,[1,1]]", {1, 1, 2, 1, 1}},
	};
	bool success = false;
	for (const auto& [input, expected] : test_data) {
		auto result = test(input);
		cout << input << " => " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
