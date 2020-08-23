#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  using ll = long long;
  vector<vector<ll>> mat(n, vector<ll>(m));
  for (auto& i : mat) {
    for (auto& j : i) {
      cin >> j;
    }
    for (int j = 0; j < m; j++) {
      i.push_back(i[j]);
    }
  }

  vector<ll> dp(2 * m);
  ll ans = -1e18;
  for (int i = 0; i < n; i++) {
    fill(dp.begin(), dp.end(), 0);
    for (int j = i; j < n; j++) {
      ll sum = 0;
      int bg = 0;

      for (int k = 0; k < 2 * m; k++) {
        if (k - bg >= m) {
          sum -= dp[bg];
          bg++;
          while (bg < k && dp[bg] < 0) {
            sum -= dp[bg];
            bg++;
          }
        }
        dp[k] += mat[j][k];
        sum += dp[k];
        ans = max(ans, dp[k]);
        if (sum <= 0) {
          if (dp[k] < 0) {
            bg = k + 1;
            sum = 0;
          } else {
            bg = k;
            sum = dp[k];
          }
          continue;
        }
        ans = max(ans, sum);
      }
    }
  }
  cout << ans << endl;
  return 0;
}