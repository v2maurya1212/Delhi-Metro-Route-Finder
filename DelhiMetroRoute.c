/*Improved version*/
/*Solved*/
#include<stdio.h>          
#include<strings.h>
#include<stdlib.h>            
#define Yellow 1001
#define Blue 1002
#define Red 1003
#define Green 1004
#define Violet 1005
#define MAX 200
#define MAXMATCH 15
#define infinity 9999
#define NIL -1                    
#define TEMP 0
#define PERM 1
int checkJunc;
int adj[MAX][MAX];
int predecessor[MAX];
int pathLength[MAX];
int status[MAX];
int Match3[MAXMATCH];
int top=-1;
void push3(int data);
int pop3();
int station(char Name[30]); //Getting designated number of the source/destination names
int stationNotFound(char Name[30]); //If no exact match found then first three characters are used to search stations
void leftSame(int destColor);
void rightSame(int destColor);
void createGraph();
void dijkstra(int sourceNumber);
int min_temp();
void findPath(int sourceNumber,int destNumber,int sourceColor);
int joLeRi(int a,int t);
void numToName(int t);
void headingWhere(int vb);
void headingWhere2(int vb);
int colorDecider(int Number);


void main()
{
int sourceColor,destColor,sourceNumber,destNumber,item=-10,manualcheck;
char sourceName[30];
char destName[30];
int manualNumber;
/*source station part begins here*/
printf("\nEnter the Source Station Name\n");
gets(sourceName);
sourceNumber = station(sourceName);
if(sourceNumber == -50)
{
manualNumber = stationNotFound(sourceName);
if(manualNumber==-51)
{
printf("\nNo Stations Found!\n");
exit(1);
}
else
{
printf("\n\nIf Your station is listed above, please enter the Search key,Type any other key follwed by ENTER to exit\n");
scanf("%d",&manualNumber);
while(top!=-1)
{
item=pop3();   // Stack is used to avoid any wrong inputs
if(manualNumber==item)
{
sourceNumber=manualNumber;
top=-1;   
manualcheck=-1;
break;
}
}
if(manualcheck!=-1)
{
printf("\nProgram Terminated\n");
exit(1);
}
}
}
//Source Line decider
sourceColor = colorDecider(sourceNumber);
/*Source part ends here*/


/*Destination part begins from here*/
printf("\nEnter the Destination Station Name\n");
scanf(" %30[^\n]%*c",destName); //I used it instead of gets() to avoid problems caused by gets().
destNumber = station(destName);
if(destNumber == -50)
{
manualNumber = stationNotFound(destName);
if(manualNumber==-51)
{
printf("\nNo Stations Found!\n");
exit(1);
}
else
{
printf("\n\nIf Your station is listed above, please enter the Search key,Type any other key follwed by Enter to exit\n");
scanf("%d",&manualNumber);

while(top!=-1)
{
item=pop3();
if(manualNumber==item)
{
destNumber=manualNumber;
top=-1;
manualcheck=-2;
break;
}
}
if(manualcheck!=-2)
{
printf("\nProgram Terminated\n");
exit(1);
}
}
}



if(destNumber==sourceNumber)
{
printf("\nSource and Destination Stations are the same\n");
exit(1);
}

//Destination line decider
destColor = colorDecider(destNumber);
/*Destination part ends here*/


/*There are some conflicts in junctions, This part solves that*/
if(sourceNumber == 21 && destColor !=Yellow)//Junction conflict Yellow/blue line
{
sourceNumber = 66;
sourceColor = Blue;
}
if(destNumber == 21 && sourceColor !=Yellow)//Junction conflict Yellow/blue line
{
destNumber = 66;
destColor = Blue;
}
if(sourceNumber == 25 && destColor !=Yellow)//Junction conflict Yellow/Red line
{
sourceNumber = 104;
sourceColor = Red;
}
if(destNumber == 25 && sourceColor !=Yellow)//Junction conflict Yellow/Red line
{
destNumber = 104;
destColor = Red;
}
if(sourceNumber == 99 && destColor ==Green)//Junction conflict Green/Red line
{
sourceNumber = 126;
sourceColor = Green;
}
if(destNumber == 99 && sourceColor ==Green)//Junction conflict Yellow/blue line
{
destNumber = 126;
destColor = Green;
}
if(sourceNumber == 59 && destColor ==Green)//Junction conflict Green/Red line
{
sourceNumber = 128;
sourceColor = Green;
}
if(destNumber == 59 && sourceColor ==Green)//Junction conflict Yellow/blue line
{
destNumber = 128;
destColor = Green;
}
if(sourceNumber == 68 && destColor ==Violet)//Junction conflict Violet/blue line
{
sourceNumber = 131;
sourceColor = Violet;
}
if(destNumber == 68 && sourceColor ==Violet)//Junction conflict Violet/blue line
{
destNumber = 131;
sourceColor = Violet;
}
if(destNumber == 19 && sourceColor ==Blue)//Junction conflict Yellow/Violet line
{
destNumber = 133;
destColor = Violet;
}
if(sourceNumber == 19 && destColor ==Violet)//Junction conflict Yellow/Violet line
{
sourceNumber = 133;
sourceColor = Violet;
}
if(sourceNumber == 68 && destColor ==Yellow)//Junction conflict Violet/blue line
{
if(destNumber<=20)
{
sourceNumber = 131;
sourceColor = Violet;
}
}
if(sourceNumber == 19 && destColor ==Blue)//Junction conflict Violet/blue line
{
if(destNumber >=67 && destNumber<90)
{
sourceNumber = 133;
sourceColor = Violet;
}
}
/*Junction conflicts end here*/

createGraph();
dijkstra(sourceNumber);
findPath(sourceNumber,destNumber,sourceColor);
}

