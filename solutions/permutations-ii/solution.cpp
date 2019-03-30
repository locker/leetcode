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
	//
	// Generate the next permutation in lexicographical order.
	// Returns false if the given permutation is the last one.
	//
	bool nextPermutation(vector<int>& nums) {
		if (nums.empty())
			return false;
		//
		// Find the first element starting from the end violating
		// the descending order:
		//
		//   [1, 3, 5, 4, 2]
		//       ^
		//     pivot
		//
		auto pivot = nums.rbegin() + 1;
		while (pivot != nums.rend() && *pivot >= *(pivot - 1))
			++pivot;
		//
		// If there's none, this is the lexicographically greatest
		// permutation.
		//
		if (pivot == nums.rend())
			return false;
		//
		// Find the first element greater than the pivot among
		// the skipped elements and swap it with the pivot:
		//
		//   [1, 4, 5, 3, 2]
		//       ^     ^
		//       swapped
		//
		auto upper = upper_bound(nums.rbegin(), pivot, *pivot);
		swap(*upper, *pivot);
		//
		// Sort the skipped elements in the ascending order:
		//
		//   [1, 4, 2, 3, 5]
		//         \______/
		//          sorted
		//
		auto it1 = nums.rbegin();
		auto it2 = pivot - 1;
		while (it1 < it2)
			swap(*it1++, *it2--);
		return true;
	}
public:
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());
		do {
			result.push_back(nums);
		} while (nextPermutation(nums));
		return result;
	}
};

int main()
{
	vector<int> input[] = {
		{},
		{1},
		{1, 1},
		{1, 2},
		{1, 1, 2},
		{3, 2, 1},
	};
	Solution solution;
	for (auto& nums: input) {
		cout << "Input: " << nums << endl;
		cout << "Output: " << endl <<
			solution.permuteUnique(nums) << endl << endl;
	}
	return 0;
}
