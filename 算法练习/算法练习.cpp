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

using namespace std;

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
	*/string simplifyPath(string path)
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
		if (stk.size() < 2)
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
};



void test()
{
	vector<int>a{ 1,2,3,4 };
}

int main()
{


	vector<int> nums{ 0,1,2,4,5,7 };
	vector<int> num1{ };
	vector<string> srtVec{ "2","1","+","3","*" };
	string str = "/home/";
	string t = "anagram";
	string strs{ "Marge, let's \"[went].\" I await {news} telegram." };
	vector<vector<int>> board = { {1,4},{4,5} };
	vector<int> newInterval{ 0,0 };
	Solution a;

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
	std::cout << a.evalRPN(srtVec) << endl;
	//std::cout << a.trap(nums) << endl;
	//std::cout << a.isSubsequence("b", "abc") << endl;
	//std::cout << a.hIndex(nums) << endl;
	//std::cout << a.canCompleteCircuit(nums, num1) << endl;
}