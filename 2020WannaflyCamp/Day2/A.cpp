#include <bits/stdc++.h>
using namespace std;  // namespace
const int maxn = 1e6 + 10;
char s[maxn];
double sum[maxn], sum2[maxn];
int ok(char c) {
  if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y')
    return 1;
  return 0;
}
int main() {
  int n, i, l, r;
  double ans;
  scanf("%s", s + 1);
  n = strlen(s + 1);
  sum[0] = 0;
  sum2[0] = 0;
  for (i = 1; i <= n; i++) {
    sum[i] = sum[i - 1] + 1.0 / i;
    sum2[i] = sum2[i - 1] + (1.0 * n + 1 - i) / (i);
  }
  ans = 0;
  long long sum3 = 0;
  // printf("qwe %s\n",s+1);
  for (i = 1; i <= n; i++) {
    // printf("qwe\n");
    if (ok(s[i])) {
      l = i;
      r = n + 1 - l;
      // sum3+=1LL*l*r;
      if (l > r) swap(l, r);
      // printf("i=%d %d %d\n",i,l,r);
      // if (l>r) swap(l,r);
      ans += l;
      // printf("ans=%lf\n",ans);
      ans += 1.0 * (sum[r] - sum[l]) * l;
      // printf("ans=%lf\n",ans);
      ans += sum2[n] - sum2[r];
      // printf("ans=%lf\n",ans);
    }
  }
  // printf("%d\n",n*(n-1)/2);
  printf("%.10lf\n", ans / (1.0 * n * (n + 1) / 2));
}