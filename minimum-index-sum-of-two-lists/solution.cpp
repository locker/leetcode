#include <iostream>
#include <functional>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<< (ostream& out, const vector<T>& v) {
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ", ";
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
		unordered_map<string, int> index;
		for (int i = 0; i < static_cast<int>(list1.size()); ++i)
			index.emplace(list1[i], i);

		vector<string> result;
		int min_sum = numeric_limits<int>::max();
		for (int i = 0; i < static_cast<int>(list2.size()); ++i) {
			auto found = index.find(list2[i]);
			if (found == index.end())
				continue;
			int sum = found->second + i;
			if (sum < min_sum) {
				min_sum = sum;
				result.clear();
			}
			if (sum == min_sum)
				result.emplace_back(list2[i]);
		}
		return result;
	}
};

int main()
{
	vector<string> list1{"Shogun", "KFC", "Burger King", "Tapioca Express"};
	vector<string> list2{"KFC", "Shogun", "Burger King"};
	auto result = Solution().findRestaurant(list1, list2);

	cout << "input: " << list1 << ", " << list2 << endl;
	cout << "output: " << result << endl;
	return 0;
}
