#include <stdio.h>
#include <stdlib.h>
#include "the3.h"

int are_they_the_same(char* a, char* b) // checks if 2 strings are equal.
{
    int x = 0;
    while(a[x] != '\0')
    {
        if(b[x] == '\0'){return 0;}
        else if(a[x] != b[x]){return 0;}
        ++x;
    }
    if(b[x] != '\0'){return 0;}
    return 1;
}

void freeEr(Flat* flatlist) // A simple clear function for the linked list.
{
    Flat* to_be_removed;
    if(!flatlist){free(flatlist);}
    while(flatlist)
    {
        to_be_removed = flatlist;
        flatlist = flatlist->next;
        free(to_be_removed);
    }
}

Apartment* add_apartment(Apartment* head, int index, char* apartment_name, int max_bandwidth)
{
    Apartment* temp = malloc(sizeof(Apartment));
    Apartment* newAp = malloc(sizeof(Apartment));
    Apartment* prev;
    int a = 0;

    newAp->name = apartment_name;
    newAp->max_bandwidth = max_bandwidth;
    newAp->flat_list = NULL;

    if(!head)
    {
        newAp->next = newAp;
        head = newAp;
        return head;
    }

    temp=head;
    prev=NULL;

    do // In this THE most of the loops are do while since it is an implementation for circular linked list.
    {
        if(a == index && index)
        {
            prev->next = newAp;
            newAp->next = temp;
            return head;
        }

        ++a;
        prev = temp;
        temp = temp->next;
    } while (temp != head); // It checks if the temp became head again.

    prev->next = newAp;
    newAp->next = temp;

    if(!index){head = newAp;}
    return head;
}

void add_flat(Apartment* head, char* apartment_name, int index, int flat_id, int initial_bandwidth)
{
    Apartment* temp = malloc(sizeof(Apartment)), *selected=malloc(sizeof(Apartment)); 
    Flat* temp_flat1 = malloc(sizeof(Flat)), *temp_flat2 = malloc(sizeof(Flat)), *newOne = malloc(sizeof(Flat));
    int a=0, b=0, c=1, max_bandwidth, used_bandwidth=0;

    temp = head;
    while(!are_they_the_same(temp->name, apartment_name)){temp = temp->next;} // Finding the apartment to add flat.

    selected = temp;
    temp_flat1 = selected->flat_list;
    max_bandwidth = selected->max_bandwidth;

    newOne->id = flat_id;
    newOne->initial_bandwidth = initial_bandwidth > max_bandwidth ? max_bandwidth : initial_bandwidth; 
    newOne->is_empty = 0;

    if(!temp_flat1)
    {
        newOne->next = NULL;
        newOne->prev = NULL;
        selected->flat_list = newOne;
        c=0;
    }

    while(c)
    {
        used_bandwidth += temp_flat1->initial_bandwidth;

        if(temp_flat1->next != NULL)
        {
            temp_flat1 = temp_flat1->next;
            ++a;
            continue;
        }

        if((max_bandwidth - used_bandwidth) < initial_bandwidth){newOne->initial_bandwidth = (max_bandwidth - used_bandwidth);}

        if(a < index)
        {
            temp_flat1->next = newOne;
            newOne->prev = temp_flat1;
            break;
        }

        if(!index)
        {
            temp_flat2 = selected->flat_list;
            selected->flat_list = newOne;
            newOne->next = temp_flat2;
            newOne->prev = NULL;
            temp_flat2->prev = newOne;
            break;
        }

        for(b=0; b < (a-index); ++b){temp_flat1 = temp_flat1->prev;}

        temp_flat2 = temp_flat1->prev;

        temp_flat2->next = newOne;
        newOne->next = temp_flat1;
        newOne->prev = temp_flat2;
        temp_flat1->prev = newOne;

        break;
    }
}

