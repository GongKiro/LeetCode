#include "stdafx.h"
#include "LeetCode_S.h"
#include <unordered_map>
#include <math.h>
#include <stack>
#include <cstdlib>
using namespace std;

CLeetCode_Solution* CLeetCode_Solution::instance = NULL;
CLeetCode_Solution::CLeetCode_Solution()
{
	printf("Hello LeetCode\n");
}


CLeetCode_Solution::~CLeetCode_Solution()
{
}

/*
 给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。

你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。

示例:

给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1] 
 */
std::vector<int> CLeetCode_Solution::twoSum(vector<int>& nums, int target)
{
	unordered_map<int, int> m;
	for (int i = 0; i < nums.size(); i++)
	{
		/*
		 *for (int j = i + 1; j < nums.size(); j++)
		{
			if (target == (nums[i] + nums[j]))
			{
				ret.push_back(i);
				ret.push_back(j);
			}
		}*/
		if (m.find(target - nums[i]) != m.end())
		{
			return{ m[target - nums[i]], i };
		}
		m[nums[i]] = i;
	}
	return{ 0, 0 };
}

/*
 给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转。

示例 1:

输入: 123
输出: 321
 示例 2:

输入: -123
输出: -321
*/
int CLeetCode_Solution::reverse(int x)
{
	int ret(0);
	while (x != 0)
	{
		int pop = x % 10;
		x /= 10;
		if (ret > INT_MAX / 10 || (ret == INT_MAX / 10 && pop > 7)) return 0;
		if (ret < INT_MIN / 10 || (ret == INT_MIN / 10 && pop - 8)) return 0;
		ret = ret * 10 + pop;
	}
	return ret;
}
/*
 *判断回文数
 **/
bool  CLeetCode_Solution::isPalindrome(int x) {
	if (x < 0)
	{
		return false;
	}
	long long rst(0);
	int x_tmp = x;
	while (x != 0)
	{
		int pop = x % 10;
		rst = rst * 10 + pop;
		x /= 10;
	}
	return (rst == x_tmp);
}

std::string CLeetCode_Solution::addBinary(string a, string b)
{
	int al = a.size();
	int bl = b.size();
	while (al < bl)
	{
		a = '0' + a;
		++al;
	}
	while (bl < al)
	{
		b = '0' + b;
		++bl;
	}
	for (int j = a.size() - 1; j > 0; j--)
	{
		a[j] = a[j] - '0' + b[j];
		if (a[j] >= '2')
		{
			a[j] = (a[j] - '0') % 2 + '0';
			a[j - 1] = a[j - 1] + 1;
		}
	}
	a[0] = a[0] - '0' + b[0]; //将ab的第0位相加
	if (a[0] >= '2') //若大于等于2，需要进一
	{
		a[0] = (a[0] - '0') % 2 + '0';
		a = '1' + a;
	}
	return a;
}

int CLeetCode_Solution::romanToInt(string s)
{
	//顺序计算
	/*
	unordered_map<string, int> m;
	m = { { "I", 1 },{ "IV", 3 },{ "IX", 8 },{ "V", 5 },{ "X", 10 },{ "XL", 30 },{ "XC", 80 },{ "L", 50 },{ "C", 100 },{ "CD", 300 },{ "CM", 800 },{ "D", 500 },{ "M", 1000 } };
	int ret = m[s.substr(0, 1)];
	for (int i = 1; i < s.size(); i++)
	{
		string two = s.substr(i - 1, 2);
		string one = s.substr(i, 1);
		ret += m[two] ? m[two] : m[one];
	}
	return ret;
	*/
	//倒序计算（速度和内存更佳），从后面往前面取值，每次取一个符号，如果j的值比j+1大时，则ret减去j的值(罗马计算的规则)
	/*
	 *输入: "LVIII"
	输出: 58
	解释: L = 50, V= 5, III = 3.*/
	unordered_map<char, int> m;
	m = { { 'I', 1 },{ 'V', 5 },{ 'X', 10 },{ 'L', 50 },{ 'C', 100 },{ 'D', 500 },{ 'M', 1000 } };
	int ret = m[s[s.size() - 1]];
	for (int j = s.size() - 2; j >= 0; j--)
	{
		int numL = m[s[j]];
		int numR = m[s[j + 1]];
		if (numL >= numR) ret += numL;
		else ret -= numL;
	}
	return ret;
}

