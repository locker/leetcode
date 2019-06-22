#include <algorithm>
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
	int maxProfit(const vector<int>& prices) {
		if (prices.empty())
			return 0;

		int profit = 0;
		int buy_price = *prices.begin();
		for (auto it = prices.begin() + 1; it != prices.end(); ++it) {
			int curr_price = *it;
			int prev_price = *(it - 1);
			if (curr_price < prev_price) {
				profit += prev_price - buy_price;
				buy_price = curr_price;
			}
		}
		profit += max(*prices.rbegin() - buy_price, 0);
		return profit;
	}
};

int main()
{
	vector<int> input[] = {
		{}, // 0
		{1}, // 0
		{1, 8}, // 7
		{1, 7, 2}, // 6
		{1, 5, 2, 3}, // 5
		{1, 2, 3, 4, 5}, // 4
		{7, 1, 5, 3, 6, 4}, // 7
	};
	Solution solution;
	for (const auto& prices: input)
		cout << prices << " => " << solution.maxProfit(prices) << endl;
	return 0;
}
