#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

namespace {

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << "[";
	bool first = true;
	for (const auto& x : v) {
		if (!first)
			out << ',';
		first = false;
		out << x;
	}
	out << "]";
	return out;
}

template<typename Iterator>
class Merger {
private:
	struct MergeSource {
		Iterator it_, end_;
		MergeSource(Iterator begin, Iterator end) :
			it_(begin), end_(end) {}
		bool operator<(const MergeSource& other) const {
			return *it_ > *other.it_;
		}
	};
	size_t output_size_ = 0;
	size_t source_count_ = 0;
	priority_queue<MergeSource> sources_;
public:
	Merger(Iterator begin, Iterator end) {
		push_source(begin, end);
	}

	void push_source(Iterator begin, Iterator end) {
		output_size_ += end - begin;
		++source_count_;
		sources_.emplace(begin, end);
	}

	size_t source_count() const { return source_count_; }

	size_t output_size() const { return output_size_; }

	bool has_next() const {
		return !sources_.empty();
	}

	auto next() {
		auto src = move(sources_.top());
		sources_.pop();
		auto it = src.it_++;
		if (src.it_ != src.end_)
			sources_.push(move(src));
		return *it;
	}
};


class LSM {
private:
	static constexpr int level_grow_coef = 4;
	static constexpr int level0_max_size = 128;

	vector<long long> level0_;
	vector<vector<long long>> levels_;

	void merge() {
		sort(level0_.begin(), level0_.end());
		Merger merger(level0_.begin(), level0_.end());
		for (int i = levels_.size() - 1; i >= 0; --i) {
			auto& level = levels_[i];
			if (level.size() >
			    merger.output_size() * level_grow_coef)
				break;
			merger.push_source(level.begin(), level.end());
		}
		vector<long long> new_level;
		new_level.reserve(merger.output_size());
		while (merger.has_next())
			new_level.push_back(merger.next());
		level0_.clear();
		levels_.resize(levels_.size() - (merger.source_count() - 1));
		levels_.push_back(move(new_level));
	}
public:
	LSM() {
		level0_.reserve(level0_max_size);
	}

	void push(long long v) {
		level0_.push_back(v);
		if (level0_.size() == level0_max_size)
			merge();
	}

	int count(long long lower, long long upper) const {
		int count = count_if(
			level0_.begin(), level0_.end(),
			[lower, upper](long long v) {
				return v >= lower && v <= upper;
			});
		for (const auto& level : levels_) {
			auto lower_it = lower_bound(level.begin(), level.end(),
						    lower);
			auto upper_it = upper_bound(level.begin(), level.end(),
						    upper);
			count += upper_it - lower_it;
		}
		return count;
	}
};

class Solution {
public:
	int countRangeSum(const vector<int>& nums, int lower, int upper) {
		LSM sums;
		int count = 0;
		long long sum = 0;
		for (int n : nums) {
			sum += n;
			if (sum >= lower && sum <= upper)
				++count;
			count += sums.count(sum - upper, sum - lower);
			sums.push(sum);
		}
		return count;
	}
};

} // namespace

int main()
{
	const tuple<vector<int>, int, int, int> test_data[] = {
		{{0}, 0, 0, 1},
		{{1}, 0, 0, 0},
		{{1, -1}, 0, 0, 1},
		{{-2, 5, -1}, -2, 2, 3},
		{{-2147483647,0,-2147483647,2147483647}, -564, 3864, 3},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums, lower, upper, expected] : test_data) {
		int result = solution.countRangeSum(nums, lower, upper);
		cout << "nums = " << nums << ", lower = " << lower <<
			", upper = " << upper << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	const tuple<string, int, int, int> file_test_data[] = {
		{"input/nums1.txt", -5733, 87456, 159986170},
	};
	for (const auto& [filename, lower, upper, expected] : file_test_data) {
		vector<int> nums;
		fstream f(filename, ios::in);
		while (true) {
			int n;
			if (!(f >> n))
				break;
			nums.push_back(n);
		}
		f.close();
		int result = solution.countRangeSum(nums, lower, upper);
		cout << "nums = " << filename << ", lower = " << lower <<
			", upper = " << upper << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
