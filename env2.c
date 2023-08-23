#include "shell.h"

/**
 * _environ - string array copy of environ
 * @info : structure containing potential
 *
 * Return : Always 0
*/
char **_environ(info_t *info)
{
    if(!info->environ || info->env_changed)
    {
        info->environ = list_string(info->env);
        info->env_changed = 0;
    }
    return (info->environ);
}


/**
 * rem_envirenement - remove an envirenement
 * @info : structure containnig potentiel
 * @str : string
 *
 * Return : 1 if true or 0 if false
*/
int rem_envirenement(info_t *info, char *v)
{
    list_t *n = info->env;
    char *p;
    size_t i;

    if (!n || !v)
    return (0);
    while (n)
    {
        p = startWith(n->str, v);
        if (p && *p == '=')
        {
            info->env_changed = node_index(&(info->env), 1);
            i = 0;
            n = info->env;
            continue;
        }
        n = n->next;
        i++;
    }
    return (info->env_changed);
}

/**
 * new_env -  intialize a new envirenement
 * @info : structure containnig potentiel
 * @str : string envirenement
 * @var : envirenement value
 *
 * Return : Always 0
*/
  int new_env(info_t *info, char *st, char *var)
  {
      char *buffer;
      list_t *nd;
      char *d;

      if (!st || !var)
        return (0);
      buffer = malloc(_strlength(st) + _strlength(var) + 2);
      if (!buffer)
        return (0);
      _strcomparison(buffer, st);
      str_cat(buffer, "=");
      str_cat(buffer, var);
      while (nd)
      {
          d = startWith(nd->str, st);
          if (d && *d == '=')
          {
              nd->str = buffer;
              info->env_changed = 1;
              return (0);
          }
          nd = nd->next;
      }
      _nend(&(info->env), buffer, 0);
      free(buffer);
      info->env_changed = 1;
      return (0);
  }
