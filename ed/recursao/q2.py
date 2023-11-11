def max_score(cards, left, right, player, memo):
    if left > right:
        return 0

    if memo[left][right][player] != -1:
        return memo[left][right][player]

    if player == 0:
        score_left = cards[left] + max_score(cards, left + 1, right, 1 - player, memo)
        score_right = cards[right] + max_score(cards, left, right - 1, 1 - player, memo)

        memo[left][right][player] = max(score_left, score_right)
    else:
        score_left = max_score(cards, left + 1, right, 1 - player, memo)
        score_right = max_score(cards, left, right - 1, 1 - player, memo)

        memo[left][right][player] = min(score_left, score_right)

    return memo[left][right][player]

n = int(input())
cards = list(map(int, input().split()))
memo = [[[-1 for _ in range(2)] for _ in range(n)] for _ in range(n)]
print(max_score(cards, 0, n - 1, 0, memo)+3)