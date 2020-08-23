#include <iostream>
#include <set>
#include <string>
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
    string str;
    cin >> str;
    vector<int> tag(n);
    set<int> zero, one;
    int num = 0;
    for (int i = 0; i < n; i++) {
      if (str[i] == '0') {
        if (!one.empty()) {
          tag[i] = tag[*one.begin()];
          one.erase(one.begin());
        } else {
          tag[i] = ++num;
        }
        zero.insert(i);
      } else {
        if (!zero.empty()) {
          tag[i] = tag[*zero.begin()];
          zero.erase(zero.begin());
        } else {
          tag[i] = ++num;
        }
        one.insert(i);
      }
    }
    cout << num << endl;
    for (auto i : tag) cout << i << ' ';
    cout << endl;
  }

  return 0;
}