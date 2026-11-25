#include<iostream>
using namespace std;

//This function calculates all the parameters with my id 620510 or input id 
//=====Functiontion 1 part 1:=====
void calparameters(long long int id,int &N,int &PCT,int &VAR,int &M, long long &Q, int &R,int &C,int &SM,int &DIR,
                   int &KW,int &KB,int &NR,int &K)
{
	N   = 12 + (id % 7);
    PCT = 40 + (id % 31);
    VAR = id % 2;
    M   = 10 + (id % 6);
    Q   = 12000 + 500 * (id % 13);
    R   = 12 + (id % 5);
    C   = 16 + ((id / 10) % 7);
    SM  = 5 + ((id / 100) % 3);
    DIR = id % 8;
    KW  = 2 + ((id / 1000) % 3);
    KB  = 3 + ((id / 10000) % 4);
    NR  = 6 + ((id / 7) % 3);
    K   = 20 + (id % 11);
}
//this function is the random number genrator which takes input state and genrates random numbers through it
//=====function 2 part 1:=====
long long int nextrandom(long long int &state)
{
	state = (state * 48271) % 2147483647;
	return state;
}
//this function genrates a random number between minimum value and maximum value by formulla given in assigment and calling next random function
//state is passed as refrence and also state is passed in nextrandom function

// This function is the start part required in some function where it warmup the state 10 times by runing it 
//10 times

//=====function 3 part 1:=====
void startpart(long long int &state, long long int id, int p)
{
    state = (id * 10) + p;
    for(int i = 1; i <= 10; i++)
    {
    nextrandom(state);
    }
}

//=====function 4 part 1:=====
int random(long long int &state, long long min, long long max)
{
	long long int val = nextrandom(state);
	if(val<0){val = -(val);}
	return min + (val % (max - min + 1));
}
//this function is the main essiential part of assigment part 1 which genrates all the mohhala based on conditions given in assigment 
//and this function calls function random to roll a number and based on that the mohalla category is selected  after that the mohalla code
//is made again using function random the chracted is added in first 2 part of code because 'A' have ASCII value so a new character is formed with that
// the /0 part tells that the character array have ended here and there are no more characters to enter
//at the end location is calculated by calling random function and giving it state min and max value

//=====function 5 part 1:=====
void makemohalla(long long int &state, char &type, char code[10], long long int &size, long long int &row, long long int &col, long long int &demand)
{
	//type size and demand genrator
	int roll = random(state,1,100);
	if     (roll <= 8 ) {type = 'H'; size = random(state,50,400  ); demand = size *  120;}
	else if(roll <= 20) {type = 'S'; size = random(state,200,1500); demand = size *   20;}
	else if(roll <= 40) {type = 'F'; size = random(state,5,60    ); demand = size * 3000;}
	else                {type = 'R'; size = random(state,300,6000); demand = size *   75;}
	//code genrator of each mohalla
	code[0] = 'A' + random(state,0,25);
	code[1] = 'A' + random(state,0,25);
	code[2] = '-';
	int num = random(state,100,999);
	code[3] = '0' + (num / 100);
	code[4] = '0' + ((num/10) % 10);
	code[5] = '0' + (num % 10);
	code[6] = '\0';
	//location genrator of each mohalla
	row = random(state,0,99);
	col = random(state,0,99);
}
//this function checks weather the code that is assigned to each mohalla and genrated in mohhala function is unique it is not a duplicate
//when ever the code is same it throws it away while loop in main become false and genrate a fresh code and checks again

//=====function 6 part 1:=====
bool isduplicate(char a[], char b[])
{
	for(int i=0 ; i<6; i++){if(a[i] != b[i]){return false;}}return true;
}

//=====fucntion 7 part 1:=====
void checkdup(int N,long long int &state,char type[25],char code[25][10],
              long long int size[25],long long int row[25],long long int col[25],
              long long int demand[25],long long int &totaldem,
              long long int order[25],long long int allA[25],
              long long int allB[25],long long int allC[25])
{
	totaldem =0;
	for(int i = 1 ; i<= N ; i++)
	{
	while(true)
	{
	makemohalla(state,type[i],code[i],size[i],row[i],col[i],demand[i]);
	bool duplicate = false;
	//checking if any code is duplicate or not
	for(int j=1 ; j<i ; j++)
	{
	if(isduplicate(code[j],code[i]))
	{
	duplicate = true;break;
	}
	}
	if(duplicate==false){break;}
	}
	totaldem += demand[i];
	}
}

//this function prints the summary of part 1 with mohalla number size code demand of water its type location and at the end
//total demand of each type

//=====function 8 part 1:=====
void summary(int N, char type[], long long int size[], char code[][10], long long int row[], long long int col[],
             long long int demand[], long long int totaldem)
{             
    cout<<"\n---MOHALLAS OF VALLEY QUETTA (N = "<<N<<" )---\n";
    
    //this loop prints N number of mohhalas with their size demand type and location
    for(int i=1 ; i <= N ; i++)
    {
    cout<<"Mohalla "<< i << ":"<<endl;
    cout<<code[i]<<"   |   Type: "<<type[i]<<"   |   Size: "<<size[i]<<"\t"<<"   |   Demand: "<<demand[i] <<"L\t |   Location: ("<<row[i]<<", "<<col[i]<<")\n";
	}
	
	//this block calculates total amount of types of H,R,F,S and their total demand of water
	long long int countH = 0, countS = 0, countR = 0, countF = 0, demH = 0, demS = 0, demR = 0, demF = 0;
	for(int i = 1 ; i<= N ; i++)
	{
	if     (type[i] == 'H'){countH++; demH += demand[i];}
	else if(type[i] == 'S'){countS++; demS += demand[i];}
	else if(type[i] == 'R'){countR++; demR += demand[i];}
	else if(type[i] == 'F'){countF++; demF += demand[i];}
	}
	
	//this block prints the total amount of H,R,S,F and their total demand
	cout <<"\nALL THE DETAILS OF TYPE H,S,R,F:\n";
	cout << "Hospitals  : " << countH << " \tmohallas Total Demand = " << demH << "L\n";
    cout << "School     : " << countS << " \tmohallas Total Demand = " << demS << "L\n";
    cout << "Residential: " << countR << " \tmohallas Total Demand = " << demR << "L\n";
    cout << "Farm       : " << countF << " \tmohallas Total Demand = " << demF << "L\n";
    cout << "Total Valley Demand = "  << totaldem << " L\n";
    
}
//this function signature value for calculating signature function needed for part 0 in assigment with given formulla

//=====function 9 part 0:=====
void Sig(long long int &S, long long int x)
{
	S = ((S * 31) + x) % 1000000007;
}
//this function calculate every signature value and total it save it in S, sig function is called with the value S and x

//=====function 10 part 0:=====
long long int calculatesig(long long int N1, long long int PCT1, long long int VAR1, long long int M1, 
                       long long int Q1, long long int R1, long long int C1, long long int SM1, 
                       long long int DIR1, long long int KW1, long long int KB1, long long int NR1, 
                       long long int K1){
    long long S = 0;  
    Sig(S, N1  );    
    Sig(S, PCT1);  
    Sig(S, VAR1);  
    Sig(S, M1  );   
    Sig(S, Q1  );   
    Sig(S, R1  );    
    Sig(S, C1  );    
    Sig(S, SM1 );   
    Sig(S, DIR1);  
    Sig(S, KW1 );   
    Sig(S, KB1 );   
    Sig(S, NR1 );  
    Sig(S, K1  );    

    return S;
}
//this function calculate signature p1 for part 1: using same signature formulla but with diffrent values passed

//=====function 11 part 1:=====
long long int calculatesig1(int N ,char type[], long long int size[] ,char code[][10] ,long long int row[] ,long long int col[] ,long long int demand[] ,long long int totaldem)
{
	long long int S = 0;
	
	//this is the main loop that run N times and calculate the signature
	for(int i =1 ; i<=N ; i++)
	{
	int t=0;
	if     (type[i]=='H'){t=1;}
	else if(type[i]=='S'){t=2;}
	else if(type[i]=='R'){t=3;}
	else                 {t=4;}
	Sig(S ,t);
	Sig(S ,size[i]);
	
	//this loop calculate ASCII values of 6 digit code and store it in signature
	for(int j=0 ; j<6; j++)
	{
	Sig(S ,code[i][j]);
	}
	
	//this block calculate the signature from row coloumn and demand and store it in signature
	Sig(S ,   row[i]);
	Sig(S ,   col[i]);
	Sig(S ,demand[i]);
	}
	
	//at last this line calculate signature from totaldem and return the S
	Sig(S ,totaldem);
	return S;
}






//                                ================================== PART 1 END HERE ==================================






//this function calculate the policy A priority 

//=====function 12 part 2:=====
void policyA(int N, int VAR, long long int V,char type[],long long int demand[], long long int order[], long long int allA[])
{
	//this chunk of code is the sorting chunk water is distributed after H is sorted and at starting indexes
	for(int i=1 ; i<=N ; i++)  {order[i] = i;}
	//bubble sorting this loop is the starting loop which runs N tiems
	for(int a = 1; a < N; a++)
	{
	//this loop is the secondry loop which lso run N times so even if the H is at the last index of array it can 
	//be bring to first and comapred
	for(int j=1 ; j<N ; j++)
	{
	int m1 = order[j]; int m2 = order[j + 1];
	int pri1;
	if     (type[m1] == 'H'){pri1 = 1;}
	else if(type[m1] == 'S'){pri1 = 2;}
	else if(type[m1] == 'R'){pri1 = 3;}
	else                    {pri1 = 4;}
	int pri2;
	if     (type[m2] == 'H'){pri2 = 1;}
	else if(type[m2] == 'S'){pri2 = 2;}
	else if(type[m2] == 'R'){pri2 = 3;}
	else                    {pri2 = 4;}
	
	bool swap = false;
	//condtion if both priority are same 
	if(pri1 == pri2)
	{
	if     (VAR == 0 && demand[m1] > demand[m2]) {swap = true;}
	else if(VAR == 1 && demand[m1] < demand[m2]) {swap = true;}
	else if(demand[m1] == demand[m2] && m1 > m2) {swap = true;}
	else                                         {  continue; }
    }
    //condition if priority 1 is greater then priority 2
	else if(pri1 > pri2){swap = true;}
	else                {  continue; }
	//condition to swap the other values like R S F stored in index so H can get the highest priority
	if(swap == true)
	{
	int temp = order[j];
	order[j] = order[j + 1];
	order[j + 1] = temp;
	//these both loop runs N*N times so even if H is stored at last index it can be bring to first index
	}
	}	
    }
    //this block of code distributes the water to H highest priority and remaining to the 
    //mohalla that are left and then at last the mohalla that didnt got all the demand gets the remaning
    long long int left = V;
	for(int k = 1 ; k<=N ; k++)
	{
	int m = order[k];
	
	if(left >= demand[m])
	{
	allA[m] = demand[m];
	left = left - demand[m];
	}
	//if not enough water is left to fullfill full demand it gives the remaing to it and then left = 0
	else
	{
	allA[m] = left;
	left = 0;
	}
	}
}


//this function distribute water policy B largest remainder method

//=====function 13 part 2:=====
void policyB(int N, long long int V, long long int totaldem, long long int demand[], long long int allB[])
{
	long long int rem[25],used = 0;
	int order[25];
	//distributes the water equaly with given remainder formulla in assigment
	for(int i=1 ; i<=N ; i++)
	{
	allB[i]  = (V * demand[i]) / totaldem;
	rem[i]   = (V * demand[i]) % totaldem;
	used     = used + allB[i];
	order[i] = i;
	}
	//there is still some water left so left store that
	long long int left = V - used;
	//this loop gives remaing water to those mohallas that have highest remainder becase mohalla with 
	//less remainder got more water compared to those with less remainder
	for(int j=1 ; j<=left ; j++)
	{
	int final=1;
	
	for(int k=1 ; k<=N ; k++)
	{
	//this condition finds the largest remainder and store it in final
	if(rem[k] > rem[final]){final = k;}
	}
	//final value is is given 1 extra litre and it is crossed of with -1 remainder so it doesnt get water again
	allB[final] = allB[final] + 1;
	rem[final] = -1;
	}
}
//this function policy C distributes water its a combination of policy A and B

