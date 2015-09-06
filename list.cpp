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

ListNode * rGetKthNode(ListNode *pHead,unsigned int k)
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
	while(pAhead->m_pNext != NULL)
	{
		pAhead = pAhead->m_pNext;
		pBehind = pBehind->m_pNext;
	}
	return pBehind;
}

ListNode * GetMiddleNode(ListNode *pHead)
{
	if(pHead==NULL || pHead->m_pNext ==NULL)
		return pHead;
	
	ListNode *pAhead = pHead;
	ListNode *pBehind = pHead;
	
	while(pAhead->m_pNext != NULL)
	{
		pAhead = pAhead->m_pNext;
		if(pAhead->m_pNext != NULL)
			pAhead = pAhead->m_pNext;
		else
			break;
		pBehind= pBehind->m_pNext;
			
	}
	return pBehind;
}

void RPrintList(ListNode* pHead)
{
	stack<ListNode *> s;
	ListNode *pNode =pHead;
	while(pNode != NULL)
	{
		s.push(pNode);
		pNode = pNode->m_pNext;
	}
	while(!s.empty())
	{
		pNode = s.top();
		cout<<pNode->m_nkey<<' ';
		s.pop();
	}
}

ListNode* MergeSortedList(ListNode *pHead1,ListNode *pHead2)
{
	if(pHead1 == NULL)
		return pHead1;
	if(pHead2 == NULL)
		return pHead2;
	
	ListNode *pHeadMerged =NULL;
	if(pHead1->m_nkey > pHead2->m_nkey)
	{
		pHeadMerged = pHead1;
		pHead1 = pHead1->m_pNext;
		pHeadMerged->m_pNext = NULL;
	}
	else
	{
		pHeadMerged = pHead2;
		pHead2 = pHead2->m_pNext;
		pHeadMerged->m_pNext = NULL;
	}

	ListNode *pTemp = pHeadMerged;
	while(pHead1 && pHead2)
	{
		if(pHead1->m_nkey > pHead2->m_nkey)
		{
			pTemp->m_pNext = pHead1;
			pHead1 = pHead1->m_pNext;
			pTemp = pTemp->m_pNext;
			pTemp->m_pNext = NULL;


		
		}
		else
		{
			pTemp->m_pNext = pHead2;
			pHead1 = pHead2->m_pNext;
			pTemp = pTemp->m_pNext;
			pTemp->m_pNext = NULL;
		
		}
	
	}

	if(pHead1)
		pTemp->m_pNext = pHead1;
	if(pHead2)
		pTemp->m_pNext = pHead2;
	
	return pHeadMerged;

}


bool HasCircle(ListNode *pHead)
{
	ListNode *pFast = pHead;
	ListNode *pSlow = pHead;
	while(pFast && pFast->m_pNext != NULL)
	{
		pFast = pFast->m_pNext->m_pNext;
		pSlow = pSlow->m_pNext;
		if(pFast == pSlow)
			return ture;
	}
	return false;
}

ListNode* GetFirstCommonNode(ListNode *pHead1,ListNode *pHead2)
{
	if(pHead1==NULL || pHead2==NULL)
		return NULL;
	
	unsigned int len1=1;
	ListNode pTail1= pHead1;
	while(pTail1->m_pNext != NULL)
	{
		++len1;
		pTail1 = pTail1->m_pNext;
	}

	unsigned int len2=1;
	ListNode pTail2= pHead2;
	while(pTail2->m_pNext != NULL)
	{
		++len2;
		pTail2 = pTail2->m_pNext;
	}
	if(pTail1 != pTail2)
		return NULL;

	pTail1 = pHead1;
	pTail2 = pHead2;
	if(len1 > len2)
	{
		int temp = len1 -len2;
		while(temp--)
			pTail1 = pTail1->m_pNext;
	}
	else
	{
		int temp = len2 -len1;
		while(temp--)
			pTail2 = pTail2->m_pNext;
	}
	while(pTail1 != pTail2)
	{
		pTail1 = pTail1->m_pNext;
		pTail2 = pTail2->m_pNext;
	}

	return pTail1;
}

void Delete(ListNode *pHead,ListNode *pToBeDeleted)
{
	if(pToBeDeleted == NULL)
		return;
	if(pToBeDeleted->m_pNext !=NULL)
	{
		pToBeDeleted->m_nkey = pToBeDeleted->m_pNext->m_nkey;
		ListNode *pTemp = pToBeDeleted->m_pNext;
		pToBeDeleted->m_PNext = pToBeDeleted->m_pNext->m_pNext;
		delete pTemp;
	}
	else
	{
		ListNode *pNode =pHead;
		while(pNode->m_pNext != pToBeDeleted)
			pNode = pNode->m_pNext;
		pNode->m_pNext = NULL;
		delete pToBeDeleted;
	}
}

int main(int argc,char *argv[])
{
	
	return 0;


}
