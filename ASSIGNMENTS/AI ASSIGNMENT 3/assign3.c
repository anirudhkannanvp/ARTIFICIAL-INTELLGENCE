/*AI ASSIGNMENT 3
GROUP MEMBERS:
ANIRUDH KANNAN V P 201601004
SAIRATHAN V 201601104
*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h> //Header Files
typedef struct Pair{ //Structure to hold class and corresponding values
    float value;
    int cls;
} pair;
int X[7000][200]; // Feature Vectors of Train Data
int Y[7000];    // Class Vector of Train Data
int X1[4000][200]; // Feature Vectors of Test Data
int Y1[4000];   // Class Vector of Test Data
int testinp=3333; // Number of instances in Test Data
int features=192; // Number of features
int instances=6670; // Number of instances in Train data
void scan() // Scanning Train data
{
    FILE *f=fopen("pp_tra.dat","r");
    int i,j;
	for(i=0;i<instances;i++)
    {
		for(j=0;j<features;j++)
		{
			fscanf(f," %d",&X[i][j]);
		}
		fscanf(f," %d",&Y[i]);
	}
	fclose(f);
}
int compare(const void *a,const void *b) // Compare function for qsort which calculates the Kth Nearest Neighbours
{
    return (((pair *)a)->value) > (((pair *)b)->value);
}
void getKvalue(int correct[],int s1,int e1,int s2,int e2,int s3,int e3) // Calculate the K values and number of correctly classified examples for that K
{
    int i,j,k;
    for(i=s1;i<e1;i++)
    {
        pair A[6000];
        int ind=0;
        for(j=s2;j<e2;j++)
        {
            float dist=(float)0;
            for(k=0;k<features;k++)
            {
                dist+=pow(X[i][k]-X[j][k],2);
            }
            A[ind].value=sqrt(dist);// Calculate Distances and store in Array of Structure
            A[ind++].cls=Y[j];
        }
        for(j=s3;j<e3;j++)
        {
            float dist=(float)0;
            for(k=0;k<features;k++)
            {
                dist+=pow(X[i][k]-X[j][k],2);
            }
            A[ind].value=sqrt(dist);
            A[ind++].cls=Y[j];
        }
        qsort(A,ind,sizeof(pair),compare); // Quick Sort for obtaining nearest elements
        int count[10];
        for(j=0;j<10;j++)
        {
            count[j]=0;
        }
        int max=0;
        ind=0;
        for(k=0;k<25;k++)
        {
            count[A[k].cls]++;
            if(count[A[k].cls]>max)
            {
                max=count[A[k].cls];
                ind=A[k].cls;
            }
            if(ind==Y[i])
            {
                correct[k]++;// Counting correctly classified examples for given K
            }
        }
    }
}
int getBestK()
{
    int correct[26];
    int i;
    for(i=0;i<26;i++)
    {
        correct[i]=0;
    }
    getKvalue(correct,0,2223,2223,4446,4446,6670);// First Fold
    getKvalue(correct,2223,4446,0,2223,4446,6670);// Second Fold
    getKvalue(correct,4446,6670,0,2223,2223,4446);// Third Fold
    int ans=0;
    for(i=1;i<25;i++)
    {
        if(correct[ans]<correct[i])// Getting Best K
            ans=i;
    }
    return ans+1;
}
void test(int K)
{
    FILE *f=fopen("pp_tes.dat","r");// Reading Test Data
    int i,j,k;
	for(i=0;i<testinp;i++)
    {
		for(j=0;j<features;j++)
		{
			fscanf(f," %d",&X1[i][j]);
		}
		fscanf(f," %d",&Y1[i]);
	}
	fclose(f);
	int correct=0;
	for(i=0;i<testinp;i++)
    {
        pair A[7000];
        for(j=0;j<instances;j++)
        {
            float dist=(float)0;
            for(k=0;k<features;k++)
            {
                dist+=pow(X1[i][k]-X[j][k],2);
            }
            A[j].value=sqrt(dist);
            A[j].cls=Y[j];
        }
        qsort(A,instances,sizeof(pair),compare);// Calculating K Nearest Neighbours
        int count[10];
        for(j=0;j<10;j++)
        {
            count[j]=0;
        }
        int max=0;
        int ind=0;
        for(k=0;k<K;k++)
        {
            count[A[k].cls]++;
            if(count[A[k].cls]>max)
            {
                max=count[A[k].cls];
                ind=A[k].cls;
            }
        }
        if(ind==Y1[i])
        {
            correct++;
        }
    }
    printf("Total Examples = %d\nCorrectly classified Examples = %d\nClassification Accuracy = %f%%\n",3333,correct,((float)correct)*100.0/(3333.0));
}
int main()
{
    scan();
    int k=getBestK();
    printf("Best K value with Training data obtained using 3fold Cross validation is %d\n",k);
    test(k);
    return 0;
}
