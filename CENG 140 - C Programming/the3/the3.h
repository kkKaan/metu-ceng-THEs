/* Structs */ 
struct flat
{
  int id;
  int initial_bandwidth;
  int is_empty;
  struct flat* next;
  struct flat* prev;
};
typedef struct flat Flat;

struct apartment
{
  char* name;
  int max_bandwidth;
  struct apartment* next;
  struct flat* flat_list;
};
typedef struct apartment Apartment;
/* Structs */

/* Functions */
Apartment* add_apartment(Apartment* head, int index, char* apartment_name, int max_bandwidth);

void add_flat(Apartment* head, char* apartment_name, int index, int flat_id, int initial_bandwidth);

Apartment* remove_apartment(Apartment* head, char* apartment_name);

void make_flat_empty(Apartment* head, char* apartment_name, int flat_id);

int find_sum_of_max_bandwidths(Apartment* head);

Apartment* merge_two_apartments(Apartment* head, char* apartment_name_1, char* apartment_name_2);

void relocate_flats_to_same_apartment(Apartment* head, char* new_apartment_name, int flat_id_to_shift, int* flat_id_list);
/* Functions */