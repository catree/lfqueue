#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pqueue.h"

#ifndef HP_H_
#define HP_H_


#define K 2 // TODO

typedef struct _hp_context HPContext;

typedef void ** (*hp_func)(HPContext *);

typedef struct _hprectype {  
  void *HP[K]; // TODO
  Priqueue *rlist;
  
  struct _hprectype *next;
  
  int active;
  int rcount;
  

} HPRecType;


typedef struct _hp {
  HPRecType *HPRecHead;
  int h;
  
} HPointer;


typedef struct _hp_context {
  HPRecType *myhprec;
  HPointer *hentry;

  hp_func get_hp;
  
} HPContext;




HPointer * HPInit();
void Scan(HPContext *);
/* void Scan(HPRecType *, HPointer *); */

HPRecType * HPRecInit();
HPointer * HPInit();

HPContext *
HPInitContext();


void RetireNode(Node *, HPContext *);

#endif
