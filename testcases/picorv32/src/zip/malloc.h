/*
 * malloc.c
 */
#ifdef LOGALLOC
void *smalloc(char *file, int line, int size);
void *srealloc(char *file, int line, void *p, int size);
void sfree(char *file, int line, void *p);
#define smalloc(x) smalloc(__FILE__, __LINE__, x)
#define srealloc(x, y) srealloc(__FILE__, __LINE__, x, y)
#define sfree(x) sfree(__FILE__, __LINE__, x)
#else
void *smalloc(int size);
void *srealloc(void *p, int size);
void sfree(void *p);
#endif


#define snew(type) ( (type *) smalloc (sizeof (type)) )
#define snewn(number, type) ( (type *) smalloc ((number) * sizeof (type)) )
#define sresize(array, number, type) \
	( (type *) srealloc ((array), (number) * sizeof (type)) )
#define lenof(array) ( sizeof(array) / sizeof(*(array)) )
 