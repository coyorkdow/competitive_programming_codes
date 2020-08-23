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
int main() {
  quickio;
  int n;
  cin >> n;
  map<pii, vector<int>> rec;
  for (int i = 0; i < n - 2; i++) {
    int tuple[3];
    cin >> tuple[0] >> tuple[1] >> tuple[2];
    sort(tuple, tuple + 3);
    rec[pii(tuple[0], tuple[1])].push_back(tuple[2]);
    rec[pii(tuple[0], tuple[2])].push_back(tuple[1]);
    rec[pii(tuple[1], tuple[2])].push_back(tuple[0]);
  }
  list<int> ans;
  vector<bool> chk(n + 1);
  auto bak = rec;
  for (auto& i : rec) {
    if (i.second.size() == 2) {
      chk[i.first.first] = true;
      chk[i.first.second] = true;
      chk[i.second[0]] = true;
      chk[i.second[1]] = true;
      ans.insert(ans.end(), i.first.first);
      ans.insert(ans.end(), i.first.second);
      ans.push_back(i.second[0]);
      ans.push_front(i.second[1]);
      rec.erase(i.first);
      break;
    }
  }
nxt:
  while (!rec.empty()) {
    auto it = ans.end();
    int a = *--it, b = *--it;
    if (a > b) swap(a, b);
    int cnt = 0;
    auto i = rec.find(pii(a, b));
    if (i != rec.end()) {
      cnt++;
      if (chk[i->second.back()]) i->second.pop_back();
      if (i->second.size() && chk[i->second.back()]) i->second.pop_back();
      if (i->second.size()) {
        ans.push_back(i->second.back());
        chk[i->second.back()] = true;
        i->second.pop_back();
      }
      if (i->second.empty()) rec.erase(i);
    }
    it = ans.begin();
    a = *it, b = *++it;
    if (a > b) swap(a, b);
    i = rec.find(pii(a, b));
    if (i != rec.end()) {
      cnt++;
      if (chk[i->second.back()]) i->second.pop_back();
      if (i->second.size() && chk[i->second.back()]) i->second.pop_back();
      if (i->second.size()) {
        ans.push_front(i->second.back());
        chk[i->second.back()] = true;
        i->second.pop_back();
      }
      if (i->second.empty()) rec.erase(i);
    }
    if (!cnt) break;
  }
  if (ans.size() != n) {
    ans.clear();
    fill(all(chk), false);
    rec = bak;
    for (auto& i : rec) {
      if (i.second.size() == 2) {
        chk[i.first.first] = true;
        chk[i.first.second] = true;
        chk[i.second[0]] = true;
        chk[i.second[1]] = true;
        ans.insert(ans.end(), i.first.first);
        ans.insert(ans.end(), i.first.second);
        ans.push_back(i.second[1]);
        ans.push_front(i.second[0]);
        rec.erase(i.first);
        break;
      }
    }
    goto nxt;
  }
  for (auto& i : ans) cout << i << ' ';
  return 0;
}