//=====function 14 part 2:=====
void policyC(int N, long long int V, char type[], long long int demand[], long long int allC[])
{
	long long int remdemand[25], extra[25], used = 0, remtotal = 0;
	//hospitals are given higher priority first loop scans hospitals
	for(int i=1 ; i<=N ; i++)
	{
	if(type[i] == 'H' && used + demand[i]<= V)
	{
	//hospitals demand are fullfilled 100%
	allC[i] = demand[i];
	used = used + demand[i];
	remdemand[i] = 0;
	}
	//other types are given 0 water for now
	else
	{
	allC[i] = 0;
	remdemand[i] = demand[i];
	remtotal = remtotal + remdemand[i];
	}
	}
	//calculating the water that is left
	long long int leftV = V - used;
	//using policy b to devide the water equally among other types with the remaning water
	if(leftV > 0 && remtotal > 0)
	{
	policyB(N, leftV, remtotal, remdemand, extra);
	//hospitals remaing demand was already 0 so policy B doesnt effect them and other types got the water equally distributed
	for(int j=1 ; j<=N ; j++)   {allC[j] = allC[j] + extra[j];}
	}
}
//this function calculates that how fairly the water was distributed amout N number of mohallas and how many mohallas are left
//who got 0 water and at the end it calculate the total percenttage of water distributation among N mohallas
//it uses pass by refrence so at the end the final values are send summary of part 2 function

//=====function 15 part 2:=====
void measure(int N, long long int demand[], long long int all[], int &full, int &zero, long long int &minP, long long int &avgpercentage)
{
	full = 0, zero = 0, minP = 100;  long long int sum = 0;
	//this loop checks each mohalla of policy A B and C if there demand is fullfilled 100 percent or not
	for(int i=1 ; i<=N ; i++)
	{
	if(all[i] == demand[i]){full++;}
	else{}
	if(all[i] == 0)        {zero++;}
	else{}
	//calculates percentage how much their demand is full filled
	long long int percentage = (all[i] * 100) / demand[i];
	//is condition checks the minumum percentage that which mohhala got the most minimum amount of water
	if(percentage < minP){minP = percentage;}
	sum = sum + percentage;
	}
	//calculating the average of whole valley N mohallas
	avgpercentage = sum / N;
}
//this function sort the demands in assending order from smalles to largest

//=====function 16 part 2:=====
void sortdemand(int N, long long int demand[], long long int sorted[])
{
	//this loop copies demand array elements into sorted array so demand remain untouched
	for(int i = 1 ; i<=N ; i++)
	{
	// i did a mistake through out the program i saved all the demands starting from index 1 insted of 0
	//so now sorted array also start from 1 
	sorted[i] = demand[i];
	}
	//using bubble sorting method we used earlier to comapre 2 elements of array and swap them
	for(int j = 1 ; j<=N-1 ; j++)
	{
	//doing N-1 because we have used K+1 which already compares all the elements in array 
	for(int k = 1 ; k<=N-1 ; k++)
	{
	if(sorted[k] > sorted[k+1])
	{
	//this block of code swaps the demand
	long long int temp = sorted[k];
	sorted[k] = sorted[k + 1];
	sorted[k + 1] = temp;
	}
	}
	}
}
//this function perform action of sorted demands and check how many demands are <= X and how many comparisons it took to find
//it these all are done by binary search operation provided in assigment

//=====fucntion 17 part 2:=====
int binsearch(int N, long long int sorted[], long long int X, int &comp)
{
	int lo = 1, hi = N+1;
	comp = 0;
	while(lo < hi)
	{
	int mid = (lo + hi) / 2; comp++;
	if(sorted[mid] <= X) {lo = mid + 1;}
	else                 {  hi = mid;  }
	}
	return lo-1;
}
//this function check sorted demands >= X from left to right with linear search method provided in assigment and it also
//calculate how many comparisons it took to to find it

//=====function 18 part 2:=====	
int linesearch(int N, long long int sorted[], long long int X, int &comp)
{
	int position = 1;
	comp = 0;
	while(position <= N)
	{
	comp++;
	if(sorted[position] > X) {break;}
	else                     {position = position + 1;}
	}
	return position-1;
}

//this function calculates signature p2 from already computed values
//bcomp mean binary comparison and lcomp mean linier comparison
//=====function 19 part 2:=====	
long long int calculatesig2(int N,long long int V,long long int allA[],long long int allB[],
                            int fullA,int zeroA,long long int minA,long long int avgA,
                            int fullB,int zeroB,long long int minB,long long int avgB,
                            long long int X[],int ans[],int bcomp[],int lcomp[])
{
	//this block of code calculates the signature p2
	long long int S = 0;
	Sig(S, V);
	for(int i=1 ; i<=N ; i++) {Sig(S, allA[i]);}
	for(int i=1 ; i<=N ; i++) {Sig(S, allB[i]);}
	Sig(S, fullA);
	Sig(S, zeroA);
	Sig(S, minA);
	Sig(S, avgA);
	Sig(S, fullB);
	Sig(S, zeroB);
	Sig(S, minB);
	Sig(S, avgB);
	for(int k=0 ; k<3 ; k++)
	{
	Sig(S, X[k]);
	Sig(S, ans[k]);
	Sig(S, bcomp[k]);
	Sig(S, lcomp[k]);
	}
	cout<<"P2 SIGNATURE = "<<S<<endl;
	//returns the signature value
	return S;
}

//this function prints the summary of the part 2

//=====function 20 part 2:=====
long long int printpart2(int N,long long int V,long long int order[],long long int demand[],long long int allA[],long long int allB[],long long int allC[],int printonoff)
{
	//value of V and order heading
	if(printonoff==1)
	{
	cout<<"\n---Part 2 sharing the water---\n";
	cout<<"Avaliable water V = "<<V<<"L\nOrder: ";
	//loop the print the assending order of mohhalas who recieved water
	for(int i = 1 ; i<=N ; i++){cout << order[i]<<" ";}
	//headings
	cout<<"\nmohalla\t|demand \t|policy A \t|policy B \t|policy C \t\n";
	//main loop to print al the information
	for(int i =1 ; i<=N ; i++)
	{
	cout<<i<<"\t|"<< demand[i]<<"\t\t|"<<allA[i]<<"\t\t|"<<allB[i]<<"\t\t|"<<allC[i]<<"\n";
	}
	cout<<endl;
	}
	// this block of code calculates how many mohallas got full demand how many got zero water what was the minimum
	//percentage of the mohhala getting water and total average of the valley
	int fullA, zeroA, fullB, zeroB, fullC, zeroC;
	long long int minA, avgA, minB, avgB, minC, avgC;
	measure(N, demand, allA, fullA, zeroA, minA, avgA);
	measure(N, demand, allB, fullB, zeroB, minB, avgB);
	measure(N, demand, allC, fullC, zeroC, minC, avgC);
	if(printonoff==1)
	{
	cout<<"Policy A = Full: "<<fullA<<" | Zero: "<<zeroA<<" | min%: "<<minA<<" | AVG%: "<<avgA<<endl;
	cout<<"Policy B = Full: "<<fullB<<" | Zero: "<<zeroB<<" | min%: "<<minB<<" | AVG%: "<<avgB<<endl;
	cout<<"Policy C = Full: "<<fullC<<" | Zero: "<<zeroC<<" | min%: "<<minC<<" | AVG%: "<<avgC<<endl;
	}
	
	long long int sorted[25];
	sortdemand(N, demand, sorted);
	long long int X[3] = {V/N ,50000 ,250000};
	//binarycompare and linear compare methods
	
	int ans[3], ans2[3], bcomp[3], lcomp[3];
	//this loop calculates the answer with binary search and linear search
	for(int k=0 ; k<3 ; k++)
	{
	ans[k] = binsearch(N ,sorted, X[k], bcomp[k]);
	ans2[k]=linesearch(N ,sorted ,X[k] ,lcomp[k]);
	if(printonoff==1)
	{
	cout<<"X = "<<X[k]<<"\t | answer= "<<ans[k]<<"\t | binnary search comparison= "<<bcomp[k]<<"\t | Linear search comparison= "<<lcomp[k]<<endl;
	}
	}
	long long int S=calculatesig2(N,V,allA,allB,fullA,zeroA,minA,avgA,fullB,zeroB,minB,avgB,X,ans,bcomp,lcomp);
	return S;
			 
}






//                                ================================== PART 2 END HERE ==================================







//this is the starting function of part 3 where tanker priority and taker size is calculated
//using the random number genrator
//=====function 21 part 3:=====
void makerequest(long long int id,int M,long long int s[],int p[])
{
	long long int state = (id * 10) + 3;
	for(int i=1 ; i<=10 ; i++){nextrandom(state);}
	for(int j=1 ; j<=M ; j++)
	{
	//this line decide the size Q of tanker
	s[j] = random(state ,10 ,90) * 100;
	//this line decide the priority of of urgency from 1 to 9
	// 9 is the most urgent and 1 is the less
	p[j] = random(state ,1 ,9);	
	}
}

//=====function 22 part 3:=====
void winner(int M,long long int Q,long long int L,int P,int current[],int best[],long long int &highestL,int &bestP)
{
	//this condition check truck isnt overflowing and priority sccore is higher then the best one and if
	//they have same priority score it pick that uses less water
	if(L <= Q && (P > bestP || (P == bestP && L < highestL)))
	{
	//if condition is true best priority and highestL is ubdated 
	bestP = P;
	highestL = L;
	for(int i=1 ; i<=M ; i++){best[i] = current[i];}	
	}
}
//this function calculates all the posibilities without checking the overflow all the combinations that 
//can be taken and skipped using winner function the winner is decided

//=====function 23 part 3:=====
void version1(int j,int M,long long int Q,long long int s[],int p[],long long int L,int P,
              int current[],int best[],long long int &highestL,int &bestP,long long int &call)
{
	call++;
	//this condition check if the requests are completed or not
	if(j > M)  {winner(M,Q,L,P,current,best,highestL,bestP);}
	else
	{
	// this block is TAKE path it genrates all the path combinations that can be taken
	current[j] = 1;
	version1(j + 1,M,Q,s,p,L + s[j],P + p[j],current,best,highestL,bestP,call);
	//this block is the SKIP path all the combinations that can be skiped 
	current[j] = 0;
	version1(j + 1,M,Q,s,p,L,P,current,best,highestL,bestP,call);
	}
}
//this function is same as version 1 the diffrence is the TAKE have a condition provided in assigment
//and SKIP is same it is executed after TAKE so all comaprisions and possibilites can be found out

//=====function 24 part 3:=====
void version2(int j,int M,long long int Q,long long int s[],int p[],long long int L,int P,
              int current[],int best[],long long int &highestL,int &bestP,long long int &call)
{
	call++;
	//condtion to pass the values to winner block
	if(j > M)  {winner(M,Q,L,P,current,best,highestL,bestP);}
	//recursive block to check all possible combinations
	else
	{
	//the condition of TAKE
	if(L + s[j] <= Q)
	{
	current[j] = 1;
	version2(j + 1,M,Q,s,p,L + s[j],P + p[j],current,best,highestL,bestP,call);
    }
    //SKIP 
    else{}
	current[j] = 0;
	version2(j + 1,M,Q,s,p,L,P,current,best,highestL,bestP,call);
	}
}
//this is version 3 which follow starting condition given in assigment and then also function 2 logic is used to make up version 3

//=====function 25 part 3:=====
void version3(int j,int M,long long int Q,long long int s[],int p[],long long int L,int P,
              int current[],int best[],long long int &highestL,int &bestP,long long int &call)
{
	call++;
	int rem = 0;
	for(int i=j ; i<=M ; i++){rem+=p[i];}
	//condition of passing the value to to check the winner
	if(P + rem >= bestP)
	{
	if(j > M) {winner(M,Q,L,P,current,best,highestL,bestP);}
	  
	//recursive block
	else
	{
    //condition of TAKE 
	if(L + s[j] <= Q)
	{
	current[j] = 1;
	version3(j + 1,M,Q,s,p,L + s[j],P + p[j],current,best,highestL,bestP,call);
    }
    //SKIP have no condition so it will check all posible combinations
	current[j] = 0;
	version3(j + 1,M,Q,s,p,L,P,current,best,highestL,bestP,call);
	}
}
}


