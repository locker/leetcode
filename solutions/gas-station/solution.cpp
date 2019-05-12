#include <iostream>
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
	int canCompleteCircuit(const vector<int>& gas, const vector<int>& cost) {
		int len = gas.size();
		// For each starting point, check if we can complete
		// the circuit without running out of gas.
		int start = 0;
		while (start < len) {
			int pos = start;
			int tank = gas[pos];
			while (tank >= cost[pos]) {
				tank -= cost[pos];
				pos = (pos + 1) % len;
				tank += gas[pos];
				if (pos == start)
					return start;
			}
			// We can't for this starting point. Moreover, if we
			// started from any point between 'start' and 'pos',
			// inclusive, we wouldn't be able to complete the
			// circuit either, because we would have even less
			// gas on each gas station then, so we can safely
			// skip them.
			if (pos < start)
				break;
			start = pos + 1;
		}
		return -1;
	}
};

int main()
{
	pair<vector<int>, vector<int>> input[] = {
		{{1}, {1}}, // 0
		{{1}, {2}}, // -1
		{{4, 5}, {5, 4}}, // 1
		{{2, 3, 4}, {3, 4, 3}}, // -1
		{{1, 2, 3, 4, 5}, {3, 4, 5, 1, 2}}, // 3
	};
	Solution solution;
	for (const auto& p: input) {
		const auto& gas = p.first;
		const auto& cost = p.second;
		int idx = solution.canCompleteCircuit(gas, cost);
		cout << "Input:" << endl <<
			"gas  = " << gas << endl <<
			"cost = " << cost << endl <<
			"Output: " << idx << endl << endl;
	}
	return 0;
}
