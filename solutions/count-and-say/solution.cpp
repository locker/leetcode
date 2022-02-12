#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
private:
	string say(const string& input) {
		assert(!input.empty());
		string output;
		int count = 0;
		char curr = 0;
		for (auto it = input.begin(); ; ++it) {
			if (it == input.begin())
				curr = *it;
			if (it == input.end() || curr != *it) {
				assert(count > 0);
				assert(curr != 0);
				output.append(to_string(count));
				output.push_back(curr);
				if (it == input.end())
					break;
				curr = *it;
				count = 0;
			}
			++count;
		}
		return output;
	}
public:
	string countAndSay(int n) {
		assert(n >= 1);
		string s = "1";
		for (int i = 1; i < n; ++i)
			s = say(s);
		return s;
	}
};

int main()
{
	vector<string> expected = {
		"1",
		"11",
		"21",
		"1211",
		"111221",
		"312211",
		"13112221",
		"1113213211",
		"31131211131221",
		"13211311123113112211",
	};
	bool success = true;
	Solution solution;
	for (int i = 0; i < static_cast<int>(expected.size()); ++i) {
		int n = i + 1;
		string result = solution.countAndSay(n);
		cout << n << " => " << result << endl;
		if (result != expected[i]) {
			cout << "  ERROR: expected " << expected[i] << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
