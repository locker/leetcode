#include <algorithm>
#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

namespace {

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
	bool canPartition(const vector<int>& nums) {
		const int n = nums.size();
		vector<int> dp;
		dp.push_back(nums[0]);
		int sum = 0;
		for (int num : nums)
			sum += num;
		sum -= nums[0];
		for (int i = 1; i < n; ++i) {
			int num = nums[i];
			sum -= num;
			vector<int> dp1;
			dp1.reserve(dp.size() * 2);
			for (int diff : dp) {
				if (abs(diff + num) <= sum &&
				    (diff + num + sum) % 2 == 0)
					dp1.push_back(diff + num);
				if (abs(diff - num) <= sum &&
				    (diff - num + sum) % 2 == 0)
					dp1.push_back(diff - num);
			}
			dp = move(dp1);
			sort(dp.begin(), dp.end());
			dp.erase(unique(dp.begin(), dp.end()), dp.end());
		}
		return binary_search(dp.begin(), dp.end(), 0);
	}
};

} // namespace

int main()
{
	const tuple<vector<int>, bool> test_data[] = {
		{{1}, false},
		{{2, 1}, false},
		{{3, 3}, true},
		{{1,5,11,5}, true},
		{{1,2,3,5}, false},
		{{3,3,3,4,5}, true},
		{{100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
		  100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
		  100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
		  100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
		  100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
		  100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
		  100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
		  100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
		  100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
		  100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
		  100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
		  100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
		  100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
		  100,100,100,99,97}, false},
		{{98,31,19,48,18,47,14,64,94,57,1,73,12,93,85,30,99,57,42,86,62,
		  47,18,18,81,76,40,67,98,60,86,65,71,74,61,91,29,35,70,62,74,
		  31,34,41,95,62,36,47,36,40,13,45,80,50,23,69,1,93,54,13,86,70,
		  61,82,55,51,71,94,84,52,14,44,6,79,52,86,22,4,67,52,49,70,73,
		  32,20,18,63,54,86,58,61,18,31,50,61,15,63,41,76,58}, false},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums, expected] : test_data) {
		bool result = solution.canPartition(nums);
		cout << nums << " -> " << (result ? "true" : "false") << endl;
		if (result != expected) {
			cout << "  ERROR: wrong result" << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
