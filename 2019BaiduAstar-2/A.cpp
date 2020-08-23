#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define mem(a,x) memset(a, x, sizeof a)
#define precision(n) fixed<<setprecision(n)
int ans[(int)1e5+10];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--)
    {
        int n;
        cin>>n;
        int m=n,k=0;
        while (m)
        {
            k+=m%10;
            m/=10;
        }
        int cnt=0;
        for(int i=1;i<=k;i++)
        {
            if(k%i==0&&n%i==0){
                ans[cnt++]=i;
            }
        }
        cout<<cnt<<endl;
        for(int i=0;i<cnt;i++){
            cout<<ans[i];
            if(i==cnt-1)cout<<endl;
            else cout<<' ';
        }
    }
    return 0;
}