//this function calculates signature p3 from values already calculated in part 3

//=====function 26 part 3:=====
long long int calculatesig3(int M,long long int s[],int p[],int best[],
                            int bestP,long long int highestL,long long int c1,long long int c2,long long int c3,
                            long long int Q4,int best4[],int P4,long long int L4,long long int c4)
{
	//this block of code calculates the signature p3
	long long int S = 0;
	for(int i=1 ; i<=M ; i++) {Sig(S,s[i]); Sig(S,p[i]);}
	for(int i=1 ; i<=M ; i++) {if(best[i] == 1) {Sig(S,i);}}
	
	Sig(S,bestP);
	Sig(S,highestL);
	Sig(S,c1);
	Sig(S,c2);
	Sig(S,c3);
	Sig(S,Q4);
	for(int i=1 ; i<=4 ; i++) {if(best4[i] == 1) {Sig(S,i);}}
	Sig(S,P4);
	Sig(S,L4);
	Sig(S,c4);
	cout<<"P3 SIGNATURE = "<<S<<endl;
	//returns the signature value
	return S;
}

//it prints the summary of part 3

//=====function 27 part 3:=====
long long int printpart3(long long int id, int M, long long int Q,int printonoff)
{
	long long int L1=0,L2=0,s[25],highestL = 0,L4 = 0,c1 = 0,c2 = 0,c3 = 0,c4 = 0,S = 0;
	int P1=0,P2=0,best1[25],best2[25],p[25],current[25],best[25],best4[25],bestP = 0,P4 = 0;
	makerequest(id, M, s, p);
	if(printonoff==1)
	{
	cout<<"\nThe Emergency Tanker\nTanker:"<<endl;
	for(int i=1 ; i<=M ; i++){cout<<" "<<i<<": "<<s[i]<<"L | Priority "<<p[i]<<endl;}
	}
    //calculates version 1 2 3 calls
    //version 1
	version1(1,M,Q,s,p,0,0,current,best1,L1,P1,c1);
	//best priority and highest demand is set 0 so next version start fresh
	bestP = 0 ; highestL = 0;
	//version 2
	version2(1,M,Q,s,p,0,0,current,best2,L2,P2,c2);
	//best priority and highest demand is set 0 so next version start fresh
	bestP = 0 ; highestL = 0;
	//version 3
	version3(1,M,Q,s,p,0,0,current,best,highestL,bestP,c3);
	//check if all the answers from all version are same
	bool same = (L1 == highestL && L2 == highestL && P1 == bestP && P2 == bestP);
	for(int i=1 ; i<=M ; i++) {if(best1[i] != best[i] || best2[i] != best[i]) {same = false;}}

    //this is the Q4 test with the values proivided in assigment
	long long int Q4 = (s[1] + s[2] + s[3] + s[4]) / 2;
	version2(1,4,Q4,s,p,0,0,current,best4,L4,P4,c4);
    //printing the best groups
    if(printonoff==1)
	{
	cout<<"\nBest group: ";
	for(int i=1 ; i<=M ; i++){if(best[i] == 1){cout<<i<<" ";}}
	//printing the versions call and if the values are same or not
	cout<<highestL<<"L, priority "<<bestP<<"\nCall: Version 1 = "<<c1<<", Version 2 = "<<c2<<", Version 3 = "<<c3<<"\n";
	if(same==true) {cout<<"Same answers in all versions: YES"<<endl;}
	else           {cout<<"Same answers in all versions: NO"<<endl;}
	//printing the 	Q4 tested values
	cout<<"small test of Q4 = "<<Q4<<",best group ";
	//printing the Q4 test final answer
	for(int i=1 ; i<=4 ; i++){if(best4[i] == 1){cout<<i<<" ";}}
	cout<<"|"<<L4<<"L, priority "<<P4<<"), "<<c4<<" call\n";
	}
	
	S=calculatesig3(M,s,p,best,bestP,highestL,c1,c2,c3,Q4,best4,P4,L4,c4);
	return S;
}





//                                ================================== PART 3 END HERE ==================================




//this function convert negative number to positive number so program deosnt have a 
//logical error so even negative numbers are converted to positive number

//=====function 28 part 4:=====
int absolute(int x)
{
	if(x<0){return -(x);}
	return x;
}
// this function assign compass direction letter according to the assigment and then based on the letter it assign
//the direction arrow

//=====function 29 part 4:=====
void direction(int DIR,int k,int &cr,int &cc,char &arrow)
{
	char compassd = ' ';
	//DIR 0 1 2 3 4 5 6 7 this block assign the letter compass direction according to the given table

    if     (DIR == 0) { if(k==1) compassd='N'; else if(k==2) compassd='E'; else if(k==3) compassd='S'; else if(k==4) compassd='W'; }
	else if(DIR == 1) { if(k==1) compassd='E'; else if(k==2) compassd='S'; else if(k==3) compassd='W'; else if(k==4) compassd='N'; }
	else if(DIR == 2) { if(k==1) compassd='S'; else if(k==2) compassd='W'; else if(k==3) compassd='N'; else if(k==4) compassd='E'; }
	else if(DIR == 3) { if(k==1) compassd='W'; else if(k==2) compassd='N'; else if(k==3) compassd='E'; else if(k==4) compassd='S'; }
	else if(DIR == 4) { if(k==1) compassd='N'; else if(k==2) compassd='W'; else if(k==3) compassd='S'; else if(k==4) compassd='E'; }
	else if(DIR == 5) { if(k==1) compassd='W'; else if(k==2) compassd='S'; else if(k==3) compassd='E'; else if(k==4) compassd='N'; }
	else if(DIR == 6) { if(k==1) compassd='S'; else if(k==2) compassd='E'; else if(k==3) compassd='N'; else if(k==4) compassd='W'; }
	else              { if(k==1) compassd='E'; else if(k==2) compassd='N'; else if(k==3) compassd='W'; else if(k==4) compassd='S'; }
	//arrow direction asssign according to the compass direction
	if     (compassd=='N'){cr = -1; cc = 0; arrow = '^';}
	else if(compassd=='E'){cr = 0; cc = 1; arrow = '>';}
	else if(compassd=='S'){cr = 1; cc = 0; arrow = 'v';}
	else                  {cr = 0; cc = -1; arrow = '<';}
	
}
//this function calculate height of each cell apply smoothing then give it direction then assign wheather if it is
//a rock well and at last it calculates its sotrm or rain it will get everything is calculated by formulla 
//given in the aassigment

//=====function  30 part 4:=====
void makemap(long long int id,int R,int C,int SM,int KW,int KB,int h[][25],int cell[][25],int rain[][25])
{
	//warming up randomgenrator 10 times
	long long int state = (id * 10) + 4;
	for(int i=1 ; i<=10 ; i++){nextrandom(state);}
	
	//raw heights as mentioned in the assigment
	for(int j=0 ; j<R ; j++)
	{
	//value genrated by random here in loop is stored in specific box which is addressed
	//like h[1][2] so row 1 and coloumn 2 have value of random
	for(int k=0 ; k<C ; k++)   {h[j][k] = random(state,0,499); cell[j][k] = 0;}
	}
	
	//smoothing SM
	int temp[25][25];
	for(int a=1 ; a<=SM ; a++)
	{
	for(int b=0 ; b<R ; b++)
	{
	for(int c=0 ; c<C ; c++)
	{
	int sum = h[b][c] , count = 1;
	
	//checking the position is inside the map or not and also it doesnot exceed the limit of R rows and C coloumns 
	//using each compass direction each cell which can also be knows as a house we calculate their neighbour how many 
	//neighbour the cell have with count++
	if(b - 1 >= 0){sum = sum + h[b - 1][c];count++;} else{}//north
	if(b + 1 < R ){sum = sum + h[b + 1][c];count++;} else{}//south 
	if(c + 1 <  C){sum = sum + h[b][c + 1];count++;} else{}//east
	if(c - 1 >= 0){sum = sum + h[b][c - 1];count++;} else{}//west
	
	//copying the answer into a new 2d array so orignal remains same and sum/count calculates how high or how low 
	//the cell is located like on a mountain or below it
	temp[b][c] = sum / count;
	}
	}
	//now assigning the new value to 'h' height 2d array we didnt did that before because it will curropt the calculation 
	//the orignal h array will be changed and all the comparison operators will check the new values instead of old
	for(int l=0; l<R ; l++){for(int m=0 ; m<C ; m++){h[l][m] = temp[l][m];}}
    }
    //shaping the valley now
    
    //this genrator gets a random number through genrator of row and coloumn and then
    //it make it the centre of the grid or matrix
    int coloumnr = random(state,0,R - 1), coloumnc = random(state,0,C - 1);
    //then this nested loop make other neighboring cells acording to that centre
    for(int d=0 ; d<R ; d++)
    {
    for(int e=0 ; e<C ; e++)
    {
    h[d][e] = h[d][e] + 12 * (absolute(d - coloumnr) + absolute(e - coloumnc));
	}
	}
	//well is denoted by 1 and rock is denoted by 2
	
	//the while loop make sure its not a duplicate by true and false evaluation
	//this is well the well is assigned randomly
	for(int k=1 ; k<=KW ; k++)
	{
	while(true)
	{
	int o = random(state,0,R-1);
	int p = random(state,0,C-1);
	if(cell[o][p] == 0){cell[o][p] = 1; break;}  else{continue;}
	}
	}
	//this is rock it is also assigned randomly 
	for(int q=1 ; q<=KB ; q++)
	{
	while(true)
	{
	int r = random(state,0,R-1);
	int s = random(state,0,C-1);
	if(cell[r][s] == 0){cell[r][s] = 2; break;}  else{continue;}
	}
	}
	
	//storm 
	int sr = random(state,0,R - 1);
	int sc = random(state,0,C - 1);
	int P  = random(state,60,120 );
	//this loop calculates how much rain will the every cell and how far is it from centre
	//recieve and if it is 0 or less then 0 rain is automatically set to 0 formullas as
	//given in assigment
	for(int s=0 ; s<R ; s++)
	{
	for(int t=0 ; t<C ; t++)
	{
	int value = P - 6 * (absolute(s - sr) + absolute(t - sc));
	if(value < 0 || cell[s][t] == 2 ){rain[s][t] = 0;}
	else                             {rain[s][t] = value;}
	}
	}
}
//this function checks that where water flow like it should flow from high to low height and not in rocks
//only in wells # mean its a rock and W mean go ahead clear way 

//=====function 31 part 4:=====
void nextcell(int r,int c,int R,int C,int DIR,int h[][25],int cell[][25],int &neighbourr,int &neighbourc,char &flow)
{
	neighbourr = r , neighbourc = c;
	if(cell[r][c] == 1){flow = 'W'; return;}// W mean open or go ahead
	if(cell[r][c] == 2){flow = '#'; return;}//# mean stop that mean it is a rock
	int low = h[r][c];
	
	flow = 'o';//o mean open flow like water can flow here
	//this loop checks neighbour N,S,E,W compass directions
	for(int k=1 ; k<=4 ; k++)
	{
	int cc,cr; //cc means change in coloumn and cr mean change in row
	char newarr;
	direction(DIR,k,cr,cc,newarr);
	int nr = r + cr; //nr mean new row and nc mean new coloumn
	int nc = c + cc;
	
	//main block which check condition and checks that is the neighbour low height so water can flow
	//and also not a rock
	if(nr >= 0 && nr < R && nc >= 0 && nc < C && cell[nr][nc] != 2)
	{
	if(h[nr][nc] < low)
	{
	low = h[nr][nc];
	neighbourr = nr; neighbourc = nc;  //mc and mr mean main row and main coloumn
	flow = newarr;
	}
	else{}
	}
	else{}
	}
}
//this function finds the sink or well moreover it check where will the water flow using nextcell function
//it checkes every celll by cell until it reaches the corner or end
//this function store everything in 2d array memory its the memory function

