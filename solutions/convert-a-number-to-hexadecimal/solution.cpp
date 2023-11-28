#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>

using namespace std;

namespace {

class Solution {
public:
	string toHex(int num) {
		if (num == 0)
			return "0";
		unsigned u;
		if (num >= 0) {
			u = num;
		} else {
			u = -(long long)num;
			u = ~u + 1;
		}
		string s;
		for (; u > 0; u >>= 4) {
			int v = u & 0xf;
			char c = v < 10 ? '0' + v : 'a' + (v - 10);
			s.push_back(c);
		}
		reverse(s.begin(), s.end());
		return s;
	}
};

} // namespace

int main()
{
	const tuple<int, string> test_data[] = {
		{0, "0"},
		{1, "1"},
		{26, "1a"},
		{-1, "ffffffff"},
		{-2147483648, "80000000"},
	};
	bool success = true;
	Solution solution;
	for (const auto& [num, expected] : test_data) {
		string result = solution.toHex(num);
		cout << num << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
