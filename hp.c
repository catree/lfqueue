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

#include "hp.h"

#define MPANIC(x) ; assert(x != NULL)

void ** get_hazard(HPContext *hcontext){
  void **hp_list = hcontext->myhprec->HP;
  void *hptr = NULL;
  

  for (int i = 0; i < K ; i++) {
    hptr = *(hp_list+i);
    if(hptr == NULL){
      return &hptr;
    }
    
  }

  return NULL;
  
}

HPContext *HPInitContext(){
  HPContext *hpcontext = malloc(sizeof(*hpcontext)) MPANIC(hpcontext);

  hpcontext->myhprec = HPRecInit();
  hpcontext->hentry = HPInit();
  hpcontext->get_hp = &get_hazard;

  return hpcontext;
}


HPointer * HPInit(){
  HPointer *hp = malloc(sizeof(*hp)) MPANIC(hp);
  
  memset(hp, sizeof(*hp), 0x00);

  hp->h = 0;
  hp->HPRecHead = NULL;

  return hp;
}


HPRecType * HPRecInit(){
  HPRecType *hprec = malloc(sizeof(*hprec)) MPANIC(hprec);

  hprec->rlist = priqueue_initialize(10);
  hprec->next = NULL;
  hprec->rcount = 0;
  hprec->active = 0;

  for(int i =0; i < K; i++){
    *(hprec->HP+i) = NULL;
  }

  return hprec;
  
}

void PrepareForReuse(Node *node){
  
  /* STUB */
  printf("\nPREPARE FOR REUSE\n");

  free(node);
}


void RetireNode(Node *node, HPContext *hpcontext){

  HPRecType * myHP = hpcontext->myhprec;
  HPRecType *head = hpcontext->hentry->HPRecHead;
  

  priqueue_insertraw(myHP->rlist, node);

  myHP->rcount++;
  
  if(myHP->rcount >= 2){
    Scan(hpcontext);
    /* TODO: Helper will be included here*/
  }

}

void Scan(HPContext *hpcontext){
  Priqueue *plist = priqueue_initialize(10);
  Priqueue *tmplist = NULL;
  
  HPRecType *hprec = hpcontext->hentry->HPRecHead;
  Node* hptr = NULL;

  //Stage 1: Insert all non Null pointers into the list
  
  while(hprec != NULL){
    for (int i = 0; i < K ; i++) {
      hptr = *(hprec->HP+i);
      if(hptr != NULL){

	priqueue_insertraw(plist, hptr);

	
      }
    }
    hprec = hprec->next;      
  }


  HPRecType * myHPRec = hpcontext->myhprec;
  Node * node = NULL;

  //Stage 2: Search plist   
  tmplist = priqueue_popall(myHPRec->rlist);
  myHPRec->rcount = 0;

  node = priqueue_pop(tmplist);
  while(node != NULL){

    if(priqueue_search(plist, (void *)node)){
      
      priqueue_insertraw(myHPRec->rlist, node);
      myHPRec->rcount++;
      
    } else {
      PrepareForReuse(node);
    }
    
    node = priqueue_pop(tmplist);

  }

  priqueue_free(plist);
  
}