void createGraph()//This function connects stations according to Delhi Metro routes
{
int i;
adj[0][1]=4;
adj[1][0]=4;
adj[1][2]=4;
adj[2][1]=4;
adj[2][3]=4;
adj[3][2]=4;
adj[3][4]=4;
adj[4][3]=4;
adj[4][5]=4;
adj[5][4]=4;
adj[5][6]=4;
adj[6][5]=4;
adj[6][7]=4;
adj[7][6]=4;
adj[7][8]=4;
adj[8][7]=4;
adj[8][9]=4;
adj[9][8]=4;
adj[9][10]=4;
adj[10][9]=4;
adj[10][11]=4;
adj[11][10]=4;
adj[11][12]=4;
adj[12][11]=4;
adj[12][13]=4;
adj[13][12]=4;
adj[13][14]=4;
adj[14][13]=4;
adj[14][15]=4;
adj[15][14]=4;
adj[15][16]=4;
adj[16][15]=4;
adj[16][17]=4;
adj[17][16]=4;
adj[17][18]=4;
adj[18][17]=4;
adj[18][19]=4;
adj[19][18]=4;
adj[19][20]=4;
adj[19][133]=5;        //Yellow to Violet
adj[20][19]=4;
adj[20][21]=4;
adj[21][66]=5;           //Yellow to Blue
adj[21][20]=4;
adj[21][22]=4;
adj[22][21]=4;
adj[22][23]=4;
adj[23][22]=4;
adj[23][24]=4;
adj[24][23]=4;
adj[24][25]=4;
adj[25][24]=4;
adj[25][26]=4;
adj[25][104]=5;        //Yellow to red
adj[26][25]=4;
adj[26][27]=4;
adj[27][26]=4;
adj[27][28]=4;
adj[28][27]=4;
adj[28][29]=4;
adj[29][28]=4;
adj[29][30]=4;
adj[30][29]=4;
adj[30][31]=4;
adj[31][30]=4;
adj[31][32]=4;
adj[32][31]=4;
adj[32][33]=4;
adj[33][32]=4;
adj[33][34]=4;
adj[34][33]=4;
adj[34][35]=4;
adj[35][34]=4;
adj[35][36]=4;
adj[36][35]=4;
//adj[37][36]=4; //End of Yellow line

adj[38][39]=4;
adj[39][38]=4;
adj[39][40]=4;
adj[40][39]=4;
adj[40][41]=4;
adj[41][40]=4;
adj[41][42]=4;
adj[42][41]=4;
adj[42][43]=4;
adj[43][42]=4;
adj[43][44]=4;
adj[44][43]=4;
adj[44][45]=4;
adj[45][44]=4;
adj[45][46]=4;
adj[46][45]=4;
adj[46][47]=4;
adj[47][46]=4;
adj[47][48]=4;
adj[48][47]=4;
adj[48][49]=4;
adj[49][48]=4;
adj[49][50]=4;
adj[50][49]=4;
adj[50][51]=4;
adj[51][50]=4;
adj[51][52]=4;
adj[52][51]=4;
adj[52][53]=4;
adj[53][52]=4;
adj[53][54]=4;
adj[54][53]=4;
adj[54][55]=4;
adj[55][54]=4;
adj[55][56]=4;
adj[56][55]=4;
adj[56][57]=4;
adj[57][56]=4;
adj[57][58]=4;
adj[58][57]=4;
adj[58][59]=4;
adj[59][58]=4;
adj[59][60]=4;
adj[59][128]=5; //Blue to Green
adj[60][59]=4;
adj[60][61]=4;
adj[61][60]=4;
adj[61][62]=4;
adj[62][61]=4;
adj[62][63]=4;
adj[63][62]=4;
adj[63][64]=4;
adj[64][63]=4;
adj[64][65]=4;
adj[65][64]=4;
adj[65][66]=4;
adj[66][65]=4;
adj[66][67]=4;
adj[66][21]=5;        //Blue to Yellow
adj[67][66]=4;
adj[67][68]=4;
adj[68][67]=4;
adj[68][69]=4;
adj[68][131]=5;        //Blue to violet
adj[69][68]=4;
adj[69][70]=4;
adj[70][69]=4;
adj[70][71]=4;
adj[71][70]=4;    //Yamuna Bank
adj[71][73]=4;    //Towards Noida
adj[71][83]=4;    //Towards Vaishali
adj[73][71]=4;    //Akshardham to Yamuna Bank
adj[73][74]=4;
adj[74][73]=4;
adj[74][75]=4;
adj[75][74]=4;
adj[75][76]=4;
adj[76][75]=4;
adj[76][77]=4;
adj[77][76]=4;
adj[77][78]=4;
adj[78][77]=4;
adj[78][79]=4;
adj[79][78]=4;
adj[79][80]=4;
adj[80][79]=4;
adj[80][81]=4;
adj[81][80]=4;
adj[81][82]=4;
adj[82][81]=4;  //City Center
adj[83][71]=4;  //Laxmi Nagar to Yamuna Bank
adj[83][84]=4;
adj[84][83]=4;
adj[84][85]=4;
adj[85][84]=4;
adj[85][86]=4;
adj[86][85]=4;
adj[86][87]=4;
adj[87][86]=4;
adj[87][88]=4;
adj[88][87]=4;
adj[88][89]=4;
adj[89][88]=4;  //Vaishali


adj[91][92]=4;  //Rithala
adj[92][91]=4;
adj[92][93]=4;
adj[93][92]=4;
adj[93][94]=4;
adj[94][93]=4;
adj[94][95]=4;
adj[95][94]=4;
adj[95][96]=4;
adj[96][95]=4;
adj[96][97]=4;
adj[97][96]=4;
adj[97][98]=4;
adj[98][97]=4;
adj[98][99]=4;
adj[99][98]=4;
adj[99][100]=4;
adj[99][126]=5; //Red to Green
adj[100][99]=4;
adj[100][101]=4;
adj[101][100]=4;
adj[101][102]=4;
adj[102][101]=4;
adj[102][103]=4;
adj[103][102]=4;
adj[103][104]=4;
adj[104][103]=4;
adj[104][105]=4;
adj[104][25]=5;  //Red to Yellow
adj[105][104]=4;
adj[105][106]=4;
adj[106][105]=4;
adj[106][107]=4;
adj[107][106]=4;
adj[107][108]=4;
adj[108][107]=4;
adj[108][109]=4;
adj[109][108]=4;
adj[109][110]=4;
adj[110][109]=4;
adj[110][111]=4;
adj[111][110]=4; //Dilshad Garden

adj[113][114]=4; //Green line
adj[114][113]=4;
adj[114][115]=4;
adj[115][114]=4;
adj[115][116]=4;
adj[116][115]=4;
adj[116][117]=4;
adj[117][116]=4;
adj[117][118]=4;
adj[118][117]=4;
adj[118][119]=4;
adj[119][118]=4;
adj[119][120]=4;
adj[120][119]=4;
adj[120][121]=4;
adj[121][120]=4;
adj[121][122]=4;
adj[122][121]=4;
adj[122][123]=4;
adj[123][122]=4;
adj[123][124]=4;
adj[124][123]=4;
adj[124][125]=4;
adj[125][124]=4;
adj[125][126]=4;
adj[126][125]=4;
adj[126][99]=5; //green line to red line
adj[125][127]=4;
adj[127][125]=4;
adj[127][128]=4;
adj[128][127]=4; //End of Green line
adj[128][59]=4;

adj[130][131]=4;
adj[131][130]=4;
adj[131][132]=4;
adj[131][68]=5;  //Violet to blue line
adj[132][131]=4;
adj[132][133]=4;
adj[133][132]=4;
adj[133][134]=4;
adj[133][19]=5;    //Violet to Yellow
adj[134][133]=4;
adj[134][135]=4;
adj[135][134]=4;
adj[135][136]=4;
adj[136][135]=4;
adj[136][137]=4;
adj[137][136]=4;
adj[137][138]=4;
adj[138][137]=4;
adj[138][139]=4;
adj[139][138]=4;
adj[139][140]=4;
adj[140][139]=4;
adj[140][141]=4;
adj[141][140]=4;
adj[141][142]=4;
adj[142][141]=4;
adj[142][143]=4;
adj[143][142]=4;
adj[143][144]=4;
adj[144][143]=4;
adj[144][145]=4;
adj[145][144]=4;
adj[145][146]=4;
adj[146][145]=4;
adj[146][147]=4;
adj[147][146]=4;
adj[147][148]=4;
adj[148][147]=4;
adj[148][149]=4;
adj[149][148]=4;
adj[149][150]=4;
adj[150][149]=4;
adj[150][151]=4;
adj[151][150]=4;
adj[151][152]=4;
adj[152][151]=4;
adj[152][153]=4;
adj[153][152]=4;
adj[153][154]=4;
adj[154][153]=4;
adj[154][155]=4;
adj[155][154]=4;
adj[155][156]=4;
adj[156][155]=4;
adj[156][157]=4;
adj[157][156]=4;


}

void dijkstra(int sourceNumber)
{
int i,n=200,current;
	
	for(i=0; i<n; i++)
	{
		predecessor[i] =  NIL;   
		pathLength[i] = infinity;
		status[i] = TEMP;
	}
	pathLength[sourceNumber] = 0;
		
	while(1)
	{
		current = min_temp( );
	
		if( current == NIL )
			return;
		
		status[current] = PERM;

		for(i=0; i<n; i++)
		{
			
			if ( adj[current][i] !=0 && status[i] == TEMP )
				if( pathLength[current] + adj[current][i] < pathLength[i] )
				{	
					predecessor[i] = current;
					pathLength[i] = pathLength[current] + adj[current][i];    
				}
		}
	}
}/*End of Dijkstra( )*/


int min_temp( )
{
	int i;
        int n=200;
	int min = infinity;
	int k = NIL;  
	for(i=0;i<n;i++)
	{
		if(status[i] == TEMP && pathLength[i] < min)
		{
			min = pathLength[i];
			k = i;
		}
	}
	return k;
}/*End of min_temp( )*/


void findPath(int sourceNumber, int destNumber,int sourceColor )
{
	int i,u,j,a,joe,t=-11;
	int path[MAX];		
	int shortdist = 0;	
	int count = 0;		
        int path2[MAX];
        int firststation;
        int Nextstation;
        int vb;
	
	/*Store the full path in the array path*/
	while( destNumber != sourceNumber )
	{
		count++;
		path[count] = destNumber;
		u = predecessor[destNumber];
                shortdist = count;
		destNumber = u;	
	}
	count++;
        shortdist++;
	path[count]=sourceNumber;
        for(i=count,j=1;i>=1,j<=count;i--,j++)
        path2[j]=path[i];
        firststation = path2[1];
        Nextstation = path2[2];
        if((firststation - Nextstation)==1)
         {
          printf("\nBoard on a metro heading towards ");
          leftSame(sourceColor);
         }
        else if((firststation - Nextstation)==-1)
         {
          printf("\nBoard on a metro heading towards ");
          rightSame(sourceColor);
         }
	for(i=1; i<=count; i++)	
               {
                a=t;
                t = path2[i];
                
                joe=joLeRi(a,t);
                if(joe==1)
                {
                shortdist=shortdist-1;
                vb=path2[i+1];
                headingWhere(vb);
                joe=0;
                }
                if(joe==2)
                {
                shortdist=shortdist-1;
                vb=path2[i+1];
                headingWhere2(vb);
                joe=0;
                }
                numToName(t);              
               }
       
        printf("Deboard here(This is your Destination)\n");
	printf("\nNumber of stations are : %d\n",shortdist);
}/*End of findPath()*/ 

