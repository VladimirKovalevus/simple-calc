#ifndef __SERVICE_UTILS_HPP__
#define __SERVICE_UTILS_HPP__

#include "polishnotation.h"


bool is_digit(char c);
int is_operator(char c);
int is_bracket(char c);
bool is_unar(char c);
int is_mod(const char* str);
int is_cos(const char* str);
int is_sin(const char* str);
int is_tan(const char* str);
int is_sqrt(const char* str);
int is_log(const char* str);
int is_ln(const char* str);
int is_function(const char* str);



#endif //__SERVICE_UTILS_HPP__
