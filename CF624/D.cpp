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
inline T power(T x, T y, T mod = numeric_limits<T>::max()) {
  if (mod == 1) return 0;
  T res = 1;
  for (T i = 1; i <= y; i <<= 1, x = x * x % mod)
    if (i & y) res = res * x % mod;
  return res;
}
template <typename T>
inline T mul(T x, T y, T mod = numeric_limits<T>::max()) {
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

int main() {
  quickio;
  int T;
  cin >> T;
  vector<vector<int>> multiplies(20001);
  for (int i = 1; i <= 20000; i++) {
    for (int j = i; j < 100000; j += i) multiplies[i].push_back(j);
  }
  while (T--) {
    int a, b, c;
    int ans0, ans1, ans2;
    cin >> a >> b >> c;
    int ans = 1e9;
    for (int i = 1; i <= 20000; i++) {
      for (int j : multiplies[i]) {
        if (j > 20000) break;
        int res = abs(i - a) + abs(j - b);
        auto it = lower_bound(all(multiplies[j]), c);
        int temp;
        if (it == multiplies[j].end()) {
          temp = multiplies[j].back();
        } else if (*it == c) {
          temp = c;
        } else {
          if (it == multiplies[j].begin())
            temp = *it;
          else {
            if (abs(*it - c) < abs(*(it - 1) - c))
              temp = *it;
            else
              temp = *(it - 1);
          }
        }
        assert(j % i == 0 && temp % j == 0);
        if (chkmin(ans, res + abs(temp - c))) {
          ans0 = i, ans1 = j, ans2 = temp;
        }
      }
    }
    cout << ans << endl;
    cout << ans0 sep ans1 sep ans2 << endl;
  }
  return 0;
}