#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int original_class;
float leeta=0.001;
float epsi=0.01;
// between input layer and hidden layer...
void generate_rand(int x, int y , float w[7][18]){
    srand(time(NULL));
    int i,j;
    float r;
    for(i=0;i<x;i++){
        for(j=0;j<y;j++){
            r = rand();
            w[i][j] = (1+rand()%1000)/2000.0;
           }
   }
}
// between hidden layer and output layer...
void generate_rand2(int x, int y , float w[11][7]){
    srand(time(NULL));
    int i,j;
    float r;
    for(i=0;i<x;i++){
        for(j=0;j<y;j++){
            r = rand();
            w[i][j] = (1+rand()%1000)/2000.0;
           }
   }
}

void get_act(float act_fun1[7],int n,float input[17], float w[7][18],int x, int y,float fnet[7]){
    int i,j;
    float hidden[n];
    for(i=0;i<x;i++){
        hidden[i]=0.0;
        for(j=0;j<y;j++){
            hidden[i] = hidden[i]+ (input[j]*w[i][j]);
           }
           hidden[i] =  -1* hidden[i];
           float z  = 1+exp(hidden[i]);
           act_fun1[i] =1/z;
    fnet[i]=act_fun1[i]*(1-act_fun1[i]);
   }
}
void get_act2(float act_fun2[10],int n,float input[7], float w[11][7],int x, int y,float fnet[10]){
    int i,j;
    float hidden[n];
    for(i=0;i<x;i++){
        hidden[i]=0.0;
        for(j=0;j<y;j++){
            hidden[i] = hidden[i]+ (input[j]*w[i][j]);
           }
           hidden[i] =  -1* hidden[i];
           float z  = 1+exp(hidden[i]);
           act_fun2[i] =1/z;
        fnet[i]=act_fun2[i]*(1-act_fun2[i]);
   }
}
float multi_layer(int original_class,float act_fun2[7],float act_fun1[10],float w[7][18],float w2[11][7],float fnet[10],float input[17],float fnet1[7],float j_w[10],float delta[10],float delta1[7]){
    int j,k;
    float dw;
    // Back propagation between hidden and output..
    for(k=0;k<10;k++){
        for(j=0;j<7;j++){
          dw=leeta*act_fun2[j]*fnet[k]*j_w[k]*(-1);
      w2[k][j]+=dw;
    }
   
    }
    int i;
    // Back propagation between hidden and input..
    for(i=0;i<7;i++){
    dw=0.0;
    for(j=0;j<10;j++){
        dw= dw + delta[j]* w2[j][i] * fnet1[i];
    }
    delta1[i] = dw;
    }

    for(k=0;k<7;k++){
        for(j=0;j<17;j++){
          dw=leeta*input[j]*delta1[k];
      w[k][j]+=dw;
    }
    //printf("\n");
    }
}

int extractmaxindex(float final[10]){
    float maxi=final[0];
    int ind=0,i;
    for(i=1;i<10;i++){
        if(final[i]>=maxi){
        maxi=final[i];
        ind=i;
    }
    }
return ind+1;
}

void func1(){
	//Training...
    int i,j,x=1,flag=0;
    float input[17];
    float w[7][18],r,act_fun1[7],w2[11][7],act_fun2[10],fnet_1[7],fnet_2[10],delta[10],delta1[7];
    FILE *fp;
    input[0]=1.0;
    generate_rand(7,17,w);
    generate_rand2(10,7,w2);
   
    fp = fopen("test.txt", "r");
    float eps=0.01,jw1=10.0,jw2=0.0;
    while(fscanf(fp, "%d", &original_class)>=1){
    
        for(i=0;i<17;i++){
        fscanf(fp, "%f", &input[i+1]);
             
        }
    while(1){
        
        get_act(act_fun1,7,input,w,7,17,fnet_1);
        get_act2(act_fun2,10,act_fun1,w2,10,7,fnet_2);
	int i,j,t_mat[11],k;
        float j_w[10];
        float sum=0.0;
        for(i=0;i<10;i++){
        t_mat[i]=0;
        }
       
        t_mat[original_class-1] = 1;
        for(i=0;i<10;i++){
        float temp = (float)t_mat[i];
        sum=sum+(pow((temp-act_fun2[i]),2));
        j_w[i]=(act_fun2[i]-temp);
           }
        jw2 = sum/2.0;
        
        for(int a=0;a<10;a++){
        delta[a] = -1* (j_w[a]) * (fnet_2[a]);
        }   
        multi_layer(original_class,act_fun2,act_fun1,w,w2,fnet_2,input,fnet_1,j_w,delta,delta1);
	  if(abs(jw1-jw2)<eps)
		break;
	jw1=jw2;
    }
    
    }
   //Testing...
    fclose(fp);
    int original_class2;
    float minput[17];
    FILE *fp1;
    fp1=fopen("test.txt","r");
    float second[7],final[10];
    
    int testclass[10000],testclass1[10000],k1=0,k2=0;
        while(fscanf(fp1, "%d", &original_class2)>=1){
        testclass[k1++]=original_class2;
        minput[0]=1;
        for(i=0;i<17;i++){
        fscanf(fp1, "%f", &minput[i+1]);     
        }
        get_act(second,7,minput,w,7,17,fnet_1);
        get_act2(final,10,second,w2,10,7,fnet_2);
            int ans=extractmaxindex(final);
        testclass1[k2++]=ans;
    }
    int  cnt=0;
    for(i=0;i<k2;i++){
        if(testclass[i]==testclass1[i])
            {
            //printf("%d %d",testclass[i],testclass1[i]);
            cnt++;
            }   
    }
   
	float accuracy=((float)cnt*100.0)/k2;
    printf("COUNT OF MATCHING CLASSES:- %d\n",cnt);
    printf("ACCURACY IS PERCENTAGE:- %f \n",accuracy);
}

