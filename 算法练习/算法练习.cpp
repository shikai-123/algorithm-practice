﻿#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib> 
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <numeric> 

using namespace std;


class RandomizedSet {
public:
	RandomizedSet() {

	}

	bool insert(int val) {
		if (find(nums.begin(), nums.end(), val) == nums.end())
		{
			nums.push_back(val);
			return true;
		}
		return false;
	}

	bool remove(int val) {

		auto it = find(nums.begin(), nums.end(), val);
		if (it != nums.end())
		{
			nums.erase(it, it + 1);
			return true;
		}
		return false;
	}

	int getRandom() {
		int min_val = 0;  // 最小值
		int max_val = nums.size() - 1; // 最大值
		int random_num = std::rand() % (max_val - min_val + 1) + min_val;


		return nums[random_num];
	}

	vector<int> nums;
};


struct CmpByValue {
	bool operator()(const int& k1, const int& k2) const {
		return k1 > k2;
	}
};



class Solution {
public:

	int removeDuplicates(vector<int>& nums)
	{
		map<int, int>index_num;/*nums中每中元素的数量 key每种元素 value每种元素数量*/
		for (size_t i = 0; i < nums.size(); i++)
		{
			index_num[nums[i]]++;/*这种元素的数量*/
		}
		int tempIndex = 0;

		for (auto keyNums = index_num.begin(); keyNums != index_num.end(); keyNums++)/*遍历map*/
		{
			if (keyNums->second > 1)
			{
				nums.erase(nums.begin() + tempIndex + 2, nums.begin() + tempIndex + index_num[keyNums->first]);
				tempIndex += 2;
			}
			else
			{
				tempIndex++;
			}
		}
		return nums.size();
	}

	int removeDuplicates1(vector<int>& nums)
	{
		map<int, int>index_num;/*nums中每中元素的数量 key每种元素 value每种元素数量*/
		for (size_t i = 0; i < nums.size(); i++)
		{
			index_num[nums[i]]++;/*这种元素的数量*/
		}
		int tempIndex = 0;

		for (auto keyNums = index_num.begin(); keyNums != index_num.end(); keyNums++)/*遍历map*/
		{
			nums.erase(nums.begin() + tempIndex + 1, nums.begin() + tempIndex + index_num[keyNums->first]);
			tempIndex++;
		}
		return nums.size();
	}


	int majorityElement1(vector<int>& nums) {
		map<int, int>index_num;/*nums中每中元素的数量 key每种元素 value每种元素数量*/
		for (size_t i = 0; i < nums.size(); i++)
		{
			index_num[nums[i]]++;/*这种元素的数量*/
		}

		auto iter = index_num.end();
		iter--;
		cout << (iter)->second << endl;
		//cout << (index_num.end()--)->second << endl;
		return (--index_num.end())->second;
	}


	int majorityElement(vector<int>& nums) {
		map<int, int, CmpByValue> index_num;
		for (size_t i = 0; i < nums.size(); i++)
		{
			index_num[nums[i]]++;
		}
		return index_num.begin()->first;
	}



	void rotate(vector<int>& nums, int k) {
		if (nums.size() == 1)
		{
			return;
		}
		if (nums.size() < k)
		{
			k = k % nums.size();
		}
		vector<int> nums1 = nums;
		for (int i = 0; i < nums1.size() - k; i++)
		{
			nums[i + k] = nums1[i];
		}
		for (int i = 0; i < k; i++)
		{
			nums[i] = nums1[nums1.size() - k + i];
		}

	}

	//时间复杂度是n方。测试过不了
	int maxProfit1(vector<int>& prices) {
		int maxValue = 0;
		for (size_t i = 0; i < prices.size(); i++)
		{
			for (size_t l = i + 1; l < prices.size(); l++)
			{
				if (prices[l] - prices[i] > maxValue)
				{
					maxValue = prices[l] - prices[i];
				}
			}
		}
		//cout << "利润 " << maxValue << endl;
		return maxValue;
	}

	int maxProfit2(vector<int>& prices) {
		int maxValue = prices[0];
		int minValue = prices[0];
		int result = 0;
		for (size_t i = 0; i < prices.size(); i++)
		{
			if (prices[i] < minValue)
			{
				minValue = prices[i];
			}
			else if (prices[i] - minValue > result)
			{
				result = prices[i] - minValue;
			}
		}
		cout << "利润 " << result << endl;
		return result;
	}

	int maxProfit(vector<int>& prices) {
		int result = 0;

		for (size_t i = 1; i < prices.size(); i++)
		{
			if (prices[i] - prices[i - 1] > 0)
			{
				result += prices[i] - prices[i - 1];
			}
		}
		cout << "利润 " << result << endl;
		return result;
	}

	bool canJump1(vector<int>& nums) {
		int index = nums[0];
		for (size_t i = 0; i < nums.size(); i++)
		{

			if (nums[i] >= nums.size() - i)//当前的元素的大小超过或等于剩余的步数，就认为成功
			{
				return true;
			}
			if (i == nums.size() - 1)
			{
				return true;
			}
			i = i + nums[i];
			if (i >= nums.size() || i == i + nums[i] && i != nums.size() - 1)//下标走到了0元素，并且不是该数组的最后位置。就说明跳跃失败
			{
				return false;
			}
		}
		return true;
	}
	/*！题解中有更简单的，另外我这是从后往前走的贪心算法，也可以试试从前往后，路径应该都是一样的。*/
	bool canJump(vector<int>& nums) {

		if (nums.size() == 1)
		{
			return true;

		}
		if (nums[0] == 0)//根据规则，第一个如果是0，并且size不是1.那么肯定不行
		{
			return false;

		}
		int orderIndex = nums.size() - 1;//目标点的下标
		for (int i = 1; i <= nums.size() - 1; i)//i是所在这个位置的点的下标
		{
			if (orderIndex - i < 0) {
				return false;//如果目标点的下标orderIndex,比从当前遍历的点到目标点需要的步数，还大。肯定是数组越界了

			}
			if (orderIndex - i + nums[orderIndex - i] >= orderIndex)//往目标点，往前退一个目标。计算它的下表+它的值，是否》=当前目标的下表。
			{
				orderIndex = orderIndex - i;
				i = 1;
			}
			else//如果不行，那么就在往前一走一个
			{
				i++;
			}
			if (orderIndex == 0)//如果目标点到了数组的第一个位置，那么肯定就是可以的。
			{
				return true;
			}
		}
		return false;
	}


