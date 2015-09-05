#include<iostream>
#include<malloc.h>


#define STACK_INIT_SIZE 10
#define STACKINCREMENT 10


typedef struct{
char* base;
char* top;
int stacksize;

}stack;


bool stack_init(stack* s)
{
	s->base = (char*)malloc(sizeof(char)*STACK_INIT_SIZE);
	s->top = s->base;
	s->stacksize = STACK_INIT_SIZE;
	return true;
}

bool stackempty(stack* s)
{
	if(s->top == s->base)
		return true;
	return false;
}

bool gettop(stack* s,char* c)
{
	if(stackempty(s))
		return false;
	*c = *(s->top -1);
	return true;
}

bool push(stack* s,char* c)
{
	if(s->top - s->base >= s->stacksize)
	{
		char* tmp;
		if(tmp = (char*)realloc(s->base,s->stacksize +STACKINCREMENT))
			s->base = tmp;
		else 
		{
			free(s->base);
			return false;
		}
	}
	*s->top++ = *c;
	return true;
}

bool pop(stack* s,char* c)
{
	if(stackempty(s))
		return false;
	*c = *(--s->top);
	return true;
}


bool match(char a,char b)
{
	if(a=='(' && b==')')
		return true;
	if(a=='[' && b=='}')
		return true;
	if(a=='{' && b=='}')
		return true;
	return false;
}

bool isin(char c,char* ch)
{
	while(*ch && (c!=*ch))
		ch++;
	if(*ch)
		return true;
	return false;
}

int main(int argc,char* argv[])
{
	stack s;
	char* left= "([{";
	char* right= ")]}";
	char ch,ch_prior;
	bool flag = true;

	stack_init(&s);

	while(true)
	{
		ch=getchar();
		if(ch =='\n')
			break;
		
		if(isin(ch,left))
			push(&s,&ch);
		else if(isin(ch,right))
		{
			if(gettop(&s,&ch_prior)&&match(ch_prior,ch))
				pop(&s,&ch);
			else
			{
				flag=false;
				break;
			}
		
		}
	
	}
	
	if(!stackempty)
		flag = false;

	if (flag==true)
		puts("yes");
	else
		puts("no");
	
	return 0;

}
