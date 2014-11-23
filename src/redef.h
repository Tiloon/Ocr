#ifndef REDEF_H
#define REDEF_H

#define LOG_MSG(...) if(flags()->verbosity) printf(__VA_ARGS__);
#define FREE(a) if(a!=0){free(a);a=0;}
#define LOG_ALLOC_ERR() \
    fprintf(stderr,"Alloc error %s:%i\n",__FILE__,__LINE__);

#endif
