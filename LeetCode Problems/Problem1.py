class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        for i in range(len(nums)):
            for j in range(len(nums)):
                answer = nums[i] + nums[j]
                if answer == target and i != j:
                    return [i, j]