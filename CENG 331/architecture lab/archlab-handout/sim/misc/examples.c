struct Node {
	long data;
	struct Node* left;
	struct Node* right;
};

struct list {
    long value;
    struct list *next;
};

/* NOTE: (void *) 0 is how NULL is defined in C.
   Basically, NULL should correspond to zero in your
   y86-64 code, nothing confusing! */

/* Given an ordered (ascending) linked list, return the kth smallest value. 
 * Return 0 if the the list is empty or there are less than k elements */
long kth_ll(const struct list *head, long k)
{
    long kth = 0;
    /* Go next until you find the kth element. */
    while (head) {
        k--;
    	if(k == 0){
            kth = head->value; /* The value of the kth element. */
            break;
        }
        head = head->next;
    }
    return kth; /* Return the kth element */
}

/* Given a binary search tree, return the kth smallest value. Basically, inorder tree traversal 
 * Return -1 if tree is empty or there are less than k nodes */
long kth_bst(struct Node* root, long *k)
{
    if (root) {
        long candidate = kth_bst(root->left, k);
       
        if (k > 0){
            -- *k;
            if (*k == 0)
                return root->data; /* Return the kth element */
            
            return kth_bst(root->right, k); /* Do the same for right tree*/
        }
        else {
           return candidate; /* The kth element found in left tree */
        }
    }
    return -1; /* Return -1 if the tree is empty */
}

/* Given an ordered (ascending) linked list, insert a new value using the specified location. 
 * Assume all the values are distinct and positive 
 * Return the new head pointer */
struct list * insert_ll(struct list *head, long *array, long value)
{
    *array = value;
    if (!head || head->value > value) { /* The list is empty or the new value is the smallest! */
        *(array+1) = head;
        return array; /* Return the new head */
    } 
    else {
        struct list *temp = head;

        while(temp->next && temp->next->value < value )
            temp = temp->next;
        /* Insert */
        *(array+1) = temp->next;
        temp->next = array;
        
        /* Finally, return the list head. */
        return head;
    }
}