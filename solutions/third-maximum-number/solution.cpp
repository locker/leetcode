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
	int thirdMax(const vector<int>& nums) {
		const int nums_size = nums.size();
		const int max_nums_size_max = 3;
		int max_nums[max_nums_size_max];
		int max_nums_size = 0;
		for (int i = 0; i < nums_size; ++i) {
			int j = 0;
			while (j < max_nums_size && max_nums[j] > nums[i])
				++j;
			if (j < max_nums_size && max_nums[j] == nums[i])
				continue;
			if (max_nums_size < max_nums_size_max)
				++max_nums_size;
			if (j == max_nums_size)
				continue;
			for (int k = max_nums_size - 1; k > j; --k)
				max_nums[k] = max_nums[k - 1];
			max_nums[j] = nums[i];
		}
		return max_nums_size < max_nums_size_max ?
			max_nums[0] : max_nums[max_nums_size - 1];
	}
};

} // namespace

int main()
{
	const tuple<vector<int>, int> test_data[] = {
		{{5}, 5},
		{{1, 2}, 2},
		{{3, 2, 1}, 1},
		{{1, 2, 3}, 1},
		{{2, 2, 3, 1}, 1},
		{{5,2,4,1,3,6,0}, 4},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums, expected] : test_data) {
		int result = solution.thirdMax(nums);
		cout << nums << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
