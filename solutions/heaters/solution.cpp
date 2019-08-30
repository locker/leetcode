#include <algorithm>
#include <iostream>
#include <limits>
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

class Solution {
public:
	int findRadius(vector<int>& houses, vector<int>& heaters) {
		if (heaters.empty())
			return -1;
		if (houses.empty())
			return 0;
		sort(houses.begin(), houses.end());
		sort(heaters.begin(), heaters.end());
		//
		// For each pair of neighboring heaters iterate over all houses
		// that are located between them and find the min radius needed
		// to cover those. This gives us linear time complexity.
		//
		int radius = 0;
		auto left = heaters.end();
		auto right = heaters.begin();
		for (auto it = houses.begin(); it != houses.end(); ) {
			if (right != heaters.end() && *it > *right) {
				// Proceed to the next pair of heaters.
				left = right++;
				continue;
			}
			// Find the min radius needed to heat this house.
			int d = numeric_limits<int>::max();
			if (left != heaters.end())
				d = min(d, *it - *left);
			if (right != heaters.end())
				d = min(d, *right - *it);
			// Update the max radius and proceed to the next house.
			radius = max(radius, d);
			++it;
		}
		return radius;
	}
};

int main()
{
	pair<vector<int>, vector<int>> input[] = {
		{{3}, {1}}, // 2
		{{1,2,3}, {2}}, // 1
		{{1,3,5}, {2}}, // 3
		{{1,2,3,4}, {1,4}}, // 1
		{{5,10,100},{1,2,3}}, // 97
		{{5,10,50,20},{6,15}}, // 35
	};
	Solution solution;
	for (auto& p: input) {
		cout << "Input: houses = " << p.first << ", heaters = " << p.second << endl <<
			"Output: " << solution.findRadius(p.first, p.second) << endl;
	}
	return 0;
}
