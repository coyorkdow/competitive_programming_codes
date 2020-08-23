#include <bits/stdc++.h>
using namespace std;
int A[(int)1e6 + 10], B[(int)1e6 + 10];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    int n, m;
    while (T--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> A[i];
        for (int i = 1; i <= n; i++)
            cin >> B[i];
        int i;
        for (i = n; i > 0; i--)
        {
            if (A[i] == 0 && B[i] == 0)
                continue;
            if (A[i] == 0)
            {
                cout << "0/1" << endl;
                break;
            }
            if (B[i] == 0)
            {
                cout << "1/0" << endl;
                break;
            }
            int gcd = __gcd(A[i], B[i]);
            cout << A[i]/gcd << '/' << B[i]/gcd << endl;
            break;
        }
    }
    return 0;
}