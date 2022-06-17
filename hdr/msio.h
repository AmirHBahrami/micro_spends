#ifndef __MSIO_H
  #define __MSIO_H 1
#endif

#ifndef __MS_ST_H
  #include "./ms_st.h"
#endif

#ifndef __STDIO_H
  #include <stdio.h>
#endif

/* mallocate a record */
REC *ms_mk_rec(char *ttl,char *curr,float amount,char *date);

/* free a record */
/* MACRO:ms_fr_rec(REC *r);*/

/* put a record in csv file */
int ms_put(FILE *csv,REC *r);

/* bulk putting records */
int ms_put_blk(FILE *csv,REC **r);

/* delete from csv FILE */
int ms_del(FILE *csv,REC *r);
