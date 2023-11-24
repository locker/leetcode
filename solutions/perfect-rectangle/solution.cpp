#include <algorithm>
#include <iostream>
#include <limits>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

namespace std {

template<typename T, typename U>
struct hash<pair<T, U>> {
	size_t operator()(const pair<T, U>& p) const {
		return hash<T>()(p.first) ^ (hash<U>()(p.second) << 1);
	}
};

} // namespace std

namespace {

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
	bool isRectangleCover(const vector<vector<int>>& rectangles) {
		long long area = 0;
		int x1 = numeric_limits<int>::max();
		int x2 = numeric_limits<int>::min();
		int y1 = numeric_limits<int>::max();
		int y2 = numeric_limits<int>::min();
		for (const auto& r : rectangles) {
			area += (long long)(r[2] - r[0]) * (r[3] - r[1]);
			x1 = min(x1, r[0]);
			x2 = max(x2, r[2]);
			y1 = min(y1, r[1]);
			y2 = max(y2, r[3]);
		}
		if (area != (long long)(x2 - x1) * (y2 - y1))
			return false;
		int odd_points = 0;
		unordered_map<pair<int, int>, int> points;
		for (const auto& r : rectangles) {
			for (int i = 0; i < 4; i += 2) {
				for (int j = 1; j < 4; j += 2) {
					int x = r[i];
					int y = r[j];
					int count = ++points[make_pair(x, y)];
					if (count % 2 == 0)
						--odd_points;
					else
						++odd_points;
					if (count > 1 &&
					    ((x == x1 && y == y1) ||
					     (x == x1 && y == y2) ||
					     (x == x2 && y == y1) ||
					     (x == x2 && y == y2)))
						return false;
				}
			}
		}
		return odd_points == 4;
	}
};

} // namespace

int main()
{
	const tuple<vector<vector<int>>, bool> test_data[] = {
		{{{1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4}}, true},
		{{{1,1,2,3},{1,3,2,4},{3,1,4,2},{3,2,4,4}}, false},
		{{{1,1,3,3},{3,1,4,2},{1,3,2,4},{2,2,4,4}}, false},
		{{{0,0,1,1},{0,0,2,1},{1,0,2,1},{0,2,2,3}}, false},
		{{{0,0,1,1},{0,0,1,1},{1,1,2,2},{1,1,2,2}}, false},
		{{{0,0,3,3},{1,1,2,2},{1,1,2,2}}, false},
	};
	bool success = true;
	Solution solution;
	for (const auto& [rectangles, expected] : test_data) {
		bool result = solution.isRectangleCover(rectangles);
		cout << rectangles << " -> " <<
			(result ? "true" : "false") << endl;
		if (result != expected) {
			cout << "  ERROR: wrong result" << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
