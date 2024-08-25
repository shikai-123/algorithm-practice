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





//字符串和数组
namespace String_Array
{
	class Solution {
	public:

		/*
		88. 合并两个有序数组
		*/
		//思路就是 nums1数组最后的位置一定是0，没有0就不用排序了。 最后是0的话，就把0替换成nums2 然后再排序  他的编译器也会优化。用nums1.size() 不会造成性能损失。
		//时间复杂的不行, 光sort就n*log2(n); 时间复杂度肯定不行
		void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
			unsigned char size = nums1.size();
			unsigned char  zeroNums1 = size - m;

			for (unsigned char i1 = 0; i1 < zeroNums1; i1++)
			{
				if (nums1[size - i1 - 1] == 0)
				{
					nums1[size - i1 - 1] = nums2[0];
					nums2.erase(nums2.begin());
				}
			}
			sort(nums1.begin(), nums1.end());
		}

		/*
		88. 合并两个有序数组
		参考:
			https://leetcode.cn/problems/merge-sorted-array/submissions/466208834/
		思路:
			先说题目,nums1的数组前面是数,后面全部是0;并且0的数量就是nums2的数量.
			题目要求把nums2放到nums1中,且正好是正序的.
			注意m是nums1中非0元素的数量,n是nums2中元素数量
			然后比较nums1中非0元素和nums2的元素(出现0也无所谓)的大小,谁大谁先挪到nums1的后面
			直到把这两个数组的元素都遍历完毕,
			最后得到的数组nums1一定是正序的
		*/
		void merge1(vector<int>& nums1, int m, vector<int>& nums2, int n) {
			int i = nums1.size() - 1;//比较大小后,要放的最终位置下标
			m--;//要被挪的nums1的元素下标
			n--;//要被挪的nums2的元素下标
			while (n >= 0) {
				while (m >= 0 && nums1[m] > nums2[n]) {
					swap(nums1[i--], nums1[m--]);
				}
				swap(nums1[i--], nums2[n--]);
			}
		}

		//!!这种从逻辑上没有啥问题,但是架不住题目中有m=0的测试样例,第一个while直接进不去,然后就ac不了
		void merge2(vector<int>& nums1, int m, vector<int>& nums2, int n) {
			int i = nums1.size() - 1;
			m--;
			n--;
			while (m >= 0) {//一定要是先m再m,要不然就会出现上面说的问题
				while (n >= 0 && nums1[m] < nums2[n]) {
					swap(nums1[i--], nums2[n--]);
				}
				swap(nums1[i--], nums1[m--]);
			}
		}



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



		/*
		189. 轮转数组
		题意：
			[1,2,3,4,5,6,7], k = 3 轮转3次，输出: [5,6,7,1,2,3,4]
		参考：

		*/
		void rotate(vector<int>& nums, int k) {
			if (nums.size() == 1)
				return;
			if (nums.size() < k)
				k = k % nums.size();
			vector<int> nums1 = nums;
			for (int i = 0; i < nums1.size() - k; i++)
				nums[i + k] = nums1[i];
			for (int i = 0; i < k; i++)
				nums[i] = nums1[nums1.size() - k + i];
		}

