#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	for (const auto& x : v)
		out << x;
	return out;
}

namespace {

class Solution {
private:
	static constexpr int mod = 1337;
public:
	int superPow(int a, vector<int> b) {
		long long result = 1;
		for (int i = 0; i < b.back(); ++i)
			result = (result * a) % mod;
		b.pop_back();
		if (!b.empty()) {
			int x = superPow(a, move(b));
			for (int i = 0; i < 10; ++i)
			     result = (result * x) % mod;
		}
		return result;
	}
};

} // namespace

int main()
{
	const tuple<int, vector<int>, int> test_data[] = {
		{2, {3}, 8},
		{2, {1, 0}, 1024},
		{2, {1, 1}, 711},
		{2, {1, 2}, 85},
		{3, {1, 2, 3}, 517},
		{1, {4, 3, 3, 8, 5, 2}, 1},
	};
	bool success = true;
	Solution solution;
	for (const auto& [a, b, expected] : test_data) {
		int result = solution.superPow(a, b);
		cout << "a=" << a << ", b=" << b << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
