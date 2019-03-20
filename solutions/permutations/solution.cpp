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

template<typename T>
ostream& operator<<(ostream& out, const vector<vector<T>>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << endl << "  " << *it;
	}
	out << endl << ']';
	return out;
}

class Solution {
public:
	vector<vector<int>> permute(const vector<int>& nums) {
		vector<vector<int>> result;
		result.push_back(nums);

		int size = nums.size();
		if (size <= 1)
			return result;

		vector<bool> chosen;
		chosen.resize(size, true);

		vector<int> perm(size);
		for (int i = 0; i < size; ++i)
			perm[i] = i;

		while (true) {
			//
			// Generate the next permutation.
			//
			// 1. Find the rightmost entry that can be increased.
			//
			int i, j;
			for (i = size - 1; i >= 0; --i) {
				chosen[perm[i]] = false;
				for (j = perm[i] + 1; j < size; ++j) {
					if (!chosen[j]) {
						chosen[j] = true;
						perm[i] = j;
						break;
					}
				}
				if (j < size)
					break;
			}
			if (i < 0)
				break;
			//
			// 2. Arrange all following entries in ascending order.
			//
			for (i = i + 1, j = -1; i < size; ++i) {
				for (j = j + 1; j < size; ++j) {
					if (!chosen[j]) {
						chosen[j] = true;
						perm[i] = j;
						break;
					}
				}
			}
			//
			// Append the permutation to the result.
			//
			vector<int> nums_perm;
			nums_perm.reserve(size);
			for (int i = 0; i < size; ++i)
				nums_perm.push_back(nums[perm[i]]);
			result.push_back(move(nums_perm));
		}
		return result;
	}
};

int main()
{
	vector<int> input[] = {
		{},
		{ 5 },
		{ 5, 4 },
		{ 1, 2, 3 },
		{ 2, 6, 4, 8 },
	};
	Solution solution;
	for (auto nums: input) {
		cout << "Input: " << nums << endl << "Output: " << endl <<
			solution.permute(nums) << endl << endl;
	}
	return 0;
}
