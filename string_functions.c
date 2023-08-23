#include "shell.h"


/**
 * startWith - str starts with c
 * @str: String
 * @c: subString
 *
 * Return str or NULL
 */
char *startWith(const char *str, const char *c)
{
    while (*c)
    {
        if (*c++ != *str++)
            return (NULL);
    }
    return ((char *)str);
}

/**
 * strcat - concatenates two strings
 * @tes: destbuffer
 * @cr: sourbuffer
 * Return pointer buffer
 */

 char *str_cat(char *tes, char *cr)
 {
    int i=0, j=0;
    char *dest;

    dest = (char *)malloc(sizeof(char)*(_strlength(tes)+_strlength(cr)+1));

    while (tes[i] != '\0') {
        dest[j] = tes[i];
        i++;
        j++;
    }
    i = 0;
    while (cr[i] != '\0') {
        dest[j] = cr[i];
        i++;
        j++;
    }
    dest[j]='\0';
    return (dest);
 }

 /**
  * _strcomparison - comparison strangs.
  * @a : strang
  * @b : strang
  *
  * Return: negative or positive or zero
  */
 int _strcomparison(char *a, char *b)
 {
       if (*a == *b)
          return (0);
       else
          return (*a < *b ? -1 : 1);
       while (*a && *b)
       {
          if ((*a) != (*b))
            return (*a - *b);
          a++;
          b++;
       }
}

/**
 * _strlength - returns the length
 * @c : string whose length to check
 *
 * Return : length of string
 */
int _strlength(char *c)
 {
   int i = 0;

   if (!c)
     return (0);
   while (*c++)
      i++;

   return (i);
 }
