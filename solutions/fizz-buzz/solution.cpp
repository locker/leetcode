#include <iostream>
#include <string>
#include <tuple>
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
public:
	vector<string> fizzBuzz(int n) {
		vector<string> result;
		for (int i = 1; i <= n; ++i) {
			if (i % 15 == 0)
				result.emplace_back("FizzBuzz");
			else if (i % 5 == 0)
				result.emplace_back("Buzz");
			else if (i % 3 == 0)
				result.emplace_back("Fizz");
			else
				result.emplace_back(to_string(i));
		}
		return result;
	}
};

} // namespace

int main()
{
	const tuple<int, vector<string>> test_data[] = {
		{3, {"1","2","Fizz"}},
		{5, {"1","2","Fizz","4","Buzz"}},
		{15, {"1","2","Fizz","4","Buzz","Fizz","7","8","Fizz","Buzz",
		      "11","Fizz","13","14","FizzBuzz"}},
	};
	bool success = true;
	Solution solution;
	for (const auto& [n, expected] : test_data) {
		auto result = solution.fizzBuzz(n);
		cout << n << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
