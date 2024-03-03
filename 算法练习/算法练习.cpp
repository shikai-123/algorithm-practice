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
#include<windows.h>

using namespace std;


struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
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


//字符串和数组
namespace String_Array
{
	class Solution {
	public:

		/*
		704. 二分查找
		参考：
			https://www.programmercarl.com/0704.%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE.html#%E6%80%9D%E8%B7%AF
		思路：
			使用二分法的前提是：1、数组有序 2、元素无重复
			看题解中，它分为左闭右闭，左闭右开，还是第一中更符合直觉。

			当左闭右闭，while[left==right]是由意义的
			判断“中间元素”和“目标元素”的大小，然后移动中间位置。（核心思想）
			如果中间的大于左边的就是left=mid+1;
			如果中间的小于右边的就是right=mid-1;
			直到nus[mid]==target;
		*/
		int search(vector<int>& nums, int target) {

			int left = 0;
			int right = nums.size() - 1; // 定义target在左闭右闭的区间里，[left, right]; 假设012，既然是左闭右闭，right的下标就是size()-1
			while (left <= right)
			{
				//int mid = (right - left) //如果是2 5则一直卡在这个循环中。
				int mid = left + ((right - left) / 2);//换成这种咋不会
				if (nums[mid] > target) {
					right = mid - 1;
				}
				else if (nums[mid] < target) {
					left = mid + 1;
				}
				else if (nums[mid] == target) {
					return mid;
				}
			}
			return -1;
		}


		/*
		27. 移除元素
		参考：
			https://www.programmercarl.com/0027.%E7%A7%BB%E9%99%A4%E5%85%83%E7%B4%A0.html#%E6%80%9D%E8%B7%AF
		思路：
			双指针——快慢指针
			遍历数组，如果数组碰不到要删除的值，就一直往里面放，慢指针++
			如果碰到了，就不放了。慢指针不动.
		*/
		int removeElement(vector<int>& nums, int val) {
			int slow = 0;
			for (size_t i = 0; i < nums.size(); i++)
			{
				if (nums[i] == val) {
					continue;
				}
				nums[slow++] = nums[i];
			}
			return slow;
		}


		/*
		977.有序数组的平方
		参考：
			https://www.programmercarl.com/0977.%E6%9C%89%E5%BA%8F%E6%95%B0%E7%BB%84%E7%9A%84%E5%B9%B3%E6%96%B9.html
		思路1：
			暴力解法：
			遍历数组，把每个元素的平方都算出来，然后用sort排序即可。时间复杂度是n+n*logn，挺好就是时间复杂度差点
		思路2：
			双指针；
			因为数组是“非递减”，所以较大的数一定位于两端。
			一个指针在前，一个在尾。
			比较他们平方的大小，谁大谁往ret数组中放。
		*/
		vector<int> sortedSquares(vector<int>& nums) {
			vector<int> ret(nums.size(), 0);
			int k = nums.size() - 1;
			int start = 0;
			int end = k;
			while (start <= end)//只有两个指针重合在一块的时候，才能把最后的元素放进去。
			{
				if (nums[start] * nums[start] > nums[end] * nums[end]) {
					ret[k--] = nums[start] * nums[start];
					start++;
				}
				else {
					ret[k--] = nums[end] * nums[end];
					end--;
				}
			}
			return ret;
		}


		/*
		https://leetcode.cn/problems/remove-duplicates-from-sorted-array/description/
		留一个就行，没必要这么多
		*/
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

		/*
		122.买卖股票的最佳时机II
		参考：
			https://www.programmercarl.com/0122.%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E7%9A%84%E6%9C%80%E4%BD%B3%E6%97%B6%E6%9C%BAII.html#%E6%80%9D%E8%B7%AF
		思路：
			贪心，只计算盈利的天数，然后把这些盈利加在一起。就是最大盈利
		*/
		int maxProfit2_1(vector<int>& prices) {
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

		/*
			题解中有更简单的，另外我这是从后往前走的贪心算法，也可以试试从前往后，路径应该都是一样的。
			我已经看不懂，我当时是怎么想的了。
			下面贪心的时候，有新的解法，代码简答，看他这个吧
		*/
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
		这个我已经忘了当初是怎么写的了，所以换成代码随想的思路，最重要的是有个可以回顾的东西
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

		/*
		151.翻转字符串里的单词
		参考：
			https://www.programmercarl.com/0151.%E7%BF%BB%E8%BD%AC%E5%AD%97%E7%AC%A6%E4%B8%B2%E9%87%8C%E7%9A%84%E5%8D%95%E8%AF%8D.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		*/
		string reverseWords(string s) {
			string temp;
			istringstream in(s);
			string res;
			while (in >> res) {//istringstream 有<< >>两中操作符重载
				temp.insert(0, res);
				temp.insert(0, " ");
			}
			temp.erase(0, 1);
			return temp;
		}

		/*
		28. 找出字符串中第一个匹配项的下标
		参考：
			https://www.programmercarl.com/0028.%E5%AE%9E%E7%8E%B0strStr.html#%E6%80%9D%E8%B7%AF
		*/
		int strStr(string haystack, string needle)
		{
			int lenth = haystack.size();
			for (int i = 0; i < lenth; i++)
			{
				if (strncmp(haystack.c_str(), needle.c_str(), needle.size()) == 0)
					return i;
				else
					haystack.erase(0, 1);//删除头一个字符，上面每次比较的都是从头开始的
			}
			return -1;
		}

		//我已经忘了思路了，可能是看别人的额答案吧。下面的思路比较简单呐。这个就不管了
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


		/*
		59.螺旋矩阵II
		参考：
			https://www.programmercarl.com/0059.%E8%9E%BA%E6%97%8B%E7%9F%A9%E9%98%B5II.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			这道题目可以说在面试中出现频率较高的题目，本题并不涉及到什么算法，就是模拟过程，但却十分考察对代码的掌控能力。
			重点就是：明确好是“左开右闭”，然后在下面的处理中，全部都是遵循这个规则。
			在遍历每条边的时候，拐角处让给新的一条边来继续画，这也是坚持了每条边左闭右开的原则。
		*/
		vector<vector<int>> generateMatrix(int n) {
			int loop = n / 2;//n的偶数正好能组成矩阵，奇数差一行，就在最后的处理一下
			int start = 0;//每圈开始的坐标
			int offset = 1;//每次遍历，“右”边界收缩1。保证“左开右闭”！.只有“从左到右”，“填充右行的从上到下”才使用这个
			int count = 1;//矩阵中要填充的数
			int i = 0, l = 0;//il代表在矩阵中的当前坐标

			vector<vector<int>> ret(n, vector<int>(n, 0));

			while (loop--)
			{
				//填充上行——从左到右
				for (l = start; l < n - offset; l++)
				{
					ret[start][l] = count++;
				}

				//填充右行——从上到下
				for (i = start; i < n - offset; i++)
				{
					ret[i][l] = count++;
				}

				//填充下行——从右到左
				for (; l > start; l--)//不能是l >= start。会出现i=-1的情况
				{
					ret[i][l] = count++;
				}

				//填充左行——从下到上
				for (; i > start; i--)
				{
					ret[i][l] = count++;
				}
				start++;//填充一圈后，开始坐标往右下角移动+1；
				offset++;//填充一圈后，有边界收缩1
			}
			if (n % 2 == 1)ret[start][start] = count++;

			return ret;
		}


		/*
		344.反转字符串
		参考：
			https://www.programmercarl.com/0344.%E5%8F%8D%E8%BD%AC%E5%AD%97%E7%AC%A6%E4%B8%B2.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			用reserve函数可以。但是没必要
		*/
		void reverseString(vector<char>& s) {
			for (size_t i = 0, l = s.size() - 1; i < s.size() / 2; i++, l--)
			{
				swap(s[i], s[l]);
			}
		}

		/*
		541. 反转字符串II
		参考：
			https://www.programmercarl.com/0541.%E5%8F%8D%E8%BD%AC%E5%AD%97%E7%AC%A6%E4%B8%B2II.html
		思路：
			在for中，每2k的步骤，开始反转k个字符

		*/
		string reverseStr(string s, int k) {
			for (size_t i = 0; i < s.size(); i += (k * 2))
			{
				if (i + k < s.size())//剩余的待返转的字符没超出数组
					reverse(s.begin() + i, s.begin() + i + k);//比如0-2 其实反转的是0-1 这是因为迭代器end()-1
				else//剩余的待返转的字符“超出”数组，但有可能还有几个还在数组中，就反转这几个
					reverse(s.begin() + i, s.end());
			}
			return s;
		}


		/*
		这个题目力扣中，没有
		替换数字
		参考：
			https://www.programmercarl.com/kama54.%E6%9B%BF%E6%8D%A2%E6%95%B0%E5%AD%97.html#%E6%80%9D%E8%B7%AF
		题目解释：
			a1b2  就是要把数字12换成number
		*/
		void replcenum()
		{
			string str;
			cin >> str;
			string ret;
			for (char s : str) {
				if (s >= '0'&&s <= '9') {//遇到0或者9 就换成number
					ret += "number";
				}
				else
					ret += s;
			}
			cout << ret;
		}



		/*
		右旋字符串——力扣上没有的，在剑指offer上也有这个题目
		参考：
			https://www.programmercarl.com/kama55.%E5%8F%B3%E6%97%8B%E5%AD%97%E7%AC%A6%E4%B8%B2.html#%E6%80%9D%E8%B7%AF
		题目解释：
			abcdefg k=2 反转成 fgabcde
		思路：
			1、把整个字符串反转过来
			2、从头到n反转
			3、从n到头反转
			最后得到的就是题目要求的
		*/
		void rightStr()
		{
			int n;
			string s;
			cin >> n;
			cin >> s;

			reverse(s.begin(), s.end());
			reverse(s.begin(), s.begin() + n);
			reverse(s.begin() + n, s.end());//虽然都是s.begin() + n。上面的不会反转s.begin() + n
			cout << s << endl;
		}

		/*
		459.重复的子字符串
		参考：
			https://www.programmercarl.com/0459.%E9%87%8D%E5%A4%8D%E7%9A%84%E5%AD%90%E5%AD%97%E7%AC%A6%E4%B8%B2.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			先把字符串s加上一份s，得到ss。然后从ss中查找s
			比如abab，得到abab abab。那么find返回的位置一定不是后面s的起始位置。
			因为abab是重复的，ab“abab”ab，会构成重复。
			如果abcd这种，ss是abcdabcd。find返回的数据，一定是第二个“abcd”的位置
			注意，find的起始位置从1开始，要不然就直接查找原来的s了，没有意义
		*/
		bool repeatedSubstringPattern(string s) {//没参考他的kmp方法
			return (s + s).find(s, 1) != s.size();
		}

		/*
		283. 移动零
		参考：
			咱没找到参考
		思路：
			关键是记录非零元素要放的“位置”——put_pos
			遇到非0元素，要把这个元素放到put_pos位置,既然该位置放了元素，下个元素要放的位置要++
			遇到0元素，啥也不用管。
			最终，只放非零元素到前面，0自然就在后面了。

			双指针，一个是i，一个是put_pos。
			i代表当前遍历的元素，put_pos非零元素要放的“位置”
		举例：
			比如010312
			遍历到0跳过，遍历到1非零，然后i=1，put_pos=0,变成100312。就是把非零的1，,放到put_pos的位置。
			然后 put_pos++
			然后再遍历，00跳过，到3，就把三放到放到put_pos，也就是1的位置。变成130012
			。。。直到结束
		*/
		void moveZeroes(vector<int>& nums) {
			int put_pos = 0;
			for (size_t i = 0; i < nums.size(); i++)
			{
				if (nums[i] != 0) {
					swap(nums[i], nums[put_pos]);
					put_pos++;
				}
			}
			return;
		}

		/*
		560. 和为 K 的子数组
		题目：
			就是给的k，在nus中有几种组合方式，加一块=k;返回所有的组合次数
		思路：
			前缀和——看来我这个地方，学的不行
			遍历数组，然后从头开始累加这个数组元素，得到sum。
			用map记录每个sum出现的次数
			用k-sum，就得到了“能和这个数组成k的数”，看看在map中有没有，
			!也就是看看当前的元素和前面遍历过的元素能不能凑成想要的
			有的话，组合次数机上对应的sum出现的次数。
			最后，不管有没有，当前遍历周期中得到的sum要放到map中，map[sum]++;

			要注意的是：一开始要初始化umap[0]=1;因为umap的含义是sum出现的次数
			0默认就是有的，另外
			考虑一个简单的情况，数组为 {7}，目标值 k 为 7。如果没有mp[0] = 1; 这行代码，那么在第一次循环时，pre 会等于 7，然后查找 mp[pre - k] 即 mp[0]，这个时候如果没有初始化 mp[0] 为 1，就会认为没有和为 7 的子数组，导致结果不准确。
		*/
		int subarraySum(vector<int>& nums, int k) {
			unordered_map<int, int> umap;//key 从头到当前元素的累加和 value 出现的次数
			umap[0] = 1;//和为0的情况，默认就是1个
			int ret = 0;
			int sum = 0;//
			for (auto num : nums) {
				sum += num;
				if (umap.find(sum - k) != umap.end()) {//！！这个和下面的地方一定是sum - k，反过来纠错
					ret += umap[sum - k];
				}
				umap[sum]++;
			}
			return ret;
		}

		/*
		41. 缺失的第一个正数
		参考：
			没啥参考的，看我的思路吧
		思路：
			一切都是建立在“把元素nusm[i]放到下标nums[i]-1的位置，也就是3放到下标2的位置上，不满足的要调整。0和负数放在后面”，这个规则上的。这个规则没有啥意思，就是这么做好处理罢了
			首先排序，让该有的位置，放到该有的位置上，这个规则是：1放到下标0；2放到下标1，以此类推；
			0和负数，都放在后面。这是因为题目要求的是第一个缺失的“正数”。
			所以，从1开始，准确说是从》0的数据开始，把这个数nusm[i]放到nums[i]-1的位置，假设是1，就是放到0.
			!!另外也要判断 nums[i] <= nums.size()，假设数组长度为2，有个元素是7，这7要放在位置6，很明显不对！
			让正数放在对应的位置上，然后遍历排序后的数组，发现谁没有在合适的位置上，说明这个位置的数据缺失了。
			如果数组遍历结束，都没有发现缺失，那么缺失的元素就是尾巴元素后面的。比如123 缺失的就是4.
			注意：调整数组顺序的时候，一定要用while，要不然调整不完全。正确的逻辑是，先用for遍历一个，也就是调整这一个数，用while使劲调，直到调到最后，才是满足条件的
		易错点：

		*/
		int firstMissingPositive(vector<int>& nums) {
			//对数组排序，不能用sort，时间复杂度从n到了nlogn。
			//对数组排序，让数据放到该放的地方，比如1放到位置0。非正数放到后面
			for (size_t i = 0; i < nums.size(); i++)
			{
				//nums[i] != nums[nums[i] - 1],很关键，就是判断“元素nusm[i]是不是放到下标nums[i]-1的位置”，相等就是放在对应的位置上，不想等就调整
				while (nums[i] >= 1 && nums[i] <= nums.size() && nums[i] != nums[nums[i] - 1])
				{
					swap(nums[i], nums[nums[i] - 1]);
				}
			}
			for (size_t i = 0; i < nums.size(); i++)
			{
				if (nums[i] != i + 1) {//假设元素1未放到位置0.返回0+1
					return i + 1;
				}
			}
			return  nums.size() + 1;//从头到尾啥也不缺，就是缺最后的元素的后一个
		}

		void test()
		{
			vector<int> nums = { 3,4,-1,1 };
			firstMissingPositive(nums);
			repeatedSubstringPattern("abab");
			vector<vector<int>> retStr = generateMatrix(4);
			for (auto i : retStr)
			{
				for (auto l : i)
				{
					cout << l << " ";
				}
				cout << endl;
			}
		}

	};
}

//双指针
namespace DoublePointer
{
	class Solution {
	public:

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



		/*
		15. 三数之和
		参考：
			https://www.programmercarl.com/0015.%E4%B8%89%E6%95%B0%E4%B9%8B%E5%92%8C.html#%E6%80%9D%E8%B7%AF
		思路：
			因为题目要求从数组中取出的数要保持不重复。所以哈希的方法不合适，具体看链接。
			（他这个重复，包括同一个元素不能用两边，两个相同的元素也不能出现。即使有俩个-1；-101，-101这两个也不同，其实看代码编的题目，所以这个重复的规则才这么绕）
			所以用双指针
			其实是三指针，一个在最左边a，一个挨着最左边的右边b，一个在最右边c
			在保持a不变的情况下，判断a+b+c的情况，分别移动b或c
			b和c都移动完了，然后移动a
			！！重点是去重，总之一句话概括。相同a相同的b相同的c，放了之后，后面的就跳过就完了。
		*/
		vector<vector<int>> threeSum(vector<int>& nums) {
			sort(nums.begin(), nums.end());
			vector<vector<int>>ret;
			int left = 0, right = 0;
			for (size_t i = 0; i < nums.size(); i++)
			{
				if (nums[i] > 0) return ret;//如果排序后一开始就大于0，说明整个数组就任何都大于0;
				if (i > 0 && nums[i] == nums[i - 1]) continue;//对a去重。这样的两个数是相同的，结果是一样的，所以要去掉。

				left = i + 1;
				right = nums.size() - 1;
				while (left < right)
				{
					if (nums[i] + nums[left] + nums[right] > 0)
						right--;
					else if (nums[i] + nums[left] + nums[right] < 0)
						left++;
					else {
						ret.push_back(vector<int>{nums[i], nums[left], nums[right]});

						//遇到了相同的元素，就不要再往结果中放了。直接往下走就行
						//!!注意这里是left+1。是为了让后面的left++和right++ 能保证不出错，如果是left - 1就会造成left多移动一次
						while (left < right&& nums[left] == nums[left + 1])
							left++;
						while (left < right&& nums[right] == nums[right - 1])
							right--;
						//别忘了，上面的left + 1就是为了匹配他俩
						left++;
						right--;
					}
				}
			}
			return ret;
		}



		/*
		第18题. 四数之和
		参考：
			https://www.programmercarl.com/0018.%E5%9B%9B%E6%95%B0%E4%B9%8B%E5%92%8C.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			总体和“于“15. 三数之和”思路非常的相似，相对多了一个for循环
			思路还是外层确定一个组合，然后双指针在内层移动。
			上题的外层只有一个for来控制，这个题目有两个for来控制。
			要注意的是，因为target是不固定的，不能简单的用“nus[i]>target”来判断是否要剪枝。
			比如-4-3-2-1 -4>-6 这里就不能剪枝。
			！！必须是“nums[i]>=0”这个条件来判断。
		*/
		vector<vector<int>> fourSum(vector<int>& nums, int target) {
			sort(nums.begin(), nums.end());
			vector<vector<int>>ret;
			int left = 0, right = 0;
			for (size_t i = 0; i < nums.size(); i++)
			{
				//剪枝，具体看上面的注释
				if (nums[i] > target&&  nums[i] >= 0) return ret;//最外面用 return ret是没问题的
				if (i > 0 && nums[i] == nums[i - 1]) continue;//对a去重。这样的两个数是相同的，结果是一样的，所以要去掉。
				for (size_t l = i + 1; l < nums.size(); l++)
				{
					//!!!二级剪枝！！ 这个别忘了。可以把这个二级剪枝看成一个数，就要对这个数剪枝
					if (nums[i] + nums[l] > target&&  nums[i] + nums[l] >= 0) break;//！！！！这个地方用“ return ret”,会导致少结果，具体原因就是return导致外面的for少遍历了
					if (l > i + 1 && nums[l] == nums[l - 1]) continue;//对a去重。这样的两个数是相同的，结果是一样的，所以要去掉。
					//if (l > i + 1 && nums[i] + nums[l] == nums[i] + nums[l - 1]) continue;//这两个是一样的


					left = l + 1;
					right = nums.size() - 1;
					while (left < right)
					{
						if ((long)nums[i] + nums[l] + nums[left] + nums[right] > target)//(long)!!有的数很大
							right--;
						else if ((long)nums[i] + nums[l] + nums[left] + nums[right] < target)
							left++;
						else {
							ret.push_back(vector<int>{nums[i], nums[l], nums[left], nums[right]});//(long)!!有的数很大

							//遇到了相同的元素，就不要再往结果中放了。直接往下走就行
							//!!注意这里是left+1。是为了让后面的left++和right++ 能保证不出错，如果是left - 1就会造成left多移动一次
							while (left < right&& nums[left] == nums[left + 1])
								left++;
							while (left < right&& nums[right] == nums[right - 1])
								right--;
							//别忘了，上面的left + 1就是为了匹配他俩
							left++;
							right--;
						}
					}
				}

			}
			return ret;
		}



		void test()
		{
			vector<int> nums{ 2,2,2,2,2 };
			vector<vector<int>>ret = fourSum(nums, 8);

		}


	};
}

//滑动窗口
namespace SlidingWindow
{
	class Solution {
	public:
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
		438、找到字符串中所有字母异位词
		题意：
			两个字符串p,s;就是p可以在s中找到，并且p可以随便调换位置，能符合s中的一段就行。然后记录这个坐标。
		参考：
			没有什么参考
		思路：
			滑动窗口
			滑动窗口大小为p的size，用数组记录下窗口每个字符出现次数。
			当窗口移动的时候，减去出去的字符的次数，记上增加上的字符出现的数量。
			如果滑动窗口中的各个字符的数量和p中的数量一样的话，把下标记上。

		*/
		vector<int> findAnagrams(string s, string p) {
			vector<int> ret;
			vector<int>vs(26, 0), vp(26, 0);//vp的长度也是26，跟p的长度无关，是根据26个字母来决定的
			for (auto c : p)//统计p中各个字符出现的次数
				vp[c - 'a']++;
			for (size_t i = 0; i < s.size(); i++)
			{
				vs[s[i] - 'a']++;
				if (i >= p.size())//滑动窗口开始往右移动的时候,窗口左边的元素数量--，右边的++
					vs[s[i - p.size()] - 'a']--;
				if (vs == vp)//!如果vs和vp相等，也就是当前滑动窗口中的各个字符出现的次数和p中的各个字符出现的字数完全一样，则满足条件
					ret.push_back(i - p.size() + 1);
			}
			return ret;
		}

		void test()
		{
			string s = "cbaebabacd";
			string p = "abc";
			vector<int> ret = findAnagrams(s, p);
			for (auto a : ret) {
				cout << a << endl;
			}
		}
	};
}

//矩阵
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

		/*
		240. 搜索二维矩阵 II
		参考：
			无
		思路：
			定位到每一行的最后一个元素，如果这个元素大于目标元素，说明这一行都不行，要往下走
			直到走到了，这一行的最后一个元素》当前元素，然后x坐标--。如果有的话就有了，没有的话就返回false
		*/
		bool searchMatrix(vector<vector<int>>& matrix, int target) {
			int x = 0;
			int y = matrix[0].size() - 1;
			while (x < matrix.size() && y >= 0) {
				if (matrix[x][y] == target)
					return true;
				else if (matrix[x][y] < target)
					x++;
				else
					y--;
			}
			return false;
		}

	};
}

//哈希
namespace Hash
{
	class Solution {
	public:
		/*
		383. 赎金信
		参考：
			https://www.programmercarl.com/0383.%E8%B5%8E%E9%87%91%E4%BF%A1.html#%E6%80%9D%E8%B7%AF
		题目：
			判断 ransomNote 是否有 magazine 中的的字符串组成，magazine中的字符只能使用一次。
		思路：
			链接：
			先是记录magazine各个字母出现的次数，record++
			然后在遍历ransomNote要是出现了对应的字符，就从record--
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
		参考：
			https://www.programmercarl.com/0242.%E6%9C%89%E6%95%88%E7%9A%84%E5%AD%97%E6%AF%8D%E5%BC%82%E4%BD%8D%E8%AF%8D.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			哈希表
			我比他少一个数组，稍微更简单一些
			1、遍历s字符，相同的字符，数组值++。
			2、遍历t字符，相同的字符，数组值--。
			2、最后，检查字符都减完了不
		*/
		bool isAnagram(string s, string t) {
			int record1[26] = { 0 };//0-25代表26个英文字母 

			for (size_t i = 0; i < s.size(); i++)
			{
				record1[s[i] - 'a']++;
			}
			for (size_t i = 0; i < t.size(); i++)
			{
				record1[t[i] - 'a']--;
			}

			for (size_t i = 0; i < 26; i++)
			{
				if (record1[i] != 0)
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
		参考：
			https://www.programmercarl.com/0001.%E4%B8%A4%E6%95%B0%E4%B9%8B%E5%92%8C.html#%E6%80%9D%E8%B7%AF
		题目：
			找到两个元素相加等于元素值，然后返回这两个元素的下标。
		思路：
			这个不能用双指针的方法，这个题目要求返回的值数组下标。
			双指针要用，就必须要排序，就不能返回正确的下标。
			之前的那个解法比较复杂，现在换个简单的。
			假设目标是9，拿到数组第一个元素为2，那么就要去找7.
			为了提高查找的效率用unordered_map。
			找到了就返回两者的下标，
			找不到就把当前的数组元素放到unordered_map中。
		*/
		vector<int> twoSum(vector<int>& nums, int target) {
			unordered_map<int, int> num;
			for (int i = 0; i < nums.size(); i++)
			{
				if (num.find(target - nums[i]) != num.end()) {//find是查找key，稍微注意下
					return { i,num[target - nums[i]] };
				}
				num.insert(pair<int, int>(nums[i], i));
			}
			return {};
		}




		/*
		202. 快乐数
		参考：
			https://www.programmercarl.com/0202.%E5%BF%AB%E4%B9%90%E6%95%B0.html#%E6%80%9D%E8%B7%AF
			其实我没有参考它的思路，这个思路更好
		思路：
			哈希表-借助无序map，不是数组的形式
			这个题目的难在的是这个题目的理解，理解这个数学题
			最后的结果sum是1返回true，
			而返回false的条件就是出现了之前出现过的值。说明他会陷入循环中。
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
				for (size_t i = 0; i < strNums.size(); i++) {
					int digit = strNums[i] - '0';
					sum += digit * digit;//！！计算平方和
				}
				if (sum == 1)//平方和是1，说明满足要求，返回true
					return true;
				if (tempNums.find(sum) == tempNums.end())//这个结果平方和，之前没有出现过，那么就放到set中，继续下一次循环
					tempNums.insert(sum);
				else//如果计算的结果之前就出现过，那么肯定是不行的。
					return false;
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
		349. 两个数组的交集
		参考：
			https://www.programmercarl.com/0349.%E4%B8%A4%E4%B8%AA%E6%95%B0%E7%BB%84%E7%9A%84%E4%BA%A4%E9%9B%86.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			题意：给定两个数组，编写一个函数来计算它们的交集。
			输出结果中的每个元素一定是 唯一 的。我们可以 不考虑输出结果的顺序 。
			把其中一个数组，放到set中，然后遍历另外一个数组。
			从set找这个数组的元素，找到了就是交集
			最后返回这个交集
		*/
		vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
			unordered_set<int> nums1_set(nums1.begin(), nums1.end());
			unordered_set<int>ret;

			for (auto num : nums2) {
				if (nums1_set.find(num) != nums1_set.end()) {
					//ret.push_back(num);//!这样会重复插入相同的数据，如果在从vector查找的话，时间复杂度就是n
					ret.insert(num);
				}
			}
			return vector<int>(ret.begin(), ret.end());
		}

		/*
		第454题.四数相加II
		参考：
			https://www.programmercarl.com/0454.%E5%9B%9B%E6%95%B0%E7%9B%B8%E5%8A%A0II.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		题目：
			给四个数组，从每个数组中挑选一个数，然后相加为0。
			返回有几种组合。
		思路：
			先计算前两个数组的所有和，放在unordered_map中，和做key，和出现次数做value
			然后用“target-两个后两个数组的所有和”得到差
			用得到的这个差，在map查找。
			如果找到了就把value的次数加上。
		*/
		int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
			int count = 0;
			unordered_map<int, int> num;
			for (auto n1 : nums1) {
				for (auto n2 : nums2) {
					num[n1 + n2]++;
				}
			}
			for (auto n3 : nums3) {
				for (auto n4 : nums4) {
					if (num.find(0 - (n3 + n4)) != num.end())
						count += num[0 - (n3 + n4)];
				}
			}
			return count;
		}



		void test() {
			vector<int> nums{ -1,0,1,2,-1,-4 };

		}
	};
}

//区间
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
			https://www.programmercarl.com/0452.%E7%94%A8%E6%9C%80%E5%B0%91%E6%95%B0%E9%87%8F%E7%9A%84%E7%AE%AD%E5%BC%95%E7%88%86%E6%B0%94%E7%90%83.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
			下面贪心命名空间中，也写了一遍
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

//栈和队列
namespace StackandQueue {

	/*
	232.用栈实现队列
	参考：
		https://www.programmercarl.com/0232.%E7%94%A8%E6%A0%88%E5%AE%9E%E7%8E%B0%E9%98%9F%E5%88%97.html
	思路：
		要用两个栈来实现，一个栈实现不了
	*/
	class MyQueue {
	public:
		stack<int> stkin;
		stack<int> stkout;
		MyQueue() {

		}

		void push(int x) {
			stkin.push(x);
		}

		int pop() {
			//！核心在这，队列出的时候，stkin全部到stkout中，最后是从stkout中出去
			if (stkout.empty())
			{
				while (!stkin.empty())
				{
					stkout.push(stkin.top());
					stkin.pop();
				}
			}
			int ret = stkout.top();
			stkout.pop();
			return ret;
		}
		//返回第一个元素
		int peek() {
			int ret = pop();
			stkout.push(ret);
			return ret;//pop函数会导致stkout缺少一个，元素，所以要补回来
		}

		bool empty() {
			return stkin.empty() && stkout.empty();
		}
	};


	/*
	225. 用队列实现栈
	参考：
		https://www.programmercarl.com/0225.%E7%94%A8%E9%98%9F%E5%88%97%E5%AE%9E%E7%8E%B0%E6%A0%88.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
	思考：
		队列模拟栈，其实一个队列就够了。两个也行。
		栈的特点，其实就是一端出入，先进后出。队列有两端出入，所以很好做
		比如123 ，栈要返回1
		每次在队列中插入数据，然后把队列中的n-1都从重新插到“尾巴； 变成231
		这样最后剩的1，就拿出去：变成23
	*/
	class MyStack {
	public:
		queue<int> que;
		MyStack() {

		}

		void push(int x) {
			que.push(x);
		}

		int pop() {
			int quesize = que.size();
			quesize--;
			while (quesize--)//从123 变成 231
			{
				que.push(que.front());
				que.pop();
			}
			int ret = que.front();
			que.pop();
			return ret;
		}

		int top() {
			return que.back();
		}

