#include<iostream>

using namespace std;

typedef struct ListNode
{
	int m_nkey;
	struct ListNode *m_pNext;
}ListNode;

int NodeCount(ListNode *pHead)
{
	if(pHead == NULL)
		return 0;
	
	int nodecount =0;
	ListNode *p = pHead;
	while(p != NULL)
	{
		p = p->m_pNext;
		++nodecount;
	}

	return nodecount;
}

ListNode * ReverseList(ListNode *pHead)
{
	if(pHead==NULL || pHead->m_pNext==NULL)
		return pHead;
	
	ListNode *pReversedHead=NULL;
	ListNode *pCurrent=pHead;
	while(pCurrent)
	{
		ListNode *pTemp = pCurrent;
		pCurrent = pCurrent->m_pNext;
		pTemp->m_pNext = pReversedHead;
		pReversedHead = pTemp;
	}
	return pHead;
}

ListNode * GetKthNode(ListNode *pHead,unsigned int k)
{
	if(k==0 || pHead ==NULL)
		return NULL;
	
	ListNode *pAhead = pHead;
	ListNode *pBehind = pHead;

	while(k>1 && pAhead)
	{
		pAhead = pAhead->m_pNext;
		--k;
	}
	if(pAhead ==NULL)
		return NULL;
	while(pAhead)
	{
		pAhead = pAhead->m_pNext;
		pBehind = pBehind->m_pNext;
	}

	return pBehind;

}

int main(int argc,char *argv[])
{
	
	return 0;


}
