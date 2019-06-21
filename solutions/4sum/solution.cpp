#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
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
	vector<vector<int>> fourSum(const vector<int>& nums, int target) {
		int size = nums.size();
		if (size < 4)
			return {};

		unordered_map<int, vector<pair<int, int>>> two_sum;
		for (int i = 0; i < size; ++i) {
			for (int j = i + 1; j < size; ++j) {
				two_sum[nums[i] + nums[j]].emplace_back(i, j);
			}
		}

		set<vector<int>> result;
		vector<int> quadruplet;
		quadruplet.resize(4);
		for (auto it1 = two_sum.begin(); it1 != two_sum.end(); ++it1) {
			auto it2 = two_sum.find(target - it1->first);
			if (it2 == two_sum.end())
				continue;
			for (const auto& p1: it1->second) {
				for (const auto& p2: it2->second) {
					if (p1.first == p2.first ||
					    p1.first == p2.second ||
					    p1.second == p2.first ||
					    p1.second == p2.second)
						continue;
					quadruplet[0] = nums[p1.first];
					quadruplet[1] = nums[p1.second];
					quadruplet[2] = nums[p2.first];
					quadruplet[3] = nums[p2.second];
					sort(quadruplet.begin(),
					     quadruplet.end());
					result.insert(quadruplet);
				}
			}
		}
		return vector<vector<int>>(result.begin(), result.end());
	}
};

int main()
{
	pair<vector<int>, int> input[] = {
		{{1, 2, 3}, 6},
		{{1, 2, 3, 4}, 8},
		{{1, 2, 3, 4}, 10},
		{{1, 1, 1, 1, 1, 1}, 4},
		{{1, 0, -1, 0, -2, 2}, 0},
		{{-2, 0, 5, -1, -5, 5, 3}, -2}, 
	};
	Solution solution;
	for (const auto& p: input) {
		const auto& nums = p.first;
		int target = p.second;
		cout << "Input: nums = " << nums << ", k = " << target << endl <<
			"Output: " << solution.fourSum(nums, target) << endl;
	}
	return 0;
}
