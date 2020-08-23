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
#define reg register
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
int main() {
  quickio;
  int T;
  cin >> T;
  string get;
  for (int i = 0; i < 10; i++) get += (char)(i + '0');
  for (int i = 0; i < 26; i++) get += (char)(i + 'a');
  for (int i = 0; i < 26; i++) get += (char)(i + 'A');
  while (T--) {
    int r, c, k, rice = 0;
    cin >> r >> c >> k;
    vector<vector<char>> mat(r, vector<char>(c));
    for (auto& i : mat)
      for (auto& j : i) {
        cin >> j;
        if (j == 'R') rice++;
      }
    vector<vector<char>> ans(r, vector<char>(c));
    int res = rice % k, each = rice / k, cur = 0, pos = 0;
    for (int i = 0; i < r; i++) {
      if (i % 2) {
        for (int j = c - 1; j >= 0; j--) {
          if (mat[i][j] == 'R') {
            if (cur == each && res == 0) {
              cur = 0, pos++;
            } else if (cur == each + 1) {
              cur = 0, pos++, res--;
            }
            cur++;
          }
          ans[i][j] = get[pos];
        }
      } else {
        for (int j = 0; j < c; j++) {
          if (mat[i][j] == 'R') {
            if (cur == each && res == 0) {
              cur = 0, pos++;
            } else if (cur == each + 1) {
              cur = 0, pos++, res--;
            }
            cur++;
          }
          ans[i][j] = get[pos];
        }
      }
    }
    for (auto& i : ans) {
      for (auto& j : i) cout << j;
      cout << endl;
    }
  }
  return 0;
}