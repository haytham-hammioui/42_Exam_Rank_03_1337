#include <stdio.h>

int must_fix;

int invalid(char *s)
{
    int unclosed=0, unopened=0;

    for (int i=0; s[i]; i++)
    {
        if (s[i] == '(') unclosed++;
        else if (s[i] == ')')
        {
            if (unclosed > 0) unclosed--;
            else unopened++;
        }
    }
    return (unclosed + unopened);
}

void    rip(char *s, int make_change, int pos)
{
    char c;

    if (must_fix == make_change && !invalid(s))
    {
        puts(s);
        return ;
    }
    for (int i=pos; s[i]; i++)
    {
        if (s[i] == '(' || s[i] == ')')
        {
            c = s[i];
            s[i] = ' ';
            rip(s, make_change+1, i+1);
            s[i] = c;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    must_fix = invalid(argv[1]);
    rip(argv[1], 0, 0);
    return (0);
}