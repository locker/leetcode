#include <iostream>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T> v)
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
	vector<int> sortedSquares(const vector<int>& nums) {
		vector<int> result;
		result.reserve(nums.size());
		auto it1 = nums.begin();
		while (it1 != nums.end() && *it1 < 0)
			++it1;
		auto it2 = nums.rbegin() + (nums.end() - it1);
		while (it1 != nums.end() && it2 != nums.rend()) {
			auto val1 = *it1 * *it1;
			auto val2 = *it2 * *it2;
			if (val1 < val2) {
				result.push_back(val1);
				++it1;
			} else {
				result.push_back(val2);
				++it2;
			}
		}
		while (it1 != nums.end()) {
			result.push_back(*it1 * *it1);
			++it1;
		}
		while (it2 != nums.rend()) {
			result.push_back(*it2 * *it2);
			++it2;
		}
		return result;
	}
};

int main()
{
	vector<int> input[] = {
		{},
		{1},
		{-1},
		{-1, 1},
		{-2, 1, 2},
		{-3, -1, 0, 1, 2},
		{-4, -1, 0, 3, 10},
		{-7, -3, 2, 3, 11},
		{-8, -4, -2, 0, 1, 3, 5},
	};
	Solution solution;
	for (const auto& nums: input)
		cout << nums << " => " << solution.sortedSquares(nums) << endl;
	return 0;
}
