#include <iostream>
#include <tuple>
#include <unordered_map>
#include <utility>
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
	bool canCross(const vector<int>& stones) {
		const int n = stones.size();
		unordered_map<int, vector<bool>> answer;
		answer[stones[n - 1]] = vector<bool>(n + 1, true);
		for (int i = n - 2; i >= 0; --i) {
			vector<bool> answer_i(i + 2, false);
			for (int j = 1; j < i + 2; ++j) {
				auto it = answer.find(stones[i] + j);
				if (it == answer.end())
					continue;
				for (int k = -1; k <= 1; ++k) {
					if (it->second[j + k]) {
						answer_i[j] = true;
						break;
					}
				}
			}
			answer[stones[i]] = move(answer_i);
		}
		return answer[stones[0]][1];
	}
};

} // namespace

int main()
{
	const tuple<vector<int>, bool> test_data[] = {
		{{0,2}, false},
		{{0,1,3,5,6,8,12,17}, true},
		{{0,1,2,3,4,8,9,11}, false},
	};
	bool success = true;
	Solution solution;
	for (const auto& [stones, expected] : test_data) {
		auto result = solution.canCross(stones);
		cout << stones << " -> " << (result ? "true" : "false") << endl;
		if (result != expected) {
			cout << "  ERROR: wrong result" << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
