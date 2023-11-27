#include <iostream>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

namespace {

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	bool first = true;
	for (const auto& x : v) {
		if (!first)
			out << ',';
		out << x;
		first = false;
	}
	out << ']';
	return out;
}

class Solution {
public:
	vector<double> calcEquation(const vector<vector<string>>& equations,
				    const vector<double>& values,
				    const vector<vector<string>>& queries) {
		unordered_map<string, vector<pair<string, double>>> nodes;
		for (int i = 0; i < static_cast<int>(equations.size()); ++i) {
			nodes[equations[i][0]].emplace_back(equations[i][1], values[i]);
			nodes[equations[i][1]].emplace_back(equations[i][0], 1.0 / values[i]);
		}
		vector<double> result;
		for (const auto& q : queries) {
			double product = -1.0;
			queue<pair<string, double>> todo;
			for (const auto& [node, val] : nodes[q[0]]) {
				todo.emplace(node, val);
			}
			unordered_set<string> seen;
			while (!todo.empty()) {
				auto [curr, curr_val] = todo.front();
				todo.pop();
				if (curr == q[1]) {
					product = curr_val;
					break;
				}
				auto [_, inserted] = seen.insert(curr);
				if (!inserted)
					continue;
				for (const auto& [node, val] : nodes[curr])
					todo.emplace(node, val * curr_val);
			}
			result.push_back(product);
		}
		return result;
	}
};

} // namespace

int main()
{
	const tuple<vector<vector<string>>,
		    vector<double>,
		    vector<vector<string>>,
		    vector<double>> test_data[] = {
		{
			{{"a", "b"}, {"b", "c"}},
			{2.0, 3.0},
			{{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}},
			{6.0, 0.5, -1.0, 1.0, -1.0},
		},
		{
			{{"a", "b"}, {"b", "c"}, {"bc", "cd"}},
			{1.5, 2.5, 5.0},
			{{"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"}},
			{3.75, 0.4, 5.0, 0.2},
		},
		{
			{{"a", "b"}},
			{0.5},
			{{"a", "b"}, {"b", "a"}, {"a", "c"}, {"x", "y"}},
			{0.5, 2.0, -1.0, -1.0},
		},
	};
	bool success = true;
	Solution solution;
	for (const auto& [equations, values, queries, expected] : test_data) {
		auto result = solution.calcEquation(equations, values, queries);
		cout << "equations = " << equations << endl <<
			"values = " << values << endl <<
			"queries = " << queries << endl <<
			"result = " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
		cout << endl;
	}
	return success ? 0 : 1;
}