std::string CLeetCode_Solution::longestCommonPrefix(vector<string>& strs)
{
	if (0 == strs.size()) return "";
	string strfirst = strs[0];
	for (int i = 1; i < strs.size(); i++)
	{
		int j = 0;
		for (; j < strfirst.size() && j < strs[i].size(); j++)
		{
			if (strfirst[j] != strs[i][j]) break;
		}
		strfirst = strfirst.substr(0, j);
		if (strfirst.empty()) return "";
	}
	return strfirst;
}

bool CLeetCode_Solution::isValid(string s)
{
	//()[]{}
	if (s.empty()) return true;
	if (0 != s.size() % 2) return false;
	unordered_map<char, char> m = { {'(',')'},{ '[',']' },{ '{','}' } };
	stack<char> ret;
	for (int i = 0; i < s.size(); i++)
	{
		if (m.find(s[i])!=m.end()) ret.push(m[s[i]]);
		else if (ret.empty() || ret.top() != s[i]) return false;
		else ret.pop();
	}
	if (ret.empty()) return true;
	else return false;

}

ListNode* CLeetCode_Solution::mergeTwoLists(ListNode* l1, ListNode* l2)
{
	if (l1 == NULL) return l2;
	if (l2 == NULL) return l1;
	 
	if (l1->val <= l2->val) 
	{
		l1->next = mergeTwoLists(l1->next, l2);
		return l1;
	}

	l2->next = mergeTwoLists(l1, l2->next);
	return l2;
}

int CLeetCode_Solution::removeDuplicates(vector<int>& nums)
{
	/*
	if (nums.empty()) return 0;
	int i = 0;
	for (int j = 1; j < nums.size();++j)
	{
		if (nums[j] != nums[i])
		{
			++i;
			nums[i] = nums[j];
		}
	}
	return i + 1;*/
	if (nums.empty()) return 0;
	int val0 = nums[0];
	for (vector<int>::iterator iter = nums.begin()+1; iter != nums.end();)
	{
		if (val0 == *iter)
		{
			iter = nums.erase(iter);
		}
		else
		{
			val0 = *iter;
			iter++;
		}
	}
	return nums.size();
}

int CLeetCode_Solution::removeElement(vector<int>& nums, int val)
{
	int len = nums.size();
	int pos = 0;
	while (pos < len) {
		if (nums[pos] == val)
			nums[pos] = nums[--len];
		else
			++pos;
	}
	nums.resize(len);
	return len;

}

int CLeetCode_Solution::strStr(string haystack, string needle)
{
	int n = haystack.size(), m = needle.size();

	for (int i = 0; i < n-m+1; ++i)
	{
		int j = 0;
		for (;j < m; ++j)
		{
			if (haystack[i + j] != needle[j]) break;
		}
		if (j == m) return i;
	}
	return -1;
}

//有序vector中插入值
int CLeetCode_Solution::searchInsert(vector<int> &nums, int target)
{
	if (nums.size() == 0) return 0;
	if (target >= nums[nums.size() - 1]) return nums.size();
	int left(0), right(nums.size() - 1);

	while (left < right)
	{
		int mid = left + (right - left) / 2;
		if (nums[mid] < target)  left = mid + 1;
		else right = mid;
	}
	return left;
}

