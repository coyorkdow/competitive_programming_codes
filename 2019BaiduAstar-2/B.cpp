#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define mem(a,x) memset(a, x, sizeof a)
#define precision(n) fixed<<setprecision(n)
int cntx[30],cnty[30],ans[100];
bool vis[100];
vector<int>pos[30];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T;
    string x,y;
    cin>>T;
    while(T--)
    {
        vector<int>mp[100];
        int N,M;
        bool judge=true;
        cin>>N>>M;
        mem(vis,false);
        mem(ans,-1);
        for(int i=0;i<N;i++)
        {
            cin>>x>>y;
            if(!judge)continue;
            mem(cntx,0);
            mem(cnty,0);
            for(int i=0;i<30;i++)
                pos[i].clear();
            for(int i=0;i<M;i++)
            {
                cntx[x[i]-'a']++;
                cnty[y[i]-'a']++;
                pos[y[i]-'a'].push_back(i);
            }
            for(int i=0;i<30;i++)
            {
                if(cntx[i]!=cnty[i]){
                    judge=false;
                    break;
                }
            }
            if(i==0){
                for(int j=0;j<M;j++)
                {
                    for(vector<int>::iterator it=pos[x[j]-'a'].begin();it!=pos[x[j]-'a'].end();it++)
                    {
                        mp[j].push_back(*it);
                    }
                }
            }else{
                for(int j=0;j<M;j++)
                {
                    vector<int>temp;
                    for(vector<int>::iterator it=pos[x[j]-'a'].begin();it!=pos[x[j]-'a'].end();it++)
                    {
                        temp.push_back(*it);
                    }
                    std::vector<int>::iterator it=set_intersection(mp[j].begin(),mp[j].end(),temp.begin(),temp.end(),mp[j].begin());
                    mp[j].resize(it-mp[j].begin());
                }
            }
        }
        for(int i=0;i<M&&judge;i++)
        {
            if(mp[i].empty())judge=false;
            else{
                for(vector<int>::iterator it=mp[i].begin();it!=mp[i].end();it++)
                {
                    if(vis[*it])continue;
                    ans[i]=*it;
                    vis[*it]=true;
                    break;
                }
                if(ans[i]==-1)judge=false;
            }
        }
        if(!judge)cout<<"-1"<<endl;
        else{
            for(int i=0;i<M;i++)
            {
                cout<<ans[i]+1;
                if(i==M-1)cout<<endl;
                else cout<<' ';
            }
        }
    }
    return 0;
}