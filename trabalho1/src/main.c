/******************************************************************************
 *                     TRABALHO 1 - CAOS AÉREO EM BACALHAU                    *
 *                                                     by: T.H. de Camargo J. *
 ******************************************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/******************************************************************************
 *                                 DEFINITIONS                                *
 ******************************************************************************/

#define MAX_AIRCRAFTS 10000000LL
#define INFTY __LONG_LONG_MAX__
#define llint long long int
#define square(x) ((x)*(x))


typedef struct {
    llint id;
    llint pos_x;
    llint pos_y;
} Aircraft;

typedef struct Pair {
    llint aircraft_a, aircraft_b;
    llint distance;
} Pair;

typedef struct {
    Pair *q;
    int sorted;
    llint size, max_size;
} Stack;


/******************************************************************************
 *                              MEMORY ALLOCATION                             *
 ******************************************************************************/

void mem_alloc(void *mem, llint n_items, size_t item_size) {
    mem = malloc(n_items * item_size);
    if (mem != NULL) return;
    fprintf(stderr, "ERROR: malloc malfunction, could not reserve heap memory!\n");
    exit(EXIT_FAILURE);
}

/******************************************************************************
 *                                 COMPARATORS                                *
 ******************************************************************************/

int compare_aircraft_x_positions(const void* item_a, const void* item_b) {
    Aircraft *a = (Aircraft *) item_a, *b = (Aircraft *) item_b;
    llint x_comparison = b->pos_x - a->pos_x;
    
    // Compare x coordinates
    if (x_comparison < 0) return -1; // b comes first
    if (x_comparison > 0) return 1;  // a comes first

    // Same position
    return 0; 
}

int compare_aircraft_y_positions(const void* item_a, const void* item_b) {
    Aircraft *a = (Aircraft *) item_a, *b = (Aircraft *) item_b;
    llint y_comparison = b->pos_y - a->pos_y;

    // Compare y coordinates
    if (y_comparison < 0) return -1; // b comes first
    if (y_comparison > 0) return 1;  // a comes first

    // Same position
    return 0; 
}

int compare_pairs(const void *item_a, const void *item_b) {
    Pair *a = (Pair *) item_a, *b = (Pair *) item_b;
    llint air_a_comparison = b->aircraft_a - a->aircraft_a,
          air_b_comparison = b->aircraft_b - a->aircraft_b;

    // Compare y coordinates
    if (air_a_comparison < 0) return -1; // b comes first
    if (air_a_comparison > 0) return 1;  // a comes first

    if (air_b_comparison < 0) return -1; // b comes first
    if (air_b_comparison > 0) return 1;  // a comes first

    // Same position
    return 0; 
}


/******************************************************************************
 *                             DISTANCE CALCULATION                           *
 ******************************************************************************/

llint distance_between_aircrafts(const Aircraft a, const Aircraft b) {
    return (square(a.pos_x - b.pos_x) + square(a.pos_y - b.pos_y));
}


/******************************************************************************
 *                                    STACK                                   *
 ******************************************************************************/

Stack *stack = NULL;

void merge_sort(
    void *vect,
    size_t v_item_size,
    llint size,
    int (* compare_positions)(const void *, const void *)
); // promisse for sorting the stack;

void init_pair(const Aircraft a, const Aircraft b, Pair *pair) {
    pair->aircraft_a = a.id;
    pair->aircraft_b = b.id;

    // Mantain i < j rule
    if (a.id > b.id) {
        pair->aircraft_a = b.id;
        pair->aircraft_b = a.id;
    }

    pair->distance = distance_between_aircrafts(a, b);
}

void print_pair(Pair *pair) {
    llint id_i = pair->aircraft_a,
          id_j = pair->aircraft_b;
    
    if (pair->aircraft_a > pair->aircraft_b) {
        id_i = pair->aircraft_b;
        id_j = pair->aircraft_a;
    }

    printf("(%lld,%lld)\n", id_i, id_j);
}

void create_stack(llint size) {
    stack = (Stack *) malloc(sizeof(Stack));
    stack->q = malloc(size * sizeof(Pair));
    stack->sorted = 0;
    stack->max_size = size;
    stack->size = 0;
}

llint get_stack_size() {
    if (stack == NULL) return 0;
    return stack->size;
}

