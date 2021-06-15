#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define revall(x) x.rbegin(), x.rend()
#define mem(a, x) memset(a, x, sizeof a)
#define precision(n) std::fixed << std::setprecision(n)
#define quickio                     \
  std::ios::sync_with_stdio(false); \
  std::cin.tie(0), std::cout.tie(0)
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
  freopen("in", "r", stdin);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int> arr(n);
    cin >> arr;
    if (arr.size() > 1000) {
      cout << 0 << endl;
      continue;
    }

    assert(arr.size() > 0);

    unordered_set<int> s;
    vector<int> redund;
    for (int i = 1; i <= 1000; i++) s.insert(i);
    for (auto i : arr) {
      if (!s.count(i))
        redund.push_back(i);
      else
        s.erase(i);
    }
    if (redund.size() > 1) {
      cout << 0 << endl;
      continue;
    }
    if (redund.size() == 1) {
      int ans = 0;
      for (auto i : s) {
        if (redund[0] - i != i && s.count(redund[0] - i)) ans = 2;
      }
      cout << ans << endl;
      continue;
    }
    int ans = 0;
    for (auto i : arr) {
      for (auto j : s) {
        if (i - j != j && s.count(i - j)) {
          ans++;
          break;
        }
      }
    }
    cout << ans << endl;
  }
  return 0;
}