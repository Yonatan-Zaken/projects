#include <iostream>
#include <cstring>

std::size_t CountAppearance(const char *str, const char *pattern)
{
    const char *strHolder = str;
    std::size_t counter = 0;

    while (*strHolder != '\0')
    {
        const char *patternRunner = pattern;
        const char *strRunner = strHolder;
        while ((*strRunner != '\0') && (*patternRunner != '\0'))
        {
            if (*strRunner == *patternRunner)
            {
                ++patternRunner;
            }

            ++strRunner;
        }
        
        if (*patternRunner == '\0')
        {
            ++counter;
        }
        
        ++strHolder;
    }

    return counter;
}

int main()
{
    char str[] = "subsequence";
    char pattern[] = "sue";

    std::cout << CountAppearance(str, pattern);

    return 0;
}