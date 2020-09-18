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
	vector<int> twoSum(vector<int>& nums, int target);// ������ӵ���Ŀ����
	int reverse(int x);//������ת
	bool  isPalindrome(int x);//������
	string addBinary(string a, string b);//���������
	int romanToInt(string s);//��������ת����������
	string longestCommonPrefix(vector<string>& strs);//�ַ��������е������ǰ׺
	bool isValid(string s);//��Ч������
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2);//������������
	int removeDuplicates(vector<int>& nums);//ɾ�����������е��ظ���
	int removeElement(vector<int>& nums, int val); //����һ������ nums ��һ��ֵ val������Ҫԭ���Ƴ�������ֵ���� val ��Ԫ�أ������Ƴ���������³��ȡ�
	int strStr(string haystack, string needle);//��дstrstr
	int searchInsert(vector<int> &nums, int target); //����vector�в���ֵ
	string countAndSay(int n);//check����ͷ
	//����3������̬�滮
	int maxSubArray(vector<int>& nums); //����һ���������� nums ���ҵ�һ���������͵����������飨���������ٰ���һ��Ԫ�أ������������͡�
	int climbStairs(int n);//��¥�ݵķ�ʽ��༸��
	int maxProfit(vector<int>& prices);//��Ʊ�����������������
	int rob(vector<int>& nums);//С͵
	ListNode* deleteDuplicates(ListNode* head);//ɾ�����������е��ظ���
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n);////�ϲ�������������
	bool isSameTree(TreeNode* p, TreeNode* q);//�ж��������ǲ���һ��
	bool isSymmetric(TreeNode* root);//�ж����Ƿ�Գ�
	int maxDepth(TreeNode* root);//��������������
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

