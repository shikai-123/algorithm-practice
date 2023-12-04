#pragma warning(disable : 4996)
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib> 
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <numeric> 
#include <map>
#include <unordered_set>
#include <queue>


using namespace std;


struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(NULL) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};



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



namespace String_Array
{
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

	};
}

namespace DoublePointer
{
	class Solution {

		/*
			125. 验证回文串
		*/
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

		/*
			392. 判断子序列
		*/
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


		/*
		167. 两数之和 II - 输入有序数组

		参考：
			https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/solutions/87919/yi-zhang-tu-gao-su-ni-on-de-shuang-zhi-zhen-jie-fa/?envType=study-plan-v2&envId=top-interview-150

		其他：
			这个和“1. 两数之和”这个题目很相似，但是编号1的题目中的数组的元素是无序的，
			这个题目中的元素是有序的。
		*/
		vector<int> twoSum2(vector<int>& numbers, int target) {
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


		/*
		11. 盛最多水的容器
		*/
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

		/*
		15. 三数之和
		*/
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
	};
}

namespace SlidingWindow
{
	class Solution {
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
	};
}

namespace Matrix
{
	class Solution {

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
	};
}

namespace Hash
{
	class Solution {
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
			对strs排序，这样的话，所谓的“字母异位词”就变成一样了。
			然后用“字母异位词”做map的key，value和这个单词往二维的vec中的行号。

		*/
		vector<vector<string>> groupAnagrams(vector<string>& strs) {

			vector<vector<string>> ret;
			map<string, int> words;
			string strTemp;
			int i = 0;//二维的vec中的行号
			for (string str : strs)
			{
				strTemp = str;
				sort(str.begin(), str.end());
				if (words.count(str) == 0)//找不到对应的key
				{
					vector<string> temp(1, strTemp);
					ret.push_back(temp);
					words[str] = i;
					i++;
				}
				else//已经有了对应的字符，那么就在相应的位置插入
				{
					ret[words[str]].push_back(strTemp);
				}
			}
			return ret;
		}


		/*
		1. 两数之和
			这个题目和“167. 两数之和 II - 输入有序数组”很想。上面有twoSum2函数 就是他。
			即使对数组排序了，这里不能直接用它的方法。

			我要做时间复杂的n的

		思路1：
			结合个“167. 两数之和 II - 输入有序数组”中的双指针的方法，另外在加上哈希表的方法。
			先排序，为了能用上双指针的方法。
			然后做个哈希表。数组的值做key，下标做value
			双指针遍历后，会得到新数组中符合条件的元素，然后从map中根据元素返回下表

			!!这个方法解决不了。重复的元素问题
			因为只存在一个有效答案，那么一旦出现重复的元素，则重复元素就是我们想要的值
		*/
		vector<int> twoSum(vector<int>& nums, int target) {

			unordered_map<int, int> num;
			int i = 0;
			int l = nums.size() - 1;

			for (int i = 0; i < nums.size(); i++)
			{
				if (num.count(nums[i]) == 0)//map中没找到这个元素
				{
					num[nums[i]] = i;
				}
				else//找到了这个元素，把相同的元素的下标返回
				{
					if (nums[num[nums[i]]] + nums[i] == target)
					{
						return vector<int>{ num[nums[i]], i};
					}
				}
			}
			sort(nums.begin(), nums.end());
			while (1)
			{
				int sun = nums[i] + nums[l];
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
					return vector<int>{ num[nums[i]], num[nums[l]]};
				}
			}
		}


		/*
		202. 快乐数
		思路：
			哈希表-借助无序map，不是数组的形式
			这个题目的难在的是这个题目的理解，理解这个数学题
			最后的结果要不就是1返回true，而返回false的条件就是出现了之前出现过的值。
			根据这个条件以及思路，代码就好做了
		其他：
			因为只需要键值，而不需要对应的value，所以用set容器是最好的
		*/
		bool isHappy(int n) {

			string strNums = to_string(n);
			int sum = 0;
			unordered_set<unsigned long long > tempNums;//放计算的结果
			while (1)
			{
				for (size_t i = 0; i < strNums.size(); i++)
				{
					int digit = strNums[i] - '0';
					sum += digit * digit;
				}
				if (sum == 1)
				{
					return 1;
				}
				if (tempNums.find(sum) == tempNums.end())
				{
					tempNums.insert(sum);
				}
				else//如果计算的结果之前就出现过，那么肯定是不行的。
				{
					return 0;
				}
				strNums = to_string(sum);
				sum = 0;
			}
			return 0;
		}


		/*
		219. 存在重复元素 II

		思路2：
			哈希表
			用这个思路，是因为这个题目在哈希表的分类中。
			unorder_map的key是数组的元素，对应元素的“最新的下标”是valuee
			最后遍历遍历map，一旦出现符合条件的返回true

		*/
		bool containsNearbyDuplicate1(vector<int>& nums, int k) {
			unordered_map<int, int>ret;

			for (size_t i = 0; i < nums.size(); i++)
			{
				if (ret.count(nums[i]) == 0)//没有出现过
				{
					ret[nums[i]] = i;//头一次出现距离就是0
				}
				else//不是第一次出现
				{
					//换成结构体性能肯定会更好
					auto iter = ret.find(nums[i]);
					if (i - iter->second <= k)
					{
						return 1;
					}
					ret[nums[i]] = i;//这个地方不会出现负值
				}
			}
			return 0;
		}

		/*
		219. 存在重复元素 II

		思路1：（！！到时候在试试）
			很明细 这是要用哈希表的思路啊。求一个数组中符号条件的最短的区间。
			细想，这个滑动窗口比较复杂，难在的是如果满足“nums[i] == nums[j]”有多个的话，那么就得是多个滑动窗口

			这个时候，就要换个思路，题目其实的意思就是在k的长度中，有没用相同的元素
			k就是滑动窗口，只要滑动窗口中出现了相同的元素，就返回true

			目前性能差点，时间都是花在set的api上了，可以参考
			https://leetcode.cn/problems/contains-duplicate-ii/solutions/1219675/gong-shui-san-xie-hua-dong-chuang-kou-yu-q02i/?envType=study-plan-v2&envId=top-interview-150
		*/
		bool containsNearbyDuplicate(vector<int>& nums, int k) {
			int L = 0;
			unordered_set<int>window;
			for (size_t R = 0; R < nums.size(); R++)
			{
				if (R < k + 1)
				{
					if (window.count(nums[R]) == 0)
					{
						window.insert(nums[R]);
					}
					else
					{
						return 1;
					}
				}
				else
				{
					cout << " " << nums[L] << endl;
					//window.erase(window.begin());//set容器是有序的，删除最前面的肯定不是串口最前面的。unordered_set顺序随机，你都不知道他是怎么拍的。肯定也不行。
					window.erase(nums[L]);
					L++;
					if (window.count(nums[R]) == 0)
					{
						window.insert(nums[R]);
					}
					else
					{
						return 1;
					}
				}

			}
			return 0;
		}

		/*
			128. 最长连续序列
				这个题目简单，但是列为中等的原因应该是因为要求时间复杂度位n的要求把
			思路1：
				如果直接用sort对vexctor排序，那么时间复杂度肯定不行。其平均时间复杂度为O(n log n)
				所以这个肯定不行，那么还得排序，还得时间复杂度可以，
				自然就是无序容器最合适，所以unordered_set。

			思路2：
				把vec中的元素放到set中，为了不是排序，而是插入和遍历的时候时间复杂度位1
				从头开始，判断他的+1或者-1是否存在，要是存在就进入while，
				+1的进去，就一直++,-1的进去就一直--，
				凡是操作一个值，就把他删掉。
				为什么删掉，就是已经参与计算的数，哪怕是被其他的数拉来的，已经被完全计算了，所以可以删掉
				出了循环之后，把两个位置的长度差记录下来，
				然后遇到新的数，肯定是之前没有计算到数，然后再重新计算。
		*/
		int longestConsecutive(vector<int>& nums) {
			unordered_set<int>set;
			for (int i = 0; i < nums.size(); i++)
			{
				set.insert(nums[i]);
			}
			int maxLen = 0;
			int tempLen = 0;
			int tempValue = 0;
			int BeginValue = 0;
			while (!set.empty())
			{
				tempValue = BeginValue = *set.begin();
				while (set.erase(++tempValue))//如果有下一位的数据就进去,没有可删的返回就是0
				{
					tempLen++;
				}
				tempValue = BeginValue;
				while (set.erase(--tempValue))
				{
					tempLen++;
				}
				set.erase(BeginValue);
				tempLen++;
				maxLen = maxLen > tempLen ? maxLen : tempLen;
				tempLen = 0;
			}
			return maxLen;
		}
	};
}

namespace Ranges
{
	class Solution {
		/*
228. 汇总区间
	“区间”这个不是思路，而是题型
思路：
	一般思路就是遍历这个vex
	记录头位置的字符，然后遍历；直到遇到了不连续的数字，然后把对应的字符加上.
	不断的循环这个方法，不断的。
	如果只有一个字符和任何字符都不连续，那么s和e相等，放入e即可。

唯一要注意的就是：
	nums[i + 1]如果正常遍历的话就会造成遍历越界，那么就应该加上“i + 1 < nums.size()”
	这个题目中加在for中是不行的，这样会导致最后的一个数字加不上。
	至于放在哪，根据题目要求来
*/
		vector<string> summaryRanges(vector<int>& nums) {
			vector<string>ret;
			int s, e = 0;//连续字符的开始和结束。
			for (size_t i = 0; i < nums.size(); i++)
			{
				s = nums[i];
				while ((i + 1 < nums.size()) && nums[i] + 1 == nums[i + 1])
				{
					i++;
				}
				e = nums[i];
				if (s != e)
				{
					string words = to_string(s) + "->" + to_string(e);
					ret.push_back(words);
				}
				else
				{
					ret.push_back(to_string(e));
				}
			}
			return ret;
		}


		/*
		56. 合并区间
		思路：

		参考：
		https://leetcode.cn/problems/merge-intervals/solutions/204805/chi-jing-ran-yi-yan-miao-dong-by-sweetiee/?envType=study-plan-v2&envId=top-interview-150
		*/
		vector<vector<int>> merge1(vector<vector<int>>& intervals) {
			//先按照intervals中元左值排序——升序
			sort(intervals.begin(), intervals.end(), [](const vector<int>& v1, const vector<int>& v2) {
				return v1[0] < v2[0];
			});

			vector<vector<int>> res(intervals.size());
			int idx = -1;
			for (const vector<int>& interval : intervals) {
				// 如果结果数组是空的，或者当前区间的起始位置 > 结果数组中最后区间的终止位置， ——或者说是新的一组interval元素在res的右侧，也就是两者没有任何交集。
				// 则不合并，直接将当前区间加入结果数组。  
				if (idx == -1 || res[idx][1] >= interval[0]) {
					res[++idx] = interval;
				}
				else {
					// 反之将当前区间合并至结果数组的最后区间 ——意思是说当interval和res有交集的话，那么新的数据区间的右侧的数据就是看res右值大，还是interval得右值大！
					res[idx][1] = max(res[idx][1], interval[1]);
				}
			}
			//这个是这样做，而不是直接返回res的原因是：vector<vector<int>> res(intervals.size());这回导致res的大小和原先是一样的
			return vector<vector<int>>(res.begin(), res.begin() + idx + 1);
		}

		/*
		57. 插入区间
		参考：
			https://leetcode.cn/problems/insert-interval/solutions/472553/57-cha-ru-qu-jian-mo-ni-cha-ru-xiang-jie-by-carlsu/?envType=study-plan-v2&envId=top-interview-150
		思路：
			参考了“代码随想”的思路
			一开始想着做些优化，尤其是min，max这几个函数的重复调用。
			如果把这两个函数冲while中拿出来的话。我试了好几次，没有完美的方案，而且会弄的很乱。就会造成问题，
			所以直接复现她的思路
		*/
		vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
			vector<vector<int>> ret;
			int index = 0;

