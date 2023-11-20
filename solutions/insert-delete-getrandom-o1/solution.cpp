#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

namespace {

class RandomizedSet {
private:
	vector<int> values;
	unordered_map<int, size_t> value_pos;
public:
	RandomizedSet() {}

	bool insert(int val) {
		auto ret = value_pos.insert(make_pair(val, values.size()));
		if (!ret.second)
			return false;
		values.push_back(val);
		return true;
	}

	bool remove(int val) {
		auto it = value_pos.find(val);
		if (it == value_pos.end())
			return false;
		size_t pos = it->second;
		value_pos.erase(it);
		if (pos != values.size() - 1) {
			values[pos] = values.back();
			value_pos[values.back()] = pos;
		}
		values.pop_back();
		return true;
	}

	int getRandom() {
		return values[rand() % values.size()];
	}
};

bool success = true;

RandomizedSet
testCreate(void)
{
	cout << "RandomizedSet()" << endl;
	return RandomizedSet();
}

void
testInsert(RandomizedSet& o, int val, bool expected)
{
	bool ret = o.insert(val);
	cout << "insert(" << val << ") = " << (ret ? "true" : "false") << endl;
	if (ret != expected) {
		cout << "  ERROR: wrong result" << endl;
		success = false;
	}
}

void
testRemove(RandomizedSet& o, int val, bool expected)
{
	bool ret = o.remove(val);
	cout << "remove(" << val << ") = " << (ret ? "true" : "false") << endl;
	if (ret != expected) {
		cout << "  ERROR: wrong result" << endl;
		success = false;
	}
}

void
testGetRandom(RandomizedSet& o, int expected)
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
	return success ? 0 : 1;
}