Apartment* remove_apartment(Apartment* head, char* apartment_name)
{
    Apartment* temp = head, *prev = NULL;
    int a=0;

    if(temp->next == temp || !temp){freeEr(temp->flat_list); free(temp); return NULL;}

    do
    {
        if(are_they_the_same(temp->name, apartment_name) && a)
        {
            prev->next = temp->next;
            freeEr(temp->flat_list);
            free(temp);
            return head;
        }
        ++a;
        prev = temp;
        temp = temp->next;

    } while (temp != head);

    prev->next = temp->next;
    head = temp->next;
    freeEr(temp->flat_list);
    free(temp);
    return head;
}

void make_flat_empty(Apartment* head, char* apartment_name, int flat_id)
{
    Apartment* temp = head;
    Flat* selected = malloc(sizeof(Flat));

    while(!are_they_the_same(temp->name, apartment_name)){temp = temp->next;}
    
    selected = temp->flat_list;

    while(selected->id != flat_id){selected = selected->next;}

    selected->is_empty = 1;
    selected->initial_bandwidth = 0;
}

int find_sum_of_max_bandwidths(Apartment* head)
{
    int summ = 0;
    Apartment *temp = head;

    if(!head){return 0;}

    do
    {
        summ += temp->max_bandwidth;
        temp = temp->next;

    } while (temp != head);

    return summ;
}

Apartment* merge_two_apartments(Apartment* head, char* apartment_name_1, char* apartment_name_2)
{
    Apartment* temp1 = head, *temp2 = head;
    Flat* fl1 = malloc(sizeof(Flat)), *fl2 = malloc(sizeof(Flat));

    while(!are_they_the_same(temp1->name, apartment_name_1)){temp1 = temp1->next;}
    while(!are_they_the_same(temp2->name, apartment_name_2)){temp2 = temp2->next;}

    temp1->max_bandwidth += temp2->max_bandwidth;

    fl1 = temp1->flat_list, fl2 = temp2->flat_list;

    while(fl1 && fl1->next != NULL){fl1 = fl1->next;}

    if(!fl1)
    {
        temp1->flat_list = fl2;
    }
    else
    {
        fl1->next = fl2;
        if(fl2){fl2->prev = fl1;}
    }

    temp2->flat_list = NULL;

    head = remove_apartment(head, apartment_name_2);

    return head;
}

void relocate_flats_to_same_apartment(Apartment* head, char* new_apartment_name, int flat_id_to_shift, int* flat_id_list)
{
    Apartment* temp1 = head;
    Flat* select = malloc(sizeof(Flat)), *temp_flat = malloc(sizeof(Flat)), *last_added = malloc(sizeof(Flat));
    int a=0, list_index=0;

    while(!are_they_the_same(temp1->name, new_apartment_name)){temp1 = temp1->next;}

    select = temp1->flat_list;

    while(select->id != flat_id_to_shift){select = select->next; a++;}

    if(a){last_added = select->prev;}

    while(flat_id_list[list_index])
    {
        Apartment* temp2 = head;
        do
        {
            if(are_they_the_same(temp2->name, new_apartment_name)){temp2 = temp2->next; continue;}

            temp_flat = temp2->flat_list;

            while(temp_flat != NULL && temp_flat->id != flat_id_list[list_index]){temp_flat = temp_flat->next;}

            if(!temp_flat){temp2 = temp2->next; continue;}

            else
            {
                select->prev = temp_flat;
                if(temp_flat->prev != NULL){temp_flat->prev->next = temp_flat->next;}
                else{temp2->flat_list = temp_flat->next;}

                if(temp_flat->next != NULL){temp_flat->next->prev = temp_flat->prev;}
                temp_flat->next = select;

                if(!a)
                {
                    a++;
                    temp_flat->prev = NULL;
                    temp1->flat_list = temp_flat;
                }
                else
                {
                    last_added->next = temp_flat;
                    temp_flat->prev = last_added;
                }  
            }
            
            last_added = temp_flat;
            break;

        } while (temp2 != head);
        
        temp2->max_bandwidth -= temp_flat->initial_bandwidth;
        temp1->max_bandwidth += temp_flat->initial_bandwidth;
        ++list_index;
    }
}