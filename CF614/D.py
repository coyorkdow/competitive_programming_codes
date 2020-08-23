x0, y0, ax, ay, bx, by = map(int, input().split())
xs, ys, t = map(int, input().split())
cnt = [[0, 0] for i in range(64)]
ansx, ansy, tmpx, tmpy = bx, by, 1, 1
cnt[0] = [x0, y0]
for i in range(1, 64):
  cnt[i][0] = cnt[i-1][0]*ax+bx
  cnt[i][1] = cnt[i-1][1]*ay+by
ans = 0
for i in range(64):
  tt = t - abs(xs-cnt[i][0]) - abs(ys-cnt[i][1])
  if tt < 0:
    continue
  tans, ii = 1, i
  while i > 0:
    tmp = cnt[i][0]-cnt[i-1][0]+cnt[i][1]-cnt[i-1][1]
    if tt - tmp < 0:
      break
    tans += 1
    tt -= tmp
    i -= 1
  tt -= cnt[ii+1][0]-x0+cnt[ii+1][1]-y0
  if tt >= 0:
    tans += 1
  i = ii + 2
  while tt >= 0:
    tmp = cnt[i+1][0]-cnt[i][0]+cnt[i][1]-cnt[i-1][1]
    if tt - tmp < 0:
      break
    tans += 1
    tt -= tmp
    i += 1
  ans = max(ans, tans)
for i in range(64):
  for j in range(64):
    tt = t - abs(xs-cnt[i][0]) - abs(ys-cnt[i][1])
    if tt < 0:
      continue
    tans, ii = 1, i
    while ii + j > i and i < 63:
      tmp = cnt[i+1][0]-cnt[i][0]+cnt[i+1][1]-cnt[i][1]
      if tt - tmp < 0:
        break
      tans += 1
      tt -= tmp
      i += 1
    if ii == 0:
      ans = max(ans, tans)
      continue
    tt -= cnt[i][0]-cnt[ii-1][0]+cnt[i][1]-cnt[ii-1][1]
    if tt >= 0:
      tans += 1
    i = ii-1
    while i > 0:
      tmp = cnt[i][0]-cnt[i-1][0]+cnt[i][1]-cnt[i-1][1]
      if tt - tmp < 0:
        break
      tans += 1
      tt -= tmp
      i -= 1
    ans = max(ans, tans)

print(ans)
