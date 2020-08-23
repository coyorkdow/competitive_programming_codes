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
#define setprecision(n) std::fixed << std::setprecision(n)
#define quickio                     \
  std::ios::sync_with_stdio(false); \
  std::cin.tie(0), std::cout.tie(0)
#define ednl '\n'
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
typedef std::pair<ull, ull> pull;
typedef std::pair<ll, ll> pll;
template <typename T>
inline T power(T x, T y, T mod = (int)1e9 + 7) {
  if (mod == 0) return 0;
  T ans = 1;
  for (T i = 1; i <= y; i <<= 1, x = x * x % mod)
    if (i & y) ans = ans * x % mod;
  return ans;
}
template <typename T>
inline T mul(T x, T y, T mod = (int)1e9 + 7) {
  if (mod == 0) return 0;
  T ans = 0;
  for (T i = 1; i <= y; i <<= 1, x = x * 2 % mod)
    if (i & y) ans = (ans + x) % mod;
  return ans;
}
namespace FastInput {
const int SIZE = 1 << 16;
char buf[SIZE], str[60];
int bi = SIZE, bn = SIZE;
inline int read(char* s) {
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
inline bool read(T& x) {
  int n = read(str), bf;
  if (!n) return 0;
  int i = 0;
  if (i == '-')
    bf = -1, i++;
  else
    bf = 1;
  T div = 0;
  for (x = 0; i < n; i++) {
    if (i == '.')
      div = 1;
    else
      x = x * 10 + i - '0', div *= 10;
  }
  if (bf < 0) x = -x;
  if (div) x /= div;
  return 1;
}
struct IO {
  template <typename T>
  IO& operator>>(T& __y) {
    read(__y);
    return *this;
  }
} input;
};  // namespace FastInput
using namespace std;
template <typename T>
class segment_tree {
 private:
  struct ele {
    T mininum, maxinum;
  };
  vector<ele> tree;
  vector<T> lazy;
  inline void down(int k) {
    lazy[k << 1] += lazy[k];
    lazy[k << 1 | 1] += lazy[k];
    tree[k << 1].mininum += lazy[k];
    tree[k << 1].maxinum += lazy[k];
    tree[k << 1 | 1].mininum += lazy[k];
    tree[k << 1 | 1].maxinum += lazy[k];
    lazy[k] = 0;
  }

 public:
  int size;
  segment_tree(int n) : size(n) {
    tree.resize(4 * n + 5);
    lazy.resize(4 * n + 5);
  }
  void modify(const int l, const int r, const T value, int __l = 1,
              int __r = -1, int k = 1) {
    if (__r == -1) __r = size;
    if (__l >= l && __r <= r) {
      lazy[k] += value;
      tree[k].mininum += value;
      tree[k].maxinum += value;
      return;
    }
    if (lazy[k] != 0) down(k);
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
    if (lazy[k] != 0) down(k);
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
  string str;
  cin >> str;
  vector<char> cur(n + 1);
  segment_tree<int> tree(n);
  int ptr = 1;
  for (auto& i : str) {
    if (i == 'L')
      ptr = max(ptr - 1, 1);
    else if (i == 'R')
      ptr++;
    else if (i == '(') {
      if (cur[ptr] == ')')
        tree.modify(ptr, n, 2);
      else if (cur[ptr] != '(')
        tree.modify(ptr, n, 1);
      cur[ptr] = '(';
    } else if (i == ')') {
      if (cur[ptr] == '(')
        tree.modify(ptr, n, -2);
      else if (cur[ptr] != ')')
        tree.modify(ptr, n, -1);
      cur[ptr] = ')';
    } else {
      if (cur[ptr] == '(')
        tree.modify(ptr, n, -1);
      else if (cur[ptr] == ')')
        tree.modify(ptr, n, 1);
      cur[ptr] = i;
    }
    auto ans = tree.query(1, n);
    if (ans.first >= 0 && tree.query(n, n).second == 0)
      cout << ans.second << ' ';
    else
      cout << "-1 ";
  }
  return 0;
}