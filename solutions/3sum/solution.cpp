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
			out << ", ";
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		int size = nums.size();
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());
		for (int k = 0; k < size - 2; ) {
			for (int i = k + 1, j = size - 1; i < j; ) {
				int sum = nums[i] + nums[j] + nums[k];
				if (sum == 0) {
					vector<int> triplet({nums[k], nums[i], nums[j]});
					result.push_back(move(triplet));
				}
				if (sum >= 0) {
					do {
						--j;
					} while (i < j && nums[j] == nums[j + 1]);
				}
				if (sum <= 0) {
					do {
						++i;
					} while (i < j && nums[i] == nums[i - 1]);
				}
			}
			do {
				++k;
			} while (k < size && nums[k] == nums[k - 1]);
		}
		return result;
	}
};

int main()
{
	vector<int> input[] = {
		{ },
		{ 0 },
		{ 1, -1 },
		{ 1, -1, 0 },
		{ -1, 0, 1, 2, -1, -4 },
		{ 2, -4, 2, 2, -2, -3, 1 },
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => ";
		cout << solution.threeSum(nums) << endl;
	}
	return 0;
}