//=====function 32 part4:===== 
void findsink1(int currentr,int currentc,int R,int C,int DIR,int h[][25],int cell[][25],int memoryR[][25],int memoryC[][25],int &sinkr,int &sinkc,long long int &countmemory)
{
	//count calculates how many steps it took to calculate the sink for all cells 
	countmemory++;
	//r stand for row and c stand for coloumn like sinkr = sink row or crcurrentc = current coloumn
	//this condition check if we have already saved the sink for this cell or not if yes then it return true
	if(memoryR[currentr][currentc] != -1)
	{
	sinkr = memoryR[currentr][currentc];
	sinkc = memoryC[currentr][currentc];
	return;
	}
	else{}
	int newr,newc;
	char flow;
	nextcell(currentr,currentc,R,C,DIR,h,cell,newr,newc,flow);
	//this is the base condition 
	if(newr == currentr && newc == currentc)
	{
	sinkr = currentr;
	sinkc = currentc;
	}
	//this is the recursive block
	else
	{
	findsink1(newr,newc,R,C,DIR,h,cell,memoryR,memoryC,sinkr,sinkc,countmemory);
	}
	//at the end of the recursive the final value or location is stored in sinkrow and sinkcoloumn
	//this is the final stage where it store the location 
	memoryR[currentr][currentc] = sinkr;
	memoryC[currentr][currentc] = sinkc;
}
//this function work same as the findsink1 but only diffrence is that it dont have a memory

//=====function 33 part 4:=====
void findsink2(int currentr, int currentc, int R, int C, int DIR, int h[][25], int cell[][25], int &sinkr, int &sinkc, long long int &countmemory)
{
	//this count how many steps it took to calculate the asnwer 
	countmemory++;
	int newrow,newcoloumn;
	char character;//chracter mean the symbol or chracter # o and W which tell water well rock and flow
	nextcell(currentr,currentc,R,C,DIR,h,cell,newrow,newcoloumn,character);
	
	//this is the base condition of recursive block
	if(newrow == currentr && newcoloumn == currentc) {sinkr = currentr; sinkc = currentc;}
	
	//this is the recursive block it will run unti the new row and new coloumn are equal to the current r and c
	//which is the base condition
	else     {findsink2(newrow,newcoloumn,R,C,DIR,h,cell,sinkr,sinkc,countmemory);}
}

//this finction check wheater if the cell is sink or not or is it a rock it reutrn true if it is 
//sink and false when it is rock seprate function is also good for this because we can call it whenever
//we want and use it

//=====function 34 part 4:=====
bool issink(int i,int j,int cell[][25],int memR[][25],int memC[][25])
{
    // Must not be a rock, and the sink which is the last point where water will flow
    return (cell[i][j] != 2 && memR[i][j] == i && memC[i][j] == j);
}

//=====function 35 part 4:=====
void makebasins(int R,int C,int h[][25],int cell[][25],int rain[][25],int memoryR[][25],int memoryC[][25],
              char bmap[][25],int &numb,char bname[],int sinkR[],int sinkC[],int bcell[],long long int bwater[])
{
    //bwater,bcell means basin cell basin water so b stand for basin and R C stand for row and coloumn
    
    numb = 0; //number of basins
    
    //basin is the entire area of cells whose water flow towards the sink
   
    for(int i=0 ; i<R ; i++){for(int j=0 ; j<C ; j++)
    {
    // the basin should not be rock so i have made a seprate function for that so we can call 
    //it when ever we want it reutrn true which mean it is sink and false if it is rock
    if(issink(i,j,cell,memoryR,memoryC))
    {
    sinkR[numb] = i;
    sinkC[numb] = j;
	numb++;	
	}
	}
	}
	
	
	//sorting sinks with height as provided in assigment low first
	//this first loop controls how many times this loop run
	//numb means number of basins we did -1 to it because we also have to compare 0 or else
	//0 will not be compared and loop will finish early 
	for(int k=0 ; k<numb-1 ; k++)
	{
	//this second loop is for array indexes to check it like 1 2 3 4
	for(int l=0 ; l<numb-1 ; l++)
	{
	//cheking the height of the sinks and saving them in the variables height 1 and height 2
	int hei1 = h[sinkR[l]][sinkC[l]];
	//doing l+1 because i am using bubble sorting to compare and sort them
	int hei2 = h[sinkR[l+1]][sinkC[l+1]];
	//based of given contions in assigment
	bool swap = false;
	if(hei1>hei2)                                   {swap = true;}
	//if height are same we look at rows 
	else if(hei1 == hei2 && sinkR[l] > sinkR[l+1])  {swap = true;}
	//if both height row are same so we check coloumn and this simply mean if height and same row are same so 
	//condition is evaluated at the coloumn number which is smaller 
	else if(hei1 == hei2 && sinkR[l] == sinkR[l+1] && sinkC[l] > sinkC[l+1]) {swap = true;}
	
	//using bubble sorting method
	if(swap == true){
	int tempR = sinkR[l] , tempC = sinkC[l];
	sinkR[l]  = sinkR[l+1] ; 
	sinkC[l] = sinkC[l+1];
	sinkR[l + 1] = tempR;
	sinkC[l + 1] = tempC; 
	}
	}
    }
    
    //assinign the names to each basin according to assigment
    for(int m=0 ; m<numb ; m++)
    {
    //if basin are more then 26 so capital letter finished to we use small letters
    bname[m] = (m<26) ? ('A' + m) : (('a') + (m - 26));
    //both total cell and water in cells that belong to basin are set to zero so they start fresh 
    // and they dont have garbage value
    bcell[m] = 0;
    bwater[m] = 0;
	}
	
	//making the basin map
	//scanning the each cell of each coloumn and row
	for(int n=0 ; n<R ; n++)//row scanning
	{
	for(int o=0 ; o<C; o++)//coloumn scanning
	{
	// for the boudry or last corner we use # to show stop
	if(cell[n][o] == 2)
	{
	bmap[n][o] = '#';
	}
	//in else we track where does the water flow or where is it flowing 
	//after finding where it go next we move to next step
	else
	{
	for(int p=0; p<numb ; p++)
	{
	//checking if the cell belong to basin
	if(memoryR[n][o] == sinkR[p] && memoryC[n][o] == sinkC[p])
	{
	//the basin cell is assigned the name
	bmap[n][o] = bname[p];
	//counter counts how many total cells are basins 
	bcell[p]++;
	//then it multiplies the water by 200 and save it according to the assigment 200mm of rain
	bwater[p] += rain[n][o] * 200; 
	}
	}
	}
	}
	}
}


//this function calculates signature p4 from values already calculated in part 4

//=====function 36 part 4:=====
long long int calculatesig4(int R,int C,int h[][25],char bmap[][25],int numb,
                            int sinkR[],int sinkC[],int bcell[],long long int bwater[],
                            long long int cmem,long long int cnomem)
{
	//this block of code calculates the signature p4
	long long int S = 0;
	for(int i=0 ; i<R ; i++) {for(int j=0 ; j<C ; j++) {Sig(S,h[i][j]);}}
	for(int i=0 ; i<R ; i++) {for(int j=0 ; j<C ; j++) {Sig(S,(int)bmap[i][j]);}}
	for(int k=0 ; k<numb ; k++)
	{
	Sig(S,sinkR[k]);
	Sig(S,sinkC[k]);
	Sig(S,bcell[k]);
	Sig(S,bwater[k]);
	}
	Sig(S,cmem);
	Sig(S,cnomem);
	cout<<"P4 SIGNATURE = "<<S<<endl;
	//returns the signature value
	return S;
}


//=====function 37 part 4:=====
long long int printPart4(long long id, int R, int C, int DIR, int SM, int KW, int KB,
                int cell[][25], char bmap[][25], char bname[], int &numb, long long bwater[],int printonoff)
{
	int  h[25][25],rain[25][25],memoryR[25][25],memoryC[25][25];
	int sinkR[60],sinkC[60],bcell[60];
	long long cmem = 0,cnomem = 0;
	numb = 0;

	//Initialize memory arrays
	for(int i=0; i<R; i++)
	{
	for(int j=0; j<C; j++)
	{
	memoryR[i][j] = -1;
	memoryC[i][j] = -1;
	}
	}

	//Generate map, wells, rocks, and rain
	makemap(id,R,C,SM,KW,KB,h,cell,rain);

	// Calculating the sinks with and without memory
	for(int i=0; i<R; i++)
	{
	for(int j=0; j<C; j++)
	{
	if(cell[i][j] != 2)
	{
	int sr1, sc1, sr2, sc2;
	findsink1(i,j,R,C,DIR,h,cell,memoryR,memoryC,sr1,sc1,cmem);
	findsink2(i,j,R,C,DIR,h,cell,sr2,sc2,cnomem);
	}
	}
	}

	// Form and sort basins
	makebasins(R,C,h,cell,rain,memoryR,memoryC,bmap,numb,bname,sinkR,sinkC,bcell,bwater);
	
	if(printonoff==1)
	{
	cout<<"Map the valley \n\n\n\nheight Map"<<endl;
	
	//height map code block
	for(int i=0 ; i<R ; i++)
	{
	for(int j=0 ; j<C ; j++)
	{
	cout<<h[i][j]<<"\t";
	}
	cout<<endl;
	}
	cout<<endl;
	cout<<"flow map"<<endl;
	//flow map
	for(int k=0 ; k<R ; k++)
	{
	for(int l=0 ; l<C ; l++)
	{
	if(cell[k][l] == 2)
	{
	cout<<"# ";
	}
	else if(cell[k][l] == 1)
	{
    cout << "W ";
    }
	else
	{
	int newr,newc;
	char flow;
	nextcell(k,l,R,C,DIR,h,cell,newr,newc,flow);
	cout<<flow<<" ";
	}
	}
	cout<<endl;
	}
	
	//basin map 
	cout << "\nbasin Map:" << endl;
	for(int p=0 ; p<R; p++)
	{
	for(int o=0; o<C; o++)
	{
	cout << bmap[p][o] << " ";
	}
	cout << endl;
	}
	//basin map
	cout<<"\nbasin\t\t|sink(r,c)\t|height\t\t|type\t\t\t|cells\t\t|water(L)"<<endl;
	for(int m=0 ; m<numb ; m++)
	{
	cout<<bname[m]<<"\t\t|("<<sinkR[m]<<","<<sinkC[m]<<")\t\t|"<<h[sinkR[m]][sinkC[m]]<<"\t\t|";
	if(cell [sinkR[m]][sinkC[m]] == 1){cout<<"well\t\t\t|";}
	else{cout<<"natural\t\t|";}
	cout<<bcell[m]<<"\t\t|"<<bwater[m]<<endl;
	}
	
	//calls
	cout<<"\ncalls: "<<cmem<<"with memory and "<<cnomem<<"without memory\n";
	}
	//we dont need signature in control room REPORT 
	if(printonoff == 2) return 0;
	return calculatesig4(R,C,h,bmap,numb,sinkR,sinkC,bcell,bwater,cmem,cnomem);

}







//                                ================================== PART 4 END HERE ==================================






//this is a helper function of part 5 which multiply 2 square matrixes together
//and toegther K times which is A power K times with loops so we dont have to 
// multiply row with coloumn again and again 

//=====function 38 part 5:=====
void matrixhelp(int NR,long long arrA[25][25],long long arrB[25][25],long long result[25][25])
{
	//initilizng temp 2d array all values to 0
	long long temp[25][25] = {0};
	for(int i=0 ; i<NR ; i++)// row loop
	{
	for(int j=0 ; j<NR ; j++)//this is the coloumn loop 
	{
	long long int sum = 0;
	//k is the main loop when i is 1 k move verticall so all values are added
	//in the row and when j coloumn is 1 it moves downward so whole coloumn is
	//filled and a proper matrix can be formed
	for(int k=0 ; k<NR ; k++)
    {
    sum = (sum + arrA[i][k] * arrB[k][j]) % 1000003;
	}
	result[i][j] = sum;
	}
	}
	//when all the values are calculated we assign them to the result 
	//final result 2d array

}

