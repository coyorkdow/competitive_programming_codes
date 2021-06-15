#include <bits/stdc++.h>
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

ll dp[10][2];
int digits[10]{};
ll dfs(const int pos, const int limit) {
  if (pos == -1) return 0;
  if (~dp[pos][limit]) return dp[pos][limit];
  int maxn = limit ? digits[pos] : 9;
  ll ans = 0;
  for (int i = 0; i <= maxn; i++) {
    if (i) {
      ans += 1 + pos;
    }
    ans += dfs(pos - 1, limit && i == maxn);
  }
  return dp[pos][limit] = ans;
}

int main() {
  //   freopen("in", "r", stdin);
  quickio;
  int T;
  cin >> T;
  while (T--) {
    int l, r;
    cin >> l >> r;
    memset(dp, -1, sizeof(dp));
    int cnt = 0;
    auto split_digit = [](int v) -> int {
      int cnt = -1;
      while (v) {
        cnt++;
        digits[cnt] = v % 10;
        v /= 10;
      }
      return cnt;
    };
    int start = split_digit(l);
    ll lans = dfs(start, 1);
    memset(dp, -1, sizeof(dp));
    start = split_digit(r);
    ll rans = dfs(start, 1);
    cout << rans - lans << endl;
  }
  return 0;
}