//BATCH NUMBER 49
//RANGA SRIRAM 2017A7PS0047P
//RAYAPATI YASWANTH KUMAR 2017A7PS0038P
//KATTA SIVA KUMAR 2017A7A7PS0078P

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "parser.h"

//Initializing Hash Table

char * program;
char * dollar;
int tokenCount;
int tokensTraversed;
tokenInfo temp_Token;

void initializeHTable(){
	int i;
	int j;
	for(i = 0; i < MAX_NT_NO; i++){
		for(j = 0; j < 2; j++){
			hash_table[i][j] = 0;
			//Hash Table has the values of occupancy and hash value(State of nonterminal)
		}
	}
}

void parserInitialize(){
	program = "PROGRAM";
	dollar = "$";
	tokenCount = 0;
	tokensTraversed = 0;
}

//Hash Function

int hash_function(char *key)
{
int hash_val = 0, hash_ret_val = 0;
const int len = strlen(key);
for (int i  =  0; i < len;i += 1)
{
	hash_val = hash_val*i + key[i];
	hash_val = hash_val % 10000;
}
	//printf("%d %s\n", hash_val, key);

hash_ret_val = hash_val % MAX_NT_NO;
	//printf("%d %s\n", hash_ret_val, key);

if(hash_table[hash_ret_val][0] == 0) {
	hash_table[hash_ret_val][0] = 1;
	hash_table[hash_ret_val][1] = hash_val;
}
else
{
	while(hash_table[hash_ret_val][0]!=0)
	{
		//printf("%d %s\n", hash_ret_val, key);

		if (hash_table[hash_ret_val][1] == hash_val) {break;}
		else {
			if(hash_ret_val==MAX_NT_NO-1) hash_ret_val = 0;
			else hash_ret_val++;
		}
		//printf("Looped");
	}
	hash_table[hash_ret_val][0]=1;
	hash_table[hash_ret_val][1]=hash_val;
}
//printf("%d %s\n", hash_ret_val, key);


return hash_ret_val;			//This is the state of nonterminal
}

//Generating Grammar