void sort_stack() {
    merge_sort(stack->q, sizeof(Pair), get_stack_size(), compare_pairs);
    stack->sorted = 1;
}

void delete_stack() {
    if (stack == NULL) return;
    free(stack->q);
    free(stack);
}

void stack_push(Pair new_pair) {
    if (stack == NULL) return;

    Pair pair, p = stack->q[0];
    llint i = 0;

    if (stack->size + 1 >= stack->max_size) return;
    stack->q[stack->size] = new_pair;
    stack->size++;
}

void stack_pop(Pair *pair) {
    if (stack == NULL || stack->size == 0) return;
    
    *pair = stack->q[stack->size-1];
    stack->size--;
}

void clean_stack_duplicates() {
    if (stack == NULL) return;

    if (get_stack_size() < 2) return;

    if (!stack->sorted) sort_stack();

    Pair *pairs = stack->q, pair_a, pair_b, aux;
    llint uniques_size = 1;

    pair_a = pairs[0];
    for (llint i = 1; i < get_stack_size(); i++) {
        pair_b = pairs[i];
        if (compare_pairs(&pair_a, &pair_b) == 0) {
            pairs[uniques_size - 1] = pair_b;
        } else {
            pairs[uniques_size++] = pair_b;
            pair_a = pair_b;
        }
    }

    stack->size = uniques_size;
}

void clear_stack() {
    if (stack == NULL) return;
    stack->size = 0;
}

void print_stack() {
    if (stack == NULL) return;
    llint i = 0;
    while (i < stack->size) print_pair(&stack->q[i++]);
}


/******************************************************************************
 *                                  MERGESORT                                 *
 ******************************************************************************/

void combine_merge_sort(
    void *v,
    size_t v_item_size,
    llint start, llint middle, llint end,
    char *left_vector,
    char *right_vector,
    int (* compare)(const void *, const void *)
) {
    char *vect = (char *)v;
    char *left_item, *right_item;
    llint lv_i = 0, rv_i = 0, lv_size, rv_size, i;
    int comparison;

    for (i = start; i <= end; i++) {
        if (i <= middle) {
            memcpy(left_vector + (lv_i * v_item_size), vect + (i * v_item_size), v_item_size);
            lv_i++;
        } else {
            memcpy(right_vector + (rv_i * v_item_size), vect + (i * v_item_size), v_item_size);
            rv_i++;
        }
    }

    lv_size = lv_i;
    rv_size = rv_i;
    lv_i = 0;
    rv_i = 0;
    i = start;
    while (lv_i < lv_size && rv_i < rv_size) {
        left_item = left_vector + (lv_i * v_item_size);
        right_item = right_vector + (rv_i * v_item_size);

        comparison = compare(left_item, right_item);

        if (comparison >= 0) {
            memcpy(vect + (i * v_item_size), left_item, v_item_size);
            lv_i++;
        } else {
            memcpy(vect + (i * v_item_size), right_item, v_item_size);
            rv_i++;
        }
        i++;
    }

    while (lv_i < lv_size) {
        memcpy(vect + (i * v_item_size), left_vector + (lv_i * v_item_size), v_item_size);
        lv_i++;
        i++;
    }

    while (rv_i < rv_size) {
        memcpy(vect + (i * v_item_size), right_vector + (rv_i * v_item_size), v_item_size);
        rv_i++;
        i++;
    }
}

void recursive_merge_sort(
    void *vect,
    size_t v_item_size,
    llint start, llint end,
    char *left_vector,
    char *right_vector,
    int (* compare)(const void *, const void *)
) {
    llint middle = start + (end - start) / 2;
    
    if (start >= end) return; // base
    
    // Divide
    recursive_merge_sort(vect, v_item_size, start, middle, left_vector, right_vector, compare);
    recursive_merge_sort(vect, v_item_size, middle + 1, end, left_vector, right_vector, compare);

    // Conquer
    combine_merge_sort(vect, v_item_size, start, middle, end, left_vector, right_vector, compare);

}

