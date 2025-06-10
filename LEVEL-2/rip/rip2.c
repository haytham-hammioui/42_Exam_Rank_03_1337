#include <stdio.h>

int is_val(char *str)
{
    int opened = 0, closed = 0;

    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '(')
            opened++;
        else if (str[i] == ')')
        {
            if (opened > 0)
                opened--;
            else
                closed++;
        }
    }
    return opened + closed;
}

void    rip(char *str, int must_fic, int n_fix, int pos)
{
    if (must_fic == n_fix && !is_val(str))
    {
        puts(str);
        return;
    }
    for(int i = pos; str[i]; i++)
    {
        if (str[i] == '('  || str[i] == ')')
        {
            int c = str[i];
            str[i] = ' ';
            rip(str, must_fic, n_fix + 1, i);
            str[i] = c;
        }
    }
}

int main(int ac, char **ag)
{
    int m_fix = is_val(ag[1]);
    rip(ag[1], m_fix, 0, 0);
}