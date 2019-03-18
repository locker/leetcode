#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& nums)
{
	out << '[';
	for (auto it = nums.begin(); it != nums.end(); ++it) {
		if (it != nums.begin())
			out << ", ";
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	void nextPermutation(vector<int>& nums) {
		if (nums.empty())
			return;
		// Find the first item that violates descending order
		// at the end of the array, e.g. [1, 2, 5, 4, 3]
		//                                   ^
		//                                 pivot
		auto pivot = nums.rbegin() + 1;
		for (; pivot != nums.rend(); ++pivot) {
			if (*pivot < *(pivot - 1))
				break;
		}
		// Swap the pivot with the next greater item.
		if (pivot != nums.rend()) {
			auto upper = upper_bound(nums.rbegin(), pivot, *pivot);
			swap(*pivot, *upper);
		}
		// Reverse all items following the pivot position.
		auto it1 = pivot - 1;
		auto it2 = nums.rbegin();
		while (it1 > it2)
			swap(*it1--, *it2++);
	}
};

int main()
{
	vector<int> input[] = {
		{},
		{1},
		{1, 2},
		{2, 1},
		{1, 2, 3},
		{3, 2, 1},
		{1, 2, 3, 4},
		{2, 3, 1, 4},
		{3, 4, 2, 1},
		{3, 5, 4, 2, 1},
	};
	Solution solution;
	for (auto& v: input) {
		cout << v << " => ";
		solution.nextPermutation(v);
		cout << v << endl;
	}
	return 0;
}
