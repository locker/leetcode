#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

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
	void wiggleSort(vector<int>& nums) {
		const int size = nums.size();
		const int middle = (size - 1) / 2;
		sort(nums.begin(), nums.end());
		int i1 = middle;
		int i2 = size - 1;
		vector<int> result;
		result.reserve(size);
		while (i1 >= 0) {
			result.push_back(nums[i1--]);
			if (i2 > middle)
				result.push_back(nums[i2--]);
		}
		nums = result;
	}
};

bool check(vector<int> nums, vector<int> result) {
	const int size = result.size();
	for (int i = 1; i < size; i += 2) {
		if (result[i] <= result[i - 1])
			return false;
		if (i < size - 1 && result[i] <= result[i + 1])
			return false;
	}
	sort(nums.begin(), nums.end());
	sort(result.begin(), result.end());
	return nums == result;
}

int main()
{
	const vector<int> input[] = {
		{1},
		{1,1,2,2,2,1},
		{1,5,1,1,6,4},
		{1,3,2,2,3,1},
		{1,1,2,1,2,2,1},
		{4,5,5,5,5,6,6,6},
		{1,4,3,4,1,2,1,3,1,3,2,3,3},
	};
	bool success = true;
	Solution solution;
	for (const auto& nums : input) {
		auto result = nums;
		solution.wiggleSort(result);
		cout << nums << " => " << result << endl;
		if (!check(nums, result)) {
			cout << "  ERROR: wrong result" << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
