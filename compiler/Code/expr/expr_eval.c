#include "library.h"
#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include "dump_ast.h"

uint64_t* state;

uint64_t* lookup(uint64_t* id){
  uint64_t* cur_list = state;
  while(!is_empty(cur_list))
  {
    uint64_t* cur_elt = get_elt(cur_list);
    if(string_compare(id,fst(cur_elt))
    {
      return make_int(snd(cur_elt));
    }
    cur_list = next_elt(cur_list);
  }

  return NULL;
}

void set(uint64_t* id, uint64_t val){
  uint64_t* cur_list = state;
  while(!is_empty(cur_list))
  {
    uint64_t* cur_elt = get_elt(cur_list);
    if(string_compare(id,fst(cur_elt))
    {
      array_set(cur_elt,2,&val);
    }
    cur_list = next_elt(cur_list);
  }

  cons(pair(id,&val),state);
}

uint64_t eval_ast(uint64_t* ast) {
  /* Initialisation de l'état */
  state = nil();

  if(ast != NULL && fst(ast)==TYPE_PAIR)
  {
    
  }

  return 0;
}
