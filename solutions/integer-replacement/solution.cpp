#include <algorithm>
#include <iostream>
#include <tuple>
#include <unordered_map>

using namespace std;

namespace {

class Solution {
public:
	int integerReplacement(long long n) {
		if (n == 1)
			return 0;
		static unordered_map<long long, int> cache;
		auto it = cache.find(n);
		if (it != cache.end())
			return it->second;
		int ret;
		if (n % 2 == 0) {
			ret = integerReplacement(n / 2);
		} else {
			ret = min(integerReplacement(n + 1),
				  integerReplacement(n - 1));
		}
		++ret;
		cache.emplace(n, ret);
		return ret;
	}
};

} // namespace

int main()
{
	const tuple<int, int> test_data[] = {
		{4, 2},
		{7, 4},
		{8, 3},
	};
	bool success = true;
	Solution solution;
	for (const auto& [n, expected] : test_data) {
		int result = solution.integerReplacement(n);
		cout << n << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
