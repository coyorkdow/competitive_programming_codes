

import math


def cal(gcd, n, k):
  y = gcd
  res_k = k // gcd
  for i in range(1, n+1):
    if i == k:
      continue
    _gcd = math.gcd(y, i)
    if _gcd != gcd:
      continue
    res_i = i // _gcd
    flag = False
    for j in range(2, res_i+1):
      if res_i % j != 0:
        continue
      if res_k % j != 0:
        y *= j
        flag = True
        break
      while res_i % j == 0:
        res_i //= j
    if flag:
      continue
    if res_i != 1 and res_k % res_i != 0:
      y *= res_i
    else:
      return -1
  return y


T = int(input())
while T:
  T -= 1
  n, k = map(int, input().split())
  sqt_k = int(math.sqrt(k))
  y = -1
  for i in range(1, sqt_k+1):
    if k % i != 0:
      continue
    _y = cal(k//i, n, k)
    if _y != -1:
      if y == -1:
        y = _y
      else:
        y = min(y, _y)
    _y = cal(i, n, k)
    if _y != -1:
      if y == -1:
        y = _y
      else:
        y = min(y, _y)
  print(y)