//this function is method 1 power times to calculate W it calculates the total number of steps or walking
//paths using the helper function of matrix of length K

//=====function 39 part 5:=====
void walkmethod1(int NR,long long int K,long long arrA[25][25],long long walk[25][25],long long &count)
{
	//setting count to 0 so it calculates exact A power 20 times and we can also check it 
	count = 0;
	//first it calculates the base structure where pipe go 
	//before using helper function and creating matrix of it
	for(int i=0 ; i<NR ; i++)
	{
	for(int j=0 ; j<NR ; j++)
	{
	walk[i][j] = arrA[i][j];
	}
	}
	// this is the main block which multiplies the matrix K times using helper function and 
	//calculates the pipe structure and at the end
	//setting step = 1 so it runs exactly 20 times A power 20 as in assigment
	for(long long int step=1 ; step<K ; step++)
	{
	long long temp[25][25];
	matrixhelp(NR,walk,arrA,temp);
	for(int k=0 ; k<NR ; k++)
	{
	for(int l=0 ; l<NR ; l++)
	{
	// we save all new values in temp so walk stays same 
	walk[k][l] = temp[k][l];
	}
	}
	//to see how many times matrix is multipliyed we use count to track it
	count++;
	}
	
}
//this is a recursive function which works on method 2 as in the assigment 

//=====function 40 part 5:=====
void walkmethod2(int NR,long long int k,long long matrix[25][25],long long result[25][25],long long &count)
{
	//as given in assigment if step = 1 like we only want 1 step 
	if(k == 1)//base case
	{
    for(int i=0 ; i<NR ; i++)
	{
    for(int j=0 ; j<NR ; j++)
	{
    result[i][j] = matrix[i][j];
    }
    }
    return;
    }
    //it is the sqauring method given in assigment it devide by half 
    //then sqaure it so it work super fast instead of dinding step by step
    long long int half[25][25];
    walkmethod2(NR,k/2,matrix,half,count);
    long long int square[25][25];
    matrixhelp(NR,half,half,square);
    count++;
    
    //as the condition in assigment if k steps are odd 
    if(k%2 != 0)//base condition
    {
    long long temp[25][25];
    matrixhelp(NR,square,matrix,temp);
    count++;
    for(int k=0 ; k<NR ; k++)
    {
    for(int l=0 ; l<NR ; l++)
    {
    //the values are stored in temp so orignal remains same
    result[k][l] = temp[k][l];
	}
	}
	}
	//if the steps are not odd that mean they are even so direct calculation
	//no recursions here just loop
	else
	{
	for(int m=0 ; m<NR ; m++)
	{
	for(int n=0 ; n<NR ; n++)
	{
	result[m][n] = square[m][n];
	}
	}
	}
}

//this function calculates the determenant of the matrix with recursions
//and by following the rules and conditions provided in assigment

//=====function 41 part 5:=====
long long int dematrix(int size,long long matrix[25][25],long long &call)
{
	//count counts how many calls or recurive calls it took 
	call++;
	//this is the first conditon provided in the assigment 
	if(size == 1) return matrix[0][0];
    long long int total = 0;
    
    for(int i=0 ; i<size ; i++)
    {
    //subm means sub matrix
    long long subm[25][25];
    //submr means sub matrix row
    int submr=0;
    for(int j=1 ; j<size ; j++)
    {
    //submc means sub matrix coloumn
    int submc = 0;
    for(int k=0 ; k<size ; k++)
    {
    if(k == i){continue;}
    subm[submr][submc] = matrix[j][k];
    submc++;
	}
	submr++;
	}
	//using ternary operators to assign the signs alternating signs
	long long int sign = (i % 2 == 0) ? 1 : -1;
	total = total + sign * matrix[0][i] * dematrix(size-1,subm,call); //calling the function recursion too and also smaller sub matrix
	}
	return total;
}

//method 2 of pipe plans
//so this function explores all the cells that are they connected to reserviors or not and useses recursive calls to check if
//they all are connected together this is method 2 of tring every group in assigment

//=====function 42 part 5:=====
void visitreser(int currentres,int NR,int matrix[25][25],bool visit[])
{
	//seting the current reservior visit to true 
	visit[currentres] = true;
	for(int i=0 ; i<NR ; i++)
	{
	//checking the comdition if the reservior is connected or not
	//this is the base case of recursion 
	if(matrix[currentres][i] == 1 && visit[i]==false)
	{
	visitreser(i,NR,matrix,visit);
	}
	//at the end it mark all the reserviours visit to true because of recursion
	}
}

//method 2 of pipe plans
//in this function it checks weather if allthe cells connected to reserviors
//are connected together not and to make sure there is no cell left that is not conencted

//=====function 43 part 5:=====
bool valid(int NR, int numpg, int groupU[],int groupV[])
{
	//numpg means number of pipers in group and group u and p represent group names
	int matrix[25][25] = {0};//initilizing matrix array with all elemetnts 0
	for(int i=0 ; i<numpg ; i++)
	{
	int u = groupU[i];
	int v = groupV[i];
	matrix[u][v] = 1;
	matrix[v][u] = 1; // v and u because we also have to check the reverse 
	}
	bool visit[25] = {false};
	visitreser(0,NR,matrix,visit);
	
	for(int j=0 ; j<NR ; j++)
	{
	if(visit[j] == false)
	{
	return false;
	}
	else
	{}
	}
	return true;//after checking all cells it return true that all reseviors are checked 
	
}

//method 2 of pipe plans main body or brain
//this function combines both function of method 2 of aassigment and find all possible
//combinations of pipes NR -1 from the pipe list genrated and check how manygroups were genrated by counter

//=====function 44 part 5:=====
void groups(int index,int startp,int totalp,int target, 
            int allpu[],int allpv[],int currentgu[],int currentgv[], 
            int NR,long long int &groupc,long long int &plan)
{
	//startp means starting pipe totalp mean toal pipe all pu mean all pipe U and all pipe V 
	//currentgu mean current group U and current group V and groupc mean group checked
	if(index == target)
	{
	groupc++;
	if(valid(NR,target,currentgu,currentgv))
	{
	plan++;
	}
	return;
	}
	//base case of recusrion
	for(int i=startp ; i<totalp ; i++)
	{
	currentgu[index] = allpu[i];
	currentgv[index] = allpv[i];
	//recursive call
	groups(index + 1,i + 1, totalp,target,allpu,allpv,currentgu,currentgv,NR,groupc,plan);
	}
}

//this function calculates signature p5 from values already calculated in part 5
//=====function 45 part 5:=====
long long int calculatesig5(int NR,int tp,int allU[],int allV[],long long int W1[][25],
                            long long int m1,long long int m2,long long int plan,
                            long long int call,long long int gc,long long int planf)
{
	//this block of code calculates the signature p5
	long long int S = 0;
	Sig(S,NR);
	Sig(S,tp);
	for(int i=0 ; i<tp ; i++) {Sig(S,allU[i]); Sig(S,allV[i]);}
	for(int i=0 ; i<NR ; i++) {for(int j=0 ; j<NR ; j++) {Sig(S,W1[i][j]);}}
	Sig(S,m1);
	Sig(S,m2);
	Sig(S,plan);
	Sig(S,call);
	Sig(S,gc);
	Sig(S,planf);
	cout<<"P5 SIGNATURE = "<<S<<endl;
	//returns the signature value
	return S;
}

//this function is part 1 of printing the part 5 becuase it was very long so i broke it down into 
// 2 seprate parts this is part 1 that combine every calculation and print it 

//=====function 46 part 5:=====
void printpart5_1(long long int id,int NR,long long int K,long long A[25][25],int allU[],
                  int allV[],int &total,long long W1[25][25],long long &m1,long long &m2,int printonoff)
{
	//settign the seed throught random number genrator for this part 
	// and also warming it up 10 times as instructed 
	long long int state;
	startpart(state,id,5);
	//this first i and j loop check all reserviours genration 
	//if there pass 1 to 100 number to genrator 
	//if the chance is below 40 percent it conenct it to a pipe 
	for(int i=0 ; i<NR ; i++)
	{
	for(int j=i+1 ; j<NR ; j++)
	{
	if(random(state, 1, 100) <= 40)
	{
	//connecting it to a pipe
	A[i][j] = 1;
	A[j][i] = 1;
	}}}
	//in this code block if any reservoir is connected to another before 
	//it mark it true as connected and if not it mark it false and assign value 1
	//
	for(int k=1 ; k<NR ; k++)
	{
	//setting the bool condition to false at starting 
	bool connectb = false;
	for(int l=0 ; l<k ; l++)
	{
	if(A[k][l]==1) //1 means that reservoir is connected to pipe 
	{
	connectb = true;
	}
	else{}
	}
	if(connectb == false)
	{
	A[k - 1][k] = 1; //1 means that reservoir is connected to pipe 
	A[k][k - 1] = 1;
	}
	}
	//setting total so it counts the amount of pipe
    total =0;
    // this m n nested loop scan the matrix genrated uper part of the matrix 
    //if it found any pipe it assign it to allU AND ALLV and total counts it
	for(int m=0 ; m<NR ; m++)
	{
	for(int n=m+1 ; n<NR ; n++)
	{
	if(A[m][n] == 1)
	{
	//saving that which pipe connect to which reservior and saving it all into
	// the list of index total and also increment in total
	allU[total] = m;
	allV[total] = n;
	total++;
	}}}
	//printonoff mean print on or off it only work when it is called my control 
	// if i am printing signatures only print is off so nothing is printed except calculating signature
	if(printonoff==1)
	{
    cout << "pipes\nconnect the reservoirs\n\npipe list " << total << " pipes\n";
    //this loop converts reserviours number into letter A B instructed in assigment
    //and prints the pipe that is connected pairs
    for(int p=0; p<total; p++)
	{
	//printing the connected pairs
    cout<<(char)('A' + allU[p])<<" "<<(char)('A' + allV[p])<<" ";
    }
    cout<<"\n\nmatrix A:\n\n";
    //this loop print the matrix for the reserviours that are connected 
    for(int q=0; q<NR; q++)
	{
    for(int r=0; r<NR; r++)
	{
    cout<<A[q][r]<<" "; // 1 mean connected and 0 mean not connected
    }
    cout<<endl;
    }
    //to find the diaognal of matrix i used helper function i created matrixhelp 
    long long int A2[25][25]={0};//intitilized all elemnts of array to 0 so no garbage value is there
    matrixhelp(NR,A,A,A2);//using the helper function 
    cout<<"\nDiagonal of A^2: ";
    for(int i=0; i<NR; i++) {
    cout<<A2[i][i]<<" ";//printing it 
    }
    cout<<endl;
    }
    //this block calculate A power k matrix steps and matrix multiplications using function
    //i created 
    walkmethod1(NR,K,A,W1,m1);
    walkmethod2(NR, K, A, W1, m2);
    if(printonoff==1)
	{
    cout<<"\n\nMatrix W:\n";
    //this block print the final walk matrix W1 with total multiplication count it took
    //in or from both methods 1 and 2
    for(int s=0; s<NR; s++)
	{
    for(int j = 0; j < NR; j++)
	{
    cout<<W1[s][j]<<"\t";
    }
    cout<<endl;
    }
    //printing the final answers
    cout<<"\n\nmultiplication method 1 = " << m1 << "\nmultiplication method 2 = "<<m2<<endl<<endl;
    }
}

