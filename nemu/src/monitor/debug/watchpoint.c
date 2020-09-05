#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = &wp_pool[i + 1];
  }
  wp_pool[NR_WP - 1].next = NULL;

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */
WP* gethead() {
	return head;
}

WP* new_wp() {
	if(!free_)
		  assert(0);
	else {
		  WP *p = free_;
		  free_ = free_->next;
		  p->next = head;
		  head = p;
		  return p;
	}
}
void free_wp(WP *wp) {
	if(!wp)
		  assert(0);
	else {
		  if(wp == head) {
			    head = head->next;
			    wp->next = free_;
			    free_ = wp;
		  }
		  else {
			    WP *temp = head;
			    while(temp->next != NULL && temp->next != wp)
				      temp = temp->next;
			    if(!temp->next)
				      assert(0);
			    temp->next = wp->next;
			    wp->next = free_;
			    free_ = wp;
		  }
	}
}

