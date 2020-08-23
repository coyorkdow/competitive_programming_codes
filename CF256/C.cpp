#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;
using pii = pair<int, int>;

int cal(vector<int> arr) {
  int ans = arr.size();
  int mini = arr[0];
  for (auto& i : arr) mini = min(mini, i);
  vector<int> sub;
  int temp_ans = mini;
  for (auto& i : arr) {
    if (i - mini == 0) {
      if (sub.size()) {
        temp_ans += cal(sub);
      }
      sub.clear();
    } else {
      sub.push_back(i - mini);
    }
  }
  if (sub.size()) {
    temp_ans += cal(sub);
  }
  return min(ans, temp_ans);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> arr(n);
  for (auto& i : arr) cin >> i;
  cout << cal(arr) << endl;

  return 0;
}