		bool empty() {
			return que.empty();
		}
	};


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
		参考：
			https://www.programmercarl.com/0020.%E6%9C%89%E6%95%88%E7%9A%84%E6%8B%AC%E5%8F%B7.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
			我这个是自己的思路，不是参考它的，我的思路在下面了。
		思路：
			括号要一一匹配。
			遍历这个s，如果是括号的左边的就往栈里放，
			从栈里往外走的时候，得判断你要拿的这个括号是不是和栈最上面的元素有对应关系。
			如果有对应关系，那么就拿，没有就直接返回false。

			对应关系就是：(40  )41   [91 ]93      {123      }125

			遍历结束后，如果栈里面被拿空了，那么说明整个字符串没有问题，只要不是空的，说明不行
		*/
		bool isValid(string s) {
			stack<char> stk;
			for (const char& c : s)
			{
				//!注意的“}”的情况， 所以当一开始就}的时候，stk.empty()保证能加进去
				if (stk.empty() || c == '(' || c == '[' || c == '{')
					stk.push(c);
				else
				{
					if (stk.top() + 1 == c || stk.top() + 2 == c)
						stk.pop();
					else
						return false;
				}
			}
			if (stk.empty())
				return true;
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
		参考：
			https://www.programmercarl.com/0150.%E9%80%86%E6%B3%A2%E5%85%B0%E8%A1%A8%E8%BE%BE%E5%BC%8F%E6%B1%82%E5%80%BC.html#%E6%80%9D%E8%B7%AF
			思路只是参考，不一样
		思路：
			遍历tokens，到栈中，
			遇到运算符的时候，就往前遍历两个元素，
			然后根据这个运算符来计算结果，
			算到的结果再次放到栈中。
			知道结束，返回计算的结果。

			中间用了switch，得知道四个ASCII码，现场写的话，还是用if判断吧 if (tokens[i] == "+")
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
					int r = stoi(stk.top());
					stk.pop();
					int l = stoi(stk.top());
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

		/*
		1047. 删除字符串中的所有相邻重复项
		参考：
			https://www.programmercarl.com/1047.%E5%88%A0%E9%99%A4%E5%AD%97%E7%AC%A6%E4%B8%B2%E4%B8%AD%E7%9A%84%E6%89%80%E6%9C%89%E7%9B%B8%E9%82%BB%E9%87%8D%E5%A4%8D%E9%A1%B9.html
		思考：
			这里使用了栈的思想，采用的string来处理的
			如果当前遍历的c和ret中的尾巴不相等就放，相等就删除ret的尾巴。
			当然，一开始的时候ret时候空的要放一个。
		*/
		string removeDuplicates(string s) {
			string ret;
			for (const char& c : s) {
				if (ret.empty() || ret.back() != c) {
					ret.push_back(c);
				}
				else
					ret.pop_back();
			}
			return ret;
		}

		/*
		239. 滑动窗口最大值
		参考：
			https://www.programmercarl.com/0239.%E6%BB%91%E5%8A%A8%E7%AA%97%E5%8F%A3%E6%9C%80%E5%A4%A7%E5%80%BC.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			单调栈的思路，没有完全按照链接中的思路去做的，他的思路确实麻烦点。
			参考的新思路，也是单调栈的思路。
			https://leetcode.cn/problems/sliding-window-maximum/solutions/2361228/239-hua-dong-chuang-kou-zui-da-zhi-dan-d-u6h0/
			1、构建出滑动窗口，使用单调栈，拿到当前窗口的最大值，然后放到ret[0]
			2、然后再到新的当前的滑动窗口中，因为滑动窗口移动了，首先要删除上次窗口中，最左边的部分-dequq.pop_front()
			3、接着使用单调栈，删除小于当前nums[i]的数据
			4、新的结果放到ret[i-k+1]
			单调栈，为从头到尾为递减栈，也就是最大元素在栈头。

			这不行的原因是因为 从栈里删除的时候，每次都删完删干净，不该删的也删了
			用std:stack不行的原因，是因为stack只能在栈顶操作元素，举例 栈顶 1 2 ，新元素3.那么最后的结果就只剩3.
			！所以，就得用deque这种两端都能操作的容器.！
		*/
		vector<int> maxSlidingWindow(vector<int>& nums, int k) {
			vector<int> ret;
			deque<int> dque;//这个不行，
			for (size_t i = 0; i < k; i++) {
				//如果发现当前的元素》栈顶元素，就删除当前元素。因为是单调栈，后面的元素肯定比栈顶小，所以最后的结果肯定是把栈里的元素都删完
				//！！注意，这里是当前元素大于队列的尾巴，就要把尾巴踢掉！！
				//！！这么做的目的是保持单调栈的单调递减！！！
				//比如1312 第一个for处理后就是31 如果比较的是dque.front()就是312.很明显没有单调性
				while (!dque.empty() && nums[i] > dque.back())
					dque.pop_back();
				dque.push_back(nums[i]);
			}
			//ret[0] = stk.top();
			ret.push_back(dque.front());

			//！@！上下两端几乎很像，就是下面多了一个移动滑动窗口要删除最左边的数据的逻辑
			for (int i = k; i < nums.size(); i++) {
				//如果栈顶，并且这个栈顶是上次滑动窗口最左边的元素，则要删除他
				//判断条件不能删除。假设栈顶元素，不是最左边的而是中间的，你要是把他删了，下个滑动窗口的最大值就不对了
				if (dque.front() == nums[i - k])
					dque.pop_front();
				while (!dque.empty() && nums[i] > dque.back())
					dque.pop_back();
				dque.push_back(nums[i]);
				ret.push_back(dque.front());
			}
			return ret;
		}

		/*
		347.前 K 个高频元素
		参考：
			https://www.programmercarl.com/0347.%E5%89%8DK%E4%B8%AA%E9%AB%98%E9%A2%91%E5%85%83%E7%B4%A0.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			priority_queue（优先级队列），会自动排序，只能从尾巴插入，从头取数据
			优先级队列，采用从头到尾，从小往大排列的，这样数据较小的就位于头部,较大的数据位于尾部。
			一旦队列中的数量超过了k，从头部删除删除掉数据，最后剩下的就是高频数据。
			最后把剩下的数据都放到vec中。
		*/
		class cm
		{
		public:
			bool operator() (const pair<int, int>& l, const  pair<int, int> &r)
			{
				return l.second > r.second;
			}
		};

		vector<int> topKFrequent(vector<int>& nums, int k) {
			map<int, int> mp;
			priority_queue<pair<int, int>, vector<pair<int, int>>, cm >pque;
			//统计各个数据出现的频率
			for (size_t i = 0; i < nums.size(); i++) {
				mp[nums[i]]++;
			}

			for (pair<int, int> it : mp) {
				pque.push(it);
				if (pque.size() > k)//!!一旦这个队列中的元素数量超过了k，这个队列是自动排序的，说明头部的这个是频率最小的，给他删掉。
					pque.pop();
			}
			vector<int>ret;
			for (size_t i = 0; i < k; i++)
			{
				ret.push_back(pque.top().first);
				pque.pop();
			}
			return ret;
		}

		void test()
		{
			vector<int>nums{ 1,3,1,2,0,5 };

			vector<int>ret = maxSlidingWindow(nums, 3);
			for (auto c : ret)
				cout << c << " ";
		}

	};
}



//链表
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
			https://www.programmercarl.com/0019.%E5%88%A0%E9%99%A4%E9%93%BE%E8%A1%A8%E7%9A%84%E5%80%92%E6%95%B0%E7%AC%ACN%E4%B8%AA%E8%8A%82%E7%82%B9.html#%E6%80%9D%E8%B7%AF
		思路：
			双指针，这样就能遍历一遍的时候，直接拿到要删除节点的对应位置。
			1、增加虚拟头结点。
				这么做的好处是方便删除头节点；具体参考：https://mp.weixin.qq.com/s/L5aanfALdLEwVWGvyXPDqA
			2、定义双指针，fast和low。
				fast先走n+1。这样的目的是为了让low落在要删除的点的前面。（到时候fast和slow一块走，fast走到末尾的时候，slow就是在对应的位置）
			3、然后移动双指针，直到fast到了最后的位置。
			4、然后low->next=low->next->next删除对应的点
			5、返回dummy->next;
		*/
		ListNode* removeNthFromEnd(ListNode* head, int n) {
			ListNode* dummy = new ListNode(0);
			dummy->next = head;
			ListNode* fast = dummy, *slow = dummy;

			// 让fast指针先走n+1步
			for (int i = 0; i < n + 1; i++) {
				fast = fast->next;
			}
			//往后移动双指针
			while (fast != nullptr) {
				fast = fast->next;
				slow = slow->next;
			}
			// 当fast指针到达末尾时，slow指针就指向了要删除节点的前一个节点
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



		/*
		203.移除链表元素
		参考：
			https://www.programmercarl.com/0203.%E7%A7%BB%E9%99%A4%E9%93%BE%E8%A1%A8%E5%85%83%E7%B4%A0.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			删除链表的元素的方法，有两种，这里选择了“统一方法”。具体参考笔记。
		*/
		ListNode* removeElements(ListNode* head, int val) {
			ListNode* dummyHead = new ListNode(0);//统一方法中的虚拟头节点
			dummyHead->next = head;
			ListNode* cur = dummyHead;//当前指针
			while (cur->next != nullptr)
			{
				if (cur->next->val == val)
				{
					ListNode* tmp = cur->next;
					cur->next = cur->next->next;
					delete tmp;//!!!在我的编译器中，delete出现了崩溃。不知道为啥
				}
				else
				{
					cur = cur->next;//当前的指针往后移动
				}
			}
			head = dummyHead->next;
			delete dummyHead;//以上两部都是为了释放dummyHead内存
			return head;
		}

		/*
		707.设计链表
		参考：
			https://www.programmercarl.com/0707.%E8%AE%BE%E8%AE%A1%E9%93%BE%E8%A1%A8.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			可以说这五个接口，已经覆盖了链表的常见操作，是练习链表操作非常好的一道题目
			为了方便操作还是采用了虚拟头节点的方法。
			如果要手撸代码的话，就画个图就好理解了。
			定义_size变量，方便后面的处理
		*/
		// 定义链表节点结构体
		struct LinkedNode {
			int val;
			LinkedNode* next;
			LinkedNode(int val) :val(val), next(nullptr) {}
		};

		class MyLinkedList {
		public:
			MyLinkedList() {
				_dummyHead = new LinkedNode(0);
				_size = 0;
			}

			//获取链表第index个节点的数值.如果索引无效，则返回-1。
			int get(int index) {
				if (index > _size - 1 || index < 0)
					return -1;
				LinkedNode *cur = _dummyHead->next;
				while (index--) {// 如果--index 就会陷入死循环!不知道为啥
					cur = cur->next;
				}
				return cur->val;
			}

			//在链表的最前面插入一个节点.插入后，新节点将成为链表的第一个节点。
			void addAtHead(int val) {
				LinkedNode *newNode = new LinkedNode(val);
				//_dummyHead->next = newNode;//_dummyHead->next本来就有东西，这么一加就把原来的替换了，不好
				newNode->next = _dummyHead->next;//_dummyHead和newNode都接上了“真。头节点”
				_dummyHead->next = newNode;//更改_dummyHead的位置到头节点
				_size++;
			}

			//在链表的最后面插入一个节点。
			void addAtTail(int val) {
				LinkedNode *newNode = new LinkedNode(val);
				LinkedNode *cur = _dummyHead;
				while (cur->next != nullptr) {
					cur = cur->next;
				}
				cur->next = newNode;
				_size++;
			}

			//将一个值为 val 的节点插入到链表中下标为 index 的节点之前。
			//如果 index 等于链表的长度，则该节点将附加到链表的末尾。
			//如果 index 大于链表长度，则不会插入节点。
			//如果index小于0，则在头部插入节点。
			void addAtIndex(int index, int val) {
				if (index > _size) return;
				if (index < 0) index = 0;
				LinkedNode *newNode = new LinkedNode(val);
				LinkedNode *cur = _dummyHead;
				while (index--) {
					cur = cur->next;
				}
				//cur->next = newNode;//cur->next本来后面就有，这样就重复了。
				newNode->next = cur->next;//newNode->next 和 cur->next都接同一个节点。
				cur->next = newNode;//看不懂就画图
				_size++;
			}

			//如果下标有效，则删除链表中下标为 index 的节点。
			void deleteAtIndex(int index) {
				if (index >= _size || index < 0) return;
				LinkedNode *cur = _dummyHead;
				while (index--) {
					cur = cur->next;
				}
				LinkedNode *tmp = cur->next;//要删除的节点
				cur->next = cur->next->next;
				delete tmp;
				_size--;
			}

		private:
			int _size;//!!我感觉不用size来记录长度也是可以的。但是我写的代码不对，我也懒得调了。
			LinkedNode *_dummyHead;
		};


		/*
		206.反转链表
		参考：
			https://www.programmercarl.com/0206.%E7%BF%BB%E8%BD%AC%E9%93%BE%E8%A1%A8.html#%E6%80%9D%E8%B7%AF
		思路：
			双指针。
			一个pre，一个cur指针。
			反转cur-》next指向，指向pre。
			(因为cur-》next有本来指向，所以要保存cur-》next的变量)
			然后往后移动pre和cur指针。
			直到cur为null，结束
			！一画图就很明白
		*/
		ListNode* reverseList(ListNode* head) {
			ListNode *cur = head;
			ListNode *pre = nullptr;
			while (cur)
			{
				ListNode *tmp = cur->next;//因为cur-》next有本来指向，所以要保存cur-》next的变量
				cur->next = pre;//反转指向，当前“指向”前一个
				pre = cur;//顺序别颠倒
				cur = tmp;
			}
			return pre;
		}

		/*
		24. 两两交换链表中的节点
		参考：
			https://www.programmercarl.com/0024.%E4%B8%A4%E4%B8%A4%E4%BA%A4%E6%8D%A2%E9%93%BE%E8%A1%A8%E4%B8%AD%E7%9A%84%E8%8A%82%E7%82%B9.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			比如：x 1234，x先接2，然后接1；再接4，然后接3。
			以12举例，x从指向1变成了指向2.没有临时变量的话，1就找不到了。
			同理，2从指向3变成了1，没有临时变量的话，3就找不到了。
			（和上体同理）
		*/
		ListNode* swapPairs(ListNode* head) {
			ListNode *dummyHead = new ListNode(0);
			dummyHead->next = head;
			ListNode *cur = dummyHead;
			while (cur->next != nullptr&&cur->next->next != nullptr)
			{
				ListNode *tmp = cur->next;//其实是“1”
				ListNode *tmp1 = cur->next->next->next;//其实是“3”

				cur->next = cur->next->next;//x接2
				cur->next->next = tmp;//2接1
				cur->next->next->next = tmp1;//1接3
				cur = cur->next->next;//cur每次要往后移动两次
			}
			return dummyHead->next;
		}

		/*
		面试题 02.07. 链表相交
		参考：
			https://www.programmercarl.com/%E9%9D%A2%E8%AF%95%E9%A2%9802.07.%E9%93%BE%E8%A1%A8%E7%9B%B8%E4%BA%A4.html#%E6%80%9D%E8%B7%AF
		思路：
			这个题目其实就是返回两个链表中元素相同的节点。
			这两个节点不是光值相同，而且“位置”相同，也就是从后面数他们的位置相同。并且两个点的内存地址也是一样的。

			1、先判断哪个链表长度长。
			2、为了方便处理，使用swap函数，使链表a始终是最长的。
			3、然后长的链表移动到和短链表开头的位置。
			4、判断两个链表中是否存在相同的元素，有的话就返回。
		*/
		ListNode *getIntersectionNode_mianshiti(ListNode *headA, ListNode *headB) {
			ListNode *tmpa = headA;
			ListNode *tmpb = headB;
			int lena = 0, lenb = 0;
			while (tmpa != nullptr) {
				tmpa = tmpa->next;
				lena++;
			}
			while (tmpb != nullptr) {
				tmpb = tmpb->next;
				lenb++;
			}
			tmpa = headA;
			tmpb = headB;
			if (lenb > lena) {//保证链表a是长的那个，后续的处理就不用分情况处理了。
				swap(lena, lenb);
				swap(tmpa, tmpb);
			}

			for (int i = 0; i < lena - lenb; i++)
			{
				tmpa = tmpa->next;
			}

			while (tmpa != nullptr)
			{
				//if (tmpa->val == tmpb->val)//！！这个题目判断的是指针相同，所以不能用值来判断。
				if (tmpa == tmpb)
					return tmpa;
				tmpa = tmpa->next;
				tmpb = tmpb->next;
			}
			return nullptr;
		}


		/*
		142.环形链表II
		参考：
			https://www.programmercarl.com/0142.%E7%8E%AF%E5%BD%A2%E9%93%BE%E8%A1%A8II.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路1——双指针：
			这个思路比较复杂，是卡子哥讲的那个思路。
			其中的数学推导确实比较麻烦。
			比下面的优势就是在空间复杂度上好点
			自己是1，下面的是n
		思路2——哈希表：
			思路非常的简洁。而且好记忆.
			遍历链表，放到set容器中。
			如果遍历的元素之前出现过，则这个就是这个点。
		*/
		ListNode *detectCycle(ListNode *head) {
			unordered_set<ListNode *> uset;
			while (head != nullptr)
			{
				if (uset.count(head) == 1)
					return head;
				uset.insert(head);
				head = head->next;
			}
			return nullptr;
		}

		/*
		160. 相交链表
		参考：
			无；这个题目和上面的题目-面试题 02.07. 链表相交。一样的。
			不同的。这个代码比较简答，那个思路复杂点
		思路：
			核心。为什么当pa==pb的时候，只要不是nullprt，就是相交的点？
		举例：
			a长度7 前2不同，后5相同；b长度8，前3不同，后5相同。
			因为代码中的一个核心是。a走完了，开始走b的。b也是一样
			对a来说，先走a的2，再走a的5，然后走b的3.
			对b来说，先走b的3，再走b的5，然后走a的2。
			这就能看出，他们走到步数相同的时候，就是这俩交点的时候。
			所以，根据题目要求就是返回交点的时候。
		*/
		ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
			if (headA == nullptr || headB == nullptr) return nullptr;
			ListNode *pa = headA;
			ListNode *pb = headB;
			while (pa != pb) {
				pa = (pa == nullptr) ? headB : pa->next;
				pb = (pb == nullptr) ? headA : pb->next;
			}
			return pa;
		}

		/*
		234. 回文链表
		参考：
			无
		思路：
			进阶：你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？
			题解中，有这个思路，我没用。！后期还是要弄下，现在先用简单的。
			把链表放到数组中，然后用双指针就很方便了。
		*/
		bool isPalindrome(ListNode* head) {
			vector<int> vec;
			while (head != nullptr) {
				vec.push_back(head->val);
				head = head->next;
			}

			for (int s = 0, e = vec.size() - 1; s <= e; s++, e--)
			{
				if (vec[s] != vec[e]) return false;
			}
			return true;
		}


		/*
		148. 排序链表
		题目参考：
			https://leetcode.cn/problems/sort-list/?envType=study-plan-v2&envId=top-100-liked
			https://leetcode.cn/problems/sort-list/solutions/2665699/lian-biao-bing-gui-pai-xu-by-zheng-zai-j-lqnn/
		并归排序参考：
			https://www.cnblogs.com/chengxiao/p/6194356.html
		思路：
			并归查找。
			先把每个元素分开，然后从分开的元素中，每两个部分各自拿出元素一一对比，然后从小到大排序放到新的一部分中。
			得到的新的一部分和另外一个新的部分，再重复这个过程，然后又得到一个新的部分。。
			直到最后，就只剩了一个新的部分。
			这个新的部分，就是最后想要的排序。
			1、通过双指针，拿到链表的中心。
			2、然后截取链表，截成左右两部分。
			3、通过递归不断不断的截取，截到只剩一个点
			4、然后开始合并这些点，根据大小排序来和。
			5、最后得到的就是题目要求的。
		*/

		ListNode* sortList(ListNode* head) {
			//1、如果题目中的给的链表的长度为1，或者为1，直接返回
			//2、这个函数本质就是分割链表的，所以当传进来的长度为 1的时候，没必要再分了。
			if (head == nullptr || head->next == nullptr) return head;
			ListNode *fast = head->next;
			ListNode *slow = head;
			while (fast != nullptr && fast->next != nullptr)//别忘了fast != nullptr，如果fast=null,后面的判断fast->next会出问题
			{
				fast = fast->next->next;//!!别忘了快指针，每次走两步
				slow = slow->next;
			}
			ListNode *rhead = slow->next;// 链表第二部分的头节点
			slow->next = nullptr;// 切断链表
			ListNode* left = sortList(head);
			ListNode* right = sortList(rhead);
			merge(left, right);
			return head;
		}
		//合并传进来的链表，按照从小到大的顺序
		ListNode* merge(ListNode *left, ListNode *right) {
			if (left == nullptr || right == nullptr) return nullptr;
			ListNode * dummyNode = new ListNode(-1);
			ListNode * p = dummyNode;
			//当发现左链表或者是右链表的“当前节点”中，有一个出现了空节点。
			//这个时候，已经没有办法继续再while判断节点的元素的值大小了，要在while外面单独处理
			while (left != nullptr && right != nullptr)
			{
				if (left->val > right->val) {
					p->next = right;//接上较小的那个点
					right = right->next;//较小的那个点，被接上了，下次如果还接的话，就是它的下个点。
				}
				else//包括了小于和等于的情况
				{
					p->next = left;//接上较小的那个点
					left = left->next;//较小的那个点，被接上了，下次如果还接的话，就是它的下个点。
				}
				p = p->next;//p也要往下走，然后来接后面的点。
			}
			//上面去接这个节点的时候，一定出现一个先被接完的，也就是该链表被遍历到nullptr。
			//while里已经不能再对他进行处理了。
			//下面，也就是谁当前不是nullptr的时候，就要把他接上
			if (left != nullptr)
				p->next = left;
			else if (right != nullptr)
				p->next = right;
			ListNode * tmp = dummyNode->next;
			delete dummyNode;
			return tmp;
		}


		ListNode* sortList_easy(ListNode* head) {//先来个简单的，到手万一想不起来了，还有这个保底。
			multiset<int> worker;
			auto sub = head;
			while (sub) worker.insert(sub->val),
				sub = sub->next;
			sub = head;
			for (auto &i : worker)
				sub->val = i, sub = sub->next;
			return head;
		}

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
			ret = a.removeElements(&lb, 5);
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

