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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    vector<int> cnt(26);
    int n;
    cin >> n;
    vector<string> arr(n);
    for (auto& i : arr) {
      cin >> i;
      for (auto& j : i) cnt[j - 'a']++;
    }
    bool check = false;
    for (int i : cnt) {
      if (i % n) {
        check = true;
      }
    }
    if (!check)
      cout << "YES\n";
    else
      cout << "NO\n";
  }

  return 0;
}