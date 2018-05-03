//
//  lab3.c
//
//
//  Created by Faisal Alnahhas on 4/25/18.
//
// Use suffix array and LCP to compute
// longest common substring of two input strings. BPW
///////////Most of this code is obtained from Dr. Weems's directory/////////////////////////////////////////
///////////Original code (for two strings) can be found  at: http://ranger.uta.edu/~weems/NOTES5311/LAB/LAB3SPR18/SAcommonSubStr2.c
//////////I modified some parts to make them appropriate for this lab///////////////////////////////////////
//The assignment can be found here: http://ranger.uta.edu/~weems/NOTES5311/LAB/LAB3SPR18/
//NOTE: The code isn't fully functional, it works for 3 out of 4 test cases.

//////////////////////////////////////////////////////
///////Compilation and Running Instructions///////////
//type: gcc file.c                                   /
//hit enter                                          /
//type: ./a.out                                      /
//hit enter                                          /
//type string 1                                      /
//hit enter                                          /
//type string 2                                      /
//hit enter                                          /
//type string 3                                      /
//hit enter                                          /
//////////////////////////////////////////////////////

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


char s[1000000],s1[500000],s2[500000],s3[500000];
int n,          // length of s[] including \0
sa[1000000],   // suffix array for s[]
rank[1000000], // rank[i] gives the rank (subscript) of s[i] in sa[]
lcp[1000000];  // lcp[i] indicates the number of identical prefix symbols
// for s[sa[i-1]] and s[sa[i]]

int suffixCompare(const void *xVoidPt,const void *yVoidPt)
{
    // Used in qsort call to generate suffix array.
    int *xPt=(int*) xVoidPt,*yPt=(int*) yVoidPt;
    
    return strcmp(&s[*xPt],&s[*yPt]);
}

void computeRank()
{
    // Computes rank as the inverse permutation of the suffix array
    int i;
    
    for (i=0;i<n;i++)
        rank[sa[i]]=i;
}

void computeLCP()
{
    //Kasai et al linear-time construction
    int h,i,j,k, k2;
    int f;
    
    h=0;  // Index to support result that lcp[rank[i]]>=lcp[rank[i-1]]-1
    for (i=0;i<n;i++)
    {
        k=rank[i];
        if (k==0)
            lcp[k]=(-1);
        else
        {
            j=sa[k-1];
            f=sa[k-2];
            // Attempt to extend lcp
            //while (i+h<n && j+h<n && s[i+h]==s[j+h])
            while (i+h<n && j+h<n && f+h<n && s[i+h]==s[j+h] && s[f+h]==s[j+h] && s[f+h]==s[i+h])
                h++;
            lcp[k]=h;
        }
        if (h>0)
            h--;  // Decrease according to result
    }
}

int fibIndex=0;

void fib(k)
int k;
{
    if (k==0)
        s[fibIndex++]='1';
    else if (k==1)
        s[fibIndex++]='0';
    else
    {
        fib(k-1);
        fib(k-2);
    }
}

/*int stringNumber(int i)
 {
 if(sa[i]<dollarPos)
 return 1;
 else if(sa[i] > dollarPos && sa[i] < poundPos)
 return 2;
 else
 return 3;
 } */

int main()
{
    int i,j,k,p, dollarPos, poundPos, LCSpos=0,LCSlength=0;
    int f; //index of 3rd string
    
    scanf("%s",s1);
    scanf("%s",s2);
    scanf("%s",s3);
    
    
    for (i=0;s1[i]!='\0';i++)
        s[i]=s1[i];
    dollarPos=i;
    s[i++]='$';
    for (j=0;s2[j]!='\0';j++)
        s[i+j]=s2[j];
    poundPos= i + j;
    s[i + j++]='#';
    for (f=0;s3[f]!='\0';f++)
        s[i+j+f]=s3[f];
    s[i+j+f]='\0';
    n=i+j+f+1;
    
    //for(int m=0; s[m]!='\0'; m++)
    //  printf("s: %c\n",s[m]);
    
    /*
     fib(4);
     fib(6);
     dollarPos=fibIndex;
     s[fibIndex++]='$';
     fib(5);
     fib(7);
     s[fibIndex]='\0';
     n=fibIndex+1;
     */
    
    
    /*
     for (i=0;i<1000;i++)
     s[i]='a';
     s[1000]='b';
     s[1001]='\0';
     */
    /*
     s[0]='a';
     for (i=1;i<1000;i++)
     s[i]='b';
     s[1000]='\0';
     */
    
    //n=strlen(s)+1;
    printf("n is %d\n",n);
    
    // Quick-and-dirty suffix array construction
    for (i=0;i<n;i++)
        sa[i]=i;
    qsort(sa,n,sizeof(int),suffixCompare);
    computeRank();
    computeLCP();
    /*if (n<200)
     {
     printf("i   sa  suffix                              lcp s rank lcp[rank]\n");
     for (i=0;i<n;i++)
     printf("%-3d %-3d %-35.35s %-3d %c  %-3d  %-3d\n",
     i,sa[i],&s[sa[i]],lcp[i],s[i],rank[i],lcp[rank[i]]);
     } */
    
    
    for (i=1;i<n;i++)
        if (  ((sa[i-1]<dollarPos && sa[i]>dollarPos) ||  (sa[i-1]>dollarPos && sa[i]<dollarPos) ) &&
            ((sa[i-1]<poundPos && sa[i]>poundPos)     ||  (sa[i-1]>poundPos && sa[i]<poundPos))
            && lcp[i]>LCSlength)
        {
            //stringNumber(i);
            LCSpos=i;
            LCSlength=lcp[i];
        }

    printf("Length of longest common substring is %d\n",LCSlength);
    //printf("at position %d\n",LCSpos);
    for (i=0;i<LCSlength;i++)
        printf("%c",s[sa[LCSpos]+i]);
    printf("\n");
    
}
