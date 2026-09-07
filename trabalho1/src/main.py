# Trabalho 1 - Caos aéreo em Bacalhau
#
# T.H. de Camargo J.


class Aircraft:
    def __init__(self, id: int, x_pos: int, y_pos: int):
        self.id = id
        self.x_pos = x_pos
        self.y_pos = y_pos

    def distance_from(self, other: Aircraft) -> float:
        return ((self.x_pos - other.x_pos) ** 2 + (self.y_pos - other.y_pos) ** 2) ** 0.5



def solve_for(aircrafts: list[Aircraft]) -> list[(Aircraft, Aircraft)]:
    # Placeholder implementation
    return [(Aircraft(1,2,3), Aircraft(4,5,6))]


if __name__ == "__main__":

    # Read input
    n_aircrafts = int(input())
    aircrafts = []
    for i in range(n_aircrafts):
        x, y = map(int, input().split())
        aircrafts.append(Aircraft(i, x, y))

    # Solve for pairs of aircrafts and print the results
    for tuple in solve_for(aircrafts):
        aircraft_i, aircraft_j = tuple

        print(f"({aircraft_i.id},{aircraft_j.id}")


