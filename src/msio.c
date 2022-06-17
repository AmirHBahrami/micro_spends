#ifndef __MSIO_H
  #include "../hdr/msio.h"
#endif

#ifndef __STDIO_H
  #include <stdio.h>
#endif

#ifndef __STDLIB_H
  #include <stdlib.h>
#endif

#ifndef __STRING_H
  #include <string.h>
#endif

#define ms_fr_rec(r) free(r)
#define MAX_LINE_LIMIT 128

REC *ms_mk_rec(char *ttl,char *curr,float amount,char *date){
  REC *r=(REC *)malloc(sizeof(REC));
  strcpy(r->ttl,ttl);
  strcpy(r->curr,curr);
  r->amount=amount;
  strcpy(r->date,date);
  return r;
}

static void ms_headers(FILE *csv){

  /* if headers aren't present, write them*/
  int res;
  fseek(csv,0,SEEK_SET);
  if(res=fscanf(csv, "title,currency,amount,date\n")==-1){
    fseek(csv,0,SEEK_SET);
    fprintf(csv,"title,currency,amount,date\n");
  }

}

int ms_put(FILE *csv,REC *r){

  ms_headers(csv);
  
  /* positioning and input check */
  if(!r) return 0;
  fseek(csv,0,SEEK_END);
  if(ferror(csv)) return 0;
  
  fprintf(csv,"%s,%s,%.2f,%s\n",r->ttl,r->curr,r->amount,r->date);
  return 1;
}

int ms_put_blk(FILE *csv,REC **r){
  int put=0;
  while(r && *r && ms_put(csv,*r)) ++put;
  return put;
}

int ms_del(FILE *csv,REC *r){

  FILE *cl; // clone file handle
  long int lnl=-1;  // last '\n' character +1
  int found=0;
  char line[128]; // buffer to hold headers

  /* info from reading one record of the file */
  char  ttl[32];
  char  curr[4];
  char  date[11];
  float amount;
  
  /* skip headers */
  fseek(csv,0,SEEK_SET);
  fscanf(csv,"%s\n",line);
  
  /* open a clone file and write headers */
  cl=fopen("data/.clone.csv","a+");
  fprintf(cl,"%s\n",line);

  /* copy each line, excluding rec matches */
  while(!ferror(csv) && !feof(csv)){
    fscanf(csv,"%[a-zA-Z_ ],%[a-zA-Z_ ],%f,%[^,\n]\n",ttl,curr,&amount,date);
    if(strcmp(ttl,r->ttl)==0 && amount==r->amount && strcmp(curr,r->curr)==0 && strcmp(date,r->date)==0){
      found=1;
      continue;
    }
    fprintf(cl,"%s,%s,%.2f,%s\n",ttl,curr,amount,date);
  }
  
  /* not found */
  if(!found){
    fclose(cl);
    fclose(csv);
    remove("data/.clone.csv");
    return -1;
  }
  
  fclose(cl);
  fclose(csv);
  
  /* move */
  remove("data/example.csv");
  rename("./data/.clone.csv","./data/example.csv");

  return 1;
}
