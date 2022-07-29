"""
Solved Two Sum Problem
Site: https://leetcode.com/problems/two-sum/ 
"""


class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        print(nums, target)
        for x in range(len(nums)):
            for y in range(x + 1, len(nums)):
                answer = nums[x] + nums[y]
                if answer == target:
                    return [x, y]