//this is the continued part of print summary of part 5 1 
//=====function 47 part 5:=====
long long int printpart5(long long int id,int NR,long long int K,int printonoff)
{
	//creating all the variables and arrays for matrix pipes walk so we can pass them
	long long int A[25][25]={0},W1[25][25],m1=0,m2=0;
    int allU[100],allV[100],tp=0;
    //passing the array and variables to parint part 5 part 1 so calculate
    //matrix pipes walk results and printing them
    printpart5_1(id,NR,K,A,allU,allV,tp,W1,m1,m2,printonoff);
    //initilizing matrix with 0 so garbage values are avoided 
    long long int matrix[25][25]={0};
    //this loop is the starting part of printing Method 1: determinant (Kirchhoff’s rule)
    //for the NR reserviours 
    for(int i=0 ; i<NR ; i++)
    {
    //setting total to 0 so we can count how many pipe touched resevoir 
    int total=0;
    for(int j=0 ; j<NR ; j++)
    {
    if(A[i][j] ==1)//condition for reserviour touching pipes
    {
    //increment in total which means pipe is touching
    total++;
    if(i!=j)// condition for pipe not touching the reservouir 
    {
    // setting it to -1 which means it is diaognal
    matrix[i][j] = -1;
	}
	}
	//saving the total into the array 
	matrix[i][i] = total;
	}
	}
	long long int subtotal[25][25];
	
	for(int k=0; k<NR-1; k++)
	{//contion NR-1 is used so matrix top left corner can be saved to
	//calculate its determenant
	for(int l=0; l<NR-1; l++)
	{
	//saving the matrix answer or the total answer into final subtotal array
	subtotal[k][l] = matrix[k][l];
    }
	}
	//for finding the determenent and pipe plans intitilizing variables
	//the function call dematrix calculate the determenant of the subtotal matrix 
	long long int call=0,plan=dematrix(NR-1,subtotal,call);
    long long gc=0,planf=0;int gU[25],gV[25]; //gc gv gu mean group checked group u and v and planf mean plan found
    //this function call test all the possible groups of pipes
    //0 0 are passed because we have to search it from index 0 and pipe 0 starting 
    groups(0,0,tp,NR-1,allU,allV,gU,gV,NR,gc,planf);
    //printonoff mean print on or off it only work when it is called my control 
	// if i am printing signatures only print is off so nothing is printed except calculating signature
    if(printonoff==1)
	{
    cout<<"plans by determenant = "<<plan<< "\ndeteremenat call: "<<call<< "\n";
    cout<<"plans by group testing = "<<planf<<"\ngroups check: "<<gc<<endl;
    }
    long long int S=calculatesig5(NR,tp,allU,allV,W1,m1,m2,plan,call,gc,planf);
	return S;

}








//                                ================================== PART 5 END HERE ==================================








//in array/0 means there are no more elements further so stop scaning array

//=====function 48 part 6:=====
int textlength(char word[])
{
	int n=0;
	while (word[n] != '\0') //condition \0 which tells to stop scaning the array
	{
	n++;
	}
	return n;
}


//this function copy the text into array 1 to array 2 and put \0 which means stop
//or there are no more elements in the array and counts how many characters were there

//=====function 49 part 6:=====
void copytext(char from[],char to[])
{
	int a=0;
	while (from[a] != '\0')
	{ 
	to[a] = from[a];
	a++;
	}
	to[a] = '\0';
}



//this is very important function becuase user can enter both capital and small 
//letter so to tackle bth this function convert small leters to large
//so both are valid 

//=====function 50 part 6:=====
void capital(char word[])
{
	//ASCIIvalue of small a is 97 and capital A is 65
	// \0 tells that this array end stop
	for(int i=0; word[i] != '\0'; i++)
	{
	if (word[i] >= 'a' && word[i] <= 'z')
	{
	//subtracting 32 because the diffrence between small letters ASCII and capital is 
	//32 so subtracting 32 makes every character capital
	word[i] = word[i] - 32;
	}
	}
}

 //this function is very important becuase if user enter find op-998 these both things have to be
 //sepreted and stored into a new 2d array with op in one place and 998 in another array
 
//=====function 51 part 6:=====
int comparetext(char a[],char b[])
{
	int i=0;
	while (a[i] != '\0' && b[i] != '\0')
	{
	if(a[i] != b[i])
	return (a[i] < b[i]) ? -1 : 1 ;
	i++;
	}
	//if both are same then it return 0 which means they are same 
	//every character ASCII value is comapred and returned
	//if no command matches it return -1 
	return (a[i] == b[i]) ? 0 : (a[i] == '\0' ? -1 : 1);
}


//this function is very important becuase if user enter find op 998 these both things have to be
//seperated and stored into a new 2d array with op in one place and 998 in another array
 
//=====function 52 part 6:=====
int splitword(char line[],char word[][30])
{
	//word [][30] mean 30 character can fit in it 
	int c = 0,k = 0;
	for (int i=0; line[i] != '\0'; i++)
	{
	//if there is a space or tab space it set the line to \0 stop
	if (line[i] == ' ' || line[i] == '\t')
	{
	if (k>0)
	{
	word[c][k] = '\0';
	c++;//increment in c which tells to move to next row c mean row and also 
	//it counts how many words were in that line 
	k=0;//setting k to 0 so on next row the character is checked from index 0 start 
	}
	}
	//if any other character are in the line or row with in the limit of 29 characters 
	//else if block runs
	else if (k < 29)
	{
	word[c][k] = line[i];
	k++; //increment in k so index move forward 1 2 3 4 like this
	}
	}
	//if word have no space in it last else condition runs that tells no spaces left
	//mark the array end stop \0
	if (k > 0)
	{
	word[c][k] = '\0';
	c++;
	}
	return c;
}

//this function checks the id if id have more then 9 digits or it have a negative sign 
//it throws error or return -1 else it return the value becuase of split function 
//the id is converted into characters so i have to make a seprate function which check that characters 
//convert it into number and check all conditions

//=====function 53 part 6:=====
long long int textnum(char word[])
{
	int num = textlength(word);
	if (num == 0 || num > 9)
	{
	return -1; // this trows the error
	}
	long long value = 0;
	//checking all characters
	for(int i=0; i<num; i++)
	{
	if (word[i] < '0' || word[i] > '9')
	{
	return -1;// this also throws the error
	}
	//the word come in string like 10 20 30 to convert into actual character we - it from '0' and multiply it by 10
	//and multiply it by 10 add up in value so it come back as the orignal number
	value=value * 10 + (word[i] - '0');
	}
	//at the last the value which is calculated is returned
	return value;
}

//this function makes the sms report KAREZ + id + : + every row of basin map joined by /
//same letters together are written as count and letter (count only if more than 1) like AAAB = 3AB

//this function genrates the sms for respected minister 
//KAREZ + your 6-digit ID (with zeros on the left) + : + the rows of the
//basin map joined by /

//=====function 54 part 6:=====
void makingsms(long long id,int R,int C,char bmap[][25],char report[])
{
	// to track the on going position we use variable p and 
	//char h[] array store heading karez 
	int p = 0; char h[] = "KAREZ";
	
	//storing the ASCII value of heading karez into report array
	//becauase we have to display it in the start of the message
	for (int i = 0; h[i]; i++)
	{
	report[p] = h[i];
	p++;
	}
	//this loop is for the id if id have less then 6 digits 0 are added automatically
	// then id is stored into report because sms also contain cms id
	for (long long int d=100000 ; d>=1; d=d/10)
	{
	report[p] = '0' + ((id / d) % 10); //it devide it by d so and % 10 same concept to extract the last digit and 
	//if the id is less then 6 digits it automaticcaly add 0 on right and then it store as a character in the array
	p++;
	}
	report[p] = ':';
	p++;
	//now this block of code find scan bmap mean basin map r mean row and c mean coloumn
	for (int r=0; r<R; r++)
	{
	for (int c=0; c<C; c++)
	{
	//run counts how many same letters are coming one after another
	char ch = bmap[r][c];
	
	int run = 1;
	//doncition check weather that the coloumn index is in map or not and
	//does the character match main condition if yes then runn is incremented 
	// the character 
	while(c + run < C && bmap[r][c + run] == ch)
	{
	run++;//counting how many same characters were found
	}
	//if run is greater then 9 or have 2 digits 
	//basically this is also the encoding block 
	if (run >= 10)
	{
	report[p] = '0' + run / 10;
	p++;
	}
	else{}
	//if run is greater then 1 so we will check how many numbers are repeated
	if (run > 1)
	{
	report[p] = '0' + run % 10;//extracting the last digit
	p++;
	}
	else{}
	//saving the code charachter into report index p 
	report[p] = ch;
	//this check that the characters that are already counted are not counted again so -1 decrement it 
	c =c + run - 1;
	p++;
	}
	if (r < R - 1)//checks if the current row is less then the total - 1 rows 
	// '/' tells that this row end here 
	{
	report[p] = '/';// '/' tells that row end here
	p++;
	}
	else{}
	}
	//at the last \0 means stop end of elements in array so messge is completed or ended
	report[p] = '\0';
}

//this function give every command a number so its easy for me in the control function to
//execute other commands and if the word is not in list it return error return 0 unknown command

//=====function 55 part 6:=====
int commandnum(char word[])
{
	//15 is the command parameter list and 12 is the coloumn list each charater occupy 1 coloumn 
	char name[15][12] = {"ID","PARAMS","PEOPLE","SHARE","TANKER","MAP","PIPES","REPORT","FIND","TESTMAP","TESTPIPES","ALL","SIGN","HELP","QUIT"};
	//loop runs 15 times becuase we have 15 commands
	for(int i=0 ; i<15 ; i++)
	{
	//this uses helper function to get the value or number of command
	if(comparetext(word,name[i]) == 0)
	{
	// + 1 is used becuase array start at 0 index so we have to do + 1
	return i+1;
	}
	}
	return 0;
}

//this function perform the decoding on the report that was incoded and also check evert letter with basin map 
//if one letter is diffrtent it become false 
//=====function 56 part 6:=====
bool roundtrip(char report[],int R,int C,char bmap[][25])
{
	//p is used as current index for array
	int p=0,row=0,coloumn=0;
	//setting bool to true
	bool good = true;
	//skipping the heading and : starting after semicolon
	while(report[p] != ':')
	{
	p++; //skipping the heading and semicolon
	}
	p++; //starting after the semicolon
	//checking if the array element havent ended or stop
	while(report[p] != '\0')
	{
	// '/' means row has ended
	if(report[p] == '/')
	{
	row++;
	coloumn=0;
	p++;
	}
	else
	{
	
	//initilizing the count it checks how many times the letter is repeated in a row
	int count=0;
	//checking the the charachter is from the give range 0-9
	while(report[p] >= '0' && report[p] <= '9')
	{
	//count get the number with the letter or character check if that letter really appear 
	//that many times there ot not 
	count = count * 10 + report[p] - '0';
	p++;
	}
	//if no number is there this condition is executed
	if(count == 0)
	{
	count = 1;
	}
	//now checking that count letter really appear on the map or not in the basin map
	for(int k=0 ; k<count ; k++)
	{
	//checking all the condiotion that are prohibitated if even 1 is true so false is returned 
	if(row >= R || coloumn + k >= C || bmap[row][coloumn+k] != report[p]) { good = false; }
	}
	//coloumn have to be increment becasue those letters coloumns have already been checked
	coloumn = coloumn + count;
	p++;
	}
	}
	//at the last it return true
	return good;
}


//this function gives water to every mohalla from the basin it is in
//if the basin has enough water everybody gets full demand and if not policy B shares it inside that basin
//delivered, left and cut are passed by reference to send the answers back

//this function distributes the water from basin to mohallas if there is enough water in 
//basin if there is not then it uses part 2 policy B equally distribute water 

