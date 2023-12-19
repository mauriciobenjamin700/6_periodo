#include <stdio.h>
#include <ctype.h>

int strcasecmp_custom(const char *s1, const char *s2)
{
    while (*s1 && *s2 && tolower(*s1) == tolower(*s2))
    {
        s1++;
        s2++;
    }
    return tolower(*s1) - tolower(*s2);
}

int main()
{
    char str1[] = "HelloU";
    char str2[] = "hellou";

    // Uso da função personalizada para comparar strings (case-insensitive)
    int result = strcasecmp_custom(str1, str2);

    if (result == 0)
    {
        printf("As strings são iguais (case-insensitive).\n");
    }
    else
    {
        printf("As strings são diferentes (case-insensitive).\n");
    }

    return 0;
}
