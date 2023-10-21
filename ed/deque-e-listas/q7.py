sarscov2 = input()
influenza = input()

len1 = len(sarscov2)
len2 = len(influenza)

dp = [[0] * (len2+1) for _ in range(len1+1)]
max_length = 0

for i in range(1, len1 + 1):
    for j in range(1, len2 + 1):
        if sarscov2[i-1] == influenza[j-1]:
            dp[i][j] = dp[i-1][j-1] + 1
            max_length = max(max_length, dp[i][j])
        else:
            dp[i][j] = 0
            
print(len1)
print(len2)
print(max_length)