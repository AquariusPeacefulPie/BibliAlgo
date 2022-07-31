#include "algorithms.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//La fonction list_create_from que j'ai utilisé à été implémenté par Jérémy Perrin

void array_create(struct array *self) {
	self->capacity=50;
	self->data = calloc(self->capacity,sizeof(int));
	self->size=0;
}

void array_create_from(struct array *self, const int *other, size_t size) {
  self->capacity=50;
	self->data = calloc(self->capacity,sizeof(int));
	self->size=0;
  for(int i = 0; i<size; i++){
      self->data[i] = other[i];
      self->size++;
  }
}

void array_destroy(struct array *self) {
  free(self->data);
  self->data = NULL;
}

bool array_empty(const struct array *self) {
   return (self->size == 0);
}

size_t array_size(const struct array *self) {
  return self->size;
}

bool array_equals(const struct array *self, const int *content, size_t size) {
  if(self->size != size){
  	return false;
  }
  else{
	for(int i=0;i < size ;i++){
		if((self->data[i]) != (content[i])){
			return false;
		}
	}
  return true;
}
}



void array_push_back(struct array *self, int value){
  if (self->size == self->capacity) {
    self->capacity= self->capacity*2;
    int *data = calloc(self->capacity, sizeof(int)); 
    memcpy(data, self->data, self->size * sizeof(int)); 
    free(self->data);
    self->data = data;
  }
  self->data[self->size] = value; 
  self->size += 1;
}


void array_pop_back(struct array *self) {
}

void array_insert(struct array *self, int value, size_t index) {
  array_push_back(self,value);
  for (size_t i = self->size; i > index; i--){
    self->data[i] = self->data[i-1];
  }
  self->size--;
  self->data[index]=value;
}

void array_remove(struct array *self, size_t index) {
	if(index<self->size){
    for(size_t i = index; i<self->size; ++i){
        self->data[i] = self->data[i+1];
    }
    self->data[self->size-1] = 0;
    self->size -= 1;
  }
}

int array_get(const struct array *self, size_t index) {
	int value;
	if(array_empty(self)||(index< 0)||(index > self->size)){	
    		return NULL;
	}
	if(!(array_empty(self)||(index< 0)||(index > self->size))){

		value= self->data[index];
		return value;
  }
}


void array_set(struct array *self, size_t index, int value) {

}

size_t array_search(const struct array *self, int value) {
  
	if(array_empty(self)){
		return 0;}	
	else{
		int i =0;
		while (i<(self->size)){

			if (self->data[i] == value){
				return i;}
			i++;                         
		}

		return i;
	}

}


static size_t search_sorted(const int *data, size_t n, int value, size_t inf, size_t sup){
  if(sup==inf){
    return n;
  }
  size_t mil = (sup+inf)/2;
  if(value<data[mil]){
    return search_sorted(data, n, value, inf, mil);
  }
  if(value>data[mil]){
    return search_sorted(data,n,value,mil+1,sup);
  }
  return mil;
}

size_t array_search_sorted(const struct array *self, int value) {
    return search_sorted(self->data,self->size,value,0,self->size);
}

bool array_is_sorted(const struct array *self) {
   	if (array_empty(self) || self->size == 1 ){
        	return true;
    	}
    	for (int i = 0 ; i< self->size-1;++i){
        	if (self->data[i] >self->data[i+1]){
            		return false;
        	}
    	}
    	return true;
}

static void array_swap(struct array *self, size_t i, size_t j){
  int tmp = self->data[i];
  self->data[i] = self->data[j];
  self->data[j] = tmp;
}


ptrdiff_t array_partition(struct array *self, ptrdiff_t i, ptrdiff_t j) {
    ptrdiff_t pivot_pos = i;
    const int pivot = self->data[pivot_pos];

    array_swap(self,pivot_pos,j);
    ptrdiff_t m = i;
    for(ptrdiff_t k = i ; k<j ; ++k){
        if (self->data[k] < pivot){
            array_swap(self,k,m);
            ++m;
        }
    }
    array_swap(self,m,j);
    return m;
}

