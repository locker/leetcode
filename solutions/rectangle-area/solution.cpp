#include <algorithm>
#include <iostream>
#include <tuple>

using namespace std;

class Solution {
public:
	int computeArea(int ax1, int ay1, int ax2, int ay2,
			int bx1, int by1, int bx2, int by2) {
		int area1 = (ax2 - ax1) * (ay2 - ay1);
		int area2 = (bx2 - bx1) * (by2 - by1);
		int isectx = max(min(ax2, bx2) - max(ax1, bx1), 0);
		int isecty = max(min(ay2, by2) - max(ay1, by1), 0);
		return area1 + area2 - isectx * isecty;
	}
};

int main()
{
	tuple<int, int, int, int, int, int, int, int, int> test_data[] = {
		{-5, -5, -2, -2,  2,  2,  5,  5, 18},
		{-5, -5,  5,  5, -3, -2,  2,  3, 100},
		{-3,  0,  3,  4,  0, -1,  9,  2, 45},
		{-2, -2,  2,  2, -2, -2,  2,  2, 16},
	};
	bool success = true;
	Solution solution;
	for (const auto [ax1, ay1, ax2, ay2, bx1, by1, bx2, by2, expected] : test_data) {
		int result = solution.computeArea(ax1, ay1, ax2, ay2, bx1, by1, bx2, by2);
		cout << "ax1=" << ax1 << ", ay1=" << ay1 << ", bx1=" << bx1 << ", by1=" << by1 << ", " <<
			"ax2=" << ax2 << ", ay2=" << ay2 << ", bx2=" << bx2 << ", by2=" << by2 << ", " <<
			"area=" << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
