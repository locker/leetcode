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

		int max_profit = 0;
		int min_price = prices[0];

		for (int price: prices) {
			if (price > min_price)
				max_profit = max(max_profit, price - min_price);
			else
				min_price = price;
		}
		return max_profit;
	}
};

int main()
{
	vector<int> input[] = {
		{1}, // 0
		{1, 2}, // 1
		{1, 2, 3}, // 2
		{7, 6, 4, 3, 1}, // 0
		{7, 1, 5, 3, 6, 4}, // 5
	};
	Solution solution;
	for (const auto& prices: input)
		cout << prices << " => " << solution.maxProfit(prices) << endl;
	return 0;
}
