# Set the source files that make up the library
set(MOVAVG_SRCS
   movavg.h movavg.c
)

# Set the library type (can be static or dynamic )
set(LIB_TYPE STATIC)

# Create the library
add_library(MovAvgLib ${LIB_TYPE} ${MOVAVG_SRCS})


