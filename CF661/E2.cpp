#include <iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<functional>
#include<queue>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(a) a.begin(), a.end()
struct edge {
  int id, c, siz;
  ll w;
  bool operator<(const edge& __y) const {
    return (w - w / 2) * siz < (__y.w - __y.w / 2) * __y.siz;
  }
};

int slove() {
  int n;
  ll S;
  cin >> n >> S;
  vector<int> weight(n - 1), C(n - 1);
  vector<vector<pii>> T(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v, w, c;
    cin >> u >> v >> w >> c;
    u--, v--;
    T[u].push_back({v, i});
    T[v].push_back({u, i});
    weight[i] = w;
    C[i] = c;
  }
  priority_queue<edge> one, two;
  ll sum = 0;
  function<int(int, int, int)> dfs = [&](int cur, int pre,
                                         int pre_edge) -> int {
    int siz = 0;
    bool is_leaf = true;
    for (auto& i : T[cur]) {
      if (i.first == pre) {
        continue;
      }
      is_leaf = false;
      siz += dfs(i.first, cur, i.second);
    }
    if (is_leaf) {
      siz = 1;
    }
    if (pre_edge == -1) {
      return siz;
    }
    sum += (ll)weight[pre_edge] * siz;
    edge e = edge{pre_edge, C[pre_edge], siz, weight[pre_edge]};
    if (C[pre_edge] == 1) {
      one.push(e);
    } else {
      two.push(e);
    }
    return siz;
  };
  dfs(0, -1, -1);
  int ans = 0;

  auto use_two = [&]() {
    edge t = two.top();
    two.pop();
    ans += 2;
    sum -= (t.w - t.w / 2) * t.siz;
    if (t.w / 2 != 0) {
      two.push(edge{t.id, t.c, t.siz, t.w / 2});
    }
  };

  auto use_one = [&]() {
    edge t = one.top();
    one.pop();
    ans += 1;
    sum -= (t.w - t.w / 2) * t.siz;
    if (t.w / 2 != 0) {
      one.push(edge{t.id, t.c, t.siz, t.w / 2});
    }
  };

  if (one.empty()) {
    while (sum > S) use_two();
  } else if (two.empty()) {
    while (sum > S) use_one();
  } else {
    ans = 1e9;
    vector<ll> one_reduse{sum}, two_reduse{sum};
    ll bak = sum;
    while (one.size()) {
      use_one();
      one_reduse.push_back(sum);
    }
    sum = bak;
    while (two.size()) {
      use_two();
      two_reduse.push_back(sum);
    }
    reverse(all(two_reduse));
    for (int i = 0; i < one_reduse.size(); i++) {
      if (one_reduse[i] <= S) {
        ans = min(ans, i);
        break;
      }
      ll tmp = bak - (one_reduse[i] - S);
      auto it = upper_bound(all(two_reduse), tmp);
      if (it != two_reduse.begin()) {
        ans = min(ans, i + 2 * int(two_reduse.end() - it));
      }
    }
  }

  return ans;
}

int main() {
  freopen("input", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cout << slove() << endl;
  }
  return 0;
}