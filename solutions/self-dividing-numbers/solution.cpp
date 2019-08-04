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
	bool isSelfDividingNumber(int num) {
		int quotient = num;
		do {
			int digit = quotient % 10;
			quotient /= 10;
			if (digit == 0 || num % digit != 0)
				return false;
		} while (quotient > 0);
		return true;
	}
public:
	vector<int> selfDividingNumbers(int left, int right) {
		vector<int> result;
		for (int num = left; num <= right; ++num) {
			if (isSelfDividingNumber(num))
				result.push_back(num);
		}
		return result;
	}
};

int main()
{
	Solution solution;
	int left = 0;
	int right = 100;
	cout << "Self-dividing numbers between " << left << " and " << right <<
		" are " << solution.selfDividingNumbers(left, right) << endl;
	return 0;
}
