#ifndef MYSTL_H
#define MYSTL_H

#ifdef MY_STL

#define STRLEN
#define STRCMP_1
#define STRCMP_2
#define STRCPY_1
#define STRCPY_2
#define STRCAT_1
#define STRCAT_2
#define STRCAT_3
#define ADD_CHAR
#define ADD_STR
#define EXTRACT_MSG
#define ITOA
#define REVERSE
#define CONSTRUCTOR_1
#define CONSTRUCTOR_2
#define CONSTRUCTOR_3
#define EQUALLY_1
#define EQUALLY_2
#define EQUALLY_3
#define PLUS_1
#define PLUS_2
#define PLUS_EQUALLY_1
#define PLUS_EQUALLY_2
#define PLUS_EQUALLY_2
#define GET_STR
#define LENGTH
#define CLEAR
#define DESTRUCTOR

#endif

#endif // MYSTL_H

namespace mySTL
{
#ifdef STRLEN
unsigned short strlen(const char *str);
#endif
#ifdef STRCMP_1
bool strcmp(const char *str1, const char *str2);
#endif
#ifdef STRCMP_2
bool strcmp(const char *str1, const char *str2, unsigned short len);
#endif
#ifdef STRCPY_1
char *strcpy(char *str1, const char *str2);
#endif
#ifdef STRCPY_2
char *strcpy(char *str1, const char *str2, unsigned short lenStr1);
#endif
#ifdef STRCAT_1
char *strcat(char *str1, const char *str2);
#endif
#ifdef STRCAT_2
char *strcat(char *str1, const char *str2, unsigned short lenStr1);
#endif
#ifdef STRCAT_3
char *strcat(char *str1, const char *str2, unsigned short lenStr1, unsigned short lenStr2);
#endif
#ifdef ADD_CHAR
char *addCh(char *str, const char ch);
#endif
#ifdef ADD_STR
char *addStr (char* str , const char* iStr);
#endif
#ifdef EXTRACT_MSG
char *extractMsg(char c, char *filter);
#endif
#ifdef ITOA
char *itoa(int i);
#endif
#ifdef REVERSE
char *reverse(char *str);
#endif
class string
{
public:
    string();
    string(const char* iStr);
    string (const string &newObj);
    char *operator= (const string &newObj);
    char *operator= (const char* iStr);
    char *operator= (const char c);
    char *operator+ (const string &newObj);
    char *operator+ (const char* iStr);
    char *operator+= (const char* iStr);
    char *operator+= (const string &newObj);
    char *operator+= (const char c);
//    char *operator[] (size_t i);
    char *getStr();
    unsigned short length();
    char* clear();
    ~string();


    char *str = nullptr;
};

}

