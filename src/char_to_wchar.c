#include "char_to_wchar.h"

char* wchar_to_char(wchar_t *wstr)
{
    char *str;
    size_t i, j;

    j = 0;
    for(i = 0; wstr[i]; i++)
    {
        j++;
        if((wstr[i] == 0xFB00) ||
                (wstr[i] == 0xFB00) ||
                (wstr[i] == 0xFB00))
            j++;
    }

    str = calloc(j + 2, sizeof(char));

    for(i = 0; wstr[i]; i++)
    {
        if((wstr[i] == 0xFB00) ||
                (wstr[i] == 0xFB00) ||
                (wstr[i] == 0xFB00))
        {
            str[j] = 'f';
            j++;
            if(wstr[i] == 0xFB00)
                str[j] = 'f';
            if(wstr[i] == 0xFB01)
                str[j] = 'i';
            if(wstr[i] == 0xFB02)
                str[j] = 'l';
        }
        else
        {
            str[j] = wstr[i];
        }
    }

    return str;
}