/*This function tells us where to change Metro*/
int joLeRi(int a,int t)
{
if(a==21 && t==66)
{
printf("\nChange here for Blue Line\n");
return 1;
}
else if(a==66 && t==21)
{
printf("\nChange here for Yellow Line\n");
return 1;
}
else if(a==71 && t==73)
{
printf("\nBoard on a metro heading towards Noida city Center (ignore if you are already sitting)");
return 0;
}
else if(a==71 && t==83)
{
printf("\nBoard on a metro heading towards Vaishali (ignore if you are already sitting)");
return 0;
}
else if(a==59 && t==128)
{
printf("\nChange here for Green Line\n");
return 0;
}
else if(a==128 && t==59)
{
printf("\nChange here for Blue Line\n");
return 1;
}

else if(a==73 && t==71)
{
return 0;
}
else if(a==83 && t==71)
{
return 0;
}
else if(a==25 && t==104)
{
printf("\nChange here for Red Line\n");
return 1;
}
else if(a==104 && t==25)
{
printf("\nChange here for Yellow Line\n");
return 1;
}
else if(a==99 && t==126)
{
printf("\nChange here for Green Line (One Way)\n");
return 0;
}
else if(a==126 && t==99)
{
printf("\nChange here for Red Line\n");
return 1;
}
else if(a==68 && t==131)
{
printf("\nChange here for Violet Line\n");
return 2;
}
else if(a==131 && t==68)
{
printf("\nChange here for Blue Line\n");
return 2;
}
else if(a==19 && t==133)
{
printf("\nChange here for Violet Line\n");
return 1;
}
else if(a==133 && t==19)
{
printf("\nChange here for Yellow Line\n");
return 2;
}
else if(a==19 && t==134)
{
printf("\nChange here for Violet Line\n");
return 2;
}

else 
return 0;
}
/*End of joLeRi*/

/*This function tells us which metro to get on*/
void headingWhere(int vb)
{
if(vb==65)
printf("\nBoard on a metro heading towards Dwarka Sector 21\n");
else if(vb==67)
printf("\nBoard on a metro heading towards Noida City Center/Vaishali\n");
else if(vb==20)
printf("\nBoard on a metro heading towards Huda City Center\n");
else if(vb==22)
printf("\nBoard on a metro heading towards Samaypur Badli\n");
else if(vb==83)
printf("\nBoard on a metro heading towards Vaishali\n");
else if(vb==71)
printf("\nBoard on a metro heading towards Vaishali\n");
else if(vb==103)
printf("\nBoard on a metro heading towards Rithala\n");
else if(vb==105)
printf("\nBoard on a metro heading towards Dilshad Garden\n");
else if(vb==98)
printf("\nBoard on a metro heading towards Rithala\n");
else if(vb==100)
printf("\nBoard on a metro heading towards Dilshad Garden\n");
else if(vb==24)
printf("\nBoard on a metro heading towards Huda City Center\n");
else if(vb==26)
printf("\nBoard on a metro heading towards Samaypur Badli\n");
else if(vb==58)
printf("\nBoard on a metro heading towards Dwarka Sector 21\n");
else if(vb==60)
printf("\nBoard on a metro heading towards Noida City Center/Vaishali\n");
else if(vb==132)
printf("\nBoard on a metro heading towards ITO\n");
else if(vb==134)
printf("\nBoard on a metro heading towards Badarpur\n");
}

/*This function is similar to the function 'headingWhere' but it is separated from that function due to some exceptios*/
void headingWhere2(int vb)
{
if(vb==132)
printf("\nBoard on a metro heading towards Badarpur\n");
else if(vb==130)
printf("\nBoard on a metro heading towards ITO\n");
else if(vb==134)
printf("\nBoard on a metro heading towards Badarpur");
else if(vb==20)
printf("\nBoard on a metro heading towards Samaypur Badli");
else if(vb==20)
printf("\nBoard on a metro heading towards Samaypur Badli");
else if(vb==18)
printf("\nBoard on a metro heading towards Huda City Center");
else if(vb==67)
printf("\nBoard on a metro heading towards Dwarka Sector 21");
else if(vb==69)
printf("\nBoard on a metro heading towards Noida City Center/Vaishali");



}




/*This function tells us which metro to catch on the station i.e The metro which is heading towards station X or the one which is coming
from the station X*/
void leftSame(int destColor)
{
if(destColor==Yellow)
printf("Huda City Center");
else if(destColor==Blue)
printf("Dwarka Sect. 21");
else if(destColor==Red)
printf("Rithala");
else if(destColor==Green)
printf("Mundka");
else if(destColor==Violet)
printf("ITO");
return;
}

//Similar to leftSame
void rightSame(int destColor)
{
if(destColor==Yellow)
printf("Samaypur Badli\n");
else if(destColor==Blue)
printf("Noida City Center/Vaishali\n");
else if(destColor==Red)
printf("Dilshad Garden");
else if(destColor==Green)
printf("Inderlok/Kirti Nagar");
else if(destColor==Violet)
printf("Badarpur");
return;
}




