#include "addition.h"

namespace mySTL
{

#ifdef STRLEN
unsigned short strlen(const char *str)
{
    if ( str == nullptr )
    {
        return 0;
    }
    unsigned short i = 0;
    while ( str[i] != 0 )
        i++;
    return i;
}
#endif

#ifdef STRCMP_1
bool strcmp (const char *str1, const char *str2)
{
    unsigned int lenStr1 = strlen(str1);
    unsigned int lenStr2 = strlen(str2);
    int i = 0;
    if (lenStr1 > 0 && lenStr2 > 0)
    {
        while ( str1[i] != 0 || str2[i] != 0 )
        {
            if ( str1[i]!=str2[i] )
                return false;
            i++;
        }
    }
    else if (lenStr1 == 0 && lenStr1 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    return true;
}
#endif

#ifdef STRCMP_2
bool strcmp(const char *str1, const char *str2, unsigned short len)
{
    unsigned short i = 0;
    while ( (str1[i] != 0 || str2[i] != 0) && i<len )
    {
        if ( str1[i]!=str2[i] )
            return false;
        i++;
    }
    return true;
}
#endif

#ifdef STRCPY_1
char *strcpy(char *str1, const char *str2)
{
    unsigned short lenStr2 = strlen(str2);
    for ( unsigned short i = 0; i < lenStr2; i++ )
        str1[i]=str2[i];
    str1[lenStr2] = 0;
    return str1;
}
#endif


#ifdef STRCPY_2
char *strcpy(char *str1, const char *str2, unsigned short lenStr2)
{
    for ( unsigned short i = 0; i < lenStr2; i++ )
        str1[i]=str2[i];
    str1[lenStr2] = 0;
    return str1;
}
#endif

#ifdef STRCAT_1
char *strcat(char *str1, const char *str2)
{
    unsigned short i = 0;
    unsigned short lenStr1 = strlen(str1);
    while ( str2[i] != 0 )
    {
        str1[i + lenStr1] = str2[i];
        i++;
    }
    str1[i + lenStr1] = 0;
    return str1;
}
#endif

#ifdef STRCAT_2
char *strcat(char *str1, const char *str2, unsigned short lenStr1)
{
    unsigned short i = 0;
    while ( str2[i] != 0 )
    {
        str1[i + lenStr1] = str2[i];
        i++;
    }
    str1[i + lenStr1] = 0;
    return str1;
}
#endif

#ifdef STRCAT_3
char *strcat(char *str1, const char *str2, unsigned short lenStr1, unsigned short lenStr2)
{
    unsigned short i = 0;
    while ( i < lenStr2 )
    {
        str1[i + lenStr1] = str2[i];
        i++;
    }
    str1[i + lenStr1] = 0;
    return str1;
}
#endif

#ifdef ADD_CHAR
char *addCh(char *str, const char ch)
{
    char *new_str;
    unsigned short lenStr;
    if (str != nullptr)
    {
        lenStr = strlen(str);
    }
    else
    {
        lenStr = 0;
    }
    new_str = (char*)malloc(lenStr+2);
    if (new_str == nullptr)
    {
        return nullptr;
    }
        if (str != nullptr)
        {
            strcpy(new_str, str);
        }
        else
        {
            new_str[0] = 0;
        }
        if ( str != nullptr )
        {
            free(str);
        }
    str = new_str;
    str[lenStr] = ch;
    str[lenStr+1] = 0;
    return str;
}
#endif

#ifdef ADD_STR
char *addStr (char* str , const char* iStr)
{
    char *new_str;
    unsigned short lenStr1Str2;

    if (iStr != nullptr)
    {
        lenStr1Str2 = strlen(iStr);
    }
    if (str != nullptr)
    {
        lenStr1Str2 += strlen(str);
    }

    new_str = (char*)malloc(lenStr1Str2+1);
    if (str != nullptr)
    {
        strcpy(new_str, str);
    }
    else
    {
        new_str[0] = 0;
    }
    if ( str != nullptr )
    {
        free(str);
    }
    str=new_str;
    strcat(str, iStr);
    return str;
}
#endif

#ifdef EXTRACT_MSG
char *extractMsg(char c, char *filter)
{
    static int i = 0;
    static int u = 0;
    static char *msg = nullptr;
    static bool isMsg = false;

    if ( filter[i] == '$' && isMsg == false)
    {
        u = i+1;
        isMsg = true;
        free(msg);
        msg = nullptr;
    }


    if ( filter[i] == c )
    {
        i++;
        if ( filter[i] == 0 )
        {
            i = 0;
            u = 0;
            isMsg = false;
            return msg;
        }
    }
    else
    {
        i = u;
    }


    if ( isMsg == true )
    {
        msg = mySTL::addCh(msg, c);
    }

    return nullptr;
}
#endif

#ifdef ITOA
char *itoa(int i)
{
    char *a = nullptr;
    while (i > 0)
    {
        a = mySTL::addCh(a, 48+i%10);
        i/=10;
    }
    reverse(a);
    return a;
}
#endif

#ifdef REVERSE
char *reverse(char *str)
{
    unsigned short temp;
    unsigned int lenStr = strlen(str);
    for (int i = 0; i < lenStr/2; i++)
    {
        temp = str[i];
        str[i] = str[lenStr-i-1];
        str[lenStr-i-1] = temp;
    }
    return str;
}
#endif

#ifdef CONSTRUCTOR_1
string::string()
{

}
#endif
#ifdef CONSTRUCTOR_2
string::string(const char* iStr)
{
    unsigned short lenStr = strlen(iStr);
    if ( lenStr == 0 )
    {
        str = nullptr;
    }
    else
    {
        str = (char*)malloc(strlen(iStr));
        strcpy(str, iStr);
    }
}
#endif

#ifdef CONSTRUCTOR_3
string::string (const string &newObj)
{
    unsigned short lenStr = strlen(newObj.str);
    if ( lenStr == 0 )
    {
        str = nullptr;
    }
    else
    {
        str = (char*)malloc(lenStr);
        strcpy(str, newObj.str);
    }
}
#endif

#ifdef EQUALLY_1
char *string::operator= (const string &newObj)
{
    unsigned short lenStr = strlen(newObj.str);
    if ( str != nullptr )
    {
        free(str);
    }
    if ( lenStr == 0 )
    {
        str = nullptr;
    }
    else
    {
        str = (char*)malloc(lenStr);
        strcpy(str, newObj.str);
    }
    return str;
}
#endif

#ifdef EQUALLY_2
char *string::operator= (const char* iStr)
{
    unsigned short lenStr = strlen(iStr);
    if ( str != nullptr )
    {
        free(str);
    }
    if ( lenStr == 0 )
    {
        str = nullptr;
    }
    else
    {
        str = (char*)malloc(lenStr +1);
        strcpy(str, iStr, lenStr);
        str[lenStr] = 0;
    }
    return str;
}
#endif

#ifdef EQUALLY_3
char *string::operator= (const char c)
{
    if ( str != nullptr )
    {
        free(str);
    }
    str = (char*)malloc(2);
    str[0] = c;
    str[1] = 0;
    return str;
}
#endif

#ifdef PLUS_1
char *string::operator+ (const char* iStr)
{
    char *newObj = (char*)malloc(strlen(iStr)+strlen(str));
    strcpy(newObj, str);
    strcat(newObj, iStr);
    return newObj;
}
#endif

#ifdef PLUS_2
char *string::operator+ (const string &newObj)
{
    char *newObject = (char*)malloc(strlen(newObj.str)+strlen(str));
    strcpy(newObject, str);
    strcat(newObject, newObj.str);
    return newObject;
}
#endif

#ifdef PLUS_EQUALLY_1
char *string::operator+= (const char* iStr)
{
    unsigned short lenStr1Str2 = strlen(iStr)+strlen(str);
    char *newObject = (char*)malloc(lenStr1Str2+1);
    newObject[lenStr1Str2] = 0;
    strcpy(newObject, str);
    if ( str != nullptr )
    {
        free(str);
    }
    str = newObject;
    strcat(str, iStr);
    return str;
}
#endif

#ifdef PLUS_EQUALLY_2
char *string::operator+= (const string &newObj)
{
    unsigned short lenStr1Str2 = strlen(newObj.str)+strlen(str);
    char *newObject = (char*)malloc(lenStr1Str2+1);
    newObject[lenStr1Str2] = 0;
    strcpy(newObject, str);
    if ( str != nullptr )
    {
        free(str);
    }
    str = newObject;
    strcat(str, newObj.str);
    return str;
}
#endif

#ifdef PLUS_EQUALLY_3
char *string::operator+= (const char c)
{
    unsigned short lenStr = strlen(str);
    char *newObject = (char*)malloc(lenStr+2);
    newObject[lenStr+1] = 0;
    strcpy(newObject, str);
    if ( str != nullptr )
    {
        free(str);
    }
    str = newObject;
    str[lenStr] = c;
    return str;
}
#endif

//#if 1
//   char* string::operator[] (unsigned short i)
//   {
//       return &str[i];
//   }
//#endif

#ifdef GET_STR
char *string::getStr()
{
    return str;
}
#endif

#ifdef LENGTH
unsigned short string::length()
{
    return strlen(str);
}
#endif

#ifdef CLEAR
char* string::clear()
{
    free(str);
    str = nullptr;
    return str;
}
#endif

#ifdef DESTRUCTOR
string::~string()
{
    free(str);
}
#endif

}