//树
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

		//什么序的意思是指在什么位置对val访问。

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

		要学习的点：
			中序遍历正确的搜索树，它的顺序是从小到大的。
		*/
		long long isValidBST_MaxValue = LONG_MIN; // 因为后台测试数据中有int最小值
		bool isValidBST(TreeNode* root) {
			if (root == nullptr)return true;//都遍历到底了，还没问题，说明这个搜索树肯定好
			bool l = isValidBST(root->left);
			if (root->val > isValidBST_MaxValue)isValidBST_MaxValue = root->val;
			else
				return false;

			bool r = isValidBST(root->right);

			return l && r;
		}

		/*
		530. 二叉搜索树的最小绝对差
		自己思路：
			采用中序遍历，其实就是求相邻两个节点的最小的差值
		参考：
			https://www.programmercarl.com/0530.%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E7%9A%84%E6%9C%80%E5%B0%8F%E7%BB%9D%E5%AF%B9%E5%B7%AE.html#%E6%80%9D%E8%B7%AF

		其中的用指针记录前一个节点的方式，手动敲一下
		*/
		int Difference_MinValue = INT_MAX;
		int Difference_LastValue = INT_MAX;//这个位置只能是这个，主要是应对一个点的处理。如果是0的话，如果遇到了0-0那么差值肯定是0了，再也不会变了。如果是INT_MIN的话，1-INT_MIN就会超过int的范围。只有max，任何-max都不会超范围，只是第一个点的时候差值会较大，但是第二个点的时候，就恢复了。
		int getMinimumDifference(TreeNode* root) {
			if (root == nullptr)return 0;
			int L = getMinimumDifference(root->left);
			if (abs(root->val - Difference_LastValue) < Difference_MinValue)Difference_MinValue = abs(root->val - Difference_LastValue);
			Difference_LastValue = root->val;
			getMinimumDifference(root->right);

			return Difference_MinValue;
		}

		/**
		501. 二叉搜索树中的众数
		自己的思路：
			1、用map记录每种key出现的次数，然后放到vec中去排序（这种适用任何二叉树）
			2、（这种适用搜索二叉树）中序遍历，先记录这个值，然后记录元素出现的次数。在进来的时候，如果是相同的值，这个次数++。如果不相同从新记录次数。
		参考：
			https://www.programmercarl.com/0501.%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E4%B8%AD%E7%9A%84%E4%BC%97%E6%95%B0.html#%E6%80%9D%E8%B7%AF
		收获：
			当一个变量代表的含义在if的含义不明确的，虽然有效果，但是思路不好理解，就别用。
			比如：判断第一个节点的时候，最明显的就是前值指针为空的时候，他就是第一个节点。
			还有判断前值的val的时候，如果用*(--findMode_vec.end())很明显一次不明确。肯定会造成bug，只能满足某些情况。不如findMode_pre->val
		*/
		vector<int> findMode_vec;
		int findMode_allCount = 0;//当前中总的次数
		int findMode_signalCount = 0;//单个元素出现的次数
		TreeNode* findMode_pre = NULL;
		void midSearch(TreeNode* root)
		{
			if (root == nullptr) return;
			midSearch(root->left);
			if (findMode_allCount == 0) {//第一个节点
				findMode_signalCount = 1;
			}
			else if (root->val == findMode_pre->val)//如果当前的值和vec中的最后一个值相等，说明又出现了同一个数，次数++
			{
				findMode_signalCount++;
			}
			else//如果次数已经不是0了，并且值和前面的不一样，说明出现了新的值。
			{
				findMode_signalCount = 1;//单个次数为1
			}
			findMode_pre = root;

			if (findMode_signalCount == findMode_allCount)
			{
				findMode_vec.push_back(root->val);
			}
			if (findMode_signalCount > findMode_allCount)
			{
				findMode_allCount = findMode_signalCount;
				findMode_vec.clear();
				findMode_vec.push_back(root->val);
			}
			midSearch(root->right);
			return;
		}
		vector<int> findMode(TreeNode* root) {
			midSearch(root);
			return findMode_vec;
		}


		/*
		236. 二叉树的最近公共祖先
			代码简单，思路复杂
		核心思路：
			从下往上找。用后序遍历。
			找到了p和q就往上父节点返回，直到他俩返回的父节点是一样的。
		要学习的是：
			分析的代码的时候，方便理解或者是写，就从叶子结点往上走，好理解
			TreeNode* left = lowestCommonAncestor(root->left, p, q);
			TreeNode* right = lowestCommonAncestor(root->right, p, q);
			这两行代码，如果要一层一层递归进去，理解很不好理解。
			可以简化理解，这个思路在任何递归的时候，都比较好用。
			 lowestCommonAncestor(root->left, p, q);  就是当前root的左子树的结果
			 lowestCommonAncestor(root->right, p, q); 就是当前root的右子树的结果
			 不管它内部是怎么递归的，就知道这个结果就行。

		参考：
			https://www.programmercarl.com/0235.%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E7%9A%84%E6%9C%80%E8%BF%91%E5%85%AC%E5%85%B1%E7%A5%96%E5%85%88.html#%E6%80%9D%E8%B7%AF
		*/
		TreeNode* lowestCommonAncestor1(TreeNode* root, TreeNode* p, TreeNode* q) {
			if (root == nullptr || root == p || root == q) return root;
			TreeNode*childLeft = lowestCommonAncestor1(root->left, p, q);//返回右子树的结果
			TreeNode*childRight = lowestCommonAncestor1(root->right, p, q);

			if (childLeft&&childRight)return root;//它的左右子树找到了pq，那么就返回他的指针，也就是root。最后最后的返回一定是在这，要返回它俩的公共的祖先。
			else if (childLeft == nullptr&&childRight)return childRight;//右子树有了p或者q，或者有了p和q。就返回右子树的指针。
			else if (childLeft &&childRight == nullptr)return childLeft;//同理
			else return nullptr;
		}

		/*
		235. 二叉搜索树的最近公共祖先
		236. 二叉树的最近公共祖先
		这两个题是一个思路，但是搜索树有自己的性质，可以根据这个性质。
		为了方便，还是学习236这种思路，通用。
		两道题的核心思想就是：
			如何判断一个节点的子树里有p，子树里有q
		参考：
			https://www.programmercarl.com/0235.%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E7%9A%84%E6%9C%80%E8%BF%91%E5%85%AC%E5%85%B1%E7%A5%96%E5%85%88.html
		*/
		TreeNode* lowestCommonAncestor11(TreeNode* root, TreeNode* p, TreeNode* q) {
			//不用判断节点为空的情况，题目中明确说了，确定存在这个点。
			if (root->val > p->val&&root->val > q->val)//如果在【pq】的右侧，那么就往左走。
			{
				TreeNode* left = lowestCommonAncestor11(root->left, p, q);
				if (left != NULL) {
					return left;
				}
			}
			else if (root->val < p->val&&root->val < q->val)//如果在【pq】的左侧，那么就往右走。
			{
				TreeNode* right = lowestCommonAncestor11(root->right, p, q);
				if (right != NULL) {
					return right;
				}
			}
			return root;
		}
		TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
			while (root)
			{
				if (root->val > p->val&&root->val > q->val)//如果在【pq】的右侧，那么就往左走。
				{
					root = root->left;
				}
				else if (root->val < p->val&&root->val < q->val)//如果在【pq】的左侧，那么就往右走。
				{
					root = root->right;
				}
				else
					return root;
			}
			return root;
		}


		/*
		701.二叉搜索树中的插入操作
		核心思路：
			迭代遍历搜索树，直到空，就插入，就这么简单。
		参考：
			https://www.programmercarl.com/0701.%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E4%B8%AD%E7%9A%84%E6%8F%92%E5%85%A5%E6%93%8D%E4%BD%9C.html#%E6%80%9D%E8%B7%AF
		*/
		TreeNode* insertIntoBST(TreeNode* root, int val) {
			if (root == nullptr)
			{
				root = new TreeNode(val);
				return root;
			}
			/*
			对于很多二叉搜索树而言，
			root->left = trimBST(root->left, low, high);
			要不都是左，要不都是右。
			为什么这样呢？
			返回值root->left代表二叉树的左节点要接的东西，
			参数root->left代表root->left要接的东西，肯地是从root->left开始往下找。
			无论往下找的时候是往左还是往右，总之都是在一开始的left下面。
			*/
			//如果要插入的值大于当前节点的值,那就插在右边
			if (val > root->val) root->right = insertIntoBST(root->right, val);//之前收
			//如果要插入的值小于当前节点的值,那就插在左边
			if (val < root->val)  root->left = insertIntoBST(root->left, val);
			return root;
		}

		/*
		450. 删除二叉搜索树中的节点
		思路：
			返回的核心，就是让遍历到要删的点，让他的父节点接上他的子节点。
		*/
		TreeNode* deleteNode(TreeNode* root, int key) {
			if (root == nullptr) return nullptr;
			if (root->val == key)
			{
				//删除是根节点——那就让对应的节点接上null
				if (root->left == nullptr&& root->right == nullptr) return nullptr;

				//删除是非根节点-左为空，右不为空,返回他的右节点
				if (root->left == nullptr&&root->right)
				{
					TreeNode* temp = root->right;
					delete root;
					return temp;
				}

				//删除是非根节点-左不为空，右为空,返回他的左节点
				if (root->left &&root->right == nullptr)
				{
					TreeNode* temp = root->left;
					delete root;
					return temp;
				}

				//删除是非根节点-左右不为空。让他的左节点接到右节点的最小的节点下面
				//二叉搜索树中，右节点都比左节点大。所以接在右节点的最小的下面。
				//寻找方法，就是从这个点开始一直往左遍历。直到遍历到了最左边的根节点
				if (root->left &&root->right)
				{
					//TreeNode* temp = root;
					//delete temp;//!!这里删除会奔溃。可能是temp删除后root就不能访问了，但是上面却可以，我也不知道力扣的编译器抽什么风
					TreeNode* cur = root->right;
					while (cur->left) cur = cur->left;
					cur->left = root->left;
					TreeNode* temp = root;
					root = root->right;     // 返回旧root的右孩子作为新root
					delete temp;            // !!总而言之，用完再删除，肯定没问题。
					return root;
				}
			}
			/*
			对于很多二叉搜索树而言，
			root->left = trimBST(root->left, low, high);
			要不都是左，要不都是右。
			为什么这样呢？
			返回值root->left代表二叉树的左节点要接的东西，
			参数root->left代表root->left要接的东西，肯地是从root->left开始往下找。
			无论往下找的时候是往左还是往右，总之都是在一开始的left下面。
			*/
			if (key > root->val)  root->right = deleteNode(root->right, key);//返回的核心，就是让遍历到要删的点，让他的父节点接上他的子节点。
			if (key < root->val)  root->left = deleteNode(root->left, key);
			return root;
		}

		/*
		669. 修剪二叉搜索树
		思路：
			返回的核心，就是让遍历到要删的点，让他的父节点接上他的子节点。
		*/
		TreeNode* trimBST(TreeNode* root, int low, int high) {
			if (root == nullptr) return nullptr;
			//该点位于范围的左侧，要考虑这个点的右子树是不是有符合规则的。
			if (root->val < low)
			{
				TreeNode* right = trimBST(root->right, low, high);
				return right;
			}
			//该点位于范围的右侧，要考虑这个点的左子树是不是有符合规则的。
			if (root->val > high)
			{
				TreeNode* left = trimBST(root->left, low, high);
				return left;
			}
			/*
			对于很多二叉搜索树而言，
			root->left = trimBST(root->left, low, high);
			要不都是左，要不都是右。
			为什么这样呢？
			返回值root->left代表二叉树的左节点要接的东西，
			参数root->left代表root->left要接的东西，肯地是从root->left开始往下找。
			无论往下找的时候是往左还是往右，总之都是在一开始的left下面。
			*/
			root->left = trimBST(root->left, low, high);
			root->right = trimBST(root->right, low, high);
			return root;
		}


		/*
		108. 将有序数组转换为二叉搜索树
		参考：
		https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/description/

		构造二叉树，自然少不了区间的分割，那么什么时候用左闭右闭呢，什么时候一开一闭呢？
		其实本质就是其实都想用左闭右闭，！只是看你怎么选了！这个想法我还没验证，!用闭区间去做这个题目。我刚才没做出来。
		比如构造二叉树这个题目，https://programmercarl.com/0106.%E4%BB%8E%E4%B8%AD%E5%BA%8F%E4%B8%8E%E5%90%8E%E5%BA%8F%E9%81%8D%E5%8E%86%E5%BA%8F%E5%88%97%E6%9E%84%E9%80%A0%E4%BA%8C%E5%8F%89%E6%A0%91.html#%E6%80%9D%E8%B7%AF
		再切中序数组的时候，比如9 3 15 20 7 知道3是根节点了，且数组下标为1；
		要切的话只能是[01) 然后是[1+1,5) 只有这种区间，才能用到下标1，并且不会把对应的元素切进去

		！！以上的分析我觉得不对，而是这个题目的设计，让01就成为了左闭右开的区间，就是不要最右边的那个元素。这是闭开只是为了方便理解题目罢了，不是核心。
		所以上面的题目要做出来的话，就得大概。不光光是要改坐标相加的地方。
		目前来看，最好的方法还是记忆，不同的题型，用不同的方法。

		二叉搜索树的构造就不用了。
		比如-10 -3 0 5 9 中间的0就是分割点，
		我要的是-10 -3 之所以“可以说”是闭区间，是因为我的代码中，不需要向上面的题目中，把分割点的下标再传进去。
		所以，闭开只是为了方便理解题目罢了，不是核心。最终还是记忆，不同的题型，用不同的方法。
		*/
		TreeNode* sortedArrayToBST1(vector<int>& nums, int left, int right)
		{
			if (left > right) return  nullptr;
			int mid = left + (right - left) / 2;//注意此处，（(right + left) / 2;）可能会出现int越界
			TreeNode* root = new TreeNode(nums[mid]);

			root->left = sortedArrayToBST1(nums, left, mid - 1);
			root->right = sortedArrayToBST1(nums, mid + 1, right);
			return root;

		}
		TreeNode* sortedArrayToBST(vector<int>& nums) {
			return sortedArrayToBST1(nums, 0, nums.size() - 1);
		}


		/*
		538. 把二叉搜索树转换为累加树
		参考：
			https://www.programmercarl.com/0538.%E6%8A%8A%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E8%BD%AC%E6%8D%A2%E4%B8%BA%E7%B4%AF%E5%8A%A0%E6%A0%91.html#%E6%80%9D%E8%B7%AF
		思路：
			二叉搜索树的题目，可以把他和数组联系起来，其他的二叉树不行，但是二叉搜索树肯定是没有问题的。
			另外这个题目用到了，双指针的思路。虽然不是双指针。
			其实就是反向中序遍历的方式(右中左)，然后不断的累加值。
			有个前置保存之前的累加值，然后按照上面的方式不断的累加，知道结束。
			就像数组倒序累加一样。

		*/
		int convertBST_pre = 0;//为什么是0呢，因为第一个节点的时候，他的累加值就是他本身
		TreeNode* convertBST(TreeNode* root) {
			if (root == nullptr) return nullptr;
			convertBST(root->right);
			root->val += convertBST_pre;
			convertBST_pre = root->val;
			convertBST(root->left);
			return root;
		}

		/*
		129. 求根节点到叶节点数字之和
		很明显是回溯的思想，学完回溯，二刷的时候再再来把
		*/
		int sumNumbers(TreeNode* root) {
			if (root->left == nullptr && root->right == nullptr) return root->val;
			sumNumbers(root->left);

		}

		/*
		968. 监控二叉树
		思路：
		先分为三种情况；
			0、未覆盖
			1、覆盖
			2、有相机
		分四种不同的情况去讨论。
			1、左右子节点都有“覆盖”，则父节点得是“无覆盖”；如果是相机也行，但是不能满足题目——最少相机节点的情况。
				让这个子节点的爷爷节点是相机，才是最少相机。但是如果他爹就是相机了，则浪费相机。
				但是，如果他爹是根节点的时候，没办法让他的爷爷做相机了（没有爷爷节点），所以父节点就赋值“相机”。（情况4）
			2、左右子节点有一个“未覆盖”，其父节点一定是“相机”，这样才能保证覆盖。（等价两个节点都未覆盖；）
			3、左右子节点有一个“相机”，其父节点一定是“覆盖”。
			4、子节点返回上来的是“覆盖”，根据情况1，该点得是“无覆盖”，该点父节点得是“相机”，但该点是根节点。没有父节点，所以该点就得为“相机”
		后续遍历：
			从下往上走的思路。
		对我而言，这四种情况的确定不是很好确定。主要是容易弄偏。
		一开始，我就弄偏了，“两个节点都未覆盖”这种情况和“左右子节点有一个“未覆盖””是一样的，父节点都得是“相机”。
		但是，都写出来也行，就是代码罗嗦点。
		*/
		int minCameraCover_ret = 0;
		int minCameraCover_Tra(TreeNode* root)
		{
			if (root == nullptr) return 1;//为了用到最少的相机，叶子节点的就得是覆盖的。
			int left = minCameraCover_Tra(root->left);
			int right = minCameraCover_Tra(root->right);
			if (left == 1 && right == 1) return 0;//1、子节点都是“覆盖”，则父节点得是“无覆盖”；
			if (left == 0 || right == 0) //2、左右子节点有一个“未覆盖”，其父节点一定是“相机”
			{
				minCameraCover_ret++;
				return 2;
			}
			if (left == 2 || right == 2)return 1;//3、左右子节点有一个“相机”，其父节点一定是“覆盖”。
			return -1;//为了满足letcode编译通过
		}
		int minCameraCover(TreeNode* root) {

			if (minCameraCover_Tra(root) == 0)//情况4
				minCameraCover_ret++;
			return minCameraCover_ret;
		}


		void test()
		{
			cout << "测试树结构" << endl;
			TreeNode *treeRoot = new TreeNode;
			TreeNode *p = new TreeNode(3);
			TreeNode *q = new TreeNode(5);

			//flatten(&treeRoot);
			//preTraversalONE(&treeRoot);

			//cout << "104. 二叉树的最大深度=" << maxDepth(&treeRoot) << endl;
			//cout << "100. 相同的树=" << isSameTree(&treeRoot, &tree4) << endl;
			//cout << "101. 对称二叉树=" << isSymmetric(&treeRoot) << endl;


			vector<string> nodes = { "5","3","6","2","4","null","7 " };
			treeRoot = createBinaryTree(nodes);//构建树
			cout << deleteNode(treeRoot, 3) << endl;
			/*vector<int> srtVec = lowestCommonAncestor(treeRoot);
			for (size_t i = 0; i < srtVec.size(); i++)
				std::cout << srtVec[i] << endl;
				*/
		}
	};
}

//回溯
namespace BackTracking {
	class Solution {
	public:


		/*
		void backtracking(参数) {
			if (终止条件) {
				存放结果;
				return;
			}

			for (选择：本层集合中元素（树中节点孩子的数量就是集合的大小）) {
				处理节点;
				backtracking(路径，选择列表); // 递归
				回溯，撤销处理结果
			}
		}
		*/


		/*
		77. 组合
		参考：
			https://www.programmercarl.com/0077.%E7%BB%84%E5%90%88.html#%E6%80%9D%E8%B7%AF
		核心：
			1、如果要用回溯算法的话，很多题目可以抽象成n叉树，用树形结构的思想去解决这些事情。
			2、回溯三部曲
				2.1、确定返回值和参数
					一般而言，递归是不需要返回值的。
					至于参数，到底使用全局变量还是局部变量，具体情况，灵活改变把
				2.2、确定回溯函数结束条件
					也就是到了所谓的“叶子节点”，
					就是拿到了想要的结果，然后要从结果中拿掉一些东西的时候。
				2.3、单层搜索的过程
					就是for和递归搭配。
					！！for负责横向遍历，递归负责纵向遍历。
		*/
		vector<int>combine_signal;//单个的结果
		vector<vector<int>> combine_ret;//总的结果

		//2.1、确定返回值和参数
		void combine_backtrak(int n, int k, int statrIndex)
		{
			//2.2、确定回溯函数结束条件
			if (combine_signal.size() == k)
			{
				combine_ret.push_back(combine_signal);
				return;
			}

			/*
			//2.3、确定单层搜索的过程——就是for和递归搭配。——递归的深度是由k控制的，宽度由n控制，剪枝后n会变小。
			for (int i = statrIndex; i <= n; i++)//选择：本层集合中元素（树中节点孩子的数量就是集合的大小
			{
				combine_signal.push_back(i);//递归，纵向遍历，增加单组元素数量，
				combine_backtrak(n, k, i + 1);
				combine_signal.pop_back();
				//增加的数量到了2，就返回，然后删除最后的元素， 从12到了1
				//然后下次for，进入所谓的横向递归，

				//!这里面面走的是12 13 14
			}
			*/
			//2.3、确定单层搜索的过程——就是for和递归搭配。
			/*
			参考：
				https://www.programmercarl.com/0077.%E7%BB%84%E5%90%88%E4%BC%98%E5%8C%96.html#%E5%89%AA%E6%9E%9D%E4%BC%98%E5%8C%96
			回溯算法，基本上在这for循环这里做“剪枝”
			1、已经选择的元素个数：combine_signal.size();
			2、还需要的元素个数为: k - combine_signal.size();
			3、 n - (k - path.size()) + 1
			*/
			for (int i = statrIndex; i <= n - (k - combine_signal.size()) + 1; i++)//本层集合中元素（树中节点孩子的数量就是集合的大小)
			{
				combine_signal.push_back(i);//递归，纵向遍历，增加单组元素数量，
				combine_backtrak(n, k, i + 1);
				combine_signal.pop_back();
				//增加的数量到了2，就返回，然后删除最后的元素， 从12到了1
				//然后下次for，进入所谓的横向递归，

				//!这里面面走的是12 13 14
			}
			return;//12 13 14走完了之后，开始走这，然后开始23 24 4
		}
		vector<vector<int>> combine(int n, int k) {
			combine_backtrak(n, k, 1);
			return combine_ret;
		}



		/*
		216. 组合总和 III
		参考;
			https://leetcode.cn/problems/combination-sum-iii/description/
		思路：
			这个题目有两个剪枝，分别是for上面的横向遍历的剪枝和递归上面的纵向遍历的剪枝
		*/
		vector<int> combinationSum3_signal;
		vector<vector<int>> combinationSum3_ret;
		//2.1、确定返回值和参数
		void combinationSum3_backtrak(int k, int targetSum, int sum, int statrIndex)
		{
			//横向遍历的剪枝
			if (sum > targetSum)
			{
				return;
			}
			//2.2、确定回溯函数结束条件
			if (combinationSum3_signal.size() == k)
			{
				if (targetSum == sum)
				{
					combinationSum3_ret.push_back(combinationSum3_signal);
				}
				return;
			}

			//2.3、确定单层搜索的过程——就是for和递归搭配。
			for (int i = statrIndex; i <= 9 - (k - combinationSum3_signal.size()) + 1; i++)
			{
				combinationSum3_signal.push_back(i);
				sum += i;
				combinationSum3_backtrak(k, targetSum, sum, i + 1);
				combinationSum3_signal.pop_back();
				sum -= i;

			}
			return;
		}
		vector<vector<int>> combinationSum3(int k, int n) {
			combinationSum3_backtrak(k, n, 0, 1);
			return combinationSum3_ret;
		}

		/*
		17. 电话号码的字母组合
		参考：
			https://www.programmercarl.com/0017.%E7%94%B5%E8%AF%9D%E5%8F%B7%E7%A0%81%E7%9A%84%E5%AD%97%E6%AF%8D%E7%BB%84%E5%90%88.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			这个题目和上面2个题目最大的区别就是有两个集合
			剪枝：
				一个集合的时候，可以做剪枝，因为后面有的结果太短了。
				多个集合的时候，不需要剪枝，因为不存在结果过短的情况
			for遍历开始的坐标：
				一个集合的时候，从上次的位置后面开始，
				多个集合的时候，从头开始，因为是不同的集合，从头开始也不会重复

		*/

		string letterCombinations_signal;
		vector<string> letterCombinations_ret;

		string iponeStr[10] = { "","",
			"abc", // 2
			"def", // 3
			"ghi", // 4
			"jkl", // 5
			"mno", // 6
			"pqrs", // 7
			"tuv", // 8
			"wxyz", // 9
		};
		// digits：按下的按键的字符串 index要出来按键字符串中的对应字符串的下标
		void letterCombinations_backtrack(string digits, int index)
		{
			if (letterCombinations_signal.size() == digits.size())
			{
				letterCombinations_ret.push_back(letterCombinations_signal);
				return;
			}
			string tmpStr = iponeStr[digits[index] - '0'];//拿到对应数字的对应字母
			for (size_t i = 0; i < tmpStr.size(); i++)
			{
				letterCombinations_signal.push_back(tmpStr[i]);
				letterCombinations_backtrack(digits, index + 1);//!!i+1不对，这样每次递归就只能是1了，起不到digits往后轮的作用
				letterCombinations_signal.pop_back();
			}
			return;
		}

		vector<string> letterCombinations(string digits) {
			if (digits.empty())return vector<string>();
			letterCombinations_backtrack(digits, 0);
			return letterCombinations_ret;
		}

		/*
		39. 组合总和
		参考：
			https://www.programmercarl.com/0039.%E7%BB%84%E5%90%88%E6%80%BB%E5%92%8C.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
			这个题目剪枝和不剪枝只是少了一些函数的递归而已。
			不剪枝的思路，更好理解
		*/
		vector<vector<int>>combinationSum_ret;
		vector<int>combinationSum_signal;

		//2.1、确定返回值和参数
		void combinationSum_back_track(const vector<int>& candidates, int sum, int target, int startIndex)
		{
			//2.2、确定回溯函数结束条件
			//if (sum > target)return; 这个剪枝之后，这个条件就用不到了，因为不会走到这一步
			if (sum == target)
			{
				combinationSum_ret.push_back(combinationSum_signal);
				return;
			}

			//2.3、确定单层搜索的过程——就是for和递归搭配; sum < target剪枝操作
			for (size_t i = startIndex; i < candidates.size() && sum < target; i++)
			{
				combinationSum_signal.push_back(candidates[i]);
				sum += candidates[i];
				combinationSum_back_track(candidates, sum, target, i);//!!因为元素是可以重复的组合，所以从i开始 比如123 有11组合
				sum -= candidates[i];
				combinationSum_signal.pop_back();
			}

		}
		vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
			sort(candidates.begin(), candidates.end());//排序的目的是为了剪枝，顺序是从小到大，前面数据的和已经超过目标值，后面的自然就不用算了。
			combinationSum_back_track(candidates, 0, target, 0);
			return combinationSum_ret;
		}


		/*
		40. 组合总和 II
		参考：
		https://www.programmercarl.com/0040.%E7%BB%84%E5%90%88%E6%80%BB%E5%92%8CII.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路有些复杂，就没有写
		*/
		vector<vector<int>>combinationSum2_ret;
		vector<int>combinationSum2_signal;
		//2.1、确定返回值和参数;bool used[]记录candidates中的数据，有没有用过，used[0]=1 低0位数据用过
		void combinationSum2_backtrack(vector<int>& candidates, int target, int sum, vector<bool>& used, int startIndex)
		{
			//2.2、确定回溯函数结束条件
			if (sum > target)return;
			if (sum == target)
			{
				combinationSum2_ret.push_back(combinationSum2_signal);
				return;
			}
			//2.3、确定单层搜索的过程——就是for和递归搭配; && sum + candidates[i] <= target剪枝操作
			for (size_t i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++)
			{
				//!看图多领会这个条件的判断。 
				//i>0保证从第二个元素开始比较，
				// candidates[i] ==candidates[i - 1] && used[i - 1] = 1说明有挨边的元素有相等的，那后面的元素的横向遍历的组合，就会和之前的重复，比如112  (前)12 有了之后，(后)12就是重复的。但是纵向遍历112 这两个1就不重复。 (前)12和(后)12 唯一的区别就是used[i-1]=1 used[i-1]=0 
				if (i > 0 && candidates[i] == candidates[i - 1] && used[i - 1] == 0)continue;
				combinationSum2_signal.push_back(candidates[i]);
				used[i] = 1;
				sum += candidates[i];
				combinationSum2_backtrack(candidates, target, sum, used, i + 1);
				used[i] = 0;// ！！ 别忘了这个回溯
				sum -= candidates[i];
				combinationSum2_signal.pop_back();
			}
			return;
		}
		vector<vector<int>>combinationSum2(vector<int>& candidates, int target) {
			vector<bool> used(candidates.size(), false);
			// 首先把给candidates排序，让其相同的元素都挨在一起。!!别忘了这个
			sort(candidates.begin(), candidates.end());
			combinationSum2_backtrack(candidates, target, 0, used, 0);
			return combinationSum2_ret;

		}


		/*
		131. 分割回文串
		参考：
			https://www.programmercarl.com/0131.%E5%88%86%E5%89%B2%E5%9B%9E%E6%96%87%E4%B8%B2.html#%E6%80%9D%E8%B7%AF
		！！这个题的最要注意的地方就是：
		递归函数的下次开始的地方 不在是固定的startIndex + 1
		而是真正对应结束位置的i，然后+1 才是新位置。
		具体看下边的注释
		*/
		vector<vector<string>> partition_ret;
		vector<string > partition_singal;
		//2.1、确定返回值和参数
		void partitionTracking(const string & s, int startIndex)
		{
			//2.2、确定回溯函数结束条件
			if (startIndex == s.size())
			{
				partition_ret.push_back(partition_singal);
				return;
			}

			//2.3、确定单层搜索的过程——！！for负责横向遍历，递归负责纵向遍历。
			for (size_t i = startIndex; i < s.size(); i++)
			{
				//判断是不是回文串
				/*
				!!!isPalindrome(s, startIndex, i - startIndex + 1) 这是错的！
				i - startIndex + 1 改成i
				一下思路，看链接的图去理解最好了。
				对于aab而言，纵向的单个a a b都取完了。
				然后开始取ab，这个时候，递归回到第二层（看图）
				for的横向遍历， ab截取a是一个i，截取"ab"是第二个i 所这个时候判断回文的范围应该是startindex 到 i
				*/
				//!!只有当前的有效才可以往下走，要不然没有意义
				if (isPalindrome(s, startIndex, i))
				{
					string cutSrt = s.substr(startIndex, i - startIndex + 1);
					partition_singal.push_back(cutSrt);
					/*
					?!为什么说递归从i+1开始 而不是寻常的startIndex + 1开始
					可以从另外一个角度理解这个事
					startIndex在一个for中是不变的，而i时发生变化的。
					！！i代表的是待处理的字串的结束位置，如果回文字符串aa这种多个的，i和startIndex就不会相等，就会出问题
					*/
					partitionTracking(s, i + 1);

					partition_singal.pop_back();
				}
				else
					continue;//这个
			}
			return;
		}

		bool isPalindrome(const string & s, int begin, int end)
		{
			for (; begin < end; begin++, end--)//<=或者<都行。比如101 
			{
				if (s[begin] == s[end])
					continue;
				else
					return false;
			}
			return true;
		}

		vector<vector<string>> partition(string s) {
			partitionTracking(s, 0);
			return partition_ret;
		}

		/*
		93. 复原 IP 地址
		参考：
			https://www.programmercarl.com/0093.%E5%A4%8D%E5%8E%9FIP%E5%9C%B0%E5%9D%80.html
		注意：
			1、递归不满足的时候，要看看用continue还是break
			2、s = "10.10.23. 这种情况，别忘了
		*/
		vector<string> restoreIpAddresses_ret;
		//2.1、确定返回值和参数
		void restoreIpAddressesTrack(string& s, int startIndex, int pointNum)
		{
			//2.2、确定回溯函数结束条件
			if (pointNum == 3)
			{
				// 判断第四段子字符串是否合法，如果合法就放进result中
				if (isValid(s, startIndex, s.size() - 1)) {
					restoreIpAddresses_ret.push_back(s);
				}
				return;
			}

			//2.3、确定单层搜索的过程——！！for负责横向遍历，递归负责纵向遍历。
			for (size_t i = startIndex; i < s.size(); i++)
			{
				if (isValid(s, startIndex, i))//当前ip合法，才有往下走的必要
				{
					s.insert(s.begin() + 1 + i, '.');//+1的原因是因为 要把.插入到i的后面
					pointNum += 1;
					restoreIpAddressesTrack(s, i + 2, pointNum);// 插入逗点之后下一个子串的起始位置为i+2
					pointNum -= 1;
					s.erase(s.begin() + 1 + i);
				}
				else
					break;
			}
		}
		bool isValid(const string& s, int start, int end)
		{
			//“”101023  s = "10.10.23."当组合成这个情况的时候，start=9 end=8
			//因为当pointNum==3的时候，会有这种情况，新的开始开始位置就是结束位置+1，很明显就超了，这种就要返回false
			if (start > end) {//!!还真有这个情况
				return false;
			}
			if (s[start] == '0' && start != end) { // 0开头的数字不合法
				return false;
			}
			int num = 0;
			//!!用atoi简化！！！
			for (int i = start; i <= end; i++) {
				if (s[i] > '9' || s[i] < '0') { // 遇到非数字字符不合法
					return false;
				}
				num = num * 10 + (s[i] - '0');
				if (num > 255) { // 如果大于255了不合法
					return false;
				}
			}
			return true;
		}

		vector<string> restoreIpAddresses(string s) {

			if (s.size() < 4)return vector<string>();
			restoreIpAddressesTrack(s, 0, 0);
			return restoreIpAddresses_ret;
		}


		/*
		78. 子集
		参考：
			https://www.programmercarl.com/0078.%E5%AD%90%E9%9B%86.html
		*/
		vector<vector<int>> subsets_ret;
		vector<int>subsets_signal;
		//2.1、确定返回值和参数
		void subsetsTracking(const vector<int>& nums, int startIndex)
		{
			//这个题目特殊的是它的结果是它遍历中的每一个都是，而不是满足了什么条件才是,所以递归结束条件才不一样
			subsets_ret.push_back(subsets_signal);// 收集子集，要放在终止添加的上面，否则会漏掉自己
			//2.2、确定回溯函数结束条件
			if (startIndex >= nums.size())return;// 终止条件可以不加
			//2.3、确定单层搜索的过程——！！for负责横向遍历，递归负责纵向遍历。
			for (size_t i = startIndex; i < nums.size(); i++)
			{
				subsets_signal.push_back(nums[i]);
				subsetsTracking(nums, i + 1);
				subsets_signal.pop_back();
			}
			return;
		}
		vector<vector<int>> subsets(vector<int>& nums) {
			subsetsTracking(nums, 0);
			return subsets_ret;
		}

		/*
		90. 子集 II
		参考：
		https://www.programmercarl.com/0090.%E5%AD%90%E9%9B%86II.html#%E6%80%9D%E8%B7%AF
		这个题目和40题组合问题II 是非常相似的。是40题和78题的组合
		！这个问题和40题组合问题II的关键都是去重，这种问题的去重分为
		树枝去重，树层去重。树枝不用去重，树层才需要去重。
		nums[i-1] == nums[i] 这个时候树枝去重，树层去重都会生效，很明显不符合要求。
		加上 used[i-1]==false;才能完成树枝不用去重，树层才需要去重。
		树枝：used[i-1]=true，used[i]=true;
		树层：used[i-1]=false，used[i]=true;
		不同就看链接中的视频
		*/
		vector<int>subsetsWithDup_signal;
		vector<vector<int>>subsetsWithDup_ret;
		void subsetsWithDup_tracking(vector<int>& nums, vector<bool>&used, int startIndex)
		{
			subsetsWithDup_ret.push_back(subsetsWithDup_signal);
			for (size_t i = startIndex; i < nums.size(); i++)
			{
				if (i > 0 && nums[i - 1] == nums[i] && used[i - 1] == false)//used[i-1]==true;在本题也行，就是性能差点
					continue;
				subsetsWithDup_signal.push_back(nums[i]);
				used[i] = true;
				subsetsWithDup_tracking(nums, used, i + 1);//!!!要说的我回溯了一下上面的所有的题目都是i+1，没有一个startIndex+1
				used[i] = false;
				subsetsWithDup_signal.pop_back();
			}
			return;
		}
		vector<vector<int>> subsetsWithDup(vector<int>& nums) {
			vector<bool>used(nums.size(), false);
			sort(nums.begin(), nums.end());
			subsetsWithDup_tracking(nums, used, 0);
			return subsetsWithDup_ret;
		}

		/*
		491.递增子序列
		参考：
		https://www.programmercarl.com/0491.%E9%80%92%E5%A2%9E%E5%AD%90%E5%BA%8F%E5%88%97.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		本题可以用数组来实现去重，但是这里为了学习不同的方法，选择用set去重。但以后就只保留一种方法即可。数组的性能更好，并且和上面的题目更统一。
		去重要不要回溯？
		如果要保证同一个父节点下的树层是不重复的（不是整个树的同一层并且挨边的两个元素重复），树枝是可以重复的。就要在for中去定义变量，并且不回溯。
		否则就得回溯。
		参考：491.递增子序列
		参考：
		https://mp.weixin.qq.com/s?__biz=MzUxNjY5NTYxNA==&mid=2247485532&idx=1&sn=d341f09725185a6a21e5241e44bd955b&scene=21#wechat_redirect
		*/
		vector<vector<int>> findSubsequences_ret;
		vector<int> findSubsequences_signal;
		void findSubsequences_tracking(vector<int>& nums, int startIndex)
		{
			if (findSubsequences_signal.size() > 1)
				findSubsequences_ret.push_back(findSubsequences_signal);
			unordered_set<int> findSubsequences_set;//!!一定要放在for中，因为我们要做的就是避免树层的重复，而树枝的重复这个可以重复。
			for (size_t i = startIndex; i < nums.size(); i++)
			{
				if (!findSubsequences_signal.empty() && findSubsequences_signal.back() > nums[i] || findSubsequences_set.find(nums[i]) != findSubsequences_set.end())continue;
				findSubsequences_set.insert(nums[i]);//!这个不用回溯，因为回溯是不能保证一层上的数据不重复，而这里是为了保证整个树，每个结果都得是不重复的。
				findSubsequences_signal.push_back(nums[i]);
				findSubsequences_tracking(nums, i + 1);
				findSubsequences_signal.pop_back();
			}
			return;
		}
		vector<vector<int>> findSubsequences(vector<int>& nums) {
			findSubsequences_tracking(nums, 0);
			return 		findSubsequences_ret;
		}


		/*
		46.全排列
		参考：
		https://www.programmercarl.com/0046.%E5%85%A8%E6%8E%92%E5%88%97.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		used数组用来标记那些元素被用了。之前都是用来去重。
		每次开始的位置都是0，因为他是排列。不是组合，比如12 有12 21 ，组合12 21是一个，
		排列中取了2之后，发现1还没取就要去取了，
		元素取没取，用used数组来判断。
		*/
		vector<int>permute_signal;
		vector<vector<int>>permute_ret;
		void permute_tracking(vector<int>& nums, vector<bool>& used)
		{
			//在叶子节点上取结果
			if (permute_signal.size() == nums.size())
			{
				permute_ret.push_back(permute_signal);
				return;
			}
			//排列要从0开始取。
			for (size_t i = 0; i < nums.size(); i++)
			{
				//如果元素被用了，就跳过
				if (used[i] == true)continue;
				permute_signal.push_back(nums[i]);
				used[i] = true;
				permute_tracking(nums, used);
				used[i] = false;
				permute_signal.pop_back();
			}
			return;
		}
		vector<vector<int>> permute(vector<int>& nums) {
			vector<bool>used(nums.size(), false);
			permute_tracking(nums, used);
			return permute_ret;
		}


