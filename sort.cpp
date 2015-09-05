#include<iostream>
#include<string.h>
using namespace std;

template <typename T>
void myswap(T& left,T& right)
{
	T temp = left;
	left = right;
	right = temp;
}

//o(n2)
template <typename T>
void bubblesort(T a[],int n)
{
	int i,j;
	for(i=0;i<n-1;i++)
	for(j=0;j<n-1-i;j++)
			if(a[j]>a[j+1])
				myswap(a[j],a[j+1]);
}

template <typename T>
void bubblesort_iv(T a[],int n)
{
	int i,j,pos;
	i= n-1;
	while(i)
	{
		pos =0;
		for(j=0;j<i;j++)
			if(a[j] > a[j+1])
			{
				myswap(a[j],a[j+1]);
				pos =j;
			}
		i = pos;
	}
}

//*******insertsort

//o(n2)
template <typename T>
void insertsort(T a[],int n)
{
	int i,j;
	T tmp;
	for(i=1;i<n;i++)
	{
		tmp = a[i];
		for(j=i;j>0 && a[j-1]>tmp;j--)
			a[j] = a[j-1];
		a[j] = tmp;
	}
}

//o(n^3/2)not stable
template <typename T>
void shellsort(T a[],int n)
{
	int i,j,increament;
	T tmp;
	for(increament = n/2;increament>0 ; increament /=2)
		for(i=increament;i<n;i++)
		{
			tmp = a[i];
			for(j=i; j>=increament && a[j-increament]>tmp; j -=increament)
				a[j] = a[j-increament];
			a[j] = tmp;
		}
}

//o(n2)
template <typename T>
void selectsort(T a[],int n)
{
	int i,j,mindex;
	for(i=0;i<n;i++)
	{
		mindex = i;
		for(j=i+1;j<n;j++)
			if(a[j]<a[mindex])
				mindex=j;
		swap(a[i],a[mindex]);
	}
}


template <typename T>
void selectsort_iv(T a[],int n)
{
	int i,j,mindex,maxdex;
	for(i=0;i<=n/2;i++)
	{
		mindex = i;
		maxdex = n-i-1;
		for(j=i+1;j<n-i;j++)
		{
			if(a[j]<a[mindex])
				mindex=j;
			if(a[j]>a[maxdex])
				maxdex=j;
		}
		swap(a[i],a[mindex]);
		swap(a[n-i-1],a[maxdex]);
	}
}

//O(nlogn)
//*********heapsort
//heap:二叉堆，优先队列。性质：结构性和堆序性。
//- and + is priority than >> 
#define PARENT(x) (((x)+1>>1) -1) 
#define LEFT(x) (((x)<<1) +1)
#define RIGHT(x) ((x)+1<<1)

template <typename T>
void perdown(T a[],int i,int n)
{
	int child;
	T tmp;
	for(tmp = a[i];LEFT(i)<n;i=child)
	{
		child = LEFT(i);
		if((child != n-1)&&(a[child]<a[child+1]))
			child++;
		if(a[child]>tmp)
			a[i]= a[child];
		else
			break;
	}
	a[i]=tmp;
}

template <typename T>
void heapsort(T a[],int n)
{
	int i;

	for(i=PARENT(n-1);i>=0;i--)
		perdown(a,i,n);

	for(i=n-1;i>0;i--)
	{
		swap(a[0],a[i]);
		perdown(a,0,i);
	}
}

//*************mergsort
template <typename T>
void merge(T a[],T tmp[],int lpos,int rpos,int rend)
{
	int lend= rpos -1;
	int tpos=lpos;
	int i,num = rend - lpos +1;
	for(;lpos<=lend && rpos<=rend;)
		if(a[lpos]<a[rpos])
			tmp[tpos++] = a[lpos++];
		else
			tmp[tpos++] = a[rpos++];

	while(lpos<=lend)
		tmp[tpos++] = a[lpos++];
	while(rpos<=rend)
		tmp[tpos++] = a[rpos++];
	
	for(i=0;i<num;i++,rend--)
		a[rend] = tmp[rend];
}

template <typename T>
void msort(T a[],T tmp[],int left,int right)
{
	int center;
	if(left<right)
	{
		center = (left + right)/2;
		msort(a,tmp,left,center);
		msort(a,tmp,center+1,right);
		merge(a,tmp,left,center+1,right);
	}
}

//o(NlogN)
template <typename T>
void mergesort(T a[],int n)
{
	T* tmparry;
	tmparry = new T[n];
	if(tmparry != NULL)
	{
		msort(a,tmparry,0,n-1);
		delete [] tmparry;
	}
	else
		cout<<"error!"<<endl;	
}


//*********quicksort****

