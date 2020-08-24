#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define mem(a,x) memset(a, x, sizeof a)
#define precision(n) fixed<<setprecision(n)
#define reg register
int li[(int)2e6+(int)1e5];
char str[(int)2e6+(int)1e5];
int maxpos[(int)2e6+(int)1e5];
int main()
{
    for(reg int len=0,j=0,k=1<<1;len<=2100000;len++)
    {
        if(k>len)maxpos[len]=j;
        else{
            maxpos[len]=++j;
            k<<=1;
        }
    }
    int T;
    scanf("%d",&T);
    while (T--)
    {
        scanf("%s",str);
//        strcpy(str,"?");
        reg int len;
        int cnt=0,tnt=0,sum=0;
        int ccnt=0,ans=-1,ttnt=0;
        for(len=0;str[len]!='\0';len++)
        {
            if(str[len]=='?'){
                tnt=1;
                while(str[len+1]=='?')
                {
                    tnt++;
                    len++;
                }
                li[ccnt++]=tnt+1;
                sum+=tnt+1;
                if(ans<tnt+1)
                    ttnt=ccnt-1,ans=tnt+1;
            }
        }
        cnt=len+1-sum;
        if(ccnt==0){
            printf("%d\n",(cnt&1));
            continue;
        }
        int _xor=((1<<(maxpos[ans]+1))-1)^ans;
        for(reg int i=0;i<ccnt;i++)
        {
            if(i!=ttnt){
                int temp=ans;
                ans|=li[i];
                //cout<<li[i]<<' '<<li[i]-((~temp)&li[i])<<' '<<endl;
                ans|=(1<<(maxpos[li[i]-((~temp)&li[i])]+1))-1;
            }
        }
        if(ans&1)ans--;
        printf("%d\n",(ans^((len+1)&1)));
    }
    return 0;
}