/*
 *「外观数列」是一个整数序列，从数字 1 开始，序列中的每一项都是对前一项的描述。前五项如下：

1.     1
2.     11
3.     21
4.     1211
5.     111221
1 被读作  "one 1"  ("一个一") , 即 11。
11 被读作 "two 1s" ("两个一"）, 即 21。
21 被读作 "one 2",  "one 1" （"一个二" ,  "一个一") , 即 1211。

给定一个正整数 n（1 ≤ n ≤ 30），输出外观数列的第 n 项。

注意：整数序列中的每一项将表示为一个字符串。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/count-and-say
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/


std::string CLeetCode_Solution::countAndSay(int n)
{
	int i = 1;
	string ret = "1";

	while (i < n)
	{
		string tmp = "";
		int sum = 1;
		for (int j = 1; j < ret.size(); ++j)
		{
			if (ret[j] == ret[j - 1])
			{
				sum++;
			}
			else
			{
				tmp += to_string(sum);
				tmp += ret[j - 1];
				sum = 1;
				
			}
		}
		tmp += to_string(sum);
		tmp += ret[ret.length() - 1];
		ret = tmp;
		i++;
	}
	return ret;
}

//vector<int> v = { -2,1,-3,4,-1,2,1,-5,4 };
int CLeetCode_Solution::maxSubArray(vector<int>& nums)
{
	/*
	int ret = INT_MIN;

	for (int i = 0; i < nums.size(); ++i)
	{
		int sum_tmp = 0;
		for (int j = i; j < nums.size(); ++j)
		{
			sum_tmp += nums[j];
			if (ret < sum_tmp)
			{
				ret = sum_tmp;
			}
		}
	}
	return ret;*/
	/*
	int ret = INT_MIN;
	int sum = 0;

	for (int i = 0; i < nums.size(); ++i)
	{
		sum += nums[i];
		ret = max(ret, sum);
		if (sum < 0)
		{
			sum = 0;
		}
	}
	return ret;*/
		
	int sum = 0;
	int dp(nums[0]);// 以第i个元素为结尾的一段最大子序和 ，第1个就是第1个前的连续子数组最大值
	int ret = dp;

	for (int i = 1; i < nums.size(); ++i)
	{
		dp = max(dp + nums[i], nums[i]);//取dp和 dp+第i个的大值
		ret = max(dp, ret);//保持ret是个dp的大值
	}
	return ret;
}

int CLeetCode_Solution::climbStairs(int n)
{
	//上第i个台阶总方法是上第i-1和i-2台阶的和
	//比如有3台阶，上第3台阶，可以从第1台阶上或者第二台阶上，上第2台阶
	// 可以从第0台阶上，或者第1台阶上，上第一台阶只能从第0台阶上
	if (n < 3) return n;
	
	int L1(1), L2(2);//前两个台阶可知数量
	int tmp(0);
	for (int i = 3; i <= n; ++n)
	{
		tmp = L1 + L2;
		L1 = L2;
		L2 = tmp;
	}
	return tmp;
}

int CLeetCode_Solution::maxProfit(vector<int>& prices)
{
	/*
	int ret(0);

	for (int i = 0; i < prices.size(); ++i)
	{
		int in_p = prices[i];
		for (int j = i+1; j < prices.size();++j)
		{
			int tmp = prices[j] - in_p;
			ret = max(ret, tmp);
		}
	}
	return ret;*/
	/*
	 *
	 */
	int l_min(prices[0]);//第i天前的买入最小值
	int l_max(0);//利润最大值

	for (int i = 1; i < prices.size(); ++i)
	{
		l_max = max(l_max, prices[i] - l_min);
		l_min = min(l_min, prices[i]);
	}
	return l_max;
}

//小偷偷钱，不能偷相邻的两个房子
int CLeetCode_Solution::rob(vector<int>& nums)
{
	/*
	if (nums.size() == 0) return 0;
	vector<int> dp(nums.size()+1);
	dp[0] = 0;
	dp[1] = nums[0];
	for (int i = 2; i <= nums.size(); i++) {
		dp[i] = max(dp[i - 1], dp[i - 2] + nums[i - 1]);
	}
	return dp[nums.size()];
	*/
	if (nums.size() == 0) return 0;
	if (nums.size() == 1) return nums[0];
	if (nums.size() == 2) return max(nums[1], nums[0]);
	
	int dp[3] = { 0 };
	dp[0] = 0;
	dp[1] = nums[0];

	for (int i = 2; i < nums.size(); ++i)
	{
		dp[2] = max(dp[0] + nums[i], dp[1]);
		dp[0] = dp[1];
		dp[1] = dp[2];
	}
	return dp[2];
}

//给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次
ListNode* CLeetCode_Solution::deleteDuplicates(ListNode* head)
{
	if (head == NULL) return head;
	
	ListNode* tmp = head;
	
	while (tmp->next != NULL)
	{
		if (tmp->val != tmp->next->val)
		{
			//往后面走一步
			tmp = tmp->next;
		}
		else
		{
			//删除掉一个点,保留一个数据
			ListNode* tmp1 = tmp->next;
			tmp->next = tmp1->next;
			delete tmp1;
		}
	}
	return head;
}

