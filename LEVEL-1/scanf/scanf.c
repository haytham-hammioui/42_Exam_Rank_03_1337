#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int ft_scanf(const char *format, ...) {
    va_list args;
    int count = 0;
    int ch = 0;

    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++;

            if (*format == 'd') {
                int *dst = va_arg(args, int *);
                int value = 0;
                int sign = 1;
                do {
                    ch = fgetc(stdin);
                    if (ch == EOF) {
                        va_end(args);
                        return count;
                    }
                } while (isspace(ch));
                if (ch == '-'|| ch == '+') {
                    if (ch == '-')
                        sign = -1;
                    ch = fgetc(stdin);
                }
                if (!isdigit(ch)) {
                    if (ch != EOF) ungetc(ch, stdin);
                    va_end(args);
                    return count;
                }
                while (isdigit(ch)) {
                    value = value * 10 + (ch - '0');
                    ch = fgetc(stdin);
                }
                if (ch != EOF)
                    ungetc(ch, stdin);

                *dst = value * sign;
                count++;
            }

            else if (*format == 's') {
                char *dst = va_arg(args, char *);
                int i = 0;
                do {
                    ch = fgetc(stdin);
                    if (ch == EOF) {
                        va_end(args);
                        return count;
                    }
                } while (isspace(ch));

                while (ch != EOF && !isspace(ch)) {
                    dst[i++] = ch;
                    ch = fgetc(stdin);
                }

                if (ch != EOF)
                    ungetc(ch, stdin);

                dst[i] = '\0';
                count++;
            }

            else if (*format == 'c') {
                char *dst = va_arg(args, char *);
                do {
                    ch = fgetc(stdin);
                    if (ch == EOF) {
                        va_end(args);
                        return count;
                    }
                } while (isspace(ch));

                *dst = ch;
                count++;
            }

            format++;
        } else {
            ch = fgetc(stdin);
            if (ch == EOF || ch != *format) {
                va_end(args);
                return count;
            }
            format++;
        }
    }

    va_end(args);
    return count;
}
