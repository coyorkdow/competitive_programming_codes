#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        int n, ans = 0;
        int a, b, pa = -1, pb = -1;
        cin >> n;
        while (n--)
        {
            cin>>a>>b;
            if(pa!=-1){
                if(pa<=b&&b<=pb){
                    pa=max(a,pa);
                    pb=b;
                }else if(a<=pb&&pb<=b){
                    pa=max(a,pa);
                }else{
                    if(pb<a){
                        ans+=ceil((a-pb)/2.0);
                        pa=a;
                        if(((a-pb)&1)&&a!=b){
                            pb=pa+1;
                        }else{
                            pb=pa;
                        }
                    }else if(b<pa){
                        ans+=ceil((pa-b)/2.0);
                        pb=b;
                        if(((pa-b)&1)&&a!=b){
                            pa=pb-1;
                        }else{
                            pa=pb;
                        }
                    }
                }
            }
            else pa=a,pb=b;
        }
        cout<<ans<<endl;
    }
    return 0;
}