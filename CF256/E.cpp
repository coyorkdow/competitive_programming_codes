#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, k;
  cin >> n >> k;
  if (k == 0) {
    cout << n << endl;
    return 0;
  }
  vector<ll> ans;
  ans.reserve((int)1e5);

  map<ll, vector<ll>> div;
  map<ll, bool> exist;
  ll sqt = sqrt(n);
  for (ll i = 1; i <= sqt; i++) {
    if (n % i == 0) {
      div[n].push_back(i);
      exist[i] = true;
    }
  }
  for (ll i = sqt * sqt == n ? sqt - 1 : sqt; i >= 1; i--) {
    if (n % i == 0) {
      div[n].push_back(n / i);
      exist[n / i] = true;
    }
  }
  exist.erase(n);
  for (ll i : div[n]) {
    for (auto j : exist) {
      if (j.first % i == 0) {
        div[j.first].push_back(i);
      }
    }
  }

  function<void(ll, int)> dfs = [&](ll cur, int _k) {
    if (_k == k || cur == 1) {
      ans.push_back(cur);
      return;
    }
    ll sqt = sqrt(cur);
    for (ll i : div[cur]) {
      dfs(i, _k + 1);
      if (ans.size() >= (int)1e5) {
        return;
      }
    }
  };

  dfs(n, 0);
  for (int i = 0; i < min((int)ans.size(), (int)1e5); i++) {
    cout << ans[i] << ' ';
  }
  return 0;
}