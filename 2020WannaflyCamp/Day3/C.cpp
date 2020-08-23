#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
const long long mod = 1e9 + 7;
int nei[maxn], a[maxn], a2[maxn][18];
int main() {
  // freopen("text.in","r",stdin);
  int n, m, s, i, j, k, ans, u, v, cnt, s2;
  scanf("%d%d", &n, &m);
  for (i = 1; i <= m; i++) {
    scanf("%d%d", &u, &v);
    nei[u] |= (1 << (v - 1));
    nei[v] |= (1 << (u - 1));
    // printf("%d %d %d %d\n",u,v,nei[u],nei[v]);
  }
  for (s = 1; s < (1 << n); s++) {
    for (i = 0; i < n; i++) {
      if (s & (1 << i)) {
        s2 = nei[i + 1] & s;
        a[s] = (1 + a[s ^ (1 << i)] + a[s2 ^ s ^ (1 << i)]) % mod;
        // printf("%d %d\n",s,a[s]);
        break;
      }
    }
    a2[s][0] = 1;
    for (k = 1; k <= n; k++) {
      a2[s][k] = 1LL * a2[s][k - 1] * a[s] % mod;
    }
  }
  for (k = 1; k <= n; k++) {
    ans = 0;
    for (s = 1; s < (1 << n); s++) {
      cnt = 0;
      for (j = 0; j < n; j++) {
        if (s & (1 << j)) cnt++;
      }
      if ((n - cnt) % 2) {
        ans -= a2[s][k];
        ans = (ans % mod + mod) % mod;
      } else {
        ans += a2[s][k];
        ans %= mod;
      }
    }
    if (ans) {
      printf("%d\n", k - 1);
      return 0;
    }
  }
  return 0;
}