		/*
		47.全排列 II
		最重要的就是树层去重，树枝不去重。
		参考：
		https://www.programmercarl.com/0047.%E5%85%A8%E6%8E%92%E5%88%97II.html#%E6%80%BB%E7%BB%93
		*/
		vector<int>permuteUnique_signal;
		vector<vector<int>>permuteUnique_ret;
		void permuteUnique_tracking(vector<int>& nums, vector<bool>& used)
		{
			//在叶子节点上取结果
			if (permuteUnique_signal.size() == nums.size())
			{
				permuteUnique_ret.push_back(permuteUnique_signal);
				return;
			}
			//排列要从0开始取。!并且要“树层”去重
			for (size_t i = 0; i < nums.size(); i++)
			{
				//树层去重
				if (i > 0 && nums[i - 1] == nums[i] && used[i - 1] == false)continue;
				//如果元素被用了，就跳过——树枝去重
				if (used[i] == true)continue;
				permuteUnique_signal.push_back(nums[i]);
				used[i] = true;
				permuteUnique_tracking(nums, used);
				used[i] = false;
				permuteUnique_signal.pop_back();
			}
			return;
		}
		vector<vector<int>> permuteUnique(vector<int>& nums) {
			vector<bool>used(nums.size(), false);
			sort(nums.begin(), nums.end());
			permuteUnique_tracking(nums, used);
			return permuteUnique_ret;
		}


		/*
		51. N皇后
		参考：
		https://www.programmercarl.com/0051.N%E7%9A%87%E5%90%8E.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		和其他题目不同的是，这是一个二维数组的回溯，之前的都是一维数组的回溯。
		用递归来控制每一行，在每层的递归中遍历这一行的不同列
		棋盘的宽度就是for循环的长度，递归的深度就是棋盘的高度，这样就可以套进回溯法的模板里了。
		*/
		bool solveNQueens_isValid(int row, int col, vector<string>& chessboard, int n) {
			//检查列——只用检查到row（当前遍历的行数），不用检查到底
			for (size_t i = 0; i < row; i++)
			{
				if (chessboard[i][col] == 'Q')return false;
			}
			//检查行——这里不用；因为在遍历每一层的时候，只会选for循环（也就是同一行）里的一个元素，所以不用去重了。
			// 检查 135度角是否有皇后-解析应该写错了
			for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
				if (chessboard[i][j] == 'Q') {
					return false;
				}
			}
			// 检查 45度角是否有皇后
			for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
				if (chessboard[i][j] == 'Q') {
					return false;
				}
			}
			return true;
		}

		vector<vector<string>> solveNQueens_ret;

		//n是棋盘的宽度
		//row是当前递归到棋盘的第几行了
		//signalchessboard构造的单个棋盘
		void solveNQueensStracking(int n, int row, vector<string>&signalchessboard)
		{
			if (row == n)
			{
				solveNQueens_ret.push_back(signalchessboard);
				return;
			}
			for (size_t i = 0; i < n; i++)
			{
				//如果当前皇后的位置符合要求的话，就放到
				if (solveNQueens_isValid(row, i, signalchessboard, n))
				{
					signalchessboard[row][i] = 'Q';
					solveNQueensStracking(n, row + 1, signalchessboard);
					signalchessboard[row][i] = '.';
				}
			}
		}

		vector<vector<string>> solveNQueens(int n) {
			//!!这个其实是个二维的数组，所以初始化signalchessboard(n, ('.'));是不对的
			vector<string> signalchessboard(n, std::string(n, '.'));
			solveNQueensStracking(n, 0, signalchessboard);
			return solveNQueens_ret;
		}

		/*
		37. 解数独
		参考：
		https://www.programmercarl.com/0037.%E8%A7%A3%E6%95%B0%E7%8B%AC.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		这套题目和前面的题目的不同是，这个题目是有2维递归，也就是用到了两个for。
		如果结果只有一个，那么返回值的是直接从尾返回到头，并且递归函数带返回值
		因为解数独找到一个符合的条件（就在树的叶子节点上）立刻就返回，相当于找从根节点到叶子节点一条唯一路径，所以需要使用bool返回值
		只有有了返回值，才能对返回值做判断，返回值复合条件了就可以返回，正好返回值的判断就在递归函数下面，接着返回，就能造成上面说的一直放回到头的效果。
		*/

		bool solveSudoku_isValid(int row, int col, char val, vector<vector<char>>& board)
		{
			for (int i = 0; i < 9; i++) { // 判断行里是否重复
				if (board[row][i] == val) {
					return false;
				}
			}
			for (int j = 0; j < 9; j++) { // 判断列里是否重复
				if (board[j][col] == val) {
					return false;
				}
			}
			int startRow = (row / 3) * 3;
			int startCol = (col / 3) * 3;
			for (int i = startRow; i < startRow + 3; i++) { // 判断9方格里是否重复
				for (int j = startCol; j < startCol + 3; j++) {
					if (board[i][j] == val) {
						return false;
					}
				}
			}
			return true;
		}
		bool solveSudoku_tracking(vector<vector<char>>& board)
		{
			for (size_t i = 0; i < board.size(); i++)
			{
				for (size_t l = 0; l < board[0].size(); l++)
				{
					//如果当前棋盘的位置是空的，那就开始放数字
					if (board[i][l] == '.')
					{
						//从1到9依次放放试试。！是小于等于
						for (char val = '1'; val <= '9'; val++)
						{
							//如果这个数字是有效的，就放到棋盘中。
							//既然是有效的，那么开始下一个位置。
							//！！别忘了在递归函数做判断，接返回值。
							//要是下个位置不行，就开始回溯到上层，开始回溯
							bool result = solveSudoku_isValid(i, l, val, board);
							if (result)
							{
								board[i][l] = val;
								if (solveSudoku_tracking(board)) return true; // 如果找到合适一组立刻返回
								board[i][l] = '.';
							}
							//如果这个数不满足要求，那就下一个数试试。
						}
						//如果1-9都不行，那就回溯到上一层，用上一层的另外一个数再试。总归是有一个满足要求的。！其实就是回到上面那行board[i][l] = '.';代码。进行回溯
						return false;
					}
				}
			}
			//遍历到最后了，肯定是满足要求的。不满足要求的，在中间早就返回了很多次了。不会到这
			return true;
		}
		void solveSudoku(vector<vector<char>>& board) {
			solveSudoku_tracking(board);
		}


		void test()
		{
			//2.1、确定返回值和参数
			//2.2、确定回溯函数结束条件
			//2.3、确定单层搜索的过程——！！for负责横向遍历，递归负责纵向遍历。

			string s = "112";
			vector<int> nums = { 1,1,2 };
			subsetsWithDup(nums);

			for (auto i : restoreIpAddresses_ret)
			{
				for (auto l : i)
				{
					cout << l << " ";
				}
				cout << endl;
			}
		}
	};
}

//贪心
namespace Greedy {
	class Solution {
	public:
		/*
		455. 分发饼干
		参考：
			https://www.programmercarl.com/0455.%E5%88%86%E5%8F%91%E9%A5%BC%E5%B9%B2.html#%E6%80%9D%E8%B7%AF
		思路：
			贪心思路，从最大的胃口开始喂，直到喂完。
			这个一定是建立在元素有序的基础上。
		*/
		int findContentChildren(vector<int>& g, vector<int>& s) {
			sort(g.begin(), g.end());
			sort(s.begin(), s.end());
			//胃口值 g  饼干 s
			int index = s.size() - 1; // 饼干数组的下标
			int result = 0;
			//要注意的就是，这个代码中饼干有时候喂了“同一个胃口”，但是不影响结果
			//比如饼干33 胃口 12 根据这个代码3喂2之后，i不会变化，index--，所以新的饼干又喂了老的个胃口
			//因为排序了，新饼干能喂后面就一定能喂前面。
			for (int i = g.size() - 1; i >= 0; i--) { // 遍历胃口 //如果满足条件，ret++  饼干s就往前挪一个。
				if (index >= 0 && s[index] >= g[i]) { // 遍历饼干
					result++;
					index--;
				}
			}
			return result;
		}


		//我自己写的这个，可以完美避免重复喂问题，但是代码复杂
		int findContentChildren1(vector<int>& g, vector<int>& s) {
			sort(g.begin(), g.end());
			sort(s.begin(), s.end());
			//胃口值 g  饼干 s
			int index = s.size() - 1;
			int ret = 0;

			for (int i = g.size() - 1; i >= 0; )
			{
				while (index >= 0 && s[index] >= g[i])//如果满足条件，ret++  饼干s就往前挪一个。
				{
					ret++;
					index--;
					if (i == 0)
					{
						return ret;
					}
					i--;
					continue;
				}
				i--;
			}
			return ret;
		}


		/*
		376. 摆动序列
		参考：
			https://www.programmercarl.com/0376.%E6%91%86%E5%8A%A8%E5%BA%8F%E5%88%97.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
			它的这个思路就是默认两头各有一个摆动。其实就为了满足当数组长度只有2的时候，统一一下思想
			当长度是2的时候，但是元素相同，最后的结果是1
			这个贪心算法的思路不是从后往前走，而是先计算出局部最优解，然后把这些局部的加一起就是最好的。
		其他：
			这个思路搞的太复杂了，看看有没有其他的办法
		*/
		int wiggleMaxLength(vector<int>& nums) {
			if (nums.size() <= 1) return nums.size();
			int curDiff = 0;//
			int preDiff = 0; //这个默认是0，是因为这个思路中默认会在数组的前面延长一段和数组头部的元素相同的元素。一切都是为了满足下面的判断
			int result = 1;  // 记录峰值个数，序列默认序列最右边有一个峰值
			for (size_t i = 0; i < nums.size() - 1; i++)
			{
				//这段代码，要注意的就是只有preDiff能为0的情况
				curDiff = nums[i + 1] - nums[i];
				if (preDiff >= 0 && curDiff < 0 || preDiff <= 0 && curDiff > 0)
				{
					result++;
					preDiff = curDiff;
				}
			}
			return result;
		}


		/*
		53. 最大子数组和
		参考：
			https://www.programmercarl.com/0053.%E6%9C%80%E5%A4%A7%E5%AD%90%E5%BA%8F%E5%92%8C.html#%E6%80%9D%E8%B7%AF
		思路：
			要注意的就是，只有当连续和小于0的时候，cout才要赋值0.
			因为只有当“和小于0了”，最后的数的相加是削减作用。
			所以这个时候，就要把这一段连续数组抛掉了。
			也就是累加和cout=0；
		*/
		int maxSubArray(vector<int>& nums)
		{
			int ret = INT32_MIN;//因为有可能最后的结果有多小不知道，弄个这个最好
			int cout = 0;

			for (size_t i = 0; i < nums.size(); i++)
			{
				cout += nums[i];
				if (cout > ret)
					ret = cout;
				if (cout < 0)
					cout = 0;
			}
			return ret;
		}


		/*
		122. 买卖股票的最佳时机 II
		参考：
			https://www.programmercarl.com/0122.%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E7%9A%84%E6%9C%80%E4%BD%B3%E6%97%B6%E6%9C%BAII.html#%E6%80%9D%E8%B7%AF
		思路：
			局部最优接，然后把这个局部都加一起，得到最后的。
		其他：
			之前做过。搜索函数名maxProfit2_1
		*/
		int maxProfit2_2(vector<int>& prices) {
			int ret = 0;
			for (size_t i = 0; i < prices.size() - 1; i++)
			{
				//只要是每天的收益大于0（局部最优），就加上
				ret += max(prices[i + 1] - prices[i], 0);
			}
			return ret;
		}

		/*
		55. 跳跃游戏
		参考：
			https://www.programmercarl.com/0055.%E8%B7%B3%E8%B7%83%E6%B8%B8%E6%88%8F.html#%E6%80%9D%E8%B7%AF
		思路：
			先算出每走一步走，算出覆盖范围有多大，然后不断的往下走，然后不断更新更大的范围（局部最优），
			如果嘴个范围大于等于了这个数组的长度，说明符合条件。（全局最优解）
		*/
		bool canJump(vector<int>& nums) {
			if (nums.size() == 1) return true; // 只有一个元素，就是能达到，即使元素是0，因为一个元素它本身就是尾巴
			int cover = nums[0];//数组最小长度为1，不会出现错误。注意cover代表的是下表，便于理解。
			// 注意这里是小于等于cover 本质就是只有小于等于才能让下标走到cover代表的位置，要不然【123】过不去，
			for (int i = 0; i <= cover; i++)
			{
				cover = max(cover, i + nums[i]);
				if (cover >= nums.size() - 1)//-1是因为cover代表的是下标
					return true;
			}
			return false;
		}

		/*
		45. 跳跃游戏 II
		参考：
			https://www.programmercarl.com/0045.%E8%B7%B3%E8%B7%83%E6%B8%B8%E6%88%8FII.html#%E6%80%9D%E8%B7%AF
		思路：
			这个思路和我想的差不多，遍历一个数，先确定一个范围，然后记录这其中最大的范围。（局部最优解）
			然后判断这个最大范围有没有超过这个数组，超过的话，就走新的一步，然后结束判断。
			没有超的话，就往后一直往后走。看看有没有合适的范围能超过数组长度的。如果一直没有，走到旧范围的最后，那么开始新的范围，也就是步数加1。
			一直这样重复，直到结束。
			每一步都是走的最大的范围，把这些最大的范围结合起来就是最好的结果（选择每一阶段的局部最优，从而达到全局最优）
			这个题目明确说明，一定能走到最后的。
		其他：
			比代码随想的效率高，可以达到8ms
		*/
		int jump(vector<int>& nums) {
			if (nums.size() == 1) return 0;//别忘了当长度为1的时候
			int step = 0;//走的步数
			int currCover = 0;//当前的最大范围
			int nextCover = 0;//下一步能走的最大范围
			for (int i = 0; i < nums.size(); i++)
			{
				nextCover = max(nextCover, nums[i] + i);//获取currCover当前的最大范围中的能得到的最大范围
				if (nextCover >= nums.size() - 1)//判断这个最大范围有没有超过这个数组，超过的话，就走新的一步，然后结束判断。
				{
					step++;
					break;
				}
				//没有超的话，就往后一直往后走。
				if (i == currCover)//如果一直没有，走到旧范围的最后，那么开始新的范围，也就是步数加1。
				{
					currCover = nextCover;
					step++;
				}
			}
			return step;
		}

		/*
		1005.K次取反后最大化的数组和
		参考：
			https://www.programmercarl.com/1005.K%E6%AC%A1%E5%8F%96%E5%8F%8D%E5%90%8E%E6%9C%80%E5%A4%A7%E5%8C%96%E7%9A%84%E6%95%B0%E7%BB%84%E5%92%8C.html#%E6%80%9D%E8%B7%AF
			和他的思路差不多，。我这个更好理解
		思路：
			先排序，然后让小的在前面（sort默认就是这样），然后翻转那些负数（局部最优解）
			如果负数不够翻转的，再次排序，找到最小的数，翻转，知道结束
			翻转的这些最小的，自然得到的和就最大的（选择每一阶段的局部最优，从而达到全局最优）
		*/
		int largestSumAfterKNegations(vector<int>& nums, int k) {
			int ret = 0;
			sort(nums.begin(), nums.end());
			size_t i = 0;
			for (i; i < k && i < nums.size() && nums[i] < 0; i++)//小于0并且翻转次数小于k的全部翻转
			{
				nums[i] = 0 - nums[i];
			}
			//这时候数组中已经是全是非负数了，这个时候在排序一下，如果没有翻转k次，就翻转最小的拿一个数
			//这个时候就翻转这一个元素就行
			sort(nums.begin(), nums.end());
			for (int l = 0; l < k - i; l++)
			{
				nums[0] = 0 - nums[0];
			}
			for (int a : nums)ret += a;
			return ret;
		}

		/*
		134. 加油站
		参考：
			https://www.programmercarl.com/0134.%E5%8A%A0%E6%B2%B9%E7%AB%99.html#%E6%80%9D%E8%B7%AF
		思路：
			先计算出每一个消耗的油量，然后累加这些油量，得到区间油耗，如果区间油耗是负数，说明从累加开始开始到结束的这部分都不行。
			但是说不定后面的就可能可以，所以就得开始新的起点，区间油耗归零，从新计算。(局部最优解)
			一直重复上述过程，直到遍历数组结束。（选择每一阶段的局部最优，从而达到全局最优）
			如果最后的总油耗和是大于0的，说明有解，这个接就是最新的起点下标。
			否则就是没有解，返回-1
		*/
		int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
			int secSum = 0;//区间油耗
			int allSum = 0;//总的油耗
			int step = 0;//起步的下标
			for (size_t i = 0; i < gas.size(); i++)
			{
				secSum += (gas[i] - cost[i]);
				allSum += (gas[i] - cost[i]);
				if (secSum < 0)//如区间油耗小于0，则说明从累加开始开始到结束的这部分都不行，就得开始新的起点。
				{
					secSum = 0;
					step = i + 1;
				}
			}
			if (allSum < 0) return -1;//总的油耗不行，啥都不用管了，油的总量就不够，从哪开始也白搭。
			return step;
		}


		/*
		135. 分发糖果
		参考：
			https://www.programmercarl.com/0135.%E5%88%86%E5%8F%91%E7%B3%96%E6%9E%9C.html
		思路：
			这种需要两边比较的题目，统一的做法都是先比较左边，然后再比较右边。
			首先，从左向右开始比较，如果右边大于左边，糖果在左边的基础上加一。
			然后，从右向左开始比较，如果左边大于右边，糖果在右边的基础上加一；
			（每次只加一个，保证了每次都是局部最优）
			最后，取这次两次分发糖果的最大值最为最终的结果（这样做保证糖果是即大于左边也大于右边）。
			（把所有的局部最优解加到一块，得到了全局最优解）
			然后计算所有糖果数量。
		*/
		int candy(vector<int>& ratings) {
			int ret = 0;
			vector<int> candyNums(ratings.size(), 1);//每个小孩手里的糖果数量，默认是1个，方便处理。
			for (size_t i = 1; i < ratings.size(); i++)//从左向右开始比较
			{
				if (ratings[i] > ratings[i - 1])//如果右边大于左边
				{
					candyNums[i] = candyNums[i - 1] + 1;//糖果在左边的基础上加一。
				}
			}
			//注意这个i会有《0的时候，size_t类型不行
			for (size_t i = ratings.size() - 2; i >= 0; i--)//从右向左开始比较
			{
				if (ratings[i] > ratings[i + 1])//如果左边大于右边
				{
					candyNums[i] = max(candyNums[i], candyNums[i + 1] + 1); //糖果在右边的基础上加一,取这次两次分发糖果的最大值最为最终的结果
				}
			}
			for (int a : candyNums) ret += a;
			return ret;
		}

		/*
		860. 柠檬水找零
		参考：
			https://leetcode.cn/problems/lemonade-change/description/
		思路：
			首先，我个人感觉这个贪心不明显；
			记录收到不同钱的数量，20的不用加，因为20不会找出去。
			找出去的钱只有5、10两种。
			优先找出10块的(局部优先解)，5块的最好用能不出去就不出去。
			最后能找完，就满足，否则就不满足（全局最优解）
		*/
		bool lemonadeChange(vector<int>& bills) {
			int five = 0, ten = 0, twenty = 0;
			for (size_t i = 0; i < bills.size(); i++)
			{
				if (bills[i] == 5) {
					five++;
				}
				else if (bills[i] == 10) {//
					ten++;
					five--;
					if (five < 0) return false;
				}
				else if (bills[i] == 20) {//收到了20，优先找出10，不够了再去找出5
					twenty++;
					if (ten > 0) {
						ten--;
						five--;
						if (five < 0) return false;
					}
					else {
						five--;
						five--;
						five--;
						if (five < 0) return false;
					}
				}
			}
			return true;
		}

		/*
		406. 根据身高重建队列
		参考：
			https://www.programmercarl.com/0406.%E6%A0%B9%E6%8D%AE%E8%BA%AB%E9%AB%98%E9%87%8D%E5%BB%BA%E9%98%9F%E5%88%97.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		题目说明：
			people[i] = [hi, ki] h是它的身高，k是比他高的数量。
			最后每个people都有大于等于k个的元素
		重点：
			对我而言，他其实是可以细化为4个维度的，所以选择哪个维度很重要，要不然就一个个的去试，到时候效率会很低。所以还是记住吧。
			很明显这是两个维度。遇到两个维度就一个一个维度单独去计算。这个题目也是不例外。
			维度有四：
			分别按照身高和k的大小组合出四种情况。但是最后符合条件的只有一个，（我测试了三个，最后一种情况每次，我觉得浪费时间）
			1、按照身高从大到小排序，身高相同，按照k从小到大。这是是最合适的。
			按照身高从大到小排序是因为：后来的排序是：
				先从头到尾遍历这些元素，然后根据元素中的k来决定插入的位置；
				从大到小的顺序保证了那些小的元素如果插到了大元素的前面，大元素也能满足条件。
			2、k从小到大是因为满足题意。
		思路：
			首先对二维数组排序。
			然后遍历这个数组。
			遍历的时候按照元素中的k作为新的位置，插入到结果数组中。
			最后返回这个数组
			用vec性能差点，因为用的是insetapi所以不能对vec预设大小，所以会出现vec扩容，导致性能下降。
			用list性能好点，代码稍微复杂点
		*/
		static bool cmp(vector<int>&a, vector<int>&b)
		{
			//比较身高，身高大的在前面
			if (a[0] > b[0]) return true;
			else if (a[0] < b[0])
				return false;
			//如果身高相等，k小的在前面
			if (a[0] = b[0])return a[1] < b[1];
			return 1;//为了让力扣的编译器过去
		}
		vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
			sort(people.begin(), people.end(), cmp);
			vector<vector<int>> ret;
			for (size_t i = 0; i < people.size(); i++)
			{
				ret.insert(ret.begin() + people[i][1], people[i]);
			}
			return ret;
		}


		/*
		452. 用最少数量的箭引爆气球
		思路：
			首先，对数组排序，按照每个元素的左边的值，从小到达排序。（怎排序都可以）
			然后，从第一个元素开始，比较上个元素的右值和当前元素的左值；
			如果，上个元素的右值小于当前元素的左值，说明两者不接触。所以就需要新的弓箭。
			否则，两者是接触的。
				这时候，需要更新当前元素的右值，是为了下次的对比。具体看图就明白了。
			直到，遍历结束。
			返回，弓箭的数量。
			!!注意； 起始数量是1。下面开始遍历的时候，第一次遇到边界不相邻，两只🗡才能射完。
		参考：
			https://www.programmercarl.com/0452.%E7%94%A8%E6%9C%80%E5%B0%91%E6%95%B0%E9%87%8F%E7%9A%84%E7%AE%AD%E5%BC%95%E7%88%86%E6%B0%94%E7%90%83.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
			下面贪心命名空间中，也写了一遍
		*/
		static bool findMinArrowShots_cmp(vector<int>&a, vector<int>&b)
		{
			return a[0] < b[0];
		}
		int findMinArrowShots(vector<vector<int>>& points) {
			if (points.empty())return 0;
			sort(points.begin(), points.end(), findMinArrowShots_cmp);
			int ret = 1;//!! 起始数量是1。下面开始遍历的时候，第一次遇到边界不相邻，两只🗡才能射完。
			for (size_t i = 1; i < points.size(); i++)
			{
				if (points[i][0] > points[i - 1][1])
				{
					ret++;
				}
				else
				{
					points[i][1] = min(points[i][1], points[i - 1][1]);
				}
			}
			return ret;
		}


		/*
		435. 无重叠区间
		参考：
			https://www.programmercarl.com/0435.%E6%97%A0%E9%87%8D%E5%8F%A0%E5%8C%BA%E9%97%B4.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			这个题目和452. 用最少数量的箭引爆气球的思路非常的相似。
			这个题目要求计算出删除最少重叠区间，变得不重叠。其实就是让我们求这个区间里面重叠了多少个区间。
			怎么让空间更好的重叠，方便处理呢？那就是——排序。从小到大或者是从大到小排序都行。
			首先，对数组进行排序，按照左区间从小到大的顺序排列。
			然后，遍历这个数组，如果当前的元素的左区间“小于”上个元素的右区间，说明两者重合，那么结果++
			并且，要更新当前元素右边界的值，为当前和上个元素有边界值的最小值；这么做是为了准备的判断出下个元素是不是也有重叠
			最后，直到遍历结束，返回最后的结果。
		*/
		static bool eraseOverlapIntervals_cmp(vector<int>& a, vector<int>& b)
		{
			return a[0] < b[0];
		}
		int eraseOverlapIntervals(vector<vector<int>>& intervals) {
			sort(intervals.begin(), intervals.end(), eraseOverlapIntervals_cmp);
			int ret = 0;

			for (size_t i = 1; i < intervals.size(); i++)
			{
				//如果当前的元素的左区间“小于”上个元素的右区间，说明两者重合，那么结果++
				if (intervals[i][0] < intervals[i - 1][1])
				{
					ret++;
					intervals[i][1] = min(intervals[i][1], intervals[i - 1][1]);
				}
			}
			return ret;
		}

		/*
		763. 划分字母区间
		题目解释：
			 划分字符，让这个区间的字符只出现在这个区间，不出现在其他的区间。
			 如果区间里包含了a，那么完后遍历的时候，就得把所有的a全部拿进来。
			 最后，返回截取的各个区间长度。
		参考：
			https://www.programmercarl.com/0763.%E5%88%92%E5%88%86%E5%AD%97%E6%AF%8D%E5%8C%BA%E9%97%B4.html
		思路：
			 如果区间里包含了a，那么完后遍历的时候，就得把所有的a全部拿进来。
			 如果中间遇到了其他的字符，然后就得把这个字符也得放进去。
			 结束的条件就是一直往后遍历，直到遍历到了之前纳入的那些字符，他们中的最靠后的位置。
			首先，先确定所有字符最后出现的位置。
			然后，开始遍历字符，不断的更新字符最后的位置下标。
			直到，遍历到了最大下标的位置，记录一下区间长度。
			然后，更新新的区间开始位置。开始新的遍历，直到结束。
		*/
		vector<int> partitionLabels(string s) {
			int hashbuf[26];
			for (size_t i = 0; i < s.size(); i++)
				hashbuf[s[i] - 'a'] = i;//越往后，下标越大，不用max函数
			vector<int> ret;
			int begin = 0, maxI = 0;
			for (size_t i = 0; i < s.size(); i++)
			{
				maxI = max(maxI, hashbuf[s[i] - 'a']);//不断的更新字符最后的位置下标。
				if (maxI == i)//遍历到了最大下标的位置，记录一下区间长度。
				{
					ret.push_back(maxI - begin + 1);
					begin = maxI + 1;//新的区间位置就是最大位置+1
				}
			}
			return ret;
		}

		/*
		56. 合并区间
		参考：
			https://www.programmercarl.com/0056.%E5%90%88%E5%B9%B6%E5%8C%BA%E9%97%B4.html#%E5%85%B6%E4%BB%96%E8%AF%AD%E8%A8%80%E7%89%88%E6%9C%AC
			和他的思路一样的，但是代码不精简。！！！！
		思路：
			和上面的思路很是接近。
			首先，对数组排序。方便后续处理
			然后，遍历数组，先把第一个区间，放到结果中。
			然后，如果当前的元素的右值“大于等于”下个元素的左值，就说明两个区间和重叠的。
			然后，既然是重叠的，新结果中的区间右值用和下个区间元素的右值 被赋值 下个区间的右值和当前结果右值的最大值。
			如果，区间不重叠，那就把这个区间放到结果中。
				注意，我是当前元素和下个元素比较，当不重叠的时候，要添加下个元素的区间ret.push_back(intervals[i+1]);
			然后，接着遍历，如果重合就更新区间的右值。
			直到结束，返回结果。

		*/
		vector<vector<int>> merge(vector<vector<int>>& intervals) {
			if (intervals.size() == 1)return intervals;
			sort(intervals.begin(), intervals.end(), [](vector<int>&a, vector<int>&b)->bool {
				return a[0] < b[0];
			});
			vector<vector<int>> ret;
			ret.push_back(intervals[0]);
			for (int i = 0; i < intervals.size() - 1; i++)
			{
				//如果当前的元素的右值“大于等于”下个元素的左值，就说明两个区间和重叠的。
				if (intervals[i][1] >= intervals[i + 1][0])
				{
					ret.back()[1] = max(ret.back()[1], intervals[i + 1][1]);//既然是重叠的，新结果中的区间右值用和下个区间元素的右值 被赋值 下个区间的右值和当前结果右值的最大值。
					intervals[i + 1][1] = max(ret.back()[1], intervals[i + 1][1]);//【1 10】 【5 6】 【8 9】 没有这个max就出问题
				}
				else
				{
					ret.push_back(intervals[i + 1]);
				}
			}
			return ret;
		}
		/*
		738. 单调递增的数字
		参考：
			https://www.programmercarl.com/0738.%E5%8D%95%E8%B0%83%E9%80%92%E5%A2%9E%E7%9A%84%E6%95%B0%E5%AD%97.html#%E6%80%9D%E8%B7%AF
		思路：
			首先，把整形变成字符串，这样方便对单个数子做处理。
			然后，定义一个标志，记录这个数字从哪开始变九。
			然后，倒着遍历，从前往后遍历的话，不行。
			然后，前一个数子一定要小于后面的数字。
			然后，记录这个后面数字的下标，它后期是要变9的。
			整个核心思路，就是先让前一个数字要小于后面的数字，然后后面的数字变成9.
		*/
		int monotoneIncreasingDigits(int n) {
			string str = to_string(n);
			int flag = str.size(); //这样定义是为了当不执行下面的遍历的时候，不会造成数字变化。

			for (size_t i = str.size() - 1; i > 0; i--)
			{
				if (str[i - 1] > str[i])//后面数字大于前面数字,就让前一个数子一定要小于后面的数字。
				{
					//str[i - 1] = str[i];也白搭
					//str[i - 1] = str[i] - 1; 【10】 【332】都有问题
					str[i - 1] --;//!这个才对。这样能保证每次减少的数是最少的，从而保证了最后的结果是最大的
					flag = i;// 记录这个后面数字的下标，它后期是要变9的
				}
			}
			for (size_t i = flag; i < str.size(); i++)
			{
				str[i] = '9';//把要变成9的，都变成9
			}
			return std::atoi(str.c_str());
		}

		/*
		968. 监控二叉树
		参考：
			https://www.programmercarl.com/0968.%E7%9B%91%E6%8E%A7%E4%BA%8C%E5%8F%89%E6%A0%91.html#%E6%80%9D%E8%B7%AF
		这个贪心思想的不是很明确，所一放到二叉树的命名空间中。
		int minCameraCover(TreeNode* root) {

	}
		*/

		void test()
		{
			vector<int> a{ 1,2,3,4,5 };
			vector<int> b{ 3,4,5,1,2 };
			cout << monotoneIncreasingDigits(10);
		}
	};
}

//动态规划
namespace DynamicPlanning
{
	class Solution {
	public:

		/*
			动态规划的思路
			1、确定dp数组（dp table）以及下标的含义
			2、确定递推公式
			3、dp数组如何初始化
			4、确定遍历顺序
			5、举例推导dp数组，如果有问题的打印出来
		*/

