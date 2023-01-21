#ifndef PARSE_H
#define PARSE_H

struct DATASTRUCT
{
    char *data;
    int type;
    struct DATASTRUCT *next;
} typedef dataStruct;

void print_elements(dataStruct *head);

int formatOk(char *tmp);

char *trim(char *string);

bool isBoolean(char *ptr2);

bool isFalseBoolean(char *ptr2);

bool isFloat(char *ptr2);

bool isInt(char *ptr2);

bool isString(char *ptr2);

#endif