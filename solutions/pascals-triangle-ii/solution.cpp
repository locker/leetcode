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
	vector<int> getRow(int row_index) {
		vector<int> row(1, 1);
		row.reserve(row_index + 1);
		for (int i = 0; i < row_index; ++i) {
			int prev = row[0];
			for (int j = 1; j < i + 1; ++j) {
				int val = row[j];
				row[j] += prev;
				prev = val;
			}
			row.push_back(1);
		}
		return row;
	}
};

int main()
{
	Solution solution;
	for (int i = 0; i <= 10; ++i)
		cout << i << " => " << solution.getRow(i) << endl;
	return 0;
}
