#pragma once
#ifndef MACROS
#define MACROS

#define CLOSE_RETURN_INT(file, x) { fclose(file); return x; }
#define PRINT_RETURN(ptr, str) { if(!ptr) { puts(str); return; }}
#define PRINT_FREE_RETURN(ptr1, ptr2, str) { if(!ptr1) { puts(str); free(ptr2); return; }}
#define INT_FROM_USER(x, y, z, str) { do { scanf("%d", &x); if (x <= y || x >= z) { puts(str); } } while (x <= y || x >= z); }

#endif // !MACROS