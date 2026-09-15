/* Trabalho 1 - Caos aéreo em Bacalhau
 * 
 * T.H. de Camargo J.
 */

#include <math.h>
#include <stdio.h>


#define MAX_AIRCRAFTS 10000000
#define llint long long int


typedef struct {
    llint id;
    llint pos_x;
    llint pos_y;
} Aircraft;


double distance_between(Aircraft a, Aircraft b) {
    return sqrt(
        (a.pos_x - b.pos_x)*(a.pos_x - b.pos_x) 
        + (a.pos_y - b.pos_y)*(a.pos_y - b.pos_y)
    );
}

int compare_aircraft_positions(const Aircraft a, const Aircraft b) {
    llint x_comparison = b.pos_x - a.pos_x,
          y_comparison = b.pos_y - a.pos_y;
    
    // Compare x coordinates
    if (x_comparison < 0) return -1; // b comes first
    if (x_comparison > 0) return 1;  // a comes first

    // Compare y coordinates
    if (y_comparison < 0) return -1; // b comes first
    if (y_comparison > 0) return 1;  // a comes first

    // Same position
    return 0; 
}

void combine_merge_sort(Aircraft *aircrafts, llint start, llint middle, llint end) {
    Aircraft left_vector[MAX_AIRCRAFTS], right_vector[MAX_AIRCRAFTS];
    llint lv_i = start, rv_i = middle + 1, i;
    int comparison;

    for (i = start; i <= end; i++) {
        if (i <= middle) {
            left_vector[lv_i++] = aircrafts[i];
        } else {
            right_vector[rv_i++] = aircrafts[i];
        }
    }

    lv_i = start;
    rv_i = middle + 1;
    i = start;
    while (lv_i <= middle && rv_i <= end) {
        comparison = compare_aircraft_positions(left_vector[lv_i], right_vector[rv_i]);
        if (comparison >= 0) {
            aircrafts[i] = left_vector[lv_i++];
        } else {
            aircrafts[i] = right_vector[rv_i++];
        }
        i++;
    }

    while (lv_i <= middle) {
        aircrafts[i++] = left_vector[lv_i++];
    }

    while (rv_i <= end) {
        aircrafts[i++] = right_vector[rv_i++];
    }
}

void recursive_merge_sort(Aircraft *aircrafts, llint start, llint end) {
    llint middle = (end - start) / 2;
    
    if (start == end) return; // base
    
    // Divide
    recursive_merge_sort(aircrafts, start, middle);
    recursive_merge_sort(aircrafts, middle + 1, end);

    // Conquer
    combine_merge_sort(aircrafts, start, middle, end);

}

void merge_sort(Aircraft *aircrafts, llint size) {
    recursive_merge_sort(aircrafts, 0, size - 1);
}

void solve_for(Aircraft *aircrafts, llint n_aircrafts, llint *solution) {
    /**
     * P é a quantidade de pontos 
     */
    merge_sort(aircrafts, n_aircrafts);
 }


int main() {
    llint n_aircrafts, x, y;
    Aircraft aircrafts[MAX_AIRCRAFTS],
             solution[MAX_AIRCRAFTS][2],
             aircraft_i, aircraft_j;

    scanf("%ld", &n_aircrafts);

    for (llint i = 0; i < n_aircrafts; i++) {
        scanf("%ld %ld", &x, &y);
        aircrafts[0].id = i;
        aircrafts[0].pos_x = x;
        aircrafts[0].pos_y = y;
    }

    solve_for(aircrafts, n_aircrafts, solution);

    for (llint i = 0; i < n_aircrafts; i++) {
            aircraft_i = solution[i][0];
            aircraft_j = solution[i][1];
        if (solution[i][0].id > solution[i][1].id) {
            aircraft_i = solution[i][1];
            aircraft_j = solution[i][0];
        }
        printf("(%ld,%ld)", aircraft_i.id, aircraft_j.id);
    }

    return 0;
}