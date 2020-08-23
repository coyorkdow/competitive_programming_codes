#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
const ll N = 1e3 + 5;
int n, m;
struct node {
  int x, y;
} a[N];
string s[N];
string code(string t1, string t2) {
  if (t1.length() < t2.length()) {
    int len = t1.length();
    for (int i = t1.length(); i < t2.length(); i++) {
      t1.push_back(t1[i % len]);
    }
  }
  string t;
  // cout<<t1<<' '<<t2<<endl;
  // cout<<t1.length()<<endl;
  for (int i = 0; i < t2.length(); i++) {
    char g2, g1;
    g2 = t2[i];
    g1 = t1[i];
    if (g1 >= 'A' && g1 <= 'Z')
      g1 = g1 - 'A' + 26;
    else
      g1 = g1 - 'a';
    if (g2 >= 'A' && g2 <= 'Z')
      g2 = g2 - 'A' + 26;
    else
      g2 = g2 - 'a';
    // cout<<int(g1)<<' '<<int(g2)<<endl;
    int g = (g2 - g1 + 52) % 52;
    // cout<<g<<endl;
    if (g <= 25)
      t.push_back(char(g + 'a'));
    else
      t.push_back(char(g - 26 + 'A'));
  }
  return t;
}
int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> a[i].x >> a[i].y;
  }
  for (int i = 1; i <= n; i++) {
    cin >> s[i];
  }
  for (int i = m; i >= 1; i--) {
    s[a[i].y] = code(s[a[i].x], s[a[i].y]);
  }
  for (int i = 1; i <= n; i++) {
    cout << s[i] << endl;
  }
  return 0;
}
