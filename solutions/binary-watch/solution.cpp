#include <iostream>
#include <string>
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
	vector<string> readBinaryWatch(int turned_on) {
		vector<string> result;
		for (int h = 0; h < 12; ++h) {
			int h_bits = 0;
			for (int k = h; k != 0; k >>= 1) {
				if (k & 1)
					++h_bits;
			}
			for (int m = 0; m < 60; ++m) {
				int m_bits = 0;
				for (int k = m; k != 0; k >>= 1) {
					if (k & 1)
						++m_bits;
				}
				if (h_bits + m_bits == turned_on) {
					string s = to_string(m);
					if (s.size() == 1)
						s = '0' + s;
					s = to_string(h) + ':' + s;
					result.push_back(s);
				}
			}
		}
		return result;
	}
};

} // namespace

int main()
{
	const tuple<int, vector<string>> test_data[] = {
		{1, {"0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"}},
		{9, {}},
	};
	bool success = true;
	Solution solution;
	for (const auto& [turned_on, expected] : test_data) {
		auto result = solution.readBinaryWatch(turned_on);
		cout << turned_on << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
