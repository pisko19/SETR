

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdint.h>
#include "../src/sc_types.h"
#include "../src-gen/Statechart_required.h"
#include "../src-gen/Statechart.h"

#ifdef __cplusplus
extern "C"
{
#endif 

void statechart_display(Statechart* handle, const sc_integer Type);

#ifdef __cplusplus
}
#endif 

#endif
