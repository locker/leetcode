#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<int>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ", ";
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	int trap(const vector<int>& height) {
		int size = height.size();
		if (size == 0)
			return 0;
		int result = 0;
		int lh_max = 0;
		int rh_max = 0;
		for (int l = 0, r = size - 1; l < r; ) {
			int lh = height[l];
			int rh = height[r];
			lh_max = max(lh_max, lh);
			rh_max = max(rh_max, rh);
			if (lh <= rh) {
				result += lh_max - lh;
				++l;
			} else {
				result += rh_max - rh;
				--r;
			}
		}
		return result;
	}
};

int main()
{
	vector<int> input[] = {
		{ },
		{ 0 },
		{ 10 },
		{ 0, 0 },
		{ 1, 1 },
		{ 2, 0, 0, 2 },
		{ 10, 0, 1, 1 },
		{ 10, 0, 1, 10, 0, 1 },
		{ 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 },
	};
	Solution solution;
	for (auto& v: input)
		cout << v << " => " << solution.trap(v) << endl;
	return 0;
}
