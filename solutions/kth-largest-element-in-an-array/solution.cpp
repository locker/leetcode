#include <iostream>
#include <tuple>
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
	int findKthLargest(vector<int>& nums, int k) {
		// quick select in-place
		int s = 0; // start index
		int e = nums.size(); // end index
		while (true) {
			int p = s + (e - s) / 2; // pivot index
			for (int i = s; i < e; ++i) {
				if (i < p && nums[i] > nums[p]) {
					int tmp = nums[p];
					nums[p] = nums[i];
					nums[i] = tmp;
					p = i;
				} else if (i > p && nums[i] < nums[p]) {
					int tmp1 = nums[p];
					int tmp2 = nums[p + 1];
					nums[p] = nums[i];
					nums[p + 1] = tmp1;
					if (p + 1 != i)
						nums[i] = tmp2;
					++p;
				}
			}
			if (e - p > k) {
				s = p + 1;
			} else if (e - p < k) {
				k -= e - p;
				e = p;
			} else {
				return nums[p];
			}
		}
	}
};

int main()
{
	tuple<vector<int>, int, int> test_data[] = {
		{{5}, 1, 5},
		{{5, 3}, 1, 5},
		{{5, 3}, 2, 3},
		{{5, 7, 3}, 1, 7},
		{{5, 7, 3}, 2, 5},
		{{5, 7, 3}, 3, 3},
		{{3, 2, 1, 5, 6, 4}, 2, 5},
		{{3, 2, 3, 1, 2, 4, 5, 5, 6}, 4, 4},
	};
	bool success = true;
	Solution solution;
	for (auto& [nums, k, expected] : test_data) {
		cout << "nums=" << nums << ", k=" << k << " => ";
		int result = solution.findKthLargest(nums, k);
		cout << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
