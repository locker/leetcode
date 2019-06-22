#include <algorithm>
#include <iostream>
#include <iterator>
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
	// Find the max profit that can be gained by executing exactly one
	// transaction on the given prices. Returns the best times to buy
	// and sell stocks.
	template<typename iterator>
	pair<iterator, iterator> maxProfitOne(iterator begin, iterator end) {
		if (begin == end)
			return make_pair(begin, end);

		auto buy_it = begin;
		auto sell_it = begin;
		auto maybe_buy_it = begin;
		auto maybe_sell_it = begin;

		for (auto it = begin + 1; ; ++it) {
			if (*maybe_sell_it - *maybe_buy_it > *sell_it - *buy_it) {
				buy_it = maybe_buy_it;
				sell_it = maybe_sell_it;
			}
			if (it != end) {
				if (*it > *sell_it)
					sell_it = it;
				if (*it > *maybe_sell_it)
					maybe_sell_it = it;
				if (*it < *maybe_buy_it)
					maybe_buy_it = maybe_sell_it = it;
			} else
				break;
		}
		return make_pair(buy_it, sell_it);
	}
public:
	int maxProfit(const vector<int>& prices) {
		if (prices.empty())
			return 0;

		// Find a sub-array that maximizes the profit that can be
		// gained by executing one transaction. It will surely be
		// a part of the two-transaction scheme. We just need to
		// find out whether we need to execute another transaction
		// in the sub-array itself or in one of its neighbors.
		auto p1 = maxProfitOne(prices.begin(), prices.end());
		int profit_one = *p1.second - *p1.first;

		// Find the max profit that can be gained by executing two
		// transactions in the found sub-array. To do that, find the
		// max profit that can be gained by executing one transaction
		// in the reversed sub-array. It's easy to see that the result
		// is the sum of the two.
		auto p2 = maxProfitOne(make_reverse_iterator(p1.second + 1),
				       make_reverse_iterator(p1.first));
		int profit_two = profit_one + *p2.second - *p2.first;

		// Find the max profit that can be gained by executing one
		// transaction in the left neighbor.
		int profit_left = 0;
		if (prices.begin() != p1.first) {
			auto p3 = maxProfitOne(prices.begin(), p1.first);
			profit_left = *p3.second - *p3.first;
		}

		// Find the max profit that can be gained by executing one
		// transaction in the right neighbor.
		int profit_right = 0;
		if (p1.second + 1 != prices.end()) {
			auto p3 = maxProfitOne(p1.second + 1, prices.end());
			profit_right = *p3.second - *p3.first;
		}

		// Choose the maximum.
		int max_profit = profit_two;
		max_profit = max(max_profit, profit_one + profit_left);
		max_profit = max(max_profit, profit_one + profit_right);
		return max_profit;
	}
};

int main()
{
	vector<int> input[] = {
		{}, // 0
		{1}, // 0
		{1, 2}, // 1
		{1, 3, 2}, // 2
		{1, 3, 2, 4}, // 4
		{7, 6, 4, 3, 1}, // 0
		{1, 2, 3, 4, 5}, // 4
		{5, 2, 4, 7, 1, 9, 3}, // 13
		{3, 3, 5, 0, 0, 3, 1, 4}, // 6
	};
	Solution solution;
	for (const auto& prices: input)
		cout << prices << " => " << solution.maxProfit(prices) << endl;
	return 0;
}
