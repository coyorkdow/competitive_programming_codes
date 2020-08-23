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
  if (mod == 1) return 0;
  T res = 1;
  for (T i = 1; i <= y; i <<= 1, x = x * x % mod)
    if (i & y) res = res * x % mod;
  return res;
}
template <typename T>
inline T mul(T x, T y, T mod = (int)1e9 + 7) {
  if (mod == 1) return 0;
  T res = 0;
  for (T i = 1; i <= y; i <<= 1, x = x * 2 % mod)
    if (i & y) res = (res + x) % mod;
  return res;
}
template <typename T>
inline bool chkmax(T &x, const T &y) {
  if (x < y) {
    x = y;
    return true;
  };
  return false;
}
template <typename T>
inline bool chkmin(T &x, const T &y) {
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
#define GG          \
  {                 \
    cout << "NO\n"; \
    goto nxt;       \
  }
int main() {
  quickio;
  int T;
  cin >> T;
  while (T--) {
    string str;
    cin >> str;
    if (str.size() == 1) {
      cout << "YES\n";
      for (int i = 0; i < 26; i++) cout << char(i + 'a');
      cout << endl;
      continue;
    }
    vector<set<char>> cnt(26);
    for (int i = 1; i < str.size(); i++) {
      cnt[str[i] - 'a'].insert(str[i - 1]);
      cnt[str[i - 1] - 'a'].insert(str[i]);
    }
    int tot = 0;
    string output(26, '\0');
    set<char> S;
    for (int i = 0; i < 26; i++) S.insert('a' + i);
    for (auto &each : cnt)
      if (each.size() > 2) GG;
    for (int i = 0; i < 26; i++) {
      if (cnt[i].size() == 1) output[0] = 'a' + i;
    }
    if (output[0] == '\0') GG;
    // set<char>S
    S.erase(output[0]);
    cnt[*cnt[output[0] - 'a'].begin() - 'a'].erase(output[0]);
    for (int i = 1; i < 26; i++) {
      if (cnt[output[i - 1] - 'a'].size() == 2) {
        GG;
      } else if (cnt[output[i - 1] - 'a'].size() == 1) {
        output[i] = *cnt[output[i - 1] - 'a'].begin();
      } else {
        for (char j : S) {
          if (cnt[j - 'a'].size() < 2) {
            output[i] = j;
            break;
          }
        }
      }
      if (output[i] == '\0') GG;
      S.erase(output[i]);
      if (!cnt[output[i] - 'a'].empty())
        cnt[*cnt[output[i] - 'a'].begin() - 'a'].erase(output[i]);
      if (i == 25 && cnt[output[i] - 'a'].size() == 2) GG;
    }
    for (auto &i : output) tot ^= (1 << (i - 'a'));
    if (tot != (1 << 26) - 1) GG;
    cout << "YES\n";
    cout << output << endl;
  nxt:
    continue;
  }
  return 0;
}