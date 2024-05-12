// Comment/uncomment to print debug info
// Basic implementation. Can be enriched e.g. with support to various debug levels
#define DBGPRINT_ON 
#ifdef DBGPRINT_ON
#define DBGPRINT(...) fprintf(stdout, __VA_ARGS__)
#else 
#define DBGPRINT(...) 
#endif 