		/*
		509. 斐波那契数
		参考：
			https://www.programmercarl.com/0509.%E6%96%90%E6%B3%A2%E9%82%A3%E5%A5%91%E6%95%B0.html#%E6%80%BB%E7%BB%93
		思路：
			这个题目简单，但是用来套动态规划的思路，是比较好理解的。
		*/
		int fib(int n) {
			if (n <= 1)return n;
			int fb[3] = { 0 };
			fb[0] = 0;
			fb[1] = 1;
			for (size_t i = 2; i <= n; i++)
			{
				int sum = fb[0] + fb[1];
				fb[0] = fb[1];
				fb[1] = sum;
			}
			return fb[1];
		}

		/*
		70. 爬楼梯
		参考：
			https://www.programmercarl.com/0070.%E7%88%AC%E6%A5%BC%E6%A2%AF.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			题目中说明了，每次只能跨1阶或者2阶楼梯。
			所以跨到这阶楼梯的方式就可以通过前面两阶楼梯确定下来。（这个要是不明白，看下图就明白）
			其中第i-1个台阶的本身的到达方法有dp[i-1]种
			其中第i-2个台阶的本身的到达方法有dp[i-2]种
			所以这个思路，很满足“动态规划”的思路，所以用动态规划是最合适的。
		*/
		int climbStairs(int n) {
			if (n <= 3)return n;//根据图来看，前3阶台阶上去的方法是可以直接返回n
			//1、确定dp数组（dp table）以及下标的含义——到第i个台阶的本身的到达方法有dp[i]种方法
			//2、确定递推公式 dp[i]=dp[i-1]+dp[i-2];
			int fb[4] = { 0 };
			//3、dp数组如何初始化 我这里保证要和第一步是相同的思路；
			fb[0] = 0;
			fb[1] = 1;
			fb[2] = 2;
			fb[3] = 3;
			//4、确定遍历顺序——正序遍历，因为后面的结果是依赖于前面的。
			for (size_t i = 4; i <= n; i++)
			{
				int sum = fb[2] + fb[3];
				fb[2] = fb[3];
				fb[3] = sum;
			}
			return fb[3];
		}

		/*
		746. 使用最小花费爬楼梯
		题目：
			cost[i] 代表从i阶楼梯往上上所消耗的费用
			并且走出数组才算是结束了，而不是到到数组末尾
		参考：
			https://www.programmercarl.com/0746.%E4%BD%BF%E7%94%A8%E6%9C%80%E5%B0%8F%E8%8A%B1%E8%B4%B9%E7%88%AC%E6%A5%BC%E6%A2%AF.html
		思路：
			按照动态规划5步来走。
			1、dp数组的含义：代表到第i个台阶，最小花费是dp[i]！！
			2、确定dp公式：dp[i]=min(dp[i-1]+cost[i-1],dp[i-2]+cost[i-2]);
			3、初始化：根据题目来看，当你到了0或1是不花费的，只有从0或1出发往后走才是要花钱的。
				dp数组的初始化，经过思考只需要初始化dp[0]dp[1]，从题目看，可以知道它俩都是0
			4、确定遍历顺序：后面的dp需要前面的dp来确定，所以是正序
			5、打印dp数组
		*/
		int minCostClimbingStairs(vector<int>& cost) {
			//2、确定dp公式.
			int dp[3] = { 0 };
			//4、确定遍历顺序!!!为什么“<=”？因为dp数组的含义：代表到第i个台阶，最小花费是dp[i]。i不到n的话，没有办法计算dp[n]的花费。
			for (size_t i = 2; i <= cost.size(); i++)
			{
				dp[2] = min(dp[1] + cost[i - 1], dp[0] + cost[i - 2]);
				dp[0] = dp[1];
				dp[1] = dp[2];
			}
			return dp[2];
		}



		/*
		62. 不同路径
		其他：
			dp数组只初始化左上角行不行，不行的。这样的话，用dp公式来算，复杂，不如直接初始化。
		参考：
			https://www.programmercarl.com/0062.%E4%B8%8D%E5%90%8C%E8%B7%AF%E5%BE%84.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			1、确定dp含义：dp[i][l] 到il有多少种不同的路径
			2、确定dp公式：dp[i][l] = dp[i-1][l]+dp[i][l-1];
			3、初始化dp：第一行第一列路径都只有一种
			4、确定遍历：从左到右，从上往下。（题目要求只能从左往右，从上往下）
		*/
		int uniquePaths(int m, int n) {
			vector<vector<int>> dp(m, vector<int>(n, 0));
			for (size_t i = 0; i < m; i++) dp[i][0] = 1;//到这些边界的位置，路径只有1种。
			for (size_t i = 0; i < n; i++) dp[0][i] = 1;

			for (size_t i = 1; i < m; i++)
			{
				for (size_t l = 1; l < n; l++)
				{
					dp[i][l] = dp[i - 1][l] + dp[i][l - 1];
				}
			}
			return dp[m - 1][n - 1];
		}

		/*
		63. 不同路径 II
		参考：
			https://www.programmercarl.com/0063.%E4%B8%8D%E5%90%8C%E8%B7%AF%E5%BE%84II.html
		思路：
			这个题目和“62. 不同路径”非常相似。所以这里只写了他俩不同的思路；
			1、初始化。62题目中，初始化的时候。第一行或者第一列中如果有障碍的话，后面的就没法到了。所以障碍后面的路径都是0。
			2、遍历。如果路径不在边上，而是在中间的位置。这个时候，就跳过这个dp数组的计算了。其他的位置，正常计算。
		*/
		int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
			vector<vector<int>>dp(obstacleGrid.size(), vector<int>(obstacleGrid[0].size(), 0));
			//如果障碍在起点或者是终点。则直接返回0；————不写这行代码也能过！
			if (obstacleGrid[0][0] == 1 || obstacleGrid[obstacleGrid.size() - 1][obstacleGrid[0].size() - 1])
				return 0;
			//障碍后面的路径都是0。
			for (size_t i = 0; i < obstacleGrid.size() && obstacleGrid[i][0] == 0; i++) dp[i][0] = 1;
			for (size_t i = 0; i < obstacleGrid[0].size() && obstacleGrid[0][i] == 0; i++) dp[0][i] = 1;
			for (size_t i = 1; i < obstacleGrid.size(); i++)
			{
				for (size_t l = 1; l < obstacleGrid[0].size(); l++)
				{
					//如果路径不在边上，而是在中间的位置。这个时候，就跳过这个dp数组的计算了。
					if (obstacleGrid[i][l] == 1)
						continue;
					dp[i][l] = dp[i - 1][l] + dp[i][l - 1];
				}
			}
			return dp[obstacleGrid.size() - 1][obstacleGrid[0].size() - 1];
		}

		/*
		343. 整数拆分
		参考：
			https://www.programmercarl.com/0343.%E6%95%B4%E6%95%B0%E6%8B%86%E5%88%86.html#%E6%80%9D%E8%B7%AF
		思路：
			这个貌似有贪心思路，不知道简单不。这个思路，仔细捋一下，不简单。只有代码简单。
			这次就不写动态规划的五部曲。写一些重点。
			就是对数“拆分”，比如n=3，分成2,1。记录一次值。然后对2再次拆分，分成11，最后就是111，记录一次值。最后从上面拿到最大的值。
		*/
		int integerBreak(int n) {
			vector<int> dp(n + 1);
			//dp[0] dp[1] 没有初始化时因为题目要求拆分最好2个。0和1拆出来的乘积都0。上面定义数组的时候，已经是0了。
			dp[2] = 1;
			/*
			这里的两个for意思是：
			第一层循环，对i进行拆分，最后拿到i拆分的所有结果中最大的一个值。题目是要对n拆分，所以i最多是n。
			第二层循环，要对i拆分的话，从1开始就行，另一个数字自然就是(i-j)；（一个拆分为j，一个拆分为(i-j)）
			第二层循环，要从1开始，因为从0开始，后面计算的结果是0，没有意义。
			dp的计算方法：
				dp[i]代表数字为i的时候，所得到得最大的结果。
				dp[i]=max(dp[i],max(j*(i-j),j*dp[i-j]));
			1、为什么有把dp[i]放到max中，因为dp的最大值可能在中间计算出来。
			2、j*(i-j)这是最直白的计算结果，肯定放进来。
				但是这个有局限，他只能计算两个数相乘的，所以只能保证那些可以通过拆成2个数，来达到最大值的情况。
				比如n=3，1*（3-1），n=4，2*(4-2)。
				比如n=10,最后的结果3*3*4=36.两个字的话，5*5 4*6都不行。这样的话，只有j*(i-j)肯定是不行的。
				所以需要一个记录之前计算结果的东西，那自然就是dp数组。因为他保存的是数字为i的时候的最大结果。
			3、j*dp[i-j]这个就是拆分出来j和剩下的i-j的最大结果dp[i-j]相乘，就有可能得到最大的值。
				然后通过max滤出最大的值。
			*/
			for (int i = 3; i <= n; i++) {
				for (int j = 1; j <= i / 2; j++) {//从1开始是因为，拆分一个
					/*
					用n=3举例子，j的返回有好几个：
					<= i:这样会导致i-j=0(3-3=0)，(i-j)*j这个结果是0，没有意思
					<= i-1:这样会导致出现(i-j)*j,(3-1)*1和(3-2)*2,导致结果重复。】
					<= i/2;这样避免了后面的重复的，以及后面j和i相同的情况。
					*/
					dp[i] = max(dp[i], max(j*(i - j), j*dp[i - j]));
				}
			}
			return dp[n];
		}


		/*
		96. 不同的二叉搜索树
		参考：
			https://www.programmercarl.com/0096.%E4%B8%8D%E5%90%8C%E7%9A%84%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
			我这个和他思路是一致的，但是有些细微差别，他写的不是很明白，我这个比较明白。
		思路：
			整个题目，和动态规划的上面的题目都是差不多，都是思路复杂，代码简单。
			因为题目是二叉搜索树，所以以不同的数字作为根节点，他的形状是不一样的。（如果题目不是二叉搜索树的话，其实也是一样的）
			分析思路：
				子树的“节点”数量决定了他的组合方式。
				0,1个节点一种方式；2个节点，两种方式。3个节点，五种方式。
			以n=3去分析题目。
			1、以1为根结点的时候，左子树有1种（空子树，也是二叉搜索树），右子树有2种(右子树两个节点)
			2、以2为根结点的时候，左子树有1种，右子树有1种
			3、以3为根结点的时候，左子树有2种，右子树有1种（空子树，也是二叉搜索树）
			所以n=3的情况，组成的二叉树就是上面三种加起来。

			用dp数组描述：dp[i]代表“节点”数量是i的时候，有多少种二叉搜索树。
			dp[3]=dp[0]*dp[2]+dp[1]*dp[1]+dp[2]*dp[0] =1*2+1*1+2*1 =5；
			这个计算方法其实就是，左子树的组合方式数量*右子树的组合方式数量。
			而这种组合方式数量是和节点数量有关系的。dp[i]代表“节点”数量是i的时候，有多少种二叉搜索树。
			第一层for循环中的i,代表着总的节点数量。
			左子树节点数量j，左子树的组合方式数量dp[i];
			右子树节点数量(i-j-1)，注意减去根节点的数量，右子树的组合方式数量dp[i-j-1];
			然后相乘就是。一种情况下组合方式。比如左子树节点为0的情况，但是还有为1为2。。的多种情况。
			所以需要把最后的结果都加起来。
			最后:
			dp[i]+=dp[i]*dp[i-j-1];
		*/
		int numTrees(int n) {
			vector<int>dp(n + 1, 0);//n+1是为了保证dp[n]不越界。
			dp[0] = 1;
			dp[1] = 1;
			for (size_t i = 2; i <= n; i++)//第一层for循环中的i,代表着总的节点数量。
			{
				//!!i-1是因为左子树的节点数量，最多也只能是所有节点-1；
				for (size_t j = 0; j <= i - 1; j++)//第一层for循环中的j,代表左子树的节点数量。
				{
					//i - j - 1：总结点数量-左节点数量-根节点数量=右节点数量。
					dp[i] += dp[j] * dp[i - j - 1];//这个计算方法其实就是，左子树的组合方式数量*右子树的组合方式数量。
				}
			}
			return dp[n];
		}


		/*
		纯01背包问题——dp是二维数组
		这个题目，代码随想讲的不好。
		有时间，我录个视频来说明一下。
		具体的关于dp算法确定以及思路都在我的本子上，到时候抄录上去。
		参考：
			https://www.programmercarl.com/%E8%83%8C%E5%8C%85%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%8001%E8%83%8C%E5%8C%85-1.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			两个for遍历顺序可以颠倒。
		*/
		void test_2_wei_bag_problem1() {
			vector<int> weight = { 1, 3, 4 };//物品重量
			vector<int> value = { 15, 20, 30 };//物品价值
			int bagweight = 4; //这个是背包容量最大边界。不是指背包具体容量。

			// 二维数组——先把所有的值初始化0；
			vector<vector<int>> dp(weight.size(), vector<int>(bagweight + 1, 0));

			//这个和下面的一样。下面的好理解
			//for (int j = weight[0]; j <= bagweight; j++) //j是当前背包容量。当j《=最大背包容量。
			//{
			//	dp[0][j] = value[0];
			//}

			// 这个和上面一样。初始化——第一行中，意味着只能放物品1，那么只要当前背包容量>=物品重量，就可以放进去。
			for (size_t i = 0; i <= bagweight; i++)//i是当前背包容量
			{
				if (i >= weight[0])//只要当前背包容量>=物品重量——发现只有>=的时候，代码才有效，那么不如直接从i = weight[0]开始，节省性能。
					dp[0][i] = value[0];
			}

			// weight数组的大小 就是物品个数
			for (int i = 1; i < weight.size(); i++) { // 遍历物品
				for (int j = 0; j <= bagweight; j++) { // 遍历背包容量
					//j是当前背包容量，当前背包容量《当前的物品重量的时候，意味着新的物品放不进去，当前物品价值保持不变。
					if (j < weight[i])
						dp[i][j] = dp[i - 1][j];
					else
						dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
				}
			}

			cout << dp[weight.size() - 1][bagweight] << endl;
		}

		/*
		纯01背包中，dp用1维数组做。
		参考：
			https://www.programmercarl.com/%E8%83%8C%E5%8C%85%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%8001%E8%83%8C%E5%8C%85-2.html#%E6%80%9D%E8%B7%AF
		思路：
			确定dp数组的定义：dp[j]表示：容量为j的背包，所背的物品价值可以最大为dp[j]。

			要注意的就是，遍历物品和容量的顺序不能反过来。
			里面的for遍历，要倒叙遍历。
			关于倒叙的解释：（我没想好）
			二维数组中每一层的数值是由上一层的正上方和左上方数据得出的
			一维数组模拟二维数组，倒序的话可以保证每一层数据也是由上一层正上方和左上方得出的
			如果是正序的话，左上方数据就会被覆盖掉了
		*/
		void test_1_wei_bag_problem() {
			vector<int> weight = { 1, 3, 4 };
			vector<int> value = { 15, 20, 30 };
			int bagWeight = 4;

			// 初始化
			vector<int> dp(bagWeight + 1, 0);
			for (int i = 0; i < weight.size(); i++) { // 遍历物品
				//bagWeight当前“剩余”背包容量，当剩余的容量》=当前物品的重量的时候，可以往包里放。每次新的循环就对背包容量一点点减下去。视频没有对这一块讲解。
				for (int j = bagWeight; j >= weight[i]; j--) { // 遍历背包容量——倒叙遍历
					//dp[j]而不是dp[i]是因为dp数组的含义，dp[x]中x代表的是容量，自然是由j这个代表容量的来代替
					//weight[i]是代表的某一个物品重量，value[i]某一个物品的价值。都是说明某一个物品，所以用i。
					dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
				}
			}
			cout << dp[bagWeight] << endl;
		}


		/*
		416. 分割等和子集
		参考：
			https://www.programmercarl.com/0416.%E5%88%86%E5%89%B2%E7%AD%89%E5%92%8C%E5%AD%90%E9%9B%86.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			把这个问题，转换成01背包问题。
			就是把这些数放进背包中，每个数只能放一次。背包的价值就是这些元素的和。
			就是相当于有个有个sum/2容量的背包，数组的中元素加起来这个是否为sum/2。
			这么做能判读的原因是因为：
			题目中是要分成两份子集，并且两个子集相等才行。
			所以其中一个子集只要他的和为总和的一半，那么另外一半自然也是这个数据，
			两个子集自然就相等。


			定义dp数组：dp[i]：i就是“容量”（i代表的就是元素和的最大值，不能超过他，所以有点像容量的概念）为i的时候，能存的最大的元素和是多少。
				比如dp[7]在这个“nums = [1,5,11,5]”中，dp[7]=6; 7是dp能接受的不大于7最大和，而在这个题目中，最大只能是6
				所以最后判断的时候，
				如果dp[sum/2]==sum/2;则说明满足条件。（也就是当让dp的最大值为sum/2的时候，他的dp[sum/2]的值也确实为sum/2，这是符合条件的）
			初始化dp数组：dp[0] =0;容量是0.存的是数也是0;
			确定dp数组等式：dp[i]=max(dp[i],dp[i-m[j]]+value[i]);
				这个地方不一样——他的重量和价值相同。
				所以：dp[i]=max(dp[i],dp[i-sum[j]]+sum[i]);
			确定遍历顺序：根据这个01背包问题的话，第二个for是倒叙遍历。
		*/
		bool canPartition(vector<int>& nums) {
			//vector<int> dp(0, nums.size());这个不对！！！ 根据dp的含义，dp[i]中的i和他的结果有可能是一样的，和nums的大小没关系
			// 题目中说：每个数组中的元素不会超过 100，数组的大小不会超过 200
			// 总和不会大于20000，背包最大只需要其中一半，所以10001大小就可以了
			vector<int> dp(10001, 0);
			int sum = 0;
			for (size_t i = 0; i < nums.size(); i++)
				sum += nums[i];
			if (sum % 2 == 1)//数组的和奇数的时候，他是不满足条件的。不满足题意中的“使得两个子集的元素和相等”
				return false;
			sum = sum / 2;

			for (size_t i = 0; i < nums.size(); i++)//遍历“物品”——实质就是遍历要放到背包的数——在本题目中就是nums[i]
			{
				//j代表剩余的可以加的大小，当剩余可加的大小》=要加上的数，说明可以往dp中加（可以往dp中放）
				for (size_t j = sum; j >= nums[i]; j--)//遍历背包“容量”——实质就是遍历背包的剩余容量——在本体中就是剩余可以加的大小。
				{
					dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
				}
			}
			if (dp[sum] == sum)
				return true;

			return false;
		}


		/*
		1049. 最后一块石头的重量 II
		参考：
			https://www.programmercarl.com/1049.%E6%9C%80%E5%90%8E%E4%B8%80%E5%9D%97%E7%9F%B3%E5%A4%B4%E7%9A%84%E9%87%8D%E9%87%8FII.html
		思路：
			尽量把石头分成重量相等两堆，这样石头相撞下来，剩下的才是最小的的。
			每个石头都是只能拿一次，所以是01背包问题。
			这个题目和“416. 分割等和子集”几乎是一样的。
		*/
		int lastStoneWeightII(vector<int>& stones) {
			//定义dp数组的大小，因为题目中最多30个石头和每个石头重量最大是100.
			//因为我只要取一半，所有只需要1500,为了不让dp[1500]越界，所以只需要长度为1501
			vector<int>dp(0, 1501);
			int sum = 0;
			for (size_t i = 0; i < stones.size(); i++)
				sum += stones[i];
			int target = sum / 2;
			//下面的for的解释参考——416. 分割等和子集
			for (size_t i = 0; i < stones.size(); i++)//遍历物品——本题就是要放的石头
			{
				for (size_t l = target; l >= stones[i]; l--)//遍历背包——dp中还能放多少石头到dp中
				{
					dp[l] = max(dp[l], dp[l - stones[i]] + stones[i]);
				}
			}
			//sum - dp[target]一定>= dp[target]; 因为target是sum/2，他是往下取整的。也就是说明target<=sum/2.target是小于等于所有数据的一半的。
			//因为dp[target]他的值（价值）不会超过target。所以dp[target]不会超过sum/2；
			//所以才有开头的结果
			return sum - dp[target] - dp[target];//剩余的石头的数量
		}


		/*
		494. 目标和
		参考：
			https://www.programmercarl.com/0494.%E7%9B%AE%E6%A0%87%E5%92%8C.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			这个题目，要求的是在给定目标值(S)一定的情况下，有几种方法。
			把计算分为加法、减法一部分。
			在S确定，数组的和确定，的前提下。
			只需要计算出加法或者减法一边的值就行。
			因为和确定，加法一边确定了，减法一边也确定了。
			计算方法：
				假设加法的总和为x，那么减法对应的总和就是sum - x。
				所以我们要求的是 x - (sum - x) = target
				x = (target + sum) / 2
			那么这个题目，就变成“从数组中挑选一些数据，是他们的和为x，每个数只能用一次，有多少种组合方法，多少种方法就是数组得到S有多少种方法”。
			这就是典型的01背包

			1、确定dp含义
			给了我们一个背包，问我们有多少种方式能装满。这个所谓的“装满”就是从数组中挑选一些元素，使和为加法的一边。
			dp[j] 表示：
				填满j（包括j）这么大容积的包，有dp[j]种方法

			dp[j] 表示：
				加法一边为j（包括j），有dp[j]种方法可以加到这个数
			2、确定的dp递推公式
				这里视频说的不好，我感觉很多动态规划题目讲的都不好。
				当“加法一边为1”有dp【1】中方法
				当“加法一边为2”有dp【2】中方法
				当“加法一边为3”有dp【3】中方法，而这个3可以从dp[1]+dp[2]来得到，也就是“加法一边为3”可以分为“加法一边为1”，“加法一边为2”
				所以：dp[j] = dp[j] + dp[j - nums[i]];
				！其实还是说的不明白。
			3、初始化
				dp[0] = 1;
				其实也没说明白，从我的思路看，“加法一边的和=0”，能有几种方法这个真不确定。
				从他的思路看，填满j（包括j）这么大容积的包，有dp[j]种方法。容量是0,填满容量是0的方法，0说的过去，1也说的过去。
				但是最终确定，还是靠试。
			4、遍历顺序

		*/
		int findTargetSumWays(vector<int>& nums, int S) {//S就是最后要得到的值
			int sum = 0;
			for (int i = 0; i < nums.size(); i++) sum += nums[i];
			if (abs(S) > sum) return 0; // 此时没有方案——要求的和S，比nums中这些所有的数得到的极大值极小值都大，肯定是不行的。
			//(S + sum) / 2是计算出加法或者减法一边的值
			if ((S + sum) % 2 == 1) return 0; // 此时没有方案——！！这个不知掉为啥，去掉之后，代码不通过，视频中没有对这个一块有个详细的解释。
			int bagSize = (S + sum) / 2;//加法最大的值就是这个
			vector<int> dp(bagSize + 1, 0);//根据我写的dp数组的含义，dp的下标就是“加法一边的和”，vec的大小自然就是S + sum) / 2+1
			dp[0] = 1;
			for (int i = 0; i < nums.size(); i++) {//遍历物品，其实就是要被组合的数组中各个元素
				for (int j = bagSize; j >= nums[i]; j--) {//遍历背包，其实就是谁做dp的下标，就遍历谁。这里下标就是一边的加法和。让“加法最大的值”和“当前能提供的数值”比较。
					dp[j] = dp[j] + dp[j - nums[i]];
				}
			}
			return dp[bagSize];
		}


		/*
		474. 一和零
		参考：
			https://www.programmercarl.com/0474.%E4%B8%80%E5%92%8C%E9%9B%B6.html
		思路：
			转成01背包问题
			dp[i][j]：最多有i个0和j个1的strs的最大子集的大小为dp[i][j]。
			dp[i][j]：放满容量可以有i个0和j个1的背包的时候，最大子集的尺寸为dp[i][j]。
			有个很关键的问题，为什么dp[][]的值就代表了最大子集的尺寸？
			看dp[i][j] = max(dp[i][j], dp[i - zeroNum][j - oneNum] + 1);，以及除了“494. 目标和”之外的所有题目的dp，
			都是发现，它的值是由“+ 1”这个位置来决定的。
			dp[i - zeroNum][j - oneNum] + 1。这个代码的含义就是去掉一些0，一些1，然后再加上一些0一些1，这个时候尺寸就+1。而这个地方就决定了dp的值的变化，决定了dp的值代表的含义。
		*/
		int findMaxForm(vector<string>& strs, int m, int n) {
			vector<vector<int>>dp(m + 1, vector<int>(n + 1, 0));//初始化二维数组，为了不越界长度+1
			for (auto str : strs)
			{
				int zeroNums = count(str.begin(), str.end(), '0');
				int oneNums = count(str.begin(), str.end(), '1');
				for (int i = m; i >= zeroNums; i--)//01背包问题中，i的初始值都是要放满物品的最大值，于i对比的就是外层for中确定本次要放的物品的数量。
				{
					for (int l = n; l >= oneNums; l--)
					{
						//把代表物品和容量的变量，代入到01的公式中，一般来说，都是一维的dp公式，并且都要根据题目，来做出具体的改变
						dp[i][l] = max(dp[i][l], dp[i - zeroNums][l - oneNums] + 1);
					}
				}
			}
			return dp[m][n];
		}





		/*
		518. 零钱兑换 II
		参考：
			https://www.programmercarl.com/0518.%E9%9B%B6%E9%92%B1%E5%85%91%E6%8D%A2II.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			转换成完全背包最合适。
			每个物品都能用多次，并且是组合。用完全背包最合适。
			1、dp数组定义：
				dp【j】 金币总额为j的时候，有多少种组合。
			2、确定递推公式：
				这个和“494目标和”题目很相似
				dp[j]=dp[j]+dp[i-cost[i]]
			3、dp数组初始化
				dp[0]=1 dp[其他非零下表]=0
			4、确定遍历顺序
				因为是题目要求的是组合，所以是先遍历物品，再遍历背包。
		*/
		int change(int amount, vector<int>& coins) {

			vector<int>dp(amount + 1, 0);
			dp[0] = 1;
			//组合问题，先遍历物品，在遍历背包。
			for (int i = 0; i < coins.size(); i++)//物品——遍历每一种物品
			{
				for (int j = 1; j <= amount; j++)//背包——每一种物品能放的最大数量。
				{
					if (j - coins[i] >= 0)
						dp[j] = dp[j] + dp[j - coins[i]];
				}
			}
			return dp[amount];
		}




		/*
		377. 组合总和 Ⅳ
		参考：
			https://www.programmercarl.com/0377.%E7%BB%84%E5%90%88%E6%80%BB%E5%92%8C%E2%85%A3.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			和上题目非常相似_518. 零钱兑换 II
		*/
		int combinationSum4(vector<int>& nums, int target) {
			vector<int>dp(target + 1, 0);
			dp[0] = 1;
			//排序问题，先遍历背包，再遍历物品。
			//!!!两个for颠倒了顺序，外面的依旧为i 里面的是j。
			//dp的下标依旧是“target”。要注意改变的就变。
			for (int i = 0; i <= target; i++)//背包——每一种物品能放的最大数量。
			{
				for (int j = 0; j < nums.size(); j++)//物品——遍历每一种物品
				{
					//C++测试用例有两个数相加超过int的数据( dp[j] + dp[j - nums[i]])，所以需要在if里加上dp[i] < INT_MAX - dp[i - num]。
					if (i - nums[j] >= 0 && dp[i] < INT_MAX - dp[i - nums[j]])
						dp[i] = dp[i] + dp[i - nums[j]];
				}
			}
			return dp[target];
		}


		/*
		322. 零钱兑换
		参考：
			https://www.programmercarl.com/0322.%E9%9B%B6%E9%92%B1%E5%85%91%E6%8D%A2.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			转换成背包问题：就是背包容量一定，最少能放几种背包来填满背包。
			物品“钱”可以用多次，是完全背包问题;物品“钱”不分先后顺序，所以是组合,先遍历物品，再遍历背包。
			完全背包内for是正序。
			1、是在“确定dp公式上”
				dp[i] 金额为i的时候，dp[i]为所用的“最少”金币数。
				dp[j]=min(dp[j],dp[j-coins[i] + 1])
			2、在初始化dp数组
				因为要求的是最小值，所以dp要初始化intmax，但是当金币总额为0的时候，就是0种兑换方法。可以用题目测出来。
			这两点是这个题目的要注意的地方。
		*/
		int coinChange(vector<int>& coins, int amount) {
			vector<unsigned int>dp(amount + 1, INT_MAX);//因为dp[j - coins[i]] + 1会出现INT_MAX+1，出现越界，所有要定义无符号
			dp[0] = 0;
			for (int i = 0; i < coins.size(); i++)//物品
			{
				//当前物品重量《=背包容量
				for (int j = coins[i]; j <= amount; j++)//背包
				{
					/*
					dp[j]：“j”背包容量；
					dp[j - coins[i]] + 1：dp[背包容量-当前物品重量]+1：拿掉当前物品“j - coins[i]”，然后加上新的物品就是物品数+1；
					*/
					dp[j] = min(dp[j], dp[j - coins[i]] + 1);
				}
			}
			if (dp[amount] == INT_MAX) return -1;
			return dp[amount];
		}


		/*
		279. 完全平方数
		参考：
			https://www.programmercarl.com/0279.%E5%AE%8C%E5%85%A8%E5%B9%B3%E6%96%B9%E6%95%B0.html
		题目说明：
			1 4 9 这种被称为“完全平方数”，这个题目要给一个n，然后这个是由“完全平方数”加起来组成的数。
			求用到的“完全平方数”的最少数量
		思路：
			每个“完全平方数”可以多次使用，完全背包问题。
			不在乎顺序，就是排列。
			转换为背包思路：背包容量是n，“完全平方数”是每个物品的重量。
			问放满背包，“最少”有多少“物品”。
			1、定义dp：dp[j] 当和为j的时候，最少有dp[j]中方法。
			2、初始化：题目描述，“完全平方数”1, 4, 9, 16, ...。题目中没有0.所以=0；
			3、确定dp公式：
		*/
		int numSquares(int n) {
			vector<size_t>dp(n + 1, INT_MAX);//!!!取最小值，1、往往都是INT_MAX来初始化。2、小心dp[i - j * j] + 1越界了，正好越界1
			dp[0] = 0;//题目描述，“完全平方数”1, 4, 9, 16, ...。题目中没有0.所以=0；
			for (size_t i = 0; i <= n; i++)//背包
			{
				//物品-J*J就是具体的要放的物品的重量，！物品要小于等于背包容量！
				for (size_t j = 0; j*j <= i; j++)
				{
					/*
					dp[i]：“i”背包容量；
					dp[i - j * j] + 1：dp[背包容量-当前物品重量]+1：拿掉当前物品“i - j * j”，然后加上新的物品就是物品数+1；
					*/
					dp[i] = min(dp[i - j * j] + 1, dp[i]);
				}
			}
			return dp[n];
		}


