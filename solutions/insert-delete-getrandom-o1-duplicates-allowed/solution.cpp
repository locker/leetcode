#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

namespace std {

template<typename T, typename U>
struct hash<pair<T, U>> {
	size_t operator()(const pair<T, U>& p) const {
		return hash<T>()(p.first) ^ (hash<U>()(p.second) << 1);
	}
};

} // namespace std

namespace {

class RandomizedCollection {
private:
	vector<pair<int, int>> values;
	unordered_map<int, int> value_count;
	unordered_map<pair<int, int>, size_t> value_pos;
public:
	RandomizedCollection() {}

	bool insert(int val) {
		auto [count_it, inserted] = value_count.emplace(val, 0);
		size_t idx = count_it->second++;
		value_pos.emplace(make_pair(val, idx), values.size());
		values.emplace_back(val, idx);
		return inserted;
	}

	bool remove(int val) {
		auto count_it = value_count.find(val);
		if (count_it == value_count.end())
			return false;
		size_t idx = --count_it->second;
		if (idx == 0)
			value_count.erase(count_it);
		auto pos_it = value_pos.find(make_pair(val, idx));
		auto pos = pos_it->second;
		value_pos.erase(pos_it);
		if (pos != values.size() - 1) {
			values[pos] = values.back();
			value_pos[values.back()] = pos;
		}
		values.pop_back();
		return true;
	}

	int getRandom() {
		return values[rand() % values.size()].first;
	}
};

bool success = true;

RandomizedCollection
testCreate(void)
{
	cout << "RandomizedCollection()" << endl;
	return RandomizedCollection();
}

void
testInsert(RandomizedCollection& o, int val, bool expected)
{
	bool ret = o.insert(val);
	cout << "insert(" << val << ") = " << (ret ? "true" : "false") << endl;
	if (ret != expected) {
		cout << "  ERROR: wrong result" << endl;
		success = false;
	}
}

void
testRemove(RandomizedCollection& o, int val, bool expected)
{
	bool ret = o.remove(val);
	cout << "remove(" << val << ") = " << (ret ? "true" : "false") << endl;
	if (ret != expected) {
		cout << "  ERROR: wrong result" << endl;
		success = false;
	}
}

void
testGetRandom(RandomizedCollection& o, int expected)
{
	int val = o.getRandom();
	cout << "getRandom(" << val << ") = " << val << endl;
	if (val != expected) {
		cout << "  ERROR: expected " << expected << endl;
		success = false;
	}
}

} // namespace

int main()
{
	{
		auto o = testCreate();
		testInsert(o, 1, true);
		testRemove(o, 2, false);
		testInsert(o, 2, true);
		testGetRandom(o, 2);
		testRemove(o, 1, true);
		testInsert(o, 2, false);
		testGetRandom(o, 2);
	}
	{
		auto o = testCreate();
		testInsert(o, 0, true);
		testInsert(o, 1, true);
		testRemove(o, 0, true);
		testInsert(o, 2, true);
		testRemove(o, 1, true);
		testGetRandom(o, 2);
	}
	{
		auto o = testCreate();
		testRemove(o, 0, false);
		testRemove(o, 0, false);
		testInsert(o, 0, true);
		testGetRandom(o, 0);
		testRemove(o, 0, true);
		testInsert(o, 0, true);
	}
	{
		auto o = testCreate();
		testInsert(o, 1, true);
		testInsert(o, 1, false);
		testInsert(o, 1, false);
		testInsert(o, 1, false);
		testInsert(o, 2, true);
		testGetRandom(o, 1);
	}
	{
		auto o = testCreate();
		testInsert(o, 1, true);
		testInsert(o, 1, false);
		testInsert(o, 2, true);
		testGetRandom(o, 1);
		testRemove(o, 1, true);
		testGetRandom(o, 1);
		testRemove(o, 1, true);
		testGetRandom(o, 2);
		testRemove(o, 1, false);
		testRemove(o, 2, true);
		testRemove(o, 2, false);
	}
	return success ? 0 : 1;
}