void grammar_Generator()
{
	int rule=0,i=0,j=0,noOfNT=0,temp;
	tokenInfo token_name;
	char tempName[30] = "";
	char *temp_help = (char*)malloc(150*sizeof(char));

	FILE *fp1;
	fp1=fopen("Reconstructed_grammar.txt","r");	//Grammar is written in the Reconstructed_grammar file
    if(fp1!=NULL){
        //printf("file opened\n");
    }
    else{
        //printf("error in opening\n");
    }

	while (!feof(fp1)) {
	    fgets(temp_help,150,fp1);
        //printf("Printing temphelp:\n");
        int i = 0;
		// printf("here\n");
        // while(temp_help[i]!='\0'){       //prints the rule
        //     printf("%c", temp_help[i]);
        //     i++;
        // }
        // printf("\n");
		if (rule != -1) {
            for (temp = noOfNT; temp < MAX_RIGHTSIDE; temp++) {
                GR[rule][temp].state = -100;
            }
            //printf("Initialized one line of grammar to -100\n");
        }
        
		
		i = 0;
		noOfNT = 0;

		while (temp_help[i] != '\n' && temp_help[i] != '\0') {
		    //printf("%c\n", temp_help[i]);
		    //printf("%s\n", tempName);

		    for (j = 0; j < 30; j++) 
                tempName[j] = '\0';
		    //Initializing tempName to capture names of nonterminals

		    while (temp_help[i] == ' ' || temp_help[i] == '\t') {
		        i++;
			}

		if(temp_help[i]=='|') {
		    //printf("Encountered OR with i = %d\n", i);
			i++;
			rule++;

			while (temp_help[i] == ' ' || temp_help[i] == '\t') {
		        i++;
			}

			for (temp = noOfNT; temp < MAX_RIGHTSIDE; temp++) {
				GR[rule][temp].state = -100;
				}

			noOfNT = 1;
			GR[rule][0]=GR[rule-1][0];
			continue;
								}

		if (temp_help[i]=='<') {
			//printf("Encountered < at i:%d\n", i);
			i++;
			j = 0;
			while(temp_help[i]!='>') {
				tempName[j++]=temp_help[i];
				i++;
			    //printf("%c", tempName[j-1]);
			}
            //printf("\nCaptured token in tempName\n");
			i++;

            while(temp_help[i]=='-' || temp_help[i] == '>' || temp_help[i] == ' ' || temp_help[i]=='\t'){
                i++;
            }
            //printf("%s",tempName);

            strcpy(token_name.name,tempName);
            token_name.state=hash_function(tempName);
            GR[rule][noOfNT] = token_name;
            //printf("%s\n", GR[rule][noOfNT].state);
            noOfNT++;
            continue;
		}

		j = 0;

		if (temp_help[i] == 'e') {
			strcpy(token_name.name, "e");
			token_name.state = 1100;
			GR[rule][noOfNT]=token_name;
			noOfNT++;
			i++;
			continue;
		}

		if((temp_help[i]>='A' && temp_help[i] <= 'Z' )||(temp_help[i]>='a' && temp_help[i] <= 'z' ) || temp_help[i]=='_') {
			while ((temp_help[i]>='A' && temp_help[i] <= 'Z' )||(temp_help[i]>='a' && temp_help[i] <= 'z' ) || temp_help[i]=='_') {
                tempName[j] = temp_help[i];
                //printf("%c", temp_help[i]);
                j++;
                i++;
			}
		    //printf("%s", tempName);
			if(strcmp(tempName,"INTEGER")==0) { strcpy(token_name.name , "INTEGER"); token_name.state=	1000	;}
			if(strcmp(tempName,"REAL")==0) { strcpy(token_name.name,"REAL"); token_name.state=	1001	;}
			if(strcmp(tempName,"BOOLEAN")==0) { strcpy(token_name.name,"BOOLEAN"); token_name.state=	1002	;}
			if(strcmp(tempName,"OF")==0) { strcpy(token_name.name,"OF"); token_name.state=	1003	;}
			if(strcmp(tempName,"ARRAY")==0) { strcpy(token_name.name,"ARRAY"); token_name.state=	1004	;}
			if(strcmp(tempName,"START")==0) { strcpy(token_name.name,"START"); token_name.state=	1005	;}
			if(strcmp(tempName,"END")==0) { strcpy(token_name.name,"END"); token_name.state=	1006	;}
			if(strcmp(tempName,"DECLARE")==0) { strcpy(token_name.name,"DECLARE"); token_name.state=	1007	;}
			if(strcmp(tempName,"MODULE")==0) { strcpy(token_name.name,"MODULE"); token_name.state=	1008	;}
			if(strcmp(tempName,"DRIVER")==0) { strcpy(token_name.name,"DRIVER"); token_name.state=	1009	;}
			if(strcmp(tempName,"PROGRAM")==0) { strcpy(token_name.name,"PROGRAM"); token_name.state=	1010	;}
			//if(strcmp(tempName,"RECORD")==0) { strcpy(token_name.name,"RECORD"); token_name.state=	1011	;}
			//if(strcmp(tempName,"TAGGED")==0) { strcpy(token_name.name,"TAGGED"); token_name.state=	1012	;}
			//if(strcmp(tempName,"UNION")==0) { strcpy(token_name.name,"UNION"); token_name.state=	1013	;}
			if(strcmp(tempName,"GET_VALUE")==0) { strcpy(token_name.name,"GET_VALUE"); token_name.state=	1014	;}
			if(strcmp(tempName,"PRINT")==0) { strcpy(token_name.name,"PRINT"); token_name.state=	1015	;}
			if(strcmp(tempName,"USE")==0) { strcpy(token_name.name,"USE"); token_name.state=	1016	;}
			if(strcmp(tempName,"WITH")==0) { strcpy(token_name.name,"WITH"); token_name.state=	1017	;}
			if(strcmp(tempName,"PARAMETERS")==0) { strcpy(token_name.name,"PARAMETERS"); token_name.state=	1018	;}
			if(strcmp(tempName,"TRUE")==0) { strcpy(token_name.name,"TRUE"); token_name.state=	1019	;}
			if(strcmp(tempName,"FALSE")==0) { strcpy(token_name.name,"FALSE"); token_name.state=	1020	;}
			if(strcmp(tempName,"TAKES")==0) { strcpy(token_name.name,"TAKES"); token_name.state=	1021	;}
			if(strcmp(tempName,"INPUT")==0) { strcpy(token_name.name,"INPUT"); token_name.state=	1022	;}
			if(strcmp(tempName,"RETURNS")==0) { strcpy(token_name.name,"RETURNS"); token_name.state=	1023	;}
			if(strcmp(tempName,"AND")==0) { strcpy(token_name.name,"AND"); token_name.state=	1024	;}
			if(strcmp(tempName,"OR")==0) { strcpy(token_name.name,"OR"); token_name.state=	1025	;}
			if(strcmp(tempName,"FOR")==0) { strcpy(token_name.name,"FOR"); token_name.state=	1026	;}
			if(strcmp(tempName,"IN")==0) { strcpy(token_name.name,"IN"); token_name.state=	1027	;}
			if(strcmp(tempName,"SWITCH")==0) { strcpy(token_name.name,"SWITCH"); token_name.state=	1028	;}
			if(strcmp(tempName,"CASE")==0) { strcpy(token_name.name,"CASE"); token_name.state=	1029	;}
			if(strcmp(tempName,"BREAK")==0) { strcpy(token_name.name,"BREAK"); token_name.state=	1030	;}
			if(strcmp(tempName,"DEFAULT")==0) { strcpy(token_name.name,"DEFAULT"); token_name.state=	1031	;}
			if(strcmp(tempName,"WHILE")==0) { strcpy(token_name.name,"WHILE"); token_name.state=	1032	;}
			if(strcmp(tempName,"PLUS")==0) { strcpy(token_name.name,"PLUS"); token_name.state=	1033	;}
			if(strcmp(tempName,"MINUS")==0) { strcpy(token_name.name,"MINUS"); token_name.state=	1034	;}
			if(strcmp(tempName,"MUL")==0) { strcpy(token_name.name,"MUL"); token_name.state=	1035 ;}
			if(strcmp(tempName,"DIV")==0) { strcpy(token_name.name,"DIV"); token_name.state=	1036	;}
			if(strcmp(tempName,"LT")==0) { strcpy(token_name.name,"LT"); token_name.state=	1037	;}
			if(strcmp(tempName,"LE")==0) { strcpy(token_name.name,"LE"); token_name.state=	1038	;}
			if(strcmp(tempName,"GE")==0) { strcpy(token_name.name,"GE"); token_name.state=	1039	;}
			if(strcmp(tempName,"GT")==0) { strcpy(token_name.name,"GT"); token_name.state=	1040	;}
			if(strcmp(tempName,"EQ")==0) { strcpy(token_name.name,"EQ"); token_name.state=	1041	;}
			if(strcmp(tempName,"NE")==0) { strcpy(token_name.name,"NE"); token_name.state=	1042	;}
			if(strcmp(tempName,"DEF")==0) { strcpy(token_name.name,"DEF"); token_name.state=	1043	;}
			if(strcmp(tempName,"DRIVERDEF")==0) { strcpy(token_name.name,"DRIVERDEF"); token_name.state=	1044	;}
			if(strcmp(tempName,"ENDDEF")==0) { strcpy(token_name.name,"ENDDEF"); token_name.state=	1045	;}
			if(strcmp(tempName,"DRIVERENDDEF")==0) { strcpy(token_name.name,"DRIVERENDDEF"); token_name.state=	1046	;}
			if(strcmp(tempName,"COLON")==0) { strcpy(token_name.name,"COLON"); token_name.state=	1047	;}
			if(strcmp(tempName,"RANGEOP")==0) { strcpy(token_name.name,"RANGEOP"); token_name.state=	1048	;}
			if(strcmp(tempName,"SEMICOL")==0) { strcpy(token_name.name,"SEMICOL"); token_name.state=	1049	;}
			if(strcmp(tempName,"COMMA")==0) { strcpy(token_name.name,"COMMA"); token_name.state=	1050	;}
			if(strcmp(tempName,"ASSIGNOP")==0) { strcpy(token_name.name,"ASSIGNOP"); token_name.state=	1051	;}
			if(strcmp(tempName,"SQBO")==0) { strcpy(token_name.name,"SQBO"); token_name.state=	1052	;}
			if(strcmp(tempName,"SQBC")==0) { strcpy(token_name.name,"SQBC"); token_name.state=	1053	;}
			if(strcmp(tempName,"BO")==0) { strcpy(token_name.name,"BO"); token_name.state=	1054	;}
			if(strcmp(tempName,"BC")==0) { strcpy(token_name.name,"BC"); token_name.state=	1055	;}
			if(strcmp(tempName,"COMMENTMARK")==0) { strcpy(token_name.name,"COMMENTMARK"); token_name.state=	1056	;}
			if(strcmp(tempName,"NUM")==0) { strcpy(token_name.name,"NUM"); token_name.state=	1057	;}
			if(strcmp(tempName,"RNUM")==0) { strcpy(token_name.name,"RNUM"); token_name.state=	1058	;}
			if(strcmp(tempName,"ID")==0) { strcpy(token_name.name,"ID"); token_name.state=	1059	;}
			//printf("%s", token_name.name);
			GR[rule][noOfNT]=token_name;
			noOfNT++;
			continue;
			}
        
		}
        rule++;
	}

    // for (int i=0; i<NO_OF_RULES; i++) {				//prints terminals, nonterminals in rules
    //     printf("Line number %d: ", i);
    //     for (int j=0; j<MAX_RIGHTSIDE; j++) {
    //         if (GR[i][j].state != -100){
    //             printf("%d ", GR[i][j].state);
    //         }
    //     }
    //     printf("\n");
    // }

}

