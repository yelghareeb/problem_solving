"""
	UVA 10705
	Author: Youssef ElGhareeb
"""

import sys

def solve(n, s, k, sol, pos):
    if n == 0:
        global ans
        ans = sol
        return True
    if pos >= k:
        return False
    rem = k - pos
    if pow2[rem] - 1 < n or -1 * (pow2[rem] - 1) > n:
        return False
    flag = False
    flag = flag | solve(n, s, k, sol + "0", pos + 1)
    if s[pos] == 'p':
        flag = flag | solve (n - pow2[rem - 1], s, k, sol + "1", pos + 1)
    else:
        flag = flag | solve (n + pow2[rem - 1], s, k, sol + "1", pos + 1)
    return flag

if __name__=="__main__":
    pow2 = [ 2**i for i in range(64) ]
    t = int(input())
    while t > 0:
        ans = ""
        k = int(input())
        s = input()
        n = int(input())
        flag = solve(n, s, k, "", 0)
        
        if flag:
            ans = ans + "0" * (k - len(ans))
            print (ans) 
        else:
            print ("Impossible")
        t -= 1
