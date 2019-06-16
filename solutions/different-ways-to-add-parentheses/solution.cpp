#include <iostream>
#include <string>
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
	vector<int> doDiffWaysToCompute(string::const_iterator begin,
					string::const_iterator end) {
		vector<int> result;
		for (auto it = begin; it != end; ++it) {
			char c = *it;
			if (isdigit(c))
				continue;
			auto left = doDiffWaysToCompute(begin, it);
			auto right = doDiffWaysToCompute(it + 1, end);
			for (auto l: left) {
				for (auto r: right) {
					int v = 0;
					switch (c) {
					case '+':
						v = l + r;
						break;
					case '-':
						v = l - r;
						break;
					case '*':
						v = l * r;
						break;
					default:
						break;
					}
					result.push_back(v);
				}
			}
		}
		if (result.empty())
			result.push_back(stoi(string(begin, end)));
		return result;
	}
public:
	vector<int> diffWaysToCompute(const string& s) {
		return doDiffWaysToCompute(s.begin(), s.end());
	}
};

int main()
{
	string input[] = {
		"2", // [2]
		"2+1", // [3]
		"2-1-1", // [0, 2]
		"2*3-4*5", // [-34, -14, -10, -10, 10]
	};
	Solution solution;
	for (const auto& s: input) {
		cout << '"' << s << "\" => " <<
			solution.diffWaysToCompute(s) << endl;
	}
	return 0;
}
