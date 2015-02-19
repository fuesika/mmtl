/*
FACILITY:           nmmtl
MODULE DESCRIPTION: Contains nmmtl_add_to_sorted_list()
AUTHOR(S):          Kevin J. Buchs
CREATION DATE:      Thu Mar 12 09:54:14 1992
COPYRIGHT:          Copyright (C) 1992 by Mayo Foundation. All rights reserved.
*/


/*
 *******************************************************************
 **  INCLUDE FILES
 *******************************************************************
 */

#include "nmmtl.h"

/*

  FUNCTION NAME:  nmmtl_add_to_sorted_list


  FUNCTIONAL DESCRIPTION:

  Add a new keyed item of data to a sorted linked list.  The list consists
  of structures of FLK_KEY_LIST, keyed by a double value, and with an optional
  pointer to additional data given by a char *.

  FORMAL PARAMETERS:

  FLT_KEY_LIST_P *list  - pointer to the sorted list - may need to be created
  double key            - the double key used to sort on
  char *data            - optional additional data, pass NULL if you don'tcare.

  RETURN VALUE:

  None

  CALLING SEQUENCE:

  nmmtl_add_to_sorted_list(FLT_KEY_LIST_P *list,double key,char *data);
  */

void nmmtl_add_to_sorted_list(FLT_KEY_LIST_P *list,double key,char *data) {
  FLT_KEY_LIST_P thelist,newlist;

  /* is this an empty list ? */
  if(*list == NULL) {
    /* it is, just make this the first element on the list */
    newlist = (FLT_KEY_LIST_P)malloc(sizeof(FLT_KEY_LIST));
    newlist->key = key;
    newlist->data = data;
    newlist->next = (FLT_KEY_LIST_P)NULL;
    *list = newlist;
    return;
  } else {
    /* else list exists, will search and add entry if doesn't already exist */
    thelist = *list;

    /* check if it belongs at the start of the list */
    if(thelist->key > key) {
      /* it does, just make this the first element on the list */
      newlist = (FLT_KEY_LIST_P)malloc(sizeof(FLT_KEY_LIST));
      newlist->key = key;
      newlist->data = data;
      newlist->next = thelist;
      *list = newlist;
      return;
    }

    /* Does it match the first element? */
    if(thelist->key == key) return;

    /* Now, traverse the list and determine if it belongs between thelist
       element and the next one */

    while(thelist->next != NULL) {
      /* check if it belongs between */
      if(thelist->next->key > key) {
        /* it does */
        newlist = (FLT_KEY_LIST_P)malloc(sizeof(FLT_KEY_LIST));
        newlist->key = key;
        newlist->data = data;
        newlist->next = thelist->next;
        thelist->next = newlist;
        return;
      }

      /* check if it matched the next */
      if(thelist->next->key == key) return;

      thelist = thelist->next;
    }

    /* It you have reached this point, you need to add on to the list */

    newlist = (FLT_KEY_LIST_P)malloc(sizeof(FLT_KEY_LIST));
    newlist->key = key;
    newlist->data = data;
    newlist->next = (FLT_KEY_LIST_P)NULL;
    thelist->next = newlist;
    return;
  }
}