			//首先判断intervals在newInterval之外的数据（在newInterval左边的）——判断依据就是intervals右值值《newInterval左值，有几个就在ret加几个
			while (index < intervals.size() && intervals[index][1] < newInterval[0])
			{
				ret.push_back(intervals[index]);
				index++;
			}

			/*
			左边干完之后，开始干中间和newInterval有交集的部分
			这部分最重要的就是mix和max函数在while中不断的使用
			具体思路就是：
			因为上面的while已经把不和newInterval接触的部分都弄上了，现在就处理接触的部分，这样的话，代码的判断就简单了。
			只要是接触到newInterval就进去while，上面的while中已经是没接触的判断，所以只需要判断右边，只要是intervals的左值一旦出现没有和newInterval右边接触了，那这一部分就是接触部分
			也就是intervals的左值不大于newInterval右值的都得进while
			一开始的思路都会想，没必要把mix和max函数在while中不断的使用，这样省不了性能，max min的时间复杂度是1，即使拿出去性能基本上没有变化。

			*/
			/*
			这样省不了性能
			if (index < intervals.size() && intervals[index][0] <= newInterval[1])
			{
				newInterval[0] = min(intervals[index][0], newInterval[0]);
				while (index < intervals.size()&& intervals[index][0] <= newInterval[1])
				{
					index++;
				}
				newInterval[1] = max(intervals[index-1][1], newInterval[1]);
			}*/



			while (index < intervals.size() && intervals[index][0] <= newInterval[1])
			{
				newInterval[0] = min(intervals[index][0], newInterval[0]);
				newInterval[1] = max(intervals[index][1], newInterval[1]);
				index++;
			}
			ret.push_back(newInterval);

			/*
				剩下的就是直接往ret中放就行了
			*/
			while (index < intervals.size())
			{
				ret.push_back(intervals[index]);
				index++;
			}

			return ret;
		}


		/*
		56. 合并区间
		思路：

		参考：
		https://leetcode.cn/problems/merge-intervals/solutions/204805/chi-jing-ran-yi-yan-miao-dong-by-sweetiee/?envType=study-plan-v2&envId=top-interview-150
		*/
		vector<vector<int>> merge(vector<vector<int>>& intervals) {
			//因为intervals中的各组元组的排序没有一个规律，这种解法需要升序，所以需要排列
			sort(intervals.begin(), intervals.end(), [](const vector<int> &v1, const vector<int> &v2)->int
			{
				return v1[0] < v2[0];
			});
			vector<vector<int>>ret(intervals.size());
			int index = -1;
			/*
			因为intervals.length大小不为空。所以ret中最少是有1个元素的。
			所以，当遍历intervals一开始的时候，要把intervals都放到ret中。或者当intervals左值大于ret中的右值，也要另起一个新的vec。也就是新的intervals和ret不再重叠的时候
			要是不大于，就说明当前intervals和ret的中的元素有重叠，那么就要合并
			合并的方法，就是判断当前intervals的右值和ret右值，谁大用谁的谁的值
			*/
			for (auto interval : intervals)
			{
				/*
				在ret中开辟新的vec，这个时候有了左值和右值
				*/
				if (index == -1 || interval[0] > ret[index][1])
				{
					ret[++index] = interval;
				}
				else//vec中的右值更新
				{
					ret[index][1] = max(interval[1], ret[index][1]);
				}
			}
			return vector<vector<int>>(ret.begin(), ret.begin() + index + 1);
		}

		/*
		452. 用最少数量的箭引爆气球
		思路：
			贪心思路；
			具体，参考注释和链接
		参考：
			https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/submissions/479348550/?envType=study-plan-v2&envId=top-interview-150
		*/
		int findMinArrowShots(vector<vector<int>>& points) {
			if (points.empty())
			{
				return 0;
			}
			/*能用引用，就用引用，节省性能，根据题目的评论中，发现加不加对性能影响很大 */
			sort(points.begin(), points.end(), [](const vector<int>& v1, const vector<int>& v2) {
				return v1[0] < v2[0];
			});

			int ret = 1;
			for (size_t i = 1; i < points.size(); i++)
			{
				/*
					如果两个球不挨着了，那么肯定就是需要一个箭来射穿前面的气球
					那么判断条件就是左边的球的右边小于右边求的左边，就是两球不挨着，
					这个题目中，如果两个边边重叠就算挨着，
					所以判断条件就是《
				*/
				if (points[i - 1][1] < points[i][0])
				{
					ret++;
				}
				else
				{
					/*
					如果挨着了，那么就更新左边气球的右边界。
					是两个右边界的较小的值
					如果想要和这两个挨着的球，用同一只箭，那么一定要和较小的右边来比较。
					所以这里保存了较小的边。
					*/
					points[i][1] = min(points[i - 1][1], points[i][1]);
				}
			}
			return ret;
		}
	};
}

namespace Stack {

	/*
	155. 最小栈
	思路：
		用multiset和和stack容器搭配使用即可
	*/
	class MinStack {
	public:
		MinStack() {

		}

		void push(int val) {
			stk.push(val);
			set.insert(val);
		}

		void pop() {
			set.erase(set.find(stk.top()));
			stk.pop();
		}

		int top() {
			return  stk.top();
		}
		//并能在常数时间内检索到最小元素的栈。
		int getMin() {
			return *set.begin();
		}

	private:
		stack<int>stk;
		multiset<int>set;
	};
	class Solution {
	public:
		/*
20. 有效的括号
前言：
	这是“栈”思路的第一个题目，
思路：
	括号要一一匹配，这个是最适合用栈容器的。
	遍历这个s，如果是括号的左边的就往栈里放，
	拿的时候，不能像左边那样，直接就弄了。得有个判断条件
	得判断你要拿的这个括号是不是和栈最上面的元素有对应关系。
	如果有对应关系，那么就那，没有就直接返回false。

	对应关系就是：(40  )41   [91 ]93      {123      }125

	遍历结束后，如果栈里面被拿空了，那么说明整个字符串没有问题，只要不是空的，说明不行
*/
		bool isValid(string s) {
			stack<char> stk;

			for (const char& c : s)
			{
				if (c == '(' || c == '[' || c == '{' || stk.empty())
				{
					stk.push(c);
				}
				else
				{
					if (stk.top() + 1 == c || stk.top() + 2 == c)
					{
						stk.pop();
					}
					else
					{
						return false;
					}
				}
			}
			if (stk.empty())
			{
				return true;
			}
			return false;
		}

		/*
		71. 简化路径
		思路：
			这个也简单，不同的字符，代表出栈和入栈，然后看看最后栈里面留的是谁
			我这个思路毕竟是自己想的，虽然有点丑，但是记忆方便
			总的来说，就是先分割字符，然后判断字符是什么样的，
			再决定是入栈，出栈，还是无操作。
			和这个题解的性能一样。
			https://leetcode.cn/problems/simplify-path/?envType=study-plan-v2&envId=top-interview-150
		*/
		string simplifyPath(string path)
		{
			int pos = 0;//上次找到关键词的下一处位置
			string tmp = "";
			string retStr = "";
			stack<string>stk;
			while (true)
			{
				int ret = path.find("/", pos);
				if (ret < 0)
				{
					tmp = path.substr(pos, path.size() - pos);//有可能最后不是以/结尾，但是要把最后的字符拿出来就得是总的长度-上次关键字的长度
					if (tmp == "")
					{
						break;
					}
					if (tmp != "."&&tmp != "..")
					{
						stk.push(tmp);
					}
					else if (tmp == ".." && !stk.empty())
					{
						stk.pop();
					}
					break;
				}
				tmp = path.substr(pos, ret - pos);
				if (tmp == "")
				{
					pos = ret + 1;
					continue;
				}
				else if (tmp != "."&&tmp != "..")
				{
					stk.push(tmp);
				}
				else if (tmp == ".." && !stk.empty())
				{
					stk.pop();
				}
				pos = ret + 1;
			}
			if (stk.empty())
			{
				retStr = retStr + "/";
			}
			while (!stk.empty())
			{
				retStr.insert(0, "/" + stk.top());
				stk.pop();
			}
			return retStr;
		}

		/*
		150. 逆波兰表达式求值
		思路：
			遍历tokens，到栈中，
			遇到运算符的时候，就往前遍历两个元素，
			然后根据这个运算符来计算结果，
			算到的结果再次放到栈中。
			知道结束，返回计算的结果。
		*/
		int evalRPN(vector<string>& tokens) {
			if (tokens.size() < 2)
			{
				return stoi(tokens[0]);
			}
			stack<string>stk;
			int ret = 0;
			for (const string& token : tokens)
			{
				if (token == "+" || token == "-" || token == "*" || token == "/")
				{
					int r = atoi(stk.top().c_str());
					stk.pop();
					int l = atoi(stk.top().c_str());
					stk.pop();
					switch (token[0])
					{
					case 42:
						ret = r * l;
						break;
					case 43:
						ret = r + l;
						break;
					case 45:
						ret = l - r;
						break;
					case 47:
						ret = l / r;
						break;
					default:
						break;
					}
					stk.push(to_string(ret));
				}
				else
				{
					stk.push(token);
				}
			}
			return ret;
		}

		/*
		224. 基本计算器
		！！还没做，思路有点复杂
		参考
		https://leetcode.cn/problems/basic-calculator/solutions/465311/chai-jie-fu-za-wen-ti-shi-xian-yi-ge-wan-zheng-j-2/?envType=study-plan-v2&envId=top-interview-150
		*/
		int calculate(string s) {
			if (s.size() < 2)
			{
				return stoi(s);
			}
			stack<string>stk;
			int ret = 0;
			string temp = "";

			for (const char& token : s)
			{
				if (token == ')')
				{

				}
				else
				{
					if (token == '+' || token == '-' || token == '*' || token == '/')
					{
						int r = stoi(stk.top());
						stk.pop();
						int l = stoi(stk.top());
						stk.pop();
						switch (token)
						{
						case 42:
							ret = r * l;
							break;
						case 43:
							ret = r + l;
							break;
						case 45:
							ret = l - r;
							break;
						case 47:
							ret = l / r;
							break;
						default:
							break;
						}
						stk.push(to_string(ret));
					}
					else
					{
						temp += token;
					}
				}
			}

			return ret;
		}
	};
}

namespace LinkedList
{
	class Solution {
	public:
		/*
		141. 环形链表
			哈希表方法
			核心在于要把节点指针放进去，因为有可能出现节点数据val相同，但是数据指针不会相同的。
			如果发现了重复的指针，那么就是同一个节点，
			说明该链表出现了环。
		*/
		bool hasCycle1(ListNode *head) {
			unordered_set<ListNode *> p;
			while (head != nullptr)
			{
				if (p.find(head) == p.end())
				{
					p.insert(head);
				}
				else
				{
					return true;
				}
				head = head->next;
			}

			if (p.size() == 1)
			{
				return false;
			}
			return false;
		}
		/*
		141. 环形链表
		思路：
			双指针
			思路也很简单，主要是熟悉一下双指针用法。
			性能和我上面差不多
			一个快的，一个慢的。所谓快慢就是在一个循环中，快的走两个next慢的走一个next
			如果有环，快的慢的，早晚会遇上
		参考：
			https://leetcode.cn/problems/linked-list-cycle/solutions/175734/yi-wen-gao-ding-chang-jian-de-lian-biao-wen-ti-h-2/?envType=study-plan-v2&envId=top-interview-150
		*/
		bool hasCycle(ListNode *head) {
			ListNode *fast = head, *low = head;
			//链表有环的话，他的节点中，就不会有nullptr，如果出现了nullptr，就说明链表没有环
			while (low != nullptr&&fast != nullptr&& low->next != nullptr&&fast->next != nullptr)
			{
				fast = fast->next;
				if (fast->next != nullptr)
				{
					fast = fast->next;
				}
				if (fast == low)
				{
					return true;
				}
				low = low->next;
			}
			return false;
		}

