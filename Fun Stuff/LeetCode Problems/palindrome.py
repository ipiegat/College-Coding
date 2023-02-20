class Solution:
    def isPalindrome(self, x: int) -> bool:
        x = str(x)
        a = x[::-1]
        b = x
        if a == b:
            return True
        else:
            return False