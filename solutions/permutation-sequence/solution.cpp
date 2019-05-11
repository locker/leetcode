#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Solution {
	// Assuming [begin, end) stores the first permutation
	// (i.e. a sequence sorted in ascending order), 'count'
	// stores the total number of permutations, recursively
	// generate k-th permutation, 1 <= k <= count.
	template<typename iterator>
	void permute(iterator begin, iterator end, int count, int k) {
		if (begin == end)
			return;

		// Find the position of the entry that is going to
		// be the first in the resulting permutation.
		count /= end - begin;
		int pos = (k - 1) / count;

		// Move it to the first position, shifting all its
		// predecessors.
		for (int i = pos; i > 0; --i)
			swap(*(begin + i), *(begin + i - 1));

		// Repeat for [begin + 1, end).
		k -= pos * count;
		permute(begin + 1, end, count, k);
	}
public:
	string getPermutation(int n, int k) {
		string result;
		result.reserve(n);
		int count = 1;
		for (int i = 1; i <= n; ++i) {
			count *= i;
			result.push_back('0' + i);
		}
		permute(result.begin(), result.end(), count, k);
		return result;
	}
};

int main()
{
	pair<int, int> input[] = {
		{1, 1}, // 1
		{2, 1}, // 12
		{2, 2}, // 21
		{3, 1}, // 123
		{3, 2}, // 132
		{3, 3}, // 213
		{3, 4}, // 231
		{3, 5}, // 312
		{3, 6}, // 321
		{4, 1}, // 1234
		{4, 2}, // 1243
		{4, 3}, // 1324
		{4, 4}, // 1342
		{4, 5}, // 1423
		{4, 6}, // 1432
		{4, 7}, // 2134
		{4, 8}, // 2143
		{4, 9}, // 2314
		{4, 10}, // 2341
		{4, 11}, // 2413
		{4, 12}, // 2431
		{4, 24}, // 4321
	};
	Solution solution;
	for (const auto& p: input) {
		cout << "n = " << p.first << ", k = " << p.second << " => " <<
			solution.getPermutation(p.first, p.second) << endl;
	}
	return 0;
}