		ListNode* insertData(ListNode* head, int data) {
			ListNode* newNode = new ListNode(data); // 创建新节点

			if (head == NULL) {
				head = newNode; // 如果链表为空，新节点成为头节点
			}
			else {
				ListNode* curr = head;

				while (curr->next != NULL) {
					curr = curr->next; // 遍历链表找到最后一个节点
				}

				curr->next = newNode; // 将新节点插入到链表末尾
			}

			return head; // 返回更新后的头节点
		}

		/*
		2. 两数相加
			转成数字不行，有的数特别大，小点的数我这个代码没问题。
		*/
		ListNode* addTwoNumbers1(ListNode* l1, ListNode* l2) {
			unsigned long long l = 0, r = 0, sum = 0;
			int exponent = 0;//指数
			ListNode* ret = nullptr;
			while (l1 != nullptr)
			{
				l += l1->val*pow(10, exponent++);
				l1 = l1->next;
			}
			exponent = 0;
			while (l2 != nullptr)
			{
				r += l2->val*pow(10, exponent++);
				l2 = l2->next;
			}
			sum = r + l;
			string sumStr = to_string(sum);
			for (int i = sumStr.size() - 1; i >= 0; i--)
			{
				ret = insertData(ret, stoi(string(1, sumStr[i])));
			}
			return ret;
		}

		/*
		2. 两数相加
		参考：
			https://leetcode.cn/problems/add-two-numbers/solutions/4375/liang-shu-xiang-jia-by-gpe3dbjds1/comments/1554952
			他的代码是根据这个回答中改进的，思路是一样的，代码更简洁
		思路：
			放弃里把链表中的全部数字组合到一块，然后再计算的方法。
			这样避免了数据较大导致的数据溢出。
			一个一个加，然后得到的结果大于10，就出10，得到的结果，
			给下一次计算加上。不断的这样循环。
			循环结束的条件就是两个链表都是空的情况。
		*/
		ListNode* addTwoNumbers(ListNode *l1, ListNode *l2) {
			ListNode * note = new ListNode(0);
			ListNode *pre = note;
			int jinwei = 0;
			int sum = 0;

			while (l1 != nullptr || l2 != nullptr)
			{
				int l = l1 != nullptr ? l1->val : 0;
				int r = l2 != nullptr ? l2->val : 0;
				sum = l + r + jinwei;
				jinwei = sum / 10;

				/*
					!!通过循环结构，往后插数据的代码，
					就是下面这两句，
					非常的重要！
					pre 我们理解为链表当前最后面的数据，
					next就是我们要插入的数据
				   然后，pre = pre->next;
				   这样pre就又可以代表最后的数据了
				   这样的话，就是需要两个ListNode变量。
				   一个代表总的链表，也就是note
				   一个就是代表最后的节点，也就是pre。
				 */
				pre->next = new ListNode(sum % 10);
				pre = pre->next;
				//如果l1 l2的长度不一样，这里的if的作用就显出来了
				if (l1 != nullptr) l1 = l1->next;
				if (l2 != nullptr) l2 = l2->next;
			}
			if (jinwei > 0)
			{
				pre->next = new ListNode(jinwei);
			}

			return note->next;
		}

		/*
		21. 合并两个有序链表
		我自己的方法，性能差点，思路还行，代码麻烦点
		*/
		ListNode* mergeTwoLists1(ListNode* list1, ListNode* list2) {

			ListNode *note = new ListNode(0);
			ListNode *end = note;

			while (list1 != nullptr || list2 != nullptr)
			{

				int t = list1 != nullptr ? list1->val : 0;
				int l = list2 != nullptr ? list2->val : 0;

				if (t > l&&list2 != nullptr)
				{
					end->next = new ListNode(l);
					end = end->next;
					if (list2 != nullptr) list2 = list2->next;

				}
				else if (l > t&&list1 != nullptr)
				{
					end->next = new ListNode(t);
					end = end->next;
					if (list1 != nullptr) list1 = list1->next;
				}
				else
				{

					if (list1 != nullptr)
					{
						end->next = new ListNode(t);
						end = end->next;
						list1 = list1->next;
					}
					if (list2 != nullptr)
					{
						end->next = new ListNode(l);
						end = end->next;
						list2 = list2->next;
					}

				}
			}
			return note->next;
		}


		/*
		21. 合并两个有序链表
		参考：
		https://leetcode.cn/problems/merge-two-sorted-lists/solutions/227293/merge-two-sorted-lists-by-ikaruga/comments/2128427
		思路：
			思路也是比较简单；
			先创建一个链表，然后比较两个已有的链表，
			谁的数值小，就把谁的节点接在后面，
			直到把其中的一个接完。
			因为每次都是只接一个，所以必然存在有一个先接完，有一个还没接完。
			所以任意一个接完了，都退出while。
			因为给的两个链表都是递增链表。
			所以没接完的一定比现在的数都大。
			所以直接接在后面就行
		*/
		ListNode* mergeTwoLists2(ListNode* list1, ListNode* list2) {

			auto dummy = new ListNode(0);
			auto cur = dummy;
			while (list1 && list2) {
				auto pp = (list1->val < list2->val) ? &list1 : &list2;  // 获取俩链表当前值小的结点
				cur->next = *pp;    // cur 指向值小的结点
				cur = cur->next;    // cur 后移
				*pp = (*pp)->next;  // *pp 也要后移，不然下次循环比较的还是旧的list1或list2结点
			}
			// 循环结束，list1 和 list2 其中有一个为空，但不知道是哪个
			cur->next = (list1) ? list1 : list2;

			return dummy->next;
		}

		ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
			ListNode* note = new ListNode(0);
			ListNode* end = note;
			while (list1 != nullptr && list2 != nullptr)
			{
				/*
				那个节点的数值小，就用谁的节点。
				这里取指针的原因有两个。
				1、用二级指针，来统一管理list1，list2，这两个变量。
					这样做的好处，下面的代码中，不用在特意对list1和list2做两个判断来分别做处理。
					直接用指针代替他俩，一处代码就能解决。
				2、如果不用二级指针的话；
					假设用一级指针的：
					ListNode * cur = list1;
					后面的代码
					cur = (*cur)->next;
					只能改变cur，而不能改变list1或者是list2。
					指针的核心就是：
					给变量去另外一个名字，然后去管理他。
					ListNode * cur = list1;
					cur=xx; 这种就是单纯的赋值，不会改变list1对应变量的值。

					但是如果用二级指针的话。
					ListNode ** cur = &list1;
					*cur = xx;就是改变list1的值。

				*/
				ListNode **cur = list1->val < list2->val ? &list1 : &list2;
				/*把符合条件的节点，接到后面*/
				end->next = *cur;
				end = end->next;
				/*然后，把谁接了，就完后移动节点
				!这里要注意优先级的问题；
				优先级依次是：
				（） -》 *
				如果是这种*cur = *(cur)->next;
				就是先访问(cur)->next。这种就是错误的。
				*/
				*cur = (*cur)->next;
			}
			end->next = list1 == nullptr ? list2 : list1;
			return note->next;
		}


		class Node {
		public:
			int val;
			Node* next;
			Node* random;

			Node(int _val) {
				val = _val;
				next = NULL;
				random = NULL;
			}
		};


		/*
		138. 随机链表的复制
		思路：
			这个题目，难度有2，一是理解题目，二是链表中的“random”指针的指向
			1、如果是空空链表，就返回空的
			2、构建无序map，然后用链表节点的指针做key，表节点的指针做key.
			这么做的原因1是方便找到链表，2是找链表的下一个节点的时候也好弄，
			把这个map按照链表的顺序加满。
			这样的话，可以直接用链表的节点的指针地址，直接访问对应的链表节点。

			3、通过链表节点的指针，遍历所有的map，顺便赋值。
			通过指针，找到对应的节点数据
			比如val就赋值同一个节点的map
			next自然就是“下一个节点地址”，而下个节点的地址自然就是以下个节点地址为key的map；
			同理，random也是同样的道理。

			4、最后返回的就是map的“map[head]”

		参考：
			https://leetcode.cn/problems/copy-list-with-random-pointer/solutions/2361362/138-fu-zhi-dai-sui-ji-zhi-zhen-de-lian-b-6jeo/?envType=study-plan-v2&envId=top-interview-150
			中的哈希表的方法
		*/
		Node* copyRandomList(Node* head) {
			if (head == nullptr)
			{
				return head;
			}
			unordered_map<Node*, Node*>map;
			Node* cur = head;
			Node* ret = nullptr;
			while (cur != nullptr)
			{
				map[cur] = new Node(0);
				cur = cur->next;
			}
			cur = head;
			while (cur != nullptr)
			{
				map[cur]->val = cur->val;
				map[cur]->next = map[cur->next];
				map[cur]->random = map[cur->random];
				cur = cur->next;
			}
			return map[head];

		}

		/*
		92. 反转链表 II

		思路：
			具体思路参考：这个链接
			另外的，关于链表翻转的好几种情况的写法，已经放在笔记中的-《链表》部分。
			这个一定要看看
		参考：
		https://leetcode.cn/problems/reverse-linked-list-ii/solutions/37247/bu-bu-chai-jie-ru-he-di-gui-di-fan-zhuan-lian-biao/?envType=study-plan-v2&envId=top-interview-150

		*/
		ListNode* successor = nullptr; // 后驱节点

		// 反转以 head 为起点的 n 个节点，返回新的头结点
		ListNode* reverseN(ListNode* head, int n) {
			if (n == 1) {//n==1代表链表反转到最后一个点了。这个递归该结束了
				successor = head->next;
				return head;
			}
			ListNode* last = reverseN(head->next, n - 1);//返回的依旧是反转后的头结点
			//1->2->1
			head->next->next = head;
			// 让反转之后的 head 节点和后面的节点连起来
			head->next = successor;
			return last;
		}

		/*
		用3个节点的链表。m=n=3来表示

		压栈
		1 2 34

		出栈
		返回翻转的43
		head->next接43  然后返回head 2
		再然后返回 head->next接2  然后返回head 1
		最后，上面返回的这个1即使整个链表的头指针
		12 43
		*/
		ListNode* reverseBetween(ListNode* head, int m, int n) {
			//n==1代表链表反转到最后一个点了。这个递归该结束了
			if (m == 1) {
				return reverseN(head, n);
			}
			//每次执行的时候，一定是head->nex，因为reverseBetween返回的是head后面的节点
			head->next = reverseBetween(head->next, m - 1, n - 1);
			return head;//返回一定要是head，具体看注释
		}

		ListNode* reverseBetween1(ListNode* head, int left, int right) {
			stack<ListNode*> stk;
			int index = 1;
			ListNode* Lhead = head;

			ListNode* note = new ListNode(0);
			ListNode* end = note;



			while (head != nullptr)
			{
				if (left <= index && index <= right)
				{
					stk.push(head);
				}
				index++;
				head = head->next;
			}
			head = Lhead;
			index = 1;


			while (head != nullptr)
			{
				if (left <= index && index <= right)
				{
					while (!stk.empty())
					{
						/*
						！有问题在于stk.top()返回的不是一个点，而是返回的是这个点以及之后到尾巴的链表。
						*/
						end->next = stk.top();
						end = end->next;
						stk.pop();

						index++;
						head = head->next;
					}
				}
				end->next = head;
				end = end->next;

				index++;
				head = head->next;
			}

			return note->next;
		}


