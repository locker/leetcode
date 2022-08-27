#include <iostream>
#include <set>
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

class SummaryRanges {
private:
	using Interval = vector<int>;
	struct CompareInterval {
		using is_transparent = void;
		bool operator()(const Interval& a, const Interval& b) const {
			return a[0] < b[0];
		}
		bool operator()(int a, const Interval& b) const {
			return a < b[0];
		}
	};
	set<Interval, CompareInterval> intervals;
public:
	SummaryRanges() {}

	void addNum(int val) {
		auto next = intervals.upper_bound(val);
		auto prev = next;
		if (prev == intervals.begin())
			prev = intervals.end();
		else
			--prev;
		int left = val;
		int right = val;
		if (prev != intervals.end()) {
			int prev_left = (*prev)[0];
			int prev_right = (*prev)[1];
			if (prev_right >= val)
				return;
			if (prev_right + 1 == val) {
				left = prev_left;
				intervals.erase(prev);
			}
		}
		if (next != intervals.end()) {
			int next_left = (*next)[0];
			int next_right = (*next)[1];
			if (next_left - 1 == val) {
				right = next_right;
				intervals.erase(next);
			}
		}
		intervals.insert(vector<int>({left, right}));
	}

	vector<vector<int>> getIntervals() const {
		return vector<vector<int>>(intervals.begin(), intervals.end());
	}
};

bool success = true;

SummaryRanges testCreate() {
	cout << "SummaryRanges()" << endl;
	return SummaryRanges();
}

void testAddNum(SummaryRanges& sr, int val)
{
	cout << "addNum(" << val << ")" << endl;
	sr.addNum(val);
}

void testGetIntervals(const SummaryRanges& sr,
		      const vector<vector<int>> expected)
{
	auto result = sr.getIntervals();
	cout << "getIntervals() => " << result << endl;
	if (result != expected) {
		cout << "  ERROR: expected " << expected << endl;
		success = false;
	}
}

int main()
{
	{
		auto sr = testCreate();
		testAddNum(sr, 1);
		testGetIntervals(sr, {{1, 1}});
		testAddNum(sr, 3);
		testGetIntervals(sr, {{1, 1}, {3, 3}});
		testAddNum(sr, 7);
		testGetIntervals(sr, {{1, 1}, {3, 3}, {7, 7}});
		testAddNum(sr, 2);
		testGetIntervals(sr, {{1, 3}, {7, 7}});
		testAddNum(sr, 6);
		testGetIntervals(sr, {{1, 3}, {6, 7}});
		testAddNum(sr, 2);
		testGetIntervals(sr, {{1, 3}, {6, 7}});
		testAddNum(sr, 8);
		testGetIntervals(sr, {{1, 3}, {6, 8}});
		testAddNum(sr, 10);
		testGetIntervals(sr, {{1, 3}, {6, 8}, {10, 10}});
		testAddNum(sr, 9);
		testGetIntervals(sr, {{1, 3}, {6, 10}});
		testAddNum(sr, 9);
		testGetIntervals(sr, {{1, 3}, {6, 10}});
		testAddNum(sr, 4);
		testGetIntervals(sr, {{1, 4}, {6, 10}});
		testAddNum(sr, 5);
		testGetIntervals(sr, {{1, 10}});
	}
	{
		auto sr = testCreate();
		testAddNum(sr, 1);
		testGetIntervals(sr, {{1, 1}});
		testAddNum(sr, 0);
		testGetIntervals(sr, {{0, 1}});
	}
	return success ? 0 : 1;
}
