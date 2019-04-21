#include <algorithm>
#include <iostream>
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
		out << endl << *it;
	}
	out << endl << ']';
	return out;
}

class Solution {
public:
	vector<vector<int>> subsetsWithDup(const vector<int>& nums) {
		// Remove and count duplicates.
		vector<int> nums_count;
		vector<int> nums_unique = nums;
		sort(nums_unique.begin(), nums_unique.end());
		for (auto it = nums_unique.begin(), out = nums_unique.begin();
		     it != nums_unique.end(); ++it) {
			if (it == nums_unique.begin() || *it != *(it - 1)) {
				nums_count.push_back(1);
				if (it != out)
					*out = *it;
				++out;
			} else {
				++nums_count.back();
			}
		}
		int size = nums_count.size();
		nums_unique.resize(size);

		// Enumerate subsets.
		vector<vector<int>> result;
		vector<int> chosen_count(size);
		while (true) {
			vector<int> chosen_nums;
			for (int i = 0; i < size; ++i) {
				for (int j = 0; j < chosen_count[i]; ++j)
					chosen_nums.push_back(nums_unique[i]);
			}
			result.push_back(chosen_nums);

			bool found = false;
			for (int i = 0; i < size; ++i) {
				if (chosen_count[i] < nums_count[i]) {
					++chosen_count[i];
					found = true;
					break;
				}
				chosen_count[i] = 0;
			}
			if (!found)
				break;
		}
		return result;
	}
};

int main()
{
	vector<int> input[] = {
		{},
		{1},
		{1, 1},
		{1, 2, 2},
		{2, 2, 3, 1},
		{1, 3, 2, 2, 1},
	};
	Solution solution;
	for (const auto& nums: input) {
		cout << "Input: " << nums << endl <<
			"Output: " << solution.subsetsWithDup(nums) << endl;
	}
	return 0;
}
