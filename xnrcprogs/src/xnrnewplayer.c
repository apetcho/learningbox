/** Program to add a new player to the ladder.
 * The user is expected to assign a realistic ranking value to the player. */
#include "xnrplayer.h"

static const char *validOpts = "n:r:f:";
static char *otherFile;

#ifdef PROGNAME
#undef PROGNAME
#endif
#define PROGNAME    "xnrnewplayer"
static const char *usage = "usage:\n\t" PROGNAME " -r rank - name [-f file]\n"; 
