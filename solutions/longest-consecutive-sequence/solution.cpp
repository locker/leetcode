#include <algorithm>
#include <iostream>
#include <unordered_map>
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
	int longestConsecutive(const vector<int>& nums) {
		if (nums.empty())
			return 0;

		//
		// Map: k => v, k belongs to nums.
		//
		// Depending on the sign of v, [k, k+v] or [k+v, k]
		// is a consecutive sequence.
		//
		// Initialized with one-number sequences for each
		// given number.
		//
		unordered_map<int, int> seqs;
		for (auto x: nums)
			seqs.emplace(x, 0);

		//
		// Do another pass over the array and merge adjacent
		// sequences, keeping track of the longest consecutive
		// sequence length.
		//
		int max_seq = 1;
		for (auto x: nums) {
			auto end1 = seqs.find(x);
			if (end1 == seqs.end() || end1->second > 0) {
				// The value has already been merged into
				// some sequence.
				continue;
			}
			auto begin2 = seqs.find(x + 1);
			if (begin2 == seqs.end()) {
				// No adjacent sequence.
				continue;
			}
			auto begin1 = (end1->second == 0 ? end1 :
				       seqs.find(end1->first + end1->second));
			auto end2 = (begin2->second == 0 ? begin2 :
				     seqs.find(begin2->first + begin2->second));
			int len = begin1->second + begin2->second + 1;
			begin1->second = len;
			end2->second = -len;
			if (begin1 != end1)
				seqs.erase(end1);
			if (begin2 != end2)
				seqs.erase(begin2);
			max_seq = max(max_seq, len + 1);
		}
		return max_seq;
	}
};

int main()
{
	vector<int> input[] = {
		{}, // 0
		{1}, // 1
		{1, 2}, // 2
		{2, 4, 1}, // 2
		{2, 4, 3, 6}, // 3
		{8, 3, 9, 5, 4, 7, 1}, // 3
		{100, 4, 200, 1, 2, 3}, // 4
		{3, 4, 100, 5, 101, 102, 6, 50, 60, 51}, // 4
	};
	Solution solution;
	for (const auto& nums: input) {
		cout << nums << " => " <<
			solution.longestConsecutive(nums) << endl;
	}
	return 0;
}
