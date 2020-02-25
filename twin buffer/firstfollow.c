#include "parsedef.h"

void Parse_Table_create(grammar G, table T)		//Function which generated the two dimensional parse table T for the given grammar G
{
int i,j,s=0,t,current_T,firstset_iterator,k;
//printf("here");


for(i=0;i<MAX_NT_NO;i++)				//Initializing all cell values to -1 to denote that no rule has been used in production
for(j=0;j<MAX_TER_NO;j++)
T[i][j]=-1;

//printf("here");


for(i=0;i<MAX_NT_NO;i++)				//Iterating for each non-terminal, finding its column where a production rule has to be inserted
for(j=0;j<NO_OF_RULES;j++)				//Finds all rules corresponding a particular non-terminal

if(G[j][0].state==i)
{

	if(1000<=G[j][1].state && G[j][1].state<=1060) {		//If the first RHS production is a terminal
		T[i][G[j][1].state-1000]=j;	//Assign in the corr. cell, the current rule to obtain the given terminal
		if(first[i].head == NULL){
			first_Follow_node * start = (first_Follow_node*)malloc(sizeof(first_Follow_node));
			start.token = G[j][1];
			start.next = NULL;
			first[i].head = start;
			first[i].size++;
		}
		//break;
	}
	if(G[j][1].state==1100) {			//for epsilon which is the 60th column in the parse table
		T[i][59]=j;
		//break;
		}
	//printf("here");
	firstset_iterator=0;						//firstset_iterator iterates over all the row entries in a terminal's first set
	int followset_var=0;
	while(firstSet[i][firstset_iterator]!=-100)			//-100 denotes that the first set has read its last value
	{
		current_T=firstSet[i][firstset_iterator];
		if(current_T==1100)				//used to switch to the followSet of non-terminal in question checking loop
			followset_var=1;
		k=0;
		int epsilon=0;				//used to switch to the followSet of the RHS non-terminal in production's checking loop
		if(0<=G[j][1].state && G[j][1].state<=56)
		{



				while(firstSet[G[j][1].state][k]!=-100)
			{


				if(firstSet[G[j][1].state][k]==1100)
					{

					epsilon=1;
					}
				if(firstSet[G[j][1].state][k]==current_T)
					{
					T[i][current_T-1000]=j;		//j stands for the current rule number of the grammar table G
					break;
					}
				k++;
			}

		if(epsilon==1)				//checking followSet of the RHS in production non-terminal
		{
		k=0;
		while(followSet[G[j][1].state][k]!=-100)
			{
				if(followSet[G[j][1].state][k]==current_T)
					{
					if(k==1)
					//printf("%d",current_T);
					T[i][current_T-1000]=j;
					break;
					}
				k++;
			}
		}
		}

	firstset_iterator++;
	}
	if(followset_var==1)			//if epsilon is present in the firstSet of the non-terminal in question
	{
		firstset_iterator=0;
	while(followSet[i][firstset_iterator]!=-100)
	{
		current_T=followSet[i][firstset_iterator];
		  if(followSet[i][firstset_iterator]==1060)
               break;
               //current_T=followSet[i][firstset_iterator];
               T[i][current_T-1000]=j;		//assigning rule numbers for all epsilon productions
	firstset_iterator++;
	}
	}
	}
}