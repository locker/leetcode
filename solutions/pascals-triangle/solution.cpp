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
	vector<vector<int>> generate(int n_rows) {
		if (n_rows == 0)
			return {};
		vector<vector<int>> result;
		result.emplace_back(1, 1);
		for (int i = 1; i < n_rows; ++i) {
			result.emplace_back();
			auto& curr = result[i];
			auto& prev = result[i - 1];
			curr.reserve(prev.size() + 1);
			curr.push_back(1);
			for (auto it = prev.begin() + 1; it != prev.end(); ++it)
				curr.push_back(*(it - 1) + *it);
			curr.push_back(1);
		}
		return result;
	}
};

int main()
{
	Solution solution;
	for (int i = 0; i < 7; ++i) {
		cout << "Input: " << i << endl << "Output:" << endl <<
			solution.generate(i) << endl << endl;
	}
	return 0;
}
