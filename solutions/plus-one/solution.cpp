#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	vector<int>& plusOne(vector<int>& digits) {
		bool carry = true;
		for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
			if (++*it < 10) {
				carry = false;
				break;
			}
			*it = 0;
		}
		if (carry) {
			digits.push_back(1);
			rotate(digits.begin(), digits.end() - 1, digits.end());
		}
		return digits;
	}
};

int main()
{
	vector<int> input[] = {
		{},
		{0},
		{1},
		{9},
		{0, 9},
		{1, 0},
		{1, 0, 9},
		{1, 9, 9},
		{9, 9, 9},
	};
	Solution solution;
	for (auto& digits: input) {
		cout << digits << " + 1 = ";
		cout << solution.plusOne(digits) << endl;
	}
	return 0;
}
