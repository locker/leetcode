#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

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
	vector<string> findItinerary(const vector<vector<string>>& tickets) {
		unordered_map<string, vector<string>> node_dests;
		for (const auto& ticket : tickets)
			node_dests[ticket[0]].push_back(ticket[1]);
		for (auto& [ignore, dests] : node_dests)
			sort(dests.begin(), dests.end(), std::greater<string>());
		vector<string> itinerary;
		vector<string> todo;
		todo.push_back("JFK");
		while (!todo.empty()) {
			string& src = todo.back();
			auto& dests = node_dests[src];
			if (dests.empty()) {
				itinerary.push_back(move(src));
				todo.pop_back();
			} else {
				auto dest = move(dests.back());
				dests.pop_back();
				todo.push_back(dest);
			}
		}
		reverse(itinerary.begin(), itinerary.end());
		return itinerary;
	}
};

int main()
{
	const pair<vector<vector<string>>, vector<string>> test_data[] = {
		{
			{
				{"JFK", "KUL"},
				{"JFK", "NRT"},
				{"NRT", "JFK"},
			},
			{"JFK", "NRT", "JFK", "KUL"},
		},
		{
			{
				{"MUC", "LHR"},
				{"JFK", "MUC"},
				{"SFO", "SJC"},
				{"LHR", "SFO"},
			},
			{"JFK", "MUC", "LHR", "SFO", "SJC"},
		},
		{
			{
				{"JFK", "SFO"},
				{"JFK", "ATL"},
				{"SFO", "ATL"},
				{"ATL", "JFK"},
				{"ATL", "SFO"},
			},
			{"JFK", "ATL", "JFK", "SFO", "ATL", "SFO"},
		},
		{
			{
				{"AXA", "EZE"}, {"EZE", "AUA"}, {"ADL", "JFK"},
				{"ADL", "TIA"}, {"AUA", "AXA"}, {"EZE", "TIA"},
				{"EZE", "TIA"}, {"AXA", "EZE"}, {"EZE", "ADL"},
				{"ANU", "EZE"}, {"TIA", "EZE"}, {"JFK", "ADL"},
				{"AUA", "JFK"}, {"JFK", "EZE"}, {"EZE", "ANU"},
				{"ADL", "AUA"}, {"ANU", "AXA"}, {"AXA", "ADL"},
				{"AUA", "JFK"}, {"EZE", "ADL"}, {"ANU", "TIA"},
				{"AUA", "JFK"}, {"TIA", "JFK"}, {"EZE", "AUA"},
				{"AXA", "EZE"}, {"AUA", "ANU"}, {"ADL", "AXA"},
				{"EZE", "ADL"}, {"AUA", "ANU"}, {"AXA", "EZE"},
				{"TIA", "AUA"}, {"AXA", "EZE"}, {"AUA", "SYD"},
				{"ADL", "JFK"}, {"EZE", "AUA"}, {"ADL", "ANU"},
				{"AUA", "TIA"}, {"ADL", "EZE"}, {"TIA", "JFK"},
				{"AXA", "ANU"}, {"JFK", "AXA"}, {"JFK", "ADL"},
				{"ADL", "EZE"}, {"AXA", "TIA"}, {"JFK", "AUA"},
				{"ADL", "EZE"}, {"JFK", "ADL"}, {"ADL", "AXA"},
				{"TIA", "AUA"}, {"AXA", "JFK"}, {"ADL", "AUA"},
				{"TIA", "JFK"}, {"JFK", "ADL"}, {"JFK", "ADL"},
				{"ANU", "AXA"}, {"TIA", "AXA"}, {"EZE", "JFK"},
				{"EZE", "AXA"}, {"ADL", "TIA"}, {"JFK", "AUA"},
				{"TIA", "EZE"}, {"EZE", "ADL"}, {"JFK", "ANU"},
				{"TIA", "AUA"}, {"EZE", "ADL"}, {"ADL", "JFK"},
				{"ANU", "AXA"}, {"AUA", "AXA"}, {"ANU", "EZE"},
				{"ADL", "AXA"}, {"ANU", "AXA"}, {"TIA", "ADL"},
				{"JFK", "ADL"}, {"JFK", "TIA"}, {"AUA", "ADL"},
				{"AUA", "TIA"}, {"TIA", "JFK"}, {"EZE", "JFK"},
				{"AUA", "ADL"}, {"ADL", "AUA"}, {"EZE", "ANU"},
				{"ADL", "ANU"}, {"AUA", "AXA"}, {"AXA", "TIA"},
				{"AXA", "TIA"}, {"ADL", "AXA"}, {"EZE", "AXA"},
				{"AXA", "JFK"}, {"JFK", "AUA"}, {"ANU", "ADL"},
				{"AXA", "TIA"}, {"ANU", "AUA"}, {"JFK", "EZE"},
				{"AXA", "ADL"}, {"TIA", "EZE"}, {"JFK", "AXA"},
				{"AXA", "ADL"}, {"EZE", "AUA"}, {"AXA", "ANU"},
				{"ADL", "EZE"}, {"AUA", "EZE"},
			},
			{
				{
					"JFK", "ADL", "ANU", "ADL", "ANU",
					"AUA", "ADL", "AUA", "ADL", "AUA",
					"ANU", "AXA", "ADL", "AUA", "ANU",
					"AXA", "ADL", "AXA", "ADL", "AXA",
					"ANU", "AXA", "ANU", "AXA", "EZE",
					"ADL", "AXA", "EZE", "ADL", "AXA",
					"EZE", "ADL", "EZE", "ADL", "EZE",
					"ADL", "EZE", "ANU", "EZE", "ANU",
					"EZE", "AUA", "AXA", "EZE", "AUA",
					"AXA", "EZE", "AUA", "AXA", "JFK",
					"ADL", "EZE", "AUA", "EZE", "AXA",
					"JFK", "ADL", "JFK", "ADL", "JFK",
					"ADL", "JFK", "ADL", "TIA", "ADL",
					"TIA", "AUA", "JFK", "ANU", "TIA",
					"AUA", "JFK", "AUA", "JFK", "AUA",
					"TIA", "AUA", "TIA", "AXA", "TIA",
					"EZE", "AXA", "TIA", "EZE", "JFK",
					"AXA", "TIA", "EZE", "JFK", "AXA",
					"TIA", "JFK", "EZE", "TIA", "JFK",
					"EZE", "TIA", "JFK", "TIA", "JFK",
					"AUA", "SYD",
				},
			},
		},
	};
	bool success = true;
	Solution solution;
	for (const auto& [tickets, expected] : test_data) {
		auto result = solution.findItinerary(tickets);
		cout << tickets << " => " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
