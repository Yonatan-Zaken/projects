#include <stdio.h>

/*
typedef struct Person
{
	char name[32];
	int age;
} person_t;

typedef struct List 
{
	person_t *person;
	struct List *next;
	int key;
} list_t;
*/

typedef struct Person person_t;
typedef struct List list_t;

int x = 5.5;		

void *ll_find(list_t *ll, int key);

void foo(list_t *ll, int key, int age)
{
	void *vv = ll_find(ll, key);
	person_t *p = static_cast<person_t*>(vv);
	p->age = age;
}

int main()
{
	int x = 5;
	

	return 0;	
}
