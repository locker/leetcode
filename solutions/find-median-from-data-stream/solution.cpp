#include <cassert>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class MedianFinder {
private:
	priority_queue<int, vector<int>, less<int>> lo;
	priority_queue<int, vector<int>, greater<int>> hi;
public:
	void addNum(int num) {
		if (lo.empty() || lo.top() >= num) {
			lo.push(num);
			if (lo.size() > hi.size() + 1) {
				hi.push(lo.top());
				lo.pop();
			}
		} else {
			hi.push(num);
			if (hi.size() > lo.size() + 1) {
				lo.push(hi.top());
				hi.pop();
			}
		}
	}

	double findMedian() {
		assert(!lo.empty() > 0 || !hi.empty());
		assert(abs(static_cast<int>(lo.size() - hi.size())) <= 1);
		if (lo.size() > hi.size())
			return lo.top();
		if (lo.size() < hi.size())
			return hi.top();
		return (lo.top() + hi.top()) / 2.0;
	}
};

bool success = true;

MedianFinder testCreate() {
	cout << "MedianFinder()" << endl;
	return MedianFinder();
}

void testAdd(MedianFinder& m, int num) {
	cout << "addNum(" << num << ")" << endl;
	m.addNum(num);
}

void testFindMedian(MedianFinder& m, double expected) {
	double result = m.findMedian();
	cout << "findMedian() -> " << result << endl;
	if (fabs(result - expected) > 1e-5) {
		cout << "  ERROR: expected " << expected << endl;
		success = false;
	}
}

int main()
{
	{
		auto m = testCreate();
		testAdd(m, 1);
		testFindMedian(m, 1);
		testAdd(m, 1);
		testFindMedian(m, 1);
		testAdd(m, -1);
		testFindMedian(m, 1);
		testAdd(m, -1);
		testFindMedian(m, 0);
	}
	{
		auto m = testCreate();
		testAdd(m, 10);
		testAdd(m, 20);
		testFindMedian(m, 15);
		testAdd(m, 100);
		testFindMedian(m, 20);
		testAdd(m, 200);
		testFindMedian(m, 60);
		testAdd(m, 1);
		testAdd(m, 2);
		testFindMedian(m, 15);
	}
	return success ? 0 : 1;
}