	/*和前一个不同的是，它跳跃的距离是不固定的，之前跳的距离就是元素大小，现在是0--元素大小之间0 <= j <= nums[i]
	这个更只能用贪心算法

	*/
	int jump(vector<int>& nums) {
		int jumpNums = 0;
		int orderValue = 0;
		if (nums.size() == 1)
		{
			return 0;
		}
		int orderIndex = nums.size() - 1;//目标点的下标
		int tempMax = 0;//在一个周期中。距离目标点的最大距离
		for (int i = 1; i <= nums.size() - 1; i++)//i是所在这个位置的点的下标
		{
			for (int i = 1; i <= orderIndex; i++)//i是所在这个位置的点的下标
			{
				if (orderIndex - i + nums[orderIndex - i] >= orderIndex)//往目标点，往前退一个目标。计算它的下表+它的值，是否》=当前目标的下表。
				{
					if (nums[orderIndex - i] >= i)
					{
						tempMax = i;
					}
				}
			}
			orderIndex = orderIndex - tempMax;
			orderValue = 0;
			jumpNums++;
			if (orderIndex == 0)
			{
				return jumpNums;
			}
		}
		return jumpNums;
	}


	int hIndex1(vector<int>& citations) {

		sort(citations.begin(), citations.end());
		int sun = 0;
		int aveValue = 0;
		int midIndexValue = 0;
		int base = 0;
		int h = 0;
		int hTemp = 0;
		int minValue = 0;
		for (size_t i = 0; i < citations.size(); i++)
		{
			for (size_t l = 0; l < citations[i]; l++)
			{
				if (citations[i + l] >= citations[i])
				{
					h++;
				}

			}
		}



		return h;
	}


	int hIndex(vector<int>& citations) {
		sort(citations.begin(), citations.end());
		int h = 0, i = citations.size() - 1;
		while (i >= 0 && citations[i] > h) {
			h++;
			i--;
		}
		return h;
	}

