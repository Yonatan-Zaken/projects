#ifndef __SHARED_H__
#define __SHARED_H__

#ifdef __cplusplus 
int Foo(int a, int b);
void Foo(char c);
void Foo(float f);

extern "C" 
{
#endif

void Bar(char c);
#ifdef __cplusplus
}
#endif

#endif