void CLeetCode_Solution::merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
{
	int m_ = m - 1;
	int n_ = n - 1;
	int len = m + n - 1;
	while (m_ >= 0 && n_ >= 0) 
	{
		nums1[len--] = nums1[m_] > nums2[n_] ? nums1[m_--] : nums2[n_--];
	}
		
	while (n_ >= 0) nums1[len--] = nums2[n_--]; //最后 nums2有残留就一定是在最前面的 nums1无所谓，因为已经排好序
}
/*
 *输入:       1         1
		  / \       / \
		 2   3     2   3

		[1,2,3],   [1,2,3]

输出: true
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 **/
bool CLeetCode_Solution::isSameTree(TreeNode* p, TreeNode* q)
{
	if (p == NULL && q == NULL) return true;
	if (p == NULL || q == NULL) return false;
	if (p->val != q->val) return false;
	return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}
/*
给定一个二叉树，检查它是否是镜像对称的。

例如，二叉树 [1,2,2,3,4,4,3] 是对称的。

	1
   / \
  2   2
 / \ / \
3  4 4  3
 **/
bool isSymmetrictmp(TreeNode* q, TreeNode* p)
{
	if (p == NULL && q == NULL) return true;
	if (p == NULL || q == NULL) return false;
	
	return (q->val == p->val) && isSymmetrictmp(q->left, p->right) && isSymmetrictmp(q->right, p->left);
}

bool CLeetCode_Solution::isSymmetric(TreeNode* root)
{
	if (root == NULL) return true;
	//不停的left和right对比就行
	return isSymmetrictmp(root->left, root->right);

}
/*
*二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

说明: 叶子节点是指没有子节点的节点。

示例：
给定二叉树 [3,9,20,null,null,15,7]，

  3
 / \
9   20
   /  \
  15   7
*/
int CLeetCode_Solution::maxDepth(TreeNode* root)
{
	if (root == NULL) return 0;
	int ret_L = 1, ret_R = 1;
	//取所有left和和right的深度
	if (root->left) ret_L += maxDepth(root->left);
	if (root->right) ret_R += maxDepth(root->right);

	return max(ret_L, ret_R);
}
/*
 *给定一个二叉树，返回其节点值自底向上的层次遍历。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）

例如：
给定二叉树 [3,9,20,null,null,15,7],

	3
   / \
  9  20
	/  \
   15   7
返回其自底向上的层次遍历为：

[
  [15,7],
  [9,20],
  [3]
]
*/

vector<vector<int>> ret;
void  levelOrderBottomTmp(queue<TreeNode*>current)
{
	queue<TreeNode*>next;
	vector<int> curVal;

	while (!current.empty())
	{
		TreeNode* top = current.front();
		current.pop();
		curVal.push_back(top->val);

		if (top->left != NULL) next.push(top->left);
		if (top->right != NULL) next.push(top->right);
	}
	if (!next.empty()) (levelOrderBottomTmp(next));

	ret.push_back(curVal);
}

vector<vector<int>> CLeetCode_Solution::levelOrderBottom(TreeNode* root) {

	if (root == NULL) return ret;

	queue<TreeNode*> next;
	next.push(root);
	levelOrderBottomTmp(next);
	return ret;
}

/*
 *给定一个二叉树，判断它是否是高度平衡的二叉树。

本题中，一棵高度平衡二叉树定义为：

一个二叉树每个节点 的   左右两个子树  的高度差的绝对值不超过1。

示例 1:

给定二叉树 [3,9,20,null,null,15,7]

	3
   / \
  9  20
	/  \
   15   7
返回 true 。

示例 2:

给定二叉树 [1,2,2,3,3,null,null,4,4]

	   1
	  / \
	 2   2
	/ \
   3   3
  / \
 4   4
返回 false 。*/
/*
	def isBalanced(self, root: TreeNode) -> bool:
		return self.depth(root) != -1

	def depth(self, root):
		if not root: return 0
		left = self.depth(root.left)
		if left == -1: return -1
		right = self.depth(root.right)
		if right == -1: return -1
		return max(left, right) + 1 if abs(left - right) < 2 else -1*/
