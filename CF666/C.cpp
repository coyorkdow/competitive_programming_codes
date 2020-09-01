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
  cin >> n;
  vector<ll> arr(n);
  for (ll& i : arr) cin >> i;
  if (n == 1) {
    cout << 1 << ' ' << 1 << endl;
    cout << -arr[0] << endl;
    cout << 1 << ' ' << 1 << endl;
    cout << 0 << endl;
    cout << 1 << ' ' << 1 << endl;
    cout << 0 << endl;
  } else {
    cout << 1 << ' ' << n << endl;
    for (auto i : arr) cout << -i * n << ' ';
    cout << endl;
    cout << 1 << ' ' << n - 1 << endl;
    for (int i = 0; i < arr.size() - 1; i++) cout << arr[i] * (n - 1) << ' ';
    cout << endl;
    cout << n << ' ' << n << endl;
    cout << -(arr.back() - arr.back() * n) << endl;
  }
  return 0;
}
