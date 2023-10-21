# Impostores amongus

n = int(input())
usernames = []

for _ in range(n):
    usernames.append(input())
    
impostores = input().split()

crewmates = []
    
for jogador in usernames:
    if jogador not in impostores:
        crewmates.append(jogador)

print(' '.join(crewmates))