int depth(TreeNode* cur)
{
	if (cur == NULL) return 0;
	printf("cur value = %d\n", cur->val);

	int left = depth(cur->left);
	if (-1 == left) return -1;
	
	int right = depth(cur->right);
	if (-1 == right) return -1;
	
	printf("left value = %d\n", left);
	printf("right value = %d\n", right);
	return (abs(left - right)) < 2 ? max(left, right)+1 : -1;

}
bool CLeetCode_Solution::isBalanced(TreeNode* root)
{
	return depth(root) != -1;
}

/*
 *给定两个数组，编写一个函数来计算它们的交集。

示例 1:

输入: nums1 = [1,2,2,1], nums2 = [2,2]
输出: [2,2]
示例 2:

输入: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出: [4,9]
说明：

输出结果中每个元素出现的次数，应与元素在两个数组中出现的次数一致。
我们可以不考虑输出结果的顺序。
进阶:

如果给定的数组已经排好序呢？你将如何优化你的算法？
如果 nums1 的大小比 nums2 小很多，哪种方法更优？
如果 nums2 的元素存储在磁盘上，磁盘内存是有限的，并且你不能一次加载所有的元素到内存中，你该怎么办？*/
std::vector<int> CLeetCode_Solution::intersect(vector<int>& nums1, vector<int>& nums2)
{
	//先来个sort
	sort(nums1.begin(), nums1.end());
	sort(nums2.begin(), nums2.end());

	vector<int> ret;
	for (int i(0),j(0); i < nums1.size()&&j<nums2.size();)
	{
		//nums2滞后了，往前推一步
		if (nums1[i] > nums2[j]) ++j;
		else if (nums1[i] < nums2[j]) ++i;
		else
		{
			//这时 nums1[i] == nums2[j]
			ret.push_back(nums1[i]);
			++i;
			++j;
		}
	}
	return ret;
}
/*
 *给定一个由整数组成的非空数组所表示的非负整数，在该数的基础上加一。

最高位数字存放在数组的首位， 数组中每个元素只存储单个数字。

你可以假设除了整数 0 之外，这个整数不会以零开头。

示例 1:

输入: [1,2,3]
输出: [1,2,4]
解释: 输入数组表示数字 123。*/
std::vector<int> CLeetCode_Solution::plusOne(vector<int>& digits)
{
	digits[digits.size() - 1]++;

	for (int i = digits.size() - 1; i > 0; --i)
	{
		if (digits[i] >= 10)
		{
			digits[i] = 0;
			digits[i - 1] += 1;
		}
	}
	if (digits[0] >= 10)
	{
		digits[0] = 0;
		digits.insert(digits.begin(), 1);
	}
	return digits;

}
/*
 *给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

示例:

输入: [0,1,0,3,12]
输出: [1,3,12,0,0]
说明:

必须在原数组上操作，不能拷贝额外的数组。
尽量减少操作次数。*/
void CLeetCode_Solution::moveZeroes(vector<int>& nums)
{
	int tmp = 0;
	int i = 0;
	int j = -1;
	for ( ;i < nums.size();++i)
	{
		if (nums[i] != 0)
		{
			j++;
			nums[j] = nums[i];
			if (i != j)
			{
				nums[i] = 0;
			}
		}
	}
}
//数组排序
/*
1 <= nums.length <= 50000
-50000 <= nums[i] <= 50000
*/
std::vector<int> CLeetCode_Solution::sortArray(vector<int>& nums)
{
	int len = nums.size();
	int minVal = INT_MAX;
	int maxVal = INT_MIN;
	for (int i = 0; i < len; i++) {
		minVal = min(nums[i], minVal);
		maxVal = max(nums[i], maxVal);
	}
	int mapsum = maxVal - minVal + 1;
	vector<int> hmap(mapsum);
	for (int i = 0; i < len;++i)
	{
		//下标为实际值-minval, hmap[0]为最小值; 值为数量，hmap的值为0时，表示该值没有出现过，在给ret赋值时，将跳过
		hmap[nums[i] - minVal]++;
	}
	int inx = 0;
	for (int i = 0; i < mapsum;++i)
	{
		for (int j = 0;j < hmap[i];++j)
		{
			//hmap的下标+minval就是原始的值，
			nums[inx++] = i + minVal;
		}
	}
	return nums;
}
//1111. 有效括号的嵌套深度
//url https://leetcode-cn.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/
std::vector<int> CLeetCode_Solution::maxDepthAfterSplit(string seq)
{
	int d = -1;
	vector<int> ans;
	for (char& c : seq)
		if (c == '(') {
			++d;
			ans.push_back(d % 2);
		}
		else {
			ans.push_back(d % 2);
			--d;
		}
		return ans;
}