		/*
		19. 删除链表的倒数第 N 个结点
		参考：
			https://leetcode.cn/problems/remove-nth-node-from-end-of-list/?envType=study-plan-v2&envId=top-interview-150
		思路：
			双指针，这样就能遍历一遍的时候，直接拿到要删除节点的对应位置。
			1、增加虚拟头结点。
				这么做的好处是方便删除头节点；具体参考：https://mp.weixin.qq.com/s/L5aanfALdLEwVWGvyXPDqA
			2、定义双指针，fast和low。
				fast先走n+1。这样的目的是为了让low落在要删除的点的前面，这样的话，才能走链表删除的统一逻辑——要删除的节点，p->next=p->next->next;p是要被删除的节点前一个节点
			3、然后移动双指针，知道fast到了最后的位置。
			4、然后low->next=low->next->next删除对应的点
			5、返回dummy->nest;
		*/
		ListNode* removeNthFromEnd(ListNode* head, int n) {
			ListNode* dummy = new ListNode(0);
			dummy->next = head;
			ListNode* fast = dummy, *slow = dummy;

			// 让fast指针先走n+1步
			for (int i = 0; i <= n; i++) {
				fast = fast->next;
			}

			// 当fast指针到达末尾时，slow指针就指向了要删除节点的前一个节点
			while (fast != nullptr) {
				fast = fast->next;
				slow = slow->next;
			}
			//https://leetcode.cn/problems/remove-nth-node-from-end-of-list/solutions/655411/dai-ma-sui-xiang-lu-19-shan-chu-lian-bia-2hxt/comments/2172664
			//delete low->next;//!!!!!!!!访问到这句就奔溃！！！
			slow->next = slow->next->next;
			return dummy->next;
		}


		/*
		82. 删除排序链表中的重复元素 II
		思路：
			为了方便删除头结点，要加一个虚拟头结点。
		参考：
			https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/solutions/678600/tong-yong-shan-chu-zhong-fu-jie-dian-lia-od9g/?envType=study-plan-v2&envId=top-interview-150

			核心就是2部分，看下面的注释即可
		*/

		ListNode* deleteDuplicates1(ListNode* head)
		{
			ListNode* dummy = new ListNode(-200), *tail = dummy;//tail接上了dummy
			while (head)
			{
				if (head->next == nullptr or head->val != head->next->val)
				{
					//tail接上了head。
					tail->next = head;
					tail = head;
				}
				while (head->next and head->val == head->next->val)
				{
					/*
						每次执行这个代码的时候，head的位置都会往后移动一下。
						这样在内存里看的话，haed之前的部分就被删除。
						删除的原因是因为：
						head = head->next;导致head的内存地址被更新成新的！
						然后head之前点的next就失效了。
						有效的也就只有head以及他之后的这部分链表了。

						可以根据这个特性来做删除。

						一般我们常说的删除就是：跳过这个点。
						p->next = p->next->next;

						总结的话，要是想在head上删除
						前面的点：用head=head->next;
						后面的点：用p->next = p->next->next;
					*/
					head = head->next;
				}
				head = head->next;
			}
			/*
				每次尾巴的下一个都要清零
				清零的原因是：
				1、dummy和tail配合，通过尾插法构建了一个新的链表，但是毕竟tail通过“tail->next = head;”接上了haed整个链表。
				按道理来说，每接一个都要对dummy尾巴的next设置nullptr，也就是“tail->next = nullptr;”
				这样就能保证dummy中包含的链表只有新插入的部分。而去掉head部分。
				“tail->next = head;”
			*/
			tail->next = nullptr;
			return dummy->next;
		}


		ListNode* deleteDuplicates2(ListNode* head)
		{
			ListNode* dummy = new ListNode(-200), *tail = dummy;//tail接上了dummy
			while (head)
			{
				if (head->next == nullptr or head->val != head->next->val)
				{
					tail->next = new ListNode(head->val);
					tail = tail->next;
				}
				while (head->next and head->val == head->next->val)
				{
					head = head->next;
				}
				head = head->next;
			}
			/*
				tail->next = new ListNode(head->val);
				tail = tail->next;
				如果尾巴往后面的接法是新建的节点，那么tail后面自然就是null（看构造函数）
				就完全不用管后面了。下面这句“tail->next = nullptr;”就不用做了
				唯一的不好就是空间复杂度差点。
			*/
			//tail->next = nullptr;
			return dummy->next;
		}

		/*
			我自己写的
		*/
		ListNode* deleteDuplicates(ListNode* head)
		{
			ListNode* dummy = new ListNode(0);
			ListNode* end = dummy;

			while (head != nullptr)
			{
				/*
					加“head->next==nullptr”，是为了保证能把原始链表中的最后一个元素加上
					head 已经没有下一个节点，head 可以被插入
					head 有一下个节点，但是值与 head 不相同，head 可以被插入
				*/
				if (head->next == nullptr or head->val != head->next->val)
				{
					end->next = new ListNode(head->val);
					end = end->next;
				}
				/*
					加这个“head->next!=nullptr”是为了保证当原始链表中最后两个是相等的时候，都能抛掉
					head有下个节点，并且下个节点的值和当前的值是相同的，可以把当前删除。
				*/
				while (head->next != nullptr and  head->val == head->next->val)
				{
					head = head->next;
				}
				head = head->next;
			}
			return dummy->next;
		}


		/*
		61. 旋转链表
		思路：
			移动范围%链表长度=实际需要移动的位置。
			利用双指针的思想，迅速的遍历到尾部

			思路是对的，但是写的代码不行。
			说到底还是对链表掌握不行

		*/
		ListNode* rotateRight1(ListNode* head, int k) {
			ListNode* dummy = new ListNode(0);
			ListNode* end = dummy;
			ListNode* oldHead = head;

			int len = 0;
			while (head != nullptr)
			{
				head = head->next;
				len++;
			}
			if (len == 0) return dummy->next;
			if (k == 0) return oldHead;
			len = k % len;
			head = oldHead;
			ListNode* fast = head;
			ListNode* slow = head;

			while (len-- > 0)
			{
				fast = fast->next;
			}


			while (fast->next != nullptr)
			{
				fast = fast->next;
				slow = slow->next;

				end->next = fast;
				end = end->next;//dummy接45
			}
			(*slow).next = nullptr;//head只剩123
			while (head != nullptr)
			{
				end->next = head;
				end = end->next;//dummy接123
				head = head->next;
			}
			return dummy->next;
		}


		ListNode* rotateRight(ListNode* head, int k)
		{
			if (head == nullptr || k == 0) return head;
			// 计算有效的 k 值：对于与链表长度成整数倍的「旋转」都是没有意义的（旋转前后链表不变）
			int tot = 0;
			auto tmp = head;
			while (tmp != nullptr && ++tot > 0) tmp = tmp->next;
			k %= tot;
			if (k == 0) return head;
			//以上和我的思路 都一样的
			auto slow = head, fast = head;
			while (k-- > 0) fast = fast->next;
			while (fast->next != nullptr) {
				slow = slow->next;
				fast = fast->next;
			}
			// 保存新头结点，并将新尾结点的 next 指针置空
			auto nHead = slow->next;//接上45
			slow->next = nullptr;// head 只剩123
			// 将新链表的前半部分（原链表的后半部分）与原链表的头结点链接上
			fast->next = head;
			return nHead;
		}

		/*
		86. 分隔链表
		思路：
			遍历链表，和x比较，然后放到不同的链表中。
			如果存在小于x的链表，就把小于x的链表的指针移动到最后，然后接上大于x的链表即可
			没有的话，就直接返回大于x的链表
			这样就能包括所有的情况，小于x的要不有要不没有，有的话就加上，没有就返回其他的
			性能不错，空间复杂度差点

			后来根据人家的有优化了。
		参考：
			https://leetcode.cn/problems/partition-list/solutions/2362068/86-fen-ge-lian-biao-shuang-zhi-zhen-qing-hha7/?envType=study-plan-v2&envId=top-interview-150
			他这也是双指针，但是和只有双指针的名字，毕竟用了两个指针
		*/
		ListNode* partition(ListNode* head, int x) {
			if (head == nullptr) return head;

			ListNode* dummy = new ListNode(0);//存储小于x的链表
			ListNode* end = dummy;
			ListNode* newHead = new ListNode(0);//存储大于等于x的链表
			ListNode* newEnd = newHead;


			while (head != nullptr)
			{
				if (head->val < x)
				{
					//end->next = new ListNode(head->val);
					end->next = head;
					end = end->next;
					//end->next = nullptr;//！加这个想着省newEnd->next = nullptr;，但是不行，因为这样会导致head后面链表断开。
				}
				else
				{
					//newEnd->next =  new ListNode(head->val);;
					newEnd->next = head;
					newEnd = newEnd->next;
				}
				head = head->next;
			}
			//优化了一下。这个end->next就是dummy最尾巴的指针。把这个忘记了。不知道为啥时间复杂度一直到不了0.下面多个while还能到0
			newEnd->next = nullptr;//如果不用了new了，那么每个节点都会跟着后面的节点，这样的话，有肯能会回环。比如 4321 k=4
			end->next = newHead->next;
			return dummy->next;

			//if (dummy->next != nullptr)
			//{
			//	ListNode* newDummy = dummy->next;
			//	while (newDummy->next != nullptr)
			//	{
			//		newDummy = newDummy->next;
			//	}
			//	//以上拿到dummy最尾巴的指针
			//	newDummy->next = newHead->next;
			//	return dummy->next;
			//}
			//else
			//{
			//	return newHead->next;
			//}
		}


		/*
			25. K 个一组翻转链表
			和92题对着看，在理解92的基础上，这个很简单。
			思路：
				用链表翻转中的中间点翻转
				用while遍历，每k个开始调用函数。

		*/
		ListNode* reverseKGroup(ListNode* head, int k) {

			int index = 0;
			int b = 1;

			ListNode* oldHead = head;
			while (head != nullptr)
			{
				head = head->next;
				index++;
				if (index % k == 0)
				{
					oldHead = reverseBetween(oldHead, b, b + k - 1);
					b = b + k;
				}
			}

			return oldHead;
		}

		/*
			68. 文本左右对齐
			!太难了。看不懂
		*/
		string fillWords(vector<string>& words, int bg, int ed, int maxWidth, bool lastLine = false)
		{
			int wordCount = ed - bg + 1;
			int spaceCount = maxWidth + 1 - wordCount;  // 除去每个单词尾部空格， + 1 是最后一个单词的尾部空格的特殊处理
			for (int i = bg; i <= ed; i++)
			{
				spaceCount -= words[i].size();  // 除去所有单词的长度
			}

			int spaceSuffix = 1;    // 词尾空格
			int spaceAvg = (wordCount == 1) ? 1 : spaceCount / (wordCount - 1);     // 额外空格的平均值
			int spaceExtra = (wordCount == 1) ? 0 : spaceCount % (wordCount - 1);   // 额外空格的余数

			string ans;
			for (int i = bg; i < ed; i++)
			{
				ans += words[i];    // 填入单词
				if (lastLine)   // 特殊处理最后一行
				{
					fill_n(back_inserter(ans), 1, ' ');
					continue;
				}
				fill_n(back_inserter(ans), spaceSuffix + spaceAvg + ((i - bg) < spaceExtra), ' ');  // 根据计算结果补上空格
			}
			ans += words[ed];   // 填入最后一个单词
			fill_n(back_inserter(ans), maxWidth - ans.size(), ' '); // 补上这一行最后的空格
			return ans;
		}

