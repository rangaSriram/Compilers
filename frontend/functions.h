#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ptr{
    int index;
    int arrNum;
} ptr;

typedef struct tokeninfo{
    char * name;
    char * lexeme;
    int state;
    int lineNo;
} tokenInfo;

char buff[2][20];
int lineNo;

char* names[35] = {"", "ID", "NUM", "", "RNUM", "", "", "NUM", "COLON", "ASSIGNOP", "MUL", "LT", "LE", "DEF", "DRIVERDEF", "GT", "GE", "ENDDEF", "DRIVERENDDEF", "", "RANGEOP", "PLUS", "MINUS", "DIV", "", "EQ", "", "NE", "SEMICOL", "COMMA", "SQBO", "SQBC", "BO", "BC", "RNUM"};
int states[35] = {0, 1059, 1057, 0, 1058, 0, 0, 1057, 1047, 1051, 1035, 1037, 1038, 1043, 1044, 1040, 1039, 1045, 1046, 0, 1048, 1033, 1034, 1036, 0, 1041, 0, 1042, 1049, 1050, 1052, 1053, 1054, 1055, 1058};

char * keywordLexemes[34] = {"integer", "real", "boolean", "of", "array", "start", "end", "declare", "module", "driver", "program", "record", "tagged", "union", "get_value", "print", "use", "with", "parameters", "true", "false", "takes", "input", "returns", "AND", "OR", "for", "in", "switch", "case", "break", "default", "while", "$"};
char * keywordTokens[34] = {"INTEGER", "REAL", "BOOLEAN", "OF", "ARRAY", "START", "END", "DECLARE", "MODULE", "DRIVER", "PROGRAM", "ID", "ID", "ID", "GET_VALUE", "PRINT", "USE", "WITH", "PARAMETERS", "TRUE", "FALSE", "TAKES", "INPUT", "RETURNS", "AND", "OR", "FOR", "IN", "SWITCH", "CASE", "BREAK", "DEFAULT", "WHILE", "$"};

ptr bp, fp;

FILE * file;                                    //current file pointer
FILE * start;                                   //starting file pointer

char error[15] = "error";
char eof[15] = "EOF";

#define MAX_NT_NO 57
#define MAX_TER_NO 60
#define MAX_TOKENS 1000
#define MAX_RIGHTSIDE 13
#define NO_OF_RULES 105

static tokenInfo temp_Token;
static int tokenCount;
static int tokensTraversed;

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

//static first_follow_node * first[MAX_NT_NO][20];

//static first_follow_node * follow[MAX_NT_NO][20];

static int hash_table[MAX_NT_NO][2];

typedef struct cq cqueue;

typedef struct ptnode {
	tokenInfo token;
	struct ptnode *next;
	struct ptnode *parent;
	cqueue *children;
	struct ptnode *ASTparent;
	cqueue *ASTchildren;
	int member;
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

extern void initializeHTable();

extern int hash_function(char *key);

extern void grammar_Generator();

extern void Parse_Table_create();

extern void createStack(); 

extern void push(tokenInfo t);

extern tokenInfo pop();

extern  int getState(tokenInfo nonterminal);

extern int get_grammar_rule(tokenInfo nonterminal, tokenInfo terminal);

extern tokenInfo *get_grammar_rule_Row(int n);

extern cqueue *pushQ(parseTreeNode *a, cqueue *q);

extern cqueue *putInChildQ(int ruleNo, parseTreeNode *par);

extern void parsetreeCreate();

extern parseTreeNode *updateCurrentParseTree(parseTreeNode *argcurr);

extern void insertInTree(int ruleNo);

extern void print_tree(parseTreeNode * print_helper, FILE * fp, int index);

extern void printParseTree(parseTree * p, char * file);

extern void push_Rule_Stack(tokenInfo nonterminal, tokenInfo terminal);

extern parseTree parseInputSourceCode(char *testcaseFile, table T);

void doEverything();

tokenInfo getToken();

int fillBuffer(int n);

int increment();

int retract();

int isKeyword(char * token);