/*
918. 环形子数组的最大和
给定一个由整数数组 A 表示的环形数组 C，求 C 的非空子数组的最大可能和。

在此处，环形数组意味着数组的末端将会与开头相连呈环状。（形式上，当0 <= i < A.length 时 C[i] = A[i]，而当 i >= 0 时 C[i+A.length] = C[i]）

此外，子数组最多只能包含固定缓冲区 A 中的每个元素一次。（形式上，对于子数组 C[i], C[i+1], ..., C[j]，不存在 i <= k1, k2 <= j 其中 k1 % A.length = k2 % A.length）

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-sum-circular-subarray
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/
int CLeetCode_Solution::maxSubarraySumCircular(vector<int>& A)
{
// 	bool a = true;
// 	int len = A.size();
// 	int ret1(INT_MIN), sum(0);
// /*	A.push_back(A[0]);*/
// 	for (int i = 0; i < len; ++i)
// 	{
// 		sum += A[i];
// 		ret1 = max(sum, ret1);
// /*		sum = sum < 0 ? 0 : sum;*/
// 		if (sum < 0)
// 		{
// 			a = false;
// 			sum = 0;
// 		}
// 	}
// 	ret1;
// 
// 	a = true;
// 	A.push_back(A[0]);
// 	A.erase(A.begin());
// 	int ret2(INT_MIN);
// 	sum = 0;
// 	for (int i = 0; i < len; ++i)
// 	{
// 		sum += A[i];
// 		ret2 = max(sum, ret2);
// 		/*		sum = sum < 0 ? 0 : sum;*/
// 		if (sum < 0)
// 		{
// 			a = false;
// 			sum = 0;
// 		}
// 	}
// 	
// 	return max(ret1, ret2);
	int minimum = INT_MAX, minSum = 0;
	int maximum = INT_MIN, maxSum = 0;
	int sum = 0;
	for (int i = 0; i < A.size();++i) {
		minSum = min(minSum + A[i], A[i]);
		minimum = min(minimum, minSum);
		maxSum = max(maxSum + A[i], A[i]);
		maximum = max(maximum, maxSum);
		sum += A[i];
	}
	if (sum - minimum == 0) {
		return maximum;
	}
	return max(maximum, sum - minimum);
}
/*
输入: 5
输出:
[
[1],
[1,1],
[1,2,1],
[1,3,3,1],
[1,4,6,4,1]
]*/
std::vector<std::vector<int>> CLeetCode_Solution::generate(int numRows)
{
	vector<std::vector<int>> ret;
	if (numRows == 0) return ret;

	for (int i = 0; i < numRows; i++)
	{
		//将第二层vec全部初始化为1，避开处理边界的1
		vector<int> ret_sec(i + 1, 1);
		//从1开始处理，并且不处理最后一个
		for (int j=1; j < i;++j)
			ret_sec[j] = ret[ret.size() - 1][j - 1] + ret[ret.size() - 1][j];
		ret.push_back(ret_sec);
	}
	return ret;
}

int CLeetCode_Solution::lastRemaining(int n)
{
	if (n == 1) 
		return 1;
	return 2 * (n / 2 - lastRemaining(n / 2) + 1);
}