/*Entered station name is compared with each stations in this function*/
int station(char Name[30])
{
int i;

i=strcasecmp(Name,"Huda City Center");
if(i==0)
return 0;

i=strcasecmp(Name,"Iffco Chowk");
if(i==0)
return 1;

i=strcasecmp(Name,"MG Road");
if(i==0)
return 2;

i=strcasecmp(Name,"Sikanderpur");
if(i==0)
return 3;

i=strcasecmp(Name,"Guru Dronacharya");
if(i==0)
return 4;
i=strcasecmp(Name,"Arjangarh");
if(i==0)
return 5;
i = strcasecmp(Name,"Ghitorni");
if(i ==0)
return 6;

i = strcasecmp(Name,"Sultanpur");
if(i == 0)
return 7;

i = strcasecmp(Name,"Chattarpur");
if(i == 0)
return 8;

i = strcasecmp(Name,"Qutub Minar");
if(i==0)
return 9;

i = strcasecmp(Name,"Saket");
if(i==0)
return 10;

i =strcasecmp(Name,"Malviya Nagar");
if(i==0)
return 11;

i =strcasecmp(Name,"Hauz Khas");
if(i==0)
return 12;

i = strcasecmp(Name,"Green Park");
if(i==0)
return 13;

i = strcasecmp(Name,"AIIMS");
if(i==0)
return 14;

i= strcasecmp(Name,"INA");
if(i==0)
return 15;

i = strcasecmp(Name,"Jor Bagh");
if(i==0)
return 16;

i = strcasecmp(Name,"Race Course");
if(i==0)
return 17;

i = strcasecmp(Name,"Udyog Bhawan");
if(i==0)
return 18;

i = strcasecmp(Name,"Central Secratariat");
if(i==0)
return 19;

i = strcasecmp(Name,"Patel Chowk");
if(i==0)
return 20;

i = strcasecmp(Name,"Rajiv Chowk");                //         Junction
if(i==0)
return 21;

i = strcasecmp(Name,"New Delhi");
if(i==0)
return 22;

i = strcasecmp(Name,"Chawri Bazaar");
if(i==0)
return 23;


i=strcasecmp(Name,"Chandni Chowk");
if(i==0)
return 24;
i=strcasecmp(Name,"Kashmere Gate");
if(i==0)
return 25;
i=strcasecmp(Name,"Civil Lines");
if(i==0)
return 26;
i=strcasecmp(Name,"Vidhan Sabha");
if(i==0)
return 27;
i=strcasecmp(Name,"Vishwavidyalaya");
if(i==0)
return 28;
i=strcasecmp(Name,"GTB Nagar");
if(i==0)
return 29;
i=strcasecmp(Name,"Model Town");
if(i==0)
return 30;
i=strcasecmp(Name,"Azadpur");
if(i==0)
return 31;
i=strcasecmp(Name,"Adarsh Nagar");
if(i==0)
return 32;
i=strcasecmp(Name,"Jahangirpuri");
if(i==0)
return 33;
i=strcasecmp(Name,"Haiderpur Badli Mor");
if(i==0)
return 34;
i=strcasecmp(Name,"Rohini Sector 18/19");
if(i==0)
return 35;
i=strcasecmp(Name,"Samaypur Badli");
if(i==0)
return 36;



//Blue line
i = strcasecmp(Name,"Dwarka Sect. 21");
if(i==0)
return 38;

i = strcasecmp(Name,"Dwarka Sect. 8");
if(i==0)
return 39;

i = strcasecmp(Name,"Dwarka Sect. 9");
if(i==0)
return 40;

i = strcasecmp(Name,"Dwarka Sect. 10");
if(i==0)
return 41;

i = strcasecmp(Name,"Dwarka Sect. 11");
if(i==0)
return 42;

i = strcasecmp(Name,"Dwarka Sect. 12");
if(i==0)
return 43;

i = strcasecmp(Name,"Dwarka Sect. 13");
if(i==0)
return 44;

i = strcasecmp(Name,"Dwarka Sect. 14");
if(i==0)
return 45;

i = strcasecmp(Name,"Dwarka");
if(i==0)
return 46;

i = strcasecmp(Name,"Dwarka Mor");
if(i==0)
return 47;

i = strcasecmp(Name,"Nawada");
if(i==0)
return 48;

i = strcasecmp(Name,"Uttam Nagar West");
if(i==0)
return 49;

i = strcasecmp(Name,"Uttam Nagar East");
if(i==0)
return 50;

i = strcasecmp(Name,"Janakpuri West");
if(i==0)
return 51;

i = strcasecmp(Name,"Janakpuri East");
if(i==0)
return 52;

i = strcasecmp(Name,"Tilak Nagar");
if(i==0)
return 53;

i = strcasecmp(Name,"Subhash Nagar");
if(i==0)
return 54;

i = strcasecmp(Name,"Tagore Garden");
if(i==0)
return 55;

i = strcasecmp(Name,"Rajouri Garden");
if(i==0)
return 56;

i = strcasecmp(Name,"Ramesh Nagar");
if(i==0)
return 57;

i = strcasecmp(Name,"Moti Nagar");
if(i==0)
return 58;

i = strcasecmp(Name,"Kirti Nagar");
if(i==0)
return 59;

i = strcasecmp(Name,"Shadipur");
if(i==0)
return 60;

i = strcasecmp(Name,"Patel Nagar");
if(i==0)
return 61;

i = strcasecmp(Name,"Rajendra Place");
if(i==0)
return 62;

i = strcasecmp(Name,"Karol Bagh");
if(i==0)
return 63;

i = strcasecmp(Name,"Jhandewalan");
if(i==0)
return 64;

i = strcasecmp(Name,"Ramakrishna Ashram Marg");
if(i==0)
return 65;

i = strcasecmp(Name,"Rajiv Chowk");   //            junction
if(i==0)
return 66;

i = strcasecmp(Name,"Barakhamba Road");
if(i==0)
return 67;

i = strcasecmp(Name,"Mandi House");
if(i==0)
return 68;

i = strcasecmp(Name,"Pragati Maidan");
if(i==0)
return 69;

i = strcasecmp(Name,"Indraprastha");
if(i==0)
return 70;

i = strcasecmp(Name,"Yamuna Bank");
if(i==0)
return 71;

i=strcasecmp(Name,"Akshardham");
if(i==0)
return 73;
i=strcasecmp(Name,"Mayur Vihar I");
if(i==0)
return 74;
i=strcasecmp(Name,"Mayur Vihar Ext.");
if(i==0)
return 75;
i=strcasecmp(Name,"New Ashok Nagar");
if(i==0)
return 76;
i=strcasecmp(Name,"Noida Sect. 15");
if(i==0)
return 77;
i=strcasecmp(Name,"Noida Sect. 16");
if(i==0)
return 78;
i=strcasecmp(Name,"Noida Sect. 18");
if(i==0)
return 79;
i=strcasecmp(Name,"Botanical Garden");
if(i==0)
return 80;
i=strcasecmp(Name,"Golf Course");
if(i==0)
return 81;
i=strcasecmp(Name,"Noida City Center");
if(i==0)
return 82;

i=strcasecmp(Name,"Lakshmi Nagar");
if(i==0)
return 83;
i=strcasecmp(Name,"Nirman Vihar");
if(i==0)
return 84;
i=strcasecmp(Name,"Preet Vihar");
if(i==0)
return 85;
i=strcasecmp(Name,"Karkarduma");
if(i==0)
return 86;
i=strcasecmp(Name,"Anand Vihar ISBT");
if(i==0)
return 87;
i=strcasecmp(Name,"Kaushambi");
if(i==0)
return 88;
i=strcasecmp(Name,"Vaishali");
if(i==0)
return 89;


i=strcasecmp(Name,"Rithala");
if(i==0)
return 91;
i=strcasecmp(Name,"Rohini West");
if(i==0)
return 92;
i=strcasecmp(Name,"Rohini East");
if(i==0)
return 93;
i=strcasecmp(Name,"Pitampura");
if(i==0)
return 94;
i=strcasecmp(Name,"Kohat Enclave");
if(i==0)
return 95;
i=strcasecmp(Name,"Netaji Subhash Place");
if(i==0)
return 96;
i=strcasecmp(Name,"Keshav Puram");
if(i==0)
return 97;
i=strcasecmp(Name,"Kanhaiya Nagar");
if(i==0)
return 98;
i=strcasecmp(Name,"Inderlok");
if(i==0)
return 99;
i=strcasecmp(Name,"Shastri Nagar");
if(i==0)
return 100;
i=strcasecmp(Name,"Pratap Nagar");
if(i==0)
return 101;
i=strcasecmp(Name,"Pulbangash");
if(i==0)
return 102;
i=strcasecmp(Name,"Tis Hazri");
if(i==0)
return 103;
i=strcasecmp(Name,"Kashmere Gate");
if(i==0)
return 104;
i=strcasecmp(Name,"Shastri Park");
if(i==0)
return 105;
i=strcasecmp(Name,"Seelampur");
if(i==0)
return 106;
i=strcasecmp(Name,"Welcome");
if(i==0)
return 107;
i=strcasecmp(Name,"Mansarover Park");
if(i==0)
return 108;
i=strcasecmp(Name,"Shahdra");
if(i==0)
return 109;
i=strcasecmp(Name,"Jhilmil");
if(i==0)
return 110;
i=strcasecmp(Name,"Dilshad Garden");
if(i==0)
return 111;

i=strcasecmp(Name,"Mundka");
if(i==0)
return 113;
i=strcasecmp(Name,"Rajdhani Park");
if(i==0)
return 114;
i=strcasecmp(Name,"Nangloi Railway Station");
if(i==0)
return 115;
i=strcasecmp(Name,"Nangloi");
if(i==0)
return 116;
i=strcasecmp(Name,"Surajmal Stadium");
if(i==0)
return 117;
i=strcasecmp(Name,"Udyog Nagar");
if(i==0)
return 118;
i=strcasecmp(Name,"Peeragarhi");
if(i==0)
return 119;
i=strcasecmp(Name,"Paschim Vihar West");
if(i==0)
return 120;
i=strcasecmp(Name,"Paschim Vihar East");
if(i==0)
return 121;
i=strcasecmp(Name,"Madipur");
if(i==0)
return 122;
i=strcasecmp(Name,"Shivaji Park");
if(i==0)
return 123;
i=strcasecmp(Name,"Punjabi Bagh");
if(i==0)
return 124;
i=strcasecmp(Name,"Ashok Park Main");
if(i==0)
return 125;
i=strcasecmp(Name,"Inderlok");
if(i==0)
return 126;
i=strcasecmp(Name,"Satguru Ram Singh Marg");
if(i==0)
return 127;
i=strcasecmp(Name,"Kirti Nagar");
if(i==0)
return 128;//End of Green line


i=strcasecmp(Name,"ITO");
if(i==0)
return 130;
i=strcasecmp(Name,"Mandi House");
if(i==0)
return 131;
i=strcasecmp(Name,"Janpath");
if(i==0)
return 132;
i=strcasecmp(Name,"Central Secratariat");
if(i==0)
return 133;
i=strcasecmp(Name,"Khan Market");
if(i==0)
return 134;
i=strcasecmp(Name,"JLN Stadium");
if(i==0)
return 135;
i=strcasecmp(Name,"Jangpura");
if(i==0)
return 136;
i=strcasecmp(Name,"Lajpat Nagar");
if(i==0)
return 137;
i=strcasecmp(Name,"Moolchand");
if(i==0)
return 138;
i=strcasecmp(Name,"Kailash Colony");
if(i==0)
return 139;
i=strcasecmp(Name,"Nehru Place");
if(i==0)
return 140;
i=strcasecmp(Name,"Kalkaji Mandir");
if(i==0)
return 141;
i=strcasecmp(Name,"Govind Puri");
if(i==0)
return 142;
i=strcasecmp(Name,"Okhla");
if(i==0)
return 143;
i=strcasecmp(Name,"Jasola - Apollo");
if(i==0)
return 144;
i=strcasecmp(Name,"Sarita Vihar");
if(i==0)
return 145;
i=strcasecmp(Name,"Mohan Estate");
if(i==0)
return 146;
i=strcasecmp(Name,"Tughlakabad");
if(i==0)
return 147;
i=strcasecmp(Name,"Badarpur Border");
if(i==0)
return 148;
i=strcasecmp(Name,"Sarai");
if(i==0)
return 149;
i=strcasecmp(Name,"NHPC Chowk");
if(i==0)
return 150;
i=strcasecmp(Name,"Mewala Maharajpur");
if(i==0)
return 151;
i=strcasecmp(Name,"Sector 28");
if(i==0)
return 152;
i=strcasecmp(Name,"Badkal Mor");
if(i==0)
return 153;
i=strcasecmp(Name,"Old Faridabad");
if(i==0)
return 154;
i=strcasecmp(Name,"Neelam Chand Ajronda");
if(i==0)
return 155;
i=strcasecmp(Name,"Bata Chowk");
if(i==0)
return 156;
i=strcasecmp(Name,"Escorts Mujesar");
if(i==0)
return 157;
else
return -50;

}

