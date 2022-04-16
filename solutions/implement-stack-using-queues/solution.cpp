#include <iostream>
#include <queue>

using namespace std;

class MyStack {
private:
	queue<int> q;
public:
	MyStack() {}

	void push(int x) {
		q.push(x);
		for (int i = 0; i < static_cast<int>(q.size() - 1); ++i) {
			q.push(q.front());
			q.pop();
		}
	}

	int pop() {
		int x = q.front();
		q.pop();
		return x;
	}

	int top() {
		return q.front();
	}

	bool empty() {
		return q.empty();
	}
};

bool success = true;

MyStack testCreate() {
	cout << "MyStack()" << endl;
	return MyStack();
}

void testPush(MyStack& s, int x) {
	cout << "push(" << x << ")" << endl;
	s.push(x);
}

void testPop(MyStack& s, int expected) {
	int x = s.pop();
	cout << "pop() = " << x << endl;
	if (x != expected) {
		cout << "  ERROR: expected " << expected << endl;
		success = false;
	}
}

void testTop(MyStack& s, int expected) {
	int x = s.top();
	cout << "top() = " << x << endl;
	if (x != expected) {
		cout << "  ERROR: expected " << expected << endl;
		success = false;
	}
}

void testEmpty(MyStack& s, bool expected) {
	bool empty = s.empty();
	cout << "empty() = " << (empty ? "true" : "false") << endl;
	if (empty != expected) {
		cout << "  ERROR: expected " <<
			(expected ? "true" : "false") << endl;
		success = false;
	}
}

int main()
{
	{
		auto s = testCreate();
		testEmpty(s, true);
		testPush(s, 1);
		testEmpty(s, false);
		testTop(s, 1);
		testEmpty(s, false);
		testPop(s, 1);
		testEmpty(s, true);
	}
	{
		auto s = testCreate();
		testPush(s, 1);
		testPush(s, 2);
		testPop(s, 2);
		testPop(s, 1);
		testEmpty(s, true);
	}
	return success ? 0 : 1;
}
