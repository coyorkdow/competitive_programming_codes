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
template <typename T>
class segment_tree {
 private:
  struct ele {
    T mininum = 1e9, maxinum = -1e9;
  };
  vector<ele> tree;

 public:
  int size;
  int nil = 1e9;
  segment_tree(int n) : size(n) { tree.resize(4 * n + 5); }
  void modify(const int l, const int r, const T value, int __l = 1,
              int __r = -1, int k = 1) {
    if (__r == -1) __r = size;
    if (__l >= l && __r <= r) {
      tree[k].mininum = value;
      tree[k].maxinum = value == nil ? -1e9 : value;
      return;
    }
    int mid = (__l + __r) >> 1;
    if (r > mid) modify(l, r, value, mid + 1, __r, k << 1 | 1);
    if (l <= mid) modify(l, r, value, __l, mid, k << 1);
    tree[k].maxinum = max(tree[k << 1].maxinum, tree[k << 1 | 1].maxinum);
    tree[k].mininum = min(tree[k << 1].mininum, tree[k << 1 | 1].mininum);
  }
  pair<T, T> query(const int l, const int r, int __l = 1, int __r = -1,
                   int k = 1) {
    if (__r == -1) __r = size;
    if (__l >= l && __r <= r)
      return make_pair(tree[k].mininum, tree[k].maxinum);
    int mid = (__l + __r) >> 1;
    pair<T, T> ans = make_pair(1e9, -1e9);
    if (r > mid) ans = query(l, r, mid + 1, __r, k << 1 | 1);
    if (l <= mid) {
      pair<T, T> tmp = query(l, r, __l, mid, k << 1);
      ans.first = min(ans.first, tmp.first);
      ans.second = max(ans.second, tmp.second);
    }
    return ans;
  }
};

int main() {
  quickio;
  int n;
  cin >> n;
  vector<int> P0(n), P1(n), pos(n + 1);
  cin >> P0 >> P1;
  segment_tree<int> seg(n);
  set<int> arr, bombs;
  for (int i = 0; i < n - 1; i++) bombs.insert(P0[P1[i] - 1]);
  for (int i = 0; i < n; i++) pos[P0[i]] = i + 1;
  for (int i = 0; i < n; i++) {
    arr.insert(P0[i]);
    if (bombs.count(P0[i])) {
      seg.modify(i + 1, i + 1, *arr.rbegin());
      arr.erase(*arr.rbegin());
    }
  }
  // cout << seg.query(1, n).first << endl;
  vector<int> ans;
  ans.reserve(n);
  ans.push_back(*arr.rbegin());
  // cout << *arr.rbegin() << ' ';
  for (int i = n - 2; i >= 0; i--) {
    int mini = seg.query(P1[i], n).first;
    if (mini != 1e9) {
      seg.modify(pos[mini], pos[mini], 1e9);
      arr.insert(mini);
    } else {
      int maxi = seg.query(1, P1[i]).second;
      seg.modify(pos[maxi], pos[maxi], 1e9);
      arr.insert(maxi);
    }
    ans.push_back(*arr.rbegin());
    // cout << *arr.rbegin() << ' ';
  }
  reverse(all(ans));
  cout << ans;
  return 0;
}