/*This function assigns a number to each station*/
void numToName(int t)
{
switch(t)
{

//Yellow Line
case 0 :
printf("\nHuda City Center->");
break;
case 1 :
printf("\nIffco Chowk->");
break;
case 2 :
printf("\nMG Road->");
break;
case 3 :
printf("\nSikanderpur->");
break;
case 4 :
printf("\nGuru Dronacharya->");
break;
case 5 :
printf("\nArjangarh->");
break;
case 6 :
printf("\nGhitorni->");
break;
case 7 :
printf("\nSultanpur->");
break;
case 8 :
printf("\nChattarpur->");
break;
case 9 :
printf("\nQutub Minar->");
break;
case 10 :
printf("\nSaket->");
break;
case 11 :
printf("\nMalviya Nagar->");
break;
case 12 :
printf("\nHauz Khas->");
break;
case 13:
printf("\nGreen Park->");
break;
case 14 :
printf("\nAIIMS->");
break;
case 15 :
printf("\nINA->");
break;
case 16 :
printf("\nJor Bagh->");
break;
case 17 :
printf("\nRace Course->");
break;
case 18 :
printf("\nUdyog Bhawan->");
break;
case 19:
printf("\nCentral Secrateriat->");
break;
case 20 :
printf("\nPatel Chowk->");
break;
case 21 :
printf("\nRajiv Chowk->");
break;

case 22 :
printf("\nNew Delhi->");
break;
case 23 :
printf("\nChawri Bazaar->");
break;
case 24 :
printf("\nChandni Chowk->");
break;
case 25 :
printf("\nKashmere Gate->");
break;
case 26 :
printf("\nCivil Lines->");
break;
case 27 :
printf("\nVidhan Sabha->");
break;
case 28 :
printf("\nVishwavidyalaya->");
break;
case 29 :
printf("\nGTB Nagar->");
break;
case 30 :
printf("\nModel Town->");
break;
case 31 :
printf("\nAzadpur->");
break;
case 32 :
printf("\nAdarsh Nagar->");
break;
case 33 :
printf("\nJahangirpuri->");
break;
case 34 :
printf("\nHaiderpur Badli Mor->");
break;
case 35 :
printf("\nRohini Sector 18,19->");
break;
case 36 :
printf("\nSamaypur Badli->");
break;

//Blue Line

case 38 :
printf("\nDwarka Sector 21->");
break;
case 39 :
printf("\nDwarka Sector 8->");
break;
case 40 :
printf("\nDwarka Sector 9->");
break;
case 41 :
printf("\nDwarka Sector 10->");
break;
case 42 :
printf("\nDwarka Sector 11->");
break;
case 43 :
printf("\nDwarka Sector 12->");
break;
case 44 :
printf("\nDwarka Sector 13->");
break;
case 45 :
printf("\nDwarka Sector 14->");
break;
case 46 :
printf("\nDwarka->");
break;
case 47 :
printf("\nDwarka Mor->");
break;
case 48 :
printf("\nNawada->");
break;
case 49 :
printf("\nUttam Nagar West->");
break;
case 50 :
printf("\nUttam Nagar East->");
break;
case 51 :
printf("\nJanakpuri West");
break;
case 52 :
printf("\nJanakpuri East");
break;
case 53 :
printf("\nTilak Nagar->");
break;
case 54 :
printf("\nSubhas Nagar->");
break;
case 55 :
printf("\nTagore Garden->");
break;
case 56 :
printf("\nRajouri Garden->");
break;
case 57 :
printf("\nRamesh Nagar->");
break;
case 58 :
printf("\nMoti Nagar->");
break;
case 59 :
printf("\nKirti Nagar->");
break;
case 60 :
printf("\nShadipur->");
break;
case 61 :
printf("\nPatel Nagar->");
break;
case 62 :
printf("\nRajendra Place->");
break;
case 63 :
printf("\nKarol Bagh->");
break;
case 64 :
printf("\nJhandewalan->");
break;
case 65 :
printf("\nRamakrishna Ashram Marg->");
break;
case 66 :
printf("\nRajiv Chowk->");
break;
case 67 :
printf("\nBarakhamba Road->");
break;
case 68 :
printf("\nMandi House->");
break;
case 69 :
printf("\nPragati Maidan->");
break;
case 70 :
printf("\nIndraprastha->");
break;
case 71 :
printf("\nYamuna Bank->");
break;


case 73 :
printf("\nAkshardham->");
break;
case 74 :
printf("\nMayur Vihar I->");
break;
case 75 :
printf("\nMayur Vihar Extn.->");
break;
case 76 :
printf("\nNew Ashok Nagar->");
break;
case 77 :
printf("\nNoida Sect. 15->");
break;
case 78 :
printf("\nNoida Sect. 16->");
break;
case 79 :
printf("\nNoida Sect. 18->");
break;
case 80 :
printf("\nBotanical Garden->");
break;
case 81 :
printf("\nGolf Cource->");
break;
case 82 :
printf("\nCity Center->");
break;
case 83 :
printf("\nLaxmi Nagar->");
break;


case 84 :
printf("\nNirman Vihar->");
break;
case 85 :
printf("\nPreet Vihar->");
break;
case 86 :
printf("\nKarkarduma->");
break;
case 87 :
printf("\nAnand Vihar ISBT->");
break;
case 88 :
printf("\nKaushambi->");
break;
case 89 :
printf("\nVaishali->");
break;


case 91 :
printf("\nRithala->");
break;
case 92 :
printf("\nRohini west->");
break;
case 93 :
printf("\nRohini East->");
break;
case 94 :
printf("\nPitampura->");
break;
case 95 :
printf("\nKohat Enclave->");
break;
case 96 :
printf("\nNetaji Subhash Place->");
break;
case 97 :
printf("\nKeshav Puram->");
break;
case 98 :
printf("\nKanhaiya Nagar->");
break;
case 99 :
printf("\nInderlok->");
break;
case 100 :
printf("\nShastri Nagar->");
break;
case 101 :
printf("\nPratap Nagar->");
break;
case 102 :
printf("\nPulbangash->");
break;
case 103 :
printf("\nTis Hazari->");
break;
case 104 :
printf("\nKashmere Gate->");
break;
case 105 :
printf("\nShastri Park->");
break;
case 106 :
printf("\nSeelampur->");
break;
case 107 :
printf("\nWelcome->");
break;
case 108 :
printf("\nMansarover Park->");
break;
case 109 :
printf("\nShahdra->");
break;
case 110 :
printf("\nJhilmil->");
break;
case 111 :
printf("\nDilshad Garden->");
break;


case 113 :
printf("\nMundka->");
break;
case 114 :
printf("\nRajdhani Park->");
break;
case 115 :
printf("\nNangloi Railway Station->");
break;
case 116 :
printf("\nNangloi->");
break;
case 117 :
printf("\nSurajmal Stadium->");
break;
case 118 :
printf("\nUdyog Nagar->");
break;
case 119 :
printf("\nPeeragarhi->");
break;
case 120 :
printf("\nPaschim Vihar west->");
break;
case 121 :
printf("\nPaschim Vihar East->");
break;
case 122 :
printf("\nMadipur->");
break;
case 123 :
printf("\nShivaji Park->");
break;
case 124 :
printf("\nPunjabi Bagh->");
break;
case 125 :
printf("\nAshok Park Main->");
break;
case 126 :
printf("\nInderlok->");
break;
case 127 :
printf("\nSatguru Ram Singh Marg->");
break;
case 128 :
printf("\nKirti Nagar->");
break;


case 130 :
printf("\nITO->");
break;
case 131 :
printf("\nMandi House->");
break;
case 132 :
printf("\nJanpath->");
break;
case 133 :
printf("\nCentral Secratariat->");
break;
case 134 :
printf("\nKhan Market->");
break;
case 135 :
printf("\nJLN Stadium->");
break;
case 136 :
printf("\nJangpura->");
break;
case 137 :
printf("\nLajpat Nagar->");
break;
case 138 :
printf("\nMoolchand->");
break;
case 139 :
printf("\nKailash Colony->");
break;
case 140 :
printf("\nNehru Place->");
break;
case 141 :
printf("\nKalkaji Mandir->");
break;
case 142 :
printf("\nGovind Puri->");
break;
case 143 :
printf("\nOkhla->");
break;
case 144 :
printf("\nJasola - Appolo->");
break;
case 145 :
printf("\nSarita Vihar->");
break;
case 146 :
printf("\nMohan Estate->");
break;
case 147 :
printf("\nTughlakabad->");
break;
case 148 :
printf("\nBadarpur Border->");
break;
case 149 :
printf("\nSarai->");
break;
case 150 :
printf("\nNHPC Chowk->");
break;
case 151 :
printf("\nMewala Maharajpur->");
break;
case 152 :
printf("\nSector 28->");
break;
case 153 :
printf("\nBadkal Mor->");
break;
case 154 :
printf("\nOld Faridabad->");
break;
case 155 :
printf("\nNeelam Chowk Ajronda->");
break;
case 156 :
printf("\nBata Chowk->");
break;
case 157 :
printf("\nEscorts Mujesar->");
break;
return;

}
}

