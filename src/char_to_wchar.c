#include "char_to_wchar.h"
#include "gui/gui.h"
char* wchar_to_char(wchar_t *wstr)
{
    char *str;
    size_t i, j, k;

    if(wstr == NULL)
        return NULL;

    k = 0;
    j = 0;

    for(i = 0; wstr[i]; i++)
    {
        j++;
        if((wstr[i] == 0xFB00) ||
                (wstr[i] == 0xFB01) ||
                (wstr[i] == 0xFB02))
            j++;
    }

    str = calloc(j + 15, sizeof(char));

    for(i = 0; wstr[i]; i++)
    {
        if((wstr[i] == 0xFB00) ||
                (wstr[i] == 0xFB01) ||
                (wstr[i] == 0xFB02))
        {
            str[k] = 'f';
            j++;
            if(wstr[i] == 0xFB00)
                str[k] = 'f';
            if(wstr[i] == 0xFB01)
                str[k] = 'i';
            if(wstr[i] == 0xFB02)
                str[k] = 'l';
	}
        else
        {
	    str[k] = wstr[i];
	    if(wstr[i] == 0xC3A8)
                str[k] = 70;
            if(wstr[i] == 0xC3A9)
                str[k] = 70;
            if(wstr[i] == 0xC3A0)
                str[k] = 70;
            if(wstr[i] == 0xC3A2)
                str[k] = 70;
            if(wstr[i] > 0x7F)
                str[k] = 'd';

        }
        k++;
    }
    //wprintf(L"%ls", wstr);
    return str;
}
