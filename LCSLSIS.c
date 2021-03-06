//A lot of this code is reused from http://ranger.uta.edu/~weems/NOTES2320/cse2320.html in LSIS and LCS files
//http://ranger.uta.edu/~weems/NOTES5311/LAB/LAB1SPR18/ the assignment
// LSIS code from: http://ranger.uta.edu/~weems/NOTES2320/LSIS.c
// LCD code from: http://ranger.uta.edu/~weems/NOTES2320/LCS.c
//  lab1.c
//  Note: this code is incomplete and doesn't run
//
//  Created by Faisal Alnahhas on 1/30/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

////////////////////////BEGINNING OF DR. WEEMS CODE///////////////////////////////////////
#define MAXSIZE 70

int length1,length2;
char string1[MAXSIZE],string2[MAXSIZE];


int LCSlength;
char LCSstring[MAXSIZE];

int *vertical2;
int *horizontal;

int cost[MAXSIZE+1][MAXSIZE+1];

void LCS()
{
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    int i,j,k;
    /*string1[i] is associated with row i+1
     string2[i] is associated with column i+1 */
    /*Initialize*/
    for (i=0;i<=length1;i++)
        cost[i][0]=0;
    for (i=1;i<=length2;i++)
        cost[0][i]=0;
    
    for (i=1;i<=length1;i++)
        for (j=1;j<=length2;j++)
            cost[i][j]=
            (string1[i-1]==string2[j-1])
            ? cost[i-1][j-1]+1
            : (cost[i][j-1]<=cost[i-1][j]) ? cost[i-1][j]
            : cost[i][j-1];
    
    LCSlength=cost[length1][length2];
    LCSstring[LCSlength]='\0';
    i=length1;
    j=length2;
    while (cost[i][j]!=0)
        if (string1[i-1]==string2[j-1])
        {
            LCSstring[cost[i][j]-1]=string1[i-1];
            i--;
            j--;
        }
        else if (cost[i][j-1]<=cost[i-1][j])
            i--;
        else
            j--;
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("CPU Time Used for LCS: %f\n", cpu_time_used);
}

int binSearchLast(int *a,int n,int key)
{
    // Input: int array a[] with n elements in ascending order.
    //        int key to find.
    // Output: Returns subscript of the last a element <= key.
    //         Returns -1 if key<a[0].
    // Processing: Binary search.
    int low,high,mid;
    low=0;
    high=n-1;
    // subscripts between low and high are in search range.
    // size of range halves in each iteration.
    // When low>high, low==high+1 and a[high]<=key and a[low]>key.
    while (low<=high)
    {
        mid=(low+high)/2;
        if (a[mid]<=key)
            low=mid+1;
        else
            high=mid-1;
    }
    return high;
    

}

////////////////////////////END OF DR. WEEMS CODE//////////////////////////////////////////////

