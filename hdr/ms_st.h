#ifndef __MS_ST_H
  #define __MS_ST_H 1
#endif

static int id_ctr=1; /* counter */

typedef struct rec_st{
  char ttl[32];
  char curr[4]; /* currency USD/EUR/etc. */
  float amount;
  char date[11]; /* YYYY-MM-DD */
}REC;

