#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include<ctype.h>
#include<math.h>
#include<iostream>
#include<unistd.h>// for  sleep function
struct Stack
{
    double *arr;
    int sp;
    int size;

    // Constructor (from C++)
    Stack()
    {
        arr = NULL;
        sp = -1;
        size = 0;
    }
};
bool initializeStack(Stack *s, int sz)
{
	if (s->arr != NULL) //In case previous malloc is called
		free(s->arr);
	s->arr = (double*)malloc(sizeof(double) * sz);
	if (s->arr == NULL)
		return false;
	s->size = sz;
	s->sp = -1;
	return true;
}
int push(Stack *s, double item)
{
    if (s->arr == NULL)
        return -1; // Stack not initialized !
    if (s->sp + 1 == s->size)
        return -2; // Stack overflow !

    s->sp = s->sp + 1; // or s->sp++;
    s->arr[s->sp] = item;
    return 0;
}
int pop(Stack *s, double *item)
{
    if (s->arr == NULL)
        return -1; 
    if (s->sp == -1)
        return -2; 

    *item = s->arr[s->sp];
    s->sp = s->sp - 1; 
    return 0;
}
int top(Stack *s, double *item)
{
    if (s->arr == NULL)
        return -1; 
    if (s->sp == -1)
        return -2; 

    *item = s->arr[s->sp];
    return 0;
}
bool isdigit(char c)
{
    if (c >= '0' && c <= '9')
        return true;
    else
        return false;
}
bool isoperator(char c)
{
    if (c == '-' || c == '+' || c == '/' || c == '*' || c == '(' || c == ')' || c == '!' || c == '^')
        return true;
    else
        return false;
}
int isempty(Stack *s)
{
    if (s->sp == -1)
        return 1;
    else
        return 0;
}
int priority(char c)
{
    if (c == '-' || c == '+')
        return 2;
    else if (c == '*' || c == '/')
        return 3;
    else if (c == '^')
        return 4;
    else if (c == '!')
        return 5;
    else if(c=='('||c==')')
     return 1;
    
    else
        return 0;
}
int check( char eq[256])
 {
     if((isoperator(eq[0])==true) && priority(eq[0]!=1) )
     {
         printf("Invalid Equation Restarting Program");         
         return 1;
     }


     for(int k=0;k<strlen(eq);k++)
     { if((isoperator(eq[k])==true) && (isoperator(eq[k+1])==true)&&(priority(eq[k])!=1)&&(priority(eq[k+1])!=1))// checking if there is a multipe op except bracket
     {
        printf("Invalid Equation Restarting Program");         
        return 1;
     }


     }

     

 }
int intopost(Stack *s, char equ[],char postfix[])
{
 
 initializeStack(s,50);
 int p,p1,j=0;
 double x,y;
 for(int i=0;i<strlen(equ);i++)
{if(isdigit(equ[i])==true || equ[i]== '.' )// to check decimal 
  postfix[j++]=equ[i];
 else if(isoperator( equ[i])==true)
 {  if(equ[i]!='('||equ[i]!=')')
     postfix[j++]=' ';// adding a space between the 2 values to separte them when evaluting 
    p=priority(equ[i]);
   if(p==1)
   {if(equ[i]=='(')
     push(s,equ[i]);
    else if(equ[i]==')')
    { while(1)
      { pop(s,&x);
        if(x=='(')
        break;
        postfix[j++]=x;

     }
 }
    
  }
else if(p==5)
  push(s,equ[i]);
 else if(p<5)
  { top(s,&y);
     p1=priority(y);
      if (p1<p)
      push(s,equ[i]);
   
    while(p1>=p)
    {if(isempty(s)==1)
      {push(s,equ[i]);
        break;
      }
        pop(s,&x);
     postfix[j++]=x;
        top(s,&y);
     p1=priority(y);
     
      
        
       

        }


    
     }
  }


 

}

while(isempty(s)!=1)
{
  pop(s,&y);
  postfix[j++]=y;
}
postfix[j]='\0';
puts(postfix);
}
int calcPostfix(Stack *s, char postfix[], double *result)
{

    double a, b;
    double c=0;//pushed variable
    for (int i = 0; i < strlen(postfix); i++)
    {
    int dotflag=0;  //to determine if dot is found or not

        if (isdigit(postfix[i]) == true)
        {   
        
        int dotX=10;   
        c = postfix[i++] - '0';
        while((isdigit(postfix[i])==true) || postfix[i]== '.' || postfix[i]== ' ')
        { 

            if(postfix[i]==' ')
            {
                i++;
                break;
            }

            else if(postfix[i]=='.')
            {
                dotflag=1;
            }
            else if(dotflag==0)//multi digit
            {  
             c*=10;
             c+=postfix[i]- '0';                         

            }
            else if(dotflag==1)
            { 
                c+=(double(postfix[i]- '0')/dotX);
                dotX*=10;

            }    
            i++;  
                }
                i--;
        push(s, c);
        
        

        }
        else
        {

            pop(s,&a);
            pop(s,&b);
           
                if (postfix[i] == '+')
                    push(s, b + a);                
                else if (postfix[i] == '-')
                    push(s, b - a);
                else if (postfix[i] == '*')
                    push(s, b * a);
                else if (postfix[i] == '/') 
                    push(s, b / a);
                else if (postfix[i] == '^') 
                    push(s, pow(b, a));
                 else if (postfix[i] == '!') 
                    {
                     push(s,b);
                      c=1;
                     for(int i=1;i<=a;i++)
                      c=c*i;
                     push(s,c);
                     

                    }

            
        }
    }

    pop(s, result);
    }
int main()
{
Stack s;
char equ[256];
char postfix[256];
double result;
printf("\nPostFix To Infix Convertor And Calculator Supporting Multidigit And Floating Points\n\n");
printf("Supported Operators:\n+ |Addition\n- |Subtraction\n* |Multiplication\n/ |Division\n! |Factorial\n^ |Power\n");
printf("Please Enter Your Equation:");
gets(equ);
if(check(equ)==1)
{
sleep(2);
system("cls");
main();
}
intopost(&s,equ,postfix);
calcPostfix(&s,postfix,&result);
printf("the result =%0.1f",result);
sleep(5);
main();
}
