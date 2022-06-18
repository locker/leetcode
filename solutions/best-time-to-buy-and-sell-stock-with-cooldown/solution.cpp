#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
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
	int maxProfit(const vector<int>& prices) {
		//
		// Let n be the size of the prices array.
		// Let p(k) be element k of the prices array.
		// Let f(k) be the max profit for the prices
		// sub-array starting from index k, 0 <= k < n.
		// We want to find f(0).
		//
		// Apparently, f(n-1) = 0. For simplicity, let us
		// assume that f(n) = f(n+1) = 0.
		//
		// Then for any 0 <= k < n-1:
		//
		//   f(k) = max(f(k+1), f(k+2),
		//              p(k+1) - p(k) + f(k+3),
		//              p(k+2) - p(k) + f(k+4),
		//              ...
		//              p(n-3) - p(k) + f(n-1),
		//              p(n-2) - p(k) + f(n),
		//              p(n-1) - p(k) + f(n+1))
		//        = max(f(k+1), f(k+2), g(k))
		//
		// where
		//
		//   g(k) = max(p(k+1) - p(k) + f(k+3),
		//              p(k+2) - p(k) + f(k+4),
		//              ...
		//              p(n-3) - p(k) + f(n-1),
		//              p(n-2) - p(k) + f(n),
		//              p(n-1) - p(k) + f(n+1))
		//        = max(p(k+1) + f(k+3),
		//              p(k+2) + f(k+4),
		//              ...
		//              p(n-3) + f(n-1),
		//              p(n-2) + f(n),
		//              p(n-1) + f(n+1)) - p(k)
		//        = h(k) - p(k)
		//
		// where
		//
		//   h(k) = max(p(k+1) + f(k+3),
		//              p(k+2) + f(k+4),
		//              ...
		//              p(n-3) + f(n-1),
		//              p(n-2) + f(n),
		//              p(n-1) + f(n+1))
		//        = max(p(k+1) + f(k+3), h(k+1))
		//
		//   h(n-1) = 0
		//
		const int n = prices.size();
		int f0 = 0; // f(k)
		int f1 = 0; // f(k+1)
		int f2 = 0; // f(k+2)
		int f3 = 0; // f(k+3)
		int h0 = 0; // h(k)
		int h1 = 0; // h(k+1)
		for (int k = n - 2; k >= 0; --k) {
			f3 = f2;
			f2 = f1;
			f1 = f0;
			h1 = h0;
			h0 = max(prices[k + 1] + f3, h1);
			f0 = max({f1, f2, h0 - prices[k]});
		}
		return f0;
	}
};

int main()
{
	pair<vector<int>, int> test_data[] = {
		{{1}, 0},
		{{1, 5}, 4},
		{{5, 1}, 0},
		{{1, 3, 10}, 9},
		{{3, 1, 10}, 9},
		{{1, 5, 2, 10}, 9},
		{{1, 2, 3, 0, 2}, 3},
	};
	Solution solution;
	bool success = true;
	for (const auto& [prices, profit] : test_data) {
		int result = solution.maxProfit(prices);
		cout << prices << " -> " << result << endl;
		if (result != profit) {
			cout << "  ERROR: expected " << profit << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
