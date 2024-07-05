"""Solution to the Queen problem using Python."""

import argparse
from enum import Enum
from typing import List


class OccupancyStatus(Enum):
    """Used to represent the occupancy status of a column or diagonal."""

    FREE = 0
    OCCUPIED = 1


class QueenProblemSolver:
    """Solves the Queen problem for N Queens on NxN chessboard."""

    def __init__(self, n: int):
        self.n: int = n
        self._placed_queen_id: List[int] = [0 for _ in range(self.n)]
        self.solution_counter: int = 0
        self._init_occupancy()

        self._place_nth_queen(0)

    def _init_occupancy(self) -> None:
        self._is_occupied_column: List[OccupancyStatus] = [
            OccupancyStatus.FREE
        ] * self.n
        number_of_diagonals: int = self._get_number_of_diagonals()
        self._is_occupied_diagonal_right: List[OccupancyStatus] = [
            OccupancyStatus.FREE
        ] * number_of_diagonals
        self._is_occupied_diagonal_left: List[OccupancyStatus] = [
            OccupancyStatus.FREE
        ] * number_of_diagonals

    def _place_nth_queen(self, row: int) -> None:
        for column in range(self.n):
            if not self._is_occupied(row, column):
                self._placed_queen_id[row] = column
                self._update_occupancy(row, column, OccupancyStatus.OCCUPIED)

                if (row + 1) < self.n:
                    self._place_nth_queen(row + 1)
                else:
                    self._print_solution()

                self._update_occupancy(row, column, OccupancyStatus.FREE)

    def _is_occupied(self, row, column) -> bool:
        return OccupancyStatus.OCCUPIED in (
            self._is_occupied_column[column],
            self._is_occupied_diagonal_right[self._get_right_diagonal(row, column)],
            self._is_occupied_diagonal_left[self._get_left_diagonal(row, column)],
        )

    def _update_occupancy(
        self, row: int, column: int, is_occupied: OccupancyStatus
    ) -> None:
        self._is_occupied_column[column] = is_occupied
        self._is_occupied_diagonal_right[self._get_right_diagonal(row, column)] = (
            is_occupied
        )
        self._is_occupied_diagonal_left[self._get_left_diagonal(row, column)] = (
            is_occupied
        )

    def _get_right_diagonal(self, row: int, column: int) -> int:
        return row + column

    def _get_left_diagonal(self, row: int, column: int) -> int:
        return (row - column) + self._get_left_diagonal_offset()

    def _get_left_diagonal_offset(self) -> int:
        return self.n - 1

    def _get_number_of_diagonals(self) -> int:
        return self.n * 2 - 1

    def _print_solution(self) -> None:
        print(f'{self.solution_counter}: {" ".join(map(str, self._placed_queen_id))}')
        self.solution_counter += 1


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-n', type=int, required=True, help='number of queens', dest='N'
    )
    args = parser.parse_args()
    QueenProblemSolver(args.N)
