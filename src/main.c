#ifndef __MSIO_H
  #include "../hdr/msio.h"
#endif

#ifndef __STDIO_H
  #include <stdio.h>
#endif

#ifndef __STDLIB_H
  #include <stdlib.h>
#endif

int main(int argc,char **argv){
  
  /* doing a test for now */
  REC *r=ms_mk_rec(
    "wallmart_junk",
    "EUR",
    0.99f,
    "2022-06-11"
  );
  REC *r1=ms_mk_rec(
    "wallmart_junk",
    "EUR",
    2.99f,
    "2022-06-14"
  );
  REC *r2=ms_mk_rec(
    "pizza",
    "EUR",
    6.99f,
    "2022-06-11"
  );
  FILE *csv=fopen("./data/example.csv","a+");
  if(ferror(csv))
    fprintf(stderr,"could not open the file\n");

  else{
    ms_put(csv,r);
    ms_put(csv,r1);
    ms_put(csv,r2);
    ms_del(csv,r); 
  }

  /* finally block - kind of! */
  free(r);
  // fclose(csv);
  return 0;
}
