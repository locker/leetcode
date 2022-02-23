#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
	string convertToTitle(int col) {
		string title;
		while (col > 0) {
			--col;
			title.push_back('A' + col % 26);
			col /= 26;
		}
		reverse(title.begin(), title.end());
		return title;
	}
};

int main()
{
	pair<int, string> test_data[] = {
		{1, "A"},
		{3, "C"},
		{26, "Z"},
		{27, "AA"},
		{28, "AB"},
	};
	bool success = true;
	Solution solution;
	for (const auto& [col, expected] : test_data) {
		auto result = solution.convertToTitle(col);
		cout << col << " => " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