FILE *file_manage(char *f)
{
    char line[256];
    char line1[256];
    char junk[256];
    //int vertical[256];
    int rows, columns;
    int vertical[sizeof(f)];
    int vertical2[rows];
    int horizontal[columns*2];
    FILE *fo = fopen(f, "r");
    if(fo == NULL)
    {
        printf("File not found.\n");
        return fo;
    }
    
    else
    {
        fgets(line1, sizeof(line1), fo);
        printf("%s", line1);
        sscanf(line1, "%d %d", &rows, &columns);
        printf("rows: %d,", rows);
        printf("columns: %d\n",columns);
        //printf("%d\n", rows);
       /* while(matrix_size != 3)
        {
            //char *chars = (char *) malloc (sizeof())
            //char chars[3] = fgetc(fo);
            printf("%s\n", chars);
            matrix_size++;
            rows = chars[0] - '0';
            columns = chars[2] - '0';
        } */
    }
    
    //rewind(fo);

    while(fscanf(fo, "%d ", vertical) != -1)
    {
        printf("vertical %d\n", *vertical);
        if((*vertical) == -1)
        {
            while(fscanf(fo, "%d ", horizontal) != -1)
            {
                //printf("found -1\n");
                //continue;
                printf("horizntal %d\n", *horizontal);
                //fscanf(fo, "%d ", horizontal);
            }
        }
    }
         
     /*int size_v = sizeof(vertical);
     int h_size = size_v/2;
     int i, j;
     
     if(size_v % 2 == 0)
     {
     for(i = 0; i < h_size ; i++)
     {
     vertical2[i] = vertical[i];
     printf("vertical2[%d]: \n", vertical2[i]);
     }
     for(j = 0; j < h_size; j++)
     {
     printf("verticallll[%d]\n", vertical[i]);
     horizontal[i] = vertical[h_size + 1];
     printf("horizontal[%d]: \n", horizontal[i]);
     }
     
     }
     else
     {
     for(i = 0; i < h_size ; i++)
     {
     vertical2[i] = vertical[i];
     printf("vertical2[%d]: \n", vertical2[i]);
     }
     for(j = 0; j < h_size; j++)
     {
     horizontal[j] = vertical[h_size + 1];
     printf("horizontal[%d]: \n", horizontal[j]);
     }
     
     } */

    
  /*  while (fgets(line, sizeof(line), fo)) {
        int i = 0;
        //printf("%s", line);
        vertical[i] = atoi(line);
        i++;
        //printf("vertical[i]: %d\n", vertical[i]);
        
        if(!strcmp(line, "-1"))
        {
            break;
        }
        printf("new vertical[i]: %d\n", vertical[i]);
    } */
    
    /*while(1)
    {
        for(int i = 0; i < 9; i++)
        {
            c = fgetc(fo);
            if(feof(fo))
            {
                break;
            }
            else
            {
                vertical[i] = c;
                printf("%c", c);
                printf("vertical[i]: %d", vertical[i]);
            }
        }
        
    } */
    
  /*  while(!feof(fo)) {
        fscanf(fo,"%[^ \n\t\r]s",line); //Get text
        printf("%s, \n", line);
        fscanf(fo,"%[ \n\t\r]s",junk); //Remove any 'white space' characters
        //printf("junk: %s\n", junk);
    }
    

    
    while(*c)
    { //TODO: copy values until -1 to array, then repeat the loop
        if(strchr(minusone, *c))
        {
            printf("found: %c %s", *c, line);
        }
        c++;
    } */

    int k;
    for (k = 0; k < rows - 1; k++)
    {
        printf("vertical2[%d]: %d\n", k, vertical2[k]);
        sprintf(&string1[k], "%d", vertical2[k]);
        //printf("string1[%d]: %c \n", k, string1[k]);
        //sprintf(&string2[k], "%d", horizontal[k]);
        //string2[k] = horizontal[k] + '\0';
        //printf("string2[%d]: %c \n", k, string2[k]);
    }
    
    int l;
    for (l = 0; l < columns - 1; l++)
    {
        printf("horizontal[%d]: %d\n", l, horizontal[l]);
        sprintf(&string2[l], "%d", horizontal[l]);
        //string2[k] = horizontal[k] + '\0';
        //printf("string2[%d]: %c \n", l, string2[l]);
    }
    
    fclose(fo);
    
    /*char stringBufferv[MAXSIZE];
    char stringBufferh[MAXSIZE];
    //char* outputStrings[5];
    
    for (int i = 0 ; i < rows ; ++i)
    {
        snprintf(stringBufferv, rows, "%d", vertical2[i]);
        snprintf(stringBufferh, columns, "%d", horizontal[i]);

        string1[i] = strdup(stringBufferv);
        string2[i] = strdup(stringBufferh);
    } */

    return fo;
    
}

void positions(int seq1[MAXSIZE], int seq2[MAXSIZE])
{
    int ind_array[MAXSIZE][MAXSIZE];
    
    int m, m2, mi = 0;
    
    int array_size = (MAXSIZE / sizeof(int));
    
    
    for(m=0; m<array_size; m++)
    {
        for(m2= m; m2 < array_size; m2++)
        {
            // printf("m: %d\n", m);
            //  printf("seq2[%d]: %d\n", m2, seq2[m2]);
            if(m != seq2[m2])
            {
                m = seq2[m2]; //reset the index
                // printf("m now:%d\n", m);
                mi = m2;
                ind_array[m][m2] = mi;
                seq1[m] = ind_array[m][mi];
                //printf("m2: %d\n", m2);
                //printf("mi: %d\n", mi);
                printf("ind_array[%d][%d]: %d\n", m, ind_array[m][mi], m2);
                printf("seq[%d]: %d\n", m, seq1[m]);
            }
            else
            {
                mi = m2;
                ind_array[m][m2] = mi;
                seq1[m] = ind_array[m][mi];
                //printf("m2: %d\n", m2);
                //printf("mi: %d\n", mi);
                printf("ind_array[%d][%d]: %d\n", m, ind_array[m][mi], m2);
                printf("seq[%d]: %d\n", m, seq1[m]);
            }
        }
    }
    
    
}





