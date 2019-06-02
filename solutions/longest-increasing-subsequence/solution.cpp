#include <algorithm>
#include <iostream>
#include <set>
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
	int lengthOfLIS(const vector<int>& nums) {
		//
		// Our task is to find the length of the longest common
		// sequence of nums and unique(sorted(nums)), which is
		// a classic dynamic programming problem solved in O(n^2)
		// time and O(n) space.
		//
		// However, since one of the sequences is sorted, we can
		// solve it in O(n*log(n)) time by applying binary search.
		//

		// First, sort the input array and remove duplicates.
		vector<int> nums2(nums);
		sort(nums2.begin(), nums2.end());
		auto last = unique(nums2.begin(), nums2.end());
		nums2.erase(last, nums2.end());

		//
		// The classic problem solution uses an array to store
		// intermediate results: when we consider suffix s1[i:]
		// of sequence s1 (i = len(s1)-1, ..., 1, 0), we store
		// the length of the longest common sequence of s1[i:] and
		// s2[j:] in array entry r[j] (j = 0, 1, ..., len(s2)-1).
		// The array is updated as follows:
		//
		//   r[j] = max(r[j], r[j+1] + 1)     if s1[i] = s2[j]
		//   r[j] = max(r[j], r[j+1])         otherwise
		//
		// If we used an array, we'd end up with O(n^2) time
		// complexity as we'd have to update it on each iteration.
		//
		// Actually, we can use an ordered set instead of an
		// array: the point is we are only interested in points
		// such that r[j] > r[j+1], i.e. s1[i] = s2[j]. It's
		// easy to see that the number of such points is, in
		// fact, the length of the longest common sequence.
		// So all we need to do is store such "bump" points in
		// an ordered set. Note, a "bump" only happens if
		// the new point falls before any point in the set.
		// If it falls between two points, we need to shift
		// the preceding point to the position of the new point.
		//
		set<int> dp;
		dp.insert(nums2.size());

		int len = nums.size();
		for (int pos = len - 1; pos >= 0; --pos) {
			int pos2 = lower_bound(nums2.begin(), nums2.end(),
					       nums[pos]) - nums2.begin();
			auto it = dp.upper_bound(pos2);
			if (it != dp.begin()) {
				auto prev = it;
				--prev;
				dp.erase(prev);
			}
			dp.insert(it, pos2);
		}
		return dp.size() - 1;
	}
};

int main()
{
	vector<int> input[] = {
		{}, // 0
		{1}, // 1
		{1, 1}, // 1
		{2, 1}, // 1
		{1, 2}, // 2
		{1, 2, 3}, // 3
		{1, 3, 2}, // 2
		{3, 1, 2}, // 2
		{3, 2, 1}, // 1
		{2, 2, 1}, // 1
		{1, 2, 1}, // 2
		{3, 2, 1, 3, 2, 1}, // 2
		{1, 1, 2, 2, 3, 3, 1, 2, 3}, // 3
		{10, 9, 2, 5, 3, 7, 101, 18}, // 4
	};
	Solution solution;
	for (const auto& nums: input)
		cout << nums << " => " << solution.lengthOfLIS(nums) << endl;
	return 0;
}
