#ifndef MACRO_ALLOC
#define MACRO_ALLOC

#define MALLOC(_p,_t,_n) do{ \
    (_p) = malloc ( (_n) * sizeof(_t)); \
    if( (_p) == NULL ) \
    { \
	     fprintf(stderr,"Allocation impossible dans le fichier :%s ligne : %s",__FILE__,__LINE__);\
	     exit(EXIT_FAILURE); \
    } \
}while(0)

#define CALLOC(_p,_t,_n) do{ \
    (_p) = calloc ( (_n) , sizeof(_t) ); \
    if( (_p) == NULL ) \
    { \
	     fprintf(stderr,"Allocation impossible dans le fichier :%s ligne : %s",__FILE__,__LINE__);\
	     exit(EXIT_FAILURE); \
    } \
}while(0)

#define REALLOC(_p,_t,_n) do{ \
    (_t) * temp; \
    temp = realloc ( (_p) , (_n) * sizeof(_t)); \
    if( temp == NULL ) \
    { \
	     fprintf(stderr,"Allocation impossible dans le fichier :%s ligne : %s",__FILE__,__LINE__);\
	     free( (_p) ); \
	     exit(EXIT_FAILURE); \
    } \
    else \
    { \
	     (_p) = temp; \
    } \
}while(0)

#define FREE(_p) do{ \
	 free(_p); \
         (_p) = NULL; \
}while(0)


#endif
