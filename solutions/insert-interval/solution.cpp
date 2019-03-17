#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

ostream& operator<<(ostream& out, const Interval& interval)
{
	return out << '[' << interval.start << ',' << interval.end << ']';
}

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
	// Find the first interval that starts at or before the given
	// position. Return intervals.end() if not found.
	decltype(auto) findBefore(vector<Interval>& intervals, int pos) {
		auto begin = intervals.begin();
		auto end = intervals.end();
		auto ret = end;
		while (begin != end) {
			auto mid = begin + (end - begin) / 2;
			if (mid->start <= pos) {
				begin = mid + 1;
				ret = mid;
			} else
				end = mid;
		}
		return ret;
	}
public:
	vector<Interval>& insert(vector<Interval>& intervals,
				 const Interval& newInterval) {
		// Last interval intersected by the new interval.
		auto last = findBefore(intervals, newInterval.end);
		if (last == intervals.end()) {
			// The new interval is to the left of
			// the first interval:
			//
			// |-- new --|
			//             |--------| ...
			//
			intervals.insert(intervals.begin(), newInterval);
			return intervals;
		}
		// First interval intersected by the new interval.
		auto first = findBefore(intervals, newInterval.start);
		if (first == intervals.end()) {
			// |-------- new --------|
			//       |first| |---| |last| ...
			//
			first = intervals.begin();
		} else if (first->end < newInterval.start) {
			//        |-------- new --------|
			// |----|     |first| |----| |last| ...
			++first;
		}
		if (first <= last) {
			// Remove all intersected intervals except
			// the first one. Update the first interval
			// with the new interval boundaries.
			first->start = min(first->start, newInterval.start);
			first->end = max(last->end, newInterval.end);
			intervals.erase(first + 1, last + 1);
		} else {
			// No intersection. Just insert the new
			// interval at the appropriate position.
			intervals.insert(first, newInterval);
		}
		return intervals;
	}
};

int main()
{
	pair<vector<Interval>, Interval> input[] = {
		{{}, {1, 2}},
		{{{3, 4}, {5, 6}}, {1, 2}},
		{{{3, 4}, {5, 6}}, {1, 3}},
		{{{1, 2}, {3, 4}}, {5, 6}},
		{{{1, 2}, {3, 4}}, {4, 6}},
		{{{1, 2}, {3, 4}}, {2, 3}},
		{{{1, 3}, {6, 9}}, {2, 5}},
		{{{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}}, {4, 8}},
	};
	Solution solution;
	for (auto& p: input) {
		cout << p.first << " + " << p.second << " = ";
		cout << solution.insert(p.first, p.second) << endl;
	}
	return 0;
}
