#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        ll n;
        cin >> n;
        if (n == 1 || n == 2)
            cout << "1" << endl;
        else
        {
            n -= 2;
            ll k = n / 6, m = n % 6;
            switch (m)
            {
            case 1:
            case 3:
                cout << k << endl;
                break;
            case 4:
                cout << 3 + k * 3 << endl;
                break;
            case 0:
                cout << 4 + (k - 1) * 3 << endl;
                break;
            case 2:
                cout << 3 + 6 * k << endl;
                break;
            case 5:
                cout << 5 + 4 * k << endl;
                break;
            default:
                break;
            }
        }
    }

    return 0;
}