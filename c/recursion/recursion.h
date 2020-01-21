#ifndef __RECURSION_H__
#define __RECURSION_H__

size_t IterFib(size_t position);
size_t RecFib(size_t position);
size_t RecStrlen(const char *str);
int RecStrcmp(const char *s1, const char *s2);
char *RecStrcpy(char *dest, const char *src);
char *RecStrcat(char *dest, const char *src);
char *RecStrstr(const char *haystack, const char *needle);
node_t *RecFlip(node_t *head);
void SortStack(stack_t *stack);

#endif
