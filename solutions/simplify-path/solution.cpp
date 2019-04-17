#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
	string simplifyPath(const string& path) {
		string result;

		// Describes what we have scanned since the last slash.
		enum {
			NONE,
			PERIOD,
			DOUBLE_PERIOD,
			OTHER,
		} state = NONE;

		auto it = path.begin();
		while (true) {
			if (it == path.end() || *it == '/') {
				if (state == DOUBLE_PERIOD && !result.empty()) {
					// Erase the previous token.
					while (result.back() != '/')
						result.pop_back();
					result.pop_back();
				}
				state = NONE;
			} else if (*it == '.') {
				if (state == NONE) {
					state = PERIOD;
				} else if (state == PERIOD) {
					state = DOUBLE_PERIOD;
				} else {
					if (state == DOUBLE_PERIOD) {
						result.append("/..");
						state = OTHER;
					}
					result.push_back('.');
				}
			} else {
				if (state == NONE)
					result.push_back('/');
				if (state == PERIOD)
					result.append("/.");
				if (state == DOUBLE_PERIOD)
					result.append("/..");
				result.push_back(*it);
				state = OTHER;
			}
			if (it == path.end())
				break;
			++it;
		}
		if (result.empty())
			result.push_back('/');
		return result;
	}
};

int main()
{
	string input[] = {
		"/home/", // "/home"
		"/./", // "/"
		"/../", // "/"
		"/...", // "/..."
		"/.a", // "/.a"
		"/.a.", // "/.a."
		"/.a..", // "/.a.."
		"/home//foo/", // "/home/foo"
		"/a/./b/../../c/", // "/c"
		"/a/../../b/../c//.//", // "/c"
		"/a//b////c/d//././/..", // "/a/b/c"
	};
	Solution solution;
	for (const auto& path: input) {
		cout << '"' << path << "\" => \"" <<
			solution.simplifyPath(path) << '"' << endl;
	}
	return 0;
}
