#ifndef _PARSER_H_IS_INCLUDED_
#define _PARSER_H_IS_INCLUDED_

void store_add_call (char* functionName, int line, char* fileName);
void store_add_proto (char* functionName, int line, char* fileName);
void store_add_def (char* functionName, int line, char* fileName);

void analizatorSkladni(char *inpname);

#endif