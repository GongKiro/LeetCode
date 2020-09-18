#pragma once
#include "stdafx.h"

class CLeetCode_Solution
{
public:
	~CLeetCode_Solution();
	static CLeetCode_Solution* getInstance()
	{
		instance = new CLeetCode_Solution();
		return instance;
	}

private:
	CLeetCode_Solution();
	static CLeetCode_Solution* instance;

public:
	void Hello() { printf("Hello LeetCode"); };
	vector<int> twoSum(vector<int>& nums, int target);// 两数相加等于目标数
	int reverse(int x);//整数反转
	bool  isPalindrome(int x);//回文数
	string addBinary(string a, string b);//二进制相加
	int romanToInt(string s);//罗马数字转阿拉伯数字
	string longestCommonPrefix(vector<string>& strs);//字符串数组中的最长公共前缀
	bool isValid(string s);//有效的括号
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2);//两个有序链表
	int removeDuplicates(vector<int>& nums);//删除排序数组中的重复项
	int removeElement(vector<int>& nums, int val); //给定一个数组 nums 和一个值 val，你需要原地移除所有数值等于 val 的元素，返回移除后数组的新长度。
	int strStr(string haystack, string needle);//手写strstr
	int searchInsert(vector<int> &nums, int target); //有序vector中插入值
	string countAndSay(int n);//check函数头
	//以下3个，动态规划
	int maxSubArray(vector<int>& nums); //给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
	int climbStairs(int n);//爬楼梯的方式最多几种
	int maxProfit(vector<int>& prices);//股票买入卖出的最大利润
	int rob(vector<int>& nums);//小偷
	ListNode* deleteDuplicates(ListNode* head);//删除排序链表中的重复项
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n);////合并两个有序数组
	bool isSameTree(TreeNode* p, TreeNode* q);//判断两个树是不是一致
	bool isSymmetric(TreeNode* root);//判断树是否对称
	int maxDepth(TreeNode* root);//二叉树的最大深度
	vector<vector<int>> levelOrderBottom(TreeNode* root);
	bool isBalanced(TreeNode* root);
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2);
	vector<int> plusOne(vector<int>& digits);
	void moveZeroes(vector<int>& nums);
	vector<int> sortArray(vector<int>& nums);
	vector<int> maxDepthAfterSplit(string seq);
	int maxSubarraySumCircular(vector<int>& A);
	vector<vector<int>> generate(int numRows);
	int lastRemaining(int n);
	int trap(vector<int>& height);
	void rotate(vector<vector<int>>& matrix);
	ListNode* reverseList(ListNode* head);
	void setZeroes(vector<vector<int>>& matrix);
	vector<int> findDiagonalOrder(vector<vector<int>>& matrix);
	string longestPalindrome(string s);
	string reverseWords(string s);
	int strStr1(string haystack, string needle);
	string shortestPalindrome(string s);
	vector<int> commputeNext(string pattern);
	ListNode* reverseBetween(ListNode* head, int m, int n);
};

