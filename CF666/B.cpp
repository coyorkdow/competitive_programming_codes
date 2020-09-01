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

ll power(ll a, ll b) {
  ll ans = 1, tmp = a;
  for (ll i = 1; i <= b; i <<= 1) {
    if (b & i) ans *= tmp;
    if (ans < 0) return ans;
    tmp *= tmp;
    if (tmp < 0) return tmp;
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<ll> arr(n);
  for (ll& i : arr) cin >> i;
  ll ans = 0;
  for (ll& i : arr) ans += i - 1;
  if (arr.size() > 40) {
    cout << ans << endl;
    return 0;
  }
  sort(arr.begin(), arr.end());
  ll cur = (ll)pow((double)arr.back(), 1 / (double)(arr.size() - 1));
  for (ll i = 2; i <= cur + 3; i++) {
    ll res = 0;
    if (power(i, arr.size() - 1) < 0) break;
    for (int j = 0; j < arr.size(); j++) {
      ll p = power(i, j);
      res += abs(p - arr[j]);
    }
    if (res < 0) break;
    ans = min(ans, res);
  }
  cout << ans << endl;
  return 0;
}