/*When entered station is not found in the function station() then the first three letters of the entered station name are compared to
each station in this function*/
int stationNotFound(char Name[30])
{
int i,data,j=0;

printf("\nDid you mean");
i=strncasecmp(Name,"Huda City Center",3);
if(i==0)
{
printf("\nHuda City Center  (search key)->0");  
j=1;

data =  0;
push3(data);
}

i=strncasecmp(Name,"Iffco Chowk",3);
if(i==0)
{
printf("\nIffco Chowk  (search key)->1"); 
j=1;

data = 1; 
push3(data);
}

i=strncasecmp(Name,"MG Road",3);
if(i==0)
{
printf("\nMG Road (search key)->2"); 
j=1;

data = 2; 
push3(data);
}

i=strncasecmp(Name,"Sikanderpur",3);
if(i==0)
{
printf("\nSikanderpur  (search key)->3"); 
j=1;

data = 3;
push3(data);
}

i=strncasecmp(Name,"Guru Dronacharya",3);
if(i==0)
{
printf("\nGuru Dronacharya  (search key)->4"); 
j=1;

data =  4;
push3(data);
}

i=strncasecmp(Name,"Arjangarh",3);
if(i==0)
{
printf("\nArjangarh  (search key)->5"); 
j=1;

data =  5;
push3(data);
}

i=strncasecmp(Name,"Ghitorni",3);
if(i ==0)
{
printf("\nGhitorni  (search key)->6"); 
j=1;

data =  6;
push3(data);
}

i=strncasecmp(Name,"Sultanpur",3);
if(i ==0)
{
printf("\nSultanpur  (search key)->7"); 
j=1;

data = 7; 
push3(data);
}

i=strncasecmp(Name,"Chattarpur",3);
if(i ==0)
{
printf("\nChattarpur  (search key)->8"); 
j=1;

data =  8;
push3(data);
}

i=strncasecmp(Name,"Qutub Minar",3);
if(i==0)
{
printf("\nQutub Minar  (search key)->9"); 
j=1;

data =  9;
push3(data);
}

i=strncasecmp(Name,"Saket",3);
if(i==0)
{
printf("\nSaket  (search key)->10"); 
j=1;

data =  10;
push3(data);
}

i=strncasecmp(Name,"Malviya Nagar",3);
if(i==0)
{
printf("\nMalviya Nagar  (search key)->11"); 
j=1;

data =  11;
push3(data);
}

i=strncasecmp(Name,"Hauz Khas",3);
if(i==0)
{
printf("\nHauz Khas  (search key)->12"); 
j=1;

data =  12;
push3(data);
}

i=strncasecmp(Name,"Green Park",3);
if(i==0)
{
printf("\nGreen Park  (search key)->13"); 
j=1;

data =  13;
push3(data);
}

i=strncasecmp(Name,"AIIMS",3);
if(i==0)
{
printf("\nAIIMS  (search key)->14"); 
j=1;

data =  14;
push3(data);
}

i=strncasecmp(Name,"INA",3);
if(i==0){
printf("\nINA  (search key)->15"); 
j=1;

data = 15; 
push3(data);
}

i=strncasecmp(Name,"Jor Bagh",3);
if(i==0)
{
printf("\nJor Bagh  (search key)->16"); 
j=1;

data =  16;
push3(data);
}

i=strncasecmp(Name,"Race Course",3);
if(i==0)
{
printf("\nRace Course  (search key)->17"); 
j=1;

data =  17;
push3(data);
}

i=strncasecmp(Name,"Udyog Bhawan",3);
if(i==0)
{
printf("\nUdyog Bhawan  (search key)->18"); 
j=1;

data =  18;
push3(data);
}

i=strncasecmp(Name,"Central Secratariat",3);
if(i==0){
printf("\nCentral Secratariat  (search key)->19"); 
j=1;

data =  19;
push3(data);

}i=strncasecmp(Name,"Patel Chowk",3);
if(i==0){
printf("\nPatel Chowk  (search key)->20"); 
j=1;

data = 20; 
push3(data);

}i=strncasecmp(Name,"Rajiv Chowk",3);                //         Junction
if(i==0){
printf("\nRajiv Chowk  (search key)->21"); 
j=1;

data =  21;
push3(data);

}i=strncasecmp(Name,"New Delhi",3);
if(i==0){
printf("\nNew Delhi  (search key)->22"); 
j=1;

data =  22;
push3(data);

}i=strncasecmp(Name,"Chawri Bazaar",3);
if(i==0){
printf("\nChawri Bazaar  (search key)->23"); 
j=1;

data =  23;
push3(data);

}i=strncasecmp(Name,"Chandni Chowk",3);
if(i==0){
printf("\nChandni Chowk  (search key)->24"); 
j=1;

data = 24; 
push3(data);
}i=strncasecmp(Name,"Kashmere Gate",3);
if(i==0){
printf("\nKashmere Gate  (search key)->25"); 
j=1;

data =  25;
push3(data);
}i=strncasecmp(Name,"Civil Lines",3);
if(i==0){
printf("\nCivil Lines  (search key)->26"); 
j=1;

data =  26;
push3(data);
}i=strncasecmp(Name,"Vidhan Sabha",3);
if(i==0){
printf("\nVidhan Sabha  (search key)->27"); 
j=1;

data =  27;
push3(data);
}i=strncasecmp(Name,"Vishwavidyalaya",3);
if(i==0){
printf("\nVishwavidyalaya  (search key)->28"); 
j=1;

data =  28;
push3(data);
}i=strncasecmp(Name,"GTB Nagar",3);
if(i==0){
printf("\nGTB Nagar  (search key)->29"); 
j=1;

data =  29;
push3(data);
}i=strncasecmp(Name,"Model Town",3);
if(i==0){
printf("\nModel Town  (search key)->30"); 
j=1;

data =  30;
push3(data);
}i=strncasecmp(Name,"Azadpur",3);
if(i==0){
printf("\nAzadpur  (search key)->31"); 
j=1;

data =  31;
push3(data);
}i=strncasecmp(Name,"Adarsh Nagar",3);
if(i==0){
printf("\nAdarsh Nagar  (search key)->32"); 
j=1;

data =  32;
push3(data);
}i=strncasecmp(Name,"Jahangirpuri",3);
if(i==0){
printf("\nJahangirpuri  (search key)->33"); 
j=1;

data =  33;
push3(data);
}i=strncasecmp(Name,"Haiderpur Badli Mor",3);
if(i==0){
printf("\nHaiderpur Badli Mor  (search key)->34"); 
j=1;

data =  34;
push3(data);
}i=strncasecmp(Name,"Rohini Sector 18/19",3);
if(i==0){
printf("\nRohini Sector 18/19  (search key)->35"); 
j=1;

data =  35;
push3(data);
}i=strncasecmp(Name,"Samaypur Badli",3);
if(i==0){
printf("\nSamaypur Badli  (search key)->36"); 
j=1;

data =  36;
push3(data);



//Blue line
}i=strncasecmp(Name,"Dwarka Sect. 21",3);
if(i==0){
printf("\nDwarka Sect. 21  (search key)->38"); 
j=1;

data =  38;
push3(data);

}i=strncasecmp(Name,"Dwarka Sect. 8",3);
if(i==0){
printf("\nDwarka Sect. 8  (search key)->39"); 
j=1;

data =  39;
push3(data);

}i=strncasecmp(Name,"Dwarka Sect. 9",3);
if(i==0){
printf("\nDwarka Sect. 9  (search key)->40"); 
j=1;

data = 40; 
push3(data);

}i=strncasecmp(Name,"Dwarka Sect. 10",3);
if(i==0){
printf("\nDwarka Sect. 10  (search key)->41"); 
j=1;

data =  41;
push3(data);

}i=strncasecmp(Name,"Dwarka Sect. 11",3);
if(i==0){
printf("\nDwarka Sect. 11  (search key)->42"); 
j=1;

data =  42;
push3(data);

}i=strncasecmp(Name,"Dwarka Sect. 12",3);
if(i==0){
printf("\nDwarka Sect. 12  (search key)->43"); 
j=1;

data =  43;
push3(data);

}i=strncasecmp(Name,"Dwarka Sect. 13",3);
if(i==0){
printf("\nDwarka Sect. 13  (search key)->44"); 
j=1;

data =  44;
push3(data);

}i=strncasecmp(Name,"Dwarka Sect. 14",3);
if(i==0){
printf("\nDwarka Sect. 14  (search key)->45"); 
j=1;

data =  45;
push3(data);

}i=strncasecmp(Name,"Dwarka",3);
if(i==0){
printf("\nDwarka  (search key)->46"); 
j=1;

data =  46; 
push3(data);

}i=strncasecmp(Name,"Dwarka Mor",3);
if(i==0){
printf("\nDwarka Mor  (search key)->47"); 
j=1;

data =  47;
push3(data);

}i=strncasecmp(Name,"Nawada",3);
if(i==0){
printf("\nNawada  (search key)->48"); 
j=1;

data =  48;
push3(data);

}i=strncasecmp(Name,"Uttam Nagar West",3);
if(i==0){
printf("\nUttam Nagar West  (search key)->49"); 
j=1;

data =  49;
push3(data);

}i=strncasecmp(Name,"Uttam Nagar East",3);
if(i==0){
printf("\nUttam Nagar East  (search key)->50"); 
j=1;

data =  50;
push3(data);

}i=strncasecmp(Name,"Janakpuri West",3);
if(i==0){
printf("\nJanakpuri West  (search key)->51"); 
j=1;

data = 51; 
push3(data);

}i=strncasecmp(Name,"Janakpuri East",3);
if(i==0){
printf("\nJanakpuri East  (search key)->52"); 
j=1;

data =  52;
push3(data);

}i=strncasecmp(Name,"Tilak Nagar",3);
if(i==0){
printf("\nTilak Nagar  (search key)->53"); 
j=1;

data =  53;
push3(data);

}i=strncasecmp(Name,"Subhash Nagar",3);
if(i==0){
printf("\nSubhash Nagar  (search key)->54"); 
j=1;

data =  54;
push3(data);

}i=strncasecmp(Name,"Tagore Garden",3);
if(i==0){
printf("\nTagore Garden  (search key)->55"); 
j=1;

data =  55;
push3(data);

}i=strncasecmp(Name,"Rajouri Garden",3);
if(i==0){
printf("\nRajouri Garden  (search key)->56"); 
j=1;

data =  56;
push3(data);

}i=strncasecmp(Name,"Ramesh Nagar",3);
if(i==0){
printf("\nRamesh Nagar  (search key)->57"); 
j=1;

data = 57; 
push3(data);

}i=strncasecmp(Name,"Moti Nagar",3);
if(i==0){
printf("\nMoti Nagar  (search key)->58"); 
j=1;

data =  58;
push3(data);

}i=strncasecmp(Name,"Kirti Nagar",3);
if(i==0){
printf("\nKirti Nagar  (search key)->59"); 
j=1;

data =  59;
push3(data);

}i=strncasecmp(Name,"Shadipur",3);
if(i==0){
printf("\nShadipur  (search key)->60"); 
j=1;

data =  60;
push3(data);

}i=strncasecmp(Name,"Patel Nagar",3);
if(i==0){
printf("\nPatel Nagar  (search key)->61"); 
j=1;

data =  61;
push3(data);

}i=strncasecmp(Name,"Rajendra Place",3);
if(i==0){
printf("\nRajendra Place  (search key)->62"); 
j=1;

data =  62;
push3(data);

}i=strncasecmp(Name,"Karol Bagh",3);
if(i==0){
printf("\nKarol Bagh  (search key)->63"); 
j=1;

data =  63;
push3(data);

}i=strncasecmp(Name,"Jhandewalan",3);
if(i==0){
printf("\nJhandewalan  (search key)->64"); 
j=1;

data =  64;
push3(data);

}i=strncasecmp(Name,"Ramakrishna Ashram Marg",3);
if(i==0){
printf("\nRamakrishna Ashram Marg  (search key)->65"); 
j=1;

data =  65;
push3(data);
}
i=strncasecmp(Name,"Barakhamba Road",3);
if(i==0){
printf("\nBarakhamba Road  (search key)->67"); 
j=1;

data =  67;
push3(data);

}i=strncasecmp(Name,"Mandi House",3);
if(i==0){
printf("\nMandi House  (search key)->68"); 
j=1;

data =  68;
push3(data);

}i=strncasecmp(Name,"Pragati Maidan",3);
if(i==0){
printf("\nPragati Maidan  (search key)->69"); 
j=1;

data =  69;
push3(data);

}i=strncasecmp(Name,"Indraprastha",3);
if(i==0){
printf("\nIndraprastha  (search key)->70"); 
j=1;

data =  70;
push3(data);

}i=strncasecmp(Name,"Yamuna Bank",3);
if(i==0){
printf("\nYamuna Bank  (search key)->71"); 
j=1;

data =  71;
push3(data);

}i=strncasecmp(Name,"Akshardham",3);
if(i==0){
printf("\nAkshardham  (search key)->73"); 
j=1;

data =  73;
push3(data);
}i=strncasecmp(Name,"Mayur Vihar I",3);
if(i==0){
printf("\nMayur Vihar I  (search key)->74"); 
j=1;

data =  74;
push3(data);
}i=strncasecmp(Name,"Mayur Vihar Ext.",3);
if(i==0){
printf("\nMayur Vihar Ext.  (search key)->75"); 
j=1;

data =  75;
push3(data);
}i=strncasecmp(Name,"New Ashok Nagar",3);
if(i==0){
printf("\nNew Ashok Nagar  (search key)->76"); 
j=1;

data =  76;
push3(data);
}i=strncasecmp(Name,"Noida Sect. 15",3);
if(i==0){
printf("\nNoida Sect. 15  (search key)->77"); 
j=1;

data =  77;
push3(data);
}i=strncasecmp(Name,"Noida Sect. 16",3);
if(i==0){
printf("\nNoida Sect. 16  (search key)->78"); 
j=1;

data =  78;
push3(data);
}i=strncasecmp(Name,"Noida Sect. 18",3);
if(i==0){
printf("\nNoida Sect. 18  (search key)->79"); 
j=1;

data =  79;
push3(data);
}i=strncasecmp(Name,"Botanical Garden",3);
if(i==0){
printf("\nBotanical Garden  (search key)->80"); 
j=1;

data =  80;
push3(data);
}i=strncasecmp(Name,"Golf Course",3);
if(i==0){
printf("\nGolf Course  (search key)->81"); 
j=1;

data =  81;
push3(data);
}i=strncasecmp(Name,"Noida City Center",3);
if(i==0){
printf("\nNoida City Center  (search key)->82"); 
j=1;

data =  82;
push3(data);

}i=strncasecmp(Name,"Lakshmi Nagar",3);
if(i==0){
printf("\nLakshmi Nagar  (search key)->83"); 
j=1;

data =  83;
push3(data);
}i=strncasecmp(Name,"Nirman Vihar",3);
if(i==0){
printf("\nNirman Vihar  (search key)->84"); 
j=1;

data =  84;
push3(data);
}i=strncasecmp(Name,"Preet Vihar",3);
if(i==0){
printf("\nPreet Vihar  (search key)->85"); 
j=1;

data =  85;
push3(data);
}i=strncasecmp(Name,"Karkarduma",3);
if(i==0){
printf("\nKarkarduma  (search key)->86"); 
j=1;

data =  86;
push3(data);
}i=strncasecmp(Name,"Anand Vihar ISBT",3);
if(i==0){
printf("\nAnand Vihar ISBT  (search key)->87"); 
j=1;

data =  87;
push3(data);
}i=strncasecmp(Name,"Kaushambi",3);
if(i==0){
printf("\nKaushambi  (search key)->88"); 
j=1;

data =  88;
push3(data);
}i=strncasecmp(Name,"Vaishali",3);
if(i==0){
printf("\nVaishali  (search key)->89"); 
j=1;

data =  89;
push3(data);



//red line
}i=strncasecmp(Name,"Rithala",3);
if(i==0){
printf("\nRithala  (search key)->91"); 
j=1;

data =  91;
push3(data);
}i=strncasecmp(Name,"Rohini West",3);
if(i==0){
printf("\nRohini West  (search key)->92"); 
j=1;

data =  92;
push3(data);
}i=strncasecmp(Name,"Rohini East",3);
if(i==0){
printf("\nRohini East  (search key)->93"); 
j=1;

data =  93;
push3(data);
}i=strncasecmp(Name,"Pitampura",3);
if(i==0){
printf("\nPitampura  (search key)->94"); 
j=1;

data =  94;
push3(data);
}i=strncasecmp(Name,"Kohat Enclave",3);
if(i==0){
printf("\nKohat Enclave  (search key)->95"); 
j=1;

data =  95;
push3(data);
}i=strncasecmp(Name,"Netaji Subhash Place",3);
if(i==0){
printf("\nNetaji Subhash Place  (search key)->96"); 
j=1;

data =  96;
push3(data);
}i=strncasecmp(Name,"Keshav Puram",3);
if(i==0){
printf("\nKeshav Puram  (search key)->97"); 
j=1;

data =  97;
push3(data);
}i=strncasecmp(Name,"Kanhaiya Nagar",3);
if(i==0){
printf("\nKanhaiya Nagar  (search key)->98"); 
j=1;

data =  98;
push3(data);
}i=strncasecmp(Name,"Inderlok",3);
if(i==0){
printf("\nInderlok  (search key)->99"); 
j=1;

data =  99;
push3(data);
}i=strncasecmp(Name,"Shastri Nagar",3);
if(i==0){
printf("\nShastri Nagar  (search key)->100"); 
j=1;

data =  100;
push3(data);
}i=strncasecmp(Name,"Pratap Nagar",3);
if(i==0){
printf("\nPratap Nagar  (search key)->101"); 
j=1;

data =  101;
push3(data);
}i=strncasecmp(Name,"Pulbangash",3);
if(i==0){
printf("\nPulbangash  (search key)->102"); 
j=1;

data =  102;
push3(data);
}i=strncasecmp(Name,"Tis Hazri",3);
if(i==0){
printf("\nTis Hazri  (search key)->103"); 
j=1;

data = 103; 
push3(data);
}i=strncasecmp(Name,"Shastri Park",3);
if(i==0){
printf("\nShastri Park  (search key)->105"); 
j=1;

data =  105;
push3(data);
}i=strncasecmp(Name,"Seelampur",3);
if(i==0){
printf("\nSeelampur  (search key)->106"); 
j=1;

data = 106; 
push3(data);
}i=strncasecmp(Name,"Welcome",3);
if(i==0){
printf("\nWelcome  (search key)->107"); 
j=1;

data =  107; 
push3(data);
}i=strncasecmp(Name,"Mansarover Park",3);
if(i==0){
printf("\nMansarover Park  (search key)->108"); 
j=1;

data =  108;
push3(data);
}i=strncasecmp(Name,"Shahdra",3);
if(i==0){
printf("\nShahdra  (search key)->109"); 
j=1;

data =  109;
push3(data);
}i=strncasecmp(Name,"Jhilmil",3);
if(i==0){
printf("\nJhilmil  (search key)->110"); 
j=1;

data =  110;
push3(data);
}i=strncasecmp(Name,"Dilshad Garden",3);
if(i==0){
printf("\nDilshad Garden  (search key)->111"); 
j=1;

data = 111; 
push3(data);

}i=strncasecmp(Name,"Mundka",3);
if(i==0){
printf("\nMundka  (search key)->113"); 
j=1;

data =  113;
push3(data);
}i=strncasecmp(Name,"Rajdhani Park",3);
if(i==0){
printf("\nRajdhani Park  (search key)->114"); 
j=1;

data =  114;
push3(data);
}i=strncasecmp(Name,"Nangloi Railway Station",3);
if(i==0){
printf("\nNangloi Railway Station  (search key)->115"); 
j=1;

data =  115;
push3(data);
}i=strncasecmp(Name,"Nangloi",3);
if(i==0){
printf("\nNangloi  (search key)->116"); 
j=1;

data =  116;
push3(data);
}i=strncasecmp(Name,"Surajmal Stadium",3);
if(i==0){
printf("\nSurajmal Stadium  (search key)->117"); 
j=1;

data =  117;
push3(data);
}i=strncasecmp(Name,"Udyog Nagar",3);
if(i==0){
printf("\nUdyog Nagar  (search key)->118"); 
j=1;

data =  118;
push3(data);
}i=strncasecmp(Name,"Peeragarhi",3);
if(i==0){
printf("\nPeeragarhi  (search key)->119"); 
j=1;

data = 119; 
push3(data);
}i=strncasecmp(Name,"Paschim Vihar West",3);
if(i==0){
printf("\nPaschim Vihar West  (search key)->120"); 
j=1;

data =  120;
push3(data);
}i=strncasecmp(Name,"Paschim Vihar East",3);
if(i==0){
printf("\nPaschim Vihar East  (search key)->121"); 
j=1;

data =  121;
push3(data);
}i=strncasecmp(Name,"Madipur",3);
if(i==0){
printf("\nMadipur  (search key)->122"); 
j=1;

data =  122;
push3(data);
}i=strncasecmp(Name,"Shivaji Park",3);
if(i==0){
printf("\nShivaji Park  (search key)->123"); 
j=1;

data =  123;
push3(data);
}i=strncasecmp(Name,"Punjabi Bagh",3);
if(i==0){
printf("\nPunjabi Bagh  (search key)->124"); 
j=1;

data =  124;
push3(data);
}i=strncasecmp(Name,"Ashok Park Main",3);
if(i==0){
printf("\nAshok Park Main  (search key)->125"); 
j=1;

data =  125;
push3(data);
}

i=strncasecmp(Name,"Satguru Ram Singh Marg",3);
if(i==0){
printf("\nSatguru Ram Singh Marg  (search key)->127"); 
j=1;

data =  127;
push3(data);
}

i=strncasecmp(Name,"ITO",3);
if(i==0){
printf("\nITO  (search key)->130"); 
j=1;

data = 130; 
push3(data);
}

i=strncasecmp(Name,"Janpath",3);
if(i==0){
printf("\nJanpath  (search key)->132"); 
j=1;

data = 132;
push3(data);
}

i=strncasecmp(Name,"Khan Market",3);
if(i==0){
printf("\nKhan Market  (search key)->134"); 
j=1;

data =  134;
push3(data);
}i=strncasecmp(Name,"JLN Stadium",3);
if(i==0){
printf("\nJLN Stadium  (search key)->135"); 
j=1;

data =  135;
push3(data);
}i=strncasecmp(Name,"Jangpura",3);
if(i==0){
printf("\nJangpura  (search key)->136"); 
j=1;

data =  136;
push3(data);
}i=strncasecmp(Name,"Lajpat Nagar",3);
if(i==0){
printf("\nLajpat Nagar  (search key)->137"); 
j=1;

data =  137;
push3(data);
}i=strncasecmp(Name,"Moolchand",3);
if(i==0){
printf("\nMoolchand  (search key)->138"); 
j=1;

data = 138; 
push3(data);
}i=strncasecmp(Name,"Kailash Colony",3);
if(i==0){
printf("\nKailash Colony  (search key)->139"); 
j=1;

data =  139;
push3(data);
}i=strncasecmp(Name,"Nehru Place",3);
if(i==0){
printf("\nNehru Place  (search key)->140"); 
j=1;

data =  140;
push3(data);
}i=strncasecmp(Name,"Kalkaji Mandir",3);
if(i==0){
printf("\nKalkaji Mandir  (search key)->141"); 
j=1;

data =  141;
push3(data);
}i=strncasecmp(Name,"Govind Puri",3);
if(i==0){
printf("\nGovind Puri  (search key)->142"); 
j=1;

data =  142;
push3(data);
}i=strncasecmp(Name,"Okhla",3);
if(i==0){
printf("\nOkhla  (search key)->143"); 
j=1;

data =  143;
push3(data);
}i=strncasecmp(Name,"Jasola - Apollo",3);
if(i==0){
printf("\nJasola - Apollo  (search key)->144"); 
j=1;

data =  144;
push3(data);
}i=strncasecmp(Name,"Sarita Vihar",3);
if(i==0){
printf("\nSarita Vihar  (search key)->145"); 
j=1;

data =  145;
push3(data);
}i=strncasecmp(Name,"Mohan Estate",3);
if(i==0){
printf("\nMohan Estate  (search key)->146"); 
j=1;

data =  146;
push3(data);
}i=strncasecmp(Name,"Tughlakabad",3);
if(i==0){
printf("\nTughlakabad  (search key)->147"); 
j=1;

data =  147;
push3(data);
}i=strncasecmp(Name,"Badarpur Border",3);
if(i==0){
printf("\nBadarpur Border  (search key)->148"); 
j=1;

data =  148;
push3(data);
}i=strncasecmp(Name,"Sarai",3);
if(i==0){
printf("\nSarai  (search key)->149"); 
j=1;

data =  149;
push3(data);
}i=strncasecmp(Name,"NHPC Chowk",3);
if(i==0){
printf("\nNHPC Chowk  (search key)->150"); 
j=1;

data =  150;
push3(data);
}i=strncasecmp(Name,"Mewala Maharajpur",3);
if(i==0){
printf("\nMewala Maharajpur  (search key)->151"); 
j=1;

data =  151;
push3(data);
}i=strncasecmp(Name,"Sector 28",3);
if(i==0){
printf("\nSector 28  (search key)->152"); 
j=1;

data =  152;
push3(data);
}i=strncasecmp(Name,"Badkal Mor",3);
if(i==0){
printf("\nBadkal Mor  (search key)->153"); 
j=1;

data =  153;
push3(data);
}i=strncasecmp(Name,"Old Faridabad",3);
if(i==0){
printf("\nOld Faridabad  (search key)->154"); 
j=1;

data =  154;
push3(data);
}i=strncasecmp(Name,"Neelam Chand Ajronda",3);
if(i==0){
printf("\nNeelam Chand Ajronda  (search key)->155"); 
j=1;

data =  155;
push3(data);
}i=strncasecmp(Name,"Bata Chowk",3);
if(i==0){
printf("\nBata Chowk  (search key)->156"); 
j=1;

data =  156;
push3(data);
}i=strncasecmp(Name,"Escorts Mujesar",3);
if(i==0){
printf("\nEscorts Mujesar  (search key)->157"); 
j=1;

data =  157;
push3(data);
}
if(j==1)
return 1;
else if(j==0)
{
printf("\r            ");
return -51;
}
}
/*Stack is used to avoid any kind of exploits done by hacker or user*/
void push3(int data)
{
if(top==MAXMATCH-1)
{
printf("\nStack Overflow");
exit(1);
}
top=top+1;
Match3[top]=data;
return;
}

int pop3()
{
int data;
if(top==-1)
{
printf("\nStack Underflow\n");
return;
}
data=Match3[top];
top=top-1;
return data;
}

int colorDecider(int Number)
{
int Color;
if(Number>=0 && Number <=37)
Color = Yellow;
else if(Number>=38 && Number <=89)
Color = Blue;
else if(Number>=91 && Number <=111)
Color = Red;
else if(Number>=113 && Number <=128)
Color = Green;
else if(Number>=130 && Number <=157)
Color = Violet;
return Color;
}