int main(int argc, char *argv[])
{
    if (argc != 2) printf("Please choose one input file only.\n");
    
    file_manage(argv[1]);
    
    int i,j;

    length1=strlen(string1);
    length2=strlen(string2);
    LCS();

    printf("LCS is %s, length==%d\n",LCSstring,LCSlength);
    
    // Print table
    printf("    ");
    for (i=0;i<length2;i++)
        printf("  %c",string2[i]);
    printf("\n ");
    for (i=0;i<=length2;i++)
        printf(" %2d",cost[0][i]);
    printf("\n");
    for (i=0;i<length1;i++)
    {
        printf("%c",string1[i]);
        for (j=0;j<=length2;j++)
            printf(" %2d",cost[i+1][j]);
        printf("\n");
    }
    
    ///////////////////////////////LSIS///////////////////////////////////////
    //Modified some of Dr. Weems's code for LSIS//////////////////////////////
    clock_t start2, end2;
    double cpu_time_used2;
    start2 = clock();
    //positions(vertical2, horizontal);
    int n;
    int *y,*bsTabC,*bsTabI,*C,*j2;
    int i2,k,LISlength;
    
    // Get input sequence
    //scanf("%d",&n);
    y=(int*) malloc((n+1)*sizeof(int));
    bsTabC=(int*) malloc((n+1)*sizeof(int));
    bsTabI=(int*) malloc((n+1)*sizeof(int));
    C=(int*) malloc((n+1)*sizeof(int));
    j2=(int*) malloc((n+1)*sizeof(int));
    if (!y || !bsTabC || !bsTabI || !C || !j2)
    {
        printf("malloc fail %d\n",__LINE__);
        exit(0);
    }
    for (i2=1;i2<=n;i2++)
        vertical2[i2] = y[i2]+1;
        //scanf("%d",y+i2);
    // Initialize table for binary search for DP
    bsTabC[0]=(-999999);  // Must be smaller than all input values.
    bsTabI[0]=0;          // Index of predecessor (0=grounded)
    for (i2=1;i<=n;i++)
        bsTabC[i2]=999999;   // Must be larger than all input values.
    
    C[0]=0;  // DP base case
    j2[0]=0;
    
    for (i2=1;i2<=n;i2++)
    {
        // Find SIS that y[i] could be appended to.
        // See CSE 2320 Notes 01 for binSearchLast()
        k=binSearchLast(bsTabC,n+1,y[i2]);
        // y[i] only matters if it is not already in table.
        if (bsTabC[k]<y[i2]) {
            C[i2]=k+1;         // Save length of LIS for y[i]
            j2[i2]=bsTabI[k];   // Predecessor of y[i]
            bsTabC[k+1]=y[i2]; // Decrease value for this length IS
            bsTabI[k+1]=i2;
        }
        else
        {
            C[i2]=(-1);        // Mark as ignored
            j2[i2]=(-1);
        }
    }
    end2 = clock();
    cpu_time_used2 = ((double) (end2 - start2)) / CLOCKS_PER_SEC;
    printf("CPU Time Used for LSIS: %f\n", cpu_time_used2);
    
    printf("  i2   y   C   j2\n");
    printf("---------------\n");
    for (i2=1;i2<=n;i2++)
        printf("%3d %3d %3d %3d\n",i2,y[i2],C[i2],j2[i2]);
    
    for (LISlength=n;
         bsTabC[LISlength]==999999;
         LISlength--)
        ;
    printf("  i2 bsTabC bsTabI\n");
    printf("-----------------\n");
    for (i2=1;i2<=LISlength;i2++)
        printf("%3d %6d %6d\n",i2,bsTabC[i2],bsTabI[i2]);
    printf("Length of LIS is %d\n",LISlength);
    printf("LIS reversed\n");
    for (i2=bsTabI[LISlength];
         i2>0;
         i2=j2[i2])
        printf("%d\n",y[i2]);
    
    free(y);
    free(bsTabC);
    free(bsTabI);
    free(C);
    free(j2);
    ////////////////////////////END OF LSIS///////////////////////////////////
    
    return 0;
}
