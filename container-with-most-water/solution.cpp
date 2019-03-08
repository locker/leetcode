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
	int maxArea(const vector<int>& height) {
		int i, j;
		int max_area = 0;
		for (i = 0, j = height.size() - 1; i < j; ) {
			int h1 = height[i];
			int h2 = height[j];
			int area = (j - i) * min(h1, h2);
			if (max_area < area)
				max_area = area;
			if (h1 <= h2) {
				while (i < j && height[i] <= h1)
					++i;
			}
			if (h1 >= h2) {
				while (j > i && height[j] <= h2)
					--j;
			}
		}
		return max_area;
	}
};

int main()
{
	vector<int> input[] = {
		{ 5 },
		{ 5, 3 },
		{ 5, 3, 5 },
		{ 5, 3, 5, 3 },
		{ 5, 3, 9, 2, 1, 4, 9, 5 },
		{ 1, 8, 6, 2, 5, 4, 8, 3, 7 },
	};
	Solution solution;
	for (auto& v: input)
		cout << v << " => " << solution.maxArea(v) << endl;
	return 0;
}
