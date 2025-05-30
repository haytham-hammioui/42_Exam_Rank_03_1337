#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int ft_sum(int *t2, int x)
{
    int sum=0;
    int j=0;
    while(j<x)
    {
        sum+=t2[j];
        j++;
    }
    return sum;
}

void ft_solve(int n , int *t, int *t2, int *lock, int s, int x, int i)
{
    if(ft_sum(t2,x)==n)
    {
        int j=0;
        while(j<x)
        {
            printf("%d ", t2[j]);
            j++;
        }
                printf("\n");

        return ;
    }  

    while(i<s)
    {
        if(lock[i])
        {
            i++;
            continue;
        }
        lock[i]=1;
            t2[x]=t[i];
            ft_solve(n , t, t2, lock, s, x+1, i+1);
        lock[i]=0;
        i++;
    }  
}

int main(int ac, char**ar)
{
    if(ac<2)
        return 1;
    
    int s=ac-2;
    int *t=calloc(s, sizeof(int ));
    int *t2=calloc(s, sizeof(int ));
    int *lock=calloc(s, sizeof(int ));
    if(!t || !t || !lock)
        return 1;
    int i=1;
    int n=atoi(ar[i]);
    i++;
    int j=0;
    while(i<ac)
    {
        t[j]=atoi(ar[i]);
        j++;
        i++;
    }
    ft_solve(n , t, t2, lock, s, 0,0);
    free(t);
    return 0;
}