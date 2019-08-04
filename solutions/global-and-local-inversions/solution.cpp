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
	bool isIdealPermutation(const vector<int>& A) {
		int size = A.size();
		if (size < 3)
			return true;
		int max_val = A[0];
		for (int val: A) {
			if (val < max_val - 1) {
				/*
				 * This value forms a global inversion with
				 * one of it predecessors. The inversion can
				 * not be local by definition.
				 */
				return false;
			}
			max_val = max(max_val, val);
		}
		return true;
	}
};

int main()
{
	vector<int> input[] = {
		{0}, // true
		{1, 0}, // true
		{2, 1, 0}, // false
		{1, 0, 2}, // true
		{1, 2, 0}, // false
		{1, 0, 3, 2}, // true
		{2, 1, 3, 0}, // false
	};
	Solution solution;
	for (auto& A: input) {
		cout << A << " => " << (solution.isIdealPermutation(A) ?
					"true" : "false") << endl;
	}
	return 0;
}
