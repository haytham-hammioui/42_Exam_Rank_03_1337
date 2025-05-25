#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f) {
    int c = fgetc(f);
    while (c != EOF && isspace(c))
        c = fgetc(f);
    if (c == EOF)
        return -1;
    ungetc(c, f);
    return 1;
}

int match_char(FILE *f, char c) {
    int input = fgetc(f);
    if (input == EOF)
        return -1;
    if (input == c)
        return 1;
    ungetc(input, f);
    return 0;
}

int scan_char(FILE *f, va_list ap) {
    int c = fgetc(f);
    if (c == EOF)
        return -1;
    char *ptr = va_arg(ap, char*);
    *ptr = c;
    return 1;
}

int scan_int(FILE *f, va_list ap) {
    int sign = 1;
    int digit_scaned = 0;
    int c = fgetc(f);
    int r = 0;

    if (c == '+' || c == '-') {
        if (c == '-')
            sign = -1;
        c = fgetc(f);
    }

    while (c != EOF && isdigit(c)) {
        r = r * 10 + (c - '0');
        digit_scaned++;
        c = fgetc(f);
    }
    if (c != EOF)
        ungetc(c, f);
    if (digit_scaned == 0)
        return 0;
    int *ptr = va_arg(ap, int*);
    *ptr = r * sign;
    return 1;
}

int scan_string(FILE *f, va_list ap) {
    char *str = va_arg(ap, char*);
    int c = fgetc(f);
    int chars_scaned = 0;

    while (c != EOF && !isspace(c)) {
        str[chars_scaned] = c;
        chars_scaned++;
        c = fgetc(f);
    }
    if (c != EOF)
        ungetc(c, f);
    str[chars_scaned] = '\0';
    if (chars_scaned == 0)
        return 0;
    return 1;
}

int match_conv(FILE *f, const char **format, va_list ap) {
    switch (**format) {
        case 'c':
            return scan_char(f, ap);
        case 'd':
            return scan_int(f, ap);
        case 's':
            return scan_string(f, ap);
        default:
            return -1;
    }
}

int ft_vfscanf(FILE *f, const char *format, va_list ap) {
    int nconv = 0;
    int ret;

    while (*format) {
        if (*format == '%') {
            format++;
            ret = match_conv(f, &format, ap);
            if (ret == -1) {
                return (nconv == 0) ? -1 : nconv;
            } else if (ret == 0) {
                return nconv;
            } else {
                nconv++;
            }
        } else if (isspace(*format)) {
            if (match_space(f) == -1) {
                return (nconv == 0) ? -1 : nconv;
            }
        } else {
            ret = match_char(f, *format);
            if (ret == -1) {
                return (nconv == 0) ? -1 : nconv;
            } else if (ret == 0) {
                return nconv;
            }
        }
        format++;
    }
    if (ferror(f)) {
        return -1;
    }
    return nconv;    
}

int ft_scanf(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    int ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    return ret;
}

int main(){
	int n;
	char c;
	char str[100];

	ft_scanf("%d  %c %s", &n, &c, str);

	printf("n: %d\n", n);
    printf("c: %c\n", c);
    printf("str: %s\n", str);
}