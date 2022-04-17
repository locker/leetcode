#include <iostream>
#include <stack>

using namespace std;

class MyQueue {
private:
	stack<int> push_stack, pop_stack;

	void preparePop() {
		if (pop_stack.empty()) {
			while (!push_stack.empty()) {
				pop_stack.push(push_stack.top());
				push_stack.pop();
			}
		}
	}
public:
	MyQueue() {}

	void push(int x) {
		push_stack.push(x);
	}

	int pop() {
		preparePop();
		int x = pop_stack.top();
		pop_stack.pop();
		return x;
	}

	int peek() {
		preparePop();
		return pop_stack.top();
	}

	bool empty() {
		return push_stack.empty() && pop_stack.empty();
	}
};

bool success = true;

MyQueue testCreate()
{
	cout << "MyQueue()" << endl;
	return MyQueue();
}

void testPush(MyQueue& q, int x)
{
	cout << "push(" << x << ")" << endl;
	q.push(x);
}

void testPop(MyQueue& q, int expected)
{
	int x = q.pop();
	cout << "pop() = " << x << endl;
	if (x != expected) {
		cout << "  ERROR: expected " << expected << endl;
		success = false;
	}
}

void testPeek(MyQueue& q, int expected)
{
	int x = q.peek();
	cout << "peek() = " << x << endl;
	if (x != expected) {
		cout << "  ERROR: expected " << expected << endl;
		success = false;
	}
}

void testEmpty(MyQueue& q, bool expected)
{
	bool empty = q.empty();
	cout << "peek() = " << (empty ? "true" : "false") << endl;
	if (empty != expected) {
		cout << "  ERROR: expected " <<
			(expected ? "true" : "false") << endl;
		success = false;
	}
}

int main()
{
	{
		MyQueue q = testCreate();
		testEmpty(q, true);
		testPush(q, 1);
		testEmpty(q, false);
		testPeek(q, 1);
		testEmpty(q, false);
		testPop(q, 1);
		testEmpty(q, true);
	}
	{
		MyQueue q = testCreate();
		testPush(q, 1);
		testPush(q, 2);
		testPeek(q, 1);
		testPop(q, 1);
		testEmpty(q, false);
		testPop(q, 2);
		testEmpty(q, true);
	}
	return success ? 0 : 1;
}