static void array_quick_sort_partial(struct array *self,ptrdiff_t i,ptrdiff_t j) {
    if (i<j){
        ptrdiff_t k = array_partition(self,i,j);
        array_quick_sort_partial(self, i, k-1);
        array_quick_sort_partial(self, k+1, j);
    }
}
void array_quick_sort(struct array *self ) {
    array_quick_sort_partial(self, 0, (self->size)-1);
}


void array_heap_sort(struct array *self) {
}

bool array_is_heap(const struct array *self) {
  return true;
}

void array_heap_add(struct array *self, int value) {
}

int array_heap_top(const struct array *self) {
  return 42;
}

void array_heap_remove_top(struct array *self) {
}

/*
 * list
 */

void list_create(struct list *self) {
	self->first =NULL; 
}

void list_create_from(struct list *self, const int *other, size_t size) {
	if(size == 1){
    self->first = malloc(sizeof(struct list_node));
    self->first->data = other[0];
    self->first->next = NULL;
    return;
  }
  self->first = NULL;
  for(long int i = size-1; i > -1 ; --i){
    struct list_node *node = malloc(sizeof(struct list_node));
    node->data = other[i];
    node->next = self->first;
    self->first = node;
  }
}

void list_destroy(struct list *self) {
	struct list_node *tmp=self->first;
	while(tmp!=0)
	{
		struct list_node *next=tmp->next;
		free(tmp);
		tmp=next;
	}
}

bool list_empty(const struct list *self) {
	if(self->first ==NULL){
		return true;
	}
	else
    return false;
}

size_t list_size(const struct list *self) {
	struct list_node *current = self->first;
	int i=0;                 
	if (self->first==NULL){
		return i;
	}
	while(current !=NULL){       
		current	=current->next;
	++i;
	}
	return i; 
}

bool list_equals(const struct list *self, const int *data, size_t size) {
	if (list_size(self)==size)
	{
		struct list_node *tmp =self->first;
		size_t i=0;
		while (tmp!=0)
		{
			if(tmp->data!=data[i])
			{
				return false;
			}
			tmp=tmp->next;
			i++;
		}
		return true;
	}
	return false;
}

void list_push_front(struct list *self, int value) {
	struct list_node *prems = malloc(sizeof(struct list_node));
	prems->data =value;    
	prems->next= self->first;
	self->first =prems;  
}

void list_pop_front(struct list *self) {
	struct list_node *tmp = self->first;
	self->first =self->first->next;
	free(tmp); 
}

void list_push_back(struct list *self, int value) {
	struct list_node *node = malloc(sizeof(struct list_node));

    if(self->first==NULL){
    node -> data = value;
    node -> next = NULL;
    self->first = node;
        return ;
    }

    struct list_node *other = self->first;
    while (other->next != NULL) {
           other = other->next;
    }
  
    node -> data = value;
    node -> next = NULL;
    other -> next = node;
}

void list_pop_back(struct list *self) {
}


void list_insert(struct list *self, int value, size_t index) {
	int i=0;
	if(index==0){
    		list_push_front(self,value);
        return ;
	}
	else{
    
    		if( list_size(self)==index) {
            list_push_back(self,value);
       			return ;}

    		else{

    			struct list_node *node =malloc(sizeof(struct list_node));
    			struct list_node *other = self->first;
             		self->first= other;
    			while((i < index-1) && (other!=NULL) ){
    			other=other->next;
    			++i;
    		}
    		node->data =value;
    		node->next=other->next;
    		other->next= node;
    		}
	}
}


void list_remove(struct list *self, size_t index) {
	if ( (self->first==NULL)  || (  index) > list_size(self) ){
            	return ;}

	int i=0;
	struct list_node *current = self->first;   

	if(index == 0){
            	self->first = current->next;
            	free(current);
            	return;
        }
	while((current->next !=NULL) &&(i != index-1)){
            	current=current->next;
            ++i;
	}
	if( i==index-1){
    		struct list_node *prochain = current->next;   
   		current->next=current->next->next;	
    		free(prochain);
	}
}

int list_get(const struct list *self, size_t index) {
int i=0;
    struct list_node *current = self->first; 

    if ( (self->first==NULL)  || (  index) > list_size(self) ){
           return i;}
    else{
        while( !((current!=NULL) &&  (i!= index))==false ){
            current=current->next;
            i++;
        }
        if(current == NULL){return NULL;}
        else{
                return (current->data);
        }
    }
}
void list_set(struct list *self, size_t index, int value) {
	
}

