#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <tuple>
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
	int nthSuperUglyNumber(int n, const vector<int>& primes) {
		int value = 0;
		vector<int> candidates = {1};
		while (n > 0) {
			int next_value = *candidates.begin();
			pop_heap(candidates.begin(), candidates.end(), greater<int>());
			candidates.pop_back();
			if (next_value == value)
				continue;
			value = next_value;
			for (int prime : primes) {
				long long candidate = (long long)value * prime;
				if (candidate <= numeric_limits<int>::max()) {
					candidates.push_back(value * prime);
					push_heap(candidates.begin(), candidates.end(),
						  greater<int>());
				}
			}
			--n;
		}
		return value;
	}
};

int main()
{
	const tuple<int, vector<int>, int> test_data[] = {
		{1, {2}, 1},
		{2, {2}, 2},
		{5, {2}, 16},
		{2, {2, 5}, 2},
		{3, {2, 5}, 4},
		{4, {2, 5}, 5},
		{5, {2, 5}, 8},
		{6, {2, 5}, 10},
		{7, {2, 5}, 16},
		{1, {2, 3, 5}, 1},
		{2, {2, 3, 5}, 2},
		{3, {2, 3, 5}, 3},
		{4, {2, 3, 5}, 4},
		{5, {2, 3, 5}, 5},
		{6, {2, 3, 5}, 6},
		{7, {2, 3, 5}, 8},
		{8, {2, 3, 5}, 9},
		{9, {2, 3, 5}, 10},
		{5, {2, 7, 13, 19}, 8},
		{7, {2, 7, 13, 19}, 14},
		{9, {2, 7, 13, 19}, 19},
		{12, {2, 7, 13, 19}, 32},
		{
			100000,
			{
				7, 19, 29, 37, 41, 47, 53, 59, 61, 79, 83, 89,
				101, 103, 109, 127, 131, 137, 139, 157, 167,
				179, 181, 199, 211, 229, 233, 239, 241, 251
			},
			1092889481,
		},
	};
	bool success = true;
	Solution solution;
	for (const auto& [n, primes, expected] : test_data) {
		int result = solution.nthSuperUglyNumber(n, primes);
		cout << "n=" << n << ", primes=" << primes << " => " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
