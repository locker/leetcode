#include <algorithm>
#include <iostream>
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
	vector<int> majorityElement(const vector<int>& nums) {
		// A candidate for a majority element.
		struct Candidate {
			// Value of the candidate for a majority element.
			// Makes sense only if count > 0.
			int val;
			// Number of such elements in the current window.
			int count;
			// Total number of elements in the current window.
			int total;

			Candidate() : val(0), count(0), total(0) {}
		};

		// Apparently, there can't be more than two majority elements
		// such that their count is >= n / 3.
		Candidate major[2];

		for (auto val: nums) {
			for (int i = 0; i < 2; ++i) {
				auto& c = major[i];
				auto& other = major[1 - i];
				if (c.count == 0) {
					// No value has been assigned to this
					// candidate yet. Assign the current
					// element value unless it's already
					// used by another candidate.
					if (other.count == 0 ||
					    other.val != val) {
						c.val = val;
						c.count = 1;
					}
				} else {
					if (val == c.val)
						++c.count;
				}
				++c.total;
				if (c.count > 0 && c.count <= c.total / 3) {
					// This candidate is no longer eligible
					// for a majority element. Moreover,
					// there cannot be another eligible
					// element in the current window except
					// perhaps another candidate. Therefore
					// we can reset the window and start
					// anew.
					c.count = 0;
					c.total = 0;
				}
			}
		}

		vector<int> result;
		int size = nums.size();
		for (auto& c: major) {
			if (c.count == 0)
				continue;
			// Check that the candidate is indeed a majority
			// element before appending it to the result.
			if (count(nums.begin(), nums.end(), c.val) > size / 3)
				result.push_back(c.val);
		}
		return result;
	}
};

int main()
{
	vector<int> input[] = {
		{}, // []
		{1}, // [1]
		{1, 2}, // [1, 2]
		{3, 2, 3}, // [3]
		{1, 2, 3, 4}, // []
		{3, 2, 3, 2}, // [2, 3]
		{1, 2, 3, 1, 2, 3}, // []
		{1, 2, 2, 1, 2, 3}, // [2]
		{1, 1, 1, 1, 1, 1, 1}, // [1]
		{1, 2, 1, 2, 1, 2, 1}, // [1, 2]
		{1, 1, 1, 3, 3, 2, 2, 2}, // [1, 2]
	};
	Solution solution;
	for (const auto& nums: input)
		cout << nums << " => " << solution.majorityElement(nums) << endl;
	return 0;
}
