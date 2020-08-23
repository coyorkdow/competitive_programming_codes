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
  T last = 1;
  for (T i = 1; i <= y; i <<= 1, x = x * x % mod)
    if (i & y) last = last * x % mod;
  return last;
}
template <typename T>
inline T mul(T x, T y, T mod = numeric_limits<T>::max()) {
  if (mod == 1) return 0;
  T last = 0;
  for (T i = 1; i <= y; i <<= 1, x = x * 2 % mod)
    if (i & y) last = (last + x) % mod;
  return last;
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

vector<int> manacher(const string &s, string &fix) {
  int l = 1;
  string String(s.length() * 2 + 2, '$');
  String[l++] = '#';
  for (int i = 0; i < s.length(); i++) {
    String[l++] = s[i];
    String[l++] = '#';
  }
  assert(l == String.length());
  vector<int> cnt(l);
  int MaxR = 0;
  int flag = 0;
  for (int i = 0; i < l; i++) {
    cnt[i] = MaxR > i ? min(cnt[2 * flag - i], MaxR - i) : 1;
    while (String[i + cnt[i]] == String[i - cnt[i]]) cnt[i]++;
    if (i + cnt[i] > MaxR) {
      MaxR = i + cnt[i];
      flag = i;
    }
  }
  fix = String;
  return cnt;
}
int main() {
  quickio;
  int T;
  cin >> T;
  while (T--) {
    string str;
    cin >> str;
    string fix;
    vector<int> cnt = manacher(str, fix);
    str = fix.substr(1);
    vector<bool> pali(str.length());
    for (int i = 0, j = str.length() - 1; i < str.length() / 2; i++, j--) {
      if (str[i] != str[j]) break;
      pali[i] = true;
    }
    vector<int> radius;
    radius.reserve(str.length());
    for (int i = 1; i < cnt.size(); i++) {
      radius.push_back(cnt[i]);
    }
    assert(radius.size() == str.length());
    auto cal = [&]() {
      int len = 0;
      int l, r;
      for (int i = 0; i < str.length(); i++) {
        int bord = i - radius[i];
        if (bord < 0) {
          if (chkmax(len, radius[i] * 2 - 1)) {
            l = i + radius[i] - 1, r = INT_MAX;
          }
        } else {
          int bordR = i + radius[i];
          if (pali[bord] && str.length() - bordR >= bord + 1) {
            if (chkmax(len, i + radius[i] + (bord + 1))) {
              l = i + radius[i] - 1, r = str.length() - bord - 1;
            }
          }
        }
      }
      string a = str.substr(0, l + 1);
      string b = r == INT_MAX ? "" : str.substr(r);
      if (a.length() + b.length() < str.length() &&
          (a.length() + b.length()) % 2 == 0) {
        a += str[l + 1];
      }
      string S;
      for (char i : a) {
        if (!islower(i)) continue;
        S += i;
      }
      for (char i : b) {
        if (!islower(i)) continue;
        S += i;
      }
      return S;
    };
    string s1 = cal();
    reverse(all(str));
    reverse(all(radius));
    string s2 = cal();
    if (s1.length() > s2.length())
      cout << s1 << endl;
    else
      cout << s2 << endl;
  }
  return 0;
}