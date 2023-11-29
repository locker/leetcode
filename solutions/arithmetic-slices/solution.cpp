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
	int numberOfArithmeticSlices(const vector<int>& nums) {
		int n = nums.size();
		int result = 0;
		int count = 0;
		for (int i = 0; i < n; ++i) {
			if (i < 2)
				continue;
			if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2]) {
				++count;
				result += count;
			} else {
				count = 0;
			}
		}
		return result;
	}
};

} // namespace

int main()
{
	const tuple<vector<int>, int> test_data[] = {
		{{1,2,3,4}, 3},
		{{1}, 0},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums, expected] : test_data) {
		int result = solution.numberOfArithmeticSlices(nums);
		cout << nums << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
