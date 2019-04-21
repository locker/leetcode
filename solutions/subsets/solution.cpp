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
	vector<vector<int>> subsets(const vector<int>& nums) {
		int size = nums.size();
		vector<vector<int>> result;
		vector<bool> chosen_bits(size);
		while (true) {
			vector<int> chosen_nums;
			for (int i = 0; i < size; ++i) {
				if (chosen_bits[i])
					chosen_nums.push_back(nums[i]);
			}
			result.push_back(chosen_nums);
			bool found = false;
			for (int i = 0; i < size; ++i) {
				if (!chosen_bits[i]) {
					chosen_bits[i] = true;
					found = true;
					break;
				}
				chosen_bits[i] = false;
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
		{1, 2},
		{1, 2, 3},
		{1, 2, 3, 4},
	};
	Solution solution;
	for (const auto& nums: input) {
		cout << "Input: " << nums << endl <<
			"Output: " << solution.subsets(nums) << endl;
	}
	return 0;
}
