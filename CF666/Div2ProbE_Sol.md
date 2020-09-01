In each level of the game, we have two plans to kill all monsters:

1. Using Pistol to kill all normal monsters and then use awp kill boss immediately.
2. Using Pistol to kill all monsters (include boss), or using Laser gun kill all normal monsters and deals 1 hp damage to boss and then use Pistol to kill it.

The difference between two plans is that boss will not be killed immediately if using plan 2, so we have to move to adjacent levels twice and spend $ 2d $ time (assume that we stay in current level after kill all monsters).

Let $ \text{once}[i] $ be the time we kill all monsters in level $ i $ by plan 1 , and $ \text{twice}[i] $ be the time we kill all monsters in level $ i $ by plan 2. At the beginning, we start the game at level $1$, and at a certain time, we are at level $i$, where all monsters in level less than $i$ were killed and all others are alive. This just same as we start the game at level $i$. So we using dynamic programming and let $dp[i]$ be the minimum time to finish the game if we start the game at level $i$.

Normally, we kill all monsters in current level, then move to next level. So we have $dp[i]=\min(dp[i],min(\text{once}[i],\text{twice}[i])+d+dp[i+1])$. And let's consider if we use plan 2 in level $i$, after deals 1 hp damage to boss we are forced to move to next level. If we use plan 2 again in level $i+1$, then we will move back to level $i$, we now kill the level $i$ boss, back to level $i+1$, and kill the boss too. Now we are at level $i+1$, where all monsters in level $i$ and $i+1$ were killed. We have moved to adjacenct level three times, if we move to level $i+2$ next, then the total time we spend on this two level is  $\text{twice}[i]+\text{twice}[i+1]$. So we also have $dp[i]=\min(dp[i],\text{twice}[i]+\text{twice}[i+1])+dp[i+2])$.

And there is also a corner case. Let's consider $dp[n-1]$, if we use plan 2 in level $n-1$, then  we will finish the game at level $n-1$. So we have $dp[n-1]=\min(dp[n-i],min(\text{twice}[n-1]+\text{once}[n],\text{twice}[n-1]+\text{twice}[n]-d))$.



