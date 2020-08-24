#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string s, t;
  cin >> s >> t;
  vector<vector<bool>> dp(s.size(), vector<bool>(t.size()));
  for (int i = 0; i < s.size(); i++) {
    for (int j = 0; j < t.size(); j++) {
      if (i < j) {
        break;
      }
      if (!i && !j) {
        if (s[i] == t[j]) {
          dp[i][j] = true;
        }
      } else if (!j) {
        if (dp[i - 1][j] || s[i] == t[j]) {
          dp[i][j] = true;
        }
      } else {
        if (dp[i - 1][j] || (dp[i - 1][j - 1] && s[i] == t[j])) {
          dp[i][j] = true;
        }
      }
    }
  }
  if (dp.back().back()) {
    cout << "automaton\n";
    return 0;
  }
  vector<int> s_cnt(26), t_cnt(26);
  for (char c : s) {
    s_cnt[c - 'a']++;
  }
  for (char c : t) {
    t_cnt[c - 'a']++;
  }
  bool check = true;
  for (int i = 0; i < 26; i++) {
    if (s_cnt[i] != t_cnt[i]) {
      check = false;
      break;
    }
  }
  if (check) {
    cout << "array\n";
    return 0;
  }
  check = true;
  for (int i = 0; i < 26; i++) {
    if (s_cnt[i] < t_cnt[i]) {
      check = false;
      break;
    }
  }
  if (check) {
    cout << "both\n";
  } else {
    cout << "need tree\n";
  }
  return 0;
}