		/*
		139.单词拆分
		参考：
			https://www.programmercarl.com/0139.%E5%8D%95%E8%AF%8D%E6%8B%86%E5%88%86.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			转成背包问题：
			此数组中拿到单词放到s中，看最后能不能放满背包。
			背包容量是要拼凑的单词的长度。
			dp[i]含义：当遍历到字符串s到位置i的时候，前面的都可以被“单词”组成
			递推公式：dp[i]很明显是依托于前面的部分。在前面能匹配上的前提下，后面的才有意义。
					if(j-i的区间能匹配，并且下标为j的时候也为true)，这个时候dp[i]=true
					为了方便匹配，用set匹配方便
			确定遍历顺序：对于组成单词而言，单词的顺序不能随意指定，所以就是排列。
			初始化：一开始一定要为true，要不然后面都是false了
		*/
		bool wordBreak(string s, vector<string>& wordDict) {
			vector<bool>dp(s.size() + 1, false);
			unordered_set<string>wordSet(wordDict.begin(), wordDict.end());
			dp[0] = true;
			//转换成背包问题，相当于往s中去放,遍历背包就是遍历s
			for (size_t i = 0; i <= s.size(); i++)//背包
			{
				//物品《=背包容量，这里人就是保持这个规则
				for (size_t j = 0; j < i; j++)//物品
				{
					//在前面能匹配上的前提下，后面的才有意义。
					//!!!截取从j开始，也就是每次从最近的dp[j]=true开始，然后往后截取，直到遍历结束
					string tmp = s.substr(j, i - j);//substr(起始位置，截取的个数)
					if (dp[j] && wordSet.find(tmp) != wordSet.end())//if(j-i的区间能匹配，并且下标为j的时候也为true)
						dp[i] = true;//新的字符串匹配上了，说明dp为true的下表要往后挪到i了
				}
			}
			return dp[s.size()];
		}

		/*
		198.打家劫舍
		题目解析：
			从数组中偷，挨边的不能偷。
		参考：
			https://www.programmercarl.com/0198.%E6%89%93%E5%AE%B6%E5%8A%AB%E8%88%8D.html
		思路：

			乍一想，i能不能偷，只看i-1不就完了，不为什么这么做的原因，是因为要考虑“最大价值”
			279为例。一开始不知道要偷2还是7。所以就要比较2+7和9的大小，谁大要谁，然后i++往后移动。
			说明，当前i房间能不能偷，取决于i-1房间偷了不，以及i-2房间偷了没。
			当前状态和前面状态会有一种依赖关系，那么这种依赖关系都是动规的递推公式。
			所以用“动态规划”

			1、往背包放钱，很明显的是背包，每个钱只能放一次，01背包。
			2、在背包容量一定的情况下，求最大的价值，要用到max函数
			dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
			dp数组含义：dp[j] 偷到“下标为i”的时候最大价值
			递推公式：dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
			初始化：从递推公式来看，要初始化1，2,，但是dp[1]要为 0 1的最大值
		*/
		int rob(vector<int>& nums) {
			if (nums.size() == 0) return 0;
			if (nums.size() == 1) return nums[0];
			vector<int>dp(nums.size(), 0);
			dp[0] = nums[0];
			dp[1] = max(nums[0], nums[1]);//初始化dp[1]，用max别忘了。这里要访问两个元素，小于两个元素，上面要单独处理
			for (size_t i = 2; i < nums.size(); i++)
			{
				dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
			}
			return dp[nums.size() - 1];
		}


		/*
		213.打家劫舍II
		题目解析：
			房间是个圈，挨边的不能偷。
		参考：
			https://www.programmercarl.com/0213.%E6%89%93%E5%AE%B6%E5%8A%AB%E8%88%8DII.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			把这个“圆数组”分解成“线性数组”，然后用“198.打家劫舍”思路解决。
			根据题意知道，头尾不能同时取，所以就分为：有头没尾，无头有尾，无头无尾。
			无头无尾，在前两种情况中都包含了。
		*/
		int robRange(vector<int>& nums, int start, int end)
		{

			vector<int>dp(nums.size(), 0);
			dp[start] = nums[start];
			dp[start + 1] = max(nums[start], nums[start + 1]);//初始化dp[1]，用max别忘了。这里要访问两个元素，小于两个元素，上面要单独处理
			for (size_t i = start + 2; i < end; i++)
			{
				dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
			}
			return dp[end - 1];
		}


		int rob2(vector<int>& nums) {
			if (nums.size() == 0) return 0;
			if (nums.size() == 1) return nums[0];
			if (nums.size() == 2)return  max(nums[0], nums[1]);//这题目。只有两个元素的时候，虽然首尾相连，但能偷一个
			int ret = robRange(nums, 1, nums.size());
			int ret1 = robRange(nums, 0, nums.size() - 1);
			return max(ret, ret1);
		}


		/*
		337.打家劫舍 III
		题目解析：
			换成了“树”结构，还是相邻的不能偷
		参考：
			https://www.programmercarl.com/0337.%E6%89%93%E5%AE%B6%E5%8A%AB%E8%88%8DIII.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			这个题目就是“树+动态规划”；
			用“后序遍历”，是因为解决思路是“从下往上”，得到的返回值让上一层节点用。
			dp含义：dp[0]不偷该点的最大值，dp[1]不偷该点的最大值
			其他思路，看注释
		*/
		struct TreeNode {/*这个题目是树。放在动态规划里*/
			int val;
			TreeNode *left;
			TreeNode *right;
		};

		vector<int> rob3Range(TreeNode* root)
		{
			/*这个不行，假设，当root左存在的时候，右不存在。进入下层递归，右的右造成非法访问。
			if (root->left == nullptr&& root->right == nullptr)
				return{ 0,root->val };*/
			if (root == nullptr)//遍历到叶子节点的下一个节点。也就是不存在的节点，偷不偷都是0；
				return { 0,0 };
			//!后序遍历
			vector<int>dpLeft = rob3Range(root->left);
			vector<int>dpRight = rob3Range(root->right);

			//当前节点没偷，左右孩子有可能偷有可能不偷
			int left = max(dpLeft[0], dpLeft[1]) + max(dpRight[0], dpRight[1]);
			//当前节点偷了，子节点一定不能偷
			int right = root->val + dpLeft[0] + dpRight[0];
			return{ left ,right };
		}
		int rob3(TreeNode* root) {
			if (root == nullptr)
				return 0;
			vector<int> val = rob3Range(root);
			return max(val[0], val[1]);
		}



		/*
		121. 买卖股票的最佳时机1
		参考：
			https://www.programmercarl.com/0122.%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E7%9A%84%E6%9C%80%E4%BD%B3%E6%97%B6%E6%9C%BAII.html#%E6%80%9D%E8%B7%AF
		思路：
			这个题目特点是，只能交易一次。
			贪心思路
			1、始终找最小值
			2、用“当前的价格-最小值”，不断的更新“最小值”右侧更大的利润。
		*/
		int maxProfit1_1(vector<int>& prices) {
			int maxValue = prices[0];
			int minValue = prices[0];
			int result = 0;
			for (size_t i = 0; i < prices.size(); i++)
			{
				if (prices[i] < minValue)
					minValue = prices[i];
				else if (prices[i] - minValue > result)
					result = prices[i] - minValue;
			}
			cout << "利润 " << result << endl;
			return result;
		}


		/*
		121. 买卖股票的最佳时机1
		参考：
			https://www.programmercarl.com/0122.%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E7%9A%84%E6%9C%80%E4%BD%B3%E6%97%B6%E6%9C%BAII.html#%E6%80%9D%E8%B7%AF
		思路：
			这个题目特点是，只能交易一次。
			动态规划思路
			这个题目，用这个思路不值当的，主要为了买卖股票的最佳时机3以及以后的题目，做思想熟悉
			1、dp数组定义：
				他用二维的原因是一维表示不出来，另外他对dp数组的描述，没我这个好。
				dp[i][0] 表示第i天持有股票所得最多现金;dp[i][1]表示第i天不持有股票所得最多现金
				*dp[i][0] 表示第i天持有股票手里最多的“利润”;dp[i][1]表示第i天不持有股票手里最多的“利润”
			2、dp数组递推公式
				dp[i][0] 表示第i天持有股票所得最多利润;
					1、i之前就持有了，手里的利润没变化和dp[i-1][0]一样
					2、i的时候买了，利润就变成-prices[i]
					两种利润去最大的那个。
				dp[i][1]表示第i天不持有股票所得最多“利润”
					1、i之前就卖了，手里的利润没变化和dp[i-1][1]一样
					2、i的时候卖了，利润就变成dp[i-1][0]+prices[i],前天没卖，今天卖了
			3、遍历顺序
				后面的利润，依靠前面的来算，所以从头开始遍历
			4、初始化
				第0天的时候，
				dp[0][0]=-prices[0];//第0天持有股票，就是买了，要花钱，利润就是-prices[0]
				dp[0][1]=0;//第i天不持有股票，没花钱利润=0；

			返回值：
				最后的要返回dp[i][0]，dp[i][1]中较大的那个，但实际上肯定是卖出股票的dp[i][1]大
		*/

		int maxProfit1_2(vector<int>& prices) {
			if (prices.size() == 0) return 0;
			vector<vector<int>>dp(prices.size(), { 0,0 });
			//vector<vector<int>>dp(prices.size(), { 0 });//力扣过不去
			dp[0][0] = -prices[0];
			dp[0][1] = 0;
			for (size_t i = 1; i < prices.size(); i++)
			{
				dp[i][0] = max(dp[i - 1][0], -prices[i]);
				dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
			}
			return dp[prices.size() - 1][1];
		}




		/*
		122.买卖股票的最佳时机II
		参考：
			https://www.programmercarl.com/0122.%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E7%9A%84%E6%9C%80%E4%BD%B3%E6%97%B6%E6%9C%BAII.html#%E6%80%9D%E8%B7%AF
		思路：
			这个题目特点是，每天都能交易。
			动态规划
			这个题目，用这个思路不值当的，主要为了买卖股票的最佳时机3以及以后的题目，做思想熟悉

			2、dp数组递推公式
				dp[i][0] 表示第i天持有股票所得最多利润;
					1、i之前就持有了，手里的利润没变化和dp[i-1][0]一样
					2、i的时候买了，利润就变成-prices[i]（原先的）
					！！“和121. 买卖股票的最佳时机1”相比，唯一的差别在这
					因为可以多次买卖，所以在i买了的时候，可能之前也交易过，
					利润就不是“第一次买的时候的-prices[i]”，那么利润就变成了：
					“之前的利润-买股票的花费”
					dp[i-1][1]-prices[i]
					即使是第一次买，dp[i-1][1]=0,也能满足题意

					两种利润去最大的那个。
				dp[i][1]表示第i天不持有股票所得最多“利润”
					1、i之前就卖了，手里的利润没变化和dp[i-1][1]一样
					2、i的时候卖了，利润就变成dp[i-1][0]+prices[i],前天没卖，今天卖了
		*/
		int maxProfit2_3(vector<int>& prices) {
			if (prices.size() == 0) return 0;
			vector<vector<int>>dp(prices.size(), { 0,0 });
			dp[0][0] = -prices[0];
			dp[0][1] = 0;
			for (size_t i = 1; i < prices.size(); i++)
			{
				dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
				dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
			}
			return dp[prices.size() - 1][1];
		}



		/*
		123.买卖股票的最佳时机III
		参考：
			https://www.programmercarl.com/0123.%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E7%9A%84%E6%9C%80%E4%BD%B3%E6%97%B6%E6%9C%BAIII.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			这个题目特点是“最多交易两次”，可以一次， 可以两次。

			1、确定dp：
				0、没有操作 （其实我们也可以不设置这个状态,前面两个题目都没有设置）
				1、第一次持有股票
				2、第一次不持有股票
				3、第二次持有股票
				4、第二次不持有股票
			2、初始化
				dp[0][0]=0;
				dp[0][1]=-prices[0];
				dp[0][2]=0;//第0天买了再卖，“利润”就是0
				dp[0][3]=-prices[0];//第0天买了再卖，这是第二次了，“利润”就是-prices[0]
				dp[0][4]=0;//第0天买了再卖，“利润”就是0。第二次也是这样
			3、遍历顺序
				第i天持有，有可能i-1就买过了dp[i-1][1]，有可能i天刚买
				dp[i][1] = max(dp[i-1][1],dp[i-1][0]-prices[i]);
				dp[i][1] = max(dp[i-1][1],-prices[i]);//两个都行，建议是这个，逻辑上更好
				dp[i][2] = max(dp[i-1][2],dp[i-1][1]+prices[i]);
				dp[i][3] = max(dp[i-1][3],dp[i-1][2]-prices[i]);
				dp[i][4] = max(dp[i-1][4],dp[i-1][3]+prices[i]);
			4、返回值的确定
				我们肯定会想到，取两次的卖出最大值。但是他说第二次卖出一定是最大值，他说的也不好，我没理解。
		*/
		int maxProfit3(vector<int>& prices) {
			if (prices.size() == 0) return 0;
			vector<vector<int>>dp(prices.size(), { 0,0,0,0,0 });
			dp[0][0] = 0;
			dp[0][1] = -prices[0];
			dp[0][2] = 0;
			dp[0][3] = -prices[0];
			dp[0][4] = 0;
			for (size_t i = 1; i < prices.size(); i++)
			{
				dp[i][1] = max(dp[i - 1][1], -prices[i]);//两个都行，建议是这个，逻辑上更好
				dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + prices[i]);
				dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - prices[i]);
				dp[i][4] = max(dp[i - 1][4], dp[i - 1][3] + prices[i]);
			}
			return dp[prices.size() - 1][4];
		}


		/*
		188. 买卖股票的最佳时机 IV
		参考：
			https://www.programmercarl.com/0188.%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E7%9A%84%E6%9C%80%E4%BD%B3%E6%97%B6%E6%9C%BAIV.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			这个题目特点是交易次数由“k”指定。
			之前都固定的，所以需要一个for来控制交易次数
			1、dp含义
				和以前一样
				2 * l - 2：第l次没有操作 （其实我们也可以不设置这个状态,前面两个题目都没有设置）
				2 * l - 1：第l次持有股票
				2 * l：    第l次不持有股票
			2、递推公式
				和以前一样，只不过用for来控制
			3、dp初始化
				和以前一样，只不过也得初始化。而且要注意，是每次交易的开始利润都是“- -prices[0]”

		*/
		int maxProfit4(int k, vector<int>& prices) {
			if (prices.size() == 0) return 0;
			vector<vector<int>> dp(prices.size(), vector<int>(2 * k + 1, 0));
			for (int j = 1; j <= k; j++) {
				dp[0][2 * j - 1] = -prices[0];
			}
			for (size_t i = 1; i < prices.size(); i++)
			{
				for (size_t l = 1; l <= k; l++)
				{
					dp[i][2 * l - 1] = max(dp[i - 1][2 * l - 1], dp[i - 1][2 * l - 2] - prices[i]);
					dp[i][2 * l] = max(dp[i - 1][2 * l], dp[i - 1][2 * l - 1] + prices[i]);
				}
			}
			return dp[prices.size() - 1][2 * k];
		}

		/*
		309.最佳买卖股票时机含冷冻期
		参考：
			https://www.programmercarl.com/0309.%E6%9C%80%E4%BD%B3%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E6%97%B6%E6%9C%BA%E5%90%AB%E5%86%B7%E5%86%BB%E6%9C%9F.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			dp[i][0]：状态一，持有股票状态（今天买入股票，或者是之前就买入了股票然后没有操作，一直持有）
				dp[i-1][0]:前一天也是保持持有
				dp[i-1][3]-prices[i]:前一天是冷静
				dp[i-1][1]-prices[i]:前一天是保持卖出

			dp[i][1]：状态二，保持卖出股票的状态（两天前就卖出了股票，度过一天冷冻期。或者是前一天就是卖出股票状态，一直没操作）
				dp[i-1][1]:前一天是保持卖出
				dp[i-1][3]:前一天是冷冻期状态

			dp[i][2]：状态三，今天卖出股票
				dp[i-1][2]:前一天也是卖出股票
				dp[i-1][0]+prices[i]:前一天是保持持有

			dp[i][3]：状态四，今天为冷冻期状态，但冷冻期状态不可持续，只有一天！
				dp[i-1][3]:前一天是冷静期状态
				dp[i-1][2]:前一天卖出股票

			这个题目的特点是，卖出后有一天的冷静期
		*/
		int maxProfitBest(vector<int>& prices) {
			if (prices.size() == 0) return 0;
			vector<vector<int>>dp(prices.size(), { 0,0,0,0 });

			dp[0][0] = -prices[0];
			dp[0][1] = 0;//保持卖出股票的状态；第一天买股票，然后第一天卖了利润是0
			dp[0][2] = 0;//今天卖出股票,第一天买股票，然后第一天卖了利润是0
			dp[0][3] = 0;//今天为冷冻期状态，冷静期也是卖了。总是都是一样，利润也是0；
			for (size_t i = 1; i < prices.size(); i++)
			{
				dp[i][0] = max(dp[i - 1][0], max(dp[i - 1][3] - prices[i], dp[i - 1][1] - prices[i]));
				dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]);
				dp[i][2] = max(dp[i - 1][2], dp[i - 1][0] + prices[i]);
				dp[i][3] = max(dp[i - 1][3], dp[i - 1][2]);
			}
			return max(dp[prices.size() - 1][1], max(dp[prices.size() - 1][2], dp[prices.size() - 1][3]));
		}

		/*
		714.买卖股票的最佳时机含手续费
		参考：
			https://www.programmercarl.com/0714.%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E7%9A%84%E6%9C%80%E4%BD%B3%E6%97%B6%E6%9C%BA%E5%90%AB%E6%89%8B%E7%BB%AD%E8%B4%B9%EF%BC%88%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%EF%BC%89.html#%E6%80%9D%E8%B7%AF
		思路：
			这个题目特点是，每天都能交易，但是交易都会有手续费。
			和122.买卖股票的最佳时机II很很相似。
			也就是“买股票时候扣一个手续费”。
				dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
			改成
				dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]-fee);

		*/
		int maxProfitFee(vector<int>& prices, int fee) {
			if (prices.size() == 0) return 0;
			vector<vector<int>>dp(prices.size(), { 0,0 });
			dp[0][0] = -prices[0];
			dp[0][1] = 0;
			for (size_t i = 1; i < prices.size(); i++)
			{
				dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
				dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i] - fee);
			}
			return dp[prices.size() - 1][1];
		}


		/*
		300.最长递增子序列
		参考：
			https://www.programmercarl.com/0300.%E6%9C%80%E9%95%BF%E4%B8%8A%E5%8D%87%E5%AD%90%E5%BA%8F%E5%88%97.html
		思路：
			1、dp含义：dp[i]代表数组nums从“上次递增结束位置”开始的的最长子序列的长度
			2、dp递推公式：
				if (nums[i] > nums[l])
					dp[i]=max(dp[i-1]+1,dp[i]);
				遍历到位置i，他的长度是由前面的最大长度+1，如果后面的值是》前面的值的话。
			3、初始化：
				!所有的都初始化1，因为最短就是1。
				初始化0，结果最后差一个。
		思考：
			这个为什么想起来用动态规划？
				因为，后面的最大长度，是由前面的最大长度+1来决定的，如果后面的值是》前面的值的话。
				这种由前后推出后面的情况，都可以用动态规划。
			为什么有两层循环？
				因为要求的递增序列，不一定是连续的。
				每个nums的最长子序列长度需要单独去算，而他要算的长度就到i。
			为什么这个用max，后面两个没有用max？
				可能和连不连续有关系吧。
		*/
		int lengthOfLIS(vector<int>& nums) {
			if (nums.size() <= 1) return 1;
			vector<int>dp(nums.size(), 1);
			int ret = 0;
			for (size_t i = 1; i < nums.size(); i++)
			{
				for (size_t l = 0; l < i; l++)
				{
					if (nums[i] > nums[l])
						dp[i] = max(dp[l] + 1, dp[i]);//!!!
				}
				//cout << "dp " << dp[i] << endl;
				ret = max(ret, dp[i]);
			}
			return ret;
		}


		/*
		674. 最长连续递增序列
		参考：
			https://www.programmercarl.com/0674.%E6%9C%80%E9%95%BF%E8%BF%9E%E7%BB%AD%E9%80%92%E5%A2%9E%E5%BA%8F%E5%88%97.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			这个题目和个题目不同的是“连续递增”，相对上题而言，不需要第二个for。
			1、dp含义：dp[i]:从上次递增结束的地方开始，到i的最长“连续”子序列的长度。
			2、公式：
				if(nums[i]>nums[i-1])
					dp[i]=dp[i-1]+1;
				else
					dp[i]=1;
		*/
		int findLengthOfLCIS(vector<int>& nums) {
			if (nums.size() <= 1) return 1;
			vector<int>dp(nums.size(), 1);
			int ret = 0;
			for (size_t i = 1; i < nums.size(); i++)
			{
				if (nums[i] > nums[i - 1])
					dp[i] = dp[i - 1] + 1;
				else
					dp[i] = 1;
				ret = max(ret, dp[i]);
			}
			return ret;
		}

		/*
		718. 最长重复子数组
		参考：
			https://www.programmercarl.com/0718.%E6%9C%80%E9%95%BF%E9%87%8D%E5%A4%8D%E5%AD%90%E6%95%B0%E7%BB%84.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			这个题目的 重复子数组是“连续的”。
			1、dp含义：
				dp[i][j]:数组nums1的下表i-1和数组nums2的下表l-1，最长重复子序列
			2、公式
				if (nums1[i-1] == nums2[l-1])//注意这！！！
						dp[i][l] = dp[i - 1][l - 1] + 1;
				else
					dp[i][l] = 1;
			3、初始化
				 假设nums1，nums2相同的话，dp[1][1]=1;
				 根据公式dp[1][1]=dp[0][0]+1;
				 所以，dp[0][0]=0;
				 这个推断也不好，总之不好初始化的时候，就赋值0或者1。
		*/
		int findLength(vector<int>& nums1, vector<int>& nums2) {
			//因为dp[i]表示遍历到i-1的位置的长度，需要多+1。另外默认值为0，因为1的时候，过不去。主要是我没找到一个好的解释，解析中也没提，也可能我没找到。
			vector<vector<int>>dp(nums1.size() + 1, vector<int>(nums2.size() + 1, 0));
			int ret = 0;
			dp[0][0] = 0;
			for (size_t i = 1; i < nums1.size() + 1; i++)
			{
				for (size_t l = 1; l < nums2.size() + 1; l++)
				{
					if (nums1[i - 1] == nums2[l - 1])//因为dp数组含义i，代表i-1下表位置，所以遍历dp[i]的时候，就是nums[i-1]
						dp[i][l] = dp[i - 1][l - 1] + 1;
					else
						dp[i][l] = 0;//一旦出现不想等的情况，长度清零
					ret = max(ret, dp[i][l]);
					//cout << ret << endl;
				}
			}
			return ret;
		}


		/*
		1143.最长公共子序列
		参考：
			https://www.programmercarl.com/1143.%E6%9C%80%E9%95%BF%E5%85%AC%E5%85%B1%E5%AD%90%E5%BA%8F%E5%88%97.html
		思考：
			这个题目的 重复子数组在text1或2中是可以“不连续的”。
			1、dp含义：dp[i][l] 代表从下表0到text1[i-1] text2[i-1]这个位置的最长子序列
			2、公式：
				相同的时候：
				if(text1[i]==text2[l])
					dp[i][l]=max(dp[i-1][l-1]+1,dp[i][l]);
				不相同的时候：
					比如abc和ace，遍历到第三个位置，c和e不同，但是此时的最长公共子序列为2
					所以，我们要考虑abc和ac或者是ab和ace。
				else
					dp[i][l]=max(dp[i][l-1],dp[i-1][l]);

			3、初始化
				dp[0][0]=0;
				test1[0, i-1]和空串的最长公共子序列自然是0，
				所以dp[i][0] = 0;
				同理dp[0][j]也是0。
				其实我一开始没想到，还是那句话，这中不好想的。先试试0，再试试1
		*/
		int longestCommonSubsequence(string text1, string text2) {
			vector<vector<int>>dp(text1.size() + 1, vector<int>(text2.size() + 1, 0));

			//int ret = 0;			ret = max(ret, dp[i][l]); 不用这个了，用这个也不错，但是dp的含义已经是
			for (size_t i = 1; i < text1.size() + 1; i++)
			{
				for (size_t l = 1; l < text2.size() + 1; l++)
				{
					if (text1[i - 1] == text2[l - 1])//-1别忘了， 遍历到i的时候，下表是i-1
						dp[i][l] = max(dp[i - 1][l - 1] + 1, dp[i][l]);
					else
						dp[i][l] = max(dp[i][l - 1], dp[i - 1][l]);
				}
			}
			return dp[text1.size()][text2.size()];
		}



		/*
		1035.不相交的线
		参考：
			https://www.programmercarl.com/1035.%E4%B8%8D%E7%9B%B8%E4%BA%A4%E7%9A%84%E7%BA%BF.html
		思考：
			这个题目和“1143.最长公共子序列”，代码是一样的；
			都是从下标0开始，然后到结束，nums1和nums2两个的子串都各个字符的顺序都不会改变位置，且两个子串是相同的。
		*/
		int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
			vector<vector<int>>dp(nums1.size() + 1, vector<int>(nums2.size() + 1, 0));
			for (size_t i = 1; i < nums1.size() + 1; i++)
			{
				for (size_t l = 1; l < nums2.size() + 1; l++)
				{
					if (nums1[i - 1] == nums2[l - 1])//-1别忘了， 遍历到i的时候，下表是i-1
						dp[i][l] = max(dp[i - 1][l - 1] + 1, dp[i][l]);
					else
						dp[i][l] = max(dp[i][l - 1], dp[i - 1][l]);
				}
			}
			return dp[nums1.size()][nums2.size()];
		}


		/*
		53. 最大子序和
		参考：
			https://www.programmercarl.com/0053.%E6%9C%80%E5%A4%A7%E5%AD%90%E5%BA%8F%E5%92%8C%EF%BC%88%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%EF%BC%89.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			之前贪心思路的时候，写过一次，代码和思路都很简单。
			1、含义：dp[i] 从0开始遍历到下标i的时候，最大的子数组和。
			2、公式：
				一看到是从0下标开始的，我都想用max，不知道后面通用不。先这么记者。
				dp[i]=max(dp[i-1]+nums[i],nums[i]);
				如果加上前面的结果加上nums[i],该没有当前的数大的话，不如用当前的数
			3、初始化：dp[0]=0;
			4、返回值，因为要求的是“连续”序列和，所以最大的结果可能在中间就出现。
		*/
		int maxSubArray(vector<int>& nums)
		{
			vector<int>dp(nums.size(), INT32_MIN);
			dp[0] = nums[0];
			int ret = dp[0];
			for (size_t i = 1; i < nums.size(); i++)
			{	//如果不是求“连续子序列和”，下面这个肯定没错——我还没试过，哈哈
				//dp[i] = max(max(dp[i - 1] + nums[i], nums[i]), dp[i - 1]);
				dp[i] = max(dp[i - 1] + nums[i], nums[i]);
				//if (dp[i] < 0) dp[i] = 0;//！！用不着，因为dp[i]已经是遍历到i的最大值了，不用把贪心的那部分弄过来当前结果《0的话，对后面的结果，就没有增益了，所以赋值0；
				//cout << "i" << i << " " << dp[i] << endl;
				ret = max(ret, dp[i]);
			}
			return ret;
		}


		/*
		392.判断子序列
		参考：
			https://www.programmercarl.com/0392.%E5%88%A4%E6%96%AD%E5%AD%90%E5%BA%8F%E5%88%97.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			这道题目算是编辑距离的入门题目（毕竟这里只是涉及到减法），也是动态规划解决的经典题型。
			这个题目，只是为了熟悉动态规划才去用，貌似双指针是很好的方法。
			大概思路就是，s出现的元素，t中也有的就留，t单独有的就“删除”。
			最后dp的值和s的长度一致，说明s是t的子串，否则是不是。
			和“1143.最长公共子序列”非常的相似。
			如果最后s的长度和最大的共有子串的长度是一样的，s肯定是t的子串。
			1、dp含义：dp[i][l] 代表从下表0到s[i-1] t[i-1]这个位置的最长子序列
			2、公式：
				相同的时候：
				if (s[i - 1] == t[l - 1])
					dp[i][l] = max(dp[i - 1][l - 1] + 1, dp[i][l]);
				不相同的时候：
					字符串s肯定是不能动的，要做的就是跳过t的当前字符串，
					dp的值保持“上一次遍历到t的字符串”的dp的值——最大的共有子串的长度。
				else
					dp[i][l] = dp[i][l - 1];
		*/
		bool isSubsequence(string s, string t) {
			vector<vector<int>>dp(s.size() + 1, vector<int>(t.size() + 1, 0));
			for (size_t i = 1; i < s.size() + 1; i++)//遍历s
			{
				for (size_t l = 1; l < t.size() + 1; l++)//遍历t
				{
					if (s[i - 1] == t[l - 1])
						dp[i][l] = max(dp[i - 1][l - 1] + 1, dp[i][l]);
					else
						dp[i][l] = dp[i][l - 1];
				}
			}
			if (s.size() == dp[s.size()][t.size()])
				return true;
			return false;
		}


		/*
		115.不同的子序列
		参考：
			https://www.programmercarl.com/0115.%E4%B8%8D%E5%90%8C%E7%9A%84%E5%AD%90%E5%BA%8F%E5%88%97.html
		思路：
			!!!没明白
		*/
		int numDistinct(string s, string t) {

		}


		/*
		583. 两个字符串的删除操作
		参考：
			https://www.programmercarl.com/0583.%E4%B8%A4%E4%B8%AA%E5%AD%97%E7%AC%A6%E4%B8%B2%E7%9A%84%E5%88%A0%E9%99%A4%E6%93%8D%E4%BD%9C.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路1：
			1、可以根据“1143.最长公共子序列”，这个题目来改动。两个数组的长度相加-最长公共子序列*2=要删除的元素数。
		思路2：
			本代码采用的思路
			1、dp含义：
				以i-1和j-1为下标的两个字符串，能达到相等的最小删除数。
			2、公式：
				i-1和j-1元素相等：dp[i-1][j-1];因为这两个元素相同，所以不用删除元素，也就不用添加删除次数。
				i-1和j-2元素不相等：dp[i][j-1]+1。+1就是增加一次删除次数
				i-2和j-1元素不相等：dp[i-1][j]+1
				if
				dp[i][j]=min(dp[i][j],min(dp[i-1][j]+1,dp[i][j-1]));
			3、初始化
				我的话，就是从for的遍历上看出来，初始化的是dp[0][j]=j和dp[i][0]=i
				从视频看的话，有个图是从三个方向推到dp[i][j]，所以要初始化dp[0][j]和dp[i][0]
				但是我每台明白他的思路，目前还是觉得我的思路好。
				dp[i][0]：word2为空字符串，以i-1为结尾的字符串word1要删除多少个元素，才能和word2相同呢，很明显dp[i][0] = i。
		*/
		int minDistance(string word1, string word2) {
			vector<vector<int>>dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
			for (size_t i = 0; i < word1.size() + 1; i++)
				dp[i][0] = i;
			for (size_t j = 0; j < word2.size() + 1; j++)
				dp[0][j] = j;
			for (size_t i = 1; i < word1.size() + 1; i++)
			{
				for (size_t j = 1; j < word2.size() + 1; j++)
				{
					if (word1[i - 1] == word2[j - 1])
						dp[i][j] = dp[i - 1][j - 1];
					else
						dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
				}
			}
			return dp[word1.size()][word2.size()];
		}

		/*
		子序列，总结：
		结果什么时候用max函数来确定？
			只有dp的定义，是从下表0开始来计算最终的长度，比如“1143.最长公共子序列”，最后的返回值就是
		什么时候dp[i][l] 代表的含义是i-1的下标怎么样
			从上面的题目来看，凡是判断nums1[i]==nums2[l]都要用-1。
		为什么上面判断相等要用i-1？
			？？？？？？？？？？
		什么时候用二维数组？
			对比两个数组它的元素是否相同的情况，要用二维。
			二维数组，自然对应的就是两个for
		什么时候初始化一条边
			首要，是二维的dp，然后dp[0][i]的时候每个值还不一样，这种很少。参考583. 两个字符串的删除操作
		*/

		/*
		72. 编辑距离
		参考：
			https://www.programmercarl.com/0072.%E7%BC%96%E8%BE%91%E8%B7%9D%E7%A6%BB.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			和“583. 两个字符串的删除操作”非常像
			1、dp[i][j]：坐标i-1和j-1，最少的操作次数
			2、公式
				i-1和j-1元素相等：dp[i-1][j-1];因为这两个元素相同，所以不用删除元素，也就不用添加删除次数。
				i-1和j-1元素不相等：
				增加：dp[i-1][j]+1或者：dp[i][j-1]+1
				删除：dp[i-1][j]+1或者：dp[i][j-1]+1；和“增加”是一样的，比如abc和ab，增加c和去掉c都是一样，最后哪个小，就用谁就行。
				替换：dp[i-1][j-1]+1；dp[i-1][j-1]是前一次两者都相等，比如abc和abd，到了d开始不相等了，只需要操作一次就行
		*/
		int minDistance1(string word1, string word2) {
			vector<vector<int>>dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
			for (size_t i = 0; i < word1.size() + 1; i++)
				dp[i][0] = i;
			for (size_t j = 0; j < word2.size() + 1; j++)
				dp[0][j] = j;
			for (size_t i = 1; i < word1.size() + 1; i++)
			{
				for (size_t j = 1; j < word2.size() + 1; j++)
				{
					if (word1[i - 1] == word2[j - 1])
						dp[i][j] = dp[i - 1][j - 1];
					else
						dp[i][j] = min(dp[i - 1][j - 1] + 1, min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
				}
			}
			return dp[word1.size()][word2.size()];
		}





		/*
		72. 编辑距离
		参考：
			https://www.programmercarl.com/0072.%E7%BC%96%E8%BE%91%E8%B7%9D%E7%A6%BB.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			和“583. 两个字符串的删除操作”非常像
			1、dp[i][j]：坐标i-1和j-1，最少的操作次数
			2、公式
				i-1和j-1元素相等：dp[i-1][j-1];因为这两个元素相同，所以不用删除元素，也就不用添加删除次数。
				i-1和j-1元素不相等：
				增加：dp[i-1][j]+1或者：dp[i][j-1]+1
				删除：dp[i-1][j]+1或者：dp[i][j-1]+1；和“增加”是一样的，比如abc和ab，增加c和去掉c都是一样，最后哪个小，就用谁就行。
				替换：dp[i-1][j-1]+1；dp[i-1][j-1]是前一次两者都相等，比如abc和abd，到了d开始不相等了，只需要操作一次就行
		*/
		int minDistance2(string word1, string word2) {
			vector<vector<int>>dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
			for (size_t i = 0; i < word1.size() + 1; i++)
				dp[i][0] = i;
			for (size_t j = 0; j < word2.size() + 1; j++)
				dp[0][j] = j;
			for (size_t i = 1; i < word1.size() + 1; i++)
			{
				for (size_t j = 1; j < word2.size() + 1; j++)
				{
					if (word1[i - 1] == word2[j - 1])
						dp[i][j] = dp[i - 1][j - 1];
					else
						dp[i][j] = min(dp[i - 1][j - 1] + 1, min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
				}
			}
			return dp[word1.size()][word2.size()];
		}


		/*
		647. 回文子串
		参考：
			https://www.programmercarl.com/0647.%E5%9B%9E%E6%96%87%E5%AD%90%E4%B8%B2.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE思路：
		思路1：
			双指针，感觉这个不错
		思路2：
			动态规划也挺好，但是空间复杂度差点。另外这个思路要是第一次见这个题目，也挺难想。
			因为是判断dp[i+1][l-1]来确定dp[i][l]，所以dp[i][l]是依赖dp[i+1][l-1]
			箭头顺序是右上，所有是从下往上，从左往右遍历。（看连接中的图）
			1、dp含义：
				dp[i][l] 区间il之间的字符串是“回文字符串”.布尔量。
			2、递推公式——错的，可以不按
				1、如果字符串il区间是回文字符串，并且str[i-1]==str[l+1],
				则说明i-1到l+1的中间是回文字符串。
				说明dp[i-1][l+1]依赖dp[i][l]，从图上画出来——遍历顺序：从下到上，从左到右
				!!这个是不对的,主要是依赖关系麻烦！对！我没有验证他不对，只是我代码没写出来，可能再改改代码就出来了，但是依赖关系非常麻烦。
				所以依赖关系还是要正常dp[i][l]依赖于其他的dp[][].这样的路是最简单的。
				2、i==l或者l-i==1，并且并且str[i-1]==str[l+1],
				则说明字符串il区间是回文字符串
				if(l-i<=1) ret++


			为了有这样的依赖关系，所以思路要换一下
			2、递推公式
			   如果str[i]==str[l]
			   如果dp[i+1][l-1]是回文字符串，则dp[i][l]是回文字符串；这样一个正常的依赖关系就出来了。
			   其实一般情况下，递推公式确定基本上是想到这。然后初始化。本教程里面，把初始化也写到这了。


			3、初始化
				初始化肯定要说全为false。
				如果i=l或者l-i=1，并str[i]==str[l]。则说明是回文字符串。
				这个其实可以合并到2中。

			4、遍历顺序
				这个顺序不太一样，不过只要在图上画出箭头的方向，就知道遍历的顺序了，具体可以看图；

		*/
		int countSubstrings(string s) {
			vector<vector<bool>>dp(s.size(), vector<bool>(s.size(), 0));
			int ret = 0;
			//参考中的for放在了下面的for中，这样虽然节省性能，但是代码不统一！！
			//！并且l的开始也改成i+1开始！
			//都是为了让“647. 回文子串”和“516. 最长回文子序列”代码和思路统一
			for (size_t i = 0; i < s.size(); i++)
			{
				ret++;
				dp[i][i] = 1;
			}
			for (int i = s.size() - 1; i >= 0; i--)
			{
				for (int l = i + 1; l < s.size(); l++)//！因为要检查的区间是i到l，所以l的值从i开始
				{
					if (s[i] == s[l])
					{
						if (l - i <= 1)
						{
							ret++;
							dp[i][l] = true;
						}
						else if (dp[i + 1][l - 1] == true)
						{
							ret++;
							dp[i][l] = true;
						}
					}
					//cout << "dp[i][l] i" << i << " l" << l << " " << dp[i][l] << endl;
				}
			}
			return ret;
		}


		/*
		516. 最长回文子序列
		参考：
			https://www.programmercarl.com/0516.%E6%9C%80%E9%95%BF%E5%9B%9E%E6%96%87%E5%AD%90%E5%BA%8F%E5%88%97.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思考：
			和“647. 回文子串”代码很相似
			1、dp含义：
				dp[i][l]区间il之间最长的回文子序列的长度
			2、公式
				1、如果s[i] == s[l]
					长度是内部已知的长度+2(dp[i+1][l-1]+2)；
					dp[i][l]=dp[i+1][l-1]+2;
				2、如果不想等，
					回文字符串的长度，最长的那部分有两种可能，
					加上左边的一个，或者加上右边的一个
					加上左边：dp[i][l-1]
					加上右边：dp[i+1][l]
					dp[i][l]=max(dp[i][l-1],dp[i+1][l])
			3、初始化
				上题“647. 回文子串”，把一部分的初始化放在内部了，
				其实还是放在外边好点，统一，并且好做题。
		*/
		int longestPalindromeSubseq(string s) {
			vector<vector<int>>dp(s.size(), vector<int>(s.size(), 0));

			for (size_t i = 0; i < s.size(); i++)
				dp[i][i] = 1;

			for (int i = s.size() - 1; i >= 0; i--)
			{
				/*!为什么这里又从l=i+1开始了，不是从i开始吗？
				参考中的解释是i到l的赋值已经在初始化中做了，所以没有必要，
				但实际上在本地中，从i开始的话，会报错，比如aaa，dp[2][2]=dp[3][1]会出现越界，
				但是上面的那个题目，却不会出现，应该是比较巧。
				后来，我修改了上面的代码，让他们尽量保持一样，然后都比较好理解。
				具体的参考一下上面。
				*/
				for (int l = i + 1; l < s.size(); l++)//有
				{
					if (s[i] == s[l])
						dp[i][l] = dp[i + 1][l - 1] + 2;
					else
						dp[i][l] = max(dp[i][l - 1], dp[i + 1][l]);
				}
			}
			return dp[0][s.size() - 1];
		}


		/*
		回文子序列总结：
		1、基本上都是二维数组，并且dp的定义都是i到l区间来决定怎么怎么样。
		*/


		void test()
		{
			string str = "bbbab";
			vector<int> dp{ -2,1,-3,4,-1,2,1,-5,4 };
			vector<int> dp1{ 3,2,1,4,7 };
			cout << longestPalindromeSubseq(str);
		}

	};
}

