#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c = fgetc(f);
    while(c != EOF && isspace(c))
        c = fgetc(f);
    if(c == EOF)
        return -1;
    ungetc(c, f);
    return (1);
}

int match_char(FILE *f, char c)
{
    int ch = fgetc(f);
    if(ch == EOF)
        return -1;
    if(ch == c)
        return 1;
    ungetc(c, f);
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
    int c = fgetc(f);
    if(c == EOF)
        return -1;
    char *ptr = va_arg(ap, char*);
    *ptr = c;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
    int result = 0;
    int sign = 1;
    int dig_scanned = 0;
    int c = fgetc(f);
    if(c == '+' || c=='-'){
        if(c == '-')
            sign = -1;
        c = fgetc(f);
    }
    while(c != EOF && isdigit(c)){
        result = result * 10 + (c - '0');
        dig_scanned++;
        c = fgetc(f);
    }
    if(c != EOF)
        ungetc(c, f);
    if(dig_scanned == 0)
        return 0;
    int *ptr = va_arg(ap, int *);
    *ptr = result * sign;
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
    char *str = va_arg(ap, char *);
	int c = fgetc(f);
	int char_scanned = 0;
	while(c != EOF && !isspace(c)){
		str[char_scanned] = c;
		char_scanned++;
		c = fgetc(f);
	}
	if(c!=EOF)
		ungetc(c, f);
	str[char_scanned] = '\0';
	if(char_scanned == 0)
		return 0;
    return (1);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}