//=====function 57 part 6:=====
void supply(int N,int R,int C,int numb,char bname[],long long bwater[],char bmap[][25],int cell[][25],
            long long row[],long long coloumn[],long long demand[],long long got[],char basin[],
            long long &deliver,long long &left,int &cut)
{
	deliver = 0; left = 0; cut = 0;
	//first finding cell of mohalla and if it is rock mohhala is skip cut and get 0 water
	for(int i=1 ; i<=N ; i++)
	{
	int r = (row[i] * R)/ 100,c = (coloumn[i] * C) / 100;
	got[i] = 0; //setting it so it start fresh no garbage or old value
	if(cell[r][c] == 2){basin[i] = '#'; cut++;} //rock no water skip
	else               {basin[i] = bmap[r][c];}
	}
	//now going basin by basin in name order
	for(int p=0 ; p<numb ; p++)//moving through each basin 
	{
	int cant = 0, whoarethey[25]; // whoarethey store mohhala number which belong to the basin
	long long d[25],share[25],total = 0; // d store demand share store policyb shareed water 
	
	//this block checks all the mohallas belong the the basin and sum their demand
	for(int j=1 ; j<=N ; j++)
	{
	if(basin[j] == bname[p])
	{
	cant++;
	whoarethey[cant] = j;
	d[cant] = demand[j];
	//suming up the demand of mohhala belong to basin
	total += demand[j];
	}
	}
	
	//if basin have enough water to fullfill all demands so it is used if there are 
	//no mohalals then the basin remain the samea
	if(total <= bwater[p])
	{
	for(int k=1 ; k<=cant ; k++)
	{
	got[whoarethey[k]] = d[k];
	}
	left += bwater[p] - total;
	}
	
	//if there is not enough water then policy B is used water is distributed equally among everyone 
	else
	{
	policyB(cant,bwater[p],total,d,share);
	for(int k=1 ; k<=cant ; k++)
	{
	got[whoarethey[k]] = share[k];
	}
	}
	}
	for(int l=1 ; l<=N ; l++)
	{
	//the water that is distributed is then stored in diliver to get the final total
	deliver += got[l];
	}
}

//this function calculates the signature of part 6 

//=====function 58 part 6:=====
long long int calculatesig6(int N,int length,int sms,long long int hash,
                            char basin[],long long int got[],long long int deliver,long long int left)
{
	//this block of code calculates the signature p6
	long long int S = 0;
	Sig(S,length);
	Sig(S,sms);
	Sig(S,hash);
	for(int i=1 ; i<=N ; i++) {Sig(S,(int)basin[i]); Sig(S,got[i]);}
	Sig(S,deliver);
	Sig(S,left);
	cout<<"P6 SIGNATURE = "<<S<<endl;
	//returns the signature value
	return S;
}

//this function print the part 6 the report hash supply table and total using helper functions

//=====function 59 part 6:=====
long long int part6(long long id,int N,int R,int C,int numb,char bname[],long long bwater[],char bmap[][25],
                int cell[][25],char code[][10],long long row[],long long coloumn[],long long demand[],int printonoff)
{
	char report[700],basin[25];
	long long got[25],deliver,left,hash=0,S=0;
	int cut;
	//genrating the sms
	makingsms(id,R,C,bmap,report);
	//calculating the length of the report and sms as mentioned in assigment
	int length = textlength(report),sms = (length + 159) / 160;
	//hash formula mentioned in assigment
	for(int i=0 ; i<length ; i++)
	{
	hash = (hash * 131 + report[i]) % 1000000007;
	}
	//printonoff mean print on or off it only work when it is called my control 
	// if i am printing signatures only print is off so nothing is printed except calculating signature
	if(printonoff==1)
	{
	cout<<"\nPart 6 control room\n"<<report<<"\nLength: "<<length<<" | SMS need: "<<sms<<" | Hash: "<<hash<<endl;
	//checking the round trip calling the function i made earlier helper function
	if(roundtrip(report,R,C,bmap))
	{
	cout<<"ROUND TRIP: OK\n";
	} 
	else
	{
	cout<<"ROUND TRIP: FAILED\n";
	}
	}
	//checking the supply using supply helper function
	supply(N,R,C,numb,bname,bwater,bmap,cell,row,coloumn,demand,got,basin,deliver,left,cut);
	// now at the last printing the table required in assigment 
	if(printonoff==1)
	{
	for(int i=1 ; i<=N ; i++)
	{
	cout<<i<<" | "<<code[i]<<" | "<<basin[i]<<" | "<<demand[i]<<" | "<<got[i]<<" | "<<got[i]*100/demand[i]<<"%\n";
	}
	cout<<"Delivered: "<<deliver<<"L | Cut off: "<<cut<<" | Water that is left: "<<left<<"L\n";
	}
	//sig
	S=calculatesig6(N,length,sms,hash,basin,got,deliver,left);
	return S;
}



//this function find the mohalla by code if user enter find gh-012 and also counts the comparisons 
//it finds and do comparisons using linier searching 

//=====function 60 part 6:=====
void findmohala(int N,char code[][10],char wantwater[])
{
	char text[30];
	int comp = 0, found = 0;
	copytext(wantwater,text);//copying text
	capital(text);//convertign the text to capital 
	
	//linier search loop
	for(int i=1 ; i<=N && found==0 ; i++)
	{
	comp++; //comaprison variable
	if(comparetext(code[i],text) == 0) //if it matches then it is marked as found
	{
	found = i;
	}
	}
	//now based on evaluation the result are shown
	if(found > 0){cout<<"Find "<<wantwater<<" finds mohala "<<found<<" with "<<comp<<" comparison done\n";}
	else         {cout<<"Find "<<wantwater<<" not found ("<<comp<<" comparison)\n";}
}

//this function is for testing the small height , map , row and coloumn without
//wells rock and rain

//=====function 61 part 6:=====
void testmap(int r,int c,int DIR)
{
	int h[25][25], cell[25][25]={0}, rain[25][25]={0}, memR[25][25], memC[25][25];
	int sinkR[60], sinkC[60], bcell[60], numb = 0;
	char bmap[25][25], bname[60], line[101], w[51][30];
	long long int bwater[60]={0}, cmem = 0, cnomem = 0;

	//reading the rown of the height
	for(int i=0; i<r; i++)
	{
	//cin get line is used for input reading whole row and 101 is used because it also read the last character \0
	//as mentioned in assigment
	cin.getline(line,101);
	splitword(line,w);//after reading the word spliting them and storing them into 2d array
	//filing up the rows of height map
	for(int j=0; j<c; j++)
	{
	h[i][j] = textnum(w[j]);
	//it mark every cell of row and coloumn as not marked which shows that every cell sink is not checked
	memR[i][j] = -1;
	memC[i][j] = -1;
	}
	}	
	//finding the sink without memory
	for(int i=0; i<r; i++)
	{
	for(int j=0; j<c; j++)
	{
	int sr1,sc1,sr2,sc2; //sr1 sc1 mean sink row 1 sink coloumn 1
	findsink1(i,j,r,c,DIR,h,cell,memR,memC,sr1,sc1,cmem);
	findsink2(i,j,r,c,DIR,h,cell,sr2,sc2,cnomem);
	}
	}
	//based on the cells flow and water making basins
	makebasins(r,c,h,cell,rain,memR,memC,bmap,numb,bname,sinkR,sinkC,bcell,bwater);
	
	//after making basins with all new computed values making the flow map of that 
	cout<<"Flow map:\n";
	for(int i=0; i<r; i++)
	{
	for(int j=0; j<c; j++)
	{
	int nr,nc;
	char flow;
	nextcell(i,j,r,c,DIR,h,cell,nr,nc,flow);
	cout<<flow<<" ";
	}
	cout<<endl;
	}
	//after flow map basin map 
	cout<<"Basin map:\n";
	for(int i=0; i<r; i++)
	{
	for(int j=0; j<c; j++)
	{
	cout << bmap[i][j] << " ";
	}
	cout<<endl;
	}
	for(int m=0; m<numb; m++)
	{
	cout<<bname[m]<<" | "<< sinkR[m]<<","<<sinkC[m]<<" | h="<<h[sinkR[m]][sinkC[m]]<<" | cells="<<bcell[m]<<endl;
	}
	//printing the amount of calls with memory and without memory
	cout<<"Calls: "<<cmem<<" with memory, "<<cnomem<<" without memory\n";
}



//this function test the pipe making or its connection with specific number of 
//eserviours and specific number of pipes n,m

//=====function 62 part 6:=====
void testpipes(int n, int m)
{
	long long int A[25][25]={0},L[25][25]={0},sub[25][25]={0},call=0,gc=0,planf=0;
	int allU[100],allV[100],gU[25],gV[25],tp=0;
	char line[101],w[51][30];

	//reading the pipes
	for(int i=0; i<m; i++)
	{
	//input cin get line as given in assigment	
	cin.getline(line,101);
	splitword(line,w);//spliting it
	capital(w[0]);//capitilizing it 
	capital(w[1]);
	
	//the reserviours letters are already converted to capital 
	int u = w[0][0] - 'A'; //converting reserviours letters A B into numbers using ASCII
	int v = w[1][0] - 'A'; //converting reserviours letters A B into numbers using ASCII
	
	//show that the pipe from u to v is connected and v to u back is also connected
	A[u][v] = 1;
	A[v][u] = 1;
	//now pipes are stored in total pipes 
	allU[tp] = u;
	allV[tp] = v;
	tp++;//tp mean total pipes
	}

	//building the matrix if pipes
	//pipe connection and building the matrix
	for(int i=0; i<n; i++)
	{
	//setting the total so it start fresh
	int total=0;
	for(int j=0; j<n; j++)
	{
	if(A[i][j] == 1)//checking if the direct pipe connecteion is avaliable or not
	{
	total++;//increment pipe count
	if(i != j)//if direct pipe connection is not avalible 
	{
	L[i][j] = -1;//setting the connection -1 which show it doesnt meet
	}
	}
	}
	L[i][i] = total; //it saves the total number of connected pipes of matrix to reserviours into total
	}
	
	//calculating the submatrix from L to sub 
	for(int i=0; i<n-1; i++)
	{
	for(int j=0; j<n-1; j++)
	{
	sub[i][j] = L[i][j];
	}
	}

	//at the end it print everything all the plans it found how many 
	//calls it took and how many plans by group testing with count
	long long int plan = dematrix(n - 1, sub, call);
	groups(0,0,tp,n - 1,allU,allV,gU,gV,n,gc,planf);
	cout<<"Plans by determinant = "<<plan<<" (calls: "<< call << ")\n";
	cout<<"Plans by group testing = "<<planf<<" (groups checked: "<< gc<<")"<<endl;
}

//this is the control room 1 this is the basically 3rd part of the main control room because 
//control room was excedding the limit of 50 lines so i broke it down into 3 sub parts this is part 1
//with case for command sign quit and help

//=====function 63 part 6:=====
void controlroom3(int command,bool &going,long long int &id,int &N,int &PCT,int &VAR,int &M,long long int &Q,
             int &R,int &C,int &SM,int &DIR,int &KW,int &KB,int &NR,int &K,
             long long int &totaldem,long long int &V,char type[],char code[][10],
             long long int size[],long long int row[],long long int col[],
             long long int demand[],long long int order[],long long int allA[],
             long long int allB[],long long int allC[],int cell[][25],
             char bmap[][25],char bname[],int &numb,long long int bwater[])
{
	switch(command)
	{
	//in switch case 13 it runs the command sign becuase i made signature functions sepretly but they 
	//still use all the calculations from the print part thats why it set print to off so nothing is printed
	//and only calculation is used to get the signatures
	case 13:
	{
	//p0
	long long int p0 = calculatesig(N,PCT,VAR,M,Q,R,C,SM,DIR,KW,KB,NR,K);
	//p1
	long long int p1 = calculatesig1(N,type,size,code,row,col,demand,totaldem);
	
	cout<<"P0 SIGNATURE = "<<p0<<endl; //p0 signature didnt  neeeded print on off so i printed it directly 
	cout<<"P1 SIGNATURE = "<<p1<<endl; //p1 signature didnt  neeeded print on off so i printed it directly
	
	long long int p2 = printpart2(N,V,order,demand,allA,allB,allC,0); //printing signature of part 2
	long long int p3 = printpart3(id,M,Q,0); //printing signature of part 3
	long long int p4 = printPart4(id,R,C,DIR,SM,KW,KB,cell,bmap,bname,numb,bwater,0); //printing signature of part 4
	long long int p5 = printpart5(id,NR,K,0); //printing signature of part 2
	long long int p6 = part6(id,N,R,C,numb,bname,bwater,bmap,cell,code,row,col,demand,0); //printing signature of part 6
	//initilizing final to zero because we have to calculate the final signature
	long long int final = 0;
	
	//final is the final signature which takes all signatures sum it up uses hash formulla 
	//convert into a small number and its the final signature of everything 
	Sig(final,p0); //signature of part 0
	Sig(final,p1); //signature of part 1
	Sig(final,p2); //signature of part 2
	Sig(final,p3); //signature of part 3
	Sig(final,p4); //signature of part 4
	Sig(final,p5); //signature of part 5
	Sig(final,p6); //signature of part 6
	cout<<"FINAL = "<<final<<endl;
	}
	break;
	//this is the switch for command help which tells all the command user can use
	case 14:
	cout<<"ID PARAMS PEOPLE SHARE TANKER MAP PIPES REPORT FIND TESTMAP TESTPIPES ALL SIGN HELP QUIT\n";
	break;
	//this is the quit command which sset going to false so program quit terminate stop
	case 15:
	going = false;
	break;
	}
}

