#include <algorithm>
#include <iostream>
#include <tuple>

using namespace std;

namespace {

class Solution {
public:
	bool canMeasureWater(int jug1, int jug2, int target) {
		if (target > jug1 + jug2)
			return false;
		if (jug1 > jug2)
			swap(jug1, jug2);
		for (int i = jug2 % jug1; ; ) {
			if (i % jug1 == target % jug1)
				return true;
			if (i > jug1 || i == 0)
				break;
			i = (jug2 - (jug1 - i)) % jug1;
		}
		return false;
	}
};

} // namespace

int main()
{
	tuple<int, int, int, bool> test_data[] = {
		{1, 1, 1, true},
		{1, 1, 2, true},
		{1, 1, 3, false},
		{1, 2, 1, true},
		{2, 1, 1, true},
		{1, 2, 2, true},
		{2, 1, 2, true},
		{1, 2, 3, true},
		{2, 1, 3, true},
		{1, 2, 4, false},
		{2, 1, 4, false},
		{3, 5, 1, true},
		{3, 5, 2, true},
		{3, 5, 3, true},
		{3, 5, 4, true},
		{3, 5, 5, true},
		{3, 5, 6, true},
		{3, 5, 7, true},
		{3, 5, 8, true},
		{3, 5, 9, false},
		{2, 6, 5, false},
		{4, 7, 3, true},
		{4, 7, 8, true},
		{6, 9, 1, false},
		{13, 11, 1, true},
		{34, 5, 6, true},
	};
	bool success = true;
	Solution solution;
	for (const auto& [jug1, jug2, target, expected] : test_data) {
		bool result = solution.canMeasureWater(jug1, jug2, target);
		cout << "jug1Capacity = " << jug1 <<
			", jug2Capacity = " << jug2 <<
			", targetCapacity = " << target <<
			" -> " << (result ? "true" : "false") << endl;
		if (result != expected) {
			cout << "  ERROR: expected " <<
				(expected ? "true" : "false") << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
