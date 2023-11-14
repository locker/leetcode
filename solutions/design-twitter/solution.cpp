#include <iostream>
#include <deque>
#include <queue>
#include <set>
#include <unordered_map>
#include <utility>
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

class Twitter {
private:
	static constexpr int MAX_TWEETS_PER_USER = 10;

	int time;

	struct Tweet {
		int id;
		int time;
		Tweet(int i, int t) : id(i), time(t) {}
	};

	struct User {
		int id;
		deque<Tweet> tweets; // sorted by time, descending
	};

	struct UserTweets {
		int pos;
		const User* user;

		UserTweets(const User& u) : pos(0), user(&u) {}

		bool operator<(const UserTweets& other) const {
			return user->tweets[pos].time <
				other.user->tweets[other.pos].time;
		}
	};

	unordered_map<int, User> users;

	// follower_id, followee_id
	set<pair<int, int>> followers;
public:
	Twitter() {}

	void postTweet(int user_id, int tweet_id) {
		auto& user = users[user_id];
		user.id = user_id;
		if (user.tweets.size() == MAX_TWEETS_PER_USER)
			user.tweets.pop_back();
		user.tweets.emplace_front(tweet_id, ++time);
	}

	vector<int> getNewsFeed(int user_id) {
		priority_queue<UserTweets> q;
		auto users_it = users.find(user_id);
		if (users_it != users.end())
			q.emplace(users_it->second);
		for (auto it = followers.lower_bound(make_pair(user_id, 0));
		     it != followers.end() && it->first == user_id; ++it) {
			users_it = users.find(it->second);
			if (users_it != users.end())
				q.emplace(users_it->second);
		}
		vector<int> tweets;
		tweets.reserve(MAX_TWEETS_PER_USER);
		while (!q.empty() && tweets.size() < MAX_TWEETS_PER_USER) {
			auto p = q.top();
			const auto& user_tweets = p.user->tweets;
			q.pop();
			tweets.push_back(user_tweets[p.pos].id);
			++p.pos;
			if ((unsigned)p.pos < user_tweets.size())
				q.push(p);
		}
		return tweets;
	}

	void follow(int follower_id, int followee_id) {
		followers.emplace(follower_id, followee_id);
	}

	void unfollow(int follower_id, int followee_id) {
		followers.erase(make_pair(follower_id, followee_id));
	}
};

bool success = true;

Twitter testCreate()
{
	cout << "Twitter()" << endl;
	return Twitter();
}

void testPostTweet(Twitter& twitter, int user_id, int tweet_id)
{
	cout << "postTweet(" << user_id << ", " << tweet_id << ")" << endl;
	twitter.postTweet(user_id, tweet_id);
}

void testGetNewsFeed(Twitter& twitter, int user_id, vector<int> expected)
{
	auto result = twitter.getNewsFeed(user_id);
	cout << "getNewsFeed(" << user_id << ") = " << result << endl;
	if (result != expected) {
		cout << "  ERROR: wrong result, expected " << expected << endl;
		success = false;
	}
}

void testFollow(Twitter& twitter, int follower_id, int followee_id) {
	cout << "follow(" << follower_id << ", " << followee_id << ")" << endl;
	twitter.follow(follower_id, followee_id);
}

void testUnfollow(Twitter& twitter, int follower_id, int followee_id) {
	cout << "unfollow(" << follower_id << ", " << followee_id << ")" << endl;
	twitter.unfollow(follower_id, followee_id);
}

} // namespace

int main()
{
	{
		auto t = testCreate();
		testGetNewsFeed(t, 1, {});
	}
	{
		auto t = testCreate();
		testPostTweet(t, 1, 5);
		testGetNewsFeed(t, 1, {5});
		testFollow(t, 1, 2);
		testPostTweet(t, 2, 6);
		testGetNewsFeed(t, 1, {6, 5});
		testUnfollow(t, 1, 2);
		testGetNewsFeed(t, 1, {5});
	}
	{
		auto t = testCreate();
		for (int i = 0; i < 15; ++i)
			testPostTweet(t, 1, i + 100);
		testGetNewsFeed(t, 1, {
			114, 113, 112, 111, 110, 109, 108, 107, 106, 105,
		});
		for (int i = 0; i < 15; ++i)
			testPostTweet(t, 2, i + 200);
		testGetNewsFeed(t, 2, {
			214, 213, 212, 211, 210, 209, 208, 207, 206, 205,
		});
		testFollow(t, 1, 2);
		testFollow(t, 2, 1);
		testGetNewsFeed(t, 1, {
			214, 213, 212, 211, 210, 209, 208, 207, 206, 205,
		});
		testGetNewsFeed(t, 1, {
			214, 213, 212, 211, 210, 209, 208, 207, 206, 205,
		});
	}
	{
		auto t = testCreate();
		testFollow(t, 1, 2);
		testPostTweet(t, 1, 1);
		testPostTweet(t, 2, 2);
		testPostTweet(t, 1, 3);
		testPostTweet(t, 2, 4);
		testGetNewsFeed(t, 1, {4, 3, 2, 1});
		testGetNewsFeed(t, 2, {4, 2});
		testFollow(t, 2, 1);
		testGetNewsFeed(t, 2, {4, 3, 2, 1});
	}
	{
		auto t = testCreate();
		testPostTweet(t, 1, 1);
		testGetNewsFeed(t, 1, {1});
		testFollow(t, 2, 1);
		testGetNewsFeed(t, 2, {1});
		testUnfollow(t, 2, 1);
		testGetNewsFeed(t, 2, {});
	}
	return success ? 0 : 1;
}
