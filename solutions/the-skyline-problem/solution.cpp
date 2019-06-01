#include <initializer_list>
#include <iostream>
#include <set>
#include <utility>
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
public:
	vector<vector<int>> getSkyline(const vector<vector<int>>& buildings) {
		// A building is given as a triplet (start, end, height).
		// A point of the skyline is given as a pair (pos, height).
		vector<vector<int>> skyline;

		// Represents a point where a building ends.
		struct BuildingEnd {
			int pos;
			int height;
			BuildingEnd(int p, int h): pos(p), height(h) {}
			bool operator<(const BuildingEnd& other) const {
				return pos < other.pos;
			}
		};

		// Set of buildings that contribute to the skyline.
		// Ordered by the building end position - buildings
		// that end earlier go first.
		set<BuildingEnd> building_ends;

		// Height of the skyline at the current position.
		int skyline_height = 0;

		// Iterate over buildings and draw the skyline.
		auto curr = buildings.begin();
		while (curr != buildings.end() || !building_ends.empty()) {
			if (curr != buildings.end() &&
			    (building_ends.empty() ||
			     building_ends.begin()->pos >= (*curr)[0])) {
				// The building starts before any other
				// building contributing to the skyline
				// ends. Raise the skyline if the building
				// is high enough.
				int start = (*curr)[0];
				int end = (*curr)[1];
				int height = (*curr)[2];
				if (height > skyline_height) {
					// Be careful not to add duplicate
					// positions to the skyline.
					if (skyline.empty() ||
					    skyline.back()[0] != start) {
						skyline.emplace_back(
							initializer_list<int>
							({start, height})
						);
					} else {
						skyline.back()[1] = height;
					}
					skyline_height = height;
				}
				// Remember the new building end position
				// provided it isn't completely overlapped,
				// and remove all buildings overlapped by
				// the new building.
				BuildingEnd b(end, height);
				auto it = building_ends.upper_bound(b);
				if (it == building_ends.begin())
					it = building_ends.end();
				else
					--it;
				while (it != building_ends.end() &&
				       it->height <= height) {
					auto next = it;
					if (next == building_ends.begin())
						next = building_ends.end();
					else
						--next;
					building_ends.erase(it);
					it = next;
				}
				if (it == building_ends.end())
					it = building_ends.begin();
				else
					++it;
				if (it == building_ends.end() ||
				    it->height < height)
					building_ends.insert(it, b);
				// Proceed to the next building.
				++curr;

			} else {
				// The building starts after some building
				// contributing to the skyline ends. Lower
				// the skyline.
				int pos = building_ends.begin()->pos;
				building_ends.erase(building_ends.begin());
				skyline_height = building_ends.empty() ? 0 :
						 building_ends.begin()->height;
				skyline.emplace_back(initializer_list<int>
						     ({pos, skyline_height}));
			}
		}

		return skyline;
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{},

		// [1 10] [5 0]
		{{1, 5, 10}},

		// [1 10] [5 0]
		{{1, 5, 10}, {2, 3, 5}},

		// [0 3] [5 0]
		{{0, 2, 3}, {2, 5, 3}},

		// [1 10] [9 0]
		{{1, 5, 10}, {2, 9, 10}},

		// [2 10] [9 15] [12 0]
		{{2, 9, 10}, {9, 12, 15}},

		// [1 10] [5 5] [9 0]
		{{1, 5, 10}, {2, 9, 5}},

		// [1 5] [5 10] [9 0]
		{{1, 9, 5}, {5, 9, 10}},

		// [1 10] [2 15] [3 10] [5 0]
		{{1, 5, 10}, {2, 3, 15}},

		// [1 10] [5 0] [10 5] [15 0]
		{{1, 5, 10}, {10, 15, 5}},

		// [1 3] [2 0]
		{{1, 2, 1}, {1, 2, 2}, {1, 2, 3}},

		// [2 10] [10 25] [17 14] [20 0]
		{{2, 13, 10}, {10, 17, 25}, {12, 20, 14}},

		// [1 4] [5 0]
		{{1, 4, 1}, {1, 3, 2}, {1, 2, 3}, {1, 5, 4}},

		// [1 5] [4 4] [7 0]
		{{1, 4, 5}, {2, 5, 3}, {3, 6, 2}, {4, 7, 4}},

		// [2 10] [3 15] [7 12] [12 0] [15 10] [20 8] [24 0]
		{{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}},
	};
	Solution solution;
	for (const auto& buildings: input) {
		cout << buildings << " => " <<
			solution.getSkyline(buildings) << endl;
	}
	return 0;
}
