#include <bits/stdc++.h>
using namespace std;

int main() {
//   freopen("CF698\\B.in", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int q, d;
    cin >> q >> d;
    while (q--) {
      int tmp;
      cin >> tmp;
      if (tmp / d >= 10 || tmp % d == 0) {
        cout << "YES\n";
      } else {
        bool flag = false;
        while (tmp > 0) {
          if (tmp % d == 0) {
            flag = true;
            break;
          }
          tmp -= 10;
        }
        if (flag)
          cout << "YES\n";
        else
          cout << "NO\n";
      }
    }
  }
  return 0;
}