		//二刷——唯一要注意的就是数组是往右转的，是把后面k个数据移动；所以k的用法都是从end()-k, 而不是begin()+k.这个是不对的。
		void rotate2(vector<int>& nums, int k) {
			k = k % nums.size();
			vector<int> tmp(nums.end() - k, nums.end());
			tmp.insert(tmp.end(), nums.begin(), nums.end() - k);
			nums = tmp;
			return;
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

		/*
		238. 除自身以外数组的乘积
		题意：
			[1,2,3,4] ，返回num[i]之外的所有元素的乘机。不能使用除法。
		参考：
			https://leetcode.cn/problems/product-of-array-except-self/solutions/274152/cjian-ji-dai-ma-shuang-zhi-zhen-6xing-dai-ma-by-or/?envType=study-plan-v2&envId=top-100-liked
			之前的方法复杂，现在换个的简单的。
			利用双指针的思路
		思路:
			首先说明的是,这个双指针是两端往中间走,但不是走到中间就停止了,而是走到最后.
			两个指针不断的往中间移动,
			具体看注释吧
		*/
		vector<int> productExceptSelf(vector<int>& nums) {
			int rightValue = 1, lightValue = 1;//数组左右元素左侧右侧的累乘积
			vector<int>ret(nums.size(), 1);//存放结果的数组，

			for (size_t l = 0, r = nums.size() - 1; l < nums.size(); l++, r--)
			{
				ret[l] = lightValue * ret[l];//首先,把lightValue理解为上次的累乘积,其实他就是累成积.
				ret[r] = rightValue * ret[r];//当前的元素乘以上次的累成积,得到这个位置的结果
											 //这里的ret[r]积总是从右往左的,ret[l]是从左往右的,因为两个指针走到最后停止,ret[r]会再次和ret[l]的一些数据再次相乘.反之亦然!

				rightValue = rightValue * nums[r];//更新左右的累成积
				lightValue = lightValue * nums[l];
			}
			return ret;
		}

		//238. 除自身以外数组的乘积--二刷
		vector<int> productExceptSelf2(vector<int>& nums) {
			int rightValue = 1, leftValue = 1;
			vector<int> ret(nums.size(), 1);//别忘了初始化大小,要不然越界
			for (int l = 0, r = nums.size() - 1; l < nums.size(); l++, r--) {//别忘了r的初始大小是size()-1 要不然越界

				ret[l] = ret[l] * leftValue;//更新数组结果
				ret[r] = ret[r] * rightValue;

				leftValue = leftValue * nums[l];
				rightValue = rightValue * nums[r];
			}
			return ret;
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

		//二刷，我想把if的条件换成==0，但是我发现我调的代码过不去，就算了。还是老办法
		void moveZeroes2(vector<int>& nums) {
			int putPos = 0;
			for (size_t i = 0; i < nums.size(); i++) {
				if (nums[i] != 0) {
					swap(nums[i], nums[putPos]);
					putPos++;
				}
			}
			return;
		}



		/*
		560. 和为 K 的子数组
		题目：
			前缀和要不是明白，看我的笔记。
			这个题目和437. 路径总和 III非常相似，要对着看
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
			int sum = 0;
			for (auto num : nums) {
				sum += num;
				if (umap.find(sum - k) != umap.end()) {//！！这个和下面的地方一定是sum - k，反过来就错
					ret += umap[sum - k];
				}
				umap[sum]++;
			}
			return ret;
		}



		//560. 和为 K 的子数组---二刷
		int subarraySum2(vector<int>& nums, int k) {
			int ret = 0;
			unordered_map<int, int> mSum;//key是前缀和,value是每个和出现的次数
			int sum = 0;
			mSum[0] = 1;//!!这个少了过不去!!
			for (int num : nums) {
				sum += num;
				if (mSum.find(sum - k) != mSum.end())//说明数组中找到了和k子数组
					ret += mSum[sum - k];//既然找到了子数组,那么符合要求的结果的次数++

				mSum[sum]++;
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

		//41. 缺失的第一个正数--二刷
		int firstMissingPositive1(vector<int>& nums) {
			for (size_t i = 0; i < nums.size(); i++)
			{
				//假设源数组是312(顺序不重要);就是想构建一个123,这样的数组,凡是没在应该的位置,都要移动.方便理解,长度为3的数组,元素123都是满足"范围条件".
				while (nums[i] >= 1 && nums[i] <= nums.size() && nums[i] != nums[nums[i] - 1])// nums[i] != i + 1这不对!必须是这个,[1,1]这种情况下,while就会卡死在这
				{
					swap(nums[i], nums[nums[i] - 1]);//nums[i]是当前的元素值, nums[nums[i] - 1]当前这个元素应该在的那个位置上的元素的值.如果不相等那么就要移动.想等了就没必要移动,
				}
			}
			for (size_t i = 0; i < nums.size(); i++)//判断移动后的数组中的哪个元素没有在合适的位置!就返回这个确实的元素的值.
			{
				if (nums[i] != i + 1)
					return i + 1;
			}
			return *(nums.end() - 1) + 1;//!!别忘了+1,什么都不缺的时候,返回的是最后的一个元素后面,而不是最后的元素.
		}


		/*
		415. 字符串相加
		参考:
			https://leetcode.cn/problems/add-strings/solutions/12250/add-strings-shuang-zhi-zhen-fa-by-jyd/
		思路:
			和"2. 两数相加"相似.
			具体思路看题解吧
		*/
		string addStrings(string num1, string num2) {
			std::string res;
			int i = num1.length() - 1, j = num2.length() - 1, carry = 0;
			while (i >= 0 || j >= 0) {
				int n1 = i >= 0 ? num1[i] - '0' : 0;
				int n2 = j >= 0 ? num2[j] - '0' : 0;
				int tmp = n1 + n2 + carry;
				carry = tmp / 10;
				res.push_back(tmp % 10 + '0');//tmp % 10 + '0' 其实就是tmp % 10这个数的ASCII
				i--;
				j--;
			}
			if (carry > 0) {
				res.push_back(carry + '0');
			}
			std::reverse(res.begin(), res.end());
			return res;
		}

		/*
		8. 字符串转换整数 (atoi)
		参考:
			https://leetcode.cn/problems/string-to-integer-atoi/solutions/2361399/8-zi-fu-chuan-zhuan-huan-zheng-shu-atoiq-a2e8/
		思路:
			先去掉空格
			再判断符号
			然后再计算值
			再判断判断越界不
			最后返回值
		*/
		int myAtoi(string s) {
			int res = 0, bndry = INT_MAX / 10;//boundary边界;一定要/10;在for中,每次*10.超了边界再返回就晚了
			int i = 0, sign = 1;//根据题目,没有符号,默认是正数
			if (s.size() == 0) return 0;
			while (s[i] == ' ')//去掉前面的空格
				if (++i == s.size()) return 0;
			if (s[i] == '-') sign = -1;
			if (s[i] == '-' || s[i] == '+') i++;//去掉符号
			for (i; i < s.size(); i++) {
				if (s[i] < '0' || s[i] > '9') break;
				if (res > bndry || res == bndry && s[i] > '7')//看图就明白.
					return sign == 1 ? INT_MAX : INT_MIN;//超了边界,根据符号,返回对应的最大值
				res = res * 10 + (s[i] - '0');
			}
			return sign * res;
		}


		/*
		165. 比较版本号
		参考:
			https://leetcode.cn/problems/compare-version-numbers/solutions/969237/bi-jiao-ban-ben-hao-shuang-zhi-zhen-suan-bcv7/
		思路:
			计算两个..之前的数据大小,然后比较大小.一直比下去
		*/
		int compareVersion(string v1, string v2) {
			int i = 0, j = 0;
			while (i < v1.size() || j < v2.size())//每次while,都是计算两个..之前的数据大小,然后比较大小
			{
				long long num1 = 0, num2 = 0;   //数据加强了，这里要用long long
				while (i < v1.size() && v1[i] != '.') num1 = num1 * 10 + v1[i++] - '0';
				while (j < v2.size() && v2[j] != '.') num2 = num2 * 10 + v2[j++] - '0';
				if (num1 > num2) return 1;
				else if (num1 < num2) return -1;
				i++, j++;
			}
			return 0;//比较完了,上面没有return,就说明两个值是相等的
		}

		/*
		LCR 140. 训练计划 II
		很简单,就是快慢指针;
		*/
		ListNode* trainingPlan(ListNode* head, int cnt) {
			ListNode *fast = head, *slow = head;
			for (int i = 0; i < cnt; i++)
				fast = fast->next;
			while (fast != nullptr) {
				fast = fast->next;
				slow = slow->next;
			}
			return slow;
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
		参考：
			https://leetcode.cn/problems/container-with-most-water/solutions/11491/container-with-most-water-shuang-zhi-zhen-fa-yi-do/?envType=study-plan-v2&envId=top-interview-150
		题意：
			数组中的不同的元素代表容器的高度，两个元素的举例就是底的长度。然后求出“最大”的体积
		思路：
			 和“单调栈的接雨水”的题目，不一样，这个使用双指针来解决。
			 首先，两个边分别在数组两边。然后向内移动。容器的两个边，决定体积的一定是较短的那个边。
			 向内移动长边，遇到了更短的边，体积肯定减少。碰到了高边，短边还是那个高度，并且底还减小了，所以还是减小。
			 向内移动短边，万一遇到长边，体积才有增大的可能。
			 直到两个边相遇就退出
		*/
		int maxArea(vector<int>& height) {
			int i = 0;
			int l = height.size() - 1;
			int maxAer = 0;
			while (true)
			{
				if (i == l)
					return  maxAer;
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

		//二刷
		int maxArea2(vector<int>& height) {
			int L = 0, R = height.size() - 1;
			int maxAre = 0;
			while (true)
			{
				maxAre = max(maxAre, (R - L)*min(height[L], height[R]));
				if (L == R)
					return maxAre;
				else if (height[L] > height[R]) {//如果左边大于右边，移动右边
					R--;
				}
				else {//如果右边大于左边，移动左边
					L++;
				}
			}
		}


		/*
		15. 三数之和
		参考：
			https://www.programmercarl.com/0015.%E4%B8%89%E6%95%B0%E4%B9%8B%E5%92%8C.html#%E6%80%9D%E8%B7%AF
		题意：
			返回所有和为 0 且不重复的三元组。nums = [-1,0,1,2,-1,-4] 输出[[-1,-1,2],[-1,0,1]]。有两个-1，,可以重复
		思路：
			因为题目要求从数组中取出的数要保持不重复。所以哈希的方法不合适，具体看链接。
			（他这个重复，包括同一个元素不能用两边，两个相同的元素也不能出现。即使有俩个-1；-101，-101这两个也不同，其实看代码编的题目，所以这个重复的规则才这么绕）
			所以用双指针
			!!先排序，方便后序处理。
			其实是三指针，一个在最左边a，一个挨着最左边的右边b，一个在最右边c
			在保持a不变的情况下，判断a+b+c的情况，分别移动b或c
			b和c都移动完了，然后移动a
			！！重点是去重，总之一句话概括。
			在遍历的时候，a后面的相同的数值，都要跳过；同理bc都是一样的，跳了之后，后面就是新数据，然后开始下一轮的判断
		*/
		vector<vector<int>> threeSum(vector<int>& nums) {
			sort(nums.begin(), nums.end());
			vector<vector<int>>ret;
			int left = 0, right = 0;
			for (size_t i = 0; i < nums.size(); i++) {
				if (nums[i] > 0) return ret;//如果排序后一开始就大于0，说明i后面就都大于0;后面没有在遍历的必要！！！
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
						//!!注意这里是left+1，right - 1。就是让左边的元素和它后面相比，如果相同不满足题意，往后再移动一位
						while (left < right&& nums[left] == nums[left + 1])
							left++;
						while (left < right&& nums[right] == nums[right - 1])
							right--;
						//上面去重完毕后，比如112，现在去重到了最后的1，left++。才能到2开始新的一轮数据判断
						left++;
						right--;
					}
				}
			}
			return ret;
		}

		//二刷
		vector<vector<int>> threeSum2(vector<int>& nums) {
			if (nums.empty())return {};
			vector<vector<int>>ret;
			sort(nums.begin(), nums.end());
			if (nums[0] > 0)return {};//排序后，第一个就大于0。肯定不行
			for (size_t i = 0; i < nums.size(); i++) {
				if (i > 0 && nums[i] == nums[i - 1]) continue;//对a去重。别忘了
				int  left = i + 1, right = nums.size() - 1;
				//上面确定了i的位置，下面b和c，用while循环
				while (left < right) {
					if (nums[i] + nums[left] + nums[right] > 0)//三数和大于0.右边的数最大，右边往里面移动
						right--;
					else if (nums[i] + nums[left] + nums[right] < 0)
						left++;
					else {//三数和==0.
						ret.push_back({ nums[i] , nums[left] , nums[right] });
						//去重,!!用while!!更重要的是，要在这个else中，不能放在外边！
						//按照逻辑来说，这里就是三数和==0。b后面和c前面相同的元素都能使三数和==0，但是元素重复了，所以都跳过
						while (left < right&&nums[left] == nums[left + 1])
							left++;
						while (left < right&&nums[right] == nums[right - 1])
							right--;
						//!这个地方容易忘记，去重完毕，比如112 ，left++，才能到新的数据2。
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


		/*
		912. 排序数组
		参考:
			https://blog.csdn.net/justidle/article/details/104203963
		说明:
			它的思路在选基数的时候都是数组第一个,这样的话时间上过不去.
			我换成了随机选择就没有问题!
			另外,思路和他链接中的思路不一致.
			但是代码能过AC

		思路:
			随机挑选一个节点,把这个节点挪到最左边(这个我没有很好的解释; 但是所有的快排基准点都是左边的,现在是随机选择的所以把这个点和最左边的点交换一下)
			先右边操作(别错了)
			右边满足>=base的,下标就不断的移动.直到出现了不满足的情况.
			左边满足<=base的,下标就不断的移动.直到出现了不满足的情况.
			然后交换这个两个不满足条件的元素.然后 交换这两个元素.
			然后不断的循环这个操作.直到本层递归的while结束.
			这个时候整个数组,i左边是小于base的.i右边是大于base的.
			然后把最左边的元素(base)和下标i的元素交换.
			然后进入下层递归!

		易错点:
			和base比较的时候,一定时>=或<=;哪个=缺失了,都报错
		*/
		void QuickSort(vector<int>& nums, int left, int right) {
			int i = left;
			int j = right;
			if (i >= j) {
				return;
			}
			int x = left + rand() % (right - left + 1);//在left和right之间随机选择一个; 举例下标012; 2-0=2,然后取余是取不到2.所以加1
			swap(nums[left], nums[x]);//!!把随机点和左边的节点交换一下!一定要换,否则报错
			int base = nums[left];
			while (i != j) {
				while (nums[j] >= base && i < j) {
					j--;
				}
				while (nums[i] <= base && i < j) {
					i++;
				}
				if (i < j) {
					swap(nums[i], nums[j]);
				}
			}
			swap(nums[left], nums[i]);// 将基准base放于自己的位置，（第i个位置）.因为上面while已经基于base的大小,分了两部分,i左边是小于base的.i右边是大于base的.所以这个时候base应该从最左边移动到中间来
			QuickSort(nums, left, i - 1);
			QuickSort(nums, i + 1, right);
		}

		/*
		912. 排序数组----推荐用这个代码,毕竟和文章中的思路是一样的!
		参考:
			只参考这篇文章的思路.代码不参考.因为文章的代码和他说的思路不一致.我写这个才是文章中的思路
			https://blog.csdn.net/justidle/article/details/104203963
		思路:
			看文章中的吧,这个花了我很长时间了,不具体写了
		*/
		void quickSort(vector<int>& nums, int left, int right) {
			// 数组有多个元素进行排序
			if (left < right) {
				int i = left; // 左指针
				int l = right;  // 右指针

				int x = left + rand() % (right - left + 1);
				swap(nums[left], nums[x]);
				int base = nums[left];

				while (i < l) {
					while (i < l && nums[l] >= base) {// 从右向左找，比base大，right--
						l--;
					}
					nums[i] = nums[l];// 比base小，替换left所在位置的数字

					while (i < l && nums[i] <= base) {// 从左向右找，比base小，left++
						i++;
					}
					nums[l] = nums[i];// 比base大，替换right所在位置的数字
				}
				nums[i] = base; // 此时left=right，用base替换这个位置的数字

				quickSort(nums, left, i - 1);// 排列比base小的数字的数组
				quickSort(nums, i + 1, right);// 排列比base大的数字的数组
			}
		}

		vector<int> sortArray(vector<int>& nums) {
			quickSort(nums, 0, nums.size() - 1);
			return nums;
		}




		void test()
		{
			vector<int> nums{ 1,-1,-1,0 };
			vector<vector<int>>ret = threeSum2(nums);
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
		参考：
			https://leetcode.cn/problems/longest-substring-without-repeating-characters/solutions/2361797/3-wu-zhong-fu-zi-fu-de-zui-chang-zi-chua-26i5/?envType=study-plan-v2&envId=top-100-liked
		思路：
			滑动窗口+哈希表
			滑动窗口不断的往后移动,然后一旦在滑动窗口中发现了重复的元素,左边界要更新
			然后不断的计算最大的ret,然后返回ret;
			用abba来举例最合适。
			遍历到第一个b的是时候，ret = 1-（-1）=2；能够计算出准确的值，“ ”这样的也能计算出正确的值，“abc”这样也能计算出正确的值
			遍历到第二个b的时候，左边界坐标更新到第一个b的位置.也就是1；所以L=1;  ret=max（2,2-1）
			遍历到最后一个a的时候，如果不用l = max(l, umap[s[cur]]);而是:l = umap[s[cur]];肯定不行，这个时候左边界l就=0了，所以该是l = max(l, umap[s[cur]]);
		*/
		int lengthOfLongestSubstring(string s) {
			int ret = 0;
			int l = -1;//滑动窗口的左边，初始化-1是因为s会是一个“ ”，带空格的字符。要求结果返回1
			unordered_map<char, int> umap;//umap中放元素和对应的下标。里面始终放不重复的子串
			for (int cur = 0; cur < s.size(); cur++) {
				if (umap.find(s[cur]) != umap.end())//如果umap中找到了已经存在的字符，说明滑动窗口的左边需要往前移动。
					l = max(l, umap[s[cur]]);//更新左边界的位置到两个重复字符的中的那个下标更靠右(更大)的位置,来保证滑动窗口中没有重复字符.
				umap[s[cur]] = cur;//无论什么情况，当前字符串的下标都要更新
				ret = max(ret, cur - l);//不用+1；理解1：在计算的时候,l是左边界的左边;理解2：左边界都是更新到和右边界相同的字符出，比如abca，左边界和右边界都是在a。那么长度就是3-0=3；
			}
			return ret;
		}

		//二刷
		int lengthOfLongestSubstring2(string s) {
			int ret = 0;
			int l = -1;
			unordered_map<char, int> umap;//每个字符串的最靠右的下标 chat字符串 int下标
			for (int cur = 0; cur < s.size(); cur++)
			{
				if (umap.find(s[cur]) != umap.end())
					l = max(l, umap[s[cur]]);
				umap[s[cur]] = cur;
				ret = max(ret, cur - l);
			}
			return ret;
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
		题意:
			返回s中,能包含(覆盖)t的最小的字串
		参考:
			https://leetcode.cn/problems/minimum-window-substring/solutions/872360/leetcode-76-zui-xiao-fu-gai-zi-chuan-cja-lmqz/?envType=study-plan-v2&envId=top-interview-150
		思路：
			如果hs哈希表中包含ht哈希表中的所有字符，并且对应的个数都不小于ht哈希表中各个字符的个数，那么说明当前的窗口是可行的，
			注意一下几个点:
			1.它的滑动窗口的大小不是固定的.
			2.判断都是hs和ht的判断
		*/
		string minWindow(string s, string t) {
			unordered_map<char, int> hs;//hs哈希表维护的是s字符串中滑动窗口中各个字符出现多少次
			unordered_map<char, int> ht;//ht哈希表维护的是t字符串各个字符出现多少次。
			for (auto c : t)
				ht[c] ++;//遍历t字符串，用ht哈希表记录t字符串各个字符出现的次数。
			string res;
			int cnt = 0;
			for (int l = 0, r = 0; r < s.size(); r++)//j指针用于收缩窗口，i指针用于延伸窗口，则区间[j,i]表示当前滑动窗口。
			{
				hs[s[r]] ++;//每次向右扩展滑动窗口一步，相当于滑动窗口维护的字符数加一，即hs[s[i]]++。
				if (hs[s[r]] <= ht[s[r]]) //对于新加入的字符s[i],如果hs[s[i]] <= ht[s[i]]，说明当前新加入的字符s[i]是必需的.也就是滑动窗口中的某个字符的数量还没有t中的多,cnt++的含义就是相当于
					cnt++;//只要t中存在这个字符串ht[s[i]]就不会为0,那么hs[s[i]] <= ht[s[i]]就说明,滑动窗口中对应的某个字符是少于t中的数量的.此时cnt++,来表明

				while (hs[s[l]] > ht[s[l]])//!!必须while,if不行!!
					hs[s[l++]] --;//这个不是传统的滑动窗口那种距离固定的,它的左边界的移动条件是,当右边界中第一次出现了左边界对应的重复字符后,左边界才开始移动.
								  //左边界不断的移动,左边界对应的字符不断的变化,不断的判断左边界的字符和t中的数量问题.

				if (cnt == t.size()) {
					if (res.empty() || r - l + 1 < res.size())//1.当res从来没有被赋值的时候，2.新的滑动窗口中符合条件的字符，别上次还小的时候
						res = s.substr(l, r - l + 1);
				}
			}
			return res;
		}




		//76. 最小覆盖子串---二刷
		string minWindow2(string s, string t) {
			string ret;
			map<char, int>ms;//每个字符的数量
			map<char, int>mt;
			int cnt = 0;//滑动窗口中拥有的t所有的字符的数量
			for (char c : t)
				mt[c]++;

			for (size_t l = 0, r = 0; r < s.size(); r++)
			{
				ms[s[r]]++;
				if (ms[s[r]] <= mt[s[r]])//!这里是<=,不是<就行了.因为mt[s[r]]++;在上面,假设mt是2,ms现在加完之后为2了,这个也得进这个if
					cnt++;

				while (ms[s[l]] > mt[s[l]])
					ms[s[l++]]--;

				if ((t.size() == cnt) && (ret.empty() || r - l + 1 < ret.size()))//别忘了.size() == cnt
					ret = s.substr(l, r - l + 1);
			}
			return ret;
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
			vector<int>vs(26, 0), vp(26, 0);//vp的长度也是26，跟p的长度无关，是根据26个字母来决定的 v是vec,vs是装s的vec,vp是装p的vec;
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



		//二刷
		vector<int> findAnagrams1(string s, string p) {
			vector<int> ret;
			vector<int> vp(26);//下标是每个字母,对应的元素值是出现次数
			vector<int> vs(26);//这里用int,有的出现次数多,

			for (auto c : p)
				vp[c - 'a']++;

			for (size_t i = 0; i < s.size(); i++)
			{
				vs[s[i] - 'a']++;
				if (i > p.size() - 1)//-1是因为i是下标  后面比较的是size 比如长度3的情况. 第四个元素下标是3,然后3>2就满足删除的条件
					vs[s[i - p.size()] - 'a']--;//i-p.size() 是得到滑动窗口左侧的元素位置
				if (vs == vp)//两者相等,说明在关系顺序的情况下,两个数组含有的元素是一样的
					ret.push_back(i - p.size() + 1);//还是按p的长度为3举例子.当i为2的时候,有三个元素,假设这三个元素都满足了.这个时候ret应该把0插进去;2-3=-1.然后加上1才能符合
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
		题意：
			请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。
		参考：
			https://leetcode.cn/problems/spiral-matrix/solutions/2362055/54-luo-xuan-ju-zhen-mo-ni-qing-xi-tu-jie-juvi/?envType=study-plan-v2&envId=top-interview-150
		思路：
			思路很简单，既然是“顺时针螺旋顺序”，那么就先从左到右，从上到下。。这么一圈绕，
			比如先来一个“从左到右”，接着“从上到下”，这里要注意的就是上边界要先++再用。
			因为从上往下走的时候，就要忽略第一个，所以加加
			最后，两个边界已经不和常理了，就退出。比如左边界和右边界重合还没事，因为这个时候还能用这个重合的元素做边，当两个边界背离的时候，就不行了。


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
					res.push_back(matrix[t][i]);

				if (++t > b) break;//！先++t在用，是因为上边界被从左到右用了，然后从上往下走的时候，就要忽略第一个，所以加加
				for (int i = t; i <= b; i++) // top to bottom
					res.push_back(matrix[i][r]);

				if (l > --r) break;
				for (int i = r; i >= l; i--) // right to left
					res.push_back(matrix[b][i]);

				if (t > --b) break;
				for (int i = b; i >= t; i--)  // bottom to top
					res.push_back(matrix[i][l]);
				if (++l > r) break;
			}
			return res;
		}

		//二刷
		vector<int> spiralOrder2(vector<vector<int>>& matrix) {
			int top = 0;
			int bottom = matrix.size() - 1;
			int l = 0;
			int r = matrix[0].size() - 1;
			vector<int> ret;
			while (true)
			{
				//从左到右
				for (int i = l; i <= r; i++)
					ret.push_back(matrix[top][i]);

				//从上往下
				if (++top > bottom)break;//!!!!注意所有的if都是先++或者——
				for (int i = top; i <= bottom; i++)
					ret.push_back(matrix[i][r]);

				//从右往左
				if (--r < l)break;
				for (int i = r; i >= l; i--)
					ret.push_back(matrix[bottom][i]);

				//从下往上
				if (--bottom < top)break;
				for (int i = bottom; i >= top; i--)
					ret.push_back(matrix[i][l]);

				//！！别忘了从左到右
				if (++l > r)break;

			}
			return ret;
		}


		/*
		48. 旋转图像
		题意：
			就是把一个“方形”矩阵，旋转90度
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
			while (pos1 < pos2)//pos1 < pos2这个时候说明还是可以的，pos1 == pos2的时候，说明已经到了矩阵的中点，这个时候就不需要移动了。
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
					matrix[pos1 + addr][pos2] = temp;//
					addr++;
				}
				/*进入新的内圈就是pos1++,pos2--*/
				pos1++;
				pos2--;
			}
		}

		//二刷
		/*
		这个题目写法是这样，先写边角4个点的移动，比如
		matrix[pos1][pos1 ] = matrix[pos2][pos1];//左下到左上
		移动完毕后，在加上addr，至于是加还是减，到时候具体分析。
		移动的顺序，要按照下面的顺序，也就是“逆时针”的方向
		*/
		void rotate2(vector<vector<int>>& matrix) {
			int pos1 = 0;
			int pos2 = matrix.size() - 1;
			while (pos1 < pos2) {
				int addr = 0;
				while (pos1 + addr < pos2) {//pos1 + addr < pos2！别忘了这个条件了。
					int tmp = matrix[pos1][pos1 + addr];
					matrix[pos1][pos1 + addr] = matrix[pos2 - addr][pos1];//左下到左上
					matrix[pos2 - addr][pos1] = matrix[pos2][pos2 - addr];//右下到左下
					matrix[pos2][pos2 - addr] = matrix[pos1 + addr][pos2];//右上到右下
					matrix[pos1 + addr][pos2] = tmp;//左上到右上
					addr++;
				}
				pos1++; pos2--;
			}
			return;
		}



		/*
		73. 矩阵置零
		参考：
			https://leetcode.cn/problems/set-matrix-zeroes/?envType=study-plan-v2&envId=top-100-liked
			这是空间复杂度为1的题解，也就是二刷的思路。
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
		二刷，换成空间复杂度为1的算法，代码长点思路很简单
		题意：
			矩阵中元素是0，所在的行和列都要被置0；
		参考：
			https://leetcode.cn/problems/set-matrix-zeroes/?envType=study-plan-v2&envId=top-100-liked
		思路：
			核心：矩阵中存在了一个0， 那么这个0所在的行、列的首行首列要置0，来记录这一行列要置0；
			因为第一行列中的元素被置0了，所以你无法判断一开始的时候它是否存在0，所以你要单独记录它们是否存在0，然后后期单独对首行首列处理。
			1、记录第一行列中是否有0
		*/
		void setZeroes2(vector<vector<int>>& matrix) {
			bool row0 = false, col0 = false;//变量的意思：行0是不是要清零
			int row = matrix.size();
			int col = matrix[0].size();

			//1、记录第一行列中是否有0
			for (size_t i = 0; i < col; i++) {
				if (matrix[0][i] == 0) {
					row0 = true;
					break;
				}
			}
			for (size_t i = 0; i < row; i++) {
				if (matrix[i][0] == 0) {
					col0 = true;
					break;
				}
			}

			//2.1、判断非首行首列中，是否存在0，,并且在首行首列中标记
			for (size_t i = 1; i < row; i++) {
				for (size_t l = 1; l < col; l++) {
					if (matrix[i][l] == 0) {
						matrix[i][0] = matrix[0][l] = 0;
					}
				}
			}
			//2.2遍历首行，元素为0所在的列，赋值0；首行首例单独处理，这里不要处理，一旦处理了，
			//假设上面处理后首行为0120.说明第12列不用置0；如果处理首行，那么这一行就都改了，然后成0000那么不该修改的也改了。
			for (size_t i = 1; i < col; i++)
			{
				if (matrix[0][i] == 0) {
					for (size_t l = 1; l < row; l++)
						matrix[l][i] = 0;
				}
			}

			//2.3遍历首列，元素为0所在的行，赋值0；
			for (size_t i = 1; i < row; i++)
			{
				if (matrix[i][0] == 0) {
					for (size_t l = 1; l < col; l++)
						matrix[i][l] = 0;
				}
			}

			//3、对首行首列赋值0
			if (row0)
				for (size_t i = 0; i < col; i++)
					matrix[0][i] = 0;
			if (col0)
				for (size_t i = 0; i < row; i++)
					matrix[i][0] = 0;
			return;
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
		74. 搜索二维矩阵
		这两个题一个答案
		题意:
			给你一个满足下述两条属性的 m x n 整数矩阵：每行中的整数从左到右按非严格递增顺序排列。每行的第一个整数大于前一行的最后一个整数。
			给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。
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

		//74. 搜索二维矩阵,	240. 搜索二维矩阵 II,二刷.
		bool searchMatrix2(vector<vector<int>>& matrix, int target) {
			for (size_t i = 0; i < matrix.size(); i++) {
				for (size_t l = 0; l < matrix[0].size(); l++) {
					if (matrix[i][l] == target)
						return true;
					else if (matrix[i][matrix[0].size() - 1] < target)
						break;
				}
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
			然后这些，字母相同，但顺序不同，放到一起。！！最后放进去的时候，要放原先顺序的！！
			字母异位词简意为两字符串长度相同，字母相同，顺序不同。
		参考：
			https://leetcode.cn/problems/group-anagrams/solutions/84916/c-yin-ru-hashbiao-shi-jian-32ms-ji-bai-9948-nei-cu/?envType=study-plan-v2&envId=top-interview-150

		思路：
			对strs排序，这样的话，所谓的“字母异位词”就变成一样了。这样就能知道哪些单词是“字母异位词”。
			把这些单词放到一块去。放的时候放原本的顺序。
			然后用“字母异位词”做map的key，单词在vec中的序号做value；
			有个遍历i，来决定返回结果ret的行数，这个单词没有在map中出现过，i++；
			先对每个单词排序，然后发现这个单词没有在map中出现过，就二维的vec中新开一行。
			如果发现在map中出现过，在结果ret中的i行中，添加结果。添加的结果是原先的顺序。
			那个单词要放在那个行，要用unordermap来记录，key是单词，value是行号。
		*/
		vector<vector<string>> groupAnagrams(vector<string>& strs) {
			vector<vector<string>> ret;
			unordered_map<string, int> words;
			string strTemp;
			int i = 0;//二维的vec中的行号
			for (string str : strs) {
				strTemp = str;
				sort(str.begin(), str.end());
				if (words.find(str) != words.end())//找不到对应的key
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
		//二刷
		vector<vector<string>> groupAnagrams2(vector<string>& strs) {
			vector<vector<string>>ret;
			int i = 0;//结果ret的行数
			unordered_map<string, int>umap;//那个单词要放在那个行，要用unordermap来记录，key是单词，value是行号。
			for (string str : strs) {
				string rawStr = str;
				sort(str.begin(), str.end());//先对每个单词排序，然后发现这个单词没有在map中出现过，就二维的vec中新开一行。
				if (umap.find(str) == umap.end()) {
					ret.push_back(vector<string>(1, rawStr));
					umap[str] = i;
					i++;
				}
				else {//如果发现在map中出现过，在结果ret中的i行中，添加结果。添加的结果是原先的顺序。
					ret[umap[str]].push_back(rawStr);
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
		//二刷
		vector<int> twoSum2(vector<int>& nums, int target) {
			unordered_map<int, int> umap;
			for (int i = 0; i < nums.size(); i++) {
				//!!不用单独用一遍for来填充数组，只有一个for一遍填充一边查找就行，比如9 27，一开始9-2找7找不到，会把2放进去，下面9-7的时候找2就能找到。
				if (umap.find(target - nums[i]) != umap.end())
					return { i,umap[target - nums[i]] };
				umap.insert(pair<int, int>(nums[i], i));
			}
			return{};
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

				这个思路貌似是我自己想的，这个思路还行吧，时间复杂不错
		*/
		int longestConsecutive(vector<int>& nums) {
			unordered_set<int>set;
			for (int i = 0; i < nums.size(); i++)
				set.insert(nums[i]);
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
				maxLen = max(maxLen, tempLen);
				tempLen = 0;
			}
			return maxLen;
		}

		//二刷，我自己想的思路，为啥还不满意呢，已经超过75%了。可以了，还是不自信，但很正常
		int longestConsecutive2(vector<int>& nums) {
			unordered_set<int> uset;
			for (int num : nums)
				uset.insert(num);
			int maxLen = 0;
			while (!uset.empty()) {
				int tempLen = 0;//临时长度
				//以这个数为中心，向两边延伸
				int tempValue = *uset.begin();
				while (uset.erase(++tempValue) != 0)//unordered_set 的 erase如果传参迭代器，返回是迭代器，传参正数，返回正数，也就是删除的数量0或者1。每次只会删除一个c++23的时候会删除所有等于参数的值，我没细研究。
					tempLen++;
				tempValue = *uset.begin();//在换方向的时候，别忘了把tempValue回到初始位置
				while (uset.erase(--tempValue) != 0)
					tempLen++;
				uset.erase(*uset.begin());//把中心的这个数也删掉，这样就实现了连续区间的数都删掉了，下次遍历就是遍历新的区间了，不会出现重复的情况。
				tempLen++;//!!删除了中心元素后，别忘了++长度
				maxLen = max(maxLen, tempLen);
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


	//232.用栈实现队列--二刷
	class MyQueue1 {
		stack<int>stkin;
		stack<int>stkout;

		void push(int x) {
			stkin.push(x);
		}

		int pop() {
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

		//返回第一个元素的时候,一定要用pop函数.要不然不对!有因为pop函数会删除掉一个元素,所以要把删除掉的元素再加上
		int peek() {
			int ret = pop();
			stkout.push(ret);
			return ret;
		}

		bool empty() {
			return (stkin.empty() && stkout.empty());
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
	题意:
		设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
		实现 MinStack 类:
		MinStack() 初始化堆栈对象。
		void push(int val) 将元素val推入堆栈。
		void pop() 删除堆栈顶部的元素。
		int top() 获取堆栈顶部的元素。
		int getMin() 获取堆栈中的最小元素。
	思路：
		用multiset和和stack容器搭配使用即可.
		multiset保证数据的排序,set的第一个元素就是最小的.另外可能会放多个相同的元素,就用multi
		因为要返回栈顶元素,set只能保证返回最小的,但是最小的不一定在栈顶,所以还需要一个栈来保证返回的是栈顶.

		思路当然有很多种,我觉得使用双端队列也可以,但是记住这个思路就行,没必要再换了.
	*/
	class MinStack {
	public:
		MinStack() {}

		void push(int val) {
			stk.push(val);//主要是把数据放到栈中,set跟着一块操作
			set.insert(val);
		}

		void pop() {//因为muilset可以放多个重复的元素,所以当参数为元素的值的时候,会删除所有等于这个值的所有的元素.要想删除重复元素的某一个.就传参迭代器.
			set.erase(set.find(stk.top()));
			stk.pop();//主要是把数据从栈中取出,set跟着一块操作
		}

		int top() {
			return  stk.top();//取出数据对栈单独操作就行
		}
		//并能在常数时间内检索到最小元素的栈。
		int getMin() {//只有这里,为了保证常数时间,才对set操作.
			return *set.begin();
		}

	private:
		stack<int>stk;
		multiset<int>set;
	};


	//155. 最小栈-二刷
	class MinStack2 {
	public:
		MinStack2() {}

		void push(int val) {
			stk.push(val);
			set.insert(val);
		}

		void pop() {
			set.erase(set.find(stk.top()));
			stk.pop();
		}

		int top() {
			return stk.top();
		}
		//并能在常数时间内检索到最小元素的栈。
		int getMin() {
			return *set.begin();
		}

	private:
		stack<int> stk;
		multiset<int> set;
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
			if (stk.empty())//!!如果碰到了只有一个括号,stk这里要判断
				return true;
			return false;
		}

		//20. 有效的括号--二刷
		bool isValid2(string s) {
			stack<char> stk;
			for (char c : s)
			{
				if (stk.empty() || c == '[' || c == '(' || c == '{')
					stk.push(c);
				else if (stk.top() + 1 == c || stk.top() + 2 == c)
					stk.pop();
				else
					return false;
			}
			if (stk.empty())	return true;
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
		class cm//优先级队列的自定义的比较函数,一定要是在类中,传参也是这个类名.
		{
		public:
			bool operator() (const pair<int, int>& l, const  pair<int, int> &r)
			{
				return l.second > r.second;
			}
		};

		vector<int> topKFrequent(vector<int>& nums, int k) {
			map<int, int> mp;//元素的值 和 它对应的出现的次数
			priority_queue<pair<int, int>, vector<pair<int, int>>, cm >pque;
			//统计各个数据出现的频率
			for (size_t i = 0; i < nums.size(); i++) {
				mp[nums[i]]++;
			}

			for (pair<int, int> it : mp) {
				pque.push(it);//插入和删除的顺序别颠倒,要不然不对
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

		//347.前 K 个高频元素--二刷
		vector<int> topKFrequent2(vector<int>& nums, int k) {
			map<int, int>map;
			priority_queue<pair<int, int>, vector<pair<int, int>>, cm> pque;

			for (int num : nums) {
				map[num]++;
			}

			for (auto it : map) {
				pque.push(it);
				if (pque.size() > k)
					pque.pop();
			}
			vector<int> ret;
			for (size_t i = 0; i < k; i++)
			{
				ret.push_back(pque.top().first);
				pque.pop();
			}
			return ret;
		}




		/*
		23. 合并 K 个升序链表
		参考：
			无
		思路：
			优先级队列。
			把链表放到优先队列中，排序方式是“按照每个链表的头元素的值，从小到大。”
			然后遍历这个队列，队列的头部一定是最小的。
			把这个在“优先队列”中当前最小的点，依次放到链表中。
			最后得到的就是合并后的节点。
			1、把链表中的点放到“优先队列”中。（有的链表是空的，注意判断，不要放）
			2、遍历优先队列，把队列中最上面的点，也就是最小的点放到新的链表中，
			3、每放完一个节点，就把该链表的下个节点放到队列中（如果下个节点存在，另外放下个节点，其实就是放从下个节点开始的链表），
				因为优先队列会自动排序，所以最小的点还是在头部
			4、最后返回新链表就行。
		*/
		ListNode* mergeKLists(vector<ListNode*>& lists) {
			ListNode *dummyNode = new ListNode(-1);//！内存没释放哈
			ListNode *preNode = dummyNode;
			auto  cmp = [](const ListNode*newvalue, const ListNode*old) { return newvalue->val > old->val; };
			//注意“decltype(&cmp)”这里的&字符。以及q实例化的时候，加上cmp
			//第三个参数是需要传入类型，所以需要用decltype
			priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pque(cmp);
			for (ListNode* list : lists)
			{
				//因为题目有给的是空列表
				if (list != nullptr)
					pque.push(list);//把vec中的链表放到优先队列中。根据自定义的比较函数可知，哪个链表的头元素最小，哪个靠前
			}

			while (!pque.empty())
			{
				preNode->next = pque.top();//head中放最小的节点
				preNode = preNode->next;//节点后移
				if (pque.top()->next != nullptr)//只要发现当前链表后面还有节点，那么就把当前节点加进去。！只要加到队列中，就会重新排序，
					pque.push(pque.top()->next);
				pque.pop();//删除节点
			}
			ListNode *tmp = dummyNode;
			delete dummyNode;
			return tmp->next;
		}

		/*
		394. 字符串解码
		题意:
			给定一个经过编码的字符串，返回它解码后的字符串。编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。
			你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。
			此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。'
			输入：s = "3[a]2[bc]"
			输出："aaabcbc"
		参考：
			https://leetcode.cn/problems/decode-string/solutions/6274/ti-jie-czhan-by-youlookdeliciousc/?envType=study-plan-v2&envId=top-100-liked
			评论区中的有一个栈的解法,这个更简单,我已经写在下面了.
			看下面的一刷和二刷的注释,最好理解

		思路：
			这个对我来说，有个思维误区，虽然用了栈，但是,不是把遍历到的元素都一个个压栈，始终栈只有一层，每次都是头顶元素在累加元素strChar.top() += str;。
			我记个和上面模一个题目很相似，这里我累了。我就不看了。
			遍历这个字符串，遇到“[”才往栈内放；遇到“]”才出栈；其他情况，对栈都不需要操作。
		巧法：
			方便记忆这个代码，用 2[ab] 这样的例子就很方便。如果用3[a2[c]]这样就理解起来，在最后else上理解起来，非常麻烦。
		*/
		string decodeString(string s) {
			string str;//最后组合出的字符
			int num = 0;//每个字母的个数
			stack<int>strNum;//记录读取的数字
			stack<string>strChar;//记录读取的字母
			for (char c : s) {
				if ('0' <= c && c <= '9')
					num = num * 10 + c - '0';//读到2.这里写的比较复杂是因为会有两位数的情况出现.一位数的时候nums=0.二位数的时候num是上次的值
				else if ('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z')
					str += c;//str读到了ab
				else if ('[' == c)
				{
					strNum.push(num);//把读到的2放到栈中
					num = 0;//num清空
					//!没错，遍历到[, str是空的，仍旧往里面放
					strChar.push(str);//将”当前层级收集的字母“压入栈中。
					str = "";
				}
				else if (']' == c)
				{
					int times = strNum.top();//把2拿出来
					strNum.pop();
					for (size_t i = 0; i < times; i++)
					{
						//!!用栈顶的元素不断的累加!!
						//因为栈只有一层，所以需要用栈顶元素不断的加。我担心的是多层的情况是不是还是我说的这个情况，就这么记忆把
						strChar.top() += str;
					}
					str = strChar.top();
					strChar.pop();
				}
			}
			return str;
		}

		//394. 字符串解码.一个栈的版本,这个比较简单
		//https://leetcode.cn/problems/decode-string/solutions/6274/ti-jie-czhan-by-youlookdeliciousc/comments/1053288
		//2[a2[b]]==abbabb
		string decodeString2(string s) {
			string strNum = "";
			string strChar = "";
			stack<string> stk;
			for (char c : s) {
				if (c >= '0' && c <= '9') {
					strNum += c;//遇到数组,就不断的加起来.
				}
				if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {//别忘了,他大小写都有
					strChar += c;//遇到字符,也是不断的加起来.
				}
				if (c == '[') {//遇到了[,就把数字和字符都压到栈.并且清空.
					stk.push(strNum); // 比如两个[之间的a2是统一层级,他们同时压到栈里.这样他们在栈中的层级是一样的.
					strNum = "";
					stk.push(strChar);
					strChar = "";
				}
				if (c == ']') {
					string top = stk.top();
					stk.pop();
					string times = stk.top();
					stk.pop();
					int itimes = atoi(times.c_str());
					for (int j = 0; j < itimes; ++j)
						top += strChar;
					strChar = top;//??为什么组合出来的字符要给strChar?因为组合出来的字符,不一定是最终的字符,可能是属于中间的层级,那么就需要把他再压入栈中,然后在和数字相乘,最终得到最终的
				}
			}
			return strChar;
		}

		//394. 字符串解码--单个栈--二刷
		//2[a2[b]]==abbabb  2一个层级 a2一个层级 b一个层级
		string decodeString3(string s) {
			string strLevel = "";//同一个层级的字符
			string numLevel = "";//同一个层级的数字
			stack<string> strChar;
			for (char c : s) {
				if ('0' <= c && c <= '9') {
					numLevel += c;
				}
				else if ('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z') {
					strLevel += c;
				}
				else if ('[' == c) {//遇到了[,说明上个层级都遍历完毕.那么上个层级积累的字符和数字都要放到栈中.然后清空.
					strChar.push(numLevel);//先压数字还是字符都行,下面出栈的时候,能对应上就行.
					numLevel = "";
					strChar.push(strLevel);
					strLevel = "";
				}
				else if (']' == c) {
					//因为上面压栈,是先压的数字,后压的字符;所以先出来的就是字符.
					string tmpStr = strChar.top();//当前的拿到的最新的
					strChar.pop();
					int times = stoi(strChar.top());
					strChar.pop();
					for (size_t i = 0; i < times; i++) {
						tmpStr += strLevel;//!!组出来一个新的层级的字符!!2[a2[b]]举例子,当遇到第二个]的时候,tmpStr=a,strLevel就是上一层级2[b]得到的bb.这样组合的字符就是一个层级了,也变成了2[abb]
					}
					strLevel = tmpStr;//然后得到的最新的一个层级的字符给了strLevel
				}
			}
			return strLevel;
		}


		/*
		295. 数据流的中位数
		题意:
			中位数是有序整数列表中的中间值。如果列表的大小是偶数，则没有中间值，中位数是两个中间值的平均值。
			例如 arr = [2,3,4] 的中位数是 3 。
			例如 arr = [2,3] 的中位数是 (2 + 3) / 2 = 2.5
		参考：
			https://leetcode.cn/problems/find-median-from-data-stream/solutions/2361972/295-shu-ju-liu-de-zhong-wei-shu-dui-qing-gmdo/?envType=study-plan-v2&envId=top-100-liked
		思路：
			相对于题目，这里做了更改，从!=改成了==。但原理都一样。返回中值的时候，从A.top()改成B.top()。
			这个题目用到了两个“优先队列”，思路简单。关于优先队列，尤其是搭配less和greater的使用。
			有两个优先队列，A保存小数据，所以得是大顶堆，B保存大数据，得是小顶堆。
			两个尺寸一样的话，就先放到A中过滤，然后从A中挑个更大的到B。这个时候假设一开始是2个元素，1和2，现在新来了3.然后3先放到A，然后把2放到B，最后拿B的top返回即可。
			尺寸不一样的话，比如A1 B23，现在来了4，那么直接放到B，然后跳出2放到A中，A12 B34 中值就是两个top/2

			要记忆的点,尺寸相等时候先给大顶堆.否则先给小顶堆
		*/
		class MedianFinder {
		private:
			priority_queue<int, vector<int>, less<int>> pqA;//用less，就是大顶堆。头部是大数,尾部是小数.保存较小的数。
			priority_queue<int, vector<int>, greater<int>> pqB;//用greater，就是小顶堆。头部是小数,尾部是大数.保存较大的数。
		public:
			MedianFinder() {

			}
			void addNum(int num) {
				//当size一样的时候,多出来的放到b中,所以最后返回的时候,也就是返回b的top
				if (pqA.size() == pqB.size()) {//当两个队列的大小相同的时候，先放A中放，因为A保存较小的数，放到A中过滤(小的话就放到A，大的话下面会放到B)
					pqA.push(num);
					pqB.push(pqA.top());
					pqA.pop();//把A的最大，挪到B了，自然就删除。
				}
				else {
					pqB.push(num);
					pqA.push(pqB.top()); //把B中最小的元素给A
					pqB.pop();
				}
			}
			double findMedian() {
				return pqA.size() != pqB.size() ? pqB.top() : (pqA.top() + pqB.top()) / 2.0;//!!别忘了这个地方是2.0;这样才能保证返回的是浮点,要不然是整数就缺少精度,最后结果也不对
			}
		};

		//295. 数据流的中位数
		class MedianFinder2 {
		private:
			priority_queue<int, vector<int>, less<int>> minQue;//大锥顶队列,头部大.保存较小的数
			priority_queue<int, vector<int>, greater<int>> maxQue;//小锥顶队列,头部小,保存较大的数
		public:
			MedianFinder2() {}
			void addNum(int num) {
				if (maxQue.size() == minQue.size()) {
					minQue.push(num);
					maxQue.push(minQue.top());
					minQue.pop();
				}
				else
				{
					maxQue.push(num);
					minQue.push(maxQue.top());
					maxQue.pop();
				}
				return;
			}
			double findMedian() {
				return maxQue.size() == minQue.size() ? maxQue.top() : (maxQue.top() + minQue.top()) / 2;
			}
		};




		void test()
		{

			MedianFinder medianFinder;
			medianFinder.addNum(1);    // arr = [1]
			medianFinder.addNum(2);    // arr = [1, 2]
			medianFinder.findMedian(); // 返回 1.5 ((1 + 2) / 2)
			medianFinder.addNum(3);    // arr[1, 2, 3]
			medianFinder.findMedian(); // return 2.0
			vector<int>nums{ 1,3,1,2,0,5 };

			//vector<int>ret = maxSlidingWindow(nums, 3);

			decodeString3("3[a]2[bc]");
			/*for (auto c : ret)
				cout << c << " ";*/
		}

	};
}



//链表
namespace LinkedList
{
	class Solution {
	public:
		/*
			链表笔记：
				> 链表中通过循环结构，往后面插入数据（没看懂！！不知道当初是怎么写的）
					ListNode * note = new ListNode(0);
					ListNode *pre = note;
					//最后返回
					return note->next;

			>链表插入数据，两种方法：
				1、end->next=head； 接原来的节点。
					缺点：
					但是要注意的是，这样会把原先整个的链表都接上。
					在有些题目中，需要end->next =nullptr。从而保证逻辑上end后面都是nullptr。
					优点：
					好处是省空间复杂度
				2、end->next = new ListNode(head->val); 接新的节点，数据和head的数据一样，
					优点：
					不用在需要end->next =nullptr。每次插入新的end->next就是nullptr，否则看你的构造函数写的对不对。
					缺点：
					空间复杂度稍微差点。
				3、这部分的思想，参考82. 删除排序链表中的重复元素 II，是很好的例子

			> 链表删除元素，有两种方法：
				1、删除头部head
					head=head->next;
				2、删除p后面的一个点：
					p->next = p->next->next;
				3、链表删除元素，统一方法
					置一个虚拟头结点在进行删除操作。
					ListNode* dummyHead = new ListNode(0); // 设置一个虚拟头结点
					dummyHead->next = head; // 将虚拟头结点指向head，这样方便后面做删除操作
					参考：
					https://www.programmercarl.com/0203.%E7%A7%BB%E9%99%A4%E9%93%BE%E8%A1%A8%E5%85%83%E7%B4%A0.html#%E6%80%9D%E8%B7%AF

				4、删除slow后面的所有的点（上面123，都是删除一个点，这里删除多个点）
					slow->next = nullptr;// slow以及slow前面的所有的点

			> 链表的浅拷贝的思考
				这个问题，对我而言是指针的浅拷贝，这样的话所有的指针都可以管理同一个指针。
				贴一些关键的代码：
				auto slow = head;
				//以下代码都会对head链表更改！但是具体的代码不太一样。
				slow = slow->next;//这个也对更改了，特殊的是head每次被赋值的都是原来的值
				slow->next =nullptr; // 这个会造成head后面的链表断开
		*/

		/*
		141. 环形链表
		题意：
			判断链表中是否有环，有环就返回true
		哈希表方法
			核心在于要把节点指针放进去，因为有可能出现节点数据val相同，但是数据指针不会相同的。
			如果发现了重复的指针，那么就是同一个节点，
			说明该链表出现了环。
		*/
		bool hasCycle1(ListNode* head) {
			unordered_set<ListNode*> uset;
			while (head != nullptr) {
				if (uset.count(head) == 1)
					return true;
				uset.insert(head);
				head = head->next;
			}
			return false;
		}

		/*
		二刷
		参考;
			https://leetcode.cn/problems/linked-list-cycle/?envType=study-plan-v2&envId=top-100-liked
		思路：
			快慢指针，快指针走两步，慢指针走一步，
			如果有环就一定会出现快慢指针相遇的情况。
		*/
		bool hasCycle2(ListNode *head) {
			ListNode *fast = head;
			ListNode *slow = head;

			//如果快指针都走到nullptr了，也就是没有环
			while (fast&&fast->next != nullptr)//!!别忘了也判断fast
			{
				fast = fast->next->next;
				slow = slow->next;
				if (fast == slow)//如果有环while肯定出不去，快慢指针总会相遇，那么就返回true
					return true;
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
		题意：
			两个链表，
				243
				564
			得到708。返回这个708。
			他说他的矩阵是逆序存储，其实就一句话，进位要往后进。
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
				int t = l1 != nullptr ? l1->val : 0;//上面的链表
				int b = l2 != nullptr ? l2->val : 0;//下面的链表
				sum = t + b + jinwei;//本次结果加上次的进位
				jinwei = sum / 10;

				/*
				!通过循环结构，往后插数据的代码，就是下面这两句，非常的重要！
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

			if (jinwei > 0)//跳出循环后，有进位的话，就加上
				pre->next = new ListNode(jinwei);

			return note->next;
		}

		//二刷——这个是错的，我没删除，就是告诉你错在哪
		ListNode* addTwoNumbers2(ListNode *l1, ListNode *l2) {
			int jinwei = 0;
			ListNode *node = new ListNode;
			ListNode *end = node;
			while (l1 || l2)//l1和l2的长度不一样，所以计算要到他们俩都到尾巴，才算结束
			{
				int top = l1 == nullptr ? 0 : l1->val;
				int bottom = l2 == nullptr ? 0 : l2->val;
				int sum = (top + bottom + jinwei) % 10;//如果sum大于10.因为要进位，所以需要保留余数
				jinwei = (top + bottom + jinwei) / 10;
				end->val = sum;//我这里是先放值，然后再申请新的空间，如果链表最后没有进位，那么就多了一个点。所以不如改成，先申请空间再赋值。
				end->next = new ListNode;
				end = end->next;
				l1 = l1 == nullptr ? l1 : l1->next;//l1的next是空，就说走到了末尾，就赋值它本身，就不要走了往下。
				l2 = l2 == nullptr ? l2 : l2->next;
			}
			if (jinwei > 0)
				end->val = jinwei;
			else {
				delete end;//假设最后的结果是123，其实如果最后没有进位的话，end是没有作用的。那么你释放end，end虽然被释放了，但是123next被赋的值还是原来的值，那么就成了123+未知空间，力扣还是会访问到end，最后报错。
				end = nullptr;
			}
			return node;
		}

		//这个是正确。就用这个
		ListNode* addTwoNumbers3(ListNode *l1, ListNode *l2) {
			int jinwei = 0;
			ListNode *node = new ListNode;
			ListNode *pre = node;//!!为什么要定义这个变量呢?是因为上面的note随着next,最后会移动到结尾.要返回整个链表肯定要返回链表最前的元素.
			while (l1 || l2)//l1和l2的长度不一样，所以计算要到他们俩都到尾巴，才算结束
			{
				int top = l1 == nullptr ? 0 : l1->val;
				int bottom = l2 == nullptr ? 0 : l2->val;
				int sum = (top + bottom + jinwei) % 10;//如果sum大于10.因为要进位，所以需要保留余数
				jinwei = (top + bottom + jinwei) / 10;
				node->next = new ListNode(sum);
				node = node->next;
				l1 = l1 == nullptr ? l1 : l1->next;//l1的next是空，就说走到了末尾，就赋值它本身，就不要走了往下。
				l2 = l2 == nullptr ? l2 : l2->next;
			}
			if (jinwei > 0) {
				node->next = new ListNode(jinwei);
				node = node->next;
			}
			return pre->next;
			//return head;返回这个在默某些情况下是错误的.比如只有1个1的情况下.所以只能用上面这个.
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
			所以直接接在后面就行。
		其他：
			这个题目的稍微难理解的是二级指针。具体的代码中的注释吧。
			下面有用auto来描述二级指针，我还是建议别用auto了。
		*/
		ListNode* mergeTwoLists1(ListNode* list1, ListNode* list2) {
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

		ListNode* mergeTwoLists2(ListNode* list1, ListNode* list2) {
			ListNode* note = new ListNode(0);
			ListNode* end = note;
			while (list1 != nullptr && list2 != nullptr)
			{
				/*
				用二级指针，来统一管理list1，list2，这两个变量。
				这样做的好处，下面的代码中，ListNode **cur = list1->val < list2->val ? &list1 : &list2;
				二级指针cur统一管理了list1和list2。
				在下面的代码中“*cur = (*cur)->next;”。该是list1还是list2移动，就该是谁。
				直接用指针代替他俩，一处代码就能解决。
				如果一级指针，
				比如：“ListNode * cur = list1;”cur只是list1的值传递，cur = (cur)->next;移动的只会是cur而不是我们想要的list
				*/
				ListNode **cur = list1->val < list2->val ? &list1 : &list2;
				/*把符合条件的节点，接到后面*/
				end->next = *cur;
				end = end->next;
				/*然后，把谁接了，就完后移动节点!这里要注意优先级的问题；
				优先级依次是：（） -》 *
				如果是这种*cur = *(cur)->next;
				就是先访问(cur)->next。这种就是错误的。
				*/
				*cur = (*cur)->next;
			}
			end->next = list1 == nullptr ? list2 : list1;
			return note->next;
		}

		//应该是3刷了
		ListNode* mergeTwoLists3(ListNode* list1, ListNode* list2) {
			ListNode*note = new ListNode;
			ListNode* end = note;
			while (list1&&list2) {
				ListNode** cur = list1->val > list2->val ? &list1 : &list2;//!!谁小先接谁，别接错了，哈哈。要不然代码超时
				end->next = *cur;
				end = end->next;
				(*cur) = (*cur)->next;
			}
			end->next = list1 == nullptr ? list2 : list1;
			return note->next;
		}




		/*
		138. 随机链表的复制
		题意：
			这个题目的题意，看起来很难，其实就是复制链表。这个链表只不过特殊在这个链表是有个随机指针，指向一个随机的节点。就是因为它导致复制起来非常复杂的原因。
			麻烦就麻烦在他的他随机指针指向的是链表的序号。
			比如：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]。后面的是随机指针，【13,0】中0它指向指的的链表中的第0个下标的节点。这种就比较难做。
		思路：
			这个题目，难度有2，一是理解题目，二是链表中的“random”指针的指向。
			1、如果是空空链表，就返回空的。

			2、构建无序map，然后用链表节点的地址做key，链表的节点做value。（有点想用map的特性做了一个指针）


			3、通过链表节点的指针，遍历map，顺便赋值。

			4、最后返回的就是map的“map[head]”
		总结：
			代码乍一看还行，其实没怎么理解。就硬记吧
		参考：
			https://leetcode.cn/problems/copy-list-with-random-pointer/solutions/2361362/138-fu-zhi-dai-sui-ji-zhi-zhen-de-lian-b-6jeo/?envType=study-plan-v2&envId=top-interview-150
			中的哈希表的方法
		*/
		Node* copyRandomList(Node* head) {
			if (head == nullptr)
				return head;
			unordered_map<Node*, Node*>map;//一定要用无序map 因为它的[]时间复杂的平均为1，坏的情况下才是n。比map的logn好多了
			Node* cur = head;
			//创建新的map节点
			while (cur != nullptr)
			{
				map[cur] = new Node(0);
				cur = cur->next;
			}
			cur = head;
			while (cur != nullptr)
			{
				map[cur]->val = cur->val;
				map[cur]->next = map[cur->next];//！！当赋值地址的时候，就要使用map了。
				map[cur]->random = map[cur->random];
				cur = cur->next;
			}
			return map[head];
		}


		//二刷
		Node* copyRandomList2(Node* head) {
			Node *cur = head;
			Node *tmpHead = head;
			unordered_map<Node*, Node*> umap;

			while (cur)
			{
				umap[cur] = new Node(0);
				cur = cur->next;
			}
			cur = tmpHead;
			while (cur)
			{
				umap[cur]->val = cur->val;
				umap[cur]->random = umap[cur->random];
				umap[cur]->next = umap[cur->next];
				cur = cur->next;
			}
			return umap[head];
		}


		/*
		92. 反转链表 II--最终用这个思路,其他的都不参考了
		思路：
			具体思路参考：这个链接
			以及我本文档中的图片
		参考：
			https://leetcode.cn/problems/reverse-linked-list-ii/solutions/1992226/you-xie-cuo-liao-yi-ge-shi-pin-jiang-tou-teqq/?envType=study-plan-v2&envId=top-interview-150
		*/
		ListNode* reverseBetween(ListNode* head, int left, int right) {
			ListNode* dummy = new ListNode(0);
			dummy->next = head;
			ListNode* p0 = dummy;//p0节点的位置位于翻转的链表之前
			//移动p0到翻转位置前面
			for (size_t i = 0; i < left - 1; i++)//left - 1是因为题目的中left=1的时候,是代表链表的第0个节点
			{
				p0 = p0->next;
			}

			//翻转链表-和"翻转链表1"思路一样.反转后从原链表来看,pre在反转后的末尾,cur在pre的后面
			//不同的是:翻转一部分链表.所以不用while,而是for来限定范围
			ListNode* cur = p0->next;//cur在反转前,代表的是翻转的起始位置,head就错了
			ListNode* pre = nullptr;
			for (int i = 0; i < right - left + 1; i++)//right-left+1代表 right到left之前的元素数量
			{
				ListNode* tmp = cur->next;
				cur->next = pre;
				pre = cur;
				cur = tmp;
			}

			p0->next->next = cur;
			p0->next = pre;

			return dummy->next;
		}


		/*
		92. 反转链表 II
		思路：
			具体思路参考：这个链接
			另外的，关于链表翻转的好几种情况的写法，已经放在笔记中的-《hot100 链表笔记》部分。
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

		ListNode* reverseBetween1(ListNode* head, int m, int n) {
			//n==1代表链表反转到最后一个点了。这个递归该结束了
			if (m == 1) {
				return reverseN(head, n);
			}
			//每次执行的时候，一定是head->nex，因为reverseBetween返回的是head后面的节点
			head->next = reverseBetween(head->next, m - 1, n - 1);
			return head;//返回一定要是head，具体看注释
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
			ListNode* dummy = new ListNode(0);//为了统一删除方法，增加虚拟节点
			dummy->next = head;
			ListNode* fast = dummy, *slow = dummy;//既然增加了虚拟点，快慢指针就要从这开始，要不然没有意义
			// 让fast指针先走n+1步 假设12345 删除倒数2个，也就是4.先走3步，这个时候fast走到了4这。
			//然后fast和slow一块走，fast走到尾巴也就是走了2步，slow走到3.3正好在4的前面，也就是再删除的元素前面。在它的前面就方便使用slow->next = slow->next->next;删除他
			for (int i = 0; i < n + 1; i++) {//
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

		//二刷
		ListNode* removeNthFromEnd2(ListNode* head, int n) {
			ListNode* dummy = new ListNode;
			dummy->next = head;
			ListNode* fast = dummy;
			ListNode* slow = dummy;

			for (size_t i = 0; i < n + 1; i++)
				fast = fast->next;
			while (fast)
			{
				fast = fast->next;
				slow = slow->next;
			}
			slow->next = slow->next->next;
			return dummy->next;
		}

		/*
		82. 删除排序链表中的重复元素 II
		参考：
			https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/solutions/678600/tong-yong-shan-chu-zhong-fu-jie-dian-lia-od9g/?envType=study-plan-v2&envId=top-interview-150
		思路：
			为了方便删除头结点，要加一个虚拟头结点。
			tail后面接满足要求的点,
			如果当前和后面的节点的值不相等,那么就用tail->next接上,然后tail往后移动一个
			如果当前和后面的节点的值相等,那么就head=head->next.相当于跳过这个节点,
			后面tail->next接head的时候,因为head跳过了这几个点,那么就相当于删除了.
			上面无论操作了哪个if,head的点都要往后移动
			最后,跳出while之后,也就是说明tail已经把能接的点都结完了,这个时候tail->next=nullptr;
			来代表整个链表结束.
		*/
		ListNode* deleteDuplicates(ListNode* head) {
			ListNode* dummy = new ListNode(-1);
			ListNode* tail = dummy;//新的链表节点都接在tail的后面
			while (head) {//if中存在head->next的访问,所以一定要判断head->next的有效性
				if (head->next == nullptr or head->val != head->next->val) {
					tail->next = head;
					tail = tail->next;
				}
				while (head->next and head->val == head->next->val)
					head = head->next;
				head = head->next;
			}
			tail->next = nullptr;
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
		参考：
			https://leetcode.cn/problems/reverse-nodes-in-k-group/?envType=study-plan-v2&envId=top-100-liked
		思路：
			 每次翻转k个节点，然后接上；然后再翻转再接上。
			 比如12345 k=2
		*/
		//左开右闭，比如传进来123，然后给你返回的21
		ListNode* reverseKGroup_reverser(ListNode* head, ListNode* tail) {
			ListNode* pre = nullptr;//要实现翻转，当前节点要接的上次节点。最一开始的时候，肯定是要接nullptr
			ListNode* cur = head;
			// !!这一部分和“206. 反转链表”很相似
			while (cur != tail) {
				ListNode*nextTmp = cur->next;
				cur->next = pre;//cur-next指向前一个
				pre = cur;//pre指针往前走
				cur = nextTmp;//cur也往前走
			}
			return pre;
		}

		ListNode* reverseKGroup(ListNode* head, int k) {
			if (head == nullptr || head->next == nullptr)
				return head;//如果链表中为空，或者只有1个点，那么就没有翻转的必要。

			ListNode *tail = head;//初始化tail，tail后面会不断的往后移动，所以一开始在头部的位置。
			for (size_t i = 0; i < k; i++)
			{
				if (tail == nullptr)//在移动尾巴的过程中，for还没完成，尾巴都移动到nullptr了，说明这一段不满足翻转要求，要返回head
					return head;
				tail = tail->next;
			}
			//已经知道了head和tail的位置，那就开始翻转
			ListNode * newHead = reverseKGroup_reverser(head, tail);
			//上面翻转完了之后，就开始处理剩余的节点
			head->next = reverseKGroup(tail, k);

			return head;//最后返回翻转后的节点
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
			！！这个题目常考！！
		题意：
			就是就是按照“使用时间”配列，最新访问的在上面，次新访问往下排，最后访问的在最下面。
			假设最多放3，现在打开一个新的就要把最老的删掉，把刚打开放在最上面。
			有点像手机多任务调度设计。
			！！函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。！！这个条件才导致了用到了uamp和list这两个容器
			只有put的时候，list因为是链表，所以insert可以做到1的时间复杂度，但是get的时间复杂度却是n。
			umap的get和put都可以做到时间复杂度为1，但是uamp无法做一个排序，我取数据的时候，没有办法去到最新的数据，所以需要他们结合。
			！！！阅读代码的时候你会发现，查找数据的时候，用到的是umap;储存数据的时候，用到的是list。

		参考：
			思路：
				https://leetcode.cn/problems/lru-cache/solutions/12711/lru-ce-lue-xiang-jie-he-shi-xian-by-labuladong/?envType=study-plan-v2&envId=top-interview-150
			代码：
				https://leetcode.cn/problems/lru-cache/solutions/12711/lru-ce-lue-xiang-jie-he-shi-xian-by-labuladong/comments/162138
		其他：
			这个代码中。最新的元素是放在list的头部。
			list别记错，它是双向链表。
			！！记忆点：lsit存key和value map存key和list的迭代器！！
	*/
	//三刷————推荐这个代码
		class LRUCache3 {
		public:
			LRUCache3(int capacity) : cap(capacity) {
			}

			int get(int key) {
				if (umap.find(key) == umap.end())
					return -1;
				//splice 翻译 移接
				//listp.begin()：这是指定移动元素的目标位置，即将元素移到链表的头部。
				//listp：表示目标链表，也就是 listp 自身。
				//it->second：这是要移动的元素的迭代器，it->second 指向的是链表节点的值，即键值对中的值。
				listp.splice(listp.begin(), listp, umap[key]);//通过spilce把指定的元素移动到头部
				return listp.front().second;
			}

			void put(int key, int value) {
				auto it = umap.find(key);
				if (it == umap.end()) {//没找到数据，
					if (listp.size() == cap) {//没找到数据，并且容量满了，删除旧数据，添加新数据
						//listp.pop_back()
						umap.erase(listp.back().first);//删除旧数据，谁是旧的就靠list来决定
						listp.pop_back();
						listp.push_front({ key,value });//添加新数据
						umap[key] = listp.begin();
					}
					else {//没找到数据，容量也没满
						listp.push_front({ key,value });
						umap[key] = listp.begin();
					}
				}
				else {//找到数据了，就把原先的数据删掉，然后把这个数据从新放到list头部
					listp.erase(umap[key]);
					listp.push_front({ key,value });
					umap[key] = listp.begin();
				}
			}

		private:
			int cap = 0;
			list<pair<int, int>> listp;
			unordered_map<int, list<pair<int, int>>::iterator> umap;
		};

		class LRUCache {
		public:
			LRUCache(int capacity) : cap(capacity) {
			}
			//int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
			int get(int key)
			{
				if (map.find(key) == map.end())
					return -1;
				auto key_value = *map[key];//查找数据的时候用umap;
				listp.erase(map[key]);//list删除umap找到的数据
				listp.push_front(key_value);//list添加新的数据到list的头部。
				map[key] = listp.begin();//map和list建立对应关系！无论这个key是新的还是旧的，[]都可以建立关系。
				return key_value.second;
				//return 	map[key]->second;//两者是一样的。
			}
			//void put(int key, int value) 如果关键字 key 已经存在，则放到最前面，代表最新访问过 ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
			void put(int key, int value) {

				if (map.find(key) == map.end())//放入的元素不存在
				{
					//!!我试了，这个if不能放在外面。要不然过不了
					if (listp.size() == cap)//当LRU的容量满了之后，删除尾巴的最旧的元素
					{
						map.erase(listp.back().first);//map中删掉最旧的数据
						listp.pop_back();//list中删除最旧的数据
					}
					listp.push_front({ key, value });//list放最新的数据在头部
					map[key] = listp.begin();//map和list建立对应关系。
				}
				else//放入的元素存在，那么就删除这个元素，然后把这个元素放到list的头部
				{
					listp.erase(map[key]);
					listp.push_front({ key, value });
					map[key] = listp.begin();//map和list建立对应关系。
				}
				//cache.push_front({ key, value });
			}
		private:
			int cap;
			//！！要注意的是，这个代码中，最新的元素是放在list的头部。
			list<pair<int, int>> listp;//list是双向链表，用它的原因是删除的时间复杂度是1。
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

				记忆点：lsit存key和value map存key和list的迭代器
			*/
		};

		//2刷
		class LRUCache2 {
		public:
			LRUCache2(int capacity) :cap(capacity) {
			}
			int get(int key) {
				if (umap.find(key) == umap.end()) {
					return -1;
				}
				auto it = umap[key];
				listp.erase(umap[key]);
				listp.push_front(*it); // 插入迭代器指向的元素到 listp 的头部
				return it->second;
			}


			//往里面放数据。
			void put(int key, int value) {
				if (umap.find(key) == umap.end()) {//没找到这个元素
					if (umap.size() == cap) {//没找到这个元素，并且容量满了，就删除最老的
						//listp.back().first;
						umap.erase(listp.back().first);
						listp.pop_back();
						listp.push_front({ key, value });
						umap[key] = listp.begin();
					}
					else {
						//没找到这个元素，并且容量没满
						listp.push_front({ key, value });
						umap[key] = listp.begin();
					}
				}
				else {//找到这个元素,就把旧的删除掉，新的放前面。
					//!!!这里会出现迭代器失效的问题，
					auto it = umap[key];
					listp.erase(it);
					listp.push_front({ key, value });
					umap[key] = listp.begin();
				}
			}



		private:
			int cap = 0;
			list<pair<int, int>> listp;
			unordered_map<int, list<pair<int, int>>::iterator> umap;
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
			1-》  2-》  3-》   4
			pre	  cur   tmp
		*/
		ListNode* reverseList(ListNode* head) {
			ListNode *cur = head;//一开始的时候，cur为头结点，pre为nullptr，头结点的next就是nullptr
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


		//二刷
		ListNode* reverseList2(ListNode* head) {
			ListNode*cur = head;
			ListNode*pre = nullptr;
			while (cur)
			{
				ListNode*tmp = cur->next;
				cur->next = pre;
				//移动cur和tmp指针，先移pre再移cur
				pre = cur;
				cur = tmp;
			}
			return pre;
			//return cur->next; while出来的时候cur是nullptr，访问越界
		}


		/*
		24. 两两交换链表中的节点
		参考：
			https://www.programmercarl.com/0024.%E4%B8%A4%E4%B8%A4%E4%BA%A4%E6%8D%A2%E9%93%BE%E8%A1%A8%E4%B8%AD%E7%9A%84%E8%8A%82%E7%82%B9.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			核心就是每次只翻转一对，然后往后移动2个位置，然后再接着翻转一对。
			比如：x 1234，x先接2，然后接1；再接4，然后接3。
			以12举例，x从指向1变成了指向2.没有临时变量的话，1就找不到了。
			同理，2从指向3变成了1，没有临时变量的话，3就找不到了。
			（和上体同理）
		*/
		ListNode* swapPairs(ListNode* head) {
			ListNode *dummyHead = new ListNode(0);
			ListNode *cur = dummyHead;
			dummyHead->next = head;
			while (cur->next != nullptr&&cur->next->next != nullptr)
			{
				ListNode *tmp1 = cur->next;//其实是“1”
				ListNode *tmp3 = cur->next->next->next;//其实是“3”

				cur->next = cur->next->next;//x接2。2把1的位置替代了，1找不到了，所以要用tmp1来保存1
				cur->next->next = tmp1;//2后面的3“换成”1。达到2接1的效果。这样的话2后面的原来的3就丢了。所以上面要用tmp3来保存3
				cur->next->next->next = tmp3;//1接3
				cur = cur->next->next;//cur每次要往后移动两次.从x移动到2，也就是12的前面移动到34的前面
			}
			return dummyHead->next;
		}

		//二刷
		ListNode* swapPairs2(ListNode* head) {
			ListNode* dummy = new ListNode;
			dummy->next = head;
			ListNode* cur = dummy;//cur在x这
			while (cur->next&&cur->next->next) {
				ListNode* tmp1 = cur->next;//节点1
				ListNode* tmp3 = cur->next->next->next;//节点3
				cur->next = cur->next->next;//x接2
				cur->next->next = tmp1;//接1
				cur->next->next->next = tmp3;//接3
				cur = cur->next->next;
			}
			return dummy->next;
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
		题意：
			给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
		参考：
			https://www.programmercarl.com/0142.%E7%8E%AF%E5%BD%A2%E9%93%BE%E8%A1%A8II.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
			题目进阶要求用1的空间复杂度，最终还是要用双指针思路
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
		二刷用双指针思路，也就是上面链接中的思路；
		不用管具体的数学公式推导，记录思路即可。
		有快慢两个指针，如果有换的话，两个指针一定会相遇。
		！！相遇之后，快或者慢指针接着往后走，然后弄一个新的指针从头开始走，
		直到两个指针再次相遇，这个相遇的位置，就是环的入口位置。
		*/
		ListNode *detectCycle2(ListNode *head) {
			ListNode *fast = head;
			ListNode *slow = head;
			while (fast&&fast->next)
			{
				fast = fast->next->next;
				slow = slow->next;
				if (fast == slow) {
					while (true) {
						//!!!这个if一定要先判断！一定要在上面
						//比如12这个环，到里层while的时候，fast和slow都在1上面，而1就是入口，这个时候不先判断，而是再往下走，返回的结果就是错的。
						if (head == slow)
							return head;
						head = head->next;
						slow = slow->next;
						//fast = fast->next;//都一样我试了

					}
				}
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

		//160. 相交链表--二刷
		ListNode *getIntersectionNode1(ListNode *headA, ListNode *headB) {
			if (headA == nullptr || headB == nullptr)
				return nullptr;
			ListNode *pa = headA;
			ListNode *pb = headB;
			while (true)//while (true)不行,比如两个11,做个一个环,就会卡死在里面,所以先判断他俩不想等的情况
			{
				pa = pa == nullptr ? headB : pa->next;
				pb = pb == nullptr ? headA : pb->next;
				if (pb == pb)
					return pb;
			}
			return nullptr;
		}



		/*
		234. 回文链表
		参考：
			无
		思路：
			进阶：你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？
			题解中，有这个思路，我没用。！后期还是要弄下，现在先用简单的。
			把链表放到数组中，然后用双指针就很方便了。
			！这个时间复杂度和空间复杂度不合要求，这个没有必要记住。但是简单，真想不起来，用这个。
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
		234. 回文链表
		参考：
			https://leetcode.cn/problems/palindrome-linked-list/solutions/41195/wo-de-kuai-man-zhi-zhen-du-cong-tou-kai-shi-gan-ju/?envType=study-plan-v2&envId=top-100-liked
		思路：
			通过快慢指针，快指针走到末尾，慢指针就会走到中间。
			还有一个pre指针是跟在慢指针后面，还有一个prepre是和pre构建一个反转的链表。
			比如1221：
			fast走到尾巴(null)的时候，slow走到后面的2，pre走到前面的2.
			slow往后走，pre往前走。不断的判断slow和pre的value知否相同，不相同就说名不是回文

			比如121
			fast走到尾巴(1)的时候，slow在2的位置，pre在1的位置。
			因为链表的数量是奇数，通过fast！=null来判断，slow要都往前走一步。
			最后和上面的是一样的：
			slow往后走，pre往前走。不断的判断slow和pre的value知否相同，不相同就说名不是回文
		*/
		bool isPalindrome2(ListNode* head) {
			ListNode* fast = head, *slow = head, *pre = head, *prepre = nullptr;
			while (fast != nullptr&&fast->next != nullptr)
			{
				pre = slow;//per是跟在slow后面的指针，在这里先更新pre，后面slow接着就往后走了。这样就完成了pre在slow后面。
				slow = slow->next;
				fast = fast->next->next;

				pre->next = prepre;//pre接反转的链表
				prepre = pre;//prepre也在往前走。
			}
			if (fast != nullptr)//fast不是空说明链表是奇数个。
				slow = slow->next;//slow还是要往后走一个

			while (slow != nullptr&&pre != nullptr)
			{
				if (slow->val != pre->val)
					return false;
				slow = slow->next;
				pre = pre->next;
			}
			return true;
		}

		//234. 回文链表--三刷
		bool isPalindrome3(ListNode* head) {
			ListNode* fast = head, *slow = head, *pre = head, *prepre = nullptr;
			while (fast != nullptr && fast->next != nullptr) {
				pre = slow;
				fast = fast->next->next;
				slow = slow->next;
				pre->next = prepre;
				prepre = pre;
			}
			if (fast != nullptr)
				slow = slow->next;


			while (slow != nullptr && pre != nullptr)
			{
				if (slow->val != pre->val)
					return false;
				slow = slow->next;
				pre = pre->next;
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
		得到的新的一部分和另外一个新的部分，再重复这个过程，然后又得到一个新的部分。
		直到最后，把所以都分割完了.具体的步骤如下:
		1、通过双指针，拿到链表的中心。
		2、然后截取链表，截成左右两部分。
		3、通过递归不断的截取链表，最后截到链表只剩一个点.

		然后开始合并,合并很简单,这个时候就是递归的回溯了.
		先创建一个新的节点,因为新的节点会往后移动,所以就弄一个pre节点.
			 只要左右节点,也就是上面分割后的节点,不是空,就一直接下去.哪个节点的值小就接谁.
		接完了之后,被接的那个往后移动,同时新节点也往后移动.
		因为左右,总会有一个先接完,谁还没接就把他接上.
		最后返回即可

		!!为什么fast是复制head->next,而slow是赋值head?
		如果两个都是赋值head,就会导致slow在链表的后面,比如链表12,最后slow的位置在2这,
		slow->next = nullptr;进行切割的时候,本来都为尾巴了,所以切割时无效的,然后ListNode* left = sortList(head);
		再去切割的时候,因为切割失败,所以传递的还是12.无限重复下去.只有head和slow拉开,才能实现切割。
		*/
		//148. 排序链表--三刷;  第一个代码太复杂了,这个思路一样,代码没这么复杂--最后就用这个!不要再折腾了!
		//参考:https://leetcode.cn/problems/sort-list/solutions/13728/sort-list-gui-bing-pai-xu-lian-biao-by-jyd/
		ListNode* sortList(ListNode* head) {
			if (head == nullptr || head->next == nullptr)
				return head;
			ListNode* fast = head->next, *slow = head; //为什么fast是复制head->next,而slow是赋值head?
			while (fast != nullptr && fast->next != nullptr) {
				slow = slow->next;
				fast = fast->next->next;
			}
			ListNode* tmp = slow->next;//下面就要切除slow后面了,所以要保存slow后面的链表.
			slow->next = nullptr;//从slow后面切断链表
			ListNode* left = sortList(head);//递归进去再切割,把两个链表的头节点传进去接着割!
			ListNode* right = sortList(tmp);//left, right 分别指向两链表头部

			//下面是开始重新接节点!只要链表没有被切完,就走不到这
			ListNode* newLN = new ListNode(0);//建立辅助 ListNode h 作为头部。
			ListNode* pre = newLN;//因为newLN要往后移动,所以这里放个不会移动的辅助节点,这个你肯定明白的.
			while (left != nullptr && right != nullptr) {
				if (left->val < right->val) {
					newLN->next = left;
					left = left->next;
				}
				else {
					newLN->next = right;
					right = right->next;
				}
				newLN = newLN->next;
			}
			newLN->next = (left != nullptr) ? left : right;//上面切割的左右链表有可能长度不一样,那么最后就会空出左或者右节点.谁不空就空了谁,把它接上就行了.
			return pre->next;
		}


		ListNode* sortList1(ListNode* head) {
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

		//148. 排序链表--先来个简单的，到手万一想不起来了，还有这个保底。就是性能差点
		ListNode* sortList_easy(ListNode* head) {
			multiset<int> worker;
			auto sub = head;
			while (sub) worker.insert(sub->val),
				sub = sub->next;
			sub = head;
			for (auto &i : worker)
				sub->val = i, sub = sub->next;
			return head;
		}


		/*
		143. 重排链表
		参考:
			https://leetcode.cn/problems/reorder-list/solutions/2843011/yi-mu-liao-ran-de-tu-shi-bu-zou-by-shawx-k3o8/
		思路:
			1.找到链表中点,按照中点把链表拆分成两个部分
			2.然后反转后面那部分的链表
			3.按照题目要求再把链表合起来

			这个题目考察的点很多.题目代码很多,但实际上理解起来不难.不明白就看链接中的图
		*/
		//找到链表的中点--定义快慢指针,快指针走到末尾,慢指针就走到中点.
		ListNode* findMid(ListNode* head) {
			ListNode* fast = head;
			ListNode* slow = head;
			while (fast->next &&
				fast->next->next) { //!!都是对fast指针的判断,且两个先后顺序别乱
				fast = fast->next->next;
				slow = slow->next;
			}
			return slow;
		}

		ListNode* reverseListNode(ListNode* head) {//最后反转的结果一定要用返回值翻出去,用形参head传出去,不行!不知道为啥
			ListNode* pre = nullptr;
			ListNode* cur = head;
			while (cur) { // 对cur判断,不是对head,
				ListNode* tmp = cur->next;
				cur->next = pre;
				pre = cur;
				cur = tmp;
			}
			return pre;
		}

		void mergeListNode(ListNode* l, ListNode* r) {

			ListNode* ltmp;
			ListNode* rtmp;

			while (l && r) {
				ltmp = l->next;
				rtmp = r->next;

				l->next = r;
				l = ltmp;

				r->next = l;
				r = rtmp;
			}
		}

		void reorderList(ListNode* head) {
			ListNode* mid = findMid(head); // 找链表的中点

			ListNode* lList = head;
			ListNode* rList = mid->next;
			mid->next = nullptr; // 从mid,把链表分为两部分

			rList = reverseListNode(rList); // 反转链表
			mergeListNode(lList, rList);
		}




		ListNode* ListNodeTest(ListNode* head, int n) {
			ListNode* dummy = new ListNode;
			dummy->next = head;
			ListNode* fast = dummy;
			ListNode* slow = dummy;

			for (size_t i = 0; i < n + 1; i++)
				fast = fast->next;

			while (fast)
			{
				fast = fast->next;
				slow = slow->next;
			}
			slow->next = slow->next->next;
			//return head;
			return dummy->next;
		}

		void test()
		{
			LinkedList::Solution a;
			ListNode lb(1);
			ListNode lb1(2);
			ListNode lb2(3);
			ListNode lb3(4);
			ListNode lb4(5);
			ListNode lb5(4);
			ListNode lb6(7);/*
			lb.next = &lb1;
			lb1.next = &lb2;
			lb2.next = &lb3;
			lb3.next = &lb4;*/

			ListNode* ret;
			ret = ListNodeTest(&lb, 1);
			while (ret != nullptr)
			{
				cout << ret->val << "  " << endl;
				ret = ret->next;
			}


			/*lb4.next = &lb5;
			lb2.next = &lb3;
			lb3.next = &lb4;
			lb4.next = &lb5;
			lb5.next = &lb6;*/

			//Node* nret;
			//Node nb(7);
			//Node nb1(13);
			//Node nb2(11);

			//Node nb3(10);
			//Node nb4(1);
			//Node nb5(4);
			//Node nb6(7);


			//nb.next = &nb1;
			//nb.random = nullptr;

			//nb1.next = &nb2;
			//nb1.random = &nb;

			//nb2.next = &nb3;
			//nb2.random = &nb4;

			//nb3.next = &nb4;
			//nb3.random = &nb2;


			//nb4.next = nullptr;
			//nb4.random = &nb1;




			////ret = reverse_link(&lb);
			////ret = reverse(&lb);
			//nret = a.copyRandomList(&nb);
			////ret = a.reverseBetween(&lb,1,2);

			//while (nret != nullptr)
			//{
			//	cout << nret->val << "  " << nret->random->val << endl;
			//	nret = nret->next;
			//}
		}
		void testLRU()
		{
			LRUCache2 lRUCache(2);
			lRUCache.put(2, 1); // 缓存是 {1=1}
			lRUCache.put(1, 1); // 缓存是 {1=1, 2=2}
			lRUCache.get(2);    // 返回 1
			lRUCache.put(4, 1); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
			lRUCache.get(1);    // 返回 -1 (未找到)
			lRUCache.get(2);    // 返回 -1 (未找到)
			//lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
			//lRUCache.get(1);    // 返回 -1 (未找到)
			//lRUCache.get(3);    // 返回 3
			//lRUCache.get(4);    // 返回 4
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


		/*
				# 树
		## 遍历
			> 深度优先遍历
				前序遍历（递归法，迭代法）
				中序遍历（递归法，迭代法）
				后序遍历（递归法，迭代法）
				对这三种遍历方式的总结就是：
				左中右是怎么排列的：
				1、什么序，中就在哪
				2、左右排序固定
				3、前序遍历，根节点一定是首先打印；中序：根节点在中间；后序：根节点再最后。可以根据这些特性从数组中构造一颗树。

			 广度优先遍历
				层次遍历（迭代法）

			要根据什么选择遍历方式？
			其实没有明显的提示可以选择什么遍历方式。或者说什么遍历方式都可以实现，只是某一种方便一些
			本题一定是要后序遍历，因为通过递归函数的返回值来做下一步计算。——337.打家劫舍 III


			## 关于树的一些总结
			> 1、做了一些题目。尤其是对于递归而言，每一次递归的开始，都把他理解为一个小子树的处理，会更好。
			  2、像这种返回bool的递归，一定要确定什么时候返回true，什么时候返回false。
				 然后在return的地方调用递归。
				参考101. 对称二叉树、112. 路径总和
				基本上都是这种做法
			  3、分析的代码的时候，方便理解或者是写，就从叶子结点往上走，好理解
				TreeNode* left = lowestCommonAncestor(root->left, p, q);
				TreeNode* right = lowestCommonAncestor(root->right, p, q);
				这两行代码，如果要一层一层递归进去，理解很不好理解。
				可以简化理解，这个思路在任何递归的时候，都比较好用。
				lowestCommonAncestor(root->left, p, q);  就是当前root的左子树的结果
				lowestCommonAncestor(root->right, p, q); 就是当前root的右子树的结果
				不管它内部是怎么递归的，就知道这个结果就行。
				参考：236. 二叉树的最近公共祖先

		## 树的高度和深度
			>二叉树节点的深度：指从根节点到该节点的最长简单路径边的条数。
			 二叉树节点的高度：指从该节点到叶子节点的最长简单路径边的条数。

			 根据以下两点，做题的时候，选择不同的思路
			 深度可以从上到下去查 所以需要前序遍历（中左右），
			 高度只能从下到上去查，所以只能后序遍历（左右中）

			 比如验证平衡二叉树
			 是不是二叉树要看它的左右孩子的高度是不是差1，那么就选择后序遍历

		## 关于树中回溯的总结
		 > 回溯基于的数据结构最好是vec或者是arry这种，加的时候也是一次，删除的也是一次。不会受到数据自身长度的影响。
		   比如：
		   257. 二叉树的所有路径
			   vector<int> path;//path一定要vec，如果要用string的话，如果添加了一个3位数字，在回溯的时候，要回溯3次，关键你还得记录他的位数。用vec的话，pop一次就行了

		## 在树中递归结束条件的写法
		 > 1、如果他的任意一个子树为空，就不满足要求，就退出。
			比如验证是否为平衡二叉树的时候，
			“一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1 ”
			其中任意一个孩子为空的话，就会构成他的其中一个子树的高度确定了，这个时候就要返回，算另一个子树
			110. 平衡二叉树
			```C++ []
					if (node == NULL) return 0;
			 ```
		  2、如果它的左右子树都为空的时候，就退出。
			  一般而言，就是用来啊、判断是否遍历到了子节点。
			  257. 二叉树的所有路径
				```C++ []
				if (cur->left == NULL && cur->right == NULL) return 0;

		  3、结束条件的判断的写法，要和你递归函数的入参要对应。要不然出现空指针访问的问题。
			  3.1、入参是子节点指针，结束条件的判断，一定要是对root的判断。 searchBST(root->left, val); 《-----》  if (root == NULL || root->val == val) return root;
				如果对root->left，就会出现nullptr->left，自然就会报错。
			  3.2、入参是root节点非子节点，结束条件的判断，才可以是对root->left等判断。
			  3.3、具体什么时候采取什么样的判断，要根据入参来。而什么样的入参，要根据题目的思路来。多体会吧。
			  3.4、  700. 二叉搜索树中的搜索 可以参考这个题目


		## 在树中返回值的选择
			> 1、当你发现返回值不是很好写的时候，考虑一下不要返回值，数据的修改放到参数加引用的时候。这句话很白话，但有时候确实是这样。——257. 二叉树的所有路径
			  2、一般情况下：如果需要搜索整棵二叉树，那么递归函数就不要返回值。如果要搜索其中一条符合条件的路径，递归函数就需要返回值，因为遇到符合条件的路径了就要及时返回。——具体看112，113这两个题目

		## 树的题目中有些是判断，最后返回一个bool量
			> 这种题目有个固定的写法，
			  在递归函数中，先判断各种true、false的情况，然后都返回。
			  然后再开始递归。
			  参考：101. 对称二叉树 100. 相同的树

		## 突然有个想法，树的题目基本上都是递归。
			> 既然都是递归，我发现很多题目树的构造，都是到了叶子节点后，然后返回上去，让root-》left 和root-》right去接，
			  既然是这样，在做题目的时候，思考的思路从底部往上走，可能更简单一些

		## 二叉搜索树
			若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
			若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
			它的左、右子树也分别为二叉搜索树
			1、“中序遍历”正确的搜索树，它的顺序是从小到大的。


		二叉树的题目中，一般都用判断题目，比如上面的判断是否为二叉搜索树，或者是其他题目，
		都是遇到false就返回，不对true做判断。然后不断的往下递归，直到结束都没遇到false这才说明整个函数才能返回true。
*/



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

		//中序遍历--二刷
		void traversal(TreeNode* root, vector<int> &ret) {
			if (root == nullptr)return;
			traversal(root->left, ret);
			ret.push_back(root->val);
			traversal(root->right, ret);
			return;
		}
		vector<int> inorderTraversal(TreeNode* root) {
			vector<int> ret;
			traversal(root, ret);
			return ret;
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
		//102. 二叉树的层序遍历
		vector<vector<int>> levelOrder(TreeNode* root) {
			if (root == nullptr) return vector<vector<int>>();//！！别忘了这个
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
					TreeNode* note = que.front();//!!每次循环拿到最新的节点
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


		//102. 二叉树的层序遍历—二刷
		vector<vector<int>> levelOrder2(TreeNode* root) {
			vector<vector<int>>ret;
			if (!root) return ret; //！！别忘了这个。 如果根节点为空，则直接返回空向量
			queue<TreeNode*> que;
			que.push(root);
			while (!que.empty())
			{
				int qsize = que.size();
				vector<int> tmp;
				for (size_t i = 0; i < qsize; i++)
				{
					TreeNode* curnote = que.front();
					que.pop();

					tmp.push_back(curnote->val);
					if (curnote->left) que.push(curnote->left);
					if (curnote->right) que.push(curnote->right);
				}
				ret.push_back(tmp);
			}
			return ret;
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

		//104. 二叉树的最大深度-二刷
		int getdepth2(TreeNode* node) {
			if (node == nullptr)return 0;
			int Ldeep = getdepth(node->left);
			int Rdeep = getdepth(node->right);
			return max(Ldeep, Rdeep) + 1;

		}
		int maxDepth2(TreeNode* root) {
			return getdepth2(root);
		}


		/*
		104. 二叉树的最大深度

		参考思路：
			这种思路更简洁！更好理解，最重要的符合层序遍历的思路
		参考：
			https://programmercarl.com/0102.%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E5%B1%82%E5%BA%8F%E9%81%8D%E5%8E%86.html#_104-%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E6%9C%80%E5%A4%A7%E6%B7%B1%E5%BA%A6
		*/
		int maxDepth3(TreeNode* root) {
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

			swap(root->right, root->left);//核心：进入一层新的节点后，交换他们的左右孩子。
			invertTree(root->right);
			invertTree(root->left);
			return root;
		}
		//226. 翻转二叉树--二刷
		TreeNode* invertTree2(TreeNode* root) {
			if (root == nullptr) return nullptr;
			swap(root->left, root->right);

			invertTree2(root->left);
			invertTree2(root->right);
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
			/*
			!!!这个地方一定要是判断“左val和右val不相等”。如果判断相等在这返回了，假设
					1
				2		2 如果判断相等，到这就不下去了.下面的就没有办法判断了。
			3    3	  3  4 核心就在于只要出现了不对称的情况就得立马返回。这个时候已经得出不对成的结论了。
			对称了，要继续往下判断，知道根节点
			*/
			if (Lroot->val != Rroot->val) return false;
			//判断对称，最左边和最右边的对比（左孩子的左节点和右孩子的右节点）。
			return isSame(Lroot->left, Rroot->right) && isSame(Lroot->right, Rroot->left);
		}


		//101. 对称二叉树---二刷
		bool isSame2(TreeNode* L, TreeNode* R) {
			if (L == nullptr&&R == nullptr)return true;
			if (L != nullptr&&R == nullptr)return false;
			if (L == nullptr&&R != nullptr)return false;
			if (L->val != R->val)return false;
			return isSame2(L->left, R->right) && isSame(L->right, R->left);
		}
		bool isSymmetric2(TreeNode* root) {
			return isSame(root->left, root->right);
		}

		//101. 对称二叉树---三刷
		bool isSame3(TreeNode* L, TreeNode* R) {
			if (L == nullptr && R == nullptr)return true;
			if (L != nullptr && R == nullptr)return false;
			if (L == nullptr && R != nullptr)return false;
			if (L->val != R->val)return false;
			bool Lret = isSame3(L->left, R->right);//Lret是当前层级节点左节点的左节点和右节点的右节点判断的结果
			bool Rret = isSame3(L->right, R->left);
			return Lret && Rret;//二叉树的遍历都是向上返回当前层级的结果,所以这里就是把当前层级的左结果和右结果'与运算',然后返回!
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
			if (preorderEnd == preorderBegin) return nullptr;

			int rootValue = preorder[preorderBegin];//找到当前前序数组的根节点
			TreeNode* root = new TreeNode(rootValue);

			//!!因为是区间是一测闭，一侧开。所以当差值是1的时候，点就剩一个了，这就是叶子节点了。所以需要返回这个点了。
			if (preorderEnd - preorderBegin == 1) return root;

			int delimiterIndex;//分割的位置.这个是在中序数组中寻找的。
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
			无论是哪种排序方式，它的子树的长度都是一样的，都是那几个对应的字符对应的。
			所以在前序中左子树的长度，就是在中序中拿到左子树的长度，
			计算方法：
				 中序“根节点位置”- “中序节点开始的位置” = “左子树的长度”
				 拿到了“左子树的长度”后。
				 前序“数组的起始位置” + 1+“左子树的长度” = “左子树的结束位置”。从而得到了后序数组中左子树的数据。
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
			// 左闭右开的原则。所以size()后面不用-1
			return traversal(inorder, 0, inorder.size(), preorder, 0, preorder.size());
		}


		//105. 从前序与中序遍历序列构造二叉树——二刷
		TreeNode* buildTre2(vector<int>& preorder, int preorderBegin, int preorderEnd, vector<int>& inorder, int inorderBegin, int inorderEnd) {
			if (preorderBegin == preorderEnd)return nullptr;
			TreeNode* root = new TreeNode(preorder[preorderBegin]);
			//!!因为是区间是一测闭，一侧开。所以当差值是1的时候，点就剩一个了，这就是叶子节点了。所以需要返回这个点了。
			if (preorderEnd - preorderBegin == 1)return root;

			int cutIndex = 0;//分割的位置,在中序数组上。
			for (cutIndex = inorderBegin; cutIndex < inorderEnd; cutIndex++)
			{
				if (inorder[cutIndex] == root->val)//找到了分割的位置。
					break;
			}

			//!一定是先切中序数组
			int leftInorderBegin = inorderBegin;
			int leftInorderEnd = cutIndex;
			int rightinorderBegin = cutIndex + 1;
			int rightinorderEnd = inorderEnd;

			//然后切割前序数组：左子树长度leftInorderEnd - leftInorderBegin
			int leftPreorderBegin = preorderBegin + 1;//!!别忘了前序数组，根节点在前面
			int leftPreorderEnd = (preorderBegin + 1) + (leftInorderEnd - leftInorderBegin);//左子树的位子就是在起始位置上+左子树长度。
			int rightPreorderBegin = (preorderBegin + 1) + (leftInorderEnd - leftInorderBegin);//右子树起始位置就是上个位置的后面。！注意是左闭又开区间，所以这个不用+1
			int rightPreorderEnd = preorderEnd;

			root->left = buildTre2(preorder, leftPreorderBegin, leftPreorderEnd, inorder, leftInorderBegin, leftInorderEnd);
			root->right = buildTre2(preorder, rightPreorderBegin, rightPreorderEnd, inorder, rightinorderBegin, rightinorderEnd);
			return root;
		}

		TreeNode* buildTree2(vector<int>& preorder, vector<int>& inorder) {
			if (preorder.empty() || inorder.empty()) return nullptr;
			return buildTre2(preorder, 0, preorder.size(), inorder, 0, inorder.size());
		}




		/*
		106. 从中序与后序遍历序列构造二叉树
		参考思路：
			这个和106. 从中序与后序遍历序列构造二叉树思路很相似
			思路也不复杂，简单来说：
			1、从后序数组中的最后的位置拿到根节点。
			2、找到根节点的值了，从中序数组中找到这个值，然后记录下这个位置。
			（！先切割中序，再切割后序。千万别弄错。）
			3、（切割中序）根据这个位置，把中序数组分为两部分。这样就知道左、右子树的长度。
				也知道了左子树的开始和结束，和右子树的开始和结束。
			4、（切割后序）知道了左子树的长度后，在后序数组中，数组开头位置+左子树的长度就是左子树的位置；剩余的部分就是右子树和最后面的根节点。
				也知道了左子树的开始和结束，和右子树的开始和结束。
			5、然后进入下次递归，这个“根节点”的左子树的参数就是 中序和后序的左子树的开始和结束

			另外，中序和前序也是这样的思路；
		注意：
			顺序别搞反了，一定是先切中序数组。卡子哥这么说的，我也不知道为啥，我试了确实不行。
		参考链接：
			https://www.programmercarl.com/0106.%E4%BB%8E%E4%B8%AD%E5%BA%8F%E4%B8%8E%E5%90%8E%E5%BA%8F%E9%81%8D%E5%8E%86%E5%BA%8F%E5%88%97%E6%9E%84%E9%80%A0%E4%BA%8C%E5%8F%89%E6%A0%91.html#%E6%80%9D%E8%B7%AF
			我把它归到同一个函数，经过测试是可以的
		*/

		/*
			目前感觉这个方法简单一些。
			注意：
				vector虽然是传的引用，只是为了节省性能，不会更改他的内容。
				这几个位置，对应的数都是在原始的位置上
		*/
		// 中序区间：[inorderBegin, inorderEnd)，后序区间[postorderBegin, postorderEnd)
		TreeNode* buildTree3(const vector<int>& inorder, int inorderBegin, int inorderEnd, const vector<int>& postorder, int postorderBegin, int postorderEnd) {
			//简单理解：traversal是处理各个左右子树，当他是空的时候，两者就相等。
			if (postorderBegin == postorderEnd) return nullptr;
			//if (inorderBegin == inorderEnd) return nullptr;//这个也行


			int rootValue = postorder[postorderEnd - 1];//找到当前后序数组的后序遍历的根节点
			TreeNode* root = new TreeNode(rootValue);

			//因为是区间是一测闭，一侧开。所以当差值是1的时候，点就剩一个了，这就是叶子节点了。所以需要返回这个点了。
			if (postorderEnd - postorderBegin == 1) return root;

			int delimiterIndex;//分割的位置
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
			无论是哪种排序方式，它的子树的长度都是一样的，都是那几个对应的字符对应的。
			所以在后序中左子树的长度，就是在中序中拿到左子树的长度，
			计算方法：
				 中序“根节点位置”- “中序节点开始的位置” = “左子树的长度”
				 拿到了“左子树的长度”后。
				 后序“数组的起始位置” + “左子树的长度” = “左子树的结束位置”。从而得到了后序数组中左子树的数据。
			*/
			// 切割后序数组
			// 左后序区间，左闭右开[leftPostorderBegin, leftPostorderEnd)
			int leftPostorderBegin = postorderBegin;
			int leftPostorderEnd = postorderBegin + (delimiterIndex - inorderBegin); // 终止位置是 需要加上 中序区间的大小size 左后序的结束，
			// 右后序区间，左闭右开[rightPostorderBegin, rightPostorderEnd)
			int rightPostorderBegin = postorderBegin + (delimiterIndex - inorderBegin);//
			int rightPostorderEnd = postorderEnd - 1; // 排除最后一个元素，因为这个元素就是当层树的根节点。

			root->left = buildTree3(inorder, leftInorderBegin, leftInorderEnd, postorder, leftPostorderBegin, leftPostorderEnd);
			root->right = buildTree3(inorder, rightInorderBegin, rightInorderEnd, postorder, rightPostorderBegin, rightPostorderEnd);

			return root;
		}
		TreeNode* buildTree3(vector<int>& inorder, vector<int>& postorder) {
			if (inorder.size() == 0 || postorder.size() == 0) return NULL;
			// 左闭右开的原则
			return buildTree3(inorder, 0, inorder.size(), postorder, 0, postorder.size());
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
		题目：
			要求就是前序遍历二叉树，然后按照顺序创建“假链表”，其实是一个只有右节点的树。
		思路：
			核心：如果当前节点存在左子节点，那么就把这个左子节点移动到右子节点位置。


			先往左遍历一个点，然后一直往右遍历，直到最后一个右节点。
			让这个右节点接到根节点的左节点。
			然后根节点的右节点接上他原来的左节点。

			然后根节点再往左下走，直到空
		参考：
			两个链接是一个思路，
			图好理解：https://leetcode.cn/problems/flatten-binary-tree-to-linked-list/solutions/17274/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by--26/?envType=study-plan-v2&envId=top-interview-150
			代码：https://leetcode.cn/problems/flatten-binary-tree-to-linked-list/solutions/1498323/by-lin-shen-shi-jian-lu-k-z5vv/?envType=study-plan-v2&envId=top-interview-150
		*/
		void flatten(TreeNode* root) {
			while (root)
			{
				TreeNode* p = root->left;//先保存左节点的指针。
				if (p) {//如果存在右节点那么才需要调整，也就是把它移动到右边。没有的话就继续往右边走。
					//不断的找刚才左节点的“最右边”的节点，是为了让这个“最右边”的节点后面接新的节点，当然也是接在它的右节点。
					//之所以是最右边的位置，是题目中要求的是形成有右边一条边的二叉树的“链表”。你接左边，肯定不能成一条边。
					while (p->right)
						p = p->right;//找左子节点的“最右边的节点”
					p->right = root->right; //让这个“最右边的节点的右节点”接上“当前节点的右节”点。
					//这四句代码，不要调换顺序。
					root->right = root->left;//把左节点移动到右节点的位置
					root->left = nullptr;//根节点左树被右节点接上后，左节点一定要赋值为空。也就是断开这个左树，要不然会出问题
				}
				root = root->right;//上面已经把左边都移动到右边了，下一步自然也是移动 按照右边的位置移动右节点。
			}
		}





		//114. 二叉树展开为链表——二刷
		void flatten2(TreeNode* root) {
			while (root) {
				TreeNode* tmpNode = root->left;
				if (tmpNode) {
					while (tmpNode->right) {
						tmpNode = tmpNode->right;
					}
					tmpNode->right = root->right;
					//这四句代码，不要调换顺序。
					root->left = nullptr;
					root->right = root->left;
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
			就是看二叉树最右侧的点
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
					TreeNode* node = que.front();//!!!!层序遍历，别忘了把这俩放在while中，我忘了好几次了。
					que.pop();
					if (i == queSize - 1)//遍历到了该层的最后位置
						ret.push_back(node->val);//只要这一层的最后一个
					if (node->left)que.push(node->left);
					if (node->right)que.push(node->right);
				}
			}
			return ret;
		}

		//199. 二叉树的右视图-二刷
		vector<int> rightSideView2(TreeNode* root) {
			vector<int>ret;
			if (root == nullptr)return ret;
			queue<TreeNode*> que;
			que.push(root);
			while (!que.empty())
			{
				int size = que.size();
				for (size_t i = 0; i < size; i++)
				{
					TreeNode* curNode = que.front();
					que.pop();
					if (i == size - 1)
						ret.push_back(root->val);
					if (curNode->left)que.push(curNode->left);
					if (curNode->right)que.push(curNode->right);
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
		思路:
			就是判断某一点的左右子树的高度,
			如果高度差超过1,就是不平衡的,这个时候返回-1;然后不断的向上传递
			上面再判断此层级的左右子树的高度差,如果还是-1,然后继续返回-1
			如果不是,则取左右子树的高度差的绝对值,只要>1,还是不平衡,然后继续返回-1
			如果此层级的左右子树是平衡的,就返回此层级的左右子树哪个高,就返回高的+1.
		*/
		// 返回以该节点为根节点的二叉树的高度，如果不是平衡二叉树了则返回-1
		int getHeight(TreeNode* node) {
			if (node == NULL) {//如果这个节点都不存在，这个node高度就是0.为什么是0呢？根据题目来看，只有一个点的时候，node高度是1
				return 0;
			}
			int leftHeight = getHeight(node->left); // （左） 当前节点为根节点的左节点的高度
			if (leftHeight == -1)
				return -1;//如果发现这个子树不平衡了，啥也不用做，直接返回吧。
			int rightHeight = getHeight(node->right); // （右）当前节点为根节点的右节点的高度
			if (rightHeight == -1)
				return -1;//如果发现这个子树不平衡了，啥也不用做，直接返回吧。

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



		//110. 平衡二叉树--二刷
		int getHeight1(TreeNode* root) {
			if (root == nullptr)
				return 0;

			int lh = getHeight1(root->left);
			if (lh == -1)
				return -1;

			int rh = getHeight1(root->right);
			if (rh == -1)
				return -1;

			if (abs(rh - lh) > 1)
				return -1;
			return max(rh, lh) + 1;
		}

		bool isBalanced1(TreeNode* root) {

			if (getHeight1(root) == -1)
				return false;
			return true;
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
		long long isValidBST_MaxValue = LONG_MIN; // 因为后台测试数据中有long long最小值,int_min范围不够用
		bool isValidBST(TreeNode* root) {
			if (root == nullptr)return true;//都遍历到底了，还没问题，说明这个搜索树肯定好
			bool l = isValidBST(root->left);
			if (root->val > isValidBST_MaxValue)
				isValidBST_MaxValue = root->val;
			else
				return false;

			bool r = isValidBST(root->right);
			//!最后发明的结果是root左子树和右子树都满足结果才是真的满足。
			return l && r;
		}

		//98. 验证二叉搜索树-二刷
		long long isValidBST_ret = LONG_MIN; // 因为后台测试数据中有long long最小值,int_min范围不够用
		bool isValidBST2(TreeNode* root) {
			if (root == nullptr) return true;
			bool L = isValidBST2(root->left);
			if (root->val > isValidBST_ret)
				isValidBST_ret = root->val;
			else
				return false;
			bool R = isValidBST2(root->right);
			return R && L;
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
			代码简单，思路复杂.
			！这个是通用的 235 236都可以用！
		核心思路：
			！“后序遍历”
			找到了p和q就往上父节点返回。
			直到他俩返回的父节点是一样的。
		参考：
			https://www.programmercarl.com/0236.%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E6%9C%80%E8%BF%91%E5%85%AC%E5%85%B1%E7%A5%96%E5%85%88.html#%E6%80%9D%E8%B7%AF
		*/
		TreeNode* lowestCommonAncestor1(TreeNode* root, TreeNode* p, TreeNode* q) {
			if (root == nullptr || root == p || root == q) return root;
			TreeNode*leftFlag = lowestCommonAncestor1(root->left, p, q);//返回“当前层root”左子树的结果。为null，说明当前层root”左子树没有q或p。不为null，说明有
			TreeNode*rightFlag = lowestCommonAncestor1(root->right, p, q);//返回“当前层root”右子树的结果
			//！指针是否空就是当前层的root左子树或者右子树是否含有qp的标示。！
			if (leftFlag&&rightFlag)
				return root;//当前层root的左子树和右子树都分别找到了qp（提议中节点不重复，不会出现两个qq的情况）。说明当前层的root是他们的公共祖先，那么就返回。
			else if (leftFlag == nullptr&&rightFlag)
				return rightFlag;// 当前层root的右子树有找到了相应的节点，把这个节点返回上去。为了在回溯的时候让他的父节点，爷爷节点或者更高的节点，这一路下来都有标示——它们其中一路中已经有了一个q或者p。直到遇到左节点也有标示的时候,说了这层的root是他们的公共祖先。
			else if (leftFlag &&rightFlag == nullptr)
				return leftFlag;//同理
			else
				return nullptr;
		}



		//236. 二叉树的最近公共祖先——二刷
		TreeNode* lowestCommonAncestor3(TreeNode* root, TreeNode* p, TreeNode* q) {
			if (root == nullptr || root == p || root == q) return  root;
			TreeNode* leftFlag = lowestCommonAncestor3(root->left, p, q);
			TreeNode* rightFlag = lowestCommonAncestor3(root->right, p, q);

			if (leftFlag&&rightFlag)
				return root;
			else if (leftFlag&&rightFlag == nullptr)
				return leftFlag;
			else if (leftFlag == nullptr&&rightFlag)
				return rightFlag;
			else
				return nullptr;
		}



		/*
		235. 二叉搜索树的最近公共祖先
		参考：
			https://www.programmercarl.com/0235.%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E7%9A%84%E6%9C%80%E8%BF%91%E5%85%AC%E5%85%B1%E7%A5%96%E5%85%88.html
		*/
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
		！！！以上都是对数组构造二叉树的问题中，所带来的开闭区间的取舍。对这个问题而言，可看可不看。

		二叉搜索树的构造就不用了。
		比如-10 -3 0 5 9 中间的0就是分割点，
		我要的是-10 -3 之所以“可以说”是闭区间，是因为我的代码中，不需要向上面的题目中，把分割点的下标再传进去。
		所以，闭开只是为了方便理解题目罢了，不是核心。最终还是记忆，不同的题型，用不同的方法。
		思路：
			它给提供的是升序数组。每次取中点，然后用中点创建一个点，左边是小于中点的值，接在中点的左边；同理大于中点的值，接在右侧。

		*/
		TreeNode* sortedArrayToBST1(vector<int>& nums, int left, int right)
		{
			if (left > right) return  nullptr;//当左》右，这种不合理的情况旧不要再分了。说明到了叶子节点，返回nullptr
			int mid = left + (right - left) / 2;//注意此处，（(right + left) / 2;）可能会出现int越界.。这个地方和二叉查找是一样的。
			TreeNode* root = new TreeNode(nums[mid]);
			root->left = sortedArrayToBST1(nums, left, mid - 1);//中点2 递归接2左边所有的点
			root->right = sortedArrayToBST1(nums, mid + 1, right);//中点2 递归接2右边所有的点
			return root;//返回根节点

		}
		TreeNode* sortedArrayToBST(vector<int>& nums) {
			return sortedArrayToBST1(nums, 0, nums.size() - 1);
		}

		//108. 将有序数组转换为二叉搜索树——二刷
		TreeNode* sortedArrayToBST3(vector<int>& nums, int L, int R) {
			if (L > R) return nullptr;
			int mid = L + (R - L) / 2;
			TreeNode* root = new TreeNode(nums[mid]);
			root->left = sortedArrayToBST3(nums, L, mid - 1);
			root->right = sortedArrayToBST3(nums, mid + 1, R);
			return root;
		}
		TreeNode* sortedArrayToBST2(vector<int>& nums) {
			return sortedArrayToBST3(nums, 0, nums.size() - 1);
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


		/*
		543. 二叉树的直径
		参考
			https://leetcode.cn/problems/diameter-of-binary-tree/solutions/142094/shi-pin-jie-shi-di-gui-dai-ma-de-yun-xing-guo-chen/?envType=study-plan-v2&envId=top-100-liked
			我的代码，和他的有些区别，但是是一样的思路，他的ppt做的很好
		思路：
			后序遍历二叉树，
			记录每个节点的左子树和右子树的和，也就是每个节点的“直径”，
			通过max保存一个最大直径，然后返回这个直径就行
			同过递归，每次递归返回当前的节点的直径+1；
		*/
		int diameterOfBinaryTree_ret = 0;
		int diameterOfBinaryTree_traversal(TreeNode* node)
		{
			if (node == nullptr) return 0;
			int L = diameterOfBinaryTree_traversal(node->left);//得到左侧节点的深度
			int R = diameterOfBinaryTree_traversal(node->right);//得到右侧节点的深度
			diameterOfBinaryTree_ret = max(diameterOfBinaryTree_ret, L + R);//从当前的已知的最大直径ans，和当前节点的“L+R”得到的新直径中，拿到最新的最大直径。
			return max(L, R) + 1;//往上返回当前节点的最大直径+1。+1是因为放回上一层，也就是返回到他的父节点的时候，直径要+1
		}

		int diameterOfBinaryTree(TreeNode* root) {
			diameterOfBinaryTree_traversal(root);
			return diameterOfBinaryTree_ret;
		}


		//543. 二叉树的直径——二刷
		int diameterOfBinaryTree_ret2 = 0;
		int diameterOfBinaryTree_traversal2(TreeNode* root) {
			if (root == nullptr)return 0;
			int L = diameterOfBinaryTree_traversal2(root->left);
			int R = diameterOfBinaryTree_traversal2(root->right);
			diameterOfBinaryTree_ret2 = max(diameterOfBinaryTree_ret2, L + R);
			return max(L, R) + 1;

		}
		int diameterOfBinaryTree2(TreeNode* root) {
			diameterOfBinaryTree_traversal(root);
			return diameterOfBinaryTree_ret2;
		}



		/*
		230. 二叉搜索树中第K小的元素
		参考：
			https://leetcode.cn/problems/kth-smallest-element-in-a-bst/solutions/1051273/fu-xue-ming-zhu-er-cha-shu-san-chong-bia-yn34/?envType=study-plan-v2&envId=top-100-liked
		思路：
			！看到二叉搜索树，就要想到中序遍历，中序遍历搜索二叉树，二叉树的值从小到大的。
			中序遍历，把数值放到数组中，然后返回k-1的位置的元素。
			这个题目，假设k=1，就要返回第一个位置的，也就是位置0的元素，具体看题目
		*/
		void kthSmallest(TreeNode* node, vector<int>& vec) {
			if (node == nullptr) return;
			kthSmallest(node->left, vec);
			vec.push_back(node->val);
			kthSmallest(node->right, vec);
			return;
		}
		int kthSmallest(TreeNode* root, int k) {
			vector<int> ret;
			kthSmallest(root, ret);
			return ret[k - 1];
		}


		//230. 二叉搜索树中第K小的元素-二刷-二叉搜索树就要想到中序遍历
		void kthSmallest2(TreeNode* root, vector<int> &ret) {
			if (root == nullptr)  return;
			kthSmallest2(root->left, ret);
			ret.push_back(root->val);
			kthSmallest2(root->right, ret);
			return;
		}
		int kthSmallest2(TreeNode* root, int k) {
			vector<int> ret;
			kthSmallest2(root, ret);
			return ret[k - 1];
		}



		/*
		437. 路径总和 III
		题意：
			求该二叉树里节点值之和等于 targetSum 的 路径 的数目。路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。
		参考：
		https://leetcode.cn/problems/path-sum-iii/solutions/615524/rang-ni-miao-dong-de-hui-su-qian-zhui-he-ou6t/?envType=study-plan-v2&envId=top-100-like
			他这个代码中，最新的测试用列会有问题，就是 int currSum太小了，就得换成 long currSum。
			这个和560. 和为 K 的子数组很相似，多看看
		思路：
			从根节点 root 到节点 node的前缀和为 currSum，我们保存前缀和中。
			然后去查找是否存在某一个节点的前缀和刚好等于 currSum−targetSum。发现根节点 root到pi 的前缀和为 currSum-targetSum。
			说明节点 pi到 node的路径上所有节点的和一定为 targetSum。
			！因为代码中是递归，所以一定能保证root---- other--- pi ----node是在一条路的。
			！代码中有回溯。意味着和他不相连的那些路径都删掉了。pathSum_umap[currSum]--;//！！回溯的时候，把这一层的前缀和再减去
		举例：
			假设targetSum=8
					root---- other--- pi ----node
			元素值  5		  6        5	   3
			前缀和	5		 11       16      19
			pi到node之间的元素的和，就是8.
		核心：
			1、他是从后往前找的，思路上有点别扭。
			   前缀和累计到19后，这个时候去找（19-8=11），就往前回头找11.找到了就说明有路径。找不到就继续往下递归。
			2、虽然看题目上，有些路径和根节点无关，但是遍历都是从根节点出发的，起始还是逃不了和根节点的关系
		*/
		unordered_map<long, long>pathSum_umap;//key是前缀和 value是该前缀和出现的次数、！！ 别忘了测试中数比较大，要用long类型
		void pathSum_travarsel(TreeNode* node, int targetSum, long currSum, int &ret) {
			if (node == nullptr)return;
			currSum += node->val;//更新前缀和
			if (pathSum_umap.find(currSum - targetSum) != pathSum_umap.end()) {//当找到了对应的前缀和的时候，次数ret= ret+ pathSum_umap[currSum - targetSum]
				ret = ret + pathSum_umap[currSum - targetSum];//！！这里不能是单纯的++。因为同样符合“currSum - targetSum”可能会有多条路线。
			}
			pathSum_umap[currSum]++;//前缀和是currSum的路线数量++
			pathSum_travarsel(node->left, targetSum, currSum, ret);
			pathSum_travarsel(node->right, targetSum, currSum, ret);
			pathSum_umap[currSum]--;//！！回溯的时候，把这一层的前缀和再减去
			return;
		}
		int pathSum(TreeNode* root, int targetSum) {
			int ret = 0;
			pathSum_umap[0] = 1;//前缀和为0，就是啥也没有，就是个空树。但是前缀和0的出现次数就是1。！！测试中有空数。
			long currSum = 0;
			pathSum_travarsel(root, targetSum, currSum, ret);
			return ret;
		}


		//437. 路径总和 III-二刷
		unordered_map<long, long> pathSum2_umap;
		void pathSum2_traval(TreeNode* root, int targetSum, long curSum, int& ret) {
			if (root == nullptr) return;
			curSum += root->val;
			if (pathSum2_umap.find(curSum - targetSum) != pathSum2_umap.end()) {
				ret += pathSum2_umap[curSum - targetSum];
			}
			pathSum2_umap[curSum]++;
			pathSum2_traval(root->left, targetSum, curSum, ret);
			pathSum2_traval(root->right, targetSum, curSum, ret);
			pathSum2_umap[curSum]--;
			return;
		}
		int pathSum2(TreeNode* root, int targetSum) {
			pathSum2_umap[0] = 1;
			int ret = 0;
			long curSum = 0;
			pathSum2_traval(root, targetSum, curSum, ret);
			return ret;
		}



		/*
		124. 二叉树中的最大路径和
		题意：
			求二叉树中的最大的路径和。
			同一个节点在一条路径序列中至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。
		参考：
			https://leetcode.cn/problems/binary-tree-maximum-path-sum/solutions/18040/er-cha-shu-zhong-de-zui-da-lu-jing-he-by-ikaruga/?envType=study-plan-v2&envId=top-100-liked
			思路是一样的，但是代码参考了评论区的“cheney”。
		思路：
			看这个代码，从树底部往上走比较好理解.
			后序遍历，并不是后序遍历有什么特点才选用。后来的代码写完才发现是后续遍历。
			遍历某一个节点的时候，确定左节点的最大值，右节点的最大值。
			如果左或者右节点的值小于0.就没有必要留下来，这样只会拖累结果。《0就让他等0就行
			然后当前节点+左+右。就得到目前节点的最大值，通过max不断的留下更大的值。
			递归的返回，上层节点要的是左或右中较大的一个+当前的值。（为什么这么做呢？因为一条路径，从当前节点通过，只能到左或右）
				上层（上层的路径：当前+左 或 当前+右）
				当前（递归从这返回到上面）
			左		右
		*/

		int maxPathSum_tarval(TreeNode* root, int &ret) {
			if (root == nullptr)return 0;
			int L = max(0, maxPathSum_tarval(root->left, ret));//当前节点的“左节点”的最大值
			int R = max(0, maxPathSum_tarval(root->right, ret));//当前节点的“右节点”的最大值
			ret = max(ret, root->val + L + R);//当前节点+左+右，也就是当前节点的路径的最大值。
			return root->val + max(L, R);//返回当前节点父节点“通过当前节点”的路径的最大值，具体看上图

		}
		int maxPathSum(TreeNode* root) {
			int ret = INT_MIN;//因为某些树的最大结果是个负值，所以你不能直接赋值0。要不然他的最大值就是0了
			maxPathSum_tarval(root, ret);
			return ret;
		}


		//124. 二叉树中的最大路径和——二刷
		int maxPathSum_tarval2(TreeNode* root, int &ret) {
			if (root == nullptr)return 0;
			int l = max(0, maxPathSum_tarval2(root->left, ret));
			int r = max(0, maxPathSum_tarval2(root->right, ret));
			ret = max(ret, root->val + l + r);//!别弄错root->val + l + r不是ret + l + r，写太快忽略了。
			return root->val + max(l, r);
		}
		int maxPathSum2(TreeNode* root) {
			int ret = INT_MIN;
			maxPathSum_tarval2(root, ret);
			return ret;
		}


		/*
		103. 二叉树的锯齿形层序遍历
		题意:
			就是二叉树层序遍历
			只不过,先从左往右,然后从右往左.接着再从左往右......
		参考:
			https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/submissions/555361472/
		思路:
			其实就是二叉树的层序遍历,然后多了两个部分
			1.这个题目中会给一个空树,所以在刚开始往队列中添加的时候,记得判断根结点是否为空.纯"二叉树层序遍历"没有空树
			2.根据题目要求,到了奇数层的时候,翻转这层二叉树的数据
		*/
		vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
			vector<vector<int>> ret;
			queue<TreeNode* > que;
			if (root)
				que.push(root);//别忘了!!这个,要不然报错.题目中有空的树
			while (!que.empty())
			{
				int size = que.size();
				vector<int> tmp;
				for (size_t i = 0; i < size; i++)
				{
					TreeNode* curNode = que.front();
					tmp.push_back(curNode->val);
					que.pop();
					if (curNode->left)
						que.push(curNode->left);
					if (curNode->right)
						que.push(curNode->right);
				}
				if (ret.size() % 2 == 1)
					reverse(tmp.begin(), tmp.end());
				ret.push_back(tmp);
			}
			return ret;
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


			vector<int> preorder{ 3,9,20,15,7 };
			vector<int> inorder{ 9,3,15,20,7 };
			vector<string> nodes = { "3","9","20","null","null","15","7" };
			treeRoot = createBinaryTree(nodes);//构建树
			//cout << pathSum(treeRoot, -1) << endl;
			/*vector<int> srtVec = lowestCommonAncestor(treeRoot);
			for (size_t i = 0; i < srtVec.size(); i++)
				std::cout << srtVec[i] << endl;
				*/



			vector<vector<int>> srtVec = zigzagLevelOrder(treeRoot);
			for (size_t i = 0; i < srtVec.size(); i++)
				for (size_t l = 0; l < srtVec[i].size(); l++)
					std::cout << srtVec[i][l] << endl;



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
		题意:
			给你一个手机键盘.每次给你一个数字字符串,然后返回这个数字字符串所拥有的字符,
			所能组成的所有字符串.
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
			string tmpStr = iponeStr[digits[index] - '0'];//拿到对应数字的对应字母.!!!!这里是减0,别弄错了!!digits里面是数字字符
			for (size_t i = 0; i < tmpStr.size(); i++)
			{
				letterCombinations_signal.push_back(tmpStr[i]);//举例abc和def;首先是a,然后是进入新的递归然后是d,这样就组成了ad,然后d被删除后,新的for,然后ae.然后af,然后bd...直到结束
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








		//17. 电话号码的字母组合--二刷
		vector<string> letterCombinations_ret2;
		string letterCombinations_signalret;
		string iponeNum[10] = { "","","abc","def", "ghi", "jkl", "mno", "pqrs", "tuv","wxyz" };
		//digits题目给的数字字符串  index本次递归用到的第几个数字
		void letterCombinations_dfs(string &digits, int index) {
			if (letterCombinations_signalret.size() == digits.size()) {
				letterCombinations_ret2.push_back(letterCombinations_signalret);
				return;
			}

			string tmpStr = iponeNum[digits[index] - 'a'];
			for (size_t i = 0; i < tmpStr.size(); i++) {
				letterCombinations_signalret.push_back(tmpStr[i]);
				letterCombinations_dfs(digits, index + 1);
				letterCombinations_signalret.pop_back();
			}
			return;
		}

		vector<string> letterCombinations2(string digits) {
			if (digits.empty())return vector<string>();
			letterCombinations_dfs(digits, 0);
			return letterCombinations_ret2;
		}


		/*
		39. 组合总和
		题意:
			给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，
			找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合 ，并以列表形式返回。你可以按 任意顺序 返回这些组合.
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

		//39. 组合总和 二刷
		vector<vector<int>> combinationSum_ret2;
		vector<int> combinationSum_signalret2;
		void combinationSum2_resever(vector<int>& candidates, int target, int sum, int index) {
			if (sum > target)return;
			else if (sum == target) {
				combinationSum_ret2.push_back(combinationSum_signalret2);
				return;//!!别忘了这个return
			}

			for (size_t i = index; i < candidates.size(); i++)
			{
				combinationSum_signalret2.push_back(candidates[i]);
				combinationSum2_resever(candidates, target, sum + candidates[i], 0);//!!这是组合,所以index从i开始,要是排列就可0开始.232 和223 在组合中是一样的
				combinationSum_signalret2.pop_back();
			}
			return;
		}
		vector<vector<int>> combinationSum_2(vector<int>& candidates, int target) {
			combinationSum2_resever(candidates, target, 0, 0);
			return combinationSum_ret2;
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
		题意:
			给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是回文串。返回 s 所有可能的分割方案。
			正着读和反着读,都是一样的,就是回文串
		参考：
			https://www.programmercarl.com/0131.%E5%88%86%E5%89%B2%E5%9B%9E%E6%96%87%E4%B8%B2.html#%E6%80%9D%E8%B7%AF
		思路:
			！！这个题的最要注意的地方就是：
			1\递归函数的下次开始的地方 不在是固定的startIndex + 1,而是真正对应结束位置的i，然后+1 才是新位置。
			2\!hot100的递归题目中,startIndex是下标,它== s.size()的时候,都是越界了,但因为他是i+1递归来的,上面是size-1,
			比如aab.
			第一层取a,然后判断a是不是回文,是就放到单个结果中
			第二层取a,然后判断,最后放到单个结果中
			第三层取b,然后判断,最后放到单个结果中
			到底了,单个结果放到总结果中.
			然后开始回溯,回到第1层中,aab的两个a都被取了,现在取ab,返现不是回文,继续回溯.
			就这么一直到结束

			!!看二刷的题目,这个写的比较复杂.
		*/
		vector<vector<string>> partition_ret;
		vector<string > partition_singal;
		//2.1、确定返回值和参数
		void partitionTracking(const string & s, int startIndex)
		{
			//2.2、确定回溯函数结束条件.
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
				把"i - startIndex + 1" 改成 "i"
				一下思路，看链接的图去理解最好了。
				对于aab而言，纵向的单个a a b都取完了。
				然后开始取ab，这个时候，递归回到第二层（看图）
				for的横向遍历， ab截取a是一个i，截取"ab"是第二个i 所这个时候判断回文的范围应该是startindex 到 i
				*/
				//!!startIndex到i的字符串是回文串,然后把字符串放到结果中.然后进入进的递归中,i要往后偏移,接着就是判断后面的字符串是不是回文,就这么一直递归下去.
				if (isPalindrome(s, startIndex, i))
				{
					string cutSrt = s.substr(startIndex, i - startIndex + 1);//截取开始的位置,和数量
					partition_singal.push_back(cutSrt);
					/*
					?!为什么说递归从i+1开始 而不是寻常的startIndex + 1开始
					!!这个地方我当时,应该是理解错了,我二刷的时候发现都是i从"i+1"开始.
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
		//判断传入的字符串s,从begin到end,是不是回文串
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

		//131. 分割回文串-二刷
		vector<vector<string>> partition2_ret;
		vector<string> partition2_sigle;
		void partition2_traval(string s, int startIndex) {
			for (size_t i = startIndex; i < s.size(); i++)
			{
				if (isPalindrome(s, startIndex, i)) {
					string str = s.substr(startIndex, i - startIndex + 1);
					partition2_sigle.push_back(str);
					if (i == s.size() - 1)//当下标走到最后一个字符串的时候,上面已经判断是回文字符串了,就把子结果放到总结果中
						partition2_ret.push_back(partition2_sigle);
					partition2_traval(s, i + 1);
					partition2_sigle.pop_back();
				}
			}
		}
		vector<vector<string>> partition2(string s) {
			partition2_traval(s, 0);
			return partition2_ret;
		}




		/*
		93. 复原 IP 地址
		参考：
			https://www.programmercarl.com/0093.%E5%A4%8D%E5%8E%9FIP%E5%9C%B0%E5%9D%80.html
		思路:
			不断的递归,每次递归移动一个位置,然后检查切除来的数据是否合法!
			具体还是看链接,这说不清楚
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
					s.insert(s.begin() + i + 1, '.');//+1的原因是因为 要把.插入到i的后面
					pointNum += 1;
					restoreIpAddressesTrack(s, i + 2, pointNum);// 插入逗点之后下一个子串的起始位置为i+2
					pointNum -= 1;
					s.erase(s.begin() + i + 1);
				}
				else
					break;//!!一定要用break.比如01,01已经不合法了,后面的更不合法,看isValid所有的不合法的条件,都一样,前面的不合法,后面的更不合法
			}
		}
		bool isValid(const string& s, int start, int end)
		{
			//“”101023  s = "10.10.23."当组合成这个情况的时候，start=9 end=8
			//因为当pointNum==3的时候，会有这种情况，新的开始开始位置就是结束位置+1，很明显就超了，这种就要返回false
			if (start > end) {//!!还真有这个情况
				return false;
			}
			if (s[start] == '0' && start != end) { // 0开头的数字不合法,除非是单个的0
				return false;
			}
			if (stol(s.substr(start, end - start + 1)) > 255)//stoi范围太小
				return false;
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
		思路:
			和组合题目很相似,可以联系"46 全排列"题目对着看.
			其实还是把他想象成一棵树,每个排列都是叶子节点,然后不断的回溯向上走,然后向下走.
		*/
		vector<vector<int>> subsets_ret;
		vector<int>subsets_signal;
		//2.1、确定返回值和参数
		void subsetsTracking(const vector<int>& nums, int startIndex) {
			//这个题目特殊的是它的结果是它遍历中的每一个都是，而不是满足了什么条件才是,所以递归结束条件才不一样
			subsets_ret.push_back(subsets_signal);// 收集子集，要放在终止添加的上面，否则会漏掉自己
			//2.2、确定回溯函数结束条件
			if (startIndex == nums.size())return;//每次排列的开始都在旧位置+1,所以当排列到最后元素的时候,就说明排列该结束了.
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


		//78. 子集--二刷
		vector<vector<int>> subsets_ret2;
		vector<int>subsets_signalret2;
		void subsetsTravsel2(vector<int>& nums, int startIndex) {
			subsets_ret2.push_back(subsets_signalret2);
			if (startIndex == nums.size()) return;

			for (size_t i = startIndex; i < nums.size(); i++) {

				subsets_signalret2.push_back(nums[i]);
				subsetsTravsel2(nums, i);
				subsets_signalret2.pop_back();
			}
			return;
		}


		vector<vector<int>> subsets2(vector<int>& nums) {
			subsetsTravsel2(nums, 0);
			return subsets_ret2;
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
		题意:
			给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。
		参考：
			https://www.programmercarl.com/0046.%E5%85%A8%E6%8E%92%E5%88%97.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路:
			used数组用来标记那些元素被用了。之前都是用来去重。
			每次开始的位置都是0，因为他是排列。不是组合，比如12 有12 21 ，组合12 21是一个，
			排列中取了2之后，发现1还没取就要去取了，
			元素取没取，用used数组来判断。

			总体来说,代码写起来很简单.回溯递归的题目就是理解起来麻烦.
		*/
		vector<int>permute_signal;//单个的组合结果
		vector<vector<int>>permute_ret;//最终的组合结果
		void permute_tracking(vector<int>& nums, vector<bool>& used)
		{
			//在叶子节点上取结果
			if (permute_signal.size() == nums.size())//单个结果的长度和原数组相同.
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
				//假设是123,现在i走到了元素3的位置,然后回溯,这个时候3的位置used=fasle.然后单个结果中删掉3,
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




		//46.全排列--二刷
		//!!一点想法:刷hot100的时候,发现46全排列和17电话号码,没用到used数组,而是在每次递归的时候,用到了新的开始下标.这个题目也是能改嘛?
		//确实可以;参考:https://leetcode.cn/problems/permutations/solutions/2363882/46-quan-pai-lie-hui-su-qing-xi-tu-jie-by-6o7h/?envType=study-plan-v2&envId=top-100-liked
		//那么都换成这个部分
		//!!他这个虽然实现了+1的方式,但是结果不对.我也是试了很多方式,都比较恶心,也没试出来,就这样把


		vector<int>permute_signalret2;
		vector<vector<int>>permute_ret2;
		void permute2(vector<int>& nums, vector<int>& uesd) {
			if (permute_signalret2.size() == nums.size()) {
				permute_ret2.push_back(permute_signalret2);
				return;
			}

			for (size_t i = 0; i < nums.size(); i++) {
				if (uesd[i] == true)
					continue;
				permute_signalret2.push_back(nums[i]);
				uesd[i] = true;
				permute2(nums, uesd);
				uesd[i] = false;
				permute_signalret2.pop_back();
			}
			return;
		}

		vector<vector<int>> permute2(vector<int>& nums) {
			vector<int> uesd(nums.size(), false);
			permute2(nums, uesd);
			return permute_ret2;
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
		题意:
			按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
			给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。
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

		//n是棋盘的宽度  row是当前递归到棋盘的第几行了  signalchessboard构造的单个棋盘
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


		/*
		22. 括号生成
		题意:
			数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
		参考：
			https://leetcode.cn/problems/generate-parentheses/solutions/938191/shen-du-you-xian-bian-li-zui-jian-jie-yi-ypti/?envType=study-plan-v2&envId=top-100-liked
			他的图话的话的很好，如果不明白，就看这个图
			我这个和题解不太一样。但思路都是一样的，我这个更好理解和记忆
		思路：
			一串括号要想满足条件；1、左右括号的数量一致。2、左括号可以临时大于右括号
			用递归的方法，
			1、只要左括号不超括号数量，先添加左括号；
			2、然后添加右括号数量。!添加右括号的时候，右括号的数量小于左括号的数量，才能再加右括号
			3、直到左右括号数量都是n个的时候，就是把括号都用完了的时候。把结果保存下来。
			4、最后返回结果
			比如2对数量的时候，(->((->(()->(()) 这个时候记录结果 ，然后一直向上回溯到(->()->()(->()()
		*/
		//n括号数量 Ln左括号数量 Rn右括号数量  str要加的括号字符 ret 用来记录结果
	public:
		void generateParenthesis_bfs(int n, int Ln, int Rn, string str, vector<string>& ret) {
			if (Ln > n && Rn > n)
				return;
			if (Ln == n && Rn == n)
				ret.push_back(str);
			if (Ln < n || Rn < n) // 如果左括号或者右括号还没用完
			{
				if (Ln < n)//当左括号还没用完
					generateParenthesis_bfs(n, Ln + 1, Rn, str + "(", ret);
				if (Rn < Ln) // 右括号《左括号
					generateParenthesis_bfs(n, Ln, Rn + 1, str + ")", ret);
			}
		}
		vector<string> generateParenthesis(int n) {
			vector<string> ret;
			generateParenthesis_bfs(n, 0, 0, "", ret);
			return ret;
		}



		//22. 括号生成--二刷,比上面的那个方法好点
		void generateParenthesis_bfs2(int n, int Ln, int Rn, string str, vector<string>& ret) {
			if (n == Ln && n == Rn)
				ret.push_back(str);
			if (Ln < n)//当左括号还没用完
				generateParenthesis_bfs2(n, Ln + 1, Rn, str + "(", ret);
			if (Rn < n && Rn < Ln)//右括号没用完,并且右括号的数量还小于左括号的时候.可以添加新的右括号了.
				generateParenthesis_bfs2(n, Ln, Rn + 1, str + ")", ret);
			return;
		}
		vector<string> generateParenthesis2(int n) {
			vector<string> ret;
			generateParenthesis_bfs2(n, 0, 0, "", ret);
			return ret;
		}





		/*
		79. 单词搜索
		题意:
			给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。
			如果 word 存在于网格中，返回 true ；否则，返回 false。
		参考：
			https://leetcode.cn/problems/word-search/solutions/2361646/79-dan-ci-sou-suo-hui-su-qing-xi-tu-jie-5yui2/?envType=study-plan-v2&envId=top-100-liked
			代码虽然有点区别,但思路是一样的.
		思路：
			深度递归+剪枝
			深度递归，检查4个不同的方向。如果单词不匹配，或者越界，返回false
			别忘了剪枝——board[row][col] = ' ';和恢复board[row][col] = word[k];
		*/
		//当前元素在矩阵 board 中的行列索引 i 和 j ，当前目标字符在 word 中的索引 k 。
		bool exist_dfs(vector<vector<char>>& board, string word, int row, int col, int k) {
			if (row < 0 || row >= board.size() ||
				col < 0 || col >= board[0].size() ||//越界
				board[row][col] != word[k])//单词不匹配
				return false;
			//如果遍历到word的最后，说明符合条件了，返回true
			if (k == word.size() - 1) return true;//??为什么要-1.abc 找的a的时候k=0;b,k=1;c,k=2;可以看到k=2的时候,所有的字符都找到了.
			//这个是一定的，假设abcb，这种带重复的就会出现问题，假设矩阵中只有一个b，abc都找到了，另外一个b实际上没有，但是你回溯的时候，如果你原先不清出，那么原先的b就会用上，就会满足条件。
			board[row][col] = ' ';//标记当前矩阵元素： 将 board[i][j] 修改为 空字符 '' ，代表此元素已访问过，防止之后搜索时重复访问。
			//上下左右遍历,顺序无所谓
			bool ret = exist_dfs(board, word, row, col + 1, k + 1) ||
				exist_dfs(board, word, row, col - 1, k + 1) ||
				exist_dfs(board, word, row - 1, col, k + 1) ||
				exist_dfs(board, word, row + 1, col, k + 1);
			//清完一个要恢复过来，不恢复的话，万一第一次尝试不行，换条路又找他了，发现路是缺失的.
			board[row][col] = word[k];//!!注意,用的是word来恢复.
			return ret;//上面是或，只要有一个true就可以
		}
		bool exist(vector<vector<char>>& board, string word) {
			//这里通过两层for,从矩阵中的左上角一个个作为单词的起点开始测试.直到发现了一个能够成功的起点.
			for (size_t i = 0; i < board.size(); i++) {
				for (size_t l = 0; l < board[0].size(); l++) {
					//如果true就是返回true，不行就返回false
					if (exist_dfs(board, word, i, l, 0))
						return true;
				}
			}
			return false;
		}


		bool exist2_bfs(vector<vector<char>>& board, string word, int row, int col, int k) {
			if (row >= board.size() || col >= board[0].size() ||
				row < 0 || col < 0 ||
				board[row][col] != word[k])
				return false;

			if (word.size() - 1 == k)
				return true;

			board[row][col] = ' ';

			bool ret = exist2_bfs(board, word, row, col + 1, k + 1) ||
				exist2_bfs(board, word, row, col - 1, k + 1) ||
				exist2_bfs(board, word, row - 1, col, k + 1) ||
				exist2_bfs(board, word, row + 1, col, k + 1);
			board[row][col] = word[k];

			return ret;
		}
		//79. 单词搜索,二刷
		bool exist2(vector<vector<char>>& board, string word) {

			for (size_t row = 0; row < board.size(); row++) {
				for (size_t col = 0; col < board[0].size(); col++) {
					if (exist2_bfs(board, word, row, col, 0))
						return true;
				}
			}
			return false;
		}


		void test()
		{
			//2.1、确定返回值和参数
			//2.2、确定回溯函数结束条件
			//2.3、确定单层搜索的过程——！！for负责横向遍历，递归负责纵向遍历。
			vector<	vector<char> > graph{ {'A','B','C','E'},
			{'S','F','C','S'},{'A','D','E','E'} };
			string s = "bb";
			vector<int> nums = { 1,1,2 };
			vector<vector<string>> ret;
			ret = partition2(s);

			for (auto i : ret)
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
		题意 ：
			要从数组中，找到这些元素最大的累加和
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

		//二刷还是用贪心，好理解
		int maxSubArray2(vector<int>& nums) {
			int ret = INT32_MIN;
			int count = 0;
			for (int num : nums) {
				count += num;//从数组头开始，不断的累加。
				if (count > ret)//数组其中一部分累加值已经大于了之前ret，就更新ret
					ret = count;
				if (count < 0)//累加和对最后的结果没用，累加和直接清0；
					count = 0;
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
		题意:
			给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。
			判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。
		参考：
			https://www.programmercarl.com/0055.%E8%B7%B3%E8%B7%83%E6%B8%B8%E6%88%8F.html#%E6%80%9D%E8%B7%AF
		思路：
			先算出每走一步走，算出覆盖范围有多大，然后不断的往下走，然后不断更新更大的范围（局部最优），
			如果嘴个范围大于等于了这个数组的长度，说明符合条件。（全局最优解）
		*/
		bool canJump(vector<int>& nums) {
			int cover = nums[0];//你能走到的范围.如果这个范围能超过数组范围就说明能走到底
			for (int i = 0; i <= cover; i++)
			{
				cover = max(cover, i + nums[i]);//没走一步更新最大的范围
				if (cover >= nums.size() - 1)//-1是因为cover代表的是下标
					return true;
			}
			return false;
		}

		//55. 跳跃游戏
		bool canJump2(vector<int>& nums) {
			int cover = nums[0];
			for (int i = 0; i <= cover; i++) {//!!I要改成和cover的类型一样,要不然max不能匹配两个类型不同的关系.
				cover = max(cover, nums[i] + i);
				if (cover >= nums.size() - 1)
					return true;
			}
			return false;
		}




		/*
		45. 跳跃游戏 II
		题意:
			给定一个长度为 n 的 0 索引整数数组 nums。初始位置为 nums[0]。
			每个元素 nums[i] 表示从索引 i 向前跳转的最大长度。换句话说，如果你在 nums[i] 处，你可以跳转到任意 nums[i + j] 处:
			0 <= j <= nums[i];i + j < n
			返回到达 nums[n - 1] 的最小跳跃次数。生成的测试用例可以到达 nums[n - 1]
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
			if (nums.size() == 1) return 0;//别忘了当长度为1的时候,它走到末尾就是0步.!!这个不能去掉
			int step = 0;//走的步数
			int currCover = 0;//当前的最大范围
			int nextCover = 0;//下一步能走的最大范围
			for (int i = 0; i < nums.size(); i++) {
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


		//45. 跳跃游戏 II
		int jump2(vector<int>& nums) {
			if (nums.size() == 1) return 0;
			int currCover = 0;
			int nextCover = 0;
			int step = 0;
			for (int i = 0; i < nums.size(); i++) {
				nextCover = max(nextCover, nums[i] + i);
				if (nextCover > nums.size() - 1) {
					step++;
					break;
				}
				if (i == currCover) {
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
				//这个地方不用>,到了尾部的时候,就已经是字符串的尾部了,如果不是尾部的话,maxI肯定会更大.
				if (maxI == i)//遍历到了最大下标的位置，记录一下区间长度。
				{
					ret.push_back(maxI - begin + 1);
					begin = maxI + 1;//新的区间位置就是最大位置+1
				}
			}
			return ret;
		}


		//763. 划分字母区间-二刷
		vector<int> partitionLabels2(string s) {
			int begin = 0;
			int maxI = 0;
			int hashBuf[26];
			vector<int>ret;
			for (int i = 0; i < s.size(); i++) {
				hashBuf[s[i] - 'a'] = i;
			}
			for (int i = 0; i < s.size(); i++)
			{
				maxI = max(maxI, hashBuf[s[i] - 'a']);
				if (i == maxI) {
					ret.push_back(i - begin + 1);
					begin = i + 1;
				}
			}
			return ret;
		}





		/*
		56. 合并区间
		参考：
			https://www.programmercarl.com/0056.%E5%90%88%E5%B9%B6%E5%8C%BA%E9%97%B4.html#%E5%85%B6%E4%BB%96%E8%AF%AD%E8%A8%80%E7%89%88%E6%9C%AC
			和他的思路一样的，但是代码不精简。！！！！
		题意：
			输入：intervals = [[1,3],[2,6],[8,10],[15,18]]。把其中重复的区间合并就行了。
		思路：
			和上面的思路很是接近。
			首先，对数组排序。方便后续处理
			然后，遍历数组，先把第一个区间，放到结果中。
			然后，如果当前的元素的右值“大于等于”下个元素的左值，就说明两个区间和重叠的。
			然后，既然是重叠的，新结果中的区间右值，看是当前区间右值大还是重叠的那个区间右值大，谁大用谁。
			然后，区间合并，区间合并后，！！别忘了，在原先数组上，重叠的那个右区间的值要更新成新的右值。
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
					int newRvalue = max(ret.back()[1], intervals[i + 1][1]);//“结果中的右边界”和下个要合并的右边界，谁大要谁。
					ret.back()[1] = newRvalue;//更新结果中的右边界
					intervals[i + 1][1] = newRvalue;//，！！别忘了，在原先数组上，重叠的那个右区间的值要更新成新的右值。要是忘了.本来1,10就可以直接合完这三个，如果不更新intervals，后面还会再更新，就错了！
					//【1 10】 【5 6】 【8 9】 没有这个max就出问题
				}
				else
					ret.push_back(intervals[i + 1]);
			}
			return ret;
		}

		vector<vector<int>> merge2(vector<vector<int>>& intervals) {
			if (intervals.size() == 1)return intervals;
			sort(intervals.begin(), intervals.end(), [](vector<int>&a, vector<int>&b) {return a[0] < b[0]; });//对数组排序，按照每个小数组开头的元素大小
			vector<vector<int>> ret;
			ret.push_back(intervals[0]);
			for (size_t i = 0; i < intervals.size() - 1; i++)
			{
				if (intervals[i][1] >= intervals[i + 1][0]) {//如果当前的右边界超过下个的左边界，那么就合并
					int newRValue = max(ret.back()[1], intervals[i + 1][1]);//“结果中的右边界”和下个要合并的右边界，谁大要谁。
					ret.back()[1] = newRValue;//更新结果中的右边界
					intervals[i + 1][1] = newRValue;//更新数组中的右边界
				}
				else
					ret.push_back(intervals[i + 1]);//注意这里！这是两个当前边界和下个边界不重复的时候，自然就是要放[i+1]的数据，不是[i]的。
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
		题意:
			假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
			每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
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



		//70. 爬楼梯--二刷
		int climbStairs2(int n) {
			if (n < 4) return n;
			int fb[3];
			fb[0] = 0;
			fb[1] = 1;
			fb[2] = 2;
			fb[3] = 3;
			int sum = 0;
			for (size_t i = 4; i <= n; i++)//!!别忘了=;得有i=n的时候.
			{
				sum = fb[2] + fb[1];
				fb[1] = fb[2];
				fb[2] = sum;
			}
			return sum;
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
		题意:
			一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
			机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。
			问总共有多少条不同的路径？
			和上楼梯基本上是一样的,只不过这个是二维的.
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


		//62. 不同路径--二刷
		int uniquePaths2(int m, int n) {
			vector<vector<int>>dp(m, vector<int>(n, 0));
			for (size_t i = 0; i < m; i++)
				dp[i][0] = 1;
			for (size_t i = 0; i < n; i++)
				dp[0][i] = 1;
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
		题意:
			给你一个 只包含正整数 的 非空 数组 nums 。
			请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
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


			定义dp数组：
				dp[i]：背包总容量（所能装的总重量）是i，放进物品后，背的最大重量为dp[i]。也就是“容量,也就是元素的和”为i的时候，能存的最大的元素和是多少。
				比如dp[7]在这个“nums = [1,5,11,5]”中，dp[7]=6; 7代表dp能接受的和诗不大于7的，而在这个题目中，是没有办法直接加到7,最大只能是6
				当dp[11]的时候,dp[11]==11;这个时候数组可以分割成 [1, 5, 5] 和 [11]
				所以最后判断的时候，
				如果dp[sum/2]==sum/2;则说明满足条件。（也就是当让dp的最大值为sum/2的时候，他的dp[sum/2]的值也确实为sum/2，这是符合条件的）
			初始化dp数组：
				dp[0] =0;容量是0.存的是数也是0;
			确定dp数组等式：
				dp[i]=max(dp[i],dp[i-m[j]]+value[i]);
				这个地方不一样——他的重量和价值相同。
				所以：dp[i]=max(dp[i],dp[i-sum[j]]+sum[i]);
			确定遍历顺序：
				根据这个01背包问题的话，第二个for是倒叙遍历。
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
				for (size_t j = sum; j >= nums[i]; j--)//遍历背包“容量”——初始化用背包容量;判断条件:当前背包容量,要大于等于物品.才能放,要不然就结束循环.
				{
					dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
				}
			}
			if (dp[sum] == sum)
				return true;

			return false;
		}


		//416. 分割等和子集--二刷
		bool canPartition2(vector<int>& nums) {
			vector<int>dp(10001, 0);
			int sum = 0;
			for (int num : nums)
				sum += num;
			if (sum % 2 == 1)
				return false;
			sum = sum / 2;
			dp[0] = 0;
			for (size_t i = 0; i < nums.size(); i++)//物品
			{
				for (size_t l = sum; l >= nums[i]; l--)//背包
				{
					dp[l] = max(dp[l], dp[l - nums[i]] + nums[i]);
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
		题意:
			给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。
			计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。
			你可以认为每种硬币的数量是无限的。
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
			for (int i = 0; i < coins.size(); i++)//物品!!!!不要用<=.要不然下面的coins[i]报错.
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

		//322. 零钱兑换--二刷
		int coinChange2(vector<int>& coins, int amount) {
			vector<unsigned int> dp(amount + 1, INT_MAX);
			dp[0] = 0;
			for (int i = 0; i < coins.size(); i++)
			{
				for (int l = coins[i]; l <= amount; l++)
				{
					dp[l] = min(dp[l], dp[l - coins[i]] + 1);
				}
			}

			if (dp[amount] == INT_MAX)//还有兑钱兑不开的情况,所以要返回-1
				return -1;
			return dp[amount];
		}

		/*
		279. 完全平方数
		题意:
			给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。
			完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。
		参考：
			https://www.programmercarl.com/0279.%E5%AE%8C%E5%85%A8%E5%B9%B3%E6%96%B9%E6%95%B0.html
		题目说明：
			1 4 9 这种被称为“完全平方数”，这个题目要给一个n，然后这个是由“完全平方数”加起来组成的数。
			求用到的“完全平方数”的最少数量
		思路：
			每个“完全平方数”可以多次使用，完全背包问题。
			不在乎顺序，就是组合。但是本题目是最"最小数",先遍历物品还是背包都行.
			转换为背包思路：背包容量是n，“完全平方数”是每个物品的重量。
			问放满背包，“最少”有多少“物品”。
			1、定义dp：dp[j] 和为j的的时候,完全平方数的"最少"数量为dp[j]
			2、确定dp公式：看下面的注释
			3、初始化：dp[0]表示 和为0的完全平方数的最小数量，那么dp[0]一定是0。非0下标的dp[j]一定要初始为最大值，这样dp[j]在递推的时候才不会被初始值覆盖

		*/
		int numSquares(int n) {
			//size_t类型不能是int,超限.别忘了n+1，要不数组越界
			vector<size_t>dp(n + 1, INT_MAX);//从递归公式dp[j] = min(dp[j - i * i] + 1, dp[j]);中可以看出每次dp[j]都要选最小的，所以非0下标的dp[j]一定要初始为最大值，这样dp[j]在递推的时候才不会被初始值覆盖。
			dp[0] = 0;//题目描述,n从1开始,题目中没有0.所以给他赋值0就行,很多时候dp的初始化,道理讲的都有点牵强.
			for (size_t i = 0; i <= n; i++)//背包
			{
				//物品-J*J就是具体的要放的物品的重量，！物品要小于等于背包容量！
				for (size_t j = 0; j*j <= i; j++)
				{
					/*dp[i]：“i”背包容量；
					dp[i - j * j] + 1：dp[背包容量-当前物品重量]+1：拿掉当前物品“i - j * j”，然后加上新的物品就是物品数+1；*/
					dp[i] = min(dp[i - j * j] + 1, dp[i]);
				}
			}
			return dp[n];
		}



		//279. 完全平方数--二刷
		int numSquares2(int n) {
			vector<size_t>dp(n + 1, INT_MAX);
			//先后顺序就无所谓了.但, 还是推荐先遍历背包,再遍历物品,这样物品往背包中放的这种思路就体现的很明显
			for (size_t i = 0; i <= n; i++)//背包!!!都别忘了有"等于".也就是背包被装满,容量为n的时候.
			{
				for (size_t l = 0; l*l <= i; l++)//物品  "l*l"这个物品要 <="l"这个背包容量
				{
					dp[i] = min(dp[i], dp[i - l * l] + 1);//别写错了了,是l*l
				}
			}
			return dp[n];
		}

		//先遍历物品,再背包就有点不好理解.
		int numSquares3(int n) {
			vector<int> dp(n + 1, INT_MAX);
			dp[0] = 0;
			for (int i = 1; i * i <= n; i++) { // 遍历物品.i*i<=n.因为如果一个元素的平方都大于n了,那么这个元素就炒了,再怎么加都得不到n
				for (int j = i * i; j <= n; j++) { // 遍历背包 j = i * i.不能是 j = i;要不然报错.!!这个就不好理解
					dp[j] = min(dp[j - i * i] + 1, dp[j]);
				}
			}
			return dp[n];
		}

		/*
		139.单词拆分
		题意:
			给你一个字符串 s 和一个字符串列表 wordDict 作为字典。如果可以利用字典中出现的一个或多个单词拼接出 s 则返回 true。
			注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用
		参考：
			https://www.programmercarl.com/0139.%E5%8D%95%E8%AF%8D%E6%8B%86%E5%88%86.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			转成背包问题：
			此数组中拿到单词放到s中，看最后能不能放满背包。
			背包容量是要拼凑的单词的长度。
			dp[i]含义：
				当遍历到字符串s到位置i的时候，前面的都可以被“单词”组成
			递推公式：
				dp[i]很明显是依托于前面的部分。在前面能匹配上的前提下，后面的才有意义。
				如果i-j的区间能匹配，并且下标为j的时候也为true)，这个时候dp[i]=true
				这个题目和"300.最长递增子序列"很相似,
				假设下标i在下标j的后面,
				如果想要字符s在下标i这个位置能够组成字符串的话,
				前提他前面的坐标j是可以被单词组成,也就是下标j的dp[j]==true
				并且j到i这一块也是单词的一部分,也就是tring tmp = s.substr(j, i - j);ordSet.find(tmp) != wordSet.end();
				只有这样才能这个位置i的时候,才能都是被单词组成的.
			确定遍历顺序：
				对于组成单词而言，单词的顺序不能随意指定，所以就是排列。
			初始化：
				一开始一定要为true，要不然后面都是false了
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



		//139.单词拆分-二刷
		bool wordBreak2(string s, vector<string>& wordDict) {
			vector<bool>dp(s.size() + 1, false);
			dp[0] = true;
			unordered_set<string>uset(wordDict.begin(), wordDict.end());
			for (size_t i = 0; i <= s.size(); i++)//遍历背包容量的时候,背包的当前容量肯定得有和最大容量相等的时候,这个时候就用到"等于".所以是"<="
			{
				for (size_t l = 0; l < i; l++)
				{
					string tmp = s.substr(l, i - l);
					if (dp[l] == true && uset.find(tmp) != uset.end()) {
						dp[i] = true;
					}
				}
			}
			return dp[s.size()];
		}






		/*
		198.打家劫舍
		题目解析：
			从数组中偷，挨边的不能偷。
			计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。
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
				dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);//
			dp数组含义：
				dp[j] 偷到“下标为i”的时候最大价值
			递推公式：
				dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
			初始化：
				从递推公式来看，要初始化1，2,，但是dp[1]要为 0 1的最大值
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


		//198.打家劫舍-二刷
		int robErShua(vector<int>& nums) {
			if (nums.empty()) return 0;
			if (nums.size() == 1) return nums[0];
			vector<int> dp(nums.size());

			dp[0] = nums[0];
			dp[1] = max(nums[0], nums[1]);
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
			//cout << "利润 " << result << endl;
			return result;
		}


		//121. 买卖股票的最佳时机1--二刷
		int maxProfit1_3(vector<int>& prices) {
			int minValue = prices[0];
			int maxValue = prices[0];
			int maxRet = 0;
			for (size_t i = 0; i < prices.size(); i++)
			{
				if (prices[i] < minValue)
					minValue = prices[i];
				else if (prices[i] - minValue > maxRet)
					maxRet = prices[i] - minValue;
			}
			return maxRet;
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
		题意:
			给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
			子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。
		参考：
			https://www.programmercarl.com/0300.%E6%9C%80%E9%95%BF%E4%B8%8A%E5%8D%87%E5%AD%90%E5%BA%8F%E5%88%97.html
		思路：
			1、dp含义：dp[i]表示nums[i]结尾的最长递增子序列的长度
			2、dp递推公式：
				if (nums[i] > nums[l])
					dp[i]=max(dp[i-1]+1,dp[i]);
				假设下标i在下标l的后面,并且如果nums[i] > nums[l],说明l到i这段是递增的,
				那么这个时候,递增序列的最大长度要+1的.
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
			vector<int>dp(nums.size(), 1);//一定要初始化1,要不然过不去
			int ret = 0;
			for (size_t i = 1; i < nums.size(); i++)
			{
				for (size_t l = 0; l < i; l++)//我们是假设i是在l的后面,所以i的范围不能超过l.
				{
					if (nums[i] > nums[l])
						//!!这里加max是而不是"dp[i] = dp[l] + 1;".
						//举例,0,3,2,3.遍历大第一个3的时候,最长为2,遍历到2的是时候,长度应该也是2.
						//这个时候就出问题了,2比前面的小,所以它的长度就变成了默认值1,
						//其实这个时候,最长子序列还是2啊!!
						//题目中,最长子序列在随着数组往后遍历的时候,只会增加不会减少.(你细想一下)所以就用max,
						dp[i] = max(dp[l] + 1, dp[i]);
				}
				//放在理解起来麻烦点,因为i在l的后面,内部的for计算的就是i到l的距离中最大的长度,i从0到末尾,这样i往后走一次都代表以i结尾的数组的最长子序列,所以放在第一层的for中,这样就会在每一次更新i的时候,更新最长长度.
				ret = max(ret, dp[i]);//max放在内部的for也是可以的,但是放在这里比较省性能.
			}
			return ret;
		}




		//300.最长递增子序列--二刷
		int lengthOfLIS2(vector<int>& nums) {
			int ret = 0;
			vector<int>dp(nums.size(), 1);//dp数组的长度也不是都要+1,这里就不需要..
			for (size_t i = 0; i < nums.size(); i++)
			{
				for (size_t l = 0; l < i; l++)
				{
					if (nums[l] < nums[i])
						dp[i] = max(dp[i], dp[l] + 1);
				}
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
		题意:
			给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。
			输入：text1 = "abcde", text2 = "ace"
			输出：3
			解释：最长公共子序列是 "ace" ，它的长度为 3 。
		参考：
			https://www.programmercarl.com/1143.%E6%9C%80%E9%95%BF%E5%85%AC%E5%85%B1%E5%AD%90%E5%BA%8F%E5%88%97.html
		思考：
			这个题目的 重复子数组在text1或2中是可以“不连续的”。
			1、dp含义：
				dp[i][l] 代表从下表0到text1[i-1] text2[i-1]这个位置的最长子序列
				注意,它代表的是下标到i-1的位置.
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
					if (text1[i - 1] == text2[l - 1])//-1别忘了,因为"dp[i][l] 代表从下表0到text1[i-1] text2[i-1]这个位置的最长子序列"
						dp[i][l] = max(dp[i - 1][l - 1] + 1, dp[i][l]);
					else
						dp[i][l] = max(dp[i][l - 1], dp[i - 1][l]);
				}
			}
			return dp[text1.size()][text2.size()];
		}


		//1143.最长公共子序列---二刷
		int longestCommonSubsequence2(string text1, string text2) {
			vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1, 0));

			for (size_t i = 1; i < text1.size() + 1; i++)
			{
				for (size_t l = 1; l < text2.size() + 1; l++)
				{
					if (text1[i - 1] == text2[l - 1])
						dp[i][l] = max(dp[i - 1][l - 1] + 1, dp[i][l]);
					else
						dp[i][l] = max(dp[i - 1][l], dp[i][l - 1]);
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
		题意:
			给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数
			输入：word1 = "horse", word2 = "ros"
			输出：3
			解释：
			horse -> rorse (将 'h' 替换为 'r')
			rorse -> rose (删除 'r')
			rose -> ros (删除 'e')
		参考：
			https://www.programmercarl.com/0072.%E7%BC%96%E8%BE%91%E8%B7%9D%E7%A6%BB.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			和“583. 两个字符串的删除操作”非常像
			1、dp[i][j]：
				坐标i-1和j-1，最少的操作次数
				表示以下标i-1为结尾的字符串word1，和以下标j-1为结尾的字符串word2，最近编辑距离为dp[i][j]。
			2、公式
				i-1和j-1元素相等：
					dp[i-1][j-1];因为这两个元素相同，所以不用删除元素，也就不用添加删除次数。
				i-1和j-1元素不相等：
					增加：dp[i-1][j]+1(操作word1),或者dp[i][j-1]+1(操作word2)
					删除：dp[i-1][j]+1或者：dp[i][j-1]+1；和“增加”是一样的，比如abc和ab，增加c和去掉c都是一样，最后哪个小，就用谁就行。
					替换：dp[i-1][j-1]+1；dp[i-1][j-1]是前一次两者都相等，比如abc和abd，到了d开始不相等了，只需要操作一次就行
			3、初始化
				dp[i][0] ：以下标i-1为结尾的字符串word1，和空字符串word2，最近编辑距离为dp[i][0]。
				那么dp[i][0]就应该是i，对word1里的元素全部做删除操作，即：dp[i][0] = i;
				同理dp[0][j] = j;
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
					if (word1[i - 1] == word2[j - 1])//!!别忘了-1,因为"dp的i,l代表坐标i-1和j-1，最少的操作次数"
						dp[i][j] = dp[i - 1][j - 1];
					else//增加,删除,替换都是在这里
						dp[i][j] = min(dp[i - 1][j - 1] + 1, min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
				}
			}
			return dp[word1.size()][word2.size()];
		}


		//72. 编辑距离--二刷
		int minDistance2(string word1, string word2) {
			vector<vector<int>>dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
			for (size_t i = 0; i < word1.size() + 1; i++)
				dp[i][0] = i;
			for (size_t i = 0; i < word2.size() + 1; i++)
				dp[0][i] = i;

			for (size_t i = 1; i < word1.size() + 1; i++)
			{
				for (size_t l = 1; l < word2.size() + 1; l++)
				{
					if (word1[i - 1] == word2[l - 1])
						dp[i][l] = dp[i - 1][l - 1];
					else
						dp[i][l] = min(dp[i - 1][l - 1] + 1, min(dp[i][l - 1] + 1, dp[i - 1][l] + 1));
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
		118. 杨辉三角
		题意:
			给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。
			在「杨辉三角」中，每个数是它左上方和右上方的数的和
		参考：
			没什么参考的，看注释就明白
		思路：
			用三角不好理解，用下面的就好理解了
			1
			11
			121//第2行，才可以计算
			1321
		*/
		vector<vector<int>> generate(int numRows) {
			vector<vector<int>>ret(numRows);

			for (int i = 0; i < numRows; i++) {
				ret[i].resize(i + 1);//调整每层的长度，满足三角形的形状

				//两头放1
				ret[i][0] = 1;
				ret[i][ret[i].size() - 1] = 1;

				//计算中间的部分,因为头部不放，起始位置就是1.
				for (int l = 1; l < i; l++)//l最小是1.i也就是 2才能进，满足“第二行才能计算”的条件
				{
					ret[i][l] = ret[i - 1][l] + ret[i - 1][l - 1];
				}
			}
			return ret;
		}


		//118. 杨辉三角--二刷
		vector<vector<int>> generate2(int numRows) {
			vector<vector<int>> ret(numRows);
			for (size_t i = 0; i < numRows; i++)
			{
				ret[i].resize(i + 1);
				ret[i][0] = 1;
				ret[i][ret[i].size() - 1] = 1;
				for (size_t l = 1; l < i; l++)
				{
					ret[i][l] = ret[i - 1][l] + ret[i - 1][l - 1];
				}
			}
			return ret;
		}

		/*
		152. 乘积最大子数组
		题意:
			给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。
			测试用例的答案是一个 32-位 整数。
			输入: nums = [2,3,-2,4]
			输出: 6
			解释: 子数组 [2,3] 有最大乘积 6。
		参考：
			https://leetcode.cn/problems/maximum-product-subarray/solutions/7561/hua-jie-suan-fa-152-cheng-ji-zui-da-zi-xu-lie-by-g/?envType=study-plan-v2&envId=top-100-liked
		思路：
			动态规划——也就是这个状态是由上个状态推导出来。
			看他的图吧，很清楚。
			核心就是，当遍历到负数的时候，把最大值和最小值交换。
			假设是 2和3,这么做
			新最大值(2)*负数，得到的较大的负数，从某种意义上是相对最“大”值。
			新最小值(3)*负数，得到的较小的负数，从某种意义上是相对最“小”值。
			tmpMax，tmpMin都要初始化为1，要是0的话，假设数组只有一个-2，那么-2*0；就变成0是最大值了。
		*/
		int maxProduct(vector<int>& nums) {
			int maxRet = INT_MIN, tmpMax = 1, tmpMin = 1;// 初始化tmpMax和tmpMin为1，因为任何数与1相乘都保持不变  
			for (int num : nums) {
				if (num < 0)
					swap(tmpMax, tmpMin);
				tmpMax = max(tmpMax*num, num);//!!!注意是比较"当前元素"和"当前元素乘以之前的最大乘积"
				tmpMin = min(tmpMin*num, num);//ai说的,这样做是为了确保连续子数组的最大乘积在每一步都能得到正确的更新，保证最终得到的是整个数组中的最大乘积。
				maxRet = max(maxRet, tmpMax);//也不是很好理解,就记住吧
			}
			return maxRet;
		}

		//152. 乘积最大子数组
		int maxProduct2(vector<int>& nums) {
			int ret = INT_MIN;
			int tmpMax = 1, tmpMin = 1;
			for (int num : nums) {
				if (num < 0)
					swap(tmpMax, tmpMin);
				tmpMax = max(num, num*tmpMax);
				tmpMin = min(num, num*tmpMin);
				ret = max(ret, tmpMax);
			}
			return ret;
		}






		/*
		32. 最长有效括号
		题意:
			给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号子串的长度
			输入：s = ")()())"
			输出：4
			解释：最长有效括号子串是 "()()"
		参考：
			https://leetcode.cn/problems/longest-valid-parentheses/?envType=study-plan-v2&envId=top-100-liked
			其实这个，我没怎么明白，我按着代码写了一些自己的注释，实在不行，到时候就换热门的题解。
		思路：
			看注释吧
		*/
		int longestValidParentheses(string s) {
			int n = s.size();
			// dp[i]定义为以s[i-1]结尾的子串中最长有效括号长度
			vector<int> dp(n + 1, 0);

			// 从第三个位置开始遍历，为什么呢？这是因为这个程序是从尾巴往前看，第三个位置才能看前两个能不能组成括号
			for (int i = 2; i <= n; ++i) {
				// 如果上个字符是右括号')'  。这个程序是从尾巴往前看，说明前面可能有（括号。
				if (s[i - 1] == ')') {
					// 尝试寻找与当前右括号匹配的左括号'(' 。 
					int j = i - 2 - dp[i - 1];  //当前位置i-括号长度2- dp[i - 1](也就是这个元素前面的那个元素如果能组合成括号的话，直接到他最前面的位置，检查是不是(,能和后面的)匹配上)
					// 如果找到了匹配的左括号  
					if (j >= 0 && s[j] == '(') {
						// 更新dp[i]，
						// dp[j]是上面得到位置的，如果这个位置已经早就算出长度的话，就加上。 
						// dp[i - 1]这个元素前面的那个元素最长有效子串长度， 如果这个位置已经早就算出长度的话，就加上。 
						// 2是新增的有效括号对长度  
						dp[i] = dp[j] + dp[i - 1] + 2;
					}
				}
			}

			// 返回dp数组中的最大值，即最长有效括号子串的长度  
			// 注意这里是从dp[1]开始遍历到dp[n]，因为dp[0]没有实际意义  
			return *max_element(dp.begin(), dp.end());
			//return dp[n]; 这不是一个累加的，比如()())dp中的元素，()()这个时候是4，到)就变成0了。所以用上面的那种。
		}



		//32. 最长有效括号
		int longestValidParentheses2(string s) {



		}




		/*
		64. 最小路径和
		题意:
			给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
			说明：每次只能向下或者向右移动一步。
		参考：
			https://leetcode.cn/problems/minimum-path-sum/solutions/25943/zui-xiao-lu-jing-he-dong-tai-gui-hua-gui-fan-liu-c/?envType=study-plan-v2&envId=top-100-liked
		思路：
			动态规划。
			dp[i][j]代表到了ij位置的最小路径。
				不用额外的dp数组。假设走到了某一个点，把这个点的值修改成当前路径和，下面再往下走的时候，路径添加新的元素值，之前的点就已经加过了,所以不用再加了.
			核心：当前路径的长度= 当前点的值+ min（左路径，上路径）。
			1、遇到左边界，
			2、遇到上边界
			3、遇到左边界和上边界
			4、正常的点。
			最后，返回右下角的值
		*/
		int minPathSum(vector<vector<int>>& grid) {
			for (int i = 0; i < grid.size(); i++) {
				for (int l = 0; l < grid[0].size(); l++) {
					if (i == 0 && l == 0) continue;//把这个放到最前面，下面的不会越界。另外别忘了加else，要不然过不去
					//靠着左边界
					else if (l == 0) grid[i][l] = grid[i][l] + grid[i - 1][l];//这些靠边的点,得单独计算,要不放在这单独计算,要不放就像"62. 不同路径"放在外边初始化,我已经写出来,在下面的二刷.
					//靠着上边界
					else if (i == 0) grid[i][l] = grid[i][l] + grid[i][l - 1];
					else
						grid[i][l] = grid[i][l] + min(grid[i - 1][l], grid[i][l - 1]);
				}
			}
			return grid[grid.size() - 1][grid[0].size() - 1];
		}


		//64. 最小路径和--二刷--推荐这个方法--放在外面初始化,好理解
		int minPathSum2(vector<vector<int>>& grid) {
			for (size_t i = 1; i < grid.size(); i++)//靠着左边界
				grid[i][0] = grid[i][0] + grid[i - 1][0];
			for (size_t l = 1; l < grid[0].size(); l++)//靠着上边界
				grid[0][l] = grid[0][l] + grid[0][l - 1];
			for (int i = 1; i < grid.size(); i++) {
				for (int l = 1; l < grid[0].size(); l++) {
					grid[i][l] = grid[i][l] + min(grid[i - 1][l], grid[i][l - 1]);
				}
			}
			return grid[grid.size() - 1][grid[0].size() - 1];
		}


		/*
		5. 最长回文子串
		题意:
			给你一个字符串 s，找到 s 中最长的回文子串。
			如果字符串的反序与原始字符串相同，则该字符串称为回文字符串。
		参考：
			https://leetcode.cn/problems/longest-palindromic-substring/solutions/7600/5-zui-chang-hui-wen-zi-chuan-cc-by-bian-bian-xiong/?envType=study-plan-v2&envId=top-100-liked
		思路：
			这个题目的算法,我粗略的看了一下,有"中心扩展算法"和"动态规划",其实还是"中心扩展算法"好理解点.

			中心扩展算法
			扩展是有两种的方式，一种奇数的，满足aba这种；一种偶数的abba这种。
			然后不断更新回文字符的长度，最后返回一个最长的。

			动态规划
			参考:https://leetcode.cn/problems/longest-palindromic-substring/solutions/63641/zhong-xin-kuo-san-fa-he-dong-tai-gui-hua-by-reedfa/?envType=study-plan-v2&envId=top-100-liked
		*/
		string longestPalindrome(string s) {
			//别忘了这个
			if (s.length() < 1) // 如果字符串长度小于1，则直接返回空字符串
				return "";
			int start = 0, end = 0;
			for (int i = 0; i < s.size(); i++)
			{
				int len1 = longestPalindrome_expan(s, i, i);// 以当前字符为中心扩展
				int len2 = longestPalindrome_expan(s, i, i + 1);// 以当前字符和下一个字符为中心扩展
				int len = max(len1, len2);
				if (len > end - start) {//如果新的回文字符串超过了上次的长度
					start = i - (len - 1) / 2;//更新回文子串的坐标
					end = i + len / 2;
					//abba i=1的时候，len1=1，len2=4. 
					//i是你遍历到的字符串的下标;现在知道回文子串的长度，那么就len/2得到回文字串的半径，然后通过i+半径和i-半径.就能得到回文子串的开始和结束的位置
					//其实还是因为 数组的下标是从0开始的，然后在确定左边的时候，就得(len-1)/2 右边就是len/2
				}
			}
			//参数截取位置， 和截取的数量。数量肯定是end-start +1)
			return s.substr(start, end - start + 1);
		}

		int longestPalindrome_expan(string s, int L, int R) {

			while (L >= 0 && R < s.size() && s[L] == s[R])// 向两边扩展，直到不是回文串为止
			{
				L--;
				R++;
			}
			return R - L - 1;//不确定的时候 找个例子算算 比如aba 在遍历到b的时候i=1，第一次l=0 r=2，第二次i=-1，r=3. 这时候长度就是3- -1 =4 长度为4然后-1得到3
		}



		int longestPalindrome_expan2(const string &s, int L, int R) {
			while (L >= 0 && R < s.size() && s[L] == s[R])
			{
				L--;
				R++;
			}
			return R - L - 1;
		}

		//5. 最长回文子串--二刷
		string longestPalindrome2(string s) {
			if (s.size() < 1) return"";
			int start = 0, end = 0;

			for (size_t i = 0; i < s.size(); i++)
			{
				int len1 = longestPalindrome_expan2(s, i, i);
				int len2 = longestPalindrome_expan2(s, i, i + 1);
				int len = max(len1, len2);
				if (len > end - start) {
					start = i - (len - 1) / 2;//这两句记住就行
					end = i + len / 2;
				}
			}
			return s.substr(start, end - start + 1);
		}






		void test()
		{
			vector<vector<int>> grid{ {1, 3, 1}, {1, 5, 1}, {4, 2, 1}, {1, 2, 3}, {4, 5, 6} };
			string str = "aba";
			vector<int> dp{ -2,1,-3,4,-1,2,1,-5,4 };
			vector<int> dp1{ 3,2,1,4,7 };
			vector<int> coins = { 2 };
			int amount = 3;
			cout << coinChange2(coins, amount);
		}

	};
}

//单调栈
namespace Dandiaozhan
{
	class Solution {
	public:
		/*
		单调栈时间复杂度：。时间复杂度为O(n)。

		什么时候用单调栈呢？
			通常是一维数组，
			要寻找任一个元素的右边或者左边“第一个”比自己大或者小的元素的"距离"，
			以单调递增栈为例，栈顶元素最小，新的元素大于这个栈顶，那么就知道右边第一个比它大的元素；
			那么左边第一个比他大的元素也好理解。这是单调递增栈，左边第一个比他大的就是栈顶的下一个元素。
			这样就知道左边和右边第一个比自己大的元素了。

		单调栈里元素是递增呢？ 还是递减呢？
			如果求一个元素右边第一个更大元素，单调栈就是递增的，遇到小于等于栈顶元素的就入栈,大于栈顶元素的就出栈.
			如果求一个元素右边第一个更小元素，单调栈就是递减的,遇到大于等于栈顶元素的就入栈,小于栈顶元素的就出栈.

		单调栈的顺序：
			 从栈头到栈底，递增就是，单调递增栈。
		*/


		/*
		739. 每日温度
		参考：
			https://www.programmercarl.com/0739.%E6%AF%8F%E6%97%A5%E6%B8%A9%E5%BA%A6.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		题意：
			给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。
			如果气温在这之后都不会升高，请在该位置用 0 来代替
		思路：
			核心就是求右侧第一个大于该元素的距离。
			当元素小于栈顶元素，进栈
			当元素等于栈顶元素，进栈
			当元素大于栈顶元素：
				记录当前栈顶元素到该元素的距离——result[stk.top()] = i - stk.top();
				把所有大于的元素都出栈或者栈空了，把元素放进去。

			栈中放的元素是数组的下标
			结果数组的含义：result[1]=2;在数组中下标1的元素，它的右侧第一个大于它的元素，与他的距离为2.

			为什么单调递增栈符合条件？解释下。
			从栈顶到栈尾递增，这样的话，假设下标5的元素10；放到底部了，这个时候只要没有10大（包括等于10），都会入栈放到10的上面，
			如果新的元素比栈顶元素大，比如8吧，栈里就开始出栈，栈里存的是下标，用当前这个元素的下标-栈顶的下标，就能得到栈里这些元素和比它大的元素的距离。
			但10肯定是出不了，这个时候8再进栈，后面遇到了遇到了大于10的数，比如11；
			这个时候就开始出栈，用当前这个元素的下标-栈顶的下标。这样就能得到栈里8，10和11的距离。
		*/
		vector<int> dailyTemperatures(vector<int>& temperatures) {
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

		//二刷，还是上面的这个简化写法，代码简单，也好理解
		vector<int> dailyTemperatures2(vector<int>& temperatures) {
			vector<int>ret(temperatures.size(), 0);
			stack<int> stk;//要找的是右边第一个大于它的元素，用单调递增栈
			for (size_t i = 0; i < temperatures.size(); i++)
			{
				while (!stk.empty() && temperatures[i] > temperatures[stk.top()]) {//单调递增栈就是当前元素大于栈顶元素，就出栈
					ret[stk.top()] = i - stk.top();
					stk.pop();
				}
				stk.push(i);
			}
			return ret;
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
						3
				2  雨水 3
				2   1   3
			  左边  mid 右边
			这个做例子最好。
			这个题目只用了一个单调递增栈，遇到了大于栈顶的元素3。
			3做右边，栈顶元素1做mid，然后栈顶出栈，新的栈顶元素2做左边。
			当前这3个元素组成的雨水面积，are=(min(左高度，右高度)-mid的高度)*右下标-左下标，
			然后不断的累加这些小的面积，就得到总的面积。
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


		//二刷
		int trap2(vector<int>& height) {
			stack<int> stk;
			int ret = 0;
			for (size_t i = 0; i < height.size(); i++)
			{
				while (!stk.empty() && height[i] > height[stk.top()])
				{
					int midH = height[stk.top()];//中间元素的高度
					stk.pop();
					if (!stk.empty())
						ret += (min(height[i], height[stk.top()]) - midH)*(i - stk.top() - 1);
				}
				stk.push(i);
			}
			return ret;
		}


		/*
		84.柱状图中最大的矩形
		题意:
			给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
			求在该柱状图中，能够勾勒出来的矩形的最大面积。
		参考：
			https://www.programmercarl.com/0084.%E6%9F%B1%E7%8A%B6%E5%9B%BE%E4%B8%AD%E6%9C%80%E5%A4%A7%E7%9A%84%E7%9F%A9%E5%BD%A2.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE
		思路：
			有暴力和单调栈方法，这里用单调栈的方法。
			求遍历到的每一个下标，它左侧第一个最小的元素和右侧第一个最小的元素。
			为什么这么做呢？
			从当前坐标的高度往左右延申，直到遇见左右第一个比它矮的矩形，(具体为啥,我也不知道了,记住吧!!!!)
			这个时候所得到的面积，就是当前遍历的下标对应的最大矩形的面积.(这里别误解,着得到的是当前下标的最大的矩形,而不是整个图像中最大的矩形.)
			然后，取其中最大的面积，就是当前数组中，也就是柱状图中最大的矩形。


			既然要求所遇到的右侧第一个“较小”的元素，则用单调递减栈,从头到尾是单调递减的,遇到了小于栈顶栈顶元素的就要出栈.
			面积：
				are = hig*wid;
			宽度：
				和“接雨水”题目一样，是需要当前遍历元素和两个栈顶元素。
				hight=i mid=第一个栈顶元素 left=第二个栈顶元素（不明白就画个图）

				wid = 右边的第一个小于当前元素的坐标-左边第一个小于当前元素的坐标 - 1；
				wid = 当先遍历元素的下标 - 第二个栈顶元素-1；
				wid = i - stk.top() - 1;
			高度：
				hig=当前栈顶元素的值

			举例：
			以465为例，头尾加0；04650；
			元素：0 4 6 5 0
			下标：0 1 2 3 4
					l m r
			遍历到5的时候，出栈，这个mid=2； wid=(3-1-1)*6=6;
			其实就是求，以num[mid]为高，宽是以mid为中心，遇到左右两方第一个小于num[mid]高度的元素。其实高度6的，左右两边都比他小是下标1，3，所以wid=1

			元素：0 4 5 0
			下标：0 1 3 4
					l m r
			遍历到0的时候，出栈，这个mid=3； wid=(4-1-1)*5=10
			其实就是求，以num[mid]为高，宽是以mid为中心，遇到左右两方第一个小于num[mid]高度的元素。其实高度5的，左右两边都比他小是下标1，4，所以wid=2

			元素：0 4 0
			下标：0 1 4
				  l m r
			遍历到0的时候，出栈，这个mid=1； wid=(4-0-1)*4=12
			其实就是求，以num[mid]为高，宽是以mid为中心，遇到左右两方第一个小于num[mid]高度的元素。其实高度4的，左右两边都比他小是下标0，4，所以wid=3

			其他：
				遍历的数组头和尾各加一个0。
				题目中用的是一个单调递减栈，假设给的数组是【1234】，那么在代码中是一直不出栈的，最后的结果就是0。
				所以为了出栈，最后一定要有一个比所有矩形都小的值。题目中说了矩形的高度是》=1的。所以要设置一个0；

				假设给你数组是【4321】.遍历到3的时候，因为3《4所以要出栈，出栈完毕后就是空，接着有个if判断栈是否为空，这个时候是就会进不去、
				接着新的一次 for循环，栈加入新的坐标，
				然后新的循环，因为新的元素总是更小，所以栈立马就会出栈，然后栈空了，下面if又是过不了，然后新的循环又开始了；
				然后又重复上面的过程，最后结果还是0.
				所以为了保证栈里面最少要有两个元素，第一个元素很好添加，第二个元素怎么保证一定比第一个大呢？题目中说了矩形的高度是》=1的。所以数组开头要设置一个0；

			注意：
				结果不是一个累加值，而是不断的更新最大值。

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

		//二刷
		int largestRectangleArea2(vector<int>& heights) {
			int ret = 0;
			stack<int>stk;
			heights.push_back(0);
			heights.insert(heights.begin(), 0);

			for (size_t i = 0; i < heights.size(); i++)
			{
				while (!stk.empty() && heights[i] < heights[stk.top()])
				{
					int mid = stk.top();//记录矩形中点的坐标
					stk.pop();
					if (!stk.empty()) {
						int r = i;
						int l = stk.top();

						int wid = r - l - 1;
						ret = max(ret, wid*heights[mid]);
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
			vector<int> dp{ 4,6,5 };
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


		//200、岛屿数量——二刷
		void numIslands2_bfs(vector<vector<char>>& grid, vector<vector<bool>> &visited, int i, int l) {
			vector<vector<int>>dir{ {0,1},{0,-1},{1,0},{-1,0} };
			queue<pair<int, int>> gridNode;
			gridNode.push({ i, l });
			visited[i][l] = true;
			while (gridNode.size())
			{
				pair<int, int> curNode = gridNode.front();
				gridNode.pop();
				for (size_t dirIndex = 0; dirIndex < 4; dirIndex++)
				{
					int nextX = curNode.first + dir[dirIndex][0];
					int nextY = curNode.second + dir[dirIndex][1];
					if (nextX >= 0 && nextX < grid.size() && 0 <= nextY && nextY <= grid[0].size())
						if (visited[nextX][nextY] == false && grid[nextX][nextY] == '1') {
							gridNode.push({ nextX, nextY });
							visited[nextX][nextY] = true;
						}
				}
			}
			return;
		}
		int numIslands2(vector<vector<char>>& grid) {
			int ret = 0;//！别忘了初始化
			//vector<vector<bool>> visited(grid.size(), (grid[0].size(), false));//!!!这种初始化方法不行
			vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));//!!别忘了初始化它的空间，要不然后面越界报错
			for (size_t i = 0; i < grid.size(); i++) {
				for (size_t l = 0; l < grid[0].size(); l++) {
					if (visited[i][l] == false && grid[i][l] == '1') {
						ret++;
						numIslands2_bfs(grid, visited, i, l);
					}
				}
			}
			return ret;
		}

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
	public:
		/*
		994. 腐烂的橘子
		题意：
			一个腐烂的橘子的四周都会腐烂，每分钟腐烂一层，最后返回腐烂玩所有的橘子之所用的最少时间(分钟)。如果腐烂不完，就返回-1
			值 0 代表空单元格；
			值 1 代表新鲜橘子；
			值 2 代表腐烂的橘子。
		参考;
			https://leetcode.cn/problems/rotting-oranges/solutions/129542/yan-du-you-xian-sou-suo-python3-c-by-z1m/?envType=study-plan-v2&envId=top-100-liked
		思路：
			广度搜索，很适合这个思路，和我图论中用的广度搜索的代码差不多
			遍历这个图论，每一步都要走腐烂四周的橘子
			然后在新的腐烂的橘子四周，继续腐烂
			如果最后新鲜的橘子完全不剩下，就返回腐烂完需要的时间.
			腐烂不完，就返回-1
		注意：
			其他的图论的题目的时候，习惯了从左上角第一个点遍历图，比如“200. 岛屿数量”。
			这个题目却不用从左上角开始，任意一个位置就行。
			无论从哪个位置开始，都是会把腐烂橘子的四周一点点的都加上。
			“200. 岛屿数量”，不从左上角开始应该也行，我没试试
			！！和“200. 岛屿数量”不一样的是：while里面有2个for。
			这是为了保证最短时间才使用的。
			假设图的左上和右下角有两个点，但是如果没有外面的那个for，那么在一分钟内，只能腐烂一个角，这样就无法得到最短的时间了
		*/
		int orangesRotting(vector<vector<int>>& grid) {
			int step = 0;
			int fresh = 0;//整个途中，新鲜的橘子的数量。
			queue<pair<int, int>>rotten;//腐烂的橘子的坐标，rotten：腐烂
			for (size_t i = 0; i < grid.size(); i++) {
				for (size_t l = 0; l < grid[0].size(); l++) {
					if (grid[i][l] == 1)
						fresh++;
					else if (grid[i][l] == 2)
						rotten.push({ i, l });//把腐烂的橘子，放到队列中，来做广度遍历。因为内部是pair，别忘了{}
				}
			}
			vector<pair<int, int>>dirs = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
			while (!rotten.empty())
			{
				int n = rotten.size();//!这个n是必须放在这，放在for中，队列的大小会增大，就不是想要的当前这一轮要遍历的橘子的数量
				bool canNextStep = false;
				for (size_t i = 0; i < n; i++)//遍历腐烂的橘子
				{
					pair<int, int> orangeDir = rotten.front();//拿到一个腐烂的橘子坐标
					rotten.pop();
					for (size_t l = 0; l < 4; l++)//在当前的腐烂的橘子四周上遍历
					{
						int newX = orangeDir.first + dirs[l].first;
						int newY = orangeDir.second + dirs[l].second;
						//新的坐标不超边界，并且是新鲜的水果，就腐烂它
						if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size() &&
							grid[newX][newY] == 1)
						{
							canNextStep = true;
							grid[newX][newY] = 2;
							rotten.push({ newX ,newY });
							fresh--;//新鲜的水果数量-1
						}
					}
				}
				if (canNextStep)//！！每走一步，腐烂的橘子会腐蚀周围的4个点，所以要放在for外面。
					step++;
			}
			return fresh > 0 ? -1 : step;
		}


		//994. 腐烂的橘子——二刷
		int orangesRotting2(vector<vector<int>>& grid) {
			int fresh = 0;
			int step = 0;//腐烂完所有的新鲜的橘子，所需要的步数。
			queue<pair<int, int>> bad;//腐烂的橘子

			for (size_t i = 0; i < grid.size(); i++)
			{
				for (size_t l = 0; l < grid[0].size(); l++)
				{
					if (grid[i][l] == 1)
						fresh++;
					else if (grid[i][l] == 2)
						bad.push({ i,l });
				}
			}
			vector<vector<int>> dir{ {0,1},{0,-1},{1,0},{-1,0} };
			//遍历
			while (bad.size())
			{
				bool canNext = false;
				int size = bad.size();//!!别忘了这又两个for
				for (size_t l = 0; l < size; l++)
				{
					pair<int, int >currBad = bad.front();
					bad.pop();
					for (size_t i = 0; i < 4; i++)
					{
						int newX = currBad.first + dir[i][0];
						int newY = currBad.second + dir[i][1];
						if (0 <= newX && newX < grid.size() && 0 <= newY && newY < grid[0].size() && grid[newX][newY] == 1) {
							grid[newX][newY] = 2;
							canNext = true;
							fresh--;
							bad.push({ newX,newY });//！！新腐烂的橘子别忘了加
						}
					}
				}
				if (canNext)//！！上面的4个方向的for走完，就要走心的点，所以要放在for外面。
					step++;

			}
			return fresh > 0 ? -1 : step;
		}



		/*
		207. 课程表
		题意：
			numCourses = 2, prerequisites = [[1,0],[0,1]]
			总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的
			给你一个数组，按照上面题意，确定能否完成学习。
		参考：
			https://leetcode.cn/problems/course-schedule/solutions/18806/course-schedule-tuo-bu-pai-xu-bfsdfsliang-chong-fa/?envType=study-plan-v2&envId=top-100-liked
			什么是拓扑排序：https://blog.csdn.net/lisonglisonglisong/article/details/45543451
			什么是邻接表：https://zhuanlan.zhihu.com/p/618361957
			要理解这两个题目，首先要明白下面这两个概念
		思路：
			“拓扑排序”就是就是用来解决依赖问题。所以这问题就是要利用这个思路。
			“拓扑排序”思路就是删掉图中的“入度为0的点”，如果最后图中什么都不剩，就是“有向无环图”，就说明满足条件；否则就是不行。
			整个题目核心其实就是“拓扑排序”
			再说下“邻接表”是什么？
			在图中，比如1和2和+3相连，那么这个数组就是0开头，23在后面。代表的这是“0”的邻接表。
		*/
		//numCourses选修的科目数
		bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
			vector<int> rudubiao(numCourses, 0);//入度表;一维数组,下标是课程编号,值是入度.(这个题目中,科目都是连续的,也就都是从0开始!)
			//!!别忘了初始化，要不然错误
			vector<vector<int>> linjiebiao(numCourses, vector<int>());//邻接表;二维数组,在图中，比如1和2和+3相连，那么这个数组就是0开头，23在后面.2的邻接表就要另起一行,所以就是二维数组.
			queue<int> q_rudu0;//保存入度为0的节点。
			//构建入度表和邻接表
			for (size_t i = 0; i < prerequisites.size(); i++)//!牢记一个关键：题目给的数组中10，方向是0-》1 
			{
				rudubiao[prerequisites[i][0]]++;//题目给的数组中10，方向是0-》1 所以入度是 prerequisites[1];
				linjiebiao[prerequisites[i][1]].push_back(prerequisites[i][0]);//方向是0-》1.领接表的头就是0 往后接1
			}

			//搞一个队列，把入度为0的点都放进去，用来后面删除这些点
			for (size_t i = 0; i < numCourses; i++)
			{
				if (rudubiao[i] == 0)
					q_rudu0.push(i);
				//!!!这个放的是下标，下面和上面都是放的的科目的名字，
			   //这个有误解，我已经测出来，所有的科目名字都是0，从0-》numCourses都是科目名字
			}

			//开始拓扑排序，也就是删除入度为0的点
			while (!q_rudu0.empty())
			{
				int kechengIndex = q_rudu0.front();//课程号
				q_rudu0.pop();
				numCourses--;//删掉一个点！！别忘了这个
				//既然这个点删掉了，那么与这个点有关的点入度都要改变。0-》1；0-》2；0删除了，1和2的入度都要减少。所以for的范围是0的邻接表.
				for (size_t i = 0; i < linjiebiao[kechengIndex].size(); i++)//！！！范围别弄错，是这个点的所有的邻接的数据 linjiebiao[deleteIndex].size()。
				{
					//用【10】举例子，方向是0-》1，现在删除0；
					//删除对应的点之后，对应入度表要跟着边；注意的是邻接表这个不用变化。比如0接了1、2。0被删除了，那么在本次while之后，0的邻接表不会再用。
					rudubiao[linjiebiao[kechengIndex][i]]--;//删除一个点后,对应的入读表也是要变化,首先rudubiao[x]--.那么x肯定是和kechengIndex(被删掉的节点)挨边的元素.
					//那么挨边的元素是多少呢?就要靠邻接表了.linjiebiao[kechengIndex][i](kechengIndex是被删的元素,i是与他挨边的元素的序号).
					if (rudubiao[linjiebiao[kechengIndex][i]] == 0)//入度改变了就有可能出现新的入度为0的点，那么就放到队列中。准备删掉他
						q_rudu0.push(linjiebiao[kechengIndex][i]);//是0的话，就把它的坐标也就是linjiebiao[deleteIndex][i]放到队列中。
				}
			}
			return numCourses == 0;//如果全删了，那么符合要求
		}

		//207. 课程表-二刷
		bool canFinish2(int numCourses, vector<vector<int>>& prerequisites) {
			vector<int>rudubiao(numCourses, 0);
			vector<vector<int>>linjiebiao(numCourses, vector<int>());//!!别忘了初始化
			for (size_t i = 0; i < prerequisites.size(); i++)//题目给的数组中10，方向是0-》1 
			{
				//用【10】举例子，方向是0-》1
				rudubiao[prerequisites[i][0]]++;//1在后面，所以是1的入度
				linjiebiao[prerequisites[i][1]].push_back(prerequisites[i][0]);//0在前面，所以是0的邻接
			}
			//邻接表和入度表弄完之后，就开始找入度为0的点，放到queue中
			queue<int> que0;//入度为0的点都放到这里
			for (size_t i = 0; i < rudubiao.size(); i++)
			{
				if (rudubiao[i] == 0)
					que0.push(i);
			}

			while (!que0.empty())//只要入度不为0的点还存在，那么就一直删下去。
			{
				int deleteIndex = que0.front();//被删除的这个点的的坐标
				que0.pop();
				numCourses--;//删掉一个点
				for (size_t i = 0; i < linjiebiao[deleteIndex].size(); i++)//!!for的目的就是找这个点的连接的那些点，他们的入度都要调节。！！！范围别弄错，是这个点的所有的邻接的数据 linjiebiao[deleteIndex].size()。
				{
					//用【10】举例子，方向是0-》1，现在删除0；
					//删除对应的点之后，对应入度表要跟着边；注意的是邻接表这个不用变化。比如0接了1、2。0被删除了，那么在本次while之后，0的邻接表不会再用。
					rudubiao[linjiebiao[deleteIndex][i]]--;
					//接着判断这个新的入度是不是0
					if (rudubiao[linjiebiao[deleteIndex][i]] == 0)
						que0.push(linjiebiao[deleteIndex][i]);//是0的话，就把它的坐标也就是linjiebiao[deleteIndex][i]放到队列中。
				}
			}
			return numCourses == 0;
		}




		/*
		208. 实现 Trie (前缀树)
		题意:
			就是插入数据,查找数据(完全匹配),查找数据(部分匹配)
		参考：
			https://leetcode.cn/problems/implement-trie-prefix-tree/solutions/98390/trie-tree-de-shi-xian-gua-he-chu-xue-zhe-by-huwt/?envType=study-plan-v2&envId=top-100-liked
		思路：
			其实就是构建多叉树，有26个英文字母，26个叉。 然后构建就完了。
			单词是由26个字母组成.除了根节点,这个树每一层有26个.然后每个节点下面都是有26个.
			这样通过从"根节点"开始往下走,如果能走到底,那么就是完全匹配.走不到底就是部分匹配.
		*/
		class Trie {
		private:
			bool isEnd;
			Trie* next[26] = { 0 };
		public:
			Trie() {
				isEnd = false;
			}
			//插入数据
			void insert(string word) {
				Trie* currNode = this;// this可以理解为树的根节点。
				for (char c : word) {
					if (currNode->next[c - 'a'] == nullptr)// node的next数组中，是否有对应的字符
						currNode->next[c - 'a'] = new Trie();// 没有的话，就增加行的节点
					currNode = currNode->next[c - 'a'];// 有的话,当前节点就移动到该节点位置，
				}
				currNode->isEnd = true;// 遍历到当前节点，也就是字符串尾巴，这个节点的isEnd = true。来标志到了尾巴
			}

			//查找数据-完全匹配
			bool search(string word) {
				Trie* currNode = this;
				for (char c : word) {
					if (currNode->next[c - 'a'] == nullptr)
						return false;
					currNode = currNode->next[c - 'a'];
				}
				return currNode->isEnd;//走到了尾巴,要找到的这个字符是完全匹配的.
			}

			//字符的部分匹配
			bool startsWith(string prefix) {
				Trie* currNode = this;
				for (char c : prefix) {
					if (currNode->next[c - 'a'] == nullptr)
						return false;
					currNode = currNode->next[c - 'a'];
				}
				return true;//部分匹配就是这样，只要在遍历完prefix后，中间没有在for中出现return false 就算ok
			}
		};












		//二刷-208. 实现 Trie (前缀树)
		class Trie2 {
		private:
			bool isEnd = false;//curNode走到最后为1,否则就是0
			Trie2 *next[26];
		public:
			//插入数据
			void insert(string word) {
				Trie2 *curNode = this;
				for (auto c : word) {
					if (curNode->next[c - 'a'] == nullptr)//如果当前字符的下个节点不存在,但是for还没走完,自然就要接上新的
						curNode->next[c - 'a'] = new Trie2();
					curNode = curNode->next[c - 'a'];
				}
				curNode->isEnd = true;//!!!别弄错.是最后一个节点的isEnd赋值
			}

			//查找完全匹配
			bool search(string word) {
				Trie2 *curNode = this;
				for (auto c : word) {
					if (curNode->next[c - 'a'] == nullptr)
						return false;
					curNode = curNode->next[c - 'a'];
				}
				return curNode->isEnd;//!!!别弄错.是最后一个节点的isEnd返回.比如123,查找的却是12,因为2不是末尾,isEnd是true.所以返回的是false,
			}


			//查找部分匹配
			bool startsWith(string prefix) {
				Trie2 *curNode = this;
				for (auto c : prefix) {
					if (curNode->next[c - 'a'] == nullptr)
						return false;
					curNode = curNode->next[c - 'a'];
				}
				return true;
			}
		};





		void test()
		{
			//string str = "bbbab";
			//vector<	vector<int> > graph{ {0,0,1,0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},{0,1,1,0,1,0,0,0,0,0,0,0,0},{0,1,0,0,1,1,0,0,1,0,1,0,0} };
			//vector<	vector<char> > graphc{ {'X','X','X','X'},{'X','O','O','X'},{'X','X','O','X'},{'X','O','X','X'} };
			vector<	vector<int> > graph1{ {2,1,1},{1,1,0},{0,1,1} };
			//vector<	vector<int> > graph2{ {1,0} };
			//vector<	vector<int> > graph3{ {4,3},{1,4},{4,8},{1,7},{6,4},{4,2},{7,4},{4,0},{0,9},{5,4} };
			//vector<	vector<int> > graph4{ {0,7},{0,8},{6,1},{2,0},{0,4},{5,8},{4,7},{1,3},{3,5},{6,5} };
			//vector<int> dp1{ 1,3,4,2 };
			//int Start = GetTickCount();
			////cout << largestIsland(graph2) << endl;
			//int Stop = GetTickCount();
			//cout << "消耗时间" << Stop - Start << endl;
			//Solution A;

			//cout << A.canFinish(2, graph2) << endl;

			//Trie trie = Trie();
			//trie.insert("apple");
			//cout << trie.search("apple") << endl;   // 返回 True
			//cout << trie.search("app") << endl;     // 返回 False
			//cout << trie.startsWith("app") << endl; // 返回 True
			//trie.insert("app");
			//cout << trie.search("app") << endl;     // 返回 True
			orangesRotting2(graph1);

			//vector<int> ret = A.findRedundantDirectedConnection(graph4);
			//cout << ret[0] << endl;
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

//二分查找法方法
namespace ERFENCAHZHAO {
	class Solution {
	public:


		/*
		二分法标准写法;
		参考:
			https://www.programmercarl.com/0704.%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE.html#%E6%80%9D%E8%B7%AF
		思路:
			我们定义 target 是在一个在左闭右闭的区间里，也就是[left, right] （这个很重要非常重要）。
			当然也有,左闭右开的区间里，也就是[left, right),这个时候就是另外一种写法,具体参考连接的写法.
		*/
		int searchStandard(vector<int>& nums, int target) {
			int left = 0;
			int right = nums.size() - 1; // 定义target在左闭右闭的区间里，[left, right]
			while (left <= right) { // 当left==right，区间[left, right]依然有效，所以用 <=
				int middle = left + ((right - left) / 2);// 防止溢出 等同于(left + right)/2
				if (nums[middle] > target) {
					right = middle - 1; // target 在左区间，所以[left, middle - 1]
				}
				else if (nums[middle] < target) {
					left = middle + 1; // target 在右区间，所以[middle + 1, right]
				}
				else { // nums[middle] == target
					return middle; // 数组中找到目标值，直接返回下标
				}
			}
			// 未找到目标值
			return -1;
		}


		/*
		35. 搜索插入位置
		题意:
			给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
			请必须使用时间复杂度为 O(log n) 的算法。
		参考：
			无，起始就是简单的二分查找的变种
		思路：
			二分查找只有left 》right才会跳出while；如果能找到，早就找到了。
			left此时已经是更新后的位置了，这个位置如果存在对应的元素，上面肯定早就找到了，找不到就在这个位置插入！！！
		*/
		int searchInsert(vector<int>& nums, int target) {
			int left = 0;
			int right = nums.size() - 1;
			int mid = left + (right - left) / 2;
			while (left <= right)
			{
				mid = left + (right - left) / 2;
				if (nums[mid] > target)
					right = mid - 1;
				else if (nums[mid] < target)
					left = mid + 1;
				else if (nums[mid] == target)
					return mid;
			}
			//二分查找只有left 》right才会跳出while；如果能找到，早就找到了。
			//left此时已经是更新后的位置了，这个位置如果存在对应的元素，上面肯定早就找到了，找不到就在这个位置插入！！！
			return left;//!!这个地方和标准的"二分查找"不一样.
			//return right + 1; 哪个都行
		}

		//35. 搜索插入位置---二刷
		int searchInsert2(vector<int>& nums, int target) {
			int Left = 0, Right = nums.size() - 1;
			int mid = 0;
			while (Left <= Right)
			{
				mid = Left + (Right - Left) / 2;
				if (nums[mid] > target)
					Right = mid - 1;
				else if (nums[mid] < target)
					Left = mid + 1;
				else
					return mid;
			}
			return Left;
		}

		/*
		34. 在排序数组中查找元素的第一个和最后一个位置
		题意:
			给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。
			如果数组中不存在目标值 target，返回 [-1, -1]。
			你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。
		参考：
			https://blog.csdn.net/qq_37500516/article/details/116116926
		思考：
			lower_bound upper_bound，是利用二分法查找，满足题目要求
		*/
		vector<int> searchRange(vector<int>& nums, int target) {
			vector<int> ret{ -1,-1 };
			//返回第一个>=target的元素的迭代器
			vector<int>::iterator it = lower_bound(nums.begin(), nums.end(), target);
			//如果找不到元素，或者找到的元素不是想要的元素，说明找不到，返回-1-1即可
			if (it == nums.end() || *it != target)
				return ret;
			//走到这，说明如果找到了并且还是等于target的元素
			ret[0] = it - nums.begin();
			//找到第一个大于target的位置
			it = upper_bound(nums.begin(), nums.end(), target);
			ret[1] = it - nums.begin() - 1;//-1是因为该位置的上个位置才是==target的位置
			return ret;
		}



		//34. 在排序数组中查找元素的第一个和最后一个位置--二刷
		vector<int> searchRange2(vector<int>& nums, int target) {
			vector<int> ret{ -1,-1 };
			auto it = lower_bound(nums.begin(), nums.end(), target);
			if (it == nums.end() || *it != target)//别忘了有时候,lower_bound找到的元素是>=target,如果>target,说明没有找到,则直接返回
				return ret;
			ret[0] = it - nums.begin();
			auto it1 = upper_bound(nums.begin(), nums.end(), target);
			//通过lower_bound,能走到这,说明数组中肯定有一个元素,upper_bound是找>target的元素,有可能找到,有可能找不到,但是无论能不能找到,都可以用ret[1] = it1 - nums.begin() - 1;
			ret[1] = it1 - nums.begin() - 1;

			return ret;
		}



		/*
		33. 搜索旋转排序数组
		题意:
			整数数组 nums 按升序排列，数组中的值 互不相同
			在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转
			例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。
			给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。
			你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。
		参考：
			没什么能参考的，
		思路：
			（不包括nums[mid]）这个我不好解释，先记住吧！
			一般的二分查找都是nums[mid]和tatget比较.而这里是nums[mid]和nums[l],nums[r]比较,
			目的是知道mid到r或者mid到l之间的元素是单调的,
			只有某一个区间是单调的,才能用二分法,代码中也是在判断出单调之后,才使用二分法.
			观察这题目,和二分查找的区别,就是上面这个区间判断.
			区间,全部都是左闭右闭,[l,mid],[mid,r]这样代码统一,方便记忆.虽然有两个mid,但是nums[mid]进入哪个if都能处理,我已经试了,没问题
			之前的是[l,mid],(mid,r].这样虽然也是全部区间,不好记忆,过段时间再看也会忘.
		*/
		int search(vector<int>& nums, int target) {
			int l = 0, r = nums.size() - 1;

			while (l <= r) {
				// 注意优先级，>>比+的优先级低，他是先算+就错了。等价(r - l)/2 + l;不用除法，为了节省性能。
				int mid = ((r - l) >> 1) + l;
				if (target == nums[mid])
					return mid;
				// 左边界《=中间节点的值时候，另外中间节点一定在左节点的右边,说明从l到mid中间都是升序的，也就是正常情况。转折点不在这。
				// 既然l到mid是确定都是有序的，那么就在l和mid之间处理
				if (nums[l] <= nums[mid]) {//!!!这里是《=
					//target在l和mid中间，那么r就要更新mid-1（不包括nums[mid]）；这个和二分法的处理是一样。
					if (nums[l] <= target && target <= nums[mid])
						r = mid - 1;
					//target不在l和mid中间，那就是在mid和r之间。那么l就要更新mid+1；这个和二分法的处理是一样。
					else
						l = mid + 1;
				}
				// 左边界>中间节点的值的时候,说明mid到r是有序的，是升序。
				else if (nums[l] >= nums[mid]) {//!!!!这里只有》，没有等于
					//target在mid和r之间。l更新成mid+1（不包括nums[mid]）；这个和二分法的处理是一样。
					if (nums[mid] <= target && target <= nums[r])
						l = mid + 1;
					else//target不在mid和r中间，那就是在l和mid之间。那么r就要更新mid-1；这个和二分法的处理是一样。
						r = mid - 1;
				}
			}
			return -1;
		}


		//33. 搜索旋转排序数组,暴力搜索,结果是对的,但是实际复杂度不合适.到时候，如果做不出来，就用这个, 时间复杂度不满足要求.
		int search1(vector<int>& nums, int target) {
			for (int i = 0; i < nums.size(); ++i)
				if (nums[i] == target) return i;
			return -1;
		}
		//33. 搜索旋转排序数组,二刷
		int search2(vector<int>& nums, int target) {
			int l = 0, r = nums.size() - 1;
			while (l <= r)
			{
				int mid = l + ((r - l) >> 2);
				if (nums[mid] == target)
					return mid;
				if (nums[l] <= nums[mid]) {
					if (nums[l] <= target && target <= nums[mid])
						r = mid - 1;
					else
						l = mid + 1;
				}
				else if (nums[mid] <= nums[r]) {

					if (nums[mid] <= target && target <= nums[r])
						l = mid + 1;
					else
						r = mid - 1;
				}
			}
			return -1;
		}




		/*
		153. 寻找旋转排序数组中的最小值
		题意:
			已知一个长度为 n 的数组，预先按照升序排列，经由 1 到 n 次 旋转 后，得到输入数组。例如，原数组 nums = [0,1,2,4,5,6,7] 在变化后可能得到：
			若旋转 4 次，则可以得到 [4,5,6,7,0,1,2]
			若旋转 7 次，则可以得到 [0,1,2,4,5,6,7]
			给你一个元素值 互不相同 的数组 nums ，它原来是一个升序排列的数组，并按上述情形进行了多次旋转。请你找出并返回数组中的 最小元素 。
			你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。

		参考：
			https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/solutions/2680224/er-fen-cha-zhao-yu-feng-zhi-bi-jiao-by-w-kanl/?envType=study-plan-v2&envId=top-100-liked
			https://www.programmercarl.com/0704.%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE.html#%E6%80%9D%E8%B7%AF
			他用的是[)的区间，我给他改成[]区间了，代码能通过。关于区间可以看代码随想的写法
		思路：
			做这个题目,一定要画图.好理解
			题目必要要用时间复杂度为 O(log n) 的算法解决此问题。如果没有这个条件，直接遍历得了，然后返回，只不过时间复杂度是n
			整体上还是二分的思路，但是于nums[mid]比较的对象，换成了固定的nums的最右侧
			不明白了，就看他的图
			数组的单调性分为两个区间,比如[4,5,6,7,0,1,2],分为4567,和012.这两个部分的区间.
			最小的部分,一定在右面区间的左边,这是一定的,要不就是像[1234567],但也是在最左边.
			利用二分查找,比较nums[mid]和nums[right]的值,nums[mid]较大,说明最小值在mid的右面
			nums[right]较大,说明最小值在mid的左侧.
		注意:
			 if (nums[mid] <= numR)这里是小于等于.等于号只能在这,
			 在if (nums[mid] >= numR)是错误的.
		*/
		int findMin(vector<int>& nums) {
			int left = 0, right = nums.size() - 1;
			int p = nums[right];
			while (left <= right)
			{
				int mid = left + ((right - left) >> 1);
				if (nums[mid] > p)
					left = mid + 1;
				else
					right = mid - 1;
			}
			return nums[left];//最后返回nums[left]
		}





		//153. 寻找旋转排序数组中的最小值--二刷
		int findMin2(vector<int>& nums) {
			int l = 0, r = nums.size() - 1;
			int numR = nums[r];
			while (l <= r)
			{
				int mid = l + (r - l) / 2;
				if (nums[mid] > numR)
					l = mid + 1;
				else if (nums[mid] <= numR)//!!等号一定要在这里,因为最低点是有可能是等于numR的
					r = mid - 1;
			}
			return nums[l];
		}




		/*
		4. 寻找两个正序数组的中位数
		参考：

		思考：
			这个题目要求算法的时间复杂度应该为 O(log (m+n))，如果没有这个要求，直接暴力就能解决了。
			两个都是有序数组。
		*/
		double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
			int n = nums1.size();
			int m = nums2.size();

			if (n > m)  //保证数组1一定最短
			{
				return findMedianSortedArrays(nums2, nums1);
			}

			// Ci 为第i个数组的割,比如C1为2时表示第1个数组只有2个元素。LMaxi为第i个数组割后的左元素。RMini为第i个数组割后的右元素。
			int LMax1, LMax2, RMin1, RMin2, c1, c2, lo = 0, hi = 2 * n;  //我们目前是虚拟加了'#'所以数组1是2*n长度

			while (lo <= hi)   //二分
			{
				c1 = (lo + hi) / 2;  //c1是二分的结果
				c2 = m + n - c1;

				LMax1 = (c1 == 0) ? INT_MIN : nums1[(c1 - 1) / 2];
				RMin1 = (c1 == 2 * n) ? INT_MAX : nums1[c1 / 2];
				LMax2 = (c2 == 0) ? INT_MIN : nums2[(c2 - 1) / 2];
				RMin2 = (c2 == 2 * m) ? INT_MAX : nums2[c2 / 2];

				if (LMax1 > RMin2)
					hi = c1 - 1;
				else if (LMax2 > RMin1)
					lo = c1 + 1;
				else
					break;
			}
			return (max(LMax1, LMax2) + min(RMin1, RMin2)) / 2.0;
		}


		void test()
		{
			vector<int> nums = { 5,7,7,8,8,10 };
			searchRange(nums, 8);

		}
	};

}


//快排
namespace KUAIPAI
{
	class Solution {
	public:


		/*
		215. 数组中的第K个最大元素
			题意:
					就是返回第k大的元素,比如12344 第2大的元素是4，不是3。因为4由有两个,所以第二个4就是第2大.题目中有说明
			参考：
				https://leetcode.cn/problems/kth-largest-element-in-an-array/solutions/2361969/215-shu-zu-zhong-de-di-k-ge-zui-da-yuan-d786p/?envType=study-plan-v2&envId=top-100-liked
			思路1：
				时间复杂的 O(n log n)。这个很简单，还能过。耗时和复杂的写法时间差不了多少.
				int findKthLargest(vector<int>& nums, int k) {
					sort(nums.begin(), nums.end());
					return nums[nums.size() - k];
				}
			思路2：
				求第几大，很明显用单调栈的思路合适。
				！！这么说是不对的，单调栈求解的思路是“找寻左边或者右边第一个比自己大或者小的元素的举例”。
			思路3：
				就这个思路时间复杂度是O(N)
			思路4：
				快排：时间复杂度平均是O (nlogn)。我对快排不是很了解，先用这。
				首先，根据我现在的理解，他不是一个单纯的快排，因为最后并不是要排序，但是其中也确实用到了一些快排的思想，比如选基点之类的。
				具体思路：先选择一个基点，为了保证算法的效率，随机选一个，选头部不一定是个好选择。
				然后，遍历数组，根据》基点，==基点，《基点，放到3个数组中，
				然后判断第k大的数据在上面3个数组中的哪个，既然第k大的元素在这，那么就在这个数组中继续寻找，也就是开始递归。
				最后，直到不再递归了，也就是在随机找数的时候，找到了想要的那个数。


			其他思路：
				优先队列：时间复杂度平均是O(Nlog⁡K)O(N \log K)O(NlogK))。
			*/

		int findKthLargest_qucikSelect(vector<int>& nums, int k)
		{
			vector<int>big, sma, equal;//vs中small是个宏
			int base = nums[rand() % nums.size()];//随机选一个元素

			for (int num : nums) {
				if (num > base)
					big.push_back(num);
				else if (num == base)
					equal.push_back(num);
				else
					sma.push_back(num);
			}

			/*
				3,2,1,5,6,"4" 第3大
				《---------------------------K从右往左，K是逐渐的减小
				small	   equal	    big
				123			4			56
				因为题目中要求的是第k大的元素,所以一定要从右往左走,
				如果题目中要求第几小的元素,那就从左往右.
			*/
			if (k <= big.size())//如果k的大小不超big的范围，那么说明第k大的元素在big中
				return	findKthLargest_qucikSelect(big, k);//继续递归，接着切割
			else if (k > big.size() + equal.size())//如果k的大小超过了big+equal的范围，那么说明第k大的元素在small中
				return findKthLargest_qucikSelect(sma, k - (big.size() + equal.size()));//第k大的元素，在small中，是第“k - (big.size() + equal.size())”大
			return base;//如果这次随机选的base.不在big也不再small区间中,而是在equ区间中,则说明是合适的.(我无法用一句干练的话描述出来,你想一想就明白)
		}


		int findKthLargest(vector<int>& nums, int k) {
			return findKthLargest_qucikSelect(nums, k);
		}



		int findKthLargest_kuaipai2(vector<int>& nums, int k) {
			vector<int> equ, big, sma;
			int base = nums[rand() % nums.size()];
			for (size_t i = 0; i < nums.size(); i++)
			{
				if (nums[i] < base)
					sma.push_back(nums[i]);
				else if (nums[i] == base)
					equ.push_back(nums[i]);
				else if (nums[i] > base)
					big.push_back(nums[i]);
			}
			if (k <= big.size())
				return findKthLargest_kuaipai2(big, k);//!!别忘了添加return,比如在第k大的元素在big中,那么就一直在这个区间中找了,找完了之后就返回,你不加return的话,就还会往下走,返回base,这个是不对的
			else if (k > (big.size() + equ.size()))//k在small的区间中,
				return findKthLargest_kuaipai2(sma, k - big.size() - equ.size());//equ的区间中.本开的第k大,在这个区间中就是k - big.size()大
			return base;
		}


		//215. 数组中的第K个最大元素--二刷
		int findKthLargest2(vector<int>& nums, int k) {
			return findKthLargest_kuaipai2(nums, k);
		}



	};
}


//技巧
namespace {

	class Solution {
	public:
		/*
		136. 只出现一次的数字
		题意:
			给你一个 非空 整数数组 nums ，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
		参考:
			https://leetcode.cn/problems/single-number/solutions/2361995/136-zhi-chu-xian-yi-ci-de-shu-zi-wei-yun-iyd0/?envType=study-plan-v2&envId=top-100-liked
		思路：
			异或，相异为1，相同为0.
			最后异或出来的数，就是那个孤独的数.
			具体我还真不好解释,总之这是没错的.
		*/
		int singleNumber(vector<int>& nums) {
			int x = 0;
			for (int num : nums) {
				x = x ^ num;
			}
			return x;
		}

		//136. 只出现一次的数字--二刷
		int singleNumber2(vector<int>& nums) {
			int x = 0;

			for (int num : nums)
				x = num ^ x;
			return x;
		}



		/*
		169. 多数元素
		题意:
			给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于  n/2  的元素。
			你可以假设数组是非空的，并且给定的数组总是存在多数元素。
			输入：nums = [2,2,1,1,1,2,2]
			输出：2
		参考:
			https://leetcode.cn/problems/majority-element/solutions/2362000/169-duo-shu-yuan-su-mo-er-tou-piao-qing-ledrh/?envType=study-plan-v2&envId=top-100-liked
			链接中的"摩尔投票",我没有采用它的方法.
			我不知道从哪找到的新的方法.
		思路:
			元素做key,次数做value.
			保存出现的最大的次数,每次这个次数更新,就要保留这个元素,
			最后返回这个元素即可.
		*/
		int majorityElement(vector<int>& nums) {
			map<int, int> index_num;
			int maxCount = 0;//出现的最大次数
			int maxNum = 0;//出现的最大的值
			for (size_t i = 0; i < nums.size(); i++)
			{
				index_num[nums[i]]++;
				if (index_num[nums[i]] > maxCount) {
					maxCount = index_num[nums[i]];
					maxNum = nums[i];
				}
			}
			return maxNum;
		}


		// 169. 多数元素--二刷
		int majorityElement2(vector<int>& nums) {
			map<int, int>numsMap;
			int maxCount = 0;
			int Ret = 0;
			for (size_t i = 0; i < nums.size(); i++)
			{
				numsMap[nums[i]]++;
				if (numsMap[nums[i]] > maxCount) {
					maxCount = numsMap[nums[i]];
					Ret = nums[i];
				}
			}
			return Ret;
		}


		/*
		75. 颜色分类
		题意:
			给定一个包含红色、白色和蓝色、共 n 个元素的数组 nums ，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
			我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
			必须在不使用库内置的 sort 函数的情况下解决这个问题
		参考:
			https://leetcode.cn/problems/sort-colors/solutions/2651983/yi-kan-jiu-dong-de-dai-ma-by-bo-bo-t1-jlht/?envType=study-plan-v2&envId=top-100-liked
		思路：
			把0放在左边：
				某个数和0交换，0放在左边后，这个0不需要在移动了，所以i和left都要++.
			2放在右边：
				某个数和2交换，2放在右边后，right--，这个换过来的"某个数"有可能还是2,所以要再判断一次来确定位置。
			剩下的1就在中间了：
				1就在中间，哪里都不要放
			为什么0交换后,不需要再判断一次呢?
				因为与0交换的都是比0大的,或者等于0的,不会让比0大的元素放到0的前面,怎么放都是0的后面,这是符合题目的判断的.
				而2,则会出现把2放到它的前面,这种等于情况.而这种是不符合题目的,所以需要再次判断一次.
		*/
		void sortColors(vector<int>& nums) {
			int i = 0, left = 0, right = nums.size() - 1;
			while (i <= right)//!!是小于等于,并且是i<=right;这样才能对整个数组检查一遍.
			{
				if (nums[i] == 0)
					swap(nums[i++], nums[left++]);
				else if (nums[i] == 2)
					swap(nums[i], nums[right--]);
				else
					i++;
			}
		}



		//75. 颜色分类--二刷
		void sortColors2(vector<int>& nums) {
			int i = 0, left = 0, right = nums.size() - 1;
			while (i <= right)
			{
				if (nums[i] == 0)
					swap(nums[i++], nums[left++]);
				else if (nums[i] == 2)
					swap(nums[i], nums[right--]);
				else
					i++;
			}
			return;
		}



		/*
		31. 下一个排列
		题意:
			看下面的思路;
		参考：
			https://leetcode.cn/problems/next-permutation/solutions/2680645/cong-hou-wang-qian-zhao-di-yi-ge-i-1iran-36ux/?envType=study-plan-v2&envId=top-100-liked
		思路：
			题解中的263541，例子不错，我用自己的话复述一遍
			263541有很多的排列方式，对这些排列按照升序排序；要找到这个排列的下一个最更大的排列，如果他就是最大了，就返回排序中最小的。
			263541，从后往前看1,41,541，已经没有办法改变顺序造成一个更大的数，只有3541才有可能，也就是当num[i-1]<num[i]的时候。
			那么3于后后面的那个交换呢？题目要求的是“下一个”，也就是只能组一个提升最小的，
			那么与1交换这个数就变小了，不满足；于4交换，这个满足；与5交换这个数很明显这个数，变得比4大。
			所以，与3交换的是，数组从后往前遍历中第一个遇到大于3的数。
			交换完毕之后，264531.后面的531是“一定”是降序的。如果不是降序的（也就是从后往前是升序的），那么在第一步num[i-1]<num[i]早就实现了。
			531是降序的，把他们变成“最”小的即可。也就是直接倒过来135
			最后的结果就是264135.
		总结:
			从后往前遍历,遇到第一个比后面的数小的数,我称为a.
			然后,再次从后往前遍历,以a为界,找第一个比a大的数,称为b.
			然后,交换a和b,
			然后,反转a位置之后的数.
			最后就得到了我们想要的数.
			如果没有反转,说明题目提供的数就是最大的数,根据题意,我们给他一个反转一下,得到最小的数即可.
		*/
		void nextPermutation(vector<int>& nums) {
			bool IsHasReverse = false; // 是否发生了翻转.!!!这里一定要要设置值false，力扣的编译器默认IsHasReverse =true。导致代码错误
			for (int i = nums.size() - 1; i > 0; i--) {
				if (nums[i - 1] < nums[i]) {//不要用nums[i + 1] ,会出现数组越界
					for (int l = nums.size() - 1; l > i - 1; l--) { // l的范围是3到末尾的位置.  i - 1;是3的位置，也就是与3交换位置的都是他后面的
						if (nums[l] > nums[i - 1]) { // 出现了第一个大于3的数据，
							swap(nums[l], nums[i - 1]);
							reverse(nums.begin() + i, nums.end()); // 3后面的部分，全部翻转
							IsHasReverse = true;
							break;//别忘了break。翻转完了就结束了。
						}
					}
					break;//位置也别错
				}
			}
			if (!IsHasReverse)
				reverse(nums.begin(), nums.end()); // 上面没有出现翻转，说明整个序列就是最大的。则应翻转成最小的。
		}

		//31. 下一个排列---二刷
		void nextPermutation2(vector<int>& nums) {
			bool IsHasReverse = false;

			for (size_t i = nums.size() - 1; i > 0; i--) {
				if (nums[i - 1] < nums[i]) {
					for (size_t l = nums.size() - 1; l > i - 1; l--) {
						if (nums[l] > nums[i - 1]) {
							swap(nums[l], nums[i - 1]);
							reverse(nums.begin() + i, nums.end());
							IsHasReverse = true;
							break;
						}
					}
					break;
				}
			}
			if (!IsHasReverse)
				reverse(nums.begin(), nums.end());
		}




		/*
		287. 寻找重复数
		题意:
			给定一个包含 n + 1 个整数的数组 nums ，其数字都在 [1, n] 范围内（包括 1 和 n），可知至少存在一个重复的整数。
			假设 nums 只有 一个重复的整数 ，返回 这个重复的数 。
			你设计的解决方案必须 不修改 数组 nums 且只用常量级 O(1) 的额外空间。
		参考：
			这个题目和链表中的"142.环形链表II"思路很像.
			https://leetcode.cn/problems/find-the-duplicate-number/solutions/58841/287xun-zhao-zhong-fu-shu-by-kirsche/?envType=study-plan-v2&envId=top-100-liked
			思路上是一样的,代码上有细微差别.
		思路：
			根据题目的条件可知，这个数组的元素一定是连续的。(如果不是连续的,那么就会出现数组越界)并且数组中一定含有重复元素。
			元素[1,2,3]报错'nums' must consist of values from 1 to 2 only.
			1、先有个快慢指针，这里的快慢很有意思  slow = nums[slow]  fast = nums[nums[fast]] 这样相当于fast每次会走两次
			2、直到快慢指针相遇，也就是两者的值相同
			3、这个时候，再定义一个指针pre在数组开头的位置，和slow两者一块走。pre= nums[pre]  slow = nums[slow] 。
			4、直到两者相遇，然后返回pre的值即可
		*/
		int findDuplicate(vector<int>& nums) {
			int slow = 0, fast = 0;
			slow = nums[slow];
			fast = nums[nums[fast]];//这两块别删除,要不然进不去下面的循环
			while (slow != fast)
			{
				slow = nums[slow];
				fast = nums[nums[fast]];
			}

			int pre = 0;
			while (pre != slow)
			{
				pre = nums[pre];
				slow = nums[slow];
			}
			return pre;
		}



		//287. 寻找重复数---二刷
		int findDuplicate2(vector<int>& nums) {
			int slow = 0, fast = 0;
			slow = nums[slow];
			fast = nums[nums[fast]];
			while (slow != fast) {
				slow = nums[slow];
				fast = nums[nums[fast]];
			}
			int pre = 0;
			while (slow != fast) {
				slow = nums[slow];
				pre = nums[pre];
			}
			return pre;
		}


		/*
		69.x的平方根
		参考:
			https://leetcode.cn/problems/sqrtx/solutions/7568/niu-dun-die-dai-fa-by-loafer/
			牛顿迭代法
		思路:
			首先随便猜一个近似值 ret，然后不断令 ret 等于 ret 和 x/ret 的平均数，迭代个六七次后 ret 的值就已经相当精确了。
		*/
		int mySqrt(int x) {
			if (x == 0)
				return 0;
			double last = 0;//last和ret不一样就行
			double ret = 1;//ret随便赋值,我这弄个1
			while (ret != last) {
				last = ret;
				ret = (ret + x / ret) / 2;
			}
			return int(ret);//题目要求的返回整数
		}


	};
}
int main()
{


	//注意“decltype(&cmp)”这里的&字符,以及加上decltype，别忘了加。以及q实例化的时候，加上cmp
	vector<int> nums{ 0,1,2,4,5,7 };
	vector<int> num1{ };
	vector<string> srtVec{ "2","1","+","3","*" };
	string str = "(1+(4+5+2)-3)+(6+8)";
	string t = "anagram";
	string strs{ "Marge, let's \"[went].\" I await {news} telegram." };
	vector<vector<int>> board = { {1,4},{4,5} };
	vector<int> newInterval{ 0,0 };

	//String_Array::Solution tree;
	//TULUN::Solution tree;
	//BackTracking::Solution tree;
	//ERFENCAHZHAO::Solution tree;
	//StackandQueue::Solution tree;
	//DynamicPlanning::Solution tree;
	//DoublePointer::Solution tree;
	//Dandiaozhan::Solution tree;
	//LinkedList::Solution tree;//tree.testLRU();
	Tree::Solution tree;
	//StackandQueue::Solution tree;

	tree.test();




}