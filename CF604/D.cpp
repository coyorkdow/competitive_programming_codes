#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
using namespace __gnu_pbds;
#define all(x) x.begin(), x.end()
#define revall(x) x.rbegin(), x.rend()
#define mem(a, x) memset(a, x, sizeof a)
#define precision(n) std::fixed << std::setprecision(n)
#define quickio                     \
  std::ios::sync_with_stdio(false); \
  std::cin.tie(0), std::cout.tie(0)
#define reg register
#define ednl '\n'
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
typedef std::pair<ull, ull> pull;
typedef std::pair<ll, ll> pll;
template <typename T>
inline T power(T x, T y, T mod = (int)1e9 + 7) {
  if (mod == 0) return 0;
  T ans = 1;
  for (T i = 1; i <= y; i <<= 1, x = x * x % mod)
    if (i & y) ans = ans * x % mod;
  return ans;
}
template <typename T>
inline T mul(T x, T y, T mod = (int)1e9 + 7) {
  if (mod == 0) return 0;
  T ans = 0;
  for (T i = 1; i <= y; i <<= 1, x = x * 2 % mod)
    if (i & y) ans = (ans + x) % mod;
  return ans;
}
namespace FastInput {
const int SIZE = 1 << 16;
char buf[SIZE], str[60];
int bi = SIZE, bn = SIZE;
inline int read(char *s) {
  while (bn) {
    while (bi < bn && buf[bi] <= ' ') bi++;
    if (bi < bn) break;
    bn = fread(buf, 1, SIZE, stdin), bi = 0;
  }
  int sn = 0;
  while (bn) {
    for (; bi < bn && buf[bi] > ' '; bi++) s[sn++] = buf[bi];
    if (bi < bn) break;
    bn = fread(buf, 1, SIZE, stdin), bi = 0;
  }
  s[sn] = 0;
  return sn;
}
template <typename T>
inline bool read(T &x) {
  int n = read(str), bf;
  if (!n) return 0;
  int i = 0;
  if (str[i] == '-')
    bf = -1, i++;
  else
    bf = 1;
  T div = 0;
  for (x = 0; i < n; i++) {
    if (str[i] == '.')
      div = 1;
    else
      x = x * 10 + str[i] - '0', div *= 10;
  }
  if (bf < 0) x = -x;
  if (div) x /= div;
  return 1;
}
struct IO {
  template <typename T>
  IO &operator>>(T &__y) {
    read(__y);
    return *this;
  }
} input;
};  // namespace FastInput
using namespace std;
int main() {
  quickio;
  int a, b, c, d;
  cin >> a >> b >> c >> d;
  int n = a + b + c + d;
  int aa = a, bb = b, cc = c, dd = d;
  if (a == 1 && !b && !c && !d) {
    cout << "YES\n";
    cout << 0;
    exit(0);
  }
  if (b == 1 && !a && !c && !d) {
    cout << "YES\n";
    cout << 1;
    exit(0);
  }
  if (c == 1 && !a && !b && !d) {
    cout << "YES\n";
    cout << 2;
    exit(0);
  }
  if (d == 1 && !a && !c && !b) {
    cout << "YES\n";
    cout << 3;
    exit(0);
  }
  vector<int> ans;
  while (a != 0 && b != 0) {
    if (a) {
      ans.push_back(0);
      a--;
    }
    if (b) {
      ans.push_back(1);
      b--;
    }
  }
  while (b != 0 && c != 0) {
    if (ans.empty() || ans.back() == 0 || ans.back() == 2) {
      if (b) {
        ans.push_back(1);
        b--;
      }
      if (c) {
        ans.push_back(2);
        c--;
      }
    } else {
      if (c) {
        ans.push_back(2);
        c--;
      }
      if (b) {
        ans.push_back(1);
        b--;
      }
    }
  }
  while (c != 0 || d != 0) {
    if (ans.empty() || ans.back() == 1 || ans.back() == 3) {
      if (c) {
        ans.push_back(2);
        c--;
      }
      if (d) {
        ans.push_back(3);
        d--;
      }
    } else {
      if (d) {
        ans.push_back(3);
        d--;
      }
      if (c) {
        ans.push_back(2);
        c--;
      }
    }
  }
  while (b) {
    ans.push_back(1);
    b--;
  }
  while (a) {
    ans.push_back(0);
    a--;
  }
  bool flag = true;
  for (int i = 1; flag && i < ans.size(); i++)
    if (abs(ans[i] - ans[i - 1]) != 1) flag = false;
  if (flag && ans.size() == n) {
    cout << "YES\n";
    for (auto &i : ans) cout << i << ' ';
  } else {
    ans.clear();
    a = aa, b = bb, c = cc, d = dd;
    while (a != 0 && b != 0) {
      if (b) {
        ans.push_back(1);
        b--;
      }
      if (a) {
        ans.push_back(0);
        a--;
      }
    }
    while (b != 0 && c != 0) {
      if (ans.empty() || ans.back() == 0 || ans.back() == 2) {
        if (b) {
          ans.push_back(1);
          b--;
        }
        if (c) {
          ans.push_back(2);
          c--;
        }
      } else {
        if (c) {
          ans.push_back(2);
          c--;
        }
        if (b) {
          ans.push_back(1);
          b--;
        }
      }
    }
    while (c != 0 || d != 0) {
      if (ans.empty() || ans.back() == 1 || ans.back() == 3) {
        if (c) {
          ans.push_back(2);
          c--;
        }
        if (d) {
          ans.push_back(3);
          d--;
        }
      } else {
        if (d) {
          ans.push_back(3);
          d--;
        }
        if (c) {
          ans.push_back(2);
          c--;
        }
      }
    }
    while (b) {
      ans.push_back(1);
      b--;
    }
    while (a) {
      ans.push_back(0);
      a--;
    }
    flag = true;
    for (int i = 1; flag && i < ans.size(); i++)
      if (abs(ans[i] - ans[i - 1]) != 1) flag = false;
    if (flag && ans.size() == n) {
      cout << "YES\n";
      for (auto &i : ans) cout << i << ' ';
    } else {
      ans.clear();
      a = aa, b = bb, c = cc, d = dd;
      while (c != 0 && d != 0) {
        if (d) {
          ans.push_back(3);
          d--;
        }
        if (c) {
          ans.push_back(2);
          c--;
        }
      }
      while (b != 0 && c != 0) {
        if (ans.empty() || ans.back() == 0 || ans.back() == 2) {
          if (b) {
            ans.push_back(1);
            b--;
          }
          if (c) {
            ans.push_back(2);
            c--;
          }
        } else {
          if (c) {
            ans.push_back(2);
            c--;
          }
          if (b) {
            ans.push_back(1);
            b--;
          }
        }
      }
      while (a != 0 || b != 0) {
        if (ans.empty() || ans.back() == 0 || ans.back() == 2) {
          if (b) {
            ans.push_back(1);
            b--;
          }
          if (a) {
            ans.push_back(0);
            a--;
          }
        } else {
          if (a) {
            ans.push_back(0);
            a--;
          }
          if (b) {
            ans.push_back(1);
            b--;
          }
        }
      }
      while (d) {
        ans.push_back(3);
        d--;
      }
      while (c) {
        ans.push_back(2);
        c--;
      }
      flag = true;
      for (int i = 1; flag && i < ans.size(); i++)
        if (abs(ans[i] - ans[i - 1]) != 1) flag = false;
      if (flag && ans.size() == n) {
        cout << "YES\n";
        for (auto &i : ans) cout << i << ' ';
      } else {
        ans.clear();
        a = aa, b = bb, c = cc, d = dd;
        while (c != 0 && d != 0) {
          if (c) {
            ans.push_back(2);
            c--;
          }
          if (d) {
            ans.push_back(3);
            d--;
          }
        }
        while (b != 0 && c != 0) {
          if (ans.empty() || ans.back() == 0 || ans.back() == 2) {
            if (b) {
              ans.push_back(1);
              b--;
            }
            if (c) {
              ans.push_back(2);
              c--;
            }
          } else {
            if (c) {
              ans.push_back(2);
              c--;
            }
            if (b) {
              ans.push_back(1);
              b--;
            }
          }
        }
        while (a != 0 || b != 0) {
          if (ans.empty() || ans.back() == 0 || ans.back() == 2) {
            if (b) {
              ans.push_back(1);
              b--;
            }
            if (a) {
              ans.push_back(0);
              a--;
            }
          } else {
            if (a) {
              ans.push_back(0);
              a--;
            }
            if (b) {
              ans.push_back(1);
              b--;
            }
          }
        }
        while (d) {
          ans.push_back(3);
          d--;
        }
        while (c) {
          ans.push_back(2);
          c--;
        }
        flag = true;
        for (int i = 1; flag && i < ans.size(); i++)
          if (abs(ans[i] - ans[i - 1]) != 1) flag = false;
        if (flag && ans.size() == n) {
          cout << "YES\n";
          for (auto &i : ans) cout << i << ' ';
        } else {
          ans.clear();
          a == aa, b = bb, c = cc, d = dd;
          if (a == 0 && b == 0) {
            if (c > d)
              while (c != 0 || d != 0) {
                if (c) {
                  ans.push_back(2);
                  c--;
                }
                if (d) {
                  ans.push_back(3);
                  d--;
                }
              }
            else
              while (c != 0 || d != 0) {
                if (d) {
                  ans.push_back(3);
                  d--;
                }
                if (c) {
                  ans.push_back(2);
                  c--;
                }
              }
          } else if (a == 0 && d == 0) {
            if (c > b)
              while (c != 0 || b != 0) {
                if (c) {
                  ans.push_back(2);
                  c--;
                }
                if (b) {
                  ans.push_back(1);
                  b--;
                }
              }
            else
              while (c != 0 || b != 0) {
                if (b) {
                  ans.push_back(1);
                  b--;
                }
                if (c) {
                  ans.push_back(2);
                  c--;
                }
              }
          } else if (c == 0 && d == 0) {
            if (a > b)
              while (a != 0 || b != 0) {
                if (a) {
                  ans.push_back(0);
                  a--;
                }
                if (b) {
                  ans.push_back(1);
                  b--;
                }
              }
            else
              while (a != 0 || b != 0) {
                if (b) {
                  ans.push_back(1);
                  b--;
                }
                if (a) {
                  ans.push_back(0);
                  a--;
                }
              }
          }
          flag = true;
          for (int i = 1; flag && i < ans.size(); i++)
            if (abs(ans[i] - ans[i - 1]) != 1) flag = false;
          if (flag && ans.size() == n) {
            cout << "YES\n";
            for (auto &i : ans) cout << i << ' ';
          } else
            cout << "NO\n";
        }
      }
    }
  }
  return 0;
}