//BATCH NUMBER 49
//RANGA SRIRAM 2017A7PS0047P
//RAYAPATI YASWANTH KUMAR 2017A7PS0038P
//KATTA SIVA KUMAR 2017A7A7PS0078P

#ifndef PARSERDEF_H
#define PARSERDEF_H


#define MAX_NT_NO 57
#define MAX_TER_NO 60
#define MAX_TOKENS 1000
#define MAX_RIGHTSIDE 15
#define NO_OF_RULES 105

#include "lexer.h"

extern tokenInfo temp_Token;
extern int tokenCount;
extern int tokensTraversed;

extern char * program;
extern char * dollar;

typedef int table[MAX_NT_NO][MAX_TER_NO];
int ptable[MAX_NT_NO][MAX_TER_NO];

typedef struct stacknode {
	tokenInfo token;
	struct stacknode *next;
} stackNode;

typedef struct {
	stackNode *head;
} stack;

static stack *S;

typedef tokenInfo grammar[NO_OF_RULES][MAX_RIGHTSIDE];
tokenInfo GR[NO_OF_RULES][MAX_RIGHTSIDE]; // Captures the grammar

typedef struct ffnode {
	tokenInfo token;
	struct ffnode *next;
} first_follow_node;

typedef struct {
	first_follow_node *head;
	int size;
} first_Follow_queue;

static first_follow_node * first[MAX_NT_NO][20];

static first_follow_node * follow[MAX_NT_NO][20];

static int hash_table[MAX_NT_NO][2];

typedef struct cq cqueue;

typedef struct ptnode {
	tokenInfo token;
	struct ptnode *next;
	struct ptnode *parent;
	cqueue *children;
	//struct ptnode *ASTparent;
	//cqueue *ASTchildren;
	//int member;
	int type;
} parseTreeNode;

typedef struct cq {
	parseTreeNode *head;
	parseTreeNode *tail;
	int size;
} cqueue;

typedef struct {
	parseTreeNode *root;
	parseTreeNode *curr;
} parseTree;

parseTree *PET;

static int firstSet[57][20] = {{1033, 1034, 1054, 1019, 1020, 1059, 1057, 1058, -100},
                                {1024, 1025, -100}, 
                                {1000, 1001, 1002, 1004, -100}, 
                                {1019, 1020, -100},
                                {1007, -100},
                                {1014, 1015, -100}, 
                                {1100, 1043, -100},
                                {1100, 1014, 1059, 1052, 1016, 1007, 1028, 1026, 1015, 1032, -100},
                                {1007, 1100, -100}, 
                                {1052, -100},
                                {1057, 1059, -100},
                                {1051, -100},
                                {1044, -100},
                                {1050, 1100, -100},
                                {1050, 1100, -100},
                                {1059, -100},
                                {1050, 1100, -100},
                                {1033, 1034, -100},
                                {1054, 1059, 1057, 1058, -100},
                                {1100, 1024, 1025, -100},
                                {1100, 1037, 1038, 1039, 1040, 1041, 1042, -100},
                                {1100, 1033, 1034, -100},
                                {1100, 1052, -100},
                                {1043, -100},
                                {1100, 1052, -100},
                                {1100, 1035, 1036, -100},
                                {1054, 1059, 1058, 1057, -100},
                                {1028, -100},
                                {1033, 1034, -100},
                                {1100, 1029, -100},
                                {1057, 1019, 1020, -100},
                                {1007, 1043, 1100, -100},
                                {1057, 1058, 1059, 1019, 1020, -100},
                                {1100, 1023, -100},
                                {1100, 1031, -100},
                                {1000, 1001, 1002, -100},
                                {1014, 1059, 1052, 1016, 1007, 1028, 1026, 1015, 1032, -100},
                                {1059, -100},
                                {1026, 1032, -100},
                                {1016, 1052, -100},
                                {1054, 1019, 1020, 1057, 1058, 1059, -100},
                                {1033, 1034, -100},
                                {1035, 1036, -100},
                                {1007, -100},
                                {1057, 1059, -100},
                                {1059, -100},
                                {1054, 1057, 1058, 1059, -100},
                                {1019, 1020, 1054, 1059, 1057, 1058, -100},
                                {1054, 1057, 1058, 1059, -100},
                                {1029, -100},
                                {1057, -100},
                                {1057, 1058, 1059, -100},
                                {1059, -100},
                                {1059, 1052, 1016, -100},
                                {1037, 1038, 1039, 1040, 1041, 1042, -100},
                                {1005, -100},
                                {1051, 1052, -100}};                                    //Done with first sets

static int followSet[57][20] = {{1049, -100},
                                {1054, 1057, 1058, 1059, 1019, 1020, -100},
                                {1053, 1049, -100},
                                {1055, 1035, 1036, 1024, 1025, 1049, -100},
                                {1006, 1030, -100},
                                {1006, 1030, -100},
                                {1044, 1060, -100},
                                {1006, 1030, -100},
                                {1043, -100},
                                {1006, 1030, -100},
                                {1053, -100},
                                {1006, 1030, -100},
                                {1043, 1060, -100},
                                {1053, -100},
                                {1053, -100},
                                {1049, 1053, 1047, 1050, -100},
                                {1049, 1053, 1047, 1050, -100},
                                {1054, 1057, 1058, 1059, -100},
                                {1055, 1037, 1038, 1039, 1040, 1041, 1042, 1024, 1025, 1049, -100}, 
                                {1055, 1049, -100},
                                {1024, 1025, 1055, 1049, -100},             
                                {1055, 1037, 1038, 1039, 1040, 1041, 1042, 1024, 1025, 1049, -100},             
                                {1055, 1035, 1036, -100},
                                {1060, 1043, -100},
                                {1016, -100},
                                {1033, 1034, 1055, 1037, 1038, 1039, 1040, 1041, 1042, 1024, 1025, 1049, -100},
                                {1035, 1036, 1033, 1034, 1055, 1037, 1038, 1039, 1040, 1041, 1042, 1024, 1025, 1049, -100},
                                {1006, 1030, -100},
                                {1049, -100},
                                {1031, 1006, -100},
                                {1047, -100},
                                {1060, -100},
                                {1055, -100},
                                {1005, -100},
                                {1006, -100},
                                {1050, 1053, 1049, -100},
                                {1006, 1030, -100},
                                {1006, 1030, -100},
                                {1006, 1030, -100},
                                {1006, 1030, -100},
                                {1055, 1049, -100},   
                                {1054, 1057, 1058, 1059, -100},
                                {1054, 1057, 1058, 1059, -100},
                                {1043, 1007, -100},
                                {1048, 1053, -100},
                                {1053, -100},
                                {1049, -100},
                                {1024, 1025, 1055, 1049, -100},
                                {1033, 1034, 1055, 1037, 1038, 1039, 1040, 1041, 1042, 1024, 1025, 1049, -100},
                                {1031, 1006, -100},
                                {1055, -100},
                                {1035, 1036, 1033, 1034, 1055, 1037, 1038, 1039, 1040, 1041, 1042, 1024, 1025, 1049, -100},
                                {1053, -100},
                                {1006, 1030, -100},
                                {1057, 1058, 1059, 1054, -100},
                                {1060, 1043, -100},
                                {1006, 1030, -100}};
#else
#endif
