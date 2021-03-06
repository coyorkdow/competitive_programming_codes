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
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int> arr[2];
    for (int i = 0; i < n; i++) {
      int tmp;
      cin >> tmp;
      arr[i % 2].push_back(tmp);
    }
    if (__gcd(n, 2) == 1) {
      cout << "Yes\n";
      continue;
    }
    sort(all(arr[0]));
    sort(all(arr[1]));
    int iter[2] = {0, 0};
    bool ok = true;
    vector<int> last;
    for (int i = 0; i < n; i++) {
      last.push_back(arr[i % 2][iter[i % 2]++]);
    }
    for (int i = 1; i < n; i++) {
      if (last[i] < last[i - 1]) ok = false;
    }
    if (ok)
      cout << "Yes\n";
    else
      cout << "No\n";
  }
  return 0;
}