//42. 接雨水
int CLeetCode_Solution::trap(vector<int>& height)
{
// 	int last_top(0);
// 	int ret(0);
// 	int top_index(0);//
// 
// 	for (int i=0;i < height.size(); i++)
// 	{
// 		if (height[i] > height[top_index]) {
// 			top_index = i;
// 		}
// 	}
// 	//1
// 	for (int i = 1; i <= top_index;)
// 	{
// 		if (height[i] >= height[last_top])
// 		{
// 			for (int j = last_top+1; j < i;++j)
// 			{
// 				ret += height[last_top] - height[j];
// 			}
// 			last_top = i;
// 			i++;
// 		}
// 		else{
// 			i++;
// 		}
// 	}
// 	last_top = height.size() -1;
// 	for (int i = last_top - 1; i >= top_index;)
// 	{
// 		if (height[i] >= height[last_top])
// 		{
// 			for (int j = last_top - 1; j > i; --j)
// 			{
// 				ret += height[last_top] - height[j];
// 			}
// 			last_top = i;
// 			i--;
// 		}
// 		else		{
// 			i--;
// 		}
// 	}
// 	return ret;
	int ans = 0, current = 0;
	stack<int> st;
	while (current < height.size()) {
		while (!st.empty() && height[current] > height[st.top()]) {
			int top = st.top();
			st.pop();
			if (st.empty())
				break;
			int distance = current - st.top() - 1;
			int bounded_height = min(height[current], height[st.top()]) - height[top];
			ans += distance * bounded_height;
		}
		st.push(current++);
	}
	return ans;
}
//反转矩阵90°
void CLeetCode_Solution::rotate(vector<vector<int>>& matrix)
{
	int len = matrix.size();

	for (int ver = 0; ver < len; ++ver)
	{
		for (int hor = 0; hor < len - ver; ++hor)
		{
			int tmp = matrix[ver][hor];
			matrix[ver][hor] = matrix[len - 1 - hor][len - 1 - ver];
			matrix[len - 1 - hor][len - 1 - ver] = tmp;
		}
	}
	for (int hor = 0; hor < len; ++hor)
	{
		for (int ver = 0; ver < len; ++ver)
		{
			int tmp = matrix[ver][hor];
			matrix[ver][hor] = matrix[len - 1 - ver][len - 1 - hor];
			matrix[len - 1 - ver][len - 1 - hor] = tmp;
		}
	}
}

//反转链表
ListNode* CLeetCode_Solution::reverseList(ListNode* head)
{
	ListNode* ret = NULL;

	while (head)	{
		ListNode* tmp = head->next;
		head->next = ret;
		ret = head;
		head = tmp;
	}
	return ret;
}

void CLeetCode_Solution::setZeroes(vector<vector<int>>& matrix)
{
	bool bIshor = false;
	bool bIsVer = false;
	uint32_t ver = matrix.size();
	uint32_t hor = matrix[0].size();

	for (uint32_t i = 0; i < hor; ++i) {
		if (matrix[0][i] == 0)
			bIshor = true;
	}
	for (uint32_t j = 0; j < ver; ++j) {
		if (matrix[j][0] == 0)
			bIsVer = true;
	}

	for (uint32_t i = 1; i < ver; ++i) {
		for (uint32_t j = 1; j < hor; ++j) {
			if (matrix[i][j] == 0){
				matrix[i][0] = 0;
				matrix[0][j] = 0;
			}
		}
	}
	for (uint32_t i = 1; i < hor; ++i) {
		if (matrix[0][i] == 0) {
			for (uint32_t j = 1; j < ver; ++j) {
				matrix[j][i] = 0;
			}
		}
	}
	for (uint32_t i = 1; i < ver; ++i) {
		if (matrix[i][0] == 0){
			for (uint32_t j = 1; j < hor; ++j) {
				matrix[i][j] = 0;
			}
		}
	}
	if (bIshor){
		for (uint32_t i = 0; i < hor; ++i) {
			matrix[0][i] = 0;
		}
	}
	if (bIsVer){
		for (uint32_t i = 0; i < ver; ++i) {
			matrix[i][0] = 0;
		}
	}
}

std::vector<int> CLeetCode_Solution::findDiagonalOrder(vector<vector<int>>& matrix)
{
	uint32_t sum = matrix.size() * matrix[0].size();
	vector<int> ret;
	
	for (uint32_t i = 0; i < sum; ++i) {
		
	}

	return ret;
}

std::string CLeetCode_Solution::longestPalindrome(string s)
{
	return "";
}

std::string CLeetCode_Solution::reverseWords(string s)
{
	string ret;
	uint32_t l = s.length();

	for (int i = l - 1; i >= 0; ++i) {

	}
	return ret;  
}

