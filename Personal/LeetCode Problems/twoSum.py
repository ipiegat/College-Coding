nums = []
target = int(input())

class Solution:
    def twoSum(self, nums, target):
        for i in range(len(nums)):
            for j in range(len(nums)):
                answer = nums[i] + nums[j]
                if answer == target and i != j:
                    return [i, j]

x = None