//this is the part 2 of control room sub part 2 of main control room 
//in this function commands like MAP REPORT TESTMAP TESTPIPES and ALL are deal
//and also if values are wrong error is printed

//=====function 64 part 6:=====
void controlroom2(int command,int count,char word[][30],long long int &id,int &N,int &PCT,
			 int &VAR,int &M,long long int &Q,
             int &R,int &C,int &SM,int &DIR,int &KW,int &KB,int &NR,int &K,
             long long int &totaldem,long long int &V,char type[],char code[][10],
             long long int size[],long long int row[],long long int col[],
             long long int demand[],long long int order[],long long int allA[],
             long long int allB[],long long int allC[],int cell[][25],
             char bmap[][25],char bname[],int &numb,long long int bwater[])
             
{
	switch(command)
	{
	//this is the case for command MAP or map it set the print to on '1' too so everything print
	case 6:
	printPart4(id,R,C,DIR,SM,KW,KB,cell,bmap,bname,numb,bwater,1);break;//1 mean print on
	
	//this case is for pipes which check reserviourrs pipe connection and steps and all valid plans
	//by determenant method and also print its result signature
	case 7:
	printpart5(id,NR,K,1);break;//1 mean print on
	
	//this case is for the command REPORT for respected minister with print '1' on verify it with 
	//roundtrip function that everything is ok and there is no loss in any data and distribute the water 
	//from the basin or using policy B and print SMS message
	case 8:
	//calling print 4 becuase we also need to print basin map and basin report
	printPart4(id,R,C,DIR,SM,KW,KB,cell,bmap,bname,numb,bwater,2);
	part6(id,N,R,C,numb,bname,bwater,bmap,cell,code,row,col,demand,1); break;
	
	//this case is for command find this mohalla if command is wrong error is printed 
	//and if command is correct findmohalla function is used to find that mohalla and print it
	case 9:
	if(count < 2)
	{
	cout<<"ERROR: missing value"<<endl;
	}else{
	findmohala(N,code,word[1]);}break;
	
	//this case is for the TESTMAP command it check wather the value are correct or not then 
	//read the height grid of the map and print its basin flow map with call count
	case 10:
	if(count < 3) //testmap have 3 parts 'TESTMAP 2 3' so count should be greater then 3
	{
	cout<<"ERROR: missing value"<<endl;
	}
	else if(textnum(word[1]) < 0 || textnum(word[2]) < 0) // if the value is in negative
	{
	cout<<"ERROR: bad number"<<endl;
	}
	else
	{ 
	testmap(textnum(word[1]),textnum(word[2]),DIR);
	}
	break;
	
	//this case is for command test pipes 
	case 11:
	if(count < 3)// testpies should also contain 3 values like 'testpipe A B'
	{
	cout<<"ERROR: missing value"<<endl;
	}
	else if(textnum(word[1]) < 0 || textnum(word[2]) < 0)//checking the values are not in negative
	{
	cout<<"ERROR: bad number"<<endl;//error
	}
	else {	
	testpipes(textnum(word[1]),textnum(word[2]));}break;
	
	//this case is for the command ALL prints everything from START TO END with signatures printing on 
	case 12:
	{
	long long int p0 = calculatesig(N,PCT,VAR,M,Q,R,C,SM,DIR,KW,KB,NR,K);//calling p0 signature storing it in p0
	long long int p1 = calculatesig1(N,type,size,code,row,col,demand,totaldem);//calling p1 signature storing it in p1
	
	cout<<"N="<<N<<" PCT="<<PCT<<" VAR="<<VAR<<" M="<<M<<" Q="<<Q<<" R="<<R<<" C="<<C
	<<" SM="<<SM<<" DIR="<<DIR<<" KW="<<KW<<" KB="<<KB<<" NR="<<NR<<" K="<<K<<endl;
	
	cout<<"P0 SIGNATURE = "<<p0<<endl;
	summary(N,type,size,code,row,col,demand,totaldem); //print part 1 summary 
	cout<<"P1 SIGNATURE = "<<p1<<endl;
	
	long long int p2 = printpart2(N,V,order,demand,allA,allB,allC,1); //calling function print part 2 storing it in p2
	long long int p3 = printpart3(id,M,Q,1);//calling function print part 3 storing it in p3
	long long int p4 = printPart4(id,R,C,DIR,SM,KW,KB,cell,bmap,bname,numb,bwater,1);//calling function print part 4 storing it in p4
	long long int p5 = printpart5(id,NR,K,1);//calling function print part 5 storing it in p5
	long long int p6 = part6(id,N,R,C,numb,bname,bwater,bmap,cell,code,row,col,demand,1);//calling function print part 6 storing it in p6
	
	//to calculate the final signature
	long long int final = 0;
	//calculataing final signature from all part signature and using hash formulla on it
	Sig(final,p0);Sig(final,p1);
	Sig(final,p2);Sig(final,p3);Sig(final,p4);Sig(final,p5);Sig(final,p6);
	cout<<"FINAL = "<<final<<endl;}break;
	}
	
}




//this is the control room main part of whole code it reades command 1 command at a time perform action on it according to
//asigment and print it do calculating

//=====function 65 part 6:=====
void control(long long int &id,int &N,int &PCT,int &VAR,int &M,long long int &Q,
             int &R,int &C,int &SM,int &DIR,int &KW,int &KB,int &NR,int &K,
             long long int &totaldem,long long int &V,char type[],char code[][10],
             long long int size[],long long int row[],long long int col[],
             long long int demand[],long long int order[],long long int allA[],
             long long int allB[],long long int allC[],int cell[][25],
             char bmap[][25],char bname[],int &numb,long long int bwater[])
{
	//main part where length of sms words id and going are initilized
	char line[101],word[51][30];
	bool setid=false,going=true;
	
	//cin get line is used for input reading whole row and 101 is used because it also read the last character \0
	//as mentioned in assigment
	while(going && cin.getline(line,101))
	{
	cout<<">> "<<line<<endl;
	//breaking or spliting the length and storing it into 2d array
	int count = splitword(line,word);
	
	//ignoring the empty lines
	if(count == 0){continue;}
	//converting the word to capital letter
	capital(word[0]);
	
	//this is the main block which look at the command convert it into number 
	//so that command switch case is executed
	int command = commandnum(word[0]);
	if(command == 0)
	{
	cout<<"ERROR: unknown command"<<endl;
	}

	//before anything only command id and quit can work so
	else if(setid==false && command != 1 && command != 14 && command != 15)
	{
	cout<<"ERROR: give ID first"<<endl; //executing any other command give this error
	}
	else
	{
		
	//the main block from where all case are executed based on user command selecteion	
	switch(command)
	{
	//this case check user id input 
	case 1:
	if(count < 2){cout<<"ERROR: missing value"<<endl;}
	else
	{
	//converting the id into numberss becuse cin gen line read it as a character
	id = textnum(word[1]);
	//if it contain negative numbers  it throw and error
	if(id < 0)
	{
	cout<<"ERROR: bad number"<<endl;//error
	}
	//if it contain more digit then 6 it give the error
	else if(id > 999999)
	{
	cout<<"ERROR: ID must be from 0 to 999999"<<endl;//error
	}
	//the main block 
	//when the correct id is enter this block execute it calculate all the parameters 
	//genrate mohalla codes and everything from part 1 to 2
	else
	{
	setid = true;
	calparameters(id,N,PCT,VAR,M,Q,R,C,SM,DIR,KW,KB,NR,K); //calculating parameters
	long long int state = 0;
	startpart(state,id,1);//warming up the genrator 10 times
	checkdup(N,state,type,code,size,row,col,demand,totaldem,order,allA,allB,allC);//checking code duplicate
	V = (totaldem * PCT) / 100;
	policyA(N,VAR,V,type,demand,order,allA); //part 2 policy A
	policyB(N,V,totaldem,demand,allB); //part 2 policy B
	policyC(N,V,type,demand,allC); //part 2 policy C
	//parameters and signature as required in 8.1 assigment
	cout<<"N="<<N<<" PCT="<<PCT<<" VAR="<<VAR<<" M="<<M<<" Q="<<Q<<" R="<<R<<" C="<<C<<
	" SM="<<SM<<" DIR="<<DIR<<" KW="<<KW<<" KB="<<KB<<" NR="<<NR<<" K="<<K<<endl;
	cout<<"P0 SIGNATURE = "<<calculatesig(N,PCT,VAR,M,Q,R,C,SM,DIR,KW,KB,NR,K)<<endl;
	}  
	}break;
	
	//this case print all the parameters calculatedwith p0 signature
	case 2:
	cout<<"N="<<N<<" PCT="<<PCT<<" VAR="<<VAR<<" M="<<M<<" Q="<<Q<<" R="<<R<<" C="<<C<<
	" SM="<<SM<<" DIR="<<DIR<<" KW="<<KW<<" KB="<<KB<<" NR="<<NR<<" K="<<K<<endl;
	cout<<"P0 SIGNATURE = "<<calculatesig(N,PCT,VAR,M,Q,R,C,SM,DIR,KW,KB,NR,K)<<endl;break;
	
	//this part genrate the mohalla summary and detials table with p1 signature
	case 3: 
	summary(N,type,size,code,row,col,demand,totaldem);
	cout<<"P1 SIGNATURE = "<<calculatesig1(N,type,size,code,row,col,demand,totaldem)<<endl;break; 
	
	//this part run on command SHARE which call part 2 to display it	
	case 4:
	printpart2(N,V,order,demand,allA,allB,allC,1);break;
	
	//this case is for command TANKERS with print 1 so print 5 is printed
	case 5:
	printpart3(id,M,Q,1);break;
	
	//becuase i devided the main control room into 2 more sub parts so in default case those functions are called and the matching command is printed
	default:
	controlroom2(command,count,word,id,N,PCT,VAR,M,Q,R,C,SM,DIR,KW,KB,NR,K,totaldem,V,type,code,size,row,col,demand,order,allA,allB,allC,cell,bmap,bname,numb,bwater);
	controlroom3(command,going,id,N,PCT,VAR,M,Q,R,C,SM,DIR,KW,KB,NR,K,totaldem,V,type,code,size,row,col,demand,order,allA,allB,allC,cell,bmap,bname,numb,bwater);break;	
	}
	}
	}
}








//                                ================================== PART 6 END HERE ==================================









int main()
{
	//printing my name and my cms id as instructed in the assigment
	cout<<"KAREZ-26 by muhammad saim ayub, CMS ID 620510\n"<<endl;
	//initilizing all the variables i will need in whole assigment here
	int N,PCT,VAR,M,R,C,SM,DIR,KW,KB,NR,K;
	long long int id=0,Q,totaldem = 0,V = 0,demand[25],order[25],allA[25],allB[25],allC[25];
	int numb = 0, cell[25][25]={0};
	long long int bwater[60]={0},size[25]={0},row[25]={0},col[25]={0};
	char type[25],bmap[25][25],bname[60],code[25][10];
	//passing everything in control becuase other parts are called from control room 
	control(id,N,PCT,VAR,M,Q,R,C,SM,DIR,KW,KB,NR,K,totaldem,V,type,code,size,row,col,demand,order,allA,allB,allC,cell,bmap,bname,numb,bwater);
	return 0;
}
