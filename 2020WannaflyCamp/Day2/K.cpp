// #pragma comment(linker, "/stack:200000000")
// #pragma GCC optimize("Ofast")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
using namespace __gnu_pbds;
#define all(x) x.begin(), x.end()
#define revall(x) x.rbegin(), x.rend()
#define mem(a, x) memset(a, x, sizeof a)
#define precision(n) std::fixed << std::setprecision(n)
#define quickio                     \
  std::ios::sync_with_stdio(false); \
  std::cin.tie(0), std::cout.tie(0)
#define ednl '\n'
#define endl '\n'
#define sep << ' ' <<
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
typedef std::pair<ull, ull> pull;
typedef std::pair<ll, ll> pll;
using namespace std;
template <typename T>
inline T power(T x, T y, T mod = (int)1e9 + 7) {
  if (mod == 0) return 0;
  T tmp = 1;
  for (T i = 1; i <= y; i <<= 1, x = x * x % mod)
    if (i & y) tmp = tmp * x % mod;
  return tmp;
}
template <typename T>
inline T mul(T x, T y, T mod = (int)1e9 + 7) {
  if (mod == 0) return 0;
  T tmp = 0;
  for (T i = 1; i <= y; i <<= 1, x = x * 2 % mod)
    if (i & y) tmp = (tmp + x) % mod;
  return tmp;
}
template <typename T>
inline bool amax(T &x, const T &y) {
  if (x < y) {
    x = y;
    return true;
  };
  return false;
}
template <typename T>
inline bool amin(T &x, const T &y) {
  if (x > y) {
    x = y;
    return true;
  }
  return false;
}
template <class T>
istream &operator>>(istream &is, vector<T> &v) {
  for (T &x : v) is >> x;
  return is;
}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  if (!v.empty()) {
    os << v.front();
    for (int i = 1; i < v.size(); ++i) os << ' ' << v[i];
  }
  return os;
}
namespace FastInput {
const int SIZE = 1 << 16;
char buf[SIZE], str[60];
int bi = SIZE, bn = SIZE;
inline int read(char *s) {
  while (bn) {
    while (bi < bn && buf[bi] <= ' ') bi++;
    if (bi < bn) break;
    bn = fread(buf, 1, SIZE, stdin), bi = 0;
  }
  int sn = 0;
  while (bn) {
    for (; bi < bn && buf[bi] > ' '; bi++) s[sn++] = buf[bi];
    if (bi < bn) break;
    bn = fread(buf, 1, SIZE, stdin), bi = 0;
  }
  s[sn] = 0;
  return sn;
}
template <typename T>
inline bool read(T &x) {
  int n = read(str), bf;
  if (!n) return 0;
  int i = 0;
  if (str[i] == '-')
    bf = -1, i++;
  else
    bf = 1;
  T div = 0;
  for (x = 0; i < n; i++) {
    if (str[i] == '.')
      div = 1;
    else
      x = x * 10 + str[i] - '0', div *= 10;
  }
  if (bf < 0) x = -x;
  if (div) x /= div;
  return 1;
}
struct IO {
  template <typename T>
  IO &operator>>(T &__y) {
    read(__y);
    return *this;
  }
} input;
};  // namespace FastInput
class aho_corasick {
 public:
  vector<vector<int>> trie;
  vector<int> fail;
  vector<pii> word;
  aho_corasick() {
    trie.push_back(vector<int>(26));
    word.push_back(pii(0, 0));
  }
  void insert(const string &str, int w) {
    int u = 0;
    for (auto &i : str) {
      if (!trie[u][i - 'a']) {
        trie[u][i - 'a'] = trie.size();
        trie.push_back(vector<int>(26));
        word.push_back(pii(0, 0));
      }
      u = trie[u][i - 'a'];
    }
    if (word[u] == pii(0, 0))
      word[u] = {str.length(), w};
    else if (word[u].second > w)
      word[u] = {str.length(), w};
  }
  void build() {
    fail.resize(trie.size());
    queue<int> q;
    for (int i = 0; i < 26; i++)
      if (trie[0][i]) q.push(trie[0][i]);
    while (q.size()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i < 26; i++) {
        if (trie[u][i])
          fail[trie[u][i]] = trie[fail[u]][i], q.push(trie[u][i]);
        else
          trie[u][i] = trie[fail[u]][i];
      }
    }
  }
};
int main() {
  quickio;
  int n;
  cin >> n;
  int w;
  string str;
  aho_corasick AC;
  for (int i = 0; i < n; i++) {
    cin >> str >> w;
    AC.insert(str, w);
  }
  AC.build();
  cin >> str;
  // fill(cost, cost + str.length() + 1, 1e18);
  vector<ll> cost(str.length() + 1, 1e18);
  cost[0] = 0;
  int u = 0;
  for (int i = 0; str[i]; i++) {
    u = AC.trie[u][str[i] - 'a'];
    for (int j = u; j; j = AC.fail[j]) {
      if (AC.word[j] != pii(0, 0)) {
        // jmp[i - word[j].first + 1].push_back(j);
        amin(cost[i + 1], cost[i + 1 - AC.word[j].first] + AC.word[j].second);
      }
    }
  }
  if (cost[str.length()] == 1e18)
    cout << -1 << endl;
  else
    cout << cost[str.length()] << endl;
  return 0;
}
