#include "library.h"
#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include "dump_ast.h"

uint64_t* state;

uint64_t lookup(uint64_t* id){
  uint64_t* cur_list = state;
  while(!is_empty(cur_list))
  {
    uint64_t* cur_elt = get_elt(cur_list);
    uint64_t *cur_id = string_get(fst(cur_elt));
    printf1("%s\n",cur_id);
    if(string_compare(string_get(id),cur_id))
    {
      return int_get(snd(cur_elt));
    }
    cur_list = next_elt(cur_list);
  }

  print((uint64_t*)"unassigned variable");
  exit(-1);;
}

void set(uint64_t* id, uint64_t val){
  uint64_t* cur_list = state;
  while(!is_empty(cur_list))
  {
    uint64_t* cur_elt = get_elt(cur_list);
    if(string_compare(string_get(id),string_get(fst(cur_elt))))
    {
      array_set(cur_elt,2,make_int(val));
    }
    cur_list = next_elt(cur_list);
  }

  cons(pair(make_string(id),make_int(val)),state);
}

uint64_t eval_expr(uint64_t* expr){
  if(node_type(expr) == TYPE_PAIR){
    uint64_t op = int_get(fst(expr));
    if(op == EINT)
      return int_get(snd(expr));
    else if(op == EVAR)
      return lookup(snd(expr));
    else
    {
      exit(1);
    }
    
  }
  else if (node_type(expr) == TYPE_TRIPLE) { // triple
    uint64_t op = int_get(fst(expr));
    if(op == EADD)
      return eval_expr(snd(expr)) + eval_expr(thr(expr));

    if(op == ESUB)
      return eval_expr(snd(expr)) - eval_expr(thr(expr));

    if(op == EMUL)
      return eval_expr(snd(expr)) * eval_expr(thr(expr));

    if(op == EDIV)
      return eval_expr(snd(expr)) / eval_expr(thr(expr));

    exit(3);
  }
  else
  {
    exit(2);
  }
  
}

uint64_t eval_ast(uint64_t* ast) {
  /* Initialisation de l'état */
  state = nil();

  if(ast != NULL && node_type(ast)==TYPE_PAIR)
  {
    /* Assignations */
    uint64_t* list_assign = fst(ast);
    uint64_t* ret = snd(ast);

    while(!is_empty(list_assign))
    {
      uint64_t* elt = get_elt(list_assign);
      set(fst(elt),eval_expr(snd(elt)));
      list_assign = next_elt(list_assign);
    }

    return eval_expr(ret);

  }

  return 0;
}
