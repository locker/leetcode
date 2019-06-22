#include <algorithm>
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
	int coinChange(const vector<int>& coins, int amount) {
		vector<int> count(amount + 1, -1);
		count[0] = 0;
		for (int i = 0; i < amount; ++i) {
			if (count[i] < 0)
				continue;
			for (int c: coins) {
				if (i > numeric_limits<int>::max() - c)
					continue;
				if (i + c > amount)
					continue;
				if (count[i + c] < 0 ||
				    count[i + c] > count[i] + 1)
					count[i + c] = count[i] + 1;
			}
		}
		return count[amount];
	}
};

int main()
{
	pair<vector<int>, int> input[] = {
		{{}, 2}, // -1
		{{2}, 3}, // -1
		{{3}, 3}, // 1: 3 = 3
		{{2}, 4}, // 2: 4 = 2 + 2
		{{1}, 3}, // 3: 3 = 1 + 1 + 1
		{{1, 2}, 3}, // 2: 3 = 1 + 2
		{{2, 2}, 4}, // 2: 4 = 2 + 2
		{{3, 4}, 10}, // 3: 10 = 3 + 3 + 4
		{{3, 4}, 11}, // 3: 11 = 3 + 4 + 4
		{{3, 4}, 17}, // 5: 17 = 3 + 3 + 3 + 4 + 4
		{{1, 2, 5}, 11}, // 3: 11 = 5 + 5 + 1
	};
	Solution solution;
	for (const auto& p: input) {
		const auto& coins = p.first;
		int amount = p.second;
		int count = solution.coinChange(coins, amount);
		cout << "Input: coins = " << coins <<
			", amount = " << amount << endl <<
			"Output: " << count << endl;
	}
	return 0;
}