//单调站
namespace Dandiaozhan
{
	class Solution {
	public:
		/*
		 什么时候用单调栈呢？
			通常是一维数组，
			要寻找任一个元素的右边或者左边“第一个”比自己大或者小的元素的"距离"，
			此时我们就要想到可以用单调栈了。时间复杂度为O(n)。
		单调栈里元素是递增呢？ 还是递减呢？
			如果求一个元素右边第一个更大元素，单调栈就是递增的，
			如果求一个元素右边第一个更小元素，单调栈就是递减的。

		没有求左边的？
			“接雨水”这个题目 求了左边第一个第一个比他大的和右边第一个比比它大的。

			“84.柱状图中最大的矩形”，这个题目同时检测了
			元素左边第一个更小元素和元素右边第一个更小元素

			综上两种情况来看，
			接雨水——中间的这个元素是栈顶元素，左边的是下一个栈顶元素，右边的是当前遍历到的元素。
			最大矩形——中间的这个元素是栈顶元素，左边的是正在遍历的元素，右边是下一个栈顶元素。
		*/



		/*
		739. 每日温度
		参考：
			https://www.programmercarl.com/0739.%E6%AF%8F%E6%97%A5%E6%B8%A9%E5%BA%A6.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			核心就是求右侧第一个大于该元素的距离。
			当元素小于栈顶元素，进栈
			当元素等于栈顶元素，进栈
			当元素大于栈顶元素：
				记录当前栈顶元素到该元素的距离——result[stk.top()] = i - stk.top();
				把所有大于的元素都出栈或者栈空了，把元素放进去。

			栈中放的元素是数组的下标
			结果数组的含义：result[1]=2;在数组中下标1的元素，它的右侧第一个大于它的元素，与他的距离为2.
		*/
		vector<int> dailyTemperatures(vector<int>& temperatures) {
			vector<int> result(temperatures.size(), 0);
			stack<int> stk;
			stk.push(0);
			for (size_t i = 1; i < temperatures.size(); i++)
			{
				if (temperatures[i] < temperatures[stk.top()])//当元素小于栈顶元素，进栈
					stk.push(i);
				else if (temperatures[i] == temperatures[stk.top()])//当元素等于栈顶元素，进栈;前两种情况可以合成一个，都已放到while下面，具体看下面的代码。
					stk.push(i);
				else
				{
					while (!stk.empty() && temperatures[i] > temperatures[stk.top()])//当元素大于栈顶元素：
					{
						result[stk.top()] = i - stk.top();
						stk.pop();
					}
					stk.push(i);
				}
			}
			return result;
		}

		//简化写法，但是思路没有上面的明确。
		vector<int> dailyTemperatures1(vector<int>& temperatures) {
			vector<int> result(temperatures.size(), 0);
			stack<int> stk;
			//stk.push(0);//!这个可以放在里面.当一次遍历，stk为空的时候，stk会插入0
			for (size_t i = 0; i < temperatures.size(); i++)
			{
				while (!stk.empty() && temperatures[i] > temperatures[stk.top()])//当元素大于栈顶元素：
				{
					result[stk.top()] = i - stk.top();
					stk.pop();
				}
				stk.push(i);//当元素小于栈顶元素，进栈;当元素等于栈顶元素，进栈。都可以放到这。
			}
			return result;
		}



		/*
		496.下一个更大元素 I
		参考：
			https://www.programmercarl.com/0496.%E4%B8%8B%E4%B8%80%E4%B8%AA%E6%9B%B4%E5%A4%A7%E5%85%83%E7%B4%A0I.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			首先还是单调栈的思路。
			不过不同的是，这次是分为两个数组，要从一个数组中到另外一个数组中找寻。
			为了解决这样的问题，所以具体思路如下：
			因为nums1是nums2的子数组，所以从nums2中找到“对应点它的最近的一个比它大的元素”
			然后看这个元素在nums1中有没有
			如果没有，那么就正常操作，继续往下遍历nums2
			如果有，那么就找到这个元素在nums1中的下标。！而根据元素找nums1的可以用umap省点事。
			然后result【对应下标】=nums2【i】
		*/
		vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
			vector<int>result(nums1.size(), -1);//初始化是-1，题目中找不到返回是-1；
			stack<int>stk;
			unordered_map<int, int>umap;
			for (size_t i = 0; i < nums1.size(); i++)
				umap[nums1[i]] = i;
			stk.push(0);
			for (size_t i = 1; i < nums2.size(); i++)
			{
				while (!stk.empty() && nums2[i] > nums2[stk.top()])
				{
					if (umap.find(nums2[stk.top()]) != umap.end())
					{
						//不对，因为nums2[i]是个比当前栈顶元素要大的元素。根据题意，要做的是把这个大的元素作为result对应位置的值去赋值。
						//而对应的位置，是根据“栈底”的值去找的。
						//!别弄错，这个题目，我在这出错了。
						//result[umap[nums2[i]]] = nums2[i];//不错
						result[umap[nums2[stk.top()]]] = nums2[i];//不错
					}
					stk.pop();
				}
				stk.push(i);
			}
			return result;
		}




		/*
		503.下一个更大元素II
		参考：
			https://www.programmercarl.com/0503.%E4%B8%8B%E4%B8%80%E4%B8%AA%E6%9B%B4%E5%A4%A7%E5%85%83%E7%B4%A0II.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			这个和“739. 每日温度”,"496.下一个更大元素 I"很相似，不同的是这个数组是循环的。
			方法看题解有两种方式：
			1、扩充数组，相当于复制一份数组接到后面，
			2、在原数组上遍历，遍历两边。用“取余”
		*/
		vector<int> nextGreaterElements(vector<int>& nums) {
			vector<int>result(nums.size(), -1);//初始化-1，找不到就是-1.
			stack<int> stk;
			for (size_t i = 0; i < nums.size() * 2; i++)
			{
				while (!stk.empty() && nums[i % nums.size()] > nums[stk.top()])
				{
					result[stk.top()] = nums[i % nums.size()];
					stk.pop();
				}
				stk.push(i % nums.size());
			}
			return result;
		}


		/*
		42. 接雨水
		参考：
			https://www.programmercarl.com/0042.%E6%8E%A5%E9%9B%A8%E6%B0%B4.html#%E6%80%9D%E8%B7%AF
		思路：
			方法有暴力，双指针，单调栈
			还是用单调栈的思路，因为比较符合“找某一个值右侧的最大值”。（不明白，看图）
			这个题目，貌似用3个元素，比较好理解，就像这个连接中的图展示的那样。
			在单调栈出栈的时候操作，这个时候一定出现了大于nums[stk.top()]的元素，出现了凹槽，这个时候有积水
			！它的计算其实是，while循环一次，计算一个新的栈顶元素和nums[i]的面积。（如果能进while的话）
			之前计算过的面积，不会重复计算已经计算过的面积。
			虽然宽度增加了，但是底的高度会变化。也就是高度会变化，这个高度是取决于栈顶元素的大小。
			mid=nums[stk.top()];//取出积水中间的坐标，也就是“上面说的底”
			高度：
				min（mid左侧的高度，mid右侧的高度）- mid高度
				stk.pop();让栈顶为mid左侧的值
				hih=min(nums[stk.top()],nums[i])-mid;
			宽度：
				当前nums的下标-最新的栈顶元素的值-1；-1才是求凹槽的宽度
				wid = i-stk.top()-1;
			面积：
				are = hih*wid;
				在while中不断的累加are的值。

			用四个元素，比如“4314”，先计算距离nums[i]最近的且小于它的面积。
			如果下一个height[st.top()]也是小于height[i] ，则计算他俩的面积
			然后通过while，不断的计算。直到结束。
		*/
		int trap(vector<int>& height) {
			stack<int> stk;
			int ret = 0;

			for (size_t i = 0; i < height.size(); i++)
			{
				while (!stk.empty() && height[i] > height[stk.top()])
				{
					int mid = height[stk.top()];
					stk.pop();
					if (!stk.empty())//!这里因为上面有pop，所以要有个删除，否则就有可能出现越界。
					{
						int hih = min(height[stk.top()], height[i]) - mid;
						int wid = i - stk.top() - 1;
						ret += hih * wid;
					}
				}
				stk.push(i);
			}
			return ret;
		}

		/*
		84.柱状图中最大的矩形
		参考：
			https://www.programmercarl.com/0084.%E6%9F%B1%E7%8A%B6%E5%9B%BE%E4%B8%AD%E6%9C%80%E5%A4%A7%E7%9A%84%E7%9F%A9%E5%BD%A2.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			有暴力和单调栈方法，这里用单调栈的方法。
			求遍历到的每一个下标，它左侧第一个最小的元素和右侧第一个最小的元素。
			为什么这么做呢？
			从当前坐标的高度往左右延申，直到遇见左右第一个比它矮的矩形，
			这个时候所得到的面积，就是当前遍历的下标对应的最大矩形的面积
			然后，取其中最大的面积，就是当前数组种，也就是柱状图中最大的矩形。


			既然要求所遇到的第一个“较小”的元素，单调栈从头到尾是单调递减的。
			面积：
				are = hig*wid;
			宽度：
				和“接雨水”题目一样，是需要当前遍历元素和两个栈顶元素。
				hight=i mid=第一个栈顶元素 left=第二个栈顶元素（不明白就画个图）

				wid = 左边的第一个小于当前元素的坐标-右边第一个小于当前元素的坐标 + 1；
				wid = 当先遍历元素的下标 - 第二个栈顶元素-1；
				wid = i - stk.top() - 1;
			高度：
				hig=当前遍历元素的值

			其他：
				遍历的数组头和尾各加一个0。不明白就看链接种的解释。
		*/
		int largestRectangleArea(vector<int>& heights) {
			heights.push_back(0);
			heights.insert(heights.begin(), 0);
			stack<int>stk;
			int ret = 0;

			for (int i = 0; i < heights.size(); i++)
			{
				while (!stk.empty() && heights[i] < heights[stk.top()])
				{
					int mid = stk.top();
					stk.pop();
					if (!stk.empty())
					{
						int wid = i - stk.top() - 1;//！！减1是因为两个坐标是分别是右边和左边第一个小于该元素的坐标，-1才是以当前元素值为高的矩形的宽度。
						int hig = heights[mid];
						ret = max(wid*hig, ret);
					}
				}
				stk.push(i);
			}
			return ret;
		}

		/*
		接雨水和最大矩形，两个题目我都是看了题解，做出来的，也基本上明白了。
		但，视频没有看完，从我做这个题目的时候，我发现视频种有些思想我可能没想到，
		这种虽然不至于让我做不出来，但还是心里有点不稳当，二刷的时候看一下视频再，巩固一下。
		*/
		void test()
		{
			string str = "bbbab";
			vector<int> dp{ 2,1,5,6,2,3 };
			vector<int> dp1{ 1,3,4,2 };
			cout << largestRectangleArea(dp) << endl;
			/*vector<int> ret = nextGreaterElement(dp, dp1);
			for (size_t i = 0; i < ret.size(); i++)
			{
				cout << ret[i] << endl;
			}*/
		}
	};
}

//图论
namespace TULUN
{
	class Solution {

	private:
		vector<int> path;
		vector<vector<int>> result;

	public:
		/*
		深度优先搜索理论基础
		dfs的代码框架和回溯算法的代码框架是差不多的。几乎是一样的。
		void dfs(参数) {
			if (终止条件) {
				存放结果;
				return;
			}

			for (选择：本节点所连接的其他节点) {
				处理节点;
				dfs(图，选择的节点); // 递归
				回溯，撤销处理结果
			}
		}
		*/

		/*
		797.所有可能的路径
		参考：
			https://www.programmercarl.com/0797.%E6%89%80%E6%9C%89%E5%8F%AF%E8%83%BD%E7%9A%84%E8%B7%AF%E5%BE%84.html#%E6%80%9D%E8%B7%AF
		思路：
			递归函数功能就是接上于x相连的所有路径。不包括x。
			所以在外面需要把x这个点额外的加上。所以一开始需要把0加上。
		*/
		//graph：图  x：当前遍历的节点在graph中的下标。当然在下标的值就是图中的节点的值
		void allPathsSourceTarget_dfs(vector<vector<int>>& graph, int x)
		{
			if (x == graph.size() - 1) {//遍历到最后的点，递归结束
				//path.push_back(x);//在加这个就重复加尾巴了。
				result.push_back(path);
				return;
			}

			//未到最后的点，开始遍历和x接触的点
			for (size_t i = 0; i < graph[x].size(); i++)
			{
				path.push_back(graph[x][i]);
				allPathsSourceTarget_dfs(graph, graph[x][i]);
				path.pop_back();//这个x点，已经在上面的函数中已经添加进去了，这个时候就要换个路径了。
			}
			return;//为了保持语法
		}

		vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
			path.push_back(0);//下面函数的功能：就是接上于x相连的所有路径。不包括x，所以在外面需要把x这个点额外的加上。
			allPathsSourceTarget_dfs(graph, 0);
			return result;
		}




		/*
		广度优先搜索理论基础
		因为广搜是从起点出发，以起始点为中心一圈一圈进行搜索，一旦遇到终点，记录之前走过的节点就是一条最短路。

		当然，也有一些问题是广搜 和 深搜都可以解决的，
		例如岛屿问题，这类问题的特征就是不涉及具体的遍历方式，只要能把相邻且相同属性的节点标记上就行。

		用队列，还是用栈，甚至用数组，都是可以的。
		*/


		/*
		200、岛屿数量
		参考：
			https://www.programmercarl.com/0200.%E5%B2%9B%E5%B1%BF%E6%95%B0%E9%87%8F.%E5%B9%BF%E6%90%9C%E7%89%88.html#%E6%80%9D%E8%B7%AF
		思路：
			用这个思路——图的“广度遍历”或者是“广度优先搜索”；
			不是从中间走的，而是从图的左上角开始。
			递归函数的功能——找到xy所在岛屿的所有的坐标，并标记visited[i][l]=true;找完了就出来
		*/

