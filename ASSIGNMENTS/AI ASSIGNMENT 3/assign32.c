/*AI ASSIGNMENT 3
GROUP MEMBERS:
ANIRUDH KANNAN V P 201601004
SAIRATHAN V 201601104
*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>//Header files
float train[10][192][5];// Training Vector WHICH IS A 3D VECTOR FOR 10 CLASSES, 192 FEATURES 5 DIFFERENT VALUES
int features=192,instances=6670,testinp=3333; // THERE ARE 192 FEATURES 6670 INSTANCES IN TRANING DATA FILE.
// THERE ARE 3333 INSTANCES IN TEST INPUT

//INITIALISING ALL THE VALUES OF THE TRAINING VECTOR TO ZERO BEFORE FINDING THE NO OF OCCURANCES
void initialise(){
	int i,j,k;
	for(i=0;i<10;i++){
		for(j=0;j<192;j++){
			for(k=0;k<5;k++){
				train[i][j][k]=0;//ALL VALUES INITIALISED TO ZER0
			}
		}
	}
}



//FUNCTION TO SCAN FROM FILE AND INCREASE VALUE FOR INSTANCES
void scanfile(){
    FILE * f = fopen("pp_tra.dat","r");
    int i,j,k,tempdataclass,temp[192];
    for(i=0;i<instances;i++){
        for(j=0;j<features;j++){
            fscanf(f," %d",&temp[j]);//SCANNING THE FEATURES AND STORING IN A TEMPORARY ARRAY
        }

        fscanf(f," %d",&tempdataclass);//CLASS VALUE WHICH IS READ EACH TIME

        for(j=0;j<features;j++){
            train[tempdataclass][j][temp[j]]+=(float)(1.0);//ADDING 1 TO THE CORRESPONDING VALUE SCANNED FROM FILE FOR FEATURES AND THAT APPROPRIATE CLASS STORED IN ARRAY
        }
    }
    fclose(f);
    for(i=0;i<10;i++){
        for(j=0;j<192;j++){
            for(k=0;k<5;k++){
                train[i][j][k]/=(float)667.0; // TOTAL 6670/10=667. DOING (float) TO TYPE CAST IT TO FLOAT
            }
        }
    }
    return;
}

//FUNCTION TO RETURN THE MAXIMUM INDEX TO IDENTIFY WHICH CLASS IT IS.
int getmax(float arr[10]){
	int i,ans=0;//
	float maximum=arr[0];
	for(i=1;i<10;i++){
		if(maximum<=arr[i]){//CHANGING THE MAXIMUM VALUE AND CORRESPONDING INDEX
			maximum=arr[i];
			ans=i;
		}
		//HERE MAXIMUM CONTAINS WHICH IS THE MAXIMUM VALUE AND ANS CONTAINS THE INDEX OF THE MAXIMUM VALUE.
	}
	return ans;
}
void test(){
	int correct=0,test1,c,temp[192],tempdataclass,i,j;
	FILE *f2=fopen("pp_tes.dat","r");
	for(test1=0;test1<testinp;test1++){
        float tempcls[10];
        for(i=0;i<10;i++)tempcls[i]=0;
        for(j=0;j<features;j++){
            fscanf(f2," %d",&temp[j]);// HERE SCANNING THE 192 FEATURES AND STORING IN A TEMPORARY ARRAY TO TEST
        }
        fscanf(f2," %d",&tempdataclass);// SCANNING THE CLASS
        for(c=0;c<10;c++){
            for(j=0;j<features;j++){
                tempcls[c]+=log(train[c][j][temp[j]]);
            }
        }
        int tempans=getmax(tempcls);
        if(tempans==tempdataclass)
            correct+=1;// IF CONDITION TO CHECK IF IT IS CORRECTLY CLASSSIFIED OR NOT
	}//THE CORRECT VARIABLE CONTAINS THE NO OF CORRECTLY CLASSIFIED EXAMPLES
	printf("Total examples = %d\nCorrectly classified Examples = %d\nClassification Accuracy = %f%%\n",3333,correct,((100.0*(correct))/3333.0));
	fclose(f2);//CLOSING THE FILE
    return;
}
int main(){
	initialise(); //CALLING THE INITIALISE FUNCTION
	scanfile(); // CALLING THE SCAN FUNCTION AND TRAINING IT AT THE SAME TIME
	test(); // CALLING THE FUNCTION TO TEST THE GIVEN FILE AND FINDING THE NUMBER OF CORRECTLY CLASSIFIED EXAMPLES AND FINDING THE ACCURACY
    return 0;
}
