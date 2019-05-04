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

template<typename T>
ostream& operator<<(ostream& out, const vector<vector<T>>& v)
{
	if (v.empty())
		return out << "[]";
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << endl << "  " << *it;
	}
	out << endl << ']';
	return out;
}

class Solution {
public:
	vector<vector<int>> combine(int n, int k) {
		if (k > n)
			k = n;
		if (k == 0)
			return {};

		vector<vector<int>> result;

		vector<int> c(k);
		c[0] = 1;

		int i = 0;
		do {
			for (; i < k - 1 && c[i] < n; ++i)
				c[i + 1] = c[i] + 1;

			result.push_back(c);

			for (; i >= 0; --i) {
				++c[i];
				if (n - c[i] >= k - i - 1)
					break;
			}
		} while (i >= 0);
		return result;
	}
};

int main()
{
	Solution solution;
	for (int n = 0; n < 5; ++n) {
		for (int k = 0; k <= n; ++k) {
			cout << "Input: n = " << n << ", k = " << k << endl <<
				"Output: " << solution.combine(n, k) << endl << endl;
		}
	}
	return 0;
}