	vector<int> productExceptSelf(vector<int>& nums) {
		vector<int>allValue(nums.size(), 0);
		vector<int>zeroValue(nums.size(), 0);


		int tempNums = 1;
		int zeroNums = 0;
		int fristZeroIndex = 0;

		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] == 0)
			{
				++zeroNums;
				if (zeroNums == 1)
				{
					fristZeroIndex = i;
				}
				if (zeroNums > 1)//如果有俩0，整个answer都是0
				{
					return zeroValue;
				}
			}
			tempNums = tempNums * nums[i];
		}
		if (zeroNums == 1)//如果有一个0，除了这个位置，其他都是0
		{
			tempNums = 1;
			for (size_t i = 0; i < nums.size(); i++)
			{
				if (i == fristZeroIndex)
				{
					continue;
				}
				tempNums = tempNums * nums[i];
			}
			zeroValue[fristZeroIndex] = tempNums;
			return zeroValue;
		}
		for (int i = 0; i < nums.size(); i++)
		{
			allValue[i] = tempNums / nums[i];
		}
		return allValue;
	}

	int canCompleteCircuit1(vector<int>& gas, vector<int>& cost) {
		int oil = 0;
		int residualOil = 0;
		int base = 0;
		int  flag = 0;
		int i = -1;
		int oilTimes = 0;
		while (true)
		{
			i++;
			if (gas[i%cost.size()] >= cost[i%cost.size()] && flag == 0)//汽油大于往下个加油站的消耗，才能用这个地方出发。
			{
				flag = 1;
				base = i;
				residualOil += gas[i%gas.size()];
				gas[i%gas.size()] = 0;
				continue;
			}
			else if (flag == 0)
			{

				if (i == cost.size() - 1)
				{
					return  -1;
				}
				continue;
			}


			if (base <= i && i < gas.size())
			{
				residualOil = residualOil - cost[(i - 1) % gas.size()];
				residualOil += gas[i%gas.size()];
				gas[i%gas.size()] = 0;
				oilTimes++;
			}
			if (i >= gas.size())
			{
				residualOil = residualOil - cost[(i - 1) % gas.size()];
				residualOil += gas[i%gas.size()];
				gas[i%gas.size()] = 0;
				oilTimes++;
			}

			if (residualOil < 0)
			{
				return  -1;
			}
			if (oilTimes == gas.size())
			{
				return base;
			}

		}

		return base;
	}


	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		int cursum = 0;
		int sum = 0;
		int start = 0;
		for (int i = 0; i < gas.size(); i++) {
			cursum += gas[i] - cost[i];
			sum += gas[i] - cost[i];
			if (cursum < 0) {
				start = i + 1;
				cursum = 0;
			}
		}
		if (sum < 0) return -1;
		return start;
	}

	int romanToInt(string s) {

		map<string, int>Control_Param = {
		{ "I", 1 },
		{ "V", 5 },
		{ "X",10 },
		{ "L",50 },
		{ "C",100 },
		{ "D",500 },
		{ "M",1000 }
		};
		int value = 0;
		int power = s.size();//次方
		for (int i = s.size() - 1; i > -1; --i)
		{
			if (Control_Param[s.substr(i - 1, i)] == 1 && s[i - 1] < 5)
			{
				value += 1;
			}
			else if (s[i] == 1 && s[i - 1] >= 5)
			{
				value += s[i - 1];
			}

		}
		return value;
	}


	int lengthOfLastWord(string s) {
		int lenth = 0;
		bool flag = 0;//1遇到单词了
		for (int i = s.size() - 1; i >= 0; i--)
		{
			if (s[i] == ' ')
			{
				if (flag == 1)
				{
					break;
				}
				lenth = 0;
			}
			else
			{
				lenth++;
				flag = 1;
			}
		}
		return lenth;
	}



	string longestCommonPrefix1(vector<string>& strs) {
		string newtemp = "";
		string oldtemp = "";
		string result = "";
		int index = 0;
		int lenth = 0;

		while (!strs[0].empty())
		{
			for (size_t i = 0; i < strs.size(); i++)
			{
				if (index >= strs[i].size())
				{
					return strs[0].substr(0, lenth);
				}
				oldtemp = newtemp;
				newtemp = string(1, strs[i][index]);
				if (i > 0 && newtemp == oldtemp)
				{
				}
				else if (i > 0)
				{
					return strs[0].substr(0, lenth);
				}
			}
			lenth++;
			index++;
			oldtemp = "";
			newtemp = "";

		}



		return strs[0].substr(0, lenth);

	}


	string reverseWords(string s) {
		string temp;
		istringstream in(s);
		string res;
		while (in >> res) {
			temp.insert(0, res);
			temp.insert(0, " ");
		}
		temp.erase(0, 1);
		return temp;
	}


	int strStr(string haystack, string needle)
	{
		int lenth = haystack.size();
		for (int i = 0; i < lenth; i++)
		{
			if (strncmp(haystack.c_str(), needle.c_str(), needle.size()) == 0)
			{
				return i;
			}
			else
			{
				haystack.erase(0, 1);
			}
		}
		return -1;
	}



	int candy(vector<int>& ratings) {
		int allValue = 0;
		vector<int> lValue(ratings.size(), 1);
		vector<int> rValue(ratings.size(), 1);
		for (int i = 1; i < ratings.size(); i++)
		{
			if (ratings[i - 1] < ratings[i])
			{
				lValue[i] = lValue[i] + lValue[i - 1];
			}
			else
			{
				lValue[i] = 1;
			}
		}

		for (int i = ratings.size() - 2; i >= 0; i--)
		{
			if (ratings[i] > ratings[i + 1])
			{
				rValue[i] = rValue[i] + rValue[i + 1];
			}
			else
			{
				rValue[i] = 1;
			}
		}


		for (size_t i = 0; i < ratings.size(); i++)
		{
			allValue = allValue + max(lValue[i], rValue[i]);
		}
		return allValue;
	}

	string convert1(string s, int numRows) {

		map<int, map<int, string>> str;
		for (size_t i = 0; i < numRows; i++)
		{
			for (size_t l = 0; l < numRows - i; l++)
			{
				if (i + l == numRows - 1)
				{
					cout << "l" << l << "  i" << i << endl;
					str[l][i] = s[0];
					s.erase(0, 1);
				}
			}

		}

		return "a";
	}
	string convert(string s, int numRows) {
		if (numRows < 2)
			return s;
		vector<string> rows(numRows);
		int i = 0, flag = -1;
		for (char c : s) {
			rows[i].push_back(c);
			if (i == 0 || i == numRows - 1)
				flag = -flag;
			i += flag;
		}
		string res;
		for (const string &row : rows)
			res += row;
		return res;
	}

	int trap(vector<int>& height)
	{
		int ans = 0;
		stack<int> st;
		for (int i = 0; i < height.size(); i++)
		{
			while (!st.empty() && height[st.top()] < height[i])
			{
				int cur = st.top();
				st.pop();
				if (st.empty()) break;
				int l = st.top();
				int r = i;
				int h = min(height[r], height[l]) - height[cur];
				ans += (r - l - 1) * h;
			}
			st.push(i);
		}
		return ans;
	}


	int largestRectangleArea(vector<int>& heights)
	{
		int ans = 0;
		vector<int> st;
		heights.insert(heights.begin(), 0);
		heights.push_back(0);
		for (int i = 0; i < heights.size(); i++)
		{
			if (!st.empty())
			{
				cout << " i-" << i << " st.back()-" << st.back() << " heights[st.back()]-" << heights[st.back()]\
					<< " heights[i]-" << heights[i] << endl;
			}
			else
			{
				cout << " empty" << endl;
			}
			while (!st.empty() && heights[st.back()] > heights[i])
			{
				int cur = st.back();
				st.pop_back();
				int left = st.back() + 1;
				int right = i - 1;
				ans = max(ans, (right - left + 1) * heights[cur]);
			}
			st.push_back(i);
		}
		return ans;
	}
	bool isPalindrome(string s) {
		/*
		https://blog.csdn.net/qq_37234166/article/details/86591576
		*/
		bool flag = 1;
		for (size_t i = 0; i < s.size(); i++)
		{
			if (97 <= s[i] && s[i] <= 122)
			{
				cout << "小写" << s[i] << " i" << i << endl;
			}
			else if (65 <= s[i] && s[i] <= 90)
			{
				s[i] = s[i] + 32;
				cout << "大写" << s[i] << " i" << i << endl;
			}
			else if (48 <= s[i] && s[i] <= 57)
			{
				cout << "数字" << s[i] << " i" << i << endl;
			}
			else {
				cout << "其他" << s[i] << " i" << i << endl;
				s.erase(i, 1);
				i--;
			}
		}
		if (s.empty())
		{
			return 1;
		}
		if (s.size() == 1)
		{
			return 1;
		}
		if (s.size() == 0)
		{
			return 1;
		}

		for (size_t i = 0; i < s.size(); i++)
		{
			if (i < s.size() / 2)
			{
				if (s[i] == s[s.size() - 1 - i])
				{
					flag = flag & 1;
				}
				else
				{
					return 0;
				}
			}
		}
		return 1;
	}


	bool isSubsequence(string s, string t) {
		int i = 0, l = 0;
		while (true)
		{
			if (s.empty())
			{
				return 1;
			}
			if (t.empty())
			{
				return 0;
			}
			if (s[i] == t[l])
			{
				i++;
				l++;
				if (i >= s.size())
				{
					return 1;
				}
			}
			else
			{
				l++;
				if (l >= t.size())
				{
					return 0;
				}
			}

		}
	}
	vector<int> twoSum(vector<int>& numbers, int target) {

		/*
		https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/solutions/87919/yi-zhang-tu-gao-su-ni-on-de-shuang-zhi-zhen-jie-fa/?envType=study-plan-v2&envId=top-interview-150
		*/
		int i = 0;
		int l = numbers.size() - 1;
		while (1)
		{
			int sun = numbers[i] + numbers[l];
			if (sun < target)
			{
				i++;
			}
			else if (sun > target)
			{
				l--;
			}
			else
			{
				return vector<int>{ i + 1, l + 1 };
			}
		}
	}
	int maxArea(vector<int>& height) {
		/*
		https://leetcode.cn/problems/container-with-most-water/solutions/11491/container-with-most-water-shuang-zhi-zhen-fa-yi-do/?envType=study-plan-v2&envId=top-interview-150
		*/
		int i = 0;
		int l = height.size() - 1;
		int maxAer = 0;
		while (true)
		{
			if (i == l)
			{
				return  maxAer;
			}
			else if (height[i] < height[l])
			{

				if ((l - i)*height[i] > maxAer)
					maxAer = (l - i)*height[i];
				i++;
			}
			else if (height[i] >= height[l])
			{
				if ((l - i)*height[l] > maxAer)
					maxAer = (l - i)*height[l];
				l--;

			}
		}
	}

	vector<vector<int>> twoSumTarget(vector<int>& nums, int start, int target) {
		// nums 数组必须有序
		sort(nums.begin(), nums.end());
		int lo = start, hi = nums.size() - 1;
		vector<vector<int>> res;
		while (lo < hi) {
			int sum = nums[lo] + nums[hi];
			int left = nums[lo], right = nums[hi];
			if (sum < target) {
				while (lo < hi && nums[lo] == left) lo++;
			}
			else if (sum > target) {
				while (lo < hi && nums[hi] == right) hi--;
			}
			else {
				res.push_back({ left, right });
				while (lo < hi && nums[lo] == left) lo++;
				while (lo < hi && nums[hi] == right) hi--;
			}
		}
		return res;
	}

	vector<vector<int>> threeSum(vector<int>& nums) {
		/*
		双指针的方法，并且这个题解中，给出了2数 3数 4数 100数的通用方法
		https://leetcode.cn/problems/3sum/solutions/328307/yi-ge-fang-fa-tuan-mie-by-labuladong/?envType=study-plan-v2&envId=top-interview-150
		*/
		sort(nums.begin(), nums.end());
		int n = nums.size();
		vector<vector<int>> res;
		// 穷举 threeSum 的第一个数
		for (int i = 0; i < n; i++) {
			// 对 target - nums[i] 计算 twoSum
			vector<vector<int>>
				tuples = twoSumTarget(nums, i + 1, 0 - nums[i]);
			// 如果存在满足条件的二元组，再加上 nums[i] 就是结果三元组
			for (vector<int>& tuple : tuples) {
				tuple.push_back(nums[i]);
				res.push_back(tuple);
			}
			// 跳过第一个数字重复的情况，否则会出现重复结果
			while (i < n - 1 && nums[i] == nums[i + 1]) i++;
		}
		return res;
	}


	vector<int> twoSum1(vector<int>& numbers, int target)
	{
		int lo = 0, hi = numbers.size() - 1;
		vector<int> ret;
		for (size_t i = 0; i < numbers.size() - 1; i++)
		{
			int tempTarget = numbers[lo] + numbers[hi];
			if (tempTarget > target)
			{
				hi--;
			}
			else if (tempTarget < target)
			{
				lo++;
			}
			else
			{
				return vector<int>{hi, lo};
			}
		}
	}

	/*209. 长度最小的子数组
	思路
		滑动窗口
		滑动窗口左边移动是会导致窗口中的数不变或者是变小。
		滑动窗口右边移动是会导致窗口中的数变大或者不变。
		所以先往右移，数据变大，然后左移一点点变小，记录最小的距离。
		直到小于target，然后右移增大，然后左移减小。
		不断的重复，知道右移到最后。
		返回最小的步数。
		如何保证，所以的数据都参与计算呢？
		这个题目有个前提是——“参与计算的数都是连续的”，我觉得这是用滑动窗口的标志！
		这个条件，就可以保证滑动窗口能让，所有符合条件的都计算一边，因为窗口中的数都是连续的，挨着的
	参考
		https://leetcode.cn/problems/minimum-size-subarray-sum/solutions/1706223/by-carlsun-2-iiee/?envType=study-plan-v2&envId=top-interview-150

	其他
		如果数组中有负数就不行了。因为滑动窗口用来算最短路径的方法，
		成功的前提是：滑动窗口左边移动是会导致窗口中的数不变或者是变小。负数会让窗口中的数变大！
	*/
	int minSubArrayLen(int target, vector<int>& nums) {

		int minStep = INT_MAX;
		int sum = 0;
		int L = 0;//L是滑动窗口的左侧下标
		//R是滑动窗口的右侧下标
		for (size_t R = 0; R < nums.size(); R++)
		{
			sum += nums[R];
			//这个地方一定是得是while，我当时写成了if，如果是if的话，滑动窗口的左边的下标如果能移动两次的话，就会造成只能移动一次！
			while (sum >= target)
			{
				int step = R - L + 1;
				minStep = step <= minStep ? step : minStep;
				sum -= nums[L];
				L++;
			}
		}
		return minStep != INT_MAX ? minStep : 0;
	}

	/*滑动窗口使用的标志——
	1、计算数组中的某一部分数据的长度！（最短的、最长的、次长次短也能算）
	2、这些长度还都是挨着的
	*/


	/*
	3. 无重复字符的最长子串
	*/
	int lengthOfLongestSubstring(string s) {

		string maxStr = "";
		int len = 0;
		for (size_t r = 0; r < s.size(); r++)
		{
			if (maxStr.find(s[r]) == maxStr.npos)
			{
				maxStr += s[r];
			}
			else//maxStr已经有了s[l]
			{
				do
				{
					maxStr.erase(maxStr.begin());
				} while ((r < s.size()) && maxStr.find(s[r]) != maxStr.npos);//maxStr已经有了s[l]
				maxStr += s[r];
			}
			//max是函数模板，左右两个参数的类型是同一类型才行，所有右侧参数需要转一下
			len = max(len, (int)maxStr.size());
		}
		return len;
	}

	/*
	30、串联所有单词的子串
	思路
		滑动窗口
		这个窗口应该是简单点，毕竟窗口的大小是固定的

	改进
	！我现在的问题就是，性能太差，时间太长，ac失败。
	如果我把words存到map中的话，然后s与map进行对比
	核心是map会自动排序。举例：abc不论那种顺序插入进去，最后都是
	*/
	vector<int> findSubstring_old(string s, vector<string>& words) {

		int  windowsLen = 0;
		int l = 0;
		vector<string> allWords;
		windowsLen += words[0].size()*words.size();
		std::sort(words.begin(), words.end());
		vector<int> pos;
		/*
		std::next_permutation 函数来生成并打印所有排列。
		当std::next_permutation 返回 false 时，表示所有排列都已生成。
		!!这种方法性能太差了，while要执行words.size的阶乘次数。以18举例子，就会执行6402373705728000次。半个小时都不一定能算完
		*/
		do {
			std::string tempWords = std::accumulate(words.begin(), words.end(), std::string(""));
			allWords.push_back(tempWords);
		} while (std::next_permutation(words.begin(), words.end()));



		for (size_t r = windowsLen - 1; r < s.size(); r++)
		{
			for (size_t i = 0; i < allWords.size(); i++)
			{
				cout << s.substr(l, r + 1) << endl;
				if (s.substr(l, windowsLen).compare(allWords[i]) == 0)
				{
					pos.push_back(l);
					break;
				}
			}
			l++;
		}
		return pos;
	}

	/*
		30、串联所有单词的子串
	*/
	vector<int> findSubstring(string s, vector<string>& words) {
		vector<int> res;
		int n = s.size();//字符串长度
		int m = words.size();//words的长度
		int d = words[0].size();//words中单个单词的长度
		int len = 0;//words中所有单词加一起的长度为 len
		unordered_map<string, int> um;//words中的单词放到um中 
		for (string w : words) {
			len += w.size();
			um[w]++;
		}

		//构造一开始的滑动窗口，string是滑动窗口的中的单词， int是滑动窗口的中这种单词的数量。比如"foobar"，在map中是两个string，但int都是0。根据不同的情况，滑动窗口数量是等于一个单词的长度的
		vector<unordered_map<string, int> > vu(d);//vec中的一个map就是一滑动窗口中的字符串，map的key就是滑动窗口中各个单词的数量。map相等就说明字符串相等，
		for (int i = 0; i < d && i + len <= n; i++) {
			for (int j = i; j < i + len; j += d) {
				string w = s.substr(j, d);
				vu[i][w]++;
			}
			if (vu[i] == um) {
				res.emplace_back(i);
			}
		}

		// sliding window: 滑动窗口，每次移动 d 个位置
		for (int i = d; i + len <= n; i++) {
			int r = i % d;//
			//这两个存的应该是滑动窗口的最前面的单词，和该处滑动窗口外的第一个单词。就是为了移动滑动窗口
			string wa = s.substr(i - d, d);
			string wb = s.substr(i + len - d, d);
			//vu[r][wa] 这个代码中的map存的都是单词，都是长度为3的单词。存到了某种单词就+1.
			if (--vu[r][wa] == 0)//这个应该是删除滑动窗口的最前面的单词，对==0判断是因为表达的是，如果这个单词的数量就是0的话，就应该把这个单词从vu抹除。就算不是1，也是会--的，到时候说明单词在vu中的数量减少了1个
			{
				vu[r].erase(wa);//把这个单词从vu抹除。
			}
			vu[r][wb]++;
			if (vu[r] == um) {
				res.emplace_back(i);
			}
		}

		return res;
	}


	/*
	76. 最小覆盖子串
		思路：这个思路和30题的思路有相似之处——用到了hash的思想
		做两个hash，分别记录各自字符的数量。
	*/
	string minWindow(string s, string t) {
		unordered_map<char, int> hs;//滑动窗口中的各个字符的数量
		unordered_map<char, int> ht;//t中的各个字符的数量。
		for (auto c : t) ht[c] ++;
		string res;
		int cnt = 0;
		for (int i = 0, j = 0; i < s.size(); i++) {
			hs[s[i]] ++;
			//滑动窗口中对应字符的数量没t中的多。说明当前新加入的字符s[i]是必需的，
			if (hs[s[i]] <= ht[s[i]]) {//!ht在这里也会增加一个新的key，如果t中没有s中的这个字符的话，value初始化为0
				cnt++;
			}
			//滑动窗口中左边对应字符的数量没t中的多。说明不需要删除。
			//注意这是个while，删掉一个后，他会再次判断下个
			//如果滑动窗口对应的字符比t中的字符多的那些字符都会删掉。不过得等到滑动窗口中的最左边的字符超过t中的才行。——相当于滑动窗口左边右移
			//他不是hs任意一个字符超过了ht就去删除。这个就是不符合咱们的直觉，逻辑上很合理。
			while (hs[s[j]] > ht[s[j]]) {
				hs[s[j++]] --;
			}
			if (cnt == t.size()) {
				if (res.empty() || i - j + 1 < res.size())//1、当res从来没有被赋值的时候，或者新的滑动窗口中符合条件的字符，别上次还小的时候
					res = s.substr(j, i - j + 1);
			}
		}
		return res;
	}

	/*
	36. 有效的数独
		思路：参考别人的。因为这是矩阵的第一个题目，所以先学一下

		参考：https://leetcode.cn/problems/valid-sudoku/description/?envType=study-plan-v2&envId=top-interview-150
	*/
	bool isValidSudoku1(vector<vector<char>>& board) {
		//比如： row[0][5] ==1 就是第0行中有5这个数； row[0][6]意思就是说第0行中没有6这个数.所以row中会出现row[0][9]也就是会访问到第10列
		int row[9][10] = { 0 };// 哈希表存储每一行的每个数是否出现过，默认初始情况下，每一行每一个数都没有出现过
		// 整个board有9行，第二维的维数10是为了让下标有9，和数独中的数字9对应。
		int col[9][10] = { 0 };// 存储每一列的每个数是否出现过，默认初始情况下，每一列的每一个数都没有出现过
		int box[9][10] = { 0 };// 存储每一个box的每个数是否出现过，默认初始情况下，在每个box中，每个数都没有出现过。整个board有9个box。
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				// 遍历到第i行第j列的那个数,我们要判断这个数在其所在的行有没有出现过，
				// 同时判断这个数在其所在的列有没有出现过
				// 同时判断这个数在其所在的box中有没有出现过
				if (board[i][j] == '.') continue;
				int curNumber = board[i][j] - '0';//因为矩阵的中的数字是字符形式的减去0的ASCII码就是该字符数字的实际数值
				if (row[i][curNumber]) return false;
				if (col[j][curNumber]) return false;
				if (box[j / 3 + (i / 3) * 3][curNumber]) return false;

				row[i][curNumber] = 1;// 之前都没出现过，现在出现了，就给它置为1，下次再遇见就能够直接返回false了。
				col[j][curNumber] = 1;
				box[j / 3 + (i / 3) * 3][curNumber] = 1;
			}
		}
		return true;
	}

	bool isValidSudoku(vector<vector<char>>& board) {

		int row[9][10] = { 0 };
		int col[9][10] = { 0 };
		int box[9][10] = { 0 };


		for (size_t h = 0; h < board.size(); h++)
		{
			for (size_t l = 0; l < board[h].size(); l++)
			{

				if (board[h][l] == '.')
				{
					continue;
				}
				int nums = board[h][l] - '0';

				if (row[h][nums]) return false;
				if (col[l][nums]) return false;
				if (box[(l / 3) + (h / 3) * 3][nums]) return false;

				row[h][nums] = 1;
				col[l][nums] = 1;
				box[(l / 3) + (h / 3) * 3][nums] = 1;

			}
		}
		return true;
	}







	/*
	54. 螺旋矩阵
		参考：
		https://leetcode.cn/problems/spiral-matrix/solutions/2362055/54-luo-xuan-ju-zhen-mo-ni-qing-xi-tu-jie-juvi/?envType=study-plan-v2&envId=top-interview-150

		思路：
		首先要明白一点的是：
		这个答案中，所说的“判断边界是否相遇（是否打印完毕），若打印完毕则跳出。”要这么理解
		对于只有一个元素的矩形，他的上下左右边界都是0。这种用“if (++t == b) ”来做判断的肯定不行。
		t是上边界，b是下边界。两者相等的时候，是不能认为两者边界是相遇的。这个时候上下边界其实正好在一个元素的上下。
		只有上边界大于下边界，或者是下边界大于上边界的时候，才是两个边界在一块的时候。
	*/
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		if (matrix.empty()) return {};
		int l = 0;//左边界
		int r = matrix[0].size() - 1;//右边界 ！这个位置必须减一，因为现在有直接拿r做下标访问导致越界。为了保证一行或一列中所有的数据都能访问，for中用了=号
		int t = 0;//上边界
		int b = matrix.size() - 1;//bottom最下边界
		vector<int> res;
		while (true) {
			for (int i = l; i <= r; i++)// left to right 也就是从左遍历到右，然后top往下走一个
			{
				res.push_back(matrix[t][i]);
			}
			if (++t > b) break;
			for (int i = t; i <= b; i++) // top to bottom
			{
				res.push_back(matrix[i][r]);
			}
			if (l > --r) break;
			for (int i = r; i >= l; i--) // right to left
			{
				res.push_back(matrix[b][i]);
			}
			if (t > --b) break;
			for (int i = b; i >= t; i--)  // bottom to top
			{
				res.push_back(matrix[i][l]);
			}
			if (++l > r) break;
		}
		return res;
	}


	/*
	48. 旋转图像
		参考：
			https://leetcode.cn/problems/rotate-image/solutions/274724/li-kou-48xiao-bai-du-neng-kan-dong-de-fang-fa-zhu-/?envType=study-plan-v2&envId=top-interview-150
		思路：
			采用分层来进行平移的方式，将矩阵的每一层都分开进行旋转
	*/
	void rotate(vector<vector<int>>& matrix)
	{
		//pos1 pos2的组合 ，可以组合出矩形4个顶点的坐标，然后移动这个4个坐标做矩阵旋转
		int pos1 = 0;
		int pos2 = matrix.size() - 1;
		int addr = 0;
		int temp;
		//判定整个矩阵是否旋转完成
		while (pos1 < pos2)
		{
			addr = 0;//每次进入新的圈子后，addr归零
			//判断其中某一条圈是否旋转完成
			while (pos1 + addr < pos2)
			{
				//从从左上角开始.顺时针旋转
				temp = matrix[pos1][pos1 + addr];//左上角赋值给临时变量
				matrix[pos1][pos1 + addr] = matrix[pos2 - addr][pos1];//左下角赋值给左上角
				matrix[pos2 - addr][pos1] = matrix[pos2][pos2 - addr];//右下角赋值给左下角
				matrix[pos2][pos2 - addr] = matrix[pos1 + addr][pos2];//右上角赋值给右下角
				matrix[pos1 + addr][pos2] = temp;
				addr++;
			}
			/*++pos1;
			--pos2;*/
			pos1++;
			pos2--;
		}
	}




	/*
	73. 矩阵置零
		思路：
		先确定0的点，然后在把这些位置对应的那些1赋值成0。时间复杂度n平方，空间复杂度m+n

		总结：
			这个方法还行。题目中让尝试1的空间复杂度，我看了看解法，就只能使用于本题目，没有普适性
			而且我这个想法也不错，第一次做，就到这吧
	*/
	void setZeroes(vector<vector<int>>& matrix) {

		vector<int> row(matrix.size());
		vector<int> rol(matrix[0].size());

		for (size_t i = 0; i < matrix.size(); i++)
		{
			for (size_t l = 0; l < matrix[i].size(); l++)
			{
				if (matrix[i][l] == 0)
				{
					row[i] = 1;
					rol[l] = 1;
				}
			}
		}
		for (size_t i = 0; i < matrix.size(); i++)
		{
			for (size_t l = 0; l < matrix[i].size(); l++)
			{
				if (row[i] == 1 && rol[l] == 1)
				{
					for (size_t lie0 = 0; lie0 < matrix[0].size(); lie0++)
					{
						matrix[i][lie0] = 0;
					}
					for (size_t hang0 = 0; hang0 < matrix.size(); hang0++)
					{
						matrix[hang0][l] = 0;
					}
				}
				continue;
			}

		}

	}


	/*
	生命游戏
	思路1：
		参考73. 矩阵置零的思路。为了消除在原矩阵中直接改变数值后，对后续数计算的影响
		所以还是先遍历矩阵，然后把要变1的变0的记录下来。
		省点空间复杂度的话就得是和73题一样（m+n），做两个数组。但是会有俩个if，影响点性能
		节省点性能，就要做个矩阵（二维数组）也就是空间复杂的是m*n.
		这个时候就看你的取舍了
		这个思路还是这一套，虽然没有动手做，但毕竟和73题不一样。
		为了提高效率 换新方法。学习新的方法
		https://leetcode.cn/problems/game-of-life/solutions/179750/sheng-ming-you-xi-by-leetcode-solution/?envType=study-plan-v2&envId=top-interview-150
		这个题解中的“毒爪的小新”就是这种方法

	思路2：
		位操作思路；
		vec是32的数据 给的矩阵中只有0、1 那么只占据一位数据 所以用次低位数据来记录后期该位要置0还是置1
		最后的时候通过移位来把更改后的矩阵遍历出来。
		该思路中和思路1相比较，其实都是用到了4个for循环 时间复杂的一致。但是空间复杂的从m+n或者是m*n 变成了固定的 也就是i 这一点特别好
	参考：
	https://leetcode.cn/problems/game-of-life/submissions/477229256/?envType=study-plan-v2&envId=top-interview-150
	*/
	void  gameOfLife(vector<vector<int>>& board) {
		//这是元素的相邻的8个元素
		int dx[] = { -1,  0,  1, -1, 1, -1, 0, 1 };
		int dy[] = { -1, -1, -1,  0, 0,  1, 1, 1 };

		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[0].size(); j++) {
				int sum = 0;
				for (int k = 0; k < 8; k++) {
					int nx = i + dx[k];
					int ny = j + dy[k];
					if (nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size()) {
						sum += (board[nx][ny] & 1); // 只累加最低位
					}
				}
				if (board[i][j] == 1) {//=1就是细胞存活
					if (sum == 2 || sum == 3) {//如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活；
						board[i][j] |= 2;  // 使用第二个bit标记是否存活 !！次低位1就是活 0就是死 默认是0
					}
					else//这种就是死亡的。 ——细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡；——活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡；
					{
						//board[i][j];//这一步可以省掉
					}
				}
				else {//这种就是细胞死亡
					if (sum == 3) {
						board[i][j] |= 2; // 使用第二个bit标记是否存活
					}
				}
			}
		}
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[i].size(); j++) {
				board[i][j] >>= 1; //右移一位，用第二bit覆盖第一个bit。
			}
		}
	}


	/*
	383. 赎金信
	前言：
		因为这是“哈希表”题目中第一题，所以就直接参考了题解

	思路：
		一开始想着用滑动窗口的方式，但是后来发现，他不是要求连续的，只要magazine能拿出一部分拼上就行，所以不哟个这个

	参考思路1：
		链接：
		https://leetcode.cn/problems/ransom-note/solutions/948784/qiao-yong-stringrong-qi-de-cha-zhao-han-kao7r/?envType=study-plan-v2&envId=top-interview-150
		利用find的方式，从magazine中找ransomNote字符。找到就从magazine消掉这个字符，避免像aa  ab的情况。这种是不对的
		只要是找不到就说明不行。
		这个方法不错，但是不是我想要的“哈希表”的方法。

	参考思路2：
		这个就是我想要的“哈希表”的方法。
		链接：
		https://leetcode.cn/problems/ransom-note/solutions/369114/383-shu-jin-xin-bao-li-jie-fa-zi-dian-ji-shu-fa-2/?envType=study-plan-v2&envId=top-interview-150
		思路毕竟简单，时间复杂度上肯定是比思路1好很多，只是空间复杂度差点。
		先是记录magazine各个字母出现的次数，然后在遍历ransomNote要是出现了对应的字符，就从record--
		如果小于0，就说明ransomNote中的字母比magazine中的多，那么不符合要求


	*/
	bool canConstruct(string ransomNote, string magazine) {
		int record[26] = { 0 };//0-25代表26个英文字母 
		for (int i = 0; i < magazine.length(); i++) {
			// 通过recode数据记录 magazine里各个字符出现次数
			record[magazine[i] - 'a'] ++;
		}
		for (int j = 0; j < ransomNote.length(); j++) {
			// 遍历ransomNote，在record里对应的字符个数做--操作
			record[ransomNote[j] - 'a']--;
			// 如果小于零说明 magazine里出现的字符，ransomNote没有
			if (record[ransomNote[j] - 'a'] < 0) {
				return false;
			}
		}
		return true;
	}


	/*
		205. 同构字符串
		思路：
			哈希表：
			两个字符串中，比如abc。他对应的字符一定是每个不同的字符加不同的固定值。
			所以可以做个数组，下标是“字符-a”，值是“固定值”
			重要的思路就是下面的那个for遍历
			他这个题目说的不明白。他说的“如果 s 中的字符可以按某种映射关系替换得到 t ，那么这两个字符串是同构的”
			乍一看只需要管s到t就行了，其实不行！t到s的映射也得是唯一的。
			所以需要后面的判断
	*/
	bool isIsomorphic(string s, string t) {
		if (s.length() != t.length()) return false;

		int record1[256] = { 0 };//256个ASCII 字符
		int record2[256] = { 0 };//256个ASCII 字符
		for (size_t i = 0; i < 256; i++)
		{
			record1[i] = 1000;//设置成1000  是因为两个字符的差值 不可能是1000
			record2[i] = 1000;//设置成1000  是因为两个字符的差值 不可能是1000
		}


		for (size_t i = 0; i < s.size(); i++)
		{
			if (record1[t[i]] == 1000)
			{
				record1[t[i]] = s[i] - t[i];
			}
			else
			{
				if (record1[t[i]] != s[i] - t[i])
				{
					return 0;
				}
			}
			if (record2[s[i]] == 1000)
			{
				record2[s[i]] = s[i] - t[i];
			}
			else
			{
				if (record2[s[i]] != s[i] - t[i])
				{
					return 0;
				}
			}
		}
		return 1;
	}


	/*
	290. 单词规律

	思路：
		哈希表
		这个题目和“205. 同构字符串”思路是一样的，就最后多了一个if判断。
		重要的思路就是下面的那个for遍历
		他这个题目说的就清楚了。他说的“这里的 遵循 指完全匹配，例如， pattern 里的每个字母和字符串 s 中的每个非空单词之间存在着双向连接的对应规律。”
		所以还是做个双向的判断。
	*/
	bool wordPattern(string pattern, string s) {
		string record1[26] = { "" };//0-25代表26个英文字母 
		map<string, string> record;
		istringstream ss(s);
		string word;
		for (size_t i = 0; i < pattern.size(); i++)
		{
			ss >> word;
			if (record1[pattern[i] - 'a'] == "")
			{
				record1[pattern[i] - 'a'] = word;
			}
			else
			{
				if (record1[pattern[i] - 'a'] != word)
				{
					return false;
				}
			}
		}
		ss.clear();//重新赋值之前必须清空，这个api我用的也不多。
		ss.str(s);
		int i = 0;
		while (ss >> word) {

			if (record[word] == "")
			{
				record[word] = pattern[i];
			}
			else
			{
				if (record[word] != pattern.substr(i, 1))
				{
					return false;
				}
			}
			i++;
		}
		if (i != pattern.size())
		{
			return false;

		}
		return true;
	}

	/*
	242. 有效的字母异位词

	思路：
		哈希表
		三个for
		前两个for分别遍历s、t的字符，相同的字符加进去.
		最后就是判断各个字符出现的次数
	*/
	bool isAnagram(string s, string t) {
		int record1[26] = { 0 };//0-25代表26个英文字母 
		int record2[26] = { 0 };//0-25代表26个英文字母 

		for (size_t i = 0; i < s.size(); i++)
		{
			record1[s[i] - 'a']++;
		}
		for (size_t i = 0; i < t.size(); i++)
		{
			record2[t[i] - 'a']++;
		}

		for (size_t i = 0; i < 26; i++)
		{
			if (record1[i] - record2[i] != 0)
			{
				return false;
			}
		}
		return true;
	}



	/*
	49. 字母异位词分组
		首先需要理解字母异位词的含义，简单理解为：两字符串长度相同，字母相同，但顺序不同。
		字母异位词简意为两字符串长度相同，字母相同，顺序不同。

	参考：
		https://leetcode.cn/problems/group-anagrams/solutions/84916/c-yin-ru-hashbiao-shi-jian-32ms-ji-bai-9948-nei-cu/?envType=study-plan-v2&envId=top-interview-150
	
	思路：
		


	
	*/
	vector<vector<string>> groupAnagrams(vector<string>& strs) {

	}












};

void test()
{
	vector<int>a{ 1,2,3,4 };
}

int main()
{
	vector<int> nums{ 2,3,1,2,4,3 };
	vector<int> num1{ };
	vector<string> srtVec{ "foo","bar" };
	string str = "anagram";
	string t = "anagram";
	string strs{ "Marge, let's \"[went].\" I await {news} telegram." };
	vector<vector<int>> board = { {1,1,1},{1,0,1}, {7,8,9} };
	Solution a;



	/*
	for (size_t i = 0; i < num1.size(); i++)
	{
		std::cout << num1[i] << endl;
	}*/
	std::cout << a.isAnagram(str, t) << endl;
	//std::cout << a.trap(nums) << endl;
	//std::cout << a.isSubsequence("b", "abc") << endl;
	//std::cout << a.hIndex(nums) << endl;
	//std::cout << a.canCompleteCircuit(nums, num1) << endl;



}