		vector<string> fullJustify(vector<string>& words, int maxWidth)
		{
			vector<string> ans;
			int cnt = 0;
			int bg = 0;
			for (int i = 0; i < words.size(); i++)
			{
				cnt += words[i].size() + 1;

				if (i + 1 == words.size() || cnt + words[i + 1].size() > maxWidth)
				{   // 如果是最后一个单词，或者加上下一个词就超过长度了，即可凑成一行
					ans.push_back(fillWords(words, bg, i, maxWidth, i + 1 == words.size()));
					bg = i + 1;
					cnt = 0;
				}
			}
			return ans;
		}
		/*
	146. LRU 缓存
		要学会用两种方法去实现。
		一种是标准std::list
		一种手动创建双向链表

		参考：
		思路：
		https://leetcode.cn/problems/lru-cache/solutions/12711/lru-ce-lue-xiang-jie-he-shi-xian-by-labuladong/?envType=study-plan-v2&envId=top-interview-150
		代码：
		https://leetcode.cn/problems/lru-cache/solutions/12711/lru-ce-lue-xiang-jie-he-shi-xian-by-labuladong/comments/162138
		这个代码中。链表最后的元素，是最老的元素。
	*/
		class LRUCache {
		public:
			LRUCache(int capacity) : cap(capacity) {

			}
			int get(int key)
			{
				if (map.find(key) == map.end()) return -1;
				auto key_value = *map[key];
				cache.erase(map[key]);
				cache.push_front(key_value);
				map[key] = cache.begin();
				return key_value.second;
			}

			void put(int key, int value) {
				if (map.find(key) == map.end())
				{
					if (cache.size() == cap)
					{
						map.erase(cache.back().first);
						cache.pop_back();
					}
				}
				else
				{
					cache.erase(map[key]);
				}
				cache.push_front({ key, value });
				map[key] = cache.begin();//hashmap对应关系也得改变?什么时候变呢？发现都是在插入新的list节点的时候，对应关系要变化。 这是自然，新的list没有对应关系，自然要对应上
			}
		private:
			int cap;
			list<pair<int, int>> cache;//这是双向链表，用双向链表而不是单向链表的原因是因为为了保证删除的时间复杂度是1。
			unordered_map<int, list<pair<int, int>>::iterator> map;

			/*
				map存在的唯一目的就是为了查找的时候，时间复杂度是1.用来弥补list查找无法做到时间复杂度是1
				list是方便处理最新的节点。为了拿到最新得要是排序，hashmap无法排序。所以借用list。
				所谓的排序就是找到对应的点，把他删掉，然后再接到最前面，（在本代码中代表最新的数据），从而完成了最新的数据在前面，老的数据在后面
				list是怎么排序的？
				利用双向list的插入和删除。时间复杂度是1
				hashmap的插入和删除的时间复杂度是1，那为什么用list呢？
				应为hashmap无法保证排序，拿不到“最旧”的点，所以借用list。

				说明要实现这个要求，必须得双方关联，方法就是：hashmap的key是key。value是list的迭代器。
				hashmap的在这里存在的目的就是为了，保证找到list节点最快。既然要找list节点，那么就放她的迭代器。有了迭代器能立马访问它的对应节点。

				list为什么要存key和value呢？
				hashmap已经存了key和list的迭代器，那么list中肯定要存value。
				那为什么要存key呢？
				如果map要删除一个数据的话，依靠什么删除？
				依靠的是key！
				什么时候要删除的呢？当然是map的对应关系改变的时候？
				什么时候，对应关系改变呢？是list发生变化的时候——删除旧的插入新的或者是排序。
				我list改动完毕了，hashmap自然也是要改变，也就是也得有删除旧的对应关系，增加的新对应关系。
				hashmap考什么删除的？
				hashmap的API有两种方式，一种是给对应的迭代器，一种是给对应的key。很明显是提供key就行。
				所以说，list要有key，然后提供给map，让他知道，

				一个节点中的key，对应了list中的value，也对应了map中list的迭代器（节点地址）。
				[key,value,noetAddr]

				记忆点：lsit存key和value map存key和迭代器
			*/
		};

		void test()
		{
			LinkedList::Solution a;
			ListNode lb(1);
			ListNode lb1(2);
			ListNode lb2(3);
			ListNode lb3(4);
			ListNode lb4(5);
			ListNode lb5(6);
			ListNode lb6(7);

			ListNode* ret;

			lb.next = &lb1;
			lb1.next = &lb2;
			lb2.next = &lb3;
			lb3.next = &lb4;/*
			lb4.next = &lb5;
			lb5.next = &lb6;*/

			//ret = reverse_link(&lb);
			//ret = reverse(&lb);
			ret = a.reverseKGroup(&lb, 2);
			//ret = a.reverseBetween(&lb,1,2);

			while (ret != nullptr)
			{
				cout << ret->val << endl;
				ret = ret->next;
			}
		}
		void testLRU()
		{
			LRUCache lRUCache(2);
			lRUCache.put(1, 1); // 缓存是 {1=1}
			lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
			lRUCache.get(1);    // 返回 1
			lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
			lRUCache.get(2);    // 返回 -1 (未找到)
			lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
			lRUCache.get(1);    // 返回 -1 (未找到)
			lRUCache.get(3);    // 返回 3
			lRUCache.get(4);    // 返回 4
		}

	};
}

