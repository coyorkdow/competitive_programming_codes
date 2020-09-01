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
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int& i : arr) cin >> i;
    sort(arr.begin(), arr.end());
    int sum = 0;
    for (int i : arr) sum += i;
    if (sum & 1)
      cout << "T\n";
    else {
      if (arr.back() > sum - arr.back())
        cout << "T\n";
      else
        cout << "HL\n";
    }
  }
  return 0;
}
