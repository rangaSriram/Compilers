//BATCH NUMBER 49
//RANGA SRIRAM 2017A7PS0047P
//RAYAPATI YASWANTH KUMAR 2017A7PS0038P
//KATTA SIVA KUMAR 2017A7A7PS0078P

#ifndef PARSER_H
#define PARSER_H

//BATCH NUMBER 49
//RANGA SRIRAM 2017A7PS0047P
//RAYAPATI YASWANTH KUMAR 2017A7PS0038P
//KATTA SIVA KUMAR 2017A7A7PS0078P

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "parseDef.h"
#include "lexer.h"

extern void initializeHTable();

extern void parserInitialize();

extern int hash_function(char *key);

extern void grammar_Generator();

extern void modifyGrammar();

extern void Parse_Table_create();

extern void createStack(); 

extern void push(tokenInfo t);

extern tokenInfo pop();

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

extern parseTree parseInputSourceCode();

void doEverything();

#endif