		//grid图 visited图上哪个点被访问过 xy 要访问的点的坐标
		void numIslands_bfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y)
		{
			int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
			queue<pair<int, int>> que;
			que.push({ x, y });//访问到了谁，待会就遍历他的四个方向。
			visited[x][y] = true;//访问到了谁，visited赋值true
			while (!que.empty())//只要是队列不空，那就是要接着遍历这个元素的四周
			{
				//每次从队列中都要拿出新的，遍历新的四个方向。
				pair<int, int> cur = que.front();
				que.pop();//!这个别忘了！
				int curX = cur.first;
				int curY = cur.second;
				for (size_t i = 0; i < 4; i++)
				{
					int nextX = curX + dir[i][0];
					int nextY = curY + dir[i][1];
					//判断数组是否越界
					if (0 <= nextX && nextX < grid.size() && 0 <= nextY && nextY < grid[0].size())
					{
						//判断这个点4个方向都是陆地的点，然后不断的加到队列中，这样就能找到与一开始提供的xy是同一块岛屿的所有坐标。
						if (!visited[nextX][nextY] && grid[nextX][nextY] == '1')
						{
							que.push({ nextX, nextY });
							visited[nextX][nextY] = true;
						}
					}
				}
			}


		}
		int numIslands(vector<vector<char>>& grid) {
			vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
			int ret = 0;
			for (size_t i = 0; i < grid.size(); i++)
			{
				for (size_t l = 0; l < grid[0].size(); l++)//从图的左上角开始
				{
					if (!visited[i][l] && grid[i][l] == '1')
					{
						ret++;
						numIslands_bfs(grid, visited, i, l);
						//在这个函数功能：找到xy所在岛屿的所有的坐标，并标记visited[i][l]=true;
						//所以这个if每进来一次，就说明出现了的新的“没有标记的”。
						//这就是新的岛屿，所以ret++;
					}
				}
			}
			return ret;
		}


		/*
		200、岛屿数量——深度搜索，我没看。题目一样，我节省点时间，二刷的时候看！
		参考：
			https://www.programmercarl.com/0200.%E5%B2%9B%E5%B1%BF%E6%95%B0%E9%87%8F.%E6%B7%B1%E6%90%9C%E7%89%88.html
		思路：

		*/

		/*
		695. 岛屿的最大面积
		参考：
			https://www.programmercarl.com/0695.%E5%B2%9B%E5%B1%BF%E7%9A%84%E6%9C%80%E5%A4%A7%E9%9D%A2%E7%A7%AF.html
		思路：
			感觉和“200、岛屿数量”题目非常相似。
			最大的面积的，就是算出各个面积，然后用max比较最大的。
			每次调用这个函数的时候，就是一个新的岛屿，然后返回面积。
		*/

		int maxAreaOfIsland_bfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y)
		{
			int are = 1;//只有当前这点没有遍历过，并且是陆地，才能进这个函数
			int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
			queue<pair<int, int>> que;
			que.push({ x, y });//访问到了谁，待会就遍历他的四个方向。
			visited[x][y] = true;//访问到了谁，visited赋值true
			while (!que.empty())//只要是队列不空，那就是要接着遍历这个元素的四周
			{
				//每次从队列中都要拿出新的，遍历新的四个方向。
				pair<int, int> cur = que.front();
				que.pop();//!这个别忘了！
				int curX = cur.first;
				int curY = cur.second;
				for (size_t i = 0; i < 4; i++)
				{
					int nextX = curX + dir[i][0];
					int nextY = curY + dir[i][1];
					//判断数组是否越界
					if (0 <= nextX && nextX < grid.size() && 0 <= nextY && nextY < grid[0].size())
					{
						//判断这个点4个方向都是陆地的点，然后不断的加到队列中，这样就能找到与一开始提供的xy是同一块岛屿的所有坐标。
						if (!visited[nextX][nextY] && grid[nextX][nextY] == 1)
						{
							are++;
							que.push({ nextX, nextY });
							visited[nextX][nextY] = true;
						}
					}
				}
			}

			return are;
		}

		int maxAreaOfIsland(vector<vector<int>>& grid) {

			vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
			int ret = 0;
			for (size_t i = 0; i < grid.size(); i++)
			{
				for (size_t l = 0; l < grid[0].size(); l++)//从图的左上角开始
				{
					if (!visited[i][l] && grid[i][l] == 1)
					{
						//ret++;
						//maxAreaOfIsland_bfs(grid, visited, i, l);
						ret = max(ret, maxAreaOfIsland_bfs(grid, visited, i, l));
						//在这个函数功能：找到xy所在岛屿的所有的坐标，并标记visited[i][l]=true;
						//所以这个if每进来一次，就说明出现了的新的“没有标记的”。
						//这就是新的岛屿，所以ret++;
					}
				}
			}
			return ret;
		}



		/*
		1020. 飞地的数量——第一个深度思想的矩阵题目
		参考：
			https://www.programmercarl.com/1020.%E9%A3%9E%E5%9C%B0%E7%9A%84%E6%95%B0%E9%87%8F.html#%E6%80%9D%E8%B7%AF
		其他：
			这个题目用深度或者广度都行，为了熟悉深度，所以用深度来做。
			我看了一下这个题解的代码，发现这个以及前面这两个题目的深度的代码和第一个题目的代码都不像，
			核心还是在于后面这个三个题目，他都是矩阵，所以遍历的时候固定都是4
			而第一个题目，一个节点到下个节点有几个节点接着不确定，所以遍历的次数不确定，是要根据当前元素的个数来确定的。

			总结：
				第一个题目，只适合用来找路径，其他的题目套不上去。
				矩阵题目的话，广度和深度都差不多。

			为了熟悉深度，最终还是决定要用“深度”思想.
			我个人感觉深搜的思路，没有广搜的思路好，以后这种矩阵，都是用“广搜”吧
		思路：
			卡子哥的思路，是遍历四条边的，边上如果有陆地，就进去深搜，并把他们变成海洋，直到四条边都结束。
			这样，飞地就在地图上剩下来了。
			最后再来一遍深搜，记录深搜次数，这个次数就是最终的飞地的数量。
			他这个代码中，没有visited[i][l]，是怎么知道哪些元素被访问了？
			其实核心还是有的，只不过他把陆地变成海洋。下次开始的位置，一定是陆地和visited[i][l]本质一样。

			我的思路——，每个岛屿都遍历，如果发现该岛屿中有地块和边界接触，则说明该岛屿不是飞地，则返回0
			是非地的，返回飞地数量。
			不断的累加，最后返回所有的数量。

			！！！执行时间300ms，不知道为啥，我看好几遍，没发现有问题的点，就是普通的深度递归啊。
			卡子哥的就用50ms。
			先这样吧，不浪费时间了
		*/
		int numEnclaves_ret = 0;
		bool numEnclaves_flag = false;//岛屿中有靠边的就是true
		int numEnclaves_dfs(vector<vector<int>>& graph, vector<vector<bool>>& visited, int x, int y)
		{
			int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };//下 上 右 左
			for (size_t i = 0; i < 4; i++)
			{
				int nextX = x + dir[i][0];
				int nextY = y + dir[i][1];
				//判断数组是否越界
				if (0 <= nextX && nextX < graph.size() && 0 <= nextY && nextY < graph[0].size())
				{
					//没有遍历过，并且是陆地
					if (!visited[nextX][nextY] && graph[nextX][nextY] == 1)
					{
						numEnclaves_ret++;
						if (nextX == 0 || nextX == graph.size() - 1 || nextY == 0 || nextY == graph[0].size() - 1)//说明是这个点碰到了边
							numEnclaves_flag = true;
						visited[nextX][nextY] = true;
						numEnclaves_dfs(graph, visited, nextX, nextY);
					}
				}
			}
			return numEnclaves_ret;
		}


		int numEnclaves(vector<vector<int>>& grid) {
			int num = 0;
			vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
			for (size_t i = 0; i < grid.size(); i++)
			{
				for (size_t l = 0; l < grid[0].size(); l++)
				{
					if (i == 0 || i == grid.size() - 1 || l == 0 || l == grid[0].size() - 1)//说明是这个点碰到了边——直接跳过。
						continue;
					if (!visited[i][l] && grid[i][l] == 1)
					{
						num++;
						numEnclaves_flag = false;
						numEnclaves_ret = 0;
						visited[i][l] = true;
						int ret = numEnclaves_dfs(grid, visited, i, l);
						if (numEnclaves_flag == false)
							num += ret;
						else
							num--;//!--是因为我每次遍历一个岛屿，都要提前加上一个，如果这个岛屿是靠边的，那么我肯定要减去。
					}
				}
			}
			return num;

		}


		/*
		130. 被围绕的区域
		参考：
			https://www.programmercarl.com/0130.%E8%A2%AB%E5%9B%B4%E7%BB%95%E7%9A%84%E5%8C%BA%E5%9F%9F.html#%E6%80%9D%E8%B7%AF
		思路：
			这个题目和“1020. 飞地的数量”非常相似。代码上和这个题目基本上共用。
			但是我的题目中，没有使用卡子哥的思路。
			所以在这个题目，我尝试使用他的思路

			题目要求是返回“填充后”的矩阵，要填充的是中间被围起来的岛屿。
			1、先把靠边的岛屿，全部从0（岛屿）变成a，这个时候图上就只剩下“被围起来的小岛屿”
			2、这个时候把剩下的岛屿，从0变成x，也就是从陆地变成水，这个时候图上就只用“水”和之前的靠边陆地“a”
			3、最后把靠边的陆地“a”变成0，然后返回矩阵即可
			4、本身是x的一直没动。
		注意：
			要注意的地方，看注释吧
		*/

		void solve_dfs(vector<vector<char>>& graph, int x, int y)
		{
			int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };//下 上 右 左
			for (size_t i = 0; i < 4; i++)
			{
				int nextX = x + dir[i][0];
				int nextY = y + dir[i][1];
				//判断数组是否越界
				if (0 <= nextX && nextX < graph.size() && 0 <= nextY && nextY < graph[0].size())
				{
					//如果下一个接触的岛屿是0，就变成a
					if (graph[nextX][nextY] == 'O')
					{
						graph[nextX][nextY] = 'A';
						solve_dfs(graph, nextX, nextY);
					}
				}
			}
		}
		/*
		！！solve_dfs 这个函数的功能，是遍历从下表x和下标y开始，但是不包括xy，所以需要在调用函数前赋值
		当然也可以放在里面，也就是访问哪个点，哪个点就赋值。具体看链接中的代码。
		另外，上面的所有的代码，都符合这个逻辑。
		后面的代码，我尽量都放在里面，这样写代码的时候不容易出错。

		 在总结这个和上面这两个题目。如果牵扯到把图中的元素改变了，那么可以不用visited
		*/
		void solve(vector<vector<char>>& board) {
			int m = board.size();
			int n = board[0].size();
			//下面两个for是用来把矩阵边上的0以及和他接触的岛屿，变成a
			for (size_t i = 0; i < m; i++)
			{
				if (board[i][0] == 'O') {
					board[i][0] = 'A';//！！这个放在函数内也可以
					solve_dfs(board, i, 0);//矩阵的左边
				}
				if (board[i][board[0].size() - 1] == 'O') {
					board[i][board[0].size() - 1] = 'A';
					solve_dfs(board, i, board[0].size() - 1);//矩阵的右边
				}
			}
			for (size_t i = 0; i < n; i++)
			{
				if (board[0][i] == 'O') {
					board[0][i] = 'A';
					solve_dfs(board, 0, i);//矩阵的上边
				}
				if (board[board.size() - 1][i] == 'O') {
					board[board.size() - 1][i] = 'A';
					solve_dfs(board, board.size() - 1, i);//矩阵的下边
				}
			}
			//这个for遍历整个图
			for (size_t i = 0; i < m; i++)
			{
				for (size_t l = 0; l < n; l++)
				{
					if (board[i][l] == 'O')
						board[i][l] = 'X';
					if (board[i][l] == 'A')//这两个不能颠倒，要不然这个刚赋值成O，下面就会变成X
						board[i][l] = 'O';
				}
			}
			return;
		}



		/*
		417. 太平洋大西洋水流问题
		参考：
			https://www.programmercarl.com/0417.%E5%A4%AA%E5%B9%B3%E6%B4%8B%E5%A4%A7%E8%A5%BF%E6%B4%8B%E6%B0%B4%E6%B5%81%E9%97%AE%E9%A2%98.html#%E6%80%9D%E8%B7%AF
		思路：
			这个题目比较复杂，简单来说就是，图上的哪些点可以同时流向太平洋和大西洋
			遍历这个图中的每个元素，然后检查这个元素能不能“同时”走到大西洋和太平洋
			怎么判断呢？
			从头开始遍历元素，从这个元素开始，4个方向发散，走到哪就用visited标记。
			4个方向走的规则，是下个元素《=当前元素的值。
			直到4个方向的遍历结束。
			这个时候再遍历4条边，如果4条边出现了同时到了走到大西洋和太平洋。这个点就满足，否则不满足。


			这个超时了，换下面的思路。

		void pacificAtlantic_dfs(vector<vector<int>>& heights, vector<vector<bool>>&visited, int x, int y)
		{
			visited[x][y] = true;//遍历谁，就把谁加标识！
			int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };//下 上 右 左
			for (size_t i = 0; i < 4; i++)
			{
				int nextX = x + dir[i][0];
				int nextY = y + dir[i][1];
				//判断数组是否越界
				if (0 <= nextX && nextX < heights.size() && 0 <= nextY && nextY < heights[0].size())
				{
					//!!别忘了，遍历过的就别遍历。
					//如果下个元素《=当前元素的值,说明可以流下去，说明有往下遍历的必要
					if (!visited[nextX][nextY] && heights[nextX][nextY] <= heights[x][y])
					{
						pacificAtlantic_dfs(heights, visited, nextX, nextY);
					}
				}
			}
		}
		bool pacificAtlantic_result(vector<vector<int>>& heights, int x, int y)
		{
			vector<vector<bool>>visited(heights.size(), vector<bool>(heights[0].size(), false));
			pacificAtlantic_dfs(heights, visited, x, y);
			bool isPacific = false;
			bool isAtlantic = false;
			//下面两个for是用来检测矩阵边上是否有被标记的点，如果有，则说明到了其中一个洋。如果两个都到的话，返回ture
			for (size_t i = 0; i < visited.size(); i++)
			{
				if (visited[i][0] == true)//矩阵的左边
					isPacific = true;
				if (visited[i][visited[0].size() - 1] == true)
					isAtlantic = true;//矩阵的右边
			}
			for (size_t i = 0; i < visited[0].size(); i++)
			{
				if (visited[0][i] == true)
					isPacific = true;//矩阵的上边
				if (visited[visited.size() - 1][i] == true)
					isAtlantic = true;//矩阵的下边
			}
			return isAtlantic && isPacific;
		}
		vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
			vector<vector<int>> ret;
			for (int i = 0; i < heights.size(); i++)
			{
				for (int l = 0; l < heights[0].size(); l++)
				{
					if (pacificAtlantic_result(heights, i, l))
						ret.push_back({ i, l });
				}
			}
			return ret;
		}
		*/
		/*
		417. 太平洋大西洋水流问题
		参考：
			https://www.programmercarl.com/0417.%E5%A4%AA%E5%B9%B3%E6%B4%8B%E5%A4%A7%E8%A5%BF%E6%B4%8B%E6%B0%B4%E6%B5%81%E9%97%AE%E9%A2%98.html#%E6%80%9D%E8%B7%AF
		思路：
			这个题目比较复杂，简单来说就是，图上的哪些点可以同时流向太平洋和大西洋;
			上面的思路，可以，但是时间复杂度太高了。
			改成，从四个边往内部走。
			从大西洋往里面走的，标记一下。
			从太平洋往里面走的，标记一下。
			然后检查每个点的标记，哪个点有两个表计，就说明满足条件。

			我这个为了省时间，我基本上都是抄他的。
		*/

		// 从低向高遍历，注意这里visited是引用，即可以改变传入的pacific和atlantic的值
		void pacificAtlantic_dfs(vector<vector<int>>& heights, vector<vector<bool>>& visited, int x, int y) {
			int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };//下 上 右 左
			if (visited[x][y]) return;

			visited[x][y] = true;
			for (int i = 0; i < 4; i++) { // 向四个方向遍历
				int nextx = x + dir[i][0];
				int nexty = y + dir[i][1];
				// 超过边界
				if (nextx < 0 || nextx >= heights.size() || nexty < 0 || nexty >= heights[0].size()) continue;
				//！！ 高度不合适，注意这里是从低向高判断——下个高度应该》=当前高度才ok。
				if (heights[x][y] > heights[nextx][nexty]) continue;
				pacificAtlantic_dfs(heights, visited, nextx, nexty);
			}
			return;

		}

		vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
			vector<vector<int>> result;
			int n = heights.size();
			int m = heights[0].size(); // 这里不用担心空指针，题目要求说了长宽都大于1

			 // 记录从太平洋边出发，可以遍历的节点
			vector<vector<bool>> pacific = vector<vector<bool>>(n, vector<bool>(m, false));

			// 记录从大西洋出发，可以遍历的节点
			vector<vector<bool>> atlantic = vector<vector<bool>>(n, vector<bool>(m, false));


			// 从最上最下行的节点出发，向高处遍历
			for (int i = 0; i < n; i++) {
				pacificAtlantic_dfs(heights, pacific, i, 0); // 遍历最左列，接触太平洋 
				pacificAtlantic_dfs(heights, atlantic, i, m - 1); // 遍历最右列，接触大西 
			}
			// 从最左最右列的节点出发，向高处遍历
			for (int j = 0; j < m; j++) {
				pacificAtlantic_dfs(heights, pacific, 0, j); // 遍历最上行，接触太平洋
				pacificAtlantic_dfs(heights, atlantic, n - 1, j); // 遍历最下行，接触大西洋
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					// 如果这个节点，从太平洋和大西洋出发都遍历过，就是结果
					if (pacific[i][j] && atlantic[i][j]) result.push_back({ i, j });
				}
			}
			return result;
		}


		/*
		827.最大人工岛
		参考：
			https://www.programmercarl.com/0827.%E6%9C%80%E5%A4%A7%E4%BA%BA%E5%B7%A5%E5%B2%9B.html#%E6%80%9D%E8%B7%AF
		思路：
			思路也很简单。
			1、先是遍历图，然后记录下每个岛屿的面积，
			   为了方便记录不同岛屿的面积，用map容易。
				多说一句，遍历图的时候，如果所有的元素都是1的话，那么就返回这个图的m*n。
			2、接着遍历上面步骤中，没有遍历的部分。
			   也就是把新的一块放到没有遍历的地方，也就是这个地方从0变成1；
			   这个时候，遍历新1的四周，看看有几个岛屿接壤，
			   (另外，一个新的1，,有可能和同一个岛屿有好几个接壤，所以需要记录下，避免重复加这块地的面积)
			   把接壤的地方都加上，这就是新的岛屿的面积。

			3、最后返回一个最大的面积就行。

			我的具体实现和它的有点区别，具体看代码
		*/
		int largestIsland_bfs(vector<vector<int>>& grid, vector<vector<bool>>&visited, int mark, int x, int y)
		{
			grid[x][y] = mark;//给地图上不同的岛屿赋值标记
			int are = 1;//只有当前这点没有遍历过，并且是陆地，才能进这个函数
			int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
			queue<pair<int, int>> que;
			que.push({ x, y });//访问到了谁，待会就遍历他的四个方向。
			visited[x][y] = true;//访问到了谁，visited赋值true
			while (!que.empty())//只要是队列不空，那就是要接着遍历这个元素的四周
			{
				//每次从队列中都要拿出新的，遍历新的四个方向。
				pair<int, int> cur = que.front();
				que.pop();//!这个别忘了！
				int curX = cur.first;
				int curY = cur.second;
				for (size_t i = 0; i < 4; i++)
				{
					int nextX = curX + dir[i][0];
					int nextY = curY + dir[i][1];
					//判断数组是否越界
					if (0 <= nextX && nextX < grid.size() && 0 <= nextY && nextY < grid[0].size())
					{
						//判断这个点4个方向都是陆地的点，然后不断的加到队列中，这样就能找到与一开始提供的xy是同一块岛屿的所有坐标。
						if (!visited[nextX][nextY] && grid[nextX][nextY] == 1)
						{
							are++;
							que.push({ nextX, nextY });
							visited[nextX][nextY] = true;
							grid[nextX][nextY] = mark;
						}
					}
				}
			}
			return are;
		}


		int largestIsland(vector<vector<int>>& grid) {
			int are = 0;//最后的面积
			int n = grid.size(), m = grid[0].size();
			vector<vector<bool>> visited = vector<vector<bool>>(n, vector<bool>(m, false));
			int mark = 1;//!一定要从1
			unordered_map<int, int>gridAre;//不同编号岛屿的面积
			bool isAllGrid = true; // 标记是否整个地图都是陆地
			//1、遍历图，然后记录下每个岛屿的面积，
			for (size_t i = 0; i < n; i++)
			{
				for (size_t l = 0; l < m; l++)
				{
					if (grid[i][l] == 0) isAllGrid = false;
					if (!visited[i][l] && grid[i][l] == 1) {
						mark++;
						gridAre[mark] = largestIsland_bfs(grid, visited, mark, i, l);
					}
				}
			}
			if (isAllGrid) return n * m; // 如果都是陆地，返回全面积
			//遍历上面步骤中，没有遍历的部分。 把接壤的地方都加上，这就是新的岛屿的面积。
			for (size_t i = 0; i < n; i++) {
				for (size_t l = 0; l < m; l++) {
					vector<bool> gridvisited(mark + 1, false);//！这个和题解不一样，这个更容易被想到
					if (!visited[i][l] && grid[i][l] == 0) {
						int temare = 1;//!别忘了初始是1!他自己本身的面积是1，别忘了加了
						for (size_t j = 0; j < 4; j++)
						{
							int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };//下 上 右 左
							int nextX = i + dir[j][0];
							int nextY = l + dir[j][1];
							//判断数组是否越界
							if (0 <= nextX && nextX < grid.size() && 0 <= nextY && nextY < grid[0].size())
							{
								int mark = grid[nextX][nextY];
								//如果新1，的下一个位置grid[nextX][nextX]的值是!=0 !=1 就是另一个岛屿.并且这个岛屿没有被加进去过。
								if (grid[nextX][nextY] != 0 && grid[nextX][nextY] != 1 && gridvisited[mark] == false)
								{
									temare += gridAre[mark];
									gridvisited[mark] = true;
								}
							}
						}
						are = max(are, temare);
					}
				}
			}
			return are;
		}


		/*
		127. 单词接龙
		参考：
			https://www.programmercarl.com/0127.%E5%8D%95%E8%AF%8D%E6%8E%A5%E9%BE%99.html#%E6%80%9D%E8%B7%AF
		其他：
			题目讲解，单词变化，每次只能变一个，每次从给的列表中去挑。
			开始单词不一定在单词列表中，但是结束单词必须在结束列表中。
		思路：
			这里无向图求最短路，广搜最为合适，广搜只要搜到了终点，那么一定是最短的路径。
			因为广搜就是以起点中心向四周扩散的搜索。
			为什么深搜直接出来的不是，这个我没明白
			？另外，他是如何保证是最短的距离的？
		*/
		int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
			//将单单词列表放到unordered_set中，是为了提高查找速度——这个单词有没有在wordList出现。
			unordered_set<string>wordSet(wordList.begin(), wordList.end());
			//如果结束单词没在结束列表中
			if (wordSet.find(endWord) == wordSet.end()) return 0;
			//为了保证每个单词只访问一次，也就是保证之前变化的就不再用了
			unordered_map<string, int> visitMap;//key是单词，int是距离
			 // 初始化visitMap
			visitMap.insert(pair<string, int>(beginWord, 1));
			queue<string> que;
			que.push(beginWord);


			while (!que.empty())
			{
				string word = que.front();
				que.pop();
				int pathLenth = visitMap[word];
				//开始对当前遍历到的单词，做变化。
				for (size_t i = 0; i < word.size(); i++)//对word的各个字符都做变化
				{
					string newWord = word;
					for (size_t l = 0; l < 26; l++)//变化的范围就是26个英文字母
					{
						newWord[i] = l + 'a';//从a开始，一个一个往上加
						if (newWord == endWord) return pathLenth + 1;//找到了结束单词，就该返回长度了
						//如果新单词在列表中出现了。并且之前没有访问过。
						if (wordSet.find(newWord) != wordSet.end() && visitMap.find(newWord) == visitMap.end())
						{
							visitMap.insert(pair<string, int>(newWord, pathLenth + 1));
							que.push(newWord);
						}
					}
				}
			}
			return 0;
		}

		/*
		841.钥匙和房间
		参考：
			https://www.programmercarl.com/0841.%E9%92%A5%E5%8C%99%E5%92%8C%E6%88%BF%E9%97%B4.html#%E6%80%9D%E8%B7%AF
		注意：
			!这个题目提示我们要注意就是：
			你的递归函数，是处理当前的节点；还是处理当前点之后的点。
			关于这个，我之前的题目中有注意到过。
			总的来说：
			1、在递归函数有专门结束递归的语句，就是处理的是当前的点
			 if (visited[key])
				return;
			2、而这种，则是在遍历中去赋值；则是处理下个节点。
			for (int key : keys) {
				if (visited[key] == false) {
					visited[key] = true;
					dfs(rooms, key, visited);
				}
			}
			！要注意的就是在调用的时候，如果是下面这种方式就要提前对结果++；
				或者做类似的处理。
		思路：
			本题目可以看成是一个有向图。
			从节点0出发，拿到所有的节点0的钥匙。
			从拿到的钥匙中，去到其他的房间，然后再拿到所有的钥匙，
			一直不断的往复。
			最后遍历这个图，查看是不是都遍历了，一旦有每遍历到的，返回false
		*/

		bool canVisitAllRooms_bfs(vector<vector<int>>& rooms)
		{
			vector<bool> visited(rooms.size(), false);
			visited[0] = true;

			queue<int>que;
			que.push(0);

			while (!que.empty())
			{
				int index = que.front();//第一个房间的下表
				que.pop();
				vector<int> keys = rooms[index];
				for (int key : keys)//遍历房间中的钥匙
				{
					if (!visited[key])
					{
						visited[key] = true;
						que.push(key);//把拿到的钥匙——也就是能到的数组下标放到que中
					}
				}
			}
			for (int signalVisit : visited)//遍历房间
			{
				if (signalVisit == false)
					return false;
			}
			return true;
		}
		bool canVisitAllRooms(vector<vector<int>>& rooms) {

			return canVisitAllRooms_bfs(rooms);

		}


		/*
		463. 岛屿的周长
		参考：
			https://www.programmercarl.com/0463.%E5%B2%9B%E5%B1%BF%E7%9A%84%E5%91%A8%E9%95%BF.html#%E6%80%9D%E8%B7%AF
		思路：
			不用dfs或者是bfs
			就单纯的遍历图，然后遍历到陆地后，
			遍历他的四周，如果满足条件，边数++
		*/
		int islandPerimeter(vector<vector<int>>& grid) {
			int direc[4][2] = { 0, 1, 1, 0, -1, 0, 0, -1 };
			int ret = 0;
			for (size_t i = 0; i < grid.size(); i++)
			{
				for (size_t l = 0; l < grid[0].size(); l++)
				{
					if (grid[i][l] == 1)//是“陆地”
					{
						for (int k = 0; k < 4; k++) {       // 上下左右四个方向
							int nextX = i + direc[k][0];
							int nextY = l + direc[k][1];
							// i在边界上,i在边界上, j在边界上,j在边界上, x,y位置是水域
							if (nextX < 0 || nextX >= grid.size() \
								|| nextY < 0 || nextY >= grid[0].size()\
								|| grid[nextX][nextY] == 0)
							{
								ret++;
							}
						}
					}

				}
			}
			return ret;
		}



		/**-------------------以下是并查集--------------------------- */
		/*
		并查集可以解决什么问题呢？
			并查集常用来解决连通性问题。
			大白话就是当我们需要判断两个元素是否在同一个集合里的时候，我们就要想到用并查集。
			并查集主要有两个功能：
			将两个元素添加到一个集合中。
			判断两个元素在不在同一个集合

		并查集主要有三个功能。

			寻找根节点，函数：find(int u)，也就是判断这个节点的祖先节点是哪个
			将两个节点接入到同一个集合，函数：join(int u, int v)，将两个节点连在同一个根节点上
			判断两个节点是否在同一个集合，函数：isSame(int u, int v)，就是判断两个节点是不是同一个根节点

		我自己：
			一般都是用在图的题目中。
		*/

		/*
		1971. 寻找图中是否存在路径
		参考：
			https://www.programmercarl.com/1971.%E5%AF%BB%E6%89%BE%E5%9B%BE%E4%B8%AD%E6%98%AF%E5%90%A6%E5%AD%98%E5%9C%A8%E8%B7%AF%E5%BE%84.html#%E6%80%9D%E8%B7%AF
		思路：

			思路大概就是：
			把有关联的数据通过“ father[v] = u;”这种方式联系起来。
			也就是串成一串。
			判断两个点在不在一个集合中——就是判断两个点的根节点是不是一样
			把两个点弄成一块，就是用这个公式实现“ father[v] = u;”。
		注意：
			在合并两个点到一个集合的时候，是两个“根节点”在合并。
			//father[vRoot] = uRoot;和father[uRoot] = vRoot;那种都行
		*/

		class Solution1 {//这里放这类，是为了防止函数冲突
		public:
			int n = 200005;
			vector<int>father = vector<int>(n, 0);//里面存的是数组的下表

			void init()//初始化，现在每个元素的都是保存的自己的坐标，这样就意味着他们只跟自己有关系。
			{
				//!!!注意这个n，每个题目中别忘了初始化了。
				//for (size_t i = 0; i < edges.size(); i++)最好改成这个
				for (size_t i = 0; i < n; i++)
					father[i] = i;
			}

			int find(int u)//用递归找到u的“根”，并且 else可以压缩路径，使这个“树”的高度变成1
			{
				if (u == father[u])
					return u;
				else
					return father[u] = find(father[u]);
			}

			bool isSame(int v, int u)
			{
				int vRoot = find(v);
				int uRoot = find(u);
				return vRoot == uRoot;
			}
			void join(int u, int v)
			{
				int vRoot = find(u);
				int uRoot = find(v);
				if (vRoot == uRoot)//如果两个要联系的节点，本来就是在一个“集合”中，就没有必要添加一块
					return;
				//father[v] = u;!!!这种写法是错的！！！！

				//!!在合并两个点到一个集合的时候，是两个“根节点”在合并。
				father[vRoot] = uRoot;//这样v和u就产生了关系，通过find(v)就能知道u是他的下一个点。随着不断的添加，这个“链条”也在慢慢的变化。
				//father[uRoot] = vRoot;这样写也行
			}
			bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
				init();
				for (size_t i = 0; i < edges.size(); i++)
				{
					join(edges[i][0], edges[i][1]);//对所有的点建立联系。
				}
				//建立所有的关系后，判断所给的点是不是有关系
				return isSame(source, destination);
			}



			/*
			684.冗余连接
			参考：
				https://www.programmercarl.com/0684.%E5%86%97%E4%BD%99%E8%BF%9E%E6%8E%A5.html#%E6%80%9D%E8%B7%AF
			思路：
				判断一条边的两个点是否在同一个集合中，
				如果在同一个集合，说明已经形成了回环。
				如果不在一个集合，说明这两个点在不同的集合，也就不会在这个集合中形成回环
				至于遍历顺序，要根据题目要求来走。
				本题目是要：“如果有多个答案，则返回数组 edges 中最后出现的那个”
				所以就是“正序”。
				比如abcd四条边形成了回环，遍历abc这三条边的时候，都没形成回环，
				当遍历d的时候，就形成了回环，那么就该返回d。
				反之“倒叙”，返回a。
			题目：
				如果有多个答案，则返回数组 edges 中最后出现的那个。
				比如例题2，感觉切34可以，但是最后返回14，是因为14是最后一个满足条件的在edges数组中
			其他：
				这个题目中用到的函数都和上面的一样，只有主函数不一样。
			*/
			vector<int> findRedundantConnection(vector<vector<int>>& edges) {
				init();
				for (size_t i = 0; i < edges.size(); i++)
				{
					//如果在同一个集合，说明已经形成了回环。 返回这两个点
					if (isSame(edges[i][0], edges[i][1]))
						return edges[i];
					//如果不在一个集合，说明这两个点在不同的集合，就把这两个点加一块
					join(edges[i][0], edges[i][1]);
				}
				//!!!!其实这个题目中，压根就不会走到这
				//写这个是为了保证编译能过去，
				//不会走到这是因为题目“给定往一棵 n 个节点的树中添加一条边后的图，这条边在树里之间是不存在的”，
				//对一个树而言，添加一条边肯定是会形成回环。所以题目中所给的就一定是“回环”。
				return {};//没有环，就返回空。
			}


			/*
			685.冗余连接II
			参考：
				https://www.programmercarl.com/0685.%E5%86%97%E4%BD%99%E8%BF%9E%E6%8E%A5II.html#%E6%80%9D%E8%B7%AF
			思路：
				题目中给的图像，一定是回环图像。
				因为他是额外的一条边，并且这个边的两点都在树上！
				一切的前提是建立在“回环图像”的基础上,并且回环只有一个！上个题目也符合要求
				既然是“回环图像”，并且只有一个回环。
				对于“有向图”而言（这也是题目为什么用有向图），他一定有“入度”
				从树上增加了一条边，
				数这个结构，正常来入度只有1（根节点是0），增加了一条边入度最多是2，不能是3的，
				有入度为1的情况，参考图片情况3.（从其他节点到根节点）（有可能有回环）
				有入度为2的情况，参考图片情况1,2.（一定有回环）
				有入度为3的情况吗？没有。（不存在这种情况）

				代码上的思路：
				有个倒叙是必须的，有些图在入度为2的情况下，删除哪个都行，所有一定要倒叙，删除最后出现的那个。
				上题，是正序是，因为遍历到最后环的最后最后一个边就行。没有什么删除

				入度为1并且出现回环的情况下，删除那个边就行，也就是这边的两点在一个集合上。
				也就是上题的情况

			题目：
				题目中给的图像，一定是回环图像。
				因为他是额外的一条边，并且这个边的两点都在树上！
			*/
			static const int N = 100;//!这里必须是静态常量，静态保证编译的时候出结果，常量保证能让N在编译的时候用来初始化数组。

			//入度为1的时候，返回删除那条构成回环的边
			vector<int> getRemoveEgde(vector<vector<int>>& edges)
			{
				init();
				for (size_t i = 0; i < edges.size(); i++)
				{
					if (isSame(edges[i][0], edges[i][1]))
						return edges[i];
					join(edges[i][0], edges[i][1]);
				}
				return {};//它的入度是1，一定不会走到这
			}


			//入度为2的时候，判断删除一条边后，是不是一个正确的树
			bool isTreeAfterRemoveEdge(vector<vector<int>>& edges, int ruduEdgeIndex)
			{
				init();
				for (size_t i = 0; i < edges.size(); i++)
				{
					if (i == ruduEdgeIndex)//当前遍历的入点为传进来的这个“入点”下标
						continue;//就不往图里加
					if (isSame(edges[i][0], edges[i][1]))
						return false;
					join(edges[i][0], edges[i][1]);
				}
				return true;
			}

			vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
				n = edges.size(); // 边的数量!!!!这个别忘了，要不然init()函数中的for遍历次数不对。
				int InDegree[N];//每个点的入度
				for (size_t i = 0; i < edges.size(); i++)
				{
					InDegree[edges[i][1]]++;//下标是后面的点。
				}
				vector<int>rudu2EdgesIndex;//保存“入度”为2的!这个边的下标！！！！
				//!!!!这个地方一定是倒叙！！！！
				//核心是为了保证返回的是在二维数组中靠后的答案。
				for (int i = edges.size() - 1; i >= 0; i--)
				{
					if (InDegree[edges[i][1]] == 2)
						rudu2EdgesIndex.push_back(i);//!!虽然这样遍历，但是上面说过“入度”为2的只有一个
				}
				//如果有入度为2的情况出现，那么要删除的就是这个点的“入度”的两条边的其中一个。
				//至于是删除前面的还是后面的不一定，所以要通过函数来测试。
				if (rudu2EdgesIndex.size() > 0)
				{
					if (isTreeAfterRemoveEdge(edges, rudu2EdgesIndex[0]))
						return edges[rudu2EdgesIndex[0]];
					return edges[rudu2EdgesIndex[1]];
				}

				//剩下的情况就是入度为1的情况，这时候要删除的边就是
				//哪个边构成了回环，就删除哪个。和上题的情况一样。
				return getRemoveEgde(edges);
			}

		};




		void test()
		{
			string str = "bbbab";
			vector<	vector<int> > graph{ {0,0,1,0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},{0,1,1,0,1,0,0,0,0,0,0,0,0},{0,1,0,0,1,1,0,0,1,0,1,0,0} };
			vector<	vector<char> > graphc{ {'X','X','X','X'},{'X','O','O','X'},{'X','X','O','X'},{'X','O','X','X'} };
			vector<	vector<int> > graph1{ {0,0,0,0},{1,0,1,0},{0,1,1,0},{0,0,0,0} };
			vector<	vector<int> > graph2{ {1,1}, {1,0} };
			vector<	vector<int> > graph3{ {4,3},{1,4},{4,8},{1,7},{6,4},{4,2},{7,4},{4,0},{0,9},{5,4} };
			vector<	vector<int> > graph4{ {0,7},{0,8},{6,1},{2,0},{0,4},{5,8},{4,7},{1,3},{3,5},{6,5} };
			vector<int> dp1{ 1,3,4,2 };
			int Start = GetTickCount();
			//cout << largestIsland(graph2) << endl;
			int Stop = GetTickCount();
			cout << "消耗时间" << Stop - Start << endl;
			Solution1 A;

			cout << A.validPath(10, graph3, 5, 9) << endl;



			vector<int> ret = A.findRedundantDirectedConnection(graph4);
			cout << ret[0] << endl;
			//= numIslands(graph1);
			/*for (size_t i = 0; i < ret.size(); i++)
			{
				for (size_t l = 0; l < ret[i].size(); l++)
				{
					cout << ret[i][l] << " ";
				}
				cout << endl;
			}*/
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

	String_Array::Solution tree;
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