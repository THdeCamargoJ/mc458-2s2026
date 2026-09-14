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

void solve_for(Aircraft aircrafts[], llint n_aircrafts, llint *solution) {

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