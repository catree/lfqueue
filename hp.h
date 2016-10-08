/*
Copyright (c) 2016, Mike Taghavi (mitghi) <mitghi[at]me.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
