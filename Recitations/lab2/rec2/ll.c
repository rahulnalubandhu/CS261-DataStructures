#include <stdio.h>
#include <stdlib.h>

#include "ll.h"

struct node* add_two_num (struct node* l1, struct node* l2)
{
	struct node *l_1, *l_2;
	struct node *head = NULL; // to track to count
	struct node **lp = &head; // **lp stores address of head
	int carry = 0, sum = 0, val1, val2;
	for (l_1 = l1, l_2 = l2; l_1 || l_2;){
		if (l_1){
			val1 = l_1->val;
			}else{
			val1 = 0;
		}
		if (l_2){
			val2 = l_2->val;
			}else{
			val2  = 0;
		}
		sum = val1 + val2 + carry;
		*lp = malloc(sizeof(struct node));
		(*lp)->val = sum % 10;
		(*lp)->next = NULL;
		carry = sum / 10;
		lp = &(*lp)->next;
		if (l_1){
			l_1 = l_1->next;
			}else{
			l_1 = NULL;
		}
		if(l_2){
			l_2 = l_2->next;
			}else{
			l_2 = NULL;
		}
	}
	if (carry) {
		*lp = malloc(sizeof(struct node));
		(*lp)->val = carry;
		(*lp)->next = NULL;
	}
	return head;
}

