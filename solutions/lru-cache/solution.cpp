#include <cassert>
#include <iostream>
#include <list>
#include <memory>
#include <unordered_map>

using namespace std;

class LRUCache {
private:
	struct Entry;
	using lru_t = list<Entry*>;
	using kv_t = unordered_map<int, unique_ptr<Entry>>;
	struct Entry {
		int value;
		kv_t::iterator in_kv;
		lru_t::iterator in_lru;
		Entry(int v) : value(v) {}
	};
	const int capacity;
	kv_t kv;
	lru_t lru;
public:
	LRUCache(int capacity_) : capacity(capacity_) {}

	int get(int key) {
		auto it = kv.find(key);
		if (it == kv.end())
			return -1;
		auto& entry = it->second;
		assert(entry->in_kv == it);
		lru.erase(entry->in_lru);
		entry->in_lru = lru.insert(lru.begin(), entry.get());
		return entry->value;
	}

	void put(int key, int value) {
		const int size = kv.size();
		assert(size <= capacity);
		if (capacity == 0)
			return; // trivial
		auto it = kv.find(key);
		if (it != kv.end()) {
			// There's already an entry for the given key.
			// All we need to do is update its value.
			auto& entry = it->second;
			assert(entry->in_kv == it);
			entry->value = value;
			lru.erase(entry->in_lru);
			entry->in_lru = lru.insert(lru.begin(), entry.get());
		} else {
			// There's no entry for the given key.
			// We need to create a new entry, eviciting
			// the oldest one if we are at the capacity.
			if (capacity == size) {
				assert(!lru.empty());
				Entry* entry = lru.back();
				lru.erase(entry->in_lru);
				kv.erase(entry->in_kv); // deletes entry
			}
			auto [it, inserted] = kv.emplace(
				key, make_unique<Entry>(value));
			assert(inserted);
			auto& entry = it->second;
			entry->in_kv = it;
			entry->in_lru = lru.insert(lru.begin(), entry.get());
		}
	}
};

bool success = true;

LRUCache testConstruct(int capacity) {
	cout << "LRUCache(" << capacity << ")" << endl;
	return LRUCache(capacity);
}

void testPut(LRUCache& lru, int key, int value) {
	cout << "put(" << key << ", " << value << ")" << endl;
	lru.put(key, value);
}

void testGet(LRUCache& lru, int key, int expected) {
	int value = lru.get(key);
	cout << "get(" << key << ") = " << value << endl;
	if (value != expected) {
		cout << "  ERROR: expected " << expected << endl;
		success = false;
	}
}

int main()
{
	{
		LRUCache lru = testConstruct(0);
		testGet(lru, 1, -1);
		testPut(lru, 1, 10);
		testGet(lru, 1, -1);
	}
	{
		LRUCache lru = testConstruct(1);
		testGet(lru, 1, -1);
		testPut(lru, 1, 10);
		testGet(lru, 1, 10);
		testPut(lru, 1, 100);
		testGet(lru, 1, 100);
		testPut(lru, 2, 20);
		testGet(lru, 1, -1);
		testGet(lru, 2, 20);
	}
	{
		LRUCache lru = testConstruct(2);
		testPut(lru, 1, 10);
		testPut(lru, 2, 20);
		testGet(lru, 1, 10);
		testPut(lru, 1, 100);
		testGet(lru, 2, 20);
		testGet(lru, 1, 100);
	}
	{
		LRUCache lru = testConstruct(2);
		testPut(lru, 1, 1);
		testPut(lru, 2, 2);
		testGet(lru, 1, 1);
		testPut(lru, 3, 3);
		testGet(lru, 2, -1);
		testPut(lru, 4, 4);
		testGet(lru, 1, -1);
		testGet(lru, 3, 3);
		testGet(lru, 4, 4);
	}
	return success ? 0 : 1;
}
