#include <iostream>
#include <optional>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T> v)
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

class Iterator {
private:
	vector<int>::const_iterator cur, end;
public:
	Iterator(const vector<int>& nums) : cur(nums.begin()), end(nums.end()) {}

	// Returns the next element in the iteration.
	int next() { return *cur++; }

	// Returns true if the iteration has more elements.
	bool hasNext() const { return cur != end; }
};

class PeekingIterator : public Iterator {
private:
	optional<int> peeked;
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
	}
	
	// Returns the next element in the iteration without advancing the
	// iterator.
	int peek() {
		if (!peeked.has_value())
			peeked = Iterator::next();
		return peeked.value();
	}

	// Returns the next element in the iteration.
	int next() {
		if (peeked.has_value()) {
			int value = peeked.value();
			peeked.reset();
			return value;
		}
		return Iterator::next();
	}

	// Returns true if the iteration has more elements.
	bool hasNext() const {
		return peeked.has_value() || Iterator::hasNext();
	}
};

bool success = true;

PeekingIterator testCreate(const vector<int>& nums) {
	cout << "create: " << nums << endl;
	return PeekingIterator(nums);
}

void testNext(PeekingIterator& it, int expected) {
	int result = it.next();
	cout << "next: " << result << endl;
	if (result != expected) {
		cout << "  ERROR: expected " << expected << endl;
		success = false;
	}
}

void testHasNext(PeekingIterator& it, bool expected) {
	bool result = it.hasNext();
	cout << "hasNext: " << (result ? "true" : "false") << endl;
	if (result != expected) {
		cout << "  ERROR: expected " <<
			(expected ? "true" : "false") << endl;
		success = false;
	}
}

void testPeek(PeekingIterator& it, int expected) {
	int result = it.peek();
	cout << "next: " << result << endl;
	if (result != expected) {
		cout << "  ERROR: expected " << expected << endl;
		success = false;
	}
}

int main()
{
	{
		vector<int> nums = {};
		auto it = testCreate(nums);
		testHasNext(it, false);
	}
	{
		vector<int> nums = {1};
		auto it = testCreate(nums);
		testHasNext(it, true);
		testPeek(it, 1);
		testHasNext(it, true);
		testNext(it, 1);
		testHasNext(it, false);
	}
	{
		vector<int> nums = {1, 2, 3};
		auto it = testCreate(nums);
		testNext(it, 1);
		testPeek(it, 2);
		testNext(it, 2);
		testNext(it, 3);
		testHasNext(it, false);
	}
	return success ? 0 : 1;
}
