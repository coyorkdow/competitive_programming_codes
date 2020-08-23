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
ll st[405][405][10][10]{};
ll mat[2005][2005]{};
void ST_prework(int n) {
  int t = log(n) / log(2);
  for (int i0 = 0; i0 <= t; i0++) {
    for (int j0 = 0; j0 <= t; j0++) {
      if (i0 + j0 == 0) continue;
      for (int i = 1; i + (1 << i0) - 1 <= n; i++) {
        for (int j = 1; j + (1 << j0) - 1 <= n; j++) {
          if (i0) {
            chkmax(st[i][j][i0][j0],
                   max(st[i][j][i0 - 1][j0],
                       st[i + (1 << (i0 - 1))][j][i0 - 1][j0]));
          } else {
            chkmax(st[i][j][i0][j0],
                   max(st[i][j][i0][j0 - 1],
                       st[i][j + (1 << (j0 - 1))][i0][j0 - 1]));
          }
        }
      }
    }
  }
}

inline ll ST_query(int x1, int y1, int x2, int y2) {
  int k1 = log(x2 - x1 + 1) / log(2);
  int k2 = log(y2 - y1 + 1) / log(2);
  x2 = x2 - (1 << k1) + 1;
  y2 = y2 - (1 << k2) + 1;
  return max(
      st[x1][y1][k1][k2],
      max(st[x1][y2][k1][k2], max(st[x2][y1][k1][k2], st[x2][y2][k1][k2])));
}

int main() {
  quickio;
  int n, m1, m2;
  cin >> n >> m1 >> m2;
  int x1, y1, x2, y2, w;
  for (int i = 0; i < m1; i++) {
    cin >> x1 >> y1 >> x2 >> y2 >> w;
    mat[x1][y1] += w;
    mat[x1][y2 + 1] -= w;
    mat[x2 + 1][y1] -= w;
    mat[x2 + 1][y2 + 1] += w;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++)
      mat[i][j] += mat[i][j - 1] + mat[i - 1][j] - mat[i - 1][j - 1];
  }
  for (int i = 1; i <= n; i += 5) {
    for (int j = 1; j <= n; j += 5) {
      ll mx = 0;
      for (int a = i; a < i + 5; a++)
        for (int b = j; b < j + 5; b++) chkmax(mx, mat[a][b]);
      st[i / 5 + 1][j / 5 + 1][0][0] = mx;
    }
  }
  ST_prework(n / 5 + 3);
  for (int i = 0; i < m2; i++) {
    cin >> x1 >> y1 >> x2 >> y2;
    int _x1 = (x1 / 5) * 5 + 2, _x2 = (x2 / 5) * 5, _y1 = (y1 / 5) * 5 + 2,
        _y2 = (y2 / 5) * 5;
    if (x1 % 5 == 0 || (x1 - 1) % 5 == 0) _x1--;
    if (y1 % 5 == 0 || (y1 - 1) % 5 == 0) _y1--;
    // cout << ST_query(x1, y1, x2, y2) << endl;
    ll _ans = 0;
    if (_x1 <= _x2 && _y1 <= _y2) _ans = ST_query(_x1, _y1, _x2, _y2);
    ll _ans0 = 0;
    for (int k = y1; k <= y2; k++) {
      for (int j = x1; j % 5 != 1; j++) {
        chkmax(_ans0, mat[j][k]);
      }
      for (int j = _x2 * 5 + 1; j <= x2; j++) {
        chkmax(_ans0, mat[j][k]);
      }
    }
  }
  return 0;
}
