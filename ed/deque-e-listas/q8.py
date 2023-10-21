def is_palindrome(s):
    return s == s[::-1]

def has_two_palindromes(word):
    for i in range(len(word)):
        for j in range(i + 3, len(word) + 1):
            substring = word[i:j]
            if is_palindrome(substring):
                for k in range(i + j, len(word) + 1):
                    other_substring = word[j:k]
                    if is_palindrome(other_substring) and substring != other_substring:
                        return True
    return False

input_str = input()
words = input_str.split()

for word in words:
    if has_two_palindromes(word):
        print(word)
