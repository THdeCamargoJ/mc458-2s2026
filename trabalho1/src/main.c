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
#define MAX_DOUBLE 100000000000LL
#define llint long long int


typedef struct {
    llint id;
    llint pos_x;
    llint pos_y;
} Aircraft;

typedef struct Pair {
    llint aircraft_a, aircraft_b;
    double distance;
    struct Pair *next;
    struct Pair *prev;
} Pair;

typedef struct {
    Pair *head, *tail;
    llint size;
} Queue;


/******************************************************************************
 *                             EUCLIDEAN DISTANCE                             *
 ******************************************************************************/

double distance_between_aircrafts(const Aircraft a, const Aircraft b) {
    return sqrt(
        (double) ((a.pos_x - b.pos_x)*(a.pos_x - b.pos_x) 
        + (a.pos_y - b.pos_y)*(a.pos_y - b.pos_y))
    );
}


/******************************************************************************
 *                                    QUEUE                                   *
 ******************************************************************************/

Queue *solution;

void init_pair(const Aircraft a, const Aircraft b, Pair *pair) {
    pair->aircraft_a = a.id;
    pair->aircraft_b = b.id;

    // Mantain i < j rule
    if (a.id > b.id) {
        pair->aircraft_a = b.id;
        pair->aircraft_b = a.id;
    }

    pair->distance = distance_between_aircrafts(a, b);
    pair->next = NULL;
    pair->prev = NULL;

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

Queue *create_queue() {
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    return queue;
}

void delete_queue(Queue *queue) {
    Pair *pair, *aux;

    if (queue->size) {
        pair = queue->head;
        while(pair != NULL) {
            aux = pair->next;
            free(pair);
            pair = aux;
        }
    }

    free(queue);
}

void enqueue_pair(Queue *queue, Pair *new_pair) {
    Pair *pair, *p = queue->head;
    
    // Evitar duplicatas
    while (p != NULL) {
        if ((p->aircraft_a == new_pair->aircraft_a && p->aircraft_b == new_pair->aircraft_b)
            || (p->aircraft_a == new_pair->aircraft_b && p->aircraft_b == new_pair->aircraft_a)) return;
        p = p->next;
    };

    pair = malloc(sizeof(Pair));
    *pair = *new_pair;

    if (queue->size == 0) {
        queue->head = pair;
        queue->tail = pair;
        queue->size = 1;
        return;
    }

    queue->tail->next = pair;
    pair->prev = queue->tail;
    queue->tail = pair;
    queue->size++;
}

int dequeue(Queue *queue, Pair *pair) {
    Pair *aux;

    if (queue->size == 0) {
        return 1;
    }

    *pair = *queue->tail;

    pair->next = NULL;
    pair->prev = NULL;

    if (queue->size == 1) {
        free(queue->tail);
        queue->head = NULL;
        queue->tail = NULL;
        queue->size = 0;
        return 0;
    }

    aux = queue->tail->prev;
    aux->next = NULL;
    free(queue->tail);
    queue->tail = aux;
    queue->size--;
    return 0;
}

llint get_queue_size(Queue *queue) {
    if (queue == NULL) return -1;
    return queue->size;
}

void clear_queue(Queue *queue) {
    Pair *pair, *aux;

    if (queue->size) {
        pair = queue->head;
        while(pair != NULL) {
            aux = pair->next;
            free(pair);
            pair = aux;
        }
        queue->head = NULL;
        queue->tail = NULL;
        queue->size = 0;
    }
}

void print_queue(Queue *queue) {
    Pair *pair = queue->tail;
    while (pair!=NULL) {
        print_pair(pair);
        pair = pair->prev;
    }
}

/******************************************************************************
 *                                  MERGESORT                                 *
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
    llint air_a_comparison = b->aircraft_a - a->aircraft_b,
          air_b_comparison = b->aircraft_b - a->aircraft_b;

    // Compare y coordinates
    if (air_a_comparison < 0) return -1; // b comes first
    if (air_a_comparison > 0) return 1;  // a comes first

    if (air_b_comparison < 0) return -1; // b comes first
    if (air_b_comparison > 0) return 1;  // a comes first

    // Same position
    return 0; 
}

void combine_merge_sort(
    void *v,
    size_t v_item_size,
    llint start, llint middle, llint end,
    int (* compare)(const void *, const void *)
) {
    char *vect = (char *)v;
    char *left_vector, *right_vector, *left_item, *right_item;
    llint lv_i = 0, rv_i = 0, lv_size, rv_size, i;
    int comparison;

    left_vector = malloc((end-start+1)*v_item_size);
    right_vector = malloc((end-start+1)*v_item_size);

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

    free(left_vector);
    free(right_vector);
}

void recursive_merge_sort(
    void *vect,
    size_t v_item_size,
    llint start, llint end,
    int (* compare)(const void *, const void *)
) {
    llint middle = start + (end - start) / 2;
    
    if (start >= end) return; // base
    
    // Divide
    recursive_merge_sort(vect, v_item_size, start, middle, compare);
    recursive_merge_sort(vect, v_item_size, middle + 1, end, compare);

    // Conquer
    combine_merge_sort(vect, v_item_size, start, middle, end, compare);

}

void merge_sort(
    void *vect,
    size_t v_item_size,
    llint size,
    int (* compare_positions)(const void *, const void *)
) {
    recursive_merge_sort(vect, v_item_size,  0, size - 1, compare_positions);
}


/******************************************************************************
 *                                  SOLUTION                                  *
 ******************************************************************************/

void check_queue_min(Pair *pair) {
    Pair queue_pair;
    double pair_dist = pair->distance;

    if (get_queue_size(solution) == 0) {
        enqueue_pair(solution, pair);
        return;
    }

    dequeue(solution, &queue_pair);
    if (pair_dist > queue_pair.distance) {
        enqueue_pair(solution, &queue_pair);
        return;
    }

    if (pair_dist < queue_pair.distance) {
        clear_queue(solution);
        enqueue_pair(solution, pair);
        return;
    }

    enqueue_pair(solution, &queue_pair);
    enqueue_pair(solution, pair);
}

double find_partition_minimum_distance(Aircraft *partition, llint p_size, double prev_min_d) {
    Pair pair;
    double min_dist = prev_min_d, distance;

    merge_sort(partition, sizeof(Aircraft), p_size, compare_aircraft_y_positions);

    for (llint i = 0; i < p_size; i++)
        for (llint j = i + 1; j < p_size
                              && (partition[j].pos_y - partition[i].pos_y) < min_dist; j++) {
            init_pair(partition[i], partition[j], &pair);
            distance = distance_between_aircrafts(partition[i], partition[j]);
            if (distance < min_dist) {
                min_dist = distance;
            }
            check_queue_min(&pair);
        }

    return min_dist;
 }

double base_case_fmd(Aircraft *aircrafts, llint start, llint end) {
    double min_dist = MAX_DOUBLE;
    Pair pair, queue_pair, min_pair;

    if (end - start + 1 == 1) return min_dist;

    for (llint i = start; i < end; i++) {
        for (llint j = i + 1; j <= end; j++) {
            init_pair(aircrafts[i], aircrafts[j], &pair);
            if (min_dist > pair.distance) {
                min_dist = pair.distance;
                min_pair = pair;
            }

            check_queue_min(&min_pair);
        }
    }

    return min_dist;
}


double recursive_fmd(Aircraft *aircrafts, llint start, llint end) {
    llint middle = start + (end - start) / 2, j, middle_x_pos = aircrafts[middle].pos_x;
    double mld, mrd, md, pmd;
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
        if (fabs(aircrafts[i].pos_x - middle_x_pos) < md) {
            partition[j++] = aircrafts[i];
        }
    }

    pmd = find_partition_minimum_distance(partition, j, md);
    free(partition);
    return md < pmd? md : pmd;
}


double find_minimum_distance(Aircraft *aircrafts, llint size) {
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

    solution = create_queue();

    solve_for(aircrafts, n_aircrafts);

    print_queue(solution);
    delete_queue(solution);

    free(aircrafts);

    return 0;
}