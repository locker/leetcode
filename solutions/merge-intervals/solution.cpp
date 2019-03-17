#include <algorithm>
#include <iostream>
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
public:
	vector<Interval>& merge(vector<Interval>& intervals) {
		if (intervals.size() <= 1)
			return intervals;
		sort(intervals.begin(), intervals.end(),
		     [](const Interval& a, const Interval& b)
		     { return a.start < b.start; });
		auto last = intervals.begin();
		for (auto curr = last + 1; curr != intervals.end(); ++curr) {
			if (last->end >= curr->start) {
				last->end = max(last->end, curr->end);
				continue;
			}
			++last;
			if (last != curr)
				*last = *curr;
		}
		intervals.resize(last - intervals.begin() + 1);
		return intervals;
	}
};

int main()
{
	vector<Interval> input[] = {
		{},
		{{1, 2}},
		{{1, 2}, {3, 4}},
		{{1, 4}, {4, 5}},
		{{3, 4}, {1, 5}},
		{{1, 3}, {2, 6}, {8, 10}, {15, 18}},
	};
	Solution solution;
	for (auto& v: input) {
		cout << v << " => ";
		cout << solution.merge(v) << endl;
	}
	return 0;
}