void func2(){
	//Training...
    int i,j,x=1;
    float input[17];
    float w[7][18],r,act_fun1[7],w2[11][7],act_fun2[10],fnet_1[7],fnet_2[10],delta[10],delta1[7];
    FILE *fp;
    input[0]=1.0;
    generate_rand(7,17,w);
    generate_rand2(10,7,w2);
   
    fp = fopen("test.txt", "r");
    int epoch=100;
    while(fscanf(fp, "%d", &original_class)>=1){
    
        for(i=0;i<17;i++){
        fscanf(fp, "%f", &input[i+1]);
             
        }
    while(epoch!=0){
        epoch--;
        get_act(act_fun1,7,input,w,7,17,fnet_1);
        get_act2(act_fun2,10,act_fun1,w2,10,7,fnet_2);
		int i,j,t_mat[11],jw=0,k;
        float j_w[10];
        float sum=0.0;
        for(i=0;i<10;i++){
        t_mat[i]=0;
        }
       
        t_mat[original_class-1] = 1;
        for(i=0;i<10;i++){
        float temp = (float)t_mat[i];
        sum=sum+(pow((temp-act_fun2[i]),2));
        j_w[i]=(act_fun2[i]-temp);
           }
        jw = sum/2.0;
       
        for(int a=0;a<10;a++){
        delta[a] = -1* (j_w[a]) * (fnet_2[a]);
        }   
        multi_layer(original_class,act_fun2,act_fun1,w,w2,fnet_2,input,fnet_1,j_w,delta,delta1);   
    }
    epoch =100;
    x++;
    }
   //Testing...
    fclose(fp);
    int original_class2;
    float minput[17];
    FILE *fp1;
    fp1=fopen("test.txt","r");
    float second[7],final[10];
    
    int testclass[10000],testclass1[10000],k1=0,k2=0;
        while(fscanf(fp1, "%d", &original_class2)>=1){
        testclass[k1++]=original_class2;
        minput[0]=1;
        for(i=0;i<17;i++){
        fscanf(fp1, "%f", &minput[i+1]);     
        }
        get_act(second,7,minput,w,7,17,fnet_1);
        get_act2(final,10,second,w2,10,7,fnet_2);
            int ans=extractmaxindex(final);
        testclass1[k2++]=ans;
    }
    int  cnt=0;
    for(i=0;i<k2;i++){
        if(testclass[i]==testclass1[i])
            {
            //printf("%d %d",testclass[i],testclass1[i]);
            cnt++;
            }   
    }
    float accuracy=((float)cnt*100.0)/k2;
    printf("COUNT OF MATCHING CLASSES:- %d\n",cnt);
    printf("ACCURACY IS PERCENTAGE:-%f\n",accuracy);
}

void func3(){
	//Training...
    int i,j,x=1;
    float input[17];
    float w[7][18],r,act_fun1[7],w2[11][7],act_fun2[10],fnet_1[7],fnet_2[10],delta[10],delta1[7];
    FILE *fp;
    input[0]=1.0;
    generate_rand(7,17,w);
    generate_rand2(10,7,w2);
    float eps=0.01,jw1=10.0,jw2=0.0;
    fp = fopen("test.txt", "r");
    int epoch=100;
    while(fscanf(fp, "%d", &original_class)>=1){
    
        for(i=0;i<17;i++){
        fscanf(fp, "%f", &input[i+1]);
             
        }
    while(1){
        epoch--;
        get_act(act_fun1,7,input,w,7,17,fnet_1);
        get_act2(act_fun2,10,act_fun1,w2,10,7,fnet_2);
		int i,j,t_mat[11],jw=0,k;
        float j_w[10];
        float sum=0.0;
        for(i=0;i<10;i++){
        t_mat[i]=0;
        }
       
        t_mat[original_class-1] = 1;
        for(i=0;i<10;i++){
        float temp = (float)t_mat[i];
        sum=sum+(pow((temp-act_fun2[i]),2));
        j_w[i]=(act_fun2[i]-temp);
           }
        jw2 = sum/2.0;
       
        for(int a=0;a<10;a++){
        delta[a] = -1* (1.0/act_fun2[a]) * (fnet_2[a]);
        }   
        multi_layer(original_class,act_fun2,act_fun1,w,w2,fnet_2,input,fnet_1,j_w,delta,delta1);  
	if(abs(jw1-jw2)<eps)
		break;
	jw1=jw2; 
    }
   
    }
   //Testing...
    fclose(fp);
    int original_class2;
    float minput[17];
    FILE *fp1;
    fp1=fopen("test.txt","r");
    float second[7],final[10];
    
    int testclass[10000],testclass1[10000],k1=0,k2=0;
        while(fscanf(fp1, "%d", &original_class2)>=1){
        testclass[k1++]=original_class2;
        minput[0]=1;
        for(i=0;i<17;i++){
        fscanf(fp1, "%f", &minput[i+1]);     
        }
        get_act(second,7,minput,w,7,17,fnet_1);
        get_act2(final,10,second,w2,10,7,fnet_2);
            int ans=extractmaxindex(final);
        testclass1[k2++]=ans;
    }
    int  cnt=0;
    for(i=0;i<k2;i++){
        if(testclass[i]==testclass1[i])
            {
            //printf("%d %d",testclass[i],testclass1[i]);
            cnt++;
            }   
    }
    float accuracy=((float)cnt*100.0)/k2;
    printf("COUNT OF MATCHING CLASSES:- %d\n",cnt);
    printf("ACCURACY IS PERCENTAGE:-%f\n",accuracy);
}

