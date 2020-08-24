#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, m, k;
  cin >> n >> m >> k;
  ll maxi = n * m;
  auto check = [&](ll x) -> bool {
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
      ll res = x / i;
      sum += min((ll)m, res);
    }
    if (sum < k) return true;
    return false;
  };
  ll l = 1, r = maxi + 1;
  while (l < r) {
    ll mid = (l + r) / 2;
    if (check(mid)) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  cout << l << endl;
  return 0;
}