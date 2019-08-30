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

class Solution {
public:
	bool isSelfCrossing(const vector<int>& x) {
		// Start drawing an outbound spiral.
		enum {
			OUTBOUND,
			SWITCH,
			INBOUND,
		} state = OUTBOUND;
		for (int i = 2; i < static_cast<int>(x.size()); ++i) {
			switch (state) {
			case OUTBOUND:
				//
				// Switch to an inbound spiral if the next step
				// can possibly cross a drawn line:
				//
				//   x[i-2]
				//  __________
				// |          |
				// |______|
				//
				//   x[i]
				//
				if (x[i] <= x[i - 2])
					state = SWITCH;
				break;
			case SWITCH:
				//
				//   x[i-4]
				//  ________    x[i]
				// |        |  ______
				// |        | |      |
				// |_________________|
				//
				//       x[i-2]
				//
				if (i >= 4 &&
				    x[i] + x[i - 4] >= x[i - 2] &&
				    x[i - 1] + (i >= 5 ? x[i - 5] : 0) >= x[i - 3])
					return true;
				state = INBOUND;
				// fall through
			case INBOUND:
				//     ______________
				//    |              |
				//    | x[i]         |
				// ___|________
				//    |________|
				//
				//      x[i-2]
				//
				if (x[i] >= x[i - 2])
					return true;
				break;
			}
		}
		return false;
	}
};

int main()
{
	vector<int> input[] = {
		{2}, // false
		{2, 2}, // false
		{2, 1, 1}, // false
		{2, 1, 1, 2}, // true
		{1, 2, 3, 4}, // false
		{1, 1, 1, 1}, // true
		{1, 2, 3, 4, 1}, // false
		{1, 2, 3, 4, 1, 5}, // true
		{1, 2, 3, 4, 1, 3}, // false
		{1, 1, 2, 2, 1, 1}, // true
		{1, 1, 2, 2, 1, 2, 3}, // true
		{1, 1, 2, 2, 3, 3, 4, 4}, // false
		{1, 1, 2, 2, 10, 2, 2, 1, 1}, // false
	};
	Solution solution;
	for (auto& x: input)
		cout << x << " => " << (solution.isSelfCrossing(x) ? "true" : "false") << endl;
	return 0;
}