void func4(){
		//Training...
    int i,j,x=1;
    float input[17];
    float w[7][18],r,act_fun1[7],w2[11][7],act_fun2[10],fnet_1[7],fnet_2[10],delta[10],delta1[7];
    FILE *fp;
    input[0]=1.0;
    generate_rand(7,17,w);
    generate_rand2(10,7,w2);
   
    fp = fopen("test.txt", "r");
    int epoch=100;
    while(fscanf(fp, "%d", &original_class)>=1){
    
        for(i=0;i<17;i++){
        fscanf(fp, "%f", &input[i+1]);
             
        }
    while(epoch!=0){
        epoch--;
        get_act(act_fun1,7,input,w,7,17,fnet_1);
        get_act2(act_fun2,10,act_fun1,w2,10,7,fnet_2);
		int i,j,t_mat[11],jw=0,k;
        float j_w[10];
        float sum=0.0;
        for(i=0;i<10;i++){
        t_mat[i]=0;
        }
       
        t_mat[original_class-1] = 1;
        for(i=0;i<10;i++){
        float temp = (float)t_mat[i];
        sum=sum+(pow((temp-act_fun2[i]),2));
        j_w[i]=(act_fun2[i]-temp);
           }
        jw = sum/2.0;
       
        for(int a=0;a<10;a++){
        delta[a] = -1* (1.0/act_fun2[a]) * (fnet_2[a]);
        }   
        multi_layer(original_class,act_fun2,act_fun1,w,w2,fnet_2,input,fnet_1,j_w,delta,delta1);   
    }
    epoch =100;
    x++;
    }
   //Testing...
    fclose(fp);
    int original_class2;
    float minput[17];
    FILE *fp1;
    fp1=fopen("test.txt","r");
    float second[7],final[10];
    
    int testclass[10000],testclass1[10000],k1=0,k2=0;
        while(fscanf(fp1, "%d", &original_class2)>=1){
        testclass[k1++]=original_class2;
        minput[0]=1;
        for(i=0;i<17;i++){
        fscanf(fp1, "%f", &minput[i+1]);     
        }
        get_act(second,7,minput,w,7,17,fnet_1);
        get_act2(final,10,second,w2,10,7,fnet_2);
            int ans=extractmaxindex(final);
        testclass1[k2++]=ans;
    }
    int  cnt=0;
    for(i=0;i<k2;i++){
        if(testclass[i]==testclass1[i])
            {
            //printf("%d %d",testclass[i],testclass1[i]);
            cnt++;
            }   
    }
    float accuracy=((float)cnt*100.0)/k2;
    printf("COUNT OF MATCHING CLASSES:- %d\n",cnt);
    printf("ACCURACY IS PERCENTAGE:-%f\n",accuracy);
}
                                               
int main()
{	
	int opt;
	printf("\n CHOOSE AN OPTION BETWEEN 1 AND 4\n");
	printf("\n OPTION 1:- Sum of Squared Deviation loss and ||ΔW|| < ε. where ||ΔW|| is   the Euclidian norm of vector ΔW and considering ε  as 0.01.  \n");
	printf("\n OPTION 2:- Sum of Squared Deviation loss and  number of epochs as 100 \n");
	printf("\n OPTION 3:- Cross-entropy loss and ||ΔW|| < ε. where ||ΔW|| is   the Euclidian norm of vector ΔW and considering ε  as 0.01.  \n");
	printf("\n OPTION 4:- Cross-entropy loss and  number of epochs as 100  \n");
        scanf("%d",&opt);
	switch(opt){
	case 1:
	func1();
	break;
	case 2:
	func2();
	break;
	case 3:
	func3();
	break;
	case 4:
	func4();
	break;
	}

   
   return 0;
}
