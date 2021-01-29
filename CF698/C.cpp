#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

#define FAIL             \
  do {                   \
    cout << "NO\n";      \
    if (T == 0) exit(0); \
    T--;                 \
    goto __continue;     \
  } while (0)

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
  __continue:
    int n;
    cin >> n;
    map<int64, int, greater<int64>> container;
    // vector<int64> debug(2 * n);
    for (int i = 0; i < 2 * n; i++) {
      int64 tmp;
      cin >> tmp;
      // debug[i] = tmp;
      container[tmp]++;
    }
    // if (n == 10 && debug.front() == 4941830) {
    //   for (auto& i : debug) cout << i << endl;
    // }
    int64 base = 0;
    int64 pre = 1e18;
    int cnt = 2 * n;
    for (auto each : container) {
      if (each.second != 2) FAIL;
      if (each.first <= base) FAIL;
      int64 cur = (each.first - base) / cnt;
      if (cur * cnt != each.first - base) FAIL;
      if (cur >= pre) FAIL;
      pre = cur;
      base += cur * each.second;
      cnt -= each.second;
    }
    if (cnt == 0)
      cout << "YES\n";
    else
      cout << "NO\n";
  }
  return 0;
}