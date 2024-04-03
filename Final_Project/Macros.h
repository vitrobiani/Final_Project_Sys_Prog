#pragma once
#ifndef MACROS
#define MACROS

#define CLOSE_RETURN(file, x) { fclose(file); return x; }
#define PRINT_RETURN(ptr, str) { if(!ptr) { puts(str); return; }}

#endif // !MACROS