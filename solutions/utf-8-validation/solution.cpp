#include <iostream>
#include <tuple>
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
	bool validUtf8(const vector<int>& data) {
		int count = 0;
		for (int code : data) {
			if (count > 0) {
				if (((code >> 6) & 3) != 2)
					return false;
				--count;
				continue;
			}
			for (int i = 7; i >= 0; --i) {
				if (((code >> i) & 1) == 0)
					break;
				++count;
			}
			if (count == 1 || count > 4)
				return false;
			if (count > 0)
				--count;
		}
		return count == 0;
	}
};

} // namespace

int main()
{
	const tuple<vector<int>, bool> test_data[] = {
		{{197, 130, 1}, true},
		{{235, 140, 4}, false},
		{{230, 136, 145}, true},
		{{248, 130, 130, 130}, false},
		{{250, 145, 145, 145, 145}, false},
	};
	bool success = true;
	Solution solution;
	for (const auto& [data, expected] : test_data) {
		bool result = solution.validUtf8(data);
		cout << data << " -> " << (result ? "true" : "false") << endl;
		if (result != expected) {
			cout << "  ERROR: wrong result" << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