int CLeetCode_Solution::strStr1(string haystack, string needle)
{
	if (needle.empty()) return 0;
	if (haystack.empty()) return -1;

	vector<int> next = commputeNext(needle);
	int j = 0;

	for (int i = 0; i < haystack.size();) {
		if (j == -1 || haystack[i] == needle[j]){
			i++;
			j++;
		}
		else{	
			j = next[j];
		}
		if (j == needle.size())
			return i - j;
	}
	return -1;
}

std::string CLeetCode_Solution::shortestPalindrome(string s)
{
	if (s == "") {
		return "";
	}
	string reverse = "";
	for (int i = s.size() - 1; i >= 0; --i) {
		reverse += s[i];
	}

	string pattern = s + '#' + reverse;

	vector<int>next(pattern.size() + 1, 0);
	next[0] = -1;
	next[1] = 0; // A没有前后缀
	int i = 2; // i表示next数组的索引
	int k = 0;
	while (i < next.size()) {
		if (pattern[i - 1] == pattern[k]) { // pattern索引比next索引小1
			next[i] = k + 1;
			k = next[i];
			++i;
		}
		else if (k == 0) {
			next[i] = 0;
			++i;
		}
		else {
			k = next[k];
		}
	}
	int max_len = next[next.size() - 1];

	string ret = reverse.substr(0, reverse.size() - max_len) + s;
	return ret;
}

std::vector<int> CLeetCode_Solution::commputeNext(string pattern)
{

	vector<int> next(pattern.size() + 1, 0);
	next[0] = -1;
	next[1] = 0;
	int indexNext = 2;
	int j = 0; //j表示pattern[index]位置  pattern[0，index]前缀和后缀相同的位置
	while (indexNext < next.size ()){
		if (pattern[indexNext - 1] == pattern[j]){
			next[indexNext] = j + 1;
			j++;
			indexNext++;
		}
		else if (j == 0){
			//next[indexNext] = 0;
			indexNext++;
		}
		else{	
			j = next[j];
		}
	}
	return next;
	/*	int j = -1, i = 0;//j在后面，i在前面
	vector<int> b(pattern.size() + 1);
	b[i] = j;
	while (i < pattern.size())
	{
		while (j >= 0 && pattern[i] != pattern[j]) 
			j = b[j];
		i++, j++;
		b[i] = j;
	}
	return b;
	
	*/

}

ListNode* CLeetCode_Solution::reverseBetween(ListNode* head, int m, int n)
{
	//假定head为 1 2 3 4 5, m为2,n为4
   	if (m == n || head == NULL || head->next == NULL)
		return head;

	//为了适配M为1的情况，设定定个-1节点，-1节点的next为原链表的head
	ListNode* first = new ListNode(-1);
	first->next = head;
	ListNode* preH = first;//preH作为锚(返回值),指向原链表的head,

	int index = 1;
	while (index++ < m)	{
		first = first->next;
	}
	ListNode* preM = first;

	ListNode* pre = NULL;//相对准备反转的一部分链表,pre为-1节点,循环结束后,为反转后的小段链表的head
	ListNode* cur = first->next;//cur为第一个要反转的节点,循环结束后,为原链表的后部分的head
	//依然使用PreS作为第一个反转的锚,当下面的循环结束后,preS也是要反转部分链表的的最后一个节点
	ListNode* preS = cur;
	
	while (index++ <= n + 1)
	{
		ListNode* tmp = cur->next;
		cur->next = pre;
		pre = cur;
		cur = tmp;
	}
	first->next = pre;
	preS->next = cur;

	return preH->next;   
}

bool isPalindrome(ListNode* head) {
	if (head == NULL || head->next == NULL)
		return true;

	stack<int> first_half;
	ListNode* one = head;
	ListNode* two = head;
	first_half.push(one->val);
	while (one->next != NULL && two->next != NULL && two->next->next != NULL) {
		one = one->next;
		two = two->next->next;
		first_half.push(one->val);
	}
	if (two->next != NULL) {
		one = one->next;
	}

	while (one != NULL) {
		if (one->val != first_half.top()) {
			return false;
		}
		first_half.pop();
		one = one->next;
	}
	return true;
}