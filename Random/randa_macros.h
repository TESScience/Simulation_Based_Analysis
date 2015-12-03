#ifndef RANDA_MACROS_H
#define RANDA_MACROS_H

#include "randa.h"

#define randa_rand() ((int)(( --_rncnt < 0 ? _nrnbuf() : *_rnbp-- ) >> 1 ))
#define randa_urand() ( --_rncnt < 0 ? _nrnbuf() : *_rnbp-- )

#endif /* ndef RANDA_MACROS_H */