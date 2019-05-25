#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
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

class Solution {
public:
	string largestNumber(vector<int>& nums) {
		// To get the largest number, we need to first choose a number
		// that has greatest leading digits, e.g. 2 is better than 123
		// and 21 is worse 222. If two numbers happen to have the same
		// leading digits, we need to wrap around the shorter number
		// and start anew, e.g. 123 and 1213 are better than 12 while
		// 121 is worse.
		sort(nums.begin(), nums.end(), [](int n1, int n2) {
			if (n1 == n2)
				return false;
			if (n1 == 0 || n2 == 0)
				return n1 != 0;
			int p1 = 1, p2 = 1;
			while (n1 / p1 / 10 > 0)
				p1 *= 10;
			while (n2 / p2 / 10 > 0)
				p2 *= 10;
			int i1 = p1, i2 = p2;
			bool wrapped1 = false, wrapped2 = false;
			while (!wrapped1 || !wrapped2) {
				if (i1 == 0) {
					i1 = p1;
					wrapped1 = true;
				}
				if (i2 == 0) {
					i2 = p2;
					wrapped2 = true;
				}
				int d1 = n1 / i1 - n1 / (i1 * 10) * 10;
				int d2 = n2 / i2 - n2 / (i2 * 10) * 10;
				if (d1 != d2)
					return d1 > d2;
				i1 /= 10;
				i2 /= 10;
			}
			return false;
		});
		if (nums[0] == 0) {
			// The array is all zeros. Don't return 000...0.
			// Return single 0.
			return "0";
		}
		// Now, as the array is sorted, we just need to concatenate all
		// numbers to get the largest number we can get.
		ostringstream s;
		for (const auto n: nums)
			s << n;
		return s.str();
	}
};

int main()
{
	vector<int> input[] = {
		{1}, // 1
		{0, 0}, // 0
		{1, 2}, // 21
		{10, 2}, // 210
		{20, 1}, // 201
		{6, 66}, // 666
		{121, 12}, // 12121
		{128, 12}, // 12812
		{1, 10, 0}, // 1100
		{2, 21, 3}, // 3212
		{1, 10, 100}, // 110100
		{3, 30, 34, 5, 9}, // 9534330
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => ";
		cout << solution.largestNumber(nums) << endl;
	}
	return 0;
}
