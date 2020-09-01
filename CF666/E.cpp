#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  ll r1, r2, r3, d;
  cin >> n >> r1 >> r2 >> r3 >> d;
  vector<ll> arr(n);
  for (ll& i : arr) cin >> i;
  vector<ll> kill_boss_once(n), kill_boss_twice(n);
  for (int i = 0; i < n; i++) {
    kill_boss_once[i] = r1 * arr[i] + r3;
    kill_boss_twice[i] = min(r1 * (arr[i] + 2), r2 + r1) + 2 * d;
  }
  vector<ll> dp(n, 1e18);
  for (int i = n - 1; i >= 0; i--) {
    if (i == n - 1) {
      dp[i] = min(kill_boss_once[n - 1], kill_boss_twice[n - 1]);
    } else {
      dp[i] = min(dp[i],
                  min(kill_boss_once[i], kill_boss_twice[i]) + d + dp[i + 1]);
    }
    if (i == n - 2) {
      dp[i] = min(dp[i], min(kill_boss_twice[i] + kill_boss_once[i + 1],
                             kill_boss_twice[i] + kill_boss_twice[i + 1] - d));
    }
    if (i < n - 2) {
      dp[i] =
          min(dp[i], kill_boss_twice[i] + kill_boss_twice[i + 1] + dp[i + 2]);
    }
  }
  cout << dp[0] << endl;
  return 0;
}