void merge_sort(
    void *vect,
    size_t v_item_size,
    llint size,
    int (* compare_positions)(const void *, const void *)
) {
    char *left_vector = malloc((size/2+1)*v_item_size),
         *right_vector = malloc((size/2+1)*v_item_size);

    recursive_merge_sort(vect, v_item_size,  0, size - 1, left_vector, right_vector, compare_positions);

    free(left_vector);
    free(right_vector);
}


/******************************************************************************
 *                                  SOLUTION                                  *
 ******************************************************************************/

void update_stack_min(Pair pair) {
    Pair stack_pair;
    llint pair_dist = pair.distance;

    if (get_stack_size() == 0) {
        stack_push(pair);
        return;
    }

    stack_pop(&stack_pair);
    if (pair_dist > stack_pair.distance) {
        stack_push(stack_pair);
        return;
    }

    stack_push(stack_pair);
    if (pair_dist < stack_pair.distance) clear_stack();

    stack_push(pair);
}

llint find_partition_minimum_distance(Aircraft *partition, llint mid_x, llint p_size, llint prev_min_d) {
    Pair pair;
    llint min_dist = prev_min_d, oposite_size_aircrafts;

    merge_sort(partition, sizeof(Aircraft), p_size, compare_aircraft_y_positions);

    for (llint i = 0; i < p_size; i++)
        for (llint j = i + 1; j < p_size; j++) {
            if (square(partition[j].pos_y - partition[i].pos_y) > min_dist) break;

            init_pair(partition[i], partition[j], &pair);
            if (pair.distance <= min_dist) {
                min_dist = pair.distance;
                update_stack_min(pair);
            }
        }

    return min_dist;
}

llint base_case_fmd(Aircraft *aircrafts, llint start, llint end) {
    llint min_dist = INFTY;
    Pair pair, queue_pair, min_pair;

    if (end - start + 1 == 1) return min_dist;

    for (llint i = start; i < end; i++) {
        for (llint j = i + 1; j <= end; j++) {
            init_pair(aircrafts[i], aircrafts[j], &pair);
            if (min_dist >= pair.distance) {
                min_dist = pair.distance;
                min_pair = pair;
                update_stack_min(min_pair);
            }

        }
    }

    return min_dist;
}


llint recursive_fmd(Aircraft *aircrafts, llint start, llint end) {
    llint middle = start + (end - start) / 2, j, middle_x_pos = aircrafts[middle].pos_x;
    llint mld, mrd, md, pmd;
    Pair pair, pair_b, pair_c, queue_pair, min_pair;
    Aircraft *partition;

    if (end - start + 1 <= 3) {
        return base_case_fmd(aircrafts, start, end);
    }

    mld = recursive_fmd(aircrafts, start, middle);
    mrd = recursive_fmd(aircrafts, middle + 1, end);

    md = mld < mrd? mld : mrd;

    partition = malloc((end-start+1)*sizeof(Aircraft));
    j = 0;
    for (llint i = start; i <= end; i++) {
        if (fabs(square(aircrafts[i].pos_x - middle_x_pos)) < md) {
            partition[j++] = aircrafts[i];
        }
    }

    pmd = find_partition_minimum_distance(partition, middle_x_pos, j, md);
    free(partition);
    return md < pmd? md : pmd;
}


llint find_minimum_distance(Aircraft *aircrafts, llint size) {
    return recursive_fmd(aircrafts, 0, size - 1);
}

void solve_for(Aircraft *aircrafts, llint n_aircrafts) {
    merge_sort(aircrafts, sizeof(Aircraft), n_aircrafts, compare_aircraft_x_positions);
    find_minimum_distance(aircrafts, n_aircrafts);
}


/******************************************************************************
 *                                    MAIN                                    *
 ******************************************************************************/

int main() {
    llint n_aircrafts, x, y, j, empty;
    Aircraft *aircrafts;

    scanf("%lld", &n_aircrafts);
    
    aircrafts = malloc(n_aircrafts * sizeof(Aircraft));

    for (llint i = 0; i < n_aircrafts; i++) {
        scanf("%lld %lld", &x, &y);
        aircrafts[i].id = i;
        aircrafts[i].pos_x = x;
        aircrafts[i].pos_y = y;
    }

    create_stack(n_aircrafts);

    solve_for(aircrafts, n_aircrafts);
    
    clean_stack_duplicates();
    print_stack();
    delete_stack();

    free(aircrafts);

    return 0;
}