template <typename T>
T median3(T a[],int left,int right)
{
	int center = (left + right)/2;

	if(a[left]>a[center])
		swap(a[left],a[center]);
	if(a[left]>a[right])
		swap(a[left],a[right]);
	if(a[center]>a[right])
		swap(a[center],a[right]);
	
	swap(a[center],a[right-1]);
	return a[right -1];
}

#define CUTOFF (3)
template <typename T>
void qsort(T a[],int left,int right)
{
	if(left + CUTOFF>=right)
	{
		int i=left,j=right;
		T pivot= median3(a,left,right);
		for(;;)
		{
			while(a[++i]<pivot);
			while(a[--j]>pivot);
			if(i<j)
				swap(a[i],a[j]);
			else 
				break;
		}
		swap(a[i],a[right-1]);
		qsort(a,left,i-1);
		qsort(a,i+1,right);
	}
	else
		insertsort(a+left,right - left +1);
}

template <typename T>
void quicksort(T a[],int n)
{
	qsort(a,0,n-1);
}


//***********countsort
void countsort(int a[],int n)
{
	int min=a[0];
	int max =a[0];
	int i;
	for(i=0;i<n;i++)
	{
		if(a[i]<min)
			min = a[i];
		if(a[i]>max)
			max = a[i];
	}

	int size = max -min +1;
	int count[size];
	memset(count,0,sizeof(count));
	
	for(i=0;i<n;i++)
		count[a[i]-min]++;
	for(i=1;i<size;i++)
		count[i] += count[i-1];
	
	int tmp[n];
	for(i=n-1;i>=0;i--)
		tmp[--count[a[i]-min]]=a[i];
	

	for(i=0;i<n;i++)
		a[i]=tmp[i];
}

//**************radixsort
int getdigit(int num,int pos)
{
	int result;
	switch(pos)
	{
		case 1: 
			result =num%10;
			break;
		case 2:
			result = num%100/10;
			break;
		case 3:
			result = num%1000/100;
			break;
		default : 
			break;
	}
	return result;
}

template <typename T>
void radixsort(T a[],int n)
{
	int count[10];
	T bucket[n];
	int digit,key,i;

	for(key=1;key<=2;key++)
	{
		memset(count,0,sizeof(int)*10);

		for(i=0;i<n;i++)
		{
			digit = getdigit(a[i],key);
			count[digit]++;
		}
	
		for(i=1;i<10;i++)
			count[i] += count[i-1];
		
		for(i=n-1;i>=0;i--)
		{
			digit= getdigit(a[i],key);
			bucket[--count[digit]]= a[i];
		}
	
		for(i=0;i<n;i++)
			a[i]=bucket[i];
	}
}


//*************bucksort

typedef struct node
{
	int key;
	struct node* next;
	node(int key_)
	{
		key = key_;
		next = NULL;
	}
}node;

#define buck_size 10

//template <typename T>
void bucksort(int a[],int n)
{
	node* buck_table[buck_size];
	memset(buck_table,0,sizeof(buck_table));

	int i,j,max_num;
	for(i=0;i<buck_size;i++)
		buck_table[i] = new node(0);

	max_num = a[0];
	for(i=1;i<n;i++)
		if(a[i]>max_num)
			max_num = a[i];
	
	node* ptr;
	node* head;
	for(i=0;i<n;i++)
	{
		ptr = new node(a[i]);
		int index = a[i]*buck_size/(max_num+1);
		head = buck_table[index];

		if(head->key ==0)
		{
			head->next = ptr;
			(buck_table[index]->key)++;
		}
		else
		{
			while(head->next !=NULL && head->key <=a[i])
				head =head->next;
			ptr->next = head->next;
			head->next = ptr;
			(buck_table[index]->key)++;
		}
	}

	node* tmp;
	for(i=0,j=0;i<n&&j<buck_size;j++)
	{
		tmp = buck_table[j]->next;
		while(tmp->next != NULL)
		{
			a[i++] = tmp->key;
			tmp = tmp->next;
		}
	}

	for(i=0;i<buck_size;i++)
	{
		while(buck_table[i] !=NULL)
		{
			tmp = buck_table[i] ->next;
			delete buck_table[i];
			buck_table[i] = tmp;
		}
			
	}

}



int main(int argc,char* argv[])
{
	int arr[]= {1,32,3,89,24,15,23,3,95,22};
	//bubblesort(arr,10);
	//bubblesort_iv(arr,10);
	//insertsort(arr,10);
	//shellsort(arr,10);
	//selectsort(arr,10);
	//selectsort_iv(arr,10);
	//heapsort(arr,10);
	//mergesort(arr,10);
	//quicksort(arr,10);
	//radixsort(arr,10);
	countsort(arr,10);
	cout<<"the sort result is:"<<endl;
	for(int i =0;i<10;i++)
		cout<<arr[i]<<" ";
	cout<<endl;
}
