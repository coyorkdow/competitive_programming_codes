#include <bits/stdc++.h>
using namespace std;

int main() {
  //freopen("CF698\\A.in", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int> que;
    for (int i = 0; i < n; i++) {
      int each;
      cin >> each;
      if (que.empty())
        que.push_back(each);
      else {
        bool flag = false;
        for (int& i : que) {
          if (i < each) {
            i = each;
            flag = true;
            break;
          }
        }
        if (!flag) que.push_back(each);
        sort(que.begin(), que.end());
      }
    }
    cout << que.size() << endl;
  }
  return 0;
}