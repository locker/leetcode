#include <iostream>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>

using namespace std;

namespace {

class Solution {
public:
	int lengthLongestPath(const string& s) {
		stack<int> dir_path_len;
		int path_len = 0;
		int max_path_len = 0;
		bool is_dir = true;
		int start = 0;
		int level = 0;
		for (int i = 0; i <= (int)s.length(); ++i) {
			int c = i < (int)s.length() ? s[i] : '\n';
			switch (c) {
			case '.':
				is_dir = false;
				break;
			case '\n':
				if (is_dir) {
					int len = i - start + 1;
					dir_path_len.push(len);
					path_len += len;
				} else {
					int len = i - start + path_len;
					if (len > max_path_len)
						max_path_len = len;
				}
				start = -1;
				level = 0;
				is_dir = true;
				break;
			case '\t':
				++level;
				break;
			default:
				if (start == -1) {
					while ((int)dir_path_len.size() > level) {
						int len = dir_path_len.top();
						path_len -= len;
						dir_path_len.pop();
					}
					start = i;
				}
				break;
			}
		}
		return max_path_len;
	}
};

} // namespace

int main()
{
	const tuple<string, int> test_data[] = {
		{"dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext", 20},
		{"dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext", 32},
		{"file.ext", 8},
		{"a", 0},
	};
	bool success = true;
	Solution solution;
	for (const auto& [input, expected] : test_data) {
		int result = solution.lengthLongestPath(input);
		cout << "Input:" << endl << input << endl;
		cout << "Result: " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
		cout << endl;
	}
	return success ? 0 : 1;
}