size_t list_search(const struct list *self, int value) {
	if (self->first==NULL){   
		return list_size(self);
	}
	else{
    		size_t i=0;
		struct list_node *current = self->first;
		while((current->next!=NULL) && (current->data !=value)){
			current=current->next;
			++i;
		}
    		if (current->data ==value)
        		return i;
    		else 
			return list_size(self);	}	




	if(self->first == NULL){
        	return true;
    	}
}

bool list_is_sorted(const struct list *self) {
  	if(self->first == NULL){
        	return true;
    	}
    	struct list_node *current = self->first;
       	while(current->next !=NULL ){
          	if(current->data  > current->next->data){
                	return false;
            	}
            	current = current->next;
       	}
    	return true;
}

void list_split(struct list *self, struct list *out1, struct list *out2) {
}

void list_merge(struct list *self, struct list *in1, struct list *in2) {
}

void list_merge_sort(struct list *self) {
}


/*
 * tree
 */

void tree_create(struct tree *self) {
	self -> root = NULL;
}
static void destroy(struct tree_node *self){
	if(self->left!=NULL){
      		destroy(self->left);
    	}
	if(self->right!=NULL){
        	destroy(self->right);
    	}  	
    	free(self);
}
void tree_destroy(struct tree *self) {
	if(self->root!=NULL){
        destroy(self->root);
    }
    else{
        free(self->root);
    }
}

bool contains(struct tree_node *self,int value){
	if(self==NULL)
    		return false;
	if(value < self->data){
    		return contains(self->left,value);
	}
	if(value > self->data){
    		return contains(self->right,value);
	}
	return true;
}
bool tree_contains(const struct tree *self, int value) {
	return contains(self->root,value);
}


bool tree_insert(struct tree *self, int value) {
  return false;
}


bool tree_remove(struct tree *self, int value) {
  return false;
}

bool tree_empty(const struct tree *self) {
	if(self -> root == NULL){
		return true;}
	else{
		return false;
	}
}

static size_t taille(const struct tree_node *self) {
	size_t size=0;
	if(self->left != NULL){
		size=size + taille(self->left);
	}
	if(self->right != NULL){
		size=size + taille(self->right);
	}	    
	return size+1;	
}
size_t tree_size(const struct tree *self) {
	if (tree_empty(self)){
		return 0;
	}
	return taille(self->root);
}

static size_t hauteur(struct tree_node *self){
    size_t left=0;
    size_t right=0;
    if (self->left !=NULL){
        left = hauteur(self->left);
    }
    if (self->right !=NULL){
        right = hauteur(self->right);
    }
        
    if (left>right)
        return left+1;
    else{
        return right+1;
    }
    return 0; 
} 
size_t tree_height(const struct tree *self) {
  
	if (tree_empty(self)){
		return 0;
	}
    	return taille(self->root);
}

void tree_node_walk_pre_order(const struct tree_node *self, tree_func_t func, void *user_data)  {
    	if(self==NULL){
        	return;
    	}
    	func(self->data, user_data);
    	tree_node_walk_pre_order(self->left, func, user_data);
    	tree_node_walk_pre_order(self->right, func, user_data);
        
}       
void tree_walk_pre_order(const struct tree *self, tree_func_t func, void *user_data)  {
	tree_node_walk_pre_order(self->root, func, user_data);
}

void tree_node_walk_in_order(const struct tree_node *self, tree_func_t func, void *user_data)  {
    	if(self==NULL){
        	return;
    	}
    	tree_node_walk_in_order(self->left, func, user_data);
    	func(self->data, user_data);
    	tree_node_walk_in_order(self->right, func, user_data);
}
void tree_walk_in_order(const struct tree *self, tree_func_t func, void *user_data) {
	tree_node_walk_in_order(self->root, func, user_data);
}
void tree_node_walk_post_order(const struct tree_node *self, tree_func_t func, void *user_data)  {
    if(self==NULL){
        return;
    }
    tree_node_walk_post_order(self->left, func, user_data);
    tree_node_walk_post_order(self->right, func, user_data);
    func(self->data, user_data);
}

void tree_walk_post_order(const struct tree *self, tree_func_t func, void *user_data) {
	tree_node_walk_post_order(self->root, func, user_data);
}
