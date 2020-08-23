import sys
input = sys.stdin.readline
 
n = int(input())
while n:
    n -= 1
    r, g, b = map(int, input().split())
    col = [r, g, b]
    col.sort()
    l, r = 0, col[1]+1
    while l < r:
        mid = (l+r)//2
        if mid <= col[1] and col[2]+col[1]-2*mid >= col[0]:
            l = mid+1
        else:
            r = mid
    print(max(r-1+col[0], min(col[0]+col[1], col[2])))