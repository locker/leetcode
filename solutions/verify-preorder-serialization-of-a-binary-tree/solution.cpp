#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
	bool isValidSerialization(const string& preorder) {
		auto it = preorder.begin();
		int count = 1;
		while (it != preorder.end() && count > 0) {
			switch (*it) {
			case ',':
				++it;
				break;
			case '#':
				--count;
				++it;
				break;
			default:
				while (it != preorder.end() && *it != ',')
					++it;
				++count;
				break;
			}
		}
		return it == preorder.end() && count == 0;
	}
};

int main()
{
	const pair<string, bool> test_data[] = {
		{"#", true},
		{"10", false},
		{"11,#", false},
		{"10,#,#", true},
		{"101,#,#,1", false},
		{"9,3,4,#,#,1,#,#,2,#,6,#,#", true},
	};
	bool success = true;
	Solution solution;
	for (const auto& [preorder, expected] : test_data) {
		bool result = solution.isValidSerialization(preorder);
		cout << '"' << preorder << '"' <<
			(result ? " is " : " is not ") <<
			"a valid serialization" << endl;
		if (result != expected) {
			cout << "  ERROR: wrong answer" << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
