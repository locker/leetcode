#include <iomanip>
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
		out << setw(2) << *it;
	}
	out << ']';
	return out;
}

template<typename T>
ostream& operator<<(ostream& out, const vector<vector<T>>& v)
{
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
	vector<vector<int>> generateMatrix(int n) {
		vector<vector<int>> matrix(n);
		for (int i = 0; i < n; ++i)
			matrix[i].resize(n);
		int v = 0;
		for (int k = 0; k <= n / 2; ++k) {
			for (int i = k; i < n - k; ++i)
				matrix[k][i] = ++v;
			for (int i = k + 1; i < n - k; ++i)
				matrix[i][n - k - 1] = ++v;
			for (int i = n - k - 2; i >= k; --i)
				matrix[n - k - 1][i] = ++v;
			for (int i = n - k - 2; i > k; --i)
				matrix[i][k] = ++v;
		}
		return matrix;
	}
};

int main()
{
	Solution solution;
	for (int n = 0; n < 5; ++n) {
		cout << "Input: " << n << endl <<
			"Output:" << endl << solution.generateMatrix(n) <<
			endl << endl;
	}
	return 0;
}