void modifyGrammar(){

	//printf("Modifying grammar\n");
	for (int i=0; i<NO_OF_RULES; i++) {
        for (int j=MAX_RIGHTSIDE-1; j>=0; j--) {
            if (GR[i][j].state == -100 && GR[i][j-1].state == 0){
				GR[i][j-1].state = -100;
            }
        }
    }

	// for (int i=0; i<NO_OF_RULES; i++) {				//prints terminals, nonterminals in rules
    //     printf("Line number %d: ", i);
    //     for (int j=0; j<MAX_RIGHTSIDE; j++) {
    //         if (GR[i][j].state != -100){
    //             printf("%d ", GR[i][j].state);
    //         }
    //     }
    //     printf("\n");
    // }
}

//Create Parse Table

void Parse_Table_create()		//Function which generated the two dimensional parse table T for the given grammar G
{
    //printf("\nInside parse table create function\n");
    int i,j,s=0,t,current_T,firstset_iterator,k;
    //printf("here");

    for(i=0;i<MAX_NT_NO;i++)				//Initializing all cell values to -1 to denote that no rule has been used in production
        for(j=0;j<MAX_TER_NO;j++)
            ptable[i][j]=-1;

    //printf("here");


    for(i=0;i<MAX_NT_NO;i++)				//Iterating for each non-terminal, finding its column where a production rule has to be inserted
        for(j=0;j<NO_OF_RULES;j++){         //Finds all rules corresponding a particular non-terminal
            //printf("state of GR[%d][%d] is %d", i, j, GR[j][i].state);
            if(GR[j][0].state==i){
                if(1000<=GR[j][1].state && GR[j][1].state<=1060) {		//If the first RHS production is a terminal
                    ptable[i][GR[j][1].state-1000]=j;	//Assign in the corr. cell, the current rule to obtain the given terminal
                    //break;
                }
                if(GR[j][1].state==1100) {			//For epsilon which is the 11th column in the parse table
                    ptable[i][11]=j;
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
                    if(0<=GR[j][1].state && GR[j][1].state<=56)
                    {
                        while(firstSet[GR[j][1].state][k]!=-100)
                        {
                            if(firstSet[GR[j][1].state][k]==1100)
                            {
                                epsilon=1;
                            }
                            if(firstSet[GR[j][1].state][k]==current_T)
                            {
                                ptable[i][current_T-1000]=j;		//j stands for the current rule number of the grammar table G
                                break;
                            }
                            k++;
                        }
                        if(epsilon==1)				//checking followSet of the RHS in production non-terminal
                        {
                            k=0;
                            while(followSet[GR[j][1].state][k]!=-100)
                            {
                                if(followSet[GR[j][1].state][k]==current_T)
                                {
                                    if(k==1)
                                    //printf("%d",current_T);
                                    ptable[i][current_T-1000]=j;
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
                        ptable[i][current_T-1000]=j;		//assigning rule numbers for all epsilon productions
                        firstset_iterator++;
                    }
                }
            }
        }				

    //     for(i=0;i<MAX_NT_NO;i++){
    //         for(j=0;j<MAX_TER_NO;j++)
    //             printf("%d ", ptable[i][j]);
    //         printf("\n");
    //     }
    // printf("\nExiting parse table create function\n");
}

void createStack() {
	free(S);
	S = (stack *) malloc(sizeof(stack));
	S->head = NULL;
	// Stack Created
}

void push(tokenInfo t) {
	stackNode *a;
	a = (stackNode *) malloc(sizeof(stackNode));
	a->token = t;

	if (S->head != NULL) {

		if (S->head->next != NULL) {
			a->next = S->head;
			S->head = a;
			//printf("Pushed!")
		}
		else {
			a->next = S->head;
			S->head = a;
		}
	}
	else {

		S->head = a;
		a->next = NULL;
		//printf("Pushed!")
	}
	//printf("%d pushed on to stack\n", t.state);
	//if (S->head != NULL) printf("%dhead", S->head->token.state);
}

tokenInfo pop() {
	tokenInfo t;
	t.name = S->head->token.name;
	t.state = S->head->token.state;
	S->head = S->head->next;
	//printf("Popped!")
	return t;
}



int get_grammar_rule(tokenInfo nonterminal, tokenInfo terminal) {
	if (terminal.state <= 1060) return ptable[nonterminal.state][terminal.state-1000];
	if (terminal.state == 1100) return ptable[nonterminal.state][11];
}


tokenInfo *get_grammar_rule_Row(int n) {
	tokenInfo *p;
	p = GR[n];
	return p;

	// int i;

	// for (i = 1; i < MAX_RIGHTSIDE && p[i].state != -100; i++) {
	// 	if (p[i].state == temp_Token.state) {
	// 		p[i] = temp_Token;
	// 		//printf("%s\n", p[i].content);
	// 	}
	// 	//printf("%d ", p[i].state);
	// }
	// //printf("\n");
	// return p;
}

cqueue *pushQ(parseTreeNode *a, cqueue *q) {
	if (q->head == NULL) {
		a->type = 0;
		q->head = a;
	}
	else {
		a->type = 1;
		q->tail->next = a;
	}
	q->tail = a;
	q->size += 1;
	return q;
}

cqueue *putInChildQ(int ruleNo, parseTreeNode *par) {
	cqueue *a;
	a = (cqueue *) malloc(sizeof(cqueue));
	a->head = NULL;
	a->tail = NULL;
	tokenInfo *t;
	t = get_grammar_rule_Row(ruleNo);
	int i;
	for (i = 1; i < MAX_RIGHTSIDE && t[i].state != -100; i++) {
		parseTreeNode *p;
		p = (parseTreeNode *) malloc(sizeof(parseTreeNode));
		p->token = t[i];
		p->parent = par;
		//p->ASTparent=p->parent;
		//p->member=0;
		//p->type=0;
		a = pushQ(p, a);
		//printf("%s ", p->token.name);
	}
	//printf("inserted under %s\n", par->token.name);
	return a;
}

void parsetreeCreate() {
	PET = (parseTree *) malloc(sizeof(parseTree));
	parseTreeNode *a;
	a = (parseTreeNode *) malloc(sizeof(parseTreeNode));
	a->token = GR[0][0];
	// strcpy(a->token.name, "program");
	// a->token.state = 31;
	a->next = NULL;
	a->parent = NULL;
	a->children = NULL;
	a->type = 0;
	PET->root = a;
	PET->curr = a;
	//insertInTree(0);
}

parseTreeNode *updateCurrentParseTree(parseTreeNode *argcurr) {
	//printf("updateCurr started correctly\n");
	//printf("%s\n curr\n hai\n", argcurr->token.name);
	if (argcurr->children->head->token.state < MAX_NT_NO) {
		//printf("\nOption 1\n");
		//printf("\nExpanding the first occuring nonterminal\n");
		return argcurr->children->head;
	}

	parseTreeNode *parse_iter;
	parse_iter = (parseTreeNode *) malloc(sizeof(parseTreeNode));
	parse_iter = argcurr->children->head;

	while (parse_iter->next != NULL) {
		if (parse_iter->token.state < MAX_NT_NO) {
			//printf("\nOption 2\n");
			//printf("\nExpanding the immmediate non-terminal occured\n");
			return parse_iter;
		}
		else parse_iter = parse_iter->next;
	}

	if (parse_iter->token.state < MAX_NT_NO) {
		//printf("\nOption 3\n");
		//printf("\nchecking the last node of the children cqueue\n");
		return parse_iter;
	}

	if (argcurr->next != NULL) {
		//printf("\nOption 4\n");
		//printf("\nGoing to expand the next nonterminal in the parent node\n");
		parse_iter = argcurr->next;
		while (parse_iter->next != NULL) {
			if (parse_iter->token.state < MAX_NT_NO) {
				//printf("\nOption 2\n");
				return parse_iter;
			}
			else parse_iter = parse_iter->next;
		}
		if (parse_iter->token.state < MAX_NT_NO) {
			//printf("\nOption 3\n");
			//printf("\nChecking the last node of the given cqueue\n");
			return parse_iter;
		}
	}

	if (argcurr->parent != NULL) {
		parseTreeNode *parent_iter;
		parent_iter = (parseTreeNode *) malloc(sizeof(parseTreeNode));
		parent_iter = argcurr->parent;
		while (parent_iter->parent != NULL) {
			if (parent_iter->next != NULL) {
				parseTreeNode *helper_iter;
				helper_iter = (parseTreeNode *) malloc(sizeof(parseTreeNode));
				helper_iter = parent_iter->next;
				//printf("%s\n aaya\n", helper_iter->token.name);
				while (helper_iter->next != NULL) {
					if (helper_iter->token.state < MAX_NT_NO) {
						return helper_iter;
					}
					else
					helper_iter = helper_iter->next;
					//printf("%s\n aaya\n", helper_iter->token.name);

				}
				if (helper_iter->token.state < MAX_NT_NO) {
					return helper_iter;
				}
			}
			parent_iter = parent_iter->parent;
			//printf("%s\n aaya\n", parent_iter->token.name);
		}
	}
	//printf("\nupdateCurr\n working correctly\n");
}

void insertInTree(int ruleNo) {
	cqueue *q;

	q = putInChildQ(ruleNo, PET->curr);
	//printf("insertInTree working correctly\n");
	PET->curr->children = q;
	//PET->curr->ASTchildren=PET->curr->children;
	PET->curr = updateCurrentParseTree(PET->curr);
	//printf("Curr is %s ", PET->curr->token.name);
	//fflush(stdout);
}


void push_Rule_Stack(tokenInfo nonterminal, tokenInfo terminal) {
	tokenInfo *p;

	int r = get_grammar_rule(nonterminal, terminal);
	//printf("Rule for %d and %d: %d\n", nonterminal.state, terminal.state, r);
	p = get_grammar_rule_Row(r);
	//printf("first token state is %d\n", p[1].state);
	//insertInTree(r);

	int i = MAX_RIGHTSIDE - 1;
	while (i > 0) {
		if (p[i].state != 1100 && p[i].state != -100) {
			push(p[i]);
		}
                        i--;
	}
	//printf("Pushed rule %d onto Stack",r);
}

parseTree parseInputSourceCode() {
	//printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%\nParsing going on\n%%%%%%%%%%%%%%%%%%%%%%\n");
	
	createStack();

	//printf("Create stack?\n");

	tokenInfo u;
	u.name = dollar;
	u.state = 1060;

	tokenInfo t;
	t.name = program;
	t.state = 31;

	//printf("Here atleast\n");

	push(u);
	push(t);

	//printf("Push $ and program done.\n");

	parsetreeCreate();

	//printf("Parse tree created\n");

	int Found_match;
	//printf("ya");
    temp_Token = getToken();
	tokenCount++;
    //printf("Token %s, %d fetched\n", temp_Token.lexeme, temp_Token.state);
	
	 while (temp_Token.state!=60) {

		if (S->head != NULL && S->head->token.state == 1060) 
			 	break;

			//temp_Token = getToken();
			//printf("%d before", tokenCount);
			//printf("%d after", tokenCount);
			Found_match = 0;
			//printf("%s", S->head->token.name);

			//printf("%s", temp_Token.name);
			while (Found_match == 0 && S->head != NULL) {
				//printParseTree(PST, "test2");
				/*stackNode *sta;
				sta = (stackNode *) malloc(sizeof(stackNode));
				sta = S->head;
				if (S->head != NULL) {
					while (sta->next != NULL) {
						printf("%s ok", sta->token.name);
						sta = sta->next;
					}

					printf("%s ok\n ", sta->token.name);

					//printf("if ke pehle");
				}
				//printf("if ke pehle");
				//printParseTree(PST, "test2");*/

				//printf("%sek", S->head->token.name);
				//printf("if ke pehle");
				//printf("%sek", S->head->token.name);
				if (S->head->token.state == temp_Token.state) {
					Found_match = 1;
					tokenInfo tk = pop();
					//printf("Token %d popped out.\n\n", tk.state);
					break;
				}
				if (get_grammar_rule(S->head->token, temp_Token) != -1) {
					//printf("pop ke pehle");
					tokenInfo tk = pop();
					//printf("Token %d popped out.\n\n", tk.state);
					//printf("pop ke baad");
					push_Rule_Stack(tk, temp_Token);
				}
				else {
					//printf("Rule is %d for %d and %d\n", get_grammar_rule(S->head->token, tempTok), S->head->token.state, tempTok.state);
					printf("The token %s for lexeme %s does not match at line %d. The expected token here is %s\n", temp_Token.name, temp_Token.lexeme, temp_Token.lineNo, S->head->token.name);
					break;
				}
			}
            temp_Token = getToken();
			//printf("Token %s, %d fetched\n", temp_Token.lexeme, temp_Token.state);
			tokenCount ++;
			//printf("%d fetched\n", tokenCount);
	}
	//printf("look");

	if (S->head != NULL) {
		while (S-> head->token.state != 1060) {
			tokenInfo panda;
			strcpy(panda.name, "e");
			//printf("%s", S->head->token.name);
			panda.state = 1100;
			if (get_grammar_rule(S->head->token, panda) != -1) {
				tokenInfo tk = pop();
				push_Rule_Stack(tk, panda);
			}
			else {
				//printf("Parsing stack not empty");
				break;
			}
		}
	}
	//printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%\nParsing done\n%%%%%%%%%%%%%%%%%%%%%%%5\n");
	return *PET;
}

void doEverything() {
	//removeComments("testcase3.txt", "test");
	grammar_Generator();
	Parse_Table_create();
	parseInputSourceCode("test.txt", ptable);
	//printParseTree(PET, "test2");
}

// void print_tree(parseTreeNode * print_helper, FILE * fp, int index){

// 	if(index == 0){
// 		if(print_helper->children == NULL){
// 			fprintf(fp, "Node: %-30s Parent node: %-30s Next sibling node: %-30s Child node: %-30s\n", print_helper->token.name,print_helper->ASTparent->token.name,print_helper->next->token.name,(print_helper->ASTchildren!=NULL)?((print_helper->ASTchildren->head!=NULL)?print_helper->ASTchildren->head->token.name:"(null)"):"(null)",print_helper->next->token.name);
// 			print_helper = print_helper->parent;
// 			fprintf(fp, "Node: %-30s Parent node: %-30s Next sibling node: %-30s Child node: %-30s\n", print_helper->token.name,print_helper->ASTparent->token.name,print_helper->next->token.name,(print_helper->ASTchildren!=NULL)?((print_helper->ASTchildren->head!=NULL)?print_helper->ASTchildren->head->token.name:"(null)"):"(null)",print_helper->next->token.name);
// 			print_helper = print_helper->children->head;
// 				if(print_helper->next != NULL){
// 					print_helper = print_helper->next;
// 					print_tree(print_helper, fp, 3 );
// 					}
// 				else{
// 					print_helper = print_helper->parent->parent;
// 					print_tree(print_helper,fp,0);
// 				}
// 			print_tree(print_helper,fp,3);
// 			//if(print_helper->parent != NULL)
// 			//print_tree(print_helper->parent, fp, 1 );
// 		}
// 		else{
// 		print_helper = print_helper->children->head;
// 		print_tree(print_helper, fp, 0);
// 		}
// 	}
// 	if(index == 1){
//         if(print_helper->children == NULL){
// 		fprintf(fp, "Node: %-30s Parent node: %-30s Next sibling node: %-30s Child node: %-30s\n", print_helper->token.name,print_helper->ASTparent->token.name,print_helper->next->token.name,(print_helper->ASTchildren!=NULL)?((print_helper->ASTchildren->head!=NULL)?print_helper->ASTchildren->head->token.name:"(null)"):"(null)",print_helper->next->token.name);
// 		print_helper = print_helper->parent;
// 		fprintf(fp, "Node: %-30s Parent node: %-30s Next sibling node: %-30s Child node: %-30s\n", print_helper->token.name,print_helper->ASTparent->token.name,print_helper->next->token.name,(print_helper->ASTchildren!=NULL)?((print_helper->ASTchildren->head!=NULL)?print_helper->ASTchildren->head->token.name:"(null)"):"(null)",print_helper->next->token.name);
// 		print_helper = print_helper->children->head;
		
// 			if(print_helper->next != NULL){
// 				print_helper = print_helper->next;
// 				print_tree(print_helper, fp, 1 );
// 				}
// 			else{
// 				print_helper = print_helper->parent->next;
// 				print_tree(print_helper,fp,3);
// 			}
// 		}
// 		else
//         print_tree(print_helper->children, fp, 0);
// 	}

// 	if(index == 2){
// 		if (print_helper != NULL) {
// 			if(print_helper -> children == NULL){
//             fprintf(fp, "Node: %-30s Parent node: %-30s Next sibling node: %-30s Child node: %-30s\n", print_helper->token.name,print_helper->ASTparent->token.name,print_helper->next->token.name,(print_helper->ASTchildren!=NULL)?((print_helper->ASTchildren->head!=NULL)?print_helper->ASTchildren->head->token.name:"(null)"):"(null)",print_helper->next->token.name);
// 			print_helper = print_helper->next;
// 			print_tree(print_helper, fp, 2);
// 											}

// 			else{
// 			print_tree(print_helper->children->head, fp, 3);
// 			}
// 		}
// 		else
// 		print_tree(print_helper->parent->parent, fp, 1);

// 	}
// 	if(index == 3){
//         if(print_helper->children == NULL){
// 		fprintf(fp, "Node: %-30s Parent node: %-30s Next sibling node: %-30s Child node: %-30s\n", print_helper->token.name,print_helper->ASTparent->token.name,print_helper->next->token.name,(print_helper->ASTchildren!=NULL)?((print_helper->ASTchildren->head!=NULL)?print_helper->ASTchildren->head->token.name:"(null)"):"(null)",print_helper->next->token.name);
// 		print_tree(print_helper->parent, fp, 4 );
//         }
//         else{
//         print_helper = print_helper->children->head;
//         print_tree(print_helper, fp, 3);
// 	}
// 	}
//     if(index == 4){
//         if(print_helper->children == NULL){
// 		fprintf(fp, "Node: %-30s Parent node: %-30s Next sibling node: %-30s Child node: %-30s\n", print_helper->token.name,print_helper->ASTparent->token.name,print_helper->next->token.name,(print_helper->ASTchildren!=NULL)?((print_helper->ASTchildren->head!=NULL)?print_helper->ASTchildren->head->token.name:"(null)"):"(null)",print_helper->next->token.name);
// 		print_helper = print_helper->next;
// 		print_tree(print_helper->parent, fp, 4 );
//                 }
//         else
//         print_helper = print_helper->children->head;
//         print_tree(print_helper, fp, 1);
// 		//fprintf(fp, "Node: %-30s Parent node: %-30s Next sibling node: %-30s Child node: %-30s\n", print_helper->token.name,print_helper->ASTparent->token.name,print_helper->next->token.name,(print_helper->ASTchildren!=NULL)?((print_helper->ASTchildren->head!=NULL)?print_helper->ASTchildren->head->token.name:"(null)"):"(null)",print_helper->next->token.name);
//         //parseTreeNode * temp_queue_help = print_helper->parent;

//         //if(print_helper ==  temp_queue_help->children->head){
//         //    print_helper(temp_queue_help, fp, 1);
//        // }
// 		//else if(print_helper->next != NULL){
// 		//print_helper = print_helper->next;
// 		//print_tree(print_helper, fp, 2 );
// 		//}
// 		//else
//          //   print_helper = print_helper->parent;
//         //    print_tree(print_helper,fp,4);
// 	}
// }



// void printParseTree(parseTree * p, char * file){
// 	FILE *fp;
// 	fp = fopen(file,"w+");
// 	print_tree(p->root, fp,  0);
// 	//fclose(fp);
// }

// int main(){
// 	   grammarGenerator();
//     FILE *fp1;
//     fp1 = fopen("test1", "w+");
//     for (i=0; i<NO_OF_RULES; i++) {
//     for (j=0; j<MAX_RIGHTSIDE; j++) {
//     if (GR[i][j].state != 100) fprintf(fp1, "%s ", GR[i][j].name);
//     }
//     fprintf(fp1, "\n", GR[i][j].name);
//     }
//     fclose(fp1);
//     removeComments("t3.txt", "test");
//     grammarGenerator();
//     createParseTable(GR, ptable);
//     parseInputSourceCode("test", ptable);
//     //travTree(PST->root);
//     //printParseTree(PST, "test2");
// }





