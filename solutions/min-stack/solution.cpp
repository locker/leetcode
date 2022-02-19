#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>

using namespace std;

class MinStack {
private:
	struct Entry {
		int val;
		int min_val;
		Entry(int val_, int min_val_) : val(val_), min_val(min_val_) {}
	};
	stack<Entry> entries;
public:
	void push(int val) {
		int min_val = val;
		if (!entries.empty())
			min_val = min(min_val, entries.top().min_val);
		entries.emplace(val, min_val);
	}

	void pop() {
		assert(!entries.empty());
		entries.pop();
	}

	int top() {
		assert(!entries.empty());
		return entries.top().val;
	}

	int getMin() {
		assert(!entries.empty());
		return entries.top().min_val;
	}
};

bool success = true;

MinStack testConstruct() {
	cout << "MinStack()" << endl;
	return MinStack();
}

void testPush(MinStack& s, int val) {
	cout << "push(" << val << ")" << endl;
	s.push(val);
}

void testPop(MinStack& s) {
	cout << "pop()" << endl;
	s.pop();
}

void testTop(MinStack& s, int expected) {
	int val = s.top();
	cout << "top() = " << val << endl;
	if (val != expected) {
		cout << "  ERROR: expected " << expected << endl;
		success = false;
	}
}

void testMin(MinStack& s, int expected) {
	int val = s.getMin();
	cout << "min() = " << val << endl;
	if (val != expected) {
		cout << "  ERROR: expected " << expected << endl;
		success = false;
	}
}

int main()
{
	{
		MinStack s = testConstruct();
		testPush(s, 1);
		testTop(s, 1);
		testMin(s, 1);
		testPush(s, 2);
		testTop(s, 2);
		testMin(s, 1);
		testPop(s);
		testTop(s, 1);
		testMin(s, 1);
	}
	{
		MinStack s = testConstruct();
		testPush(s, -2);
		testPush(s, 0);
		testPush(s, -3);
		testMin(s, -3);
		testPop(s);
		testTop(s, 0);
		testMin(s, -2);
	}
	return success ? 0 : 1;
}