namespace Tree {

	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode* next;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
	};

	TreeNode* createBinaryTree(vector<string> nodes) {
		int len = nodes.size();

		if (len == 0) {
			return NULL;
		}
		//LeetCode例题里面往往省略最后一个null
		if (len % 2 == 0) {
			nodes.push_back("null");
		}

		if (nodes[0] == "null") {
			return nullptr;
		}

		TreeNode* root;
		//建立结点队列并将根节点入队
		queue<TreeNode*> nodesQue;
		root = new TreeNode(stoi(nodes[0]));
		nodesQue.push(root);

		//loc遍历数组，每次取两个结点
		for (int loc = 1; loc < len; loc = loc + 2) {
			//获取结点并出队
			TreeNode* node = nodesQue.front();
			nodesQue.pop();

			//获取队头结点的左右结点
			string left = nodes[loc];
			string right = nodes[loc + 1];

			//赋予左右结点
			if (left == "null") {
				node->left = nullptr;
			}
			else {
				node->left = new TreeNode(stoi(left));
				nodesQue.push(node->left);
			}

			if (right == "null") {
				node->right = nullptr;
			}
			else {
				node->right = new TreeNode(stoi(right));
				nodesQue.push(node->right);
			}
		}
		return root;
	}


	//多叉树类
	class Node {
	public:
		int val;
		vector<Node*> children;

		Node() {}

		Node(int _val) {
			val = _val;
		}

		Node(int _val, vector<Node*> _children) {
			val = _val;
			children = _children;
		}
	};

	class Solution {
	public:

		//前序遍历-细节实现
		void preorderTraversal(TreeNode* root, vector<int> &node)
		{
			if (root == nullptr)return;

			node.push_back(root->val);
			cout << root->val << endl;
			preorderTraversal(root->left, node);
			preorderTraversal(root->right, node);
		}
		//前序遍历-对外接口
		void preTraversal(TreeNode* root)
		{
			cout << "前序遍历" << endl;
			vector<int> node;
			preorderTraversal(root, node);
		}
		//前序遍历-一个函数
		void preTraversalONE(TreeNode* root)
		{
			if (root == nullptr)return;
			cout << root->val << endl;
			preTraversalONE(root->left);
			preTraversalONE(root->right);
		}



		//中序遍历-细节实现
		void inorderTraversal(TreeNode* root, vector<int> &node)
		{
			if (root == nullptr)return;

			inorderTraversal(root->left, node);
			node.push_back(root->val);
			cout << root->val << endl;
			inorderTraversal(root->right, node);
		}
		//中序遍历-对外接口
		void inoTraversal(TreeNode* root)
		{
			cout << "中序遍历" << endl;
			vector<int> node;
			inorderTraversal(root, node);
		}
		//中序遍历-一个函数
		void inoTraversalONE(TreeNode* root)
		{
			if (root == nullptr)return;
			inoTraversalONE(root->left);
			cout << root->val << endl;
			inoTraversalONE(root->right);
		}




		//后序遍历-细节实现
		void postorderTraversal(TreeNode* root, vector<int> &node)
		{
			if (root == nullptr)return;

			postorderTraversal(root->left, node);
			postorderTraversal(root->right, node);
			node.push_back(root->val);
			cout << root->val << endl;
		}
		//后序遍历-对外接口
		void posTraversal(TreeNode* root)
		{
			cout << "后序遍历" << endl;
			vector<int> node;
			postorderTraversal(root, node);
		}
		//后序遍历-一个函数
		void posTraversalONE(TreeNode* root)
		{
			if (root == nullptr)return;
			posTraversalONE(root->left);
			posTraversalONE(root->right);
			cout << root->val << endl;
		}

		//层序遍历—从上往下—把遍历的元素，放到二维的vec中
		vector<vector<int>> levelOrder(TreeNode* root) {
			if (root == nullptr) return vector<vector<int>>();
			vector<vector<int>> result;
			queue<TreeNode*> que;
			que.push(root);
			while (!que.empty())
			{
				vector<int> vec;
				int size = que.size();
				for (size_t i = 0; i < size; i++)
				{
					/*
					!核心在这，层序遍历方式不是递归。
					遍历的开始，把队列中的一一拿出来，拿一个的同时把这个子树的左右子节点，都放进去了。直到把这一层的拿完。
					这样这一层的就遍历完毕，下一层的也都放进去了。
					然后开始下一层的遍历。
					*/
					TreeNode* note = que.front();
					que.pop();
					vec.push_back(note->val);
					cout << note->val << endl;
					if (note->left) que.push(note->left);
					if (note->right) que.push(note->right);
				}
				result.push_back(vec);

			}
			return result;
		}
		//层序遍历—从下往上—把遍历的元素，放到二维的vec中
		vector<vector<int>> levelOrderBottom(TreeNode* root) {
			queue<TreeNode*> que;
			if (root != NULL) que.push(root);
			vector<vector<int>> result;
			while (!que.empty()) {
				int size = que.size();
				vector<int> vec;
				// 这里一定要使用固定大小size，不要使用que.size()，因为que.size是不断变化的
				for (int i = 0; i < size; i++) {
					TreeNode* node = que.front();
					que.pop();
					vec.push_back(node->val);//! 调整这个没用的。因为下面的代码不是进入遍历！
					if (node->left) que.push(node->left);
					if (node->right) que.push(node->right);
				}
				// result.push_back(vec);
				result.insert(result.begin(), vec);//从上往下变成从下往上，唯一变化的就是这个。
			}
			return result;
		}

		//多叉树-前序
		void porder(Node* root, vector<int>& ret)
		{
			if (root == nullptr) return;
			ret.push_back(root->val);
			for (int i = 0; i < root->children.size(); i++) {
				porder(root->children[i], ret);
			}
			return;
		}
		vector<int> preorder(Node* root) {
			vector<int> ret;
			porder(root, ret);
			return ret;
		}

		/*
		核心：
		多叉树的存储结构我不熟悉，其实就是按照中序构造，在构造函数设置这个点的值，然后用vec保存这个点的所有的子节点的指针
		另外，多叉树有前序和后续遍历，没有中序遍历
	思路：
		和二叉树的遍历方式几乎一样。
		前序就是先插入值，然后遍历它的所有的子节点。
		后序就是反过来。
	参考：
		https://leetcode.cn/problems/n-ary-tree-preorder-traversal/solutions/426304/che-di-chi-tou-qian-zhong-hou-xu-di-gui-fa-di-gui-/
		*/

		//多叉树-后序
		void postorder(Node* root, vector<int>& ret)
		{
			if (root == nullptr) return;
			for (int i = 0; i < root->children.size(); i++) {
				postorder(root->children[i], ret);
			}
			ret.push_back(root->val);
			return;
		}
		vector<int> postorder(Node* root) {
			vector<int> ret;
			postorder(root, ret);
			return ret;
		}


		/*
		104. 二叉树的最大深度

		参考思路：（这个思路相当牛逼）
			从树的根节点开始，一直往下遍历，直到叶子节点。
			然后开始往上返回，每次往上返回都是+1.
			这样就能算出高度
		参考：
			https://leetcode.cn/problems/maximum-depth-of-binary-tree/?envType=study-plan-v2&envId=top-interview-150
		*/
		int maxDepth1(TreeNode* root) {
			if (root == nullptr) return 0;
			return max(maxDepth1(root->right), maxDepth1(root->left)) + 1;
		}


		/*
		104. 二叉树的最大深度

		参考思路：
			！这个要说明一下思路，虽然不是最简单的思路，但是在我学习的路上，这个体系中，我是最容易想到这个办法的。
			看到深度的时候，肯定会想到前序遍历，当然前序遍历肯定也是可以的，只是我在这里没有写。
			为什么这里写了后序遍历呢？
			代码随想给的解释是，根节点的深度（前序）和根结点的高度（后序）是一样的，所以用后序也是一样的，但是没说为什么不用前序。当然前序的代码稍微复杂一下
			其实核心还是思路的问题，我从根节点往上走的时候，也就是后序的方法是最直白的，再代码上也是最简洁的。
		参考：
			https://leetcode.cn/problems/maximum-depth-of-binary-tree/solutions/1797307/by-carlsun-2-ojzh/?envType=study-plan-v2&envId=top-interview-150
			https://programmercarl.com/0104.%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E6%9C%80%E5%A4%A7%E6%B7%B1%E5%BA%A6.html
		*/
		int getdepth(TreeNode* node) {
			if (node == NULL) return 0;
			int rightdepth = getdepth(node->right);     // 右
			int leftdepth = getdepth(node->left);       // 左
			//以上两行代码可以互换，代码随想说的，只是更细一点。内容实质基本上一样。其实也不用考虑后序遍历啥的
			int depth = 1 + max(leftdepth, rightdepth); // 中
			return depth;
		}
		int maxDepth(TreeNode* root) {
			return getdepth(root);
		}
		/*
		104. 二叉树的最大深度

		参考思路：
			这种思路更简洁！更好理解，最重要的符合层序遍历的思路
		参考：
			https://programmercarl.com/0102.%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E5%B1%82%E5%BA%8F%E9%81%8D%E5%8E%86.html#_104-%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E6%9C%80%E5%A4%A7%E6%B7%B1%E5%BA%A6
		*/
		int maxDepth2(TreeNode* root) {
			if (root == NULL) return 0;
			int depth = 0;
			queue<TreeNode*> que;
			que.push(root);
			while (!que.empty()) {
				int size = que.size();
				depth++; // 记录深度
				for (int i = 0; i < size; i++) {
					TreeNode* node = que.front();
					que.pop();
					if (node->left) que.push(node->left);
					if (node->right) que.push(node->right);
				}
			}
			return depth;
		}


		/*
		111. 二叉树的最小深度
		*/
		int minDepth(TreeNode* root) {
			if (root == NULL) return 0;
			int minDepth = 0;
			queue<TreeNode*> que;
			que.push(root);
			while (!que.empty()) {
				int size = que.size();
				minDepth++; // 记录深度
				for (int i = 0; i < size; i++) {
					TreeNode* node = que.front();
					que.pop();
					if (node->left == nullptr&&node->right == nullptr)//遍历到叶子节点就退出。题目要求就是从根节点到最近叶子节点的最短路径上的节点数量。第一次出现叶子节点的时候，就是最短的时候
					{
						return minDepth;
					}
					if (node->left) que.push(node->left);
					if (node->right) que.push(node->right);
				}
			}
			return minDepth;
		}



		/*
		100. 相同的树

		参考思路：
			采用相同的遍历方式，然后判断，不相同就返回false
			！在return上进行递归，就能保证返回的结果，不会受到递归函数中，其他代码的影响；这样就是——返回结果后，接着再返回。不受其他的影响
			1、如果两个都是null就返回true，不能再下去了
			2、如果一个是null一个不是null，返回fals
			一定要在判断值之前，对地址判断。
			3、如果两个点的值不一样返回false。

			剩下的情况就是两个点是一样，并且是存在的。
			既然是一样的，接着往下走，然后接着判断

			判断的方式是——在return上开始递归，并且是左右两个递归都在一起，并且是&&。
			一旦有一个false，开始每次递归函数就都光执行return &&。最后返回的就是false。

		参考：
			https://leetcode.cn/problems/same-tree/?envType=study-plan-v2&envId=top-interview-150


		*/
		bool isSameTree(TreeNode* p, TreeNode* q) {

			if (p == nullptr && q == nullptr)  return true;
			if (p == nullptr || q == nullptr)  return false;
			if (p->val != q->val)  return false;

			return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
		}

		/*
		226. 翻转二叉树
		参考思路：
			从根节点往下遍历
			只要这个节点不是空的，你不用管他下面的子节点是不是空，都要交换。有的情况是左有，右没有，这种也得交换。
			交换之后，然后处理左边的点和左边的点。
			然后返回处理完的“根节点”

		参考：
			https://programmercarl.com/0226.%E7%BF%BB%E8%BD%AC%E4%BA%8C%E5%8F%89%E6%A0%91.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE

		*/
		TreeNode* invertTree(TreeNode* root) {
			if (root == nullptr) return nullptr;

			swap(root->right, root->left);
			invertTree(root->right);
			invertTree(root->left);
			return root;
		}

		/*
		101. 对称二叉树
		参考思路：
			和100. 相同的树的思路很想。
			判断出来需要返回的false或者是true的。
			剩下的就是可以进入下次递归的，
			另外在return实现递归，就可以保证一旦出现return能够一直往上返回，不受影响。
		参考连接：
			https://leetcode.cn/problems/symmetric-tree/solutions/862694/dai-ma-sui-xiang-lu-dai-ni-xue-tou-er-ch-hnjo/?envType=study-plan-v2&envId=top-interview-150
		*/
		bool isSymmetric(TreeNode* root) {

			return isSame(root->left, root->right);
		}

		bool isSame(TreeNode* Lroot, TreeNode* Rroot) {
			if (Lroot == nullptr && Rroot == nullptr) return true;
			if (Lroot != nullptr && Rroot == nullptr) return false;
			if (Lroot == nullptr && Rroot != nullptr) return false;
			if (Lroot->val != Rroot->val) return false;

			return isSame(Lroot->left, Rroot->right) && isSame(Lroot->right, Rroot->left);
		}

		/*
		105. 从前序与中序遍历序列构造二叉树
		参考思路：
			这个和106. 从中序与后序遍历序列构造二叉树思路很相似
			前序
		参考链接：
		*/
		TreeNode* traversal(const vector<int>& inorder, int inorderBegin, int inorderEnd, const vector<int>& preorder, int preorderBegin, int preorderEnd) {
			//简单理解：traversal是处理各个左右子树，当他是空的时候，两者就相等。
			//有没有发现，下面的两个return中都是用后序或者前序来做的判断。是因为，每次处理的时候，都是先处理后序数组，所以必须用他来判断。
			if (preorderEnd == preorderBegin) return nullptr;

			int rootValue = preorder[preorderBegin];
			TreeNode* root = new TreeNode(rootValue);

			//因为是区间是一测闭，一侧开。所以当差值是1的时候，点就剩一个了，这就是叶子节点了。所以需要返回这个点了。
			if (preorderEnd - preorderBegin == 1) return root;

			int delimiterIndex;
			for (delimiterIndex = inorderBegin; delimiterIndex < inorderEnd; delimiterIndex++) {
				if (inorder[delimiterIndex] == rootValue) break;
			}
			// 切割中序数组
			// 左中序区间，左闭右开[leftInorderBegin, leftInorderEnd)
			int leftInorderBegin = inorderBegin;
			int leftInorderEnd = delimiterIndex;
			// 右中序区间，左闭右开[rightInorderBegin, rightInorderEnd)
			int rightInorderBegin = delimiterIndex + 1;
			int rightInorderEnd = inorderEnd;


			/*
			中序中左边的长度就是这个“子树”的左子树的长度，在前序的排列中左子树也是这么长。
			无论是哪种排序方式，它的子树的长度都是一样的，都是那几个对应的字符对应的。所以在前序中左子树的长度，就是在中序中拿到左子树的长度，用这个长度去裁剪后序中左子树的长度，剩下的就是前序中的右子树。
			计算方法：
				 中序“根节点位置”- “中序节点开始的位置” = “左子树的长度”
				 前序“左子树的结束卫视” = 前序“开始节点” + “左子树的长度”
			*/
			// 切割前序数组
			// 左后序区间，左闭右开[leftPostorderBegin, leftPostorderEnd)
			int leftPreorderBegin = preorderBegin + 1;
			int leftPreorderEnd = (preorderBegin + 1) + (delimiterIndex - inorderBegin); // 终止位置是 起始位置 加上 中序区间的大小size 左后序的结束，
			// 右后序区间，左闭右开[rightPostorderBegin, rightPostorderEnd)
			int rightPreorderBegin = (preorderBegin + 1) + (delimiterIndex - inorderBegin);//
			int rightPreorderEnd = preorderEnd; // 排除最后一个元素，已经作为节点了

			root->left = traversal(inorder, leftInorderBegin, leftInorderEnd, preorder, leftPreorderBegin, leftPreorderEnd);
			root->right = traversal(inorder, rightInorderBegin, rightInorderEnd, preorder, rightPreorderBegin, rightPreorderEnd);

			return root;
		}
		TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
			if (inorder.size() == 0 || preorder.size() == 0) return NULL;
			// 左闭右开的原则
			return traversal(inorder, 0, inorder.size(), preorder, 0, preorder.size());
		}

		/*
		106. 从中序与后序遍历序列构造二叉树
		参考思路：
			这个和106. 从中序与后序遍历序列构造二叉树思路很相似
			思路比较复杂，具体看链接。核心就是：
			后序遍历的最后一个点，就是这个树的根节点。
			这个根节点的位置就是中序遍历用来分左子树和右子树的位置，从而知道了哪些节点是左子树，哪些是右子树。
			回到后续遍历，再去看上面得到的各种子树，然后子树又知道了根节点是谁，然后再回到中序遍历中，
			不断的轮询这个过程，就知道了所有节点的位置。
			另外，中序和前序也是这样的思路；

		参考链接：
			https://www.programmercarl.com/0106.%E4%BB%8E%E4%B8%AD%E5%BA%8F%E4%B8%8E%E5%90%8E%E5%BA%8F%E9%81%8D%E5%8E%86%E5%BA%8F%E5%88%97%E6%9E%84%E9%80%A0%E4%BA%8C%E5%8F%89%E6%A0%91.html#%E6%80%9D%E8%B7%AF
			我把它归到同一个函数，经过测试是可以的
		*/
		TreeNode* buildTree2(vector<int>& inorder, vector<int>& postorder) {
			if (postorder.size() == 0) return NULL;

			// 后序遍历数组最后一个元素，就是当前的中间节点
			int rootValue = postorder[postorder.size() - 1];
			TreeNode* root = new TreeNode(rootValue);

			// 叶子节点
			if (postorder.size() == 1) return root;

			// 找到中序遍历的切割点
			int delimiterIndex;
			for (delimiterIndex = 0; delimiterIndex < inorder.size(); delimiterIndex++) {
				if (inorder[delimiterIndex] == rootValue) break;
			}

			// 切割中序数组
			// 左闭右开区间：[0, delimiterIndex)
			vector<int> leftInorder(inorder.begin(), inorder.begin() + delimiterIndex);
			// [delimiterIndex + 1, end)
			vector<int> rightInorder(inorder.begin() + delimiterIndex + 1, inorder.end());

			// postorder 舍弃末尾元素
			postorder.resize(postorder.size() - 1);

			// 切割后序数组
			// 依然左闭右开，注意这里使用了左中序数组大小作为切割点
			// [0, leftInorder.size)
			vector<int> leftPostorder(postorder.begin(), postorder.begin() + leftInorder.size());
			// [leftInorder.size(), end)
			vector<int> rightPostorder(postorder.begin() + leftInorder.size(), postorder.end());

			//用这一级的根节点左右接上他的左右子树。
			//下一轮处理。中序和后续的左右子树要对上。只有这样，都是左或者是右才能处理出来。
			root->left = buildTree2(leftInorder, leftPostorder);
			root->right = buildTree2(rightInorder, rightPostorder);

			//每轮都要把子树返回出去，然后被上级的“根节点的左右接收”，直到返回真正的根节点
			return root;
		}

		/*
			目前感觉这个方法简单一些。
			注意：
				vector虽然是传的引用，只是为了节省性能，不会更改他的内容。
				这几个位置，对应的数都是在原始的位置上
		*/
		// 中序区间：[inorderBegin, inorderEnd)，后序区间[postorderBegin, postorderEnd)
		TreeNode* traversal1(const vector<int>& inorder, int inorderBegin, int inorderEnd, const vector<int>& postorder, int postorderBegin, int postorderEnd) {
			//简单理解：traversal是处理各个左右子树，当他是空的时候，两者就相等。
			if (postorderBegin == postorderEnd) return nullptr;

			int rootValue = postorder[postorderEnd - 1];
			TreeNode* root = new TreeNode(rootValue);

			//因为是区间是一测闭，一侧开。所以当差值是1的时候，点就剩一个了，这就是叶子节点了。所以需要返回这个点了。
			if (postorderEnd - postorderBegin == 1) return root;

			int delimiterIndex;
			for (delimiterIndex = inorderBegin; delimiterIndex < inorderEnd; delimiterIndex++) {
				if (inorder[delimiterIndex] == rootValue) break;
			}
			// 切割中序数组
			// 左中序区间，左闭右开[leftInorderBegin, leftInorderEnd)
			int leftInorderBegin = inorderBegin;
			int leftInorderEnd = delimiterIndex;
			// 右中序区间，左闭右开[rightInorderBegin, rightInorderEnd)
			int rightInorderBegin = delimiterIndex + 1;
			int rightInorderEnd = inorderEnd;


			/*
			中序中左边的长度就是这个“子树”的左子树的长度，在后序的排列中左子树也是这么长。
			无论是哪种排序方式，它的子树的长度都是一样的，都是那几个对应的字符对应的。所以在后序中左子树的长度，就是在中序中拿到左子树的长度，用这个长度去裁剪后序中左子树的长度，剩下的就是后序中的右子树。
			计算方法：
				 中序“根节点位置”- “中序节点开始的位置” = “左子树的长度”
				 后序“左子树的结束卫视” = 后序“开始节点” + “左子树的长度”
			*/
			// 切割后序数组
			// 左后序区间，左闭右开[leftPostorderBegin, leftPostorderEnd)
			int leftPostorderBegin = postorderBegin;
			int leftPostorderEnd = postorderBegin + (delimiterIndex - inorderBegin); // 终止位置是 需要加上 中序区间的大小size 左后序的结束，
			// 右后序区间，左闭右开[rightPostorderBegin, rightPostorderEnd)
			int rightPostorderBegin = postorderBegin + (delimiterIndex - inorderBegin);//
			int rightPostorderEnd = postorderEnd - 1; // 排除最后一个元素，已经作为节点了

			root->left = traversal1(inorder, leftInorderBegin, leftInorderEnd, postorder, leftPostorderBegin, leftPostorderEnd);
			root->right = traversal1(inorder, rightInorderBegin, rightInorderEnd, postorder, rightPostorderBegin, rightPostorderEnd);

			return root;
		}
		TreeNode* buildTree3(vector<int>& inorder, vector<int>& postorder) {
			if (inorder.size() == 0 || postorder.size() == 0) return NULL;
			// 左闭右开的原则
			return traversal1(inorder, 0, inorder.size(), postorder, 0, postorder.size());
		}

		/*
		117.填充每个节点的下一个右侧节点指针 II
		和116的思路一样，代码也一样样
		参考思路：
			遍历每一层的时候，第一个是“链表”头指针，其他的就是从头指针往下接。
		参考：
			https://www.programmercarl.com/0102.%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E5%B1%82%E5%BA%8F%E9%81%8D%E5%8E%86.html#_116-%E5%A1%AB%E5%85%85%E6%AF%8F%E4%B8%AA%E8%8A%82%E7%82%B9%E7%9A%84%E4%B8%8B%E4%B8%80%E4%B8%AA%E5%8F%B3%E4%BE%A7%E8%8A%82%E7%82%B9%E6%8C%87%E9%92%88
		*/
		TreeNode* connect(TreeNode* root) {
			if (root == nullptr) return nullptr;
			queue<TreeNode*> que;
			que.push(root);
			TreeNode *preNote;
			while (!que.empty())
			{
				int size = que.size();
				for (size_t i = 0; i < size; i++)
				{
					TreeNode* note = que.front();
					que.pop();
					if (i == 0)
					{
						preNote = note;
						if (note->left)que.push(note->left);
						if (note->right)que.push(note->right);
					}
					else
					{
						preNote->next = note;
						preNote = preNote->next;
						if (note->left)que.push(note->left);
						if (note->right)que.push(note->right);
					}
				}
			}
			return root;
		}

		/*
		114. 二叉树展开为链表
		思路：
			不要嫌蛮烦，就是这个思路。
			先往左遍历一个点，然后一直往右遍历，直到最后一个右节点。
			让这个右节点接到根节点的左节点。
			然后根节点的右节点接上他原来的左节点。

			然后根节点再往左下走，直到空
		参考：
		https://leetcode.cn/problems/flatten-binary-tree-to-linked-list/solutions/1498323/by-lin-shen-shi-jian-lu-k-z5vv/?envType=study-plan-v2&envId=top-interview-150
		*/
		void flatten(TreeNode* root) {
			while (root)
			{
				TreeNode* p = root->left;
				if (p)
				{
					while (p->right) p = p->right;
					p->right = root->right;
					root->right = root->left;
					root->left = nullptr;//根节点左树被右节点接上后，左节点一定要赋值为空。也就是断开这个左树，要不然会出问题
				}
				root = root->right;
			}
		}

		/*
		112. 路径总和——复杂但思路清晰的写法
		思路：
			核心思路，就是在递归函数中，判断是不是到了叶子节点，以及count是否减到了0
			先遍历左边的左边，一直到底，不行了就往右一个一个遍历。直到成功，否则就是false
		总结：
			像这种返回bool的递归，一定要确定什么时候返回true，什么时候返回false。
			然后在return的地方调用递归。
			参考101. 对称二叉树
		参考：
			https://www.programmercarl.com/0112.%E8%B7%AF%E5%BE%84%E6%80%BB%E5%92%8C.html#%E6%80%9D%E8%B7%AF
		*/
		bool traversal(TreeNode* root, int count)
		{
			if (root->left == nullptr &&root->right == nullptr && count == 0) return true;//走到了叶子节点，并且cont是0了
			if (root->left == nullptr &&root->right == nullptr && count != 0) return false;//走到了叶子节点，但是cout还没减到0
			//都是一下都是未到叶子节点的情况
			if (root->left)//如果有左叶子
			{
				count -= root->left->val;//减去左叶子的值
				if (traversal(root->left, count)) return true;//沿着左节点的轨迹，进去递归，一直到左叶子节点，如果符合要求的话，就返回true，否则就是false。
				count += root->val;//如果上面是false的话，才能走到这里。说明上面遍历的结果是不对的，然后就应该把那个值加回去。
			}
			if (root->right)//右叶子节点处理的方式是一样的
			{
				count -= root->right->val;
				if (traversal(root->right, count)) return true;
				count += root->val;
			}
			return false;//如果这个点的左右节点都不行的话，那说明这个节点不行，要返回false。
		}
		bool hasPathSum1(TreeNode* root, int targetSum) {
			if (root == nullptr) return false;
			return traversal(root, targetSum - root->val);
			//这里要传,targetSum- root->val而不能targetSum。是因为traversal调用之后，里面处理的是root的子节点，肯定要传减去 root->val 之后的值
		}

		/*
		112. 路径总和——代码简洁，思路复杂一些
		思路：
			先遍历左边的左边，一直到底，不行了就往右一个一个遍历。直到成功，否则就是false
			无论是那种方式，思路都是一样的。

		总结：
			像这种返回bool的递归，一定要确定什么时候返回true，什么时候返回false。
			然后在return的地方调用递归。
			参考101. 对称二叉树、112. 路径总和
		*/
		bool hasPathSum(TreeNode* root, int targetSum) {
			if (root == nullptr) return false;//都走到叶子节点的后面了，还没有减到合适的值，就说明不满足。
			if (root->left == nullptr &&root->right == nullptr && targetSum != root->val) return false;//走到了叶子节点，并且targetSum和当前节点的值不相同相同。说明不行，这句话可以不用加，不加的话，他会继续往下走，就会在if (root == nullptr) return false;返回法拉瑟
			if (root->left == nullptr &&root->right == nullptr && targetSum == root->val) return true;//走到了叶子节点，并且targetSum和当前节点的值相同。

			return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);//左右两条路，有一条满足要求就行
		}

		/*
		199. 二叉树的右视图
		思路：
			层序遍历，保存每层中的最后一个节点的值
		*/
		vector<int> rightSideView(TreeNode* root) {
			if (root == nullptr) return vector<int>();
			queue<TreeNode*>que;
			que.push(root);
			vector<int> ret;
			while (!que.empty())
			{
				int queSize = que.size();
				for (size_t i = 0; i < queSize; i++)
				{
					TreeNode* node = que.front();
					que.pop();
					if (i == queSize - 1) ret.push_back(node->val);//只要这一层的最后一个
					if (node->left)que.push(node->left);
					if (node->right)que.push(node->right);
				}
			}
			return ret;
		}

		/*
		637. 二叉树的层平均值
		*/
		vector<double> averageOfLevels(TreeNode* root) {
			if (root == nullptr) return vector<double>();
			queue<TreeNode*>que;
			que.push(root);
			vector<double> ret;
			while (!que.empty())
			{
				int queSize = que.size();
				double nums = 0.0;
				for (size_t i = 0; i < queSize; i++)
				{
					TreeNode* node = que.front();
					que.pop();
					nums += node->val;
					if (node->left)que.push(node->left);
					if (node->right)que.push(node->right);
				}
				ret.push_back(nums / queSize);
			}
			return ret;
		}

		/*
		429. N 叉树的层序遍历
		*/
		vector<vector<int>> levelOrder(Node* root) {
			if (root == nullptr) return vector<vector<int>>();
			queue<Node*>que;
			que.push(root);
			vector<vector<int>> rets;
			while (!que.empty())
			{
				int queSize = que.size();
				double nums = 0.0;
				vector<int > ret;
				for (size_t i = 0; i < queSize; i++)
				{
					Node* node = que.front();
					que.pop();
					ret.push_back(node->val);
					for (size_t i = 0; i < node->children.size(); i++)//
					{
						que.push(node->children[i]);
					}
				}
				rets.push_back(ret);
			}
			return rets;
		}

		/*
		515. 在每个树行中找最大值
		*/
		vector<int> largestValues(TreeNode* root) {
			if (root == nullptr) return vector<int>();
			queue<TreeNode*>que;
			que.push(root);
			vector<int> ret;
			while (!que.empty())
			{
				int max = que.front()->val;//[0,-1] ！！这个地方要注意，不能赋值0；要不然一层都是-1，本来最小值是-1，这就会变成0
				int queSize = que.size();
				for (size_t i = 0; i < queSize; i++)
				{
					TreeNode* node = que.front();
					que.pop();
					max = max > node->val ? max : node->val;
					if (node->left)que.push(node->left);
					if (node->right)que.push(node->right);
				}
				ret.push_back(max);
			}
			return ret;
		}

		/*
		110. 平衡二叉树
			一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1 。
		参考：
			https://www.programmercarl.com/0110.%E5%B9%B3%E8%A1%A1%E4%BA%8C%E5%8F%89%E6%A0%91.html
		*/
		// 返回以该节点为根节点的二叉树的高度，如果不是平衡二叉树了则返回-1
		int getHeight(TreeNode* node) {
			if (node == NULL) {//如果这个节点都不存在，这个node高度就是0.为什么是0呢？根据题目来看，只有一个点的时候，node高度是1
				return 0;
			}
			int leftHeight = getHeight(node->left); // （左） 当前节点为根节点的左节点的高度
			if (leftHeight == -1) return -1;//如果发现这个子树不平衡了，啥也不用做，直接返回吧。
			int rightHeight = getHeight(node->right); // （右）当前节点为根节点的右节点的高度
			if (rightHeight == -1) return -1;//如果发现这个子树不平衡了，啥也不用做，直接返回吧。

			int result;
			if (abs(leftHeight - rightHeight) > 1) {  // （中） 高度差大于1就说明树不平衡
				result = -1;
			}
			else {
				result = 1 + max(leftHeight, rightHeight); // +1后就是当前节点为根节点的树的高度。！！千万别忘了+1
			}
			return result;//最后返回node为根节点的树的高度
		}
		bool isBalanced(TreeNode* root) {
			return getHeight(root) == -1 ? false : true;
		}

		/*
		257. 二叉树的所有路径
		参考：
			https://www.programmercarl.com/0257.%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E6%89%80%E6%9C%89%E8%B7%AF%E5%BE%84.html
			代码中有更简洁的方法，但是还是这个更好理解，本质上都是一种思路。
		思路：
			从根节点往下走，直到叶子节点。就是很明显的前序遍历。另外到了叶子节点就停止了，说明递归结束条件就是到了叶子节点。
			这种感觉用前序遍历最好了
			再加上回溯，简直是完美。
		*/
		void traversal(TreeNode* cur, vector<int>& path, vector<string>& result) {
			path.push_back(cur->val);//添加新的路径点
			if (cur->left == nullptr && cur->right == nullptr)//到了叶子节点，就要把整个路径放到result中。
			{
				string sPath = "";
				for (size_t i = 0; i < path.size() - 1; i++)//这里-1是为了只在path中的每个字符中间加上->，只是这个原因而已。
				{
					sPath += to_string(path[i]);
					sPath += "->";
				}
				sPath += to_string(sPath[path.size() - 1]);//把path最后一个字符也加上
				result.push_back(sPath);//!!别忘了，最后把处理好的路径，放到result中
			}
			if (cur->left)//加上if是是因为：左节点存在的时候才要往左边遍历。听起来很无聊哈。
			{
				traversal(cur->left, path, result);//如果左节点存在，就遍历。
				path.pop_back();//！！！回溯！！！——当子节点不存在了，也就是到了叶子节点的时候，递归才会退出，这个时候就要往右节点看看。所以要把刚才的左节点删掉。
			}
			if (cur->right)//同上
			{
				traversal(cur->right, path, result);//同上
				path.pop_back();//！！！回溯！！！——到了叶子节点的时候，并且是右边的节点。这个时候，就考虑结束了递归了，然后删除最后的路径字符。
			}
			return;
		}
		vector<string> binaryTreePaths(TreeNode* root) {
			vector<string> result;
			vector<int> path;//path一定要vec，如果要用string的话，如果添加了一个3位数字，在回溯的时候，要回溯3次，关键你还得记录他的位数。用vec的话，pop一次就行了
			if (root == NULL) return result;
			traversal(root, path, result);
			return result;
		}

		/*
		404. 左叶子之和
			虽然代码写的不简洁，但是慢慢找到感觉了。哈哈。
			思路应该是一样的，时间100%
		*/
		int sumOfLeft(TreeNode* root, int & ret, int flag)
		{
			if (root->left == nullptr &&root->right == nullptr&& flag == 1) return ret += root->val;
			if (root->left)
			{
				sumOfLeft(root->left, ret, 1);
			}
			if (root->right)
			{
				sumOfLeft(root->right, ret, 2);
			}
			return ret;
		}
		int sumOfLeftLeaves1(TreeNode* root) {
			if (root == nullptr) return 0;
			if (root->left == nullptr &&root->right == nullptr) return 0;
			int ret = 0;
			sumOfLeft(root, ret, 0);

			return ret;
		}

		/*
		404. 左叶子之和
		这个题目的要学习的地方
		平时我们解二叉树的题目时，已经习惯了通过节点的左右孩子判断本节点的属性，而本题我们要通过节点的父节点判断本节点的属性
		参考：https://www.programmercarl.com/0404.%E5%B7%A6%E5%8F%B6%E5%AD%90%E4%B9%8B%E5%92%8C.html#%E6%80%9D%E8%B7%AF
		我这个写法和他的思路基本上一致，但是顺序不一样，
		*/
		int sumOfLeftLeaves(TreeNode* root) {
			if (root == nullptr) return 0;
			int Lret = 0;
			if (root->left != nullptr  &&root->left->left == nullptr  &&root->left->right == nullptr)//！！核心在这，判断左叶子节点的办法
				Lret += root->left->val;

			Lret += sumOfLeftLeaves(root->left);
			Lret += sumOfLeftLeaves(root->right);

			return Lret;
		}

		/*
		513. 找树左下角的值
		思路：
			1、层序遍历，但是只有这个节点有左节点才能可以放到队列中——这种方式只能找到最左边的节点，一旦有节点的某个左节点符合要求，就不行了。
			2、或者是前序遍历，记录当遍历到左叶子节点的时候，然后做个判断，值比之前大就记录这个值，否则不记录。——这个也错了。这是算出左叶子节点中最大的值。

		*/
		int findBottomLeftValue(TreeNode* root) {
			int deep = 0;
			int olddeep = 0;
			if (root == nullptr) return 0;//假设二叉树中至少有一个节点。
			if (root->left != nullptr && root->left->left == nullptr &&root->left->right == nullptr)
			{
				olddeep = ++deep;
				return ++deep;
			}

			if (root->left)
				deep += findBottomLeftValue(root->left);
			if (root->right)
				deep += findBottomLeftValue(root->right);
			return deep;
		}

		/*
		654. 最大二叉树
		这两个题目和这个多看看
			106.从中序与后序遍历序列构造二叉树
			105.从前序与中序遍历序列构造二叉树
		参考：
		https://leetcode.cn/problems/maximum-binary-tree/description/
		*/
		TreeNode*maxTre(vector<int>& nums, int left, int right)
		{
			//左右下标遇到一起的时候，说明数组中已经没有节点了，要返回空
			if (left == right) return nullptr;
			//如果有节点，要找到最大的那个节点
			int maxValue = 0;
			int maxValueIndex = left;
			//注意：每次进入递归i都是用left赋值.因为我们不改变数组中的值，只是改变数组的序号，所以才要这样
			for (size_t i = left; i < right; i++)
			{
				if (nums[i] > maxValue)
				{
					maxValue = nums[i];
					maxValueIndex = i;
				}
			}
			TreeNode* root = new TreeNode(nums[maxValueIndex]);

			//找到最大的点后，就开始分左右部分开始处理
			root->left = maxTre(nums, left, maxValueIndex);
			root->right = maxTre(nums, maxValueIndex + 1, right);
			return root;
		}
		TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
			return maxTre(nums, 0, nums.size());
		}

		/*
		617. 合并二叉树
		思路：
			都合并到root1树上；具体看思路
		参考：
			https://www.programmercarl.com/0617.%E5%90%88%E5%B9%B6%E4%BA%8C%E5%8F%89%E6%A0%91.html#%E6%80%9D%E8%B7%AF
		*/
		TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
			if (root1 == nullptr)return root2;// 如果t1为空，合并之后就应该是t2
			if (root2 == nullptr)return root1;//同理
			root1->val = root1->val + root2->val;

			root1->left = mergeTrees(root1->left, root2->left);
			root1->right = mergeTrees(root1->right, root2->right);

			return root1;
		}

		/*
		700. 二叉搜索树中的搜索
		思路：
			注意：他是二叉搜索树！
		要学习的点：
			3、结束条件的判断的写法，要和你递归函数的入参要对应。要不然出现空指针访问的问题。
			  3.1、入参是子节点指针，结束条件的判断，一定要是对root的判断。 searchBST(root->left, val); 《-----》  if (root == NULL || root->val == val) return root;
				如果对root->left，就会出现nullptr->left，自然就会报错。
			  3.2、入参是root节点非子节点，结束条件的判断，才可以是对root->left等判断。
			  3.3、具体什么时候采取什么样的判断，要根据入参来。而什么样的入参，要根据题目的思路来。多体会吧。
			  3.4、  700. 二叉搜索树中的搜索 可以参考这个题目
		*/
		TreeNode* searchBST(TreeNode* root, int val) {
			if (root == nullptr)return nullptr;
			if (root->val == val)return root;
			if (root->val > val) return searchBST(root->left, val);//!!两个if只会进一个，这是由二叉搜索树来决定的。
			if (root->val < val) return searchBST(root->right, val);//另外为了保证返回值不被干扰，直接在这返回

			return nullptr;
		}

		/*
		98. 验证二叉搜索树
		思路：

		参考：
			https://www.programmercarl.com/0098.%E9%AA%8C%E8%AF%81%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		*/
		bool isValidBST(TreeNode* root) {

			if (root == nullptr)return false;
			if (true)

				if (root->left >= root->right) return false;



		}

		void test()
		{
			cout << "测试树结构" << endl;
			TreeNode *treeRoot = new TreeNode;

			//flatten(&treeRoot);
			//preTraversalONE(&treeRoot);

			//cout << "104. 二叉树的最大深度=" << maxDepth(&treeRoot) << endl;
			//cout << "100. 相同的树=" << isSameTree(&treeRoot, &tree4) << endl;
			//cout << "101. 对称二叉树=" << isSymmetric(&treeRoot) << endl;


			vector<string> nodes = { "40","20","60","10","30","50","70" };
			treeRoot = createBinaryTree(nodes);//构建树
			cout << searchBST(treeRoot, 25) << endl;
			/*vector<string> srtVec = binaryTreePaths(&treeRoot);
			for (size_t i = 0; i < srtVec.size(); i++)
				std::cout << srtVec[i] << endl;*/
		}
	};
}


int main()
{
	vector<int> nums{ 0,1,2,4,5,7 };
	vector<int> num1{ };
	vector<string> srtVec{ "2","1","+","3","*" };
	string str = "(1+(4+5+2)-3)+(6+8)";
	string t = "anagram";
	string strs{ "Marge, let's \"[went].\" I await {news} telegram." };
	vector<vector<int>> board = { {1,4},{4,5} };
	vector<int> newInterval{ 0,0 };

	Tree::Solution tree;
	tree.test();



	/*vector<vector<int>> retStr = a.merge(board);

	for (auto i : retStr)
	{
		for (auto l : i)
		{
			cout << l << " ";
		}
		cout << endl;
	}*/

	/*for (size_t i = 0; i < retStr.size(); i++)
	{
		std::cout << retStr[i] << endl;
	}*/
	//std::cout << a.trap(nums) << endl;
	//std::cout << a.isSubsequence("b", "abc") << endl;
	//std::cout << a.hIndex(nums) << endl;
	//std::cout << a.canCompleteCircuit(nums, num1) << endl;
}