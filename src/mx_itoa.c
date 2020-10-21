#include "header.h"

static void mx_swap_char(char *s1, char *s2) {
    char s3 = *s1;
    *s1 = *s2;
    *s2 = s3;
}

static int mx_strlen(const char *s) {
    int i = 0;
    
    if (!s)
        return 0;
    while (s[i])
        i++;
    return i;
}

static void mx_str_reverse(char *s) {
    int len = mx_strlen(s) - 1;
    
    if (s)
        for (int i = 0; i <= len / 2; i++)
            mx_swap_char(&s[i], &s[len - i]);
}

static char *mx_strcpy(char *dst, const char *src) {
    int i = 0;
    
    while (src[i]) {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return dst;
}

static char *mx_strnew(const int size) {
    char *memory = NULL;
    int i = 0;

    if (size < 0)
        return NULL;
    memory = (char *)malloc((size + 1) * sizeof(char));
    while (i < size) {
        memory[i] = '\0';
        i++;
    }
    memory[i] = '\0';
    return memory;
}

static int number_length(int number) {
	int length = 0;

	while (number) {
		number /= 10;
		length++;
	}
	return length;
}

char *mx_itoa(int number) {
	int length = number_length(number);
	int tmp = number;
	char *result = NULL;

	result = mx_strnew(length);
	if (number == 0)
		return mx_strcpy(result, "0");
	if (number == -2147483648)
		return mx_strcpy(result, "-2147483648");
	tmp = number;
	for (int i = 0; i < length; i++) {
		if (tmp < 0) {
			result[length] = '-';
			tmp = -tmp;
		}
		result[i] = (tmp % 10) + '0';
		tmp /= 10;
	}
	mx_str_reverse(result);
	return result;
}
