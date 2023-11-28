#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

namespace {

class Solution {
public:
	string removeKdigits(string num, int k) {
		vector<char> s;
		s.push_back('0');
		for (char c : num) {
			for (; k > 0 && c < s.back(); --k)
				s.pop_back();
			s.push_back(c);
		}
		for (; k > 0; --k)
			s.pop_back();
		auto begin = s.begin();
		auto end = s.end();
		for (; begin + 1 != end && *begin == '0'; ++begin) {
		}
		return {begin, end};
	}
};

} // namespace

int main()
{
	const tuple<string, int, string> test_data[] = {
		{"1432219", 3, "1219"},
		{"10200", 1, "200"},
		{"10", 2, "0"},
		{"91", 1, "1"},
		{"19", 1, "1"},
	};
	bool success = true;
	Solution solution;
	for (const auto& [num, k, expected] : test_data) {
		auto result = solution.removeKdigits(num, k);
		cout << "num = " << num << ", k = " << k <<
			" -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
