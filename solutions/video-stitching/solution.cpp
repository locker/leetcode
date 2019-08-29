#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

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
	int videoStitching(vector<vector<int>>& clips, int T) {
		// Sort clips by the start time in the ascending order.
		sort(clips.begin(), clips.end(), [] (const vector<int>& a,
						     const vector<int>& b) {
			return a[0] < b[0];
		});
		// Iterate over clips until the whole interval [0,T] is covered;
		// t1 is the current time, t2 is the next time;
		// count is the min number of clips needed to cover [0,t1].
		int count = 0;
		int t1 = 0, t2 = 0;
		auto it = clips.begin();
		while (it != clips.end() && t2 < T) {
			// Among all clips that start before the current time,
			// choose the one that covers the max time duration,
			// add it to the result and move the current time to
			// where the chosen clip ends.
			//
			// ( I've no idea why this is tagged as a dynamic
			//   programming problem. Looks more like a greedy
			//   approach to me. )
			auto& clip = *it;
			if (clip[0] <= t1) {
				t2 = max(t2, clip[1]);
				++it;
			} else {
				if (t2 == t1)
					break;
				t1 = t2;
				++count;
			}
		}
		return t2 < T ? -1 : count + 1;
	}
};

int main()
{
	pair<vector<vector<int>>, int> input[] = {
		{{{0,1},{1,2}},5}, // -1
		{{{0,1},{1,2}},2}, // 2
		{{{0,4},{2,8}},5}, // 2
		{{{0,1},{0,1},{0,2}},1}, // 1
		{{{0,2},{4,6},{8,10},{1,9},{1,5},{5,9}}, 10}, // 3
		{{{0,1},{6,8},{0,2},{5,6},{0,4},{0,3},{6,7},{1,3},{4,7},{1,4},{2,5},{2,6},{3,4},{4,5},{5,7},{6,9}},9}, // 3
	};
	Solution solution;
	for (auto& p: input) {
		auto& clips = p.first;
		auto T = p.second;
		cout << "Input: clips = " << clips << ", T = " << T << endl <<
			"Output: " << solution.videoStitching(clips, T) << endl;
	}
	return 0;
}
