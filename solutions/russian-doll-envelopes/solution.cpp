#include <algorithm>
#include <iostream>
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

class Solution {
public:
	int maxEnvelopes(vector<vector<int>>& envelopes) {
		// Sort by width ascending, then by height descending.
		sort(envelopes.begin(), envelopes.end(),
		     [](const vector<int>& a, const vector<int>& b)
		     { return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0]; });
		vector<int> heights;
		heights.push_back(envelopes[0][1]);
		for (int i = 1; i < static_cast<int>(envelopes.size()); ++i) {
			int height = envelopes[i][1];
			// All the envelopes seen so far fit in this one by width.
			// Find the one whose height >= this one's height.
			auto it = lower_bound(heights.begin(), heights.end(), height);
			if (it == heights.end()) {
				// No such envelope, i.e. all envelopes can fit
				// in this one by both height and width.
				heights.push_back(height);
			} else {
				// The found envelope is greater than this one
				// by height, but less than this one by width.
				// Replace it with this one, thus virtually
				// starting the iteration anew.
				*it = height;
			}
		}
		return heights.size();
	}
};

int main()
{
	pair<vector<vector<int>>, int> test_data[] = {
		{{{1,1}}, 1},
		{{{1,1},{1,1},{1,1}}, 1},
		{{{1,5},{1,3},{2,4}}, 2},
		{{{1,5},{1,3},{2,4},{2,5},{2,5},{3,5}}, 3},
		{{{5,4},{6,4},{6,7},{2,3}}, 3},
		{{{1,2},{2,3},{3,4},{3,5}}, 3},
		{{{1,2},{2,3},{3,4},{3,5},{4,5}}, 4},
		{{{1,2},{2,3},{3,4},{3,5},{4,5},{5,5}}, 4},
		{{{1,2},{2,3},{3,4},{3,5},{4,5},{5,5},{5,6}}, 5},
		{{{2,13},{5,7},{13,11},{14,17},{18,13},{18,19}}, 4},
		{{{2,13},{5,7},{11,19},{13,11},{14,17},{18,13},{18,19}}, 4},
		{{{1,2},{2,3},{3,4},{3,5},{4,5},{5,5},{5,6},{6,7},{7,8}}, 7},
		{{{8,9},{5,7},{11,19},{8,11},{13,11},{2,13},{11,19},{8,11},
		 {13,11},{2,13},{11,19},{16,1},{18,13},{14,17},{18,19}}, 5},
		{{{15,8},{2,20},{2,14},{4,17},{8,19},{8,9},{5,7},{11,19},{8,11},
		 {13,11},{2,13},{11,19},{8,11},{13,11},{2,13},{11,19},{16,1},
		 {18,13},{14,17},{18,19}}, 5},
	};
	bool success = true;
	Solution solution;
	for (auto& [envelopes, expected] : test_data) {
		cout << envelopes << " => ";
		int result = solution.maxEnvelopes(envelopes);
		cout << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	};
	return success ? 0 : 1;
}
