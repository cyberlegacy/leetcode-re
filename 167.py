class Solution(object):
    def twoSum(self, numbers, target):
        """
        :type numbers: List[int]
        :type target: int
        :rtype: List[int]
        """
        length = len(numbers)
        p1 = 0
        p2 = length-1
        while(p1 < p2):
            if numbers[p1]+numbers[p2] < target:
                p1 += 1
            elif numbers[p1]+numbers[p2] > target:
                p2 -= 1
            else:
                return [p1+1,p2+1]

