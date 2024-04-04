#pragma once
#ifndef MACROS
#define MACROS

#define CLOSE_RETURN_INT(file, x) { fclose(file); return x; }
#define PRINT_RETURN(ptr, str) { if(!ptr) { puts(str); return; }}
#define PRINT_FREE_RETURN(ptr1, ptr2, str) { if(!ptr1) { puts(str); free(ptr2); return; }}

#endif // !MACROS