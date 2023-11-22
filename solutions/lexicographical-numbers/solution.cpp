#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

namespace {

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
private:
	void helper(int n, int base, vector<int>& result) {
		for (int i = 0; i <= 9; ++i) {
			int val = base * 10 + i;
			if (val == 0)
				continue;
			if (val > n)
				break;
			result.push_back(val);
			helper(n, val, result);
		}
	}
public:
	vector<int> lexicalOrder(int n) {
		vector<int> result;
		result.reserve(n);
		helper(n, 0, result);
		return result;
	}
};

vector<int> lexicalOrderSlow(int n)
{
	vector<int> result;
	for (int i = 1; i <= n; ++i)
		result.push_back(i);
	sort(result.begin(), result.end(), [](int a, int b) {
		return to_string(a) < to_string(b);
	});
	return result;
}

} // namespace

int main()
{
	const int test_data[] = {1, 2, 5, 13, 35, 215};
	bool success = true;
	Solution solution;
	for (const auto n : test_data) {
		auto result = solution.lexicalOrder(n);
		cout << n << " -> " << result << endl;
		auto expected = lexicalOrderSlow(n);
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
