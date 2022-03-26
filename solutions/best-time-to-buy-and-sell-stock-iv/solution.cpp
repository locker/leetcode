#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

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
	int maxProfit(int k, const vector<int>& prices) {
		const int n = prices.size();
		if (n <= 1)
			return 0;
		k = min(k, n / 2);
		//
		// Let
		//
		//   p[j] = prices[j]
		//   res[i][j] = max profit for k = i and prices = prices[j:]
		//   aux[i][j] = max(p[l] + res[i][l+1]) over j <= l < n - 1
		//
		// Then
		//
		//   aux[i][j] = max(p[j] + res[i][j+1], aux[i][j + 1])
		//   res[i][j] = max(res[i-1][j], res[i][j+1], x[i][j])
		//
		// where
		//
		//   x[i][j] = max(p[l] - p[j] + res[i-1][l+1])
		//             over j <= l < n - 1
		//           = max(p[l] + res[i-1][l+1]) - p[j]
		//           = aux[i-1][j] - p[j]
		//
		vector<vector<int>> res(k + 1);
		vector<vector<int>> aux(k + 1);
		for (int i = 0; i <= k; ++i) {
			res[i].resize(n);
			aux[i].resize(n);
		}
		aux[0][n - 1] = prices[n - 1];
		for (int j = n - 2; j >= 0; --j)
			aux[0][j] = max(prices[j], aux[0][j + 1]);
		for (int i = 1; i <= k; ++i) {
			for (int j = n - 2; j >= 0; --j) {
				res[i][j] = max({res[i - 1][j], res[i][j + 1],
						 aux[i - 1][j] - prices[j]});
				aux[i][j] = max(prices[j] + res[i][j + 1],
						aux[i][j + 1]);
			}
		}
		return res[k][0];
	}
};

int main()
{
	tuple<int, vector<int>, int> test_data[] = {
		{2, {}, 0},
		{5, {1}, 0},
		{3, {1, 2}, 1},
		{0, {1, 2, 3}, 0},
		{2, {2, 4, 1}, 2},
		{2, {1, 2, 4, 7}, 6},
		{3, {5, 4, 3, 2, 1}, 0},
		{3, {5, 4, 3, 2, 10}, 8},
		{1, {1, 2, 3, 10, 7}, 9},
		{2, {1, 2, 3, 10, 7}, 9},
		{2, {3, 2, 6, 5, 0, 3}, 7},
	};
	bool success = true;
	Solution solution;
	for (const auto& [k, prices, expected] : test_data) {
		int result = solution.maxProfit(k, prices);
		cout << "k=" << k << ", prices=" << prices <<
			", profit=" << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
