#include <iostream>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int a1, a2, a3;
  int b1, b2, b3;
  int n;
  cin >> a1 >> a2 >> a3;
  cin >> b1 >> b2 >> b3;
  cin >> n;
  int a = a1 + a2 + a3, b = b1 + b2 + b3;
  int num = (a / 5 + (a % 5 ? 1 : 0)) + (b / 10 + (b % 10 ? 1 : 0));
  if (num <= n) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }
}