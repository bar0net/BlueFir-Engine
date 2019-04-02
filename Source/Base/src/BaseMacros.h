#ifndef BF_BASE_MACROS

#if(BF_DEBUG)
#include <assert.h>
#define ASSERT(x) assert(x)

#else
#define ASSERT(x)	

#endif

#define UID unsigned long long

#endif // !BF_BASE_MACROS

