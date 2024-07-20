#include <vector>
#include <algorithm>
#include <ranges>
#include <iostream>

class QueenProblemSolver
{
public:
    QueenProblemSolver(int N_) 
        : N{N_}
        , number_of_diagonals{N * 2 - 1}
        , left_diagonal_offset{N - 1}
    {
        if (N_ <= 0) return;
        placed_queen_id.resize(N, -1);
        init_occupancy();

        // place_Nth_queen(0);
        solve();
    }

private:
    enum class OccupancyStatus : bool
    {
        FREE,
        OCCUPIED,
    };

    enum class SolverState
    {
        // BEGIN,
        // NEXT_COLUMN,
        PLACE_QUEEN,
        PREVIOUS_COLUMN,
        // FOUND_SOLUTION,
        // END,
    };

private:
    void init_occupancy()
    {
        is_occupied_row.resize(N, OccupancyStatus::FREE);
        is_occupied_column.resize(N, OccupancyStatus::FREE);
        is_occupied_right_diagonal.resize(number_of_diagonals, OccupancyStatus::FREE);
        is_occupied_left_diagonal.resize(number_of_diagonals,OccupancyStatus::FREE);
    }

    void solve()
    {
        // auto state = SolverState::BEGIN;
        // auto state = SolverState::NEXT_COLUMN;
        auto state = SolverState::PLACE_QUEEN;
        int current_column{0};
        int current_row{0};

        do
        {
            switch(state)
            {
            // case SolverState::BEGIN:
            //     current_column = -1;
            //     current_row = -1;
            //     state = SolverState::NEXT_COLUMN;
            // break;
            // case SolverState::NEXT_COLUMN:
            //     ++current_column;
            //     current_row = 0;
            //     if (current_column < N)
            //     {
            //         state = SolverState::PLACE_QUEEN;
            //     }
            //     else
            //     {
            //         // state = SolverState::FOUND_SOLUTION;
            //         print_solution();
            //         state = SolverState::PREVIOUS_COLUMN;
            //     }
            // break;
            case SolverState::PLACE_QUEEN:
                if (!is_occupied(current_row, current_column))
                {
                    place_queen(current_row, current_column);
                    // state = SolverState::NEXT_COLUMN;
                    ++current_column;
                    current_row = 0;
                    if (current_column == N)
                    {
                        print_solution();
                        state = SolverState::PREVIOUS_COLUMN;
                    }
                }
                else
                {
                    ++current_row;
                    if (current_row == N)
                    {
                    //     state = SolverState::PLACE_QUEEN;
                    // }
                    // else
                    // {
                        state = SolverState::PREVIOUS_COLUMN;
                    }
                }
            break;
            case SolverState::PREVIOUS_COLUMN:
                --current_column;
                if (current_column >= 0)
                {
                    // state = SolverState::END;
                // }
                // else
                // {
                    current_row = remove_queen(current_column);
                    ++current_row;
                    if (current_row < N)
                    {
                        state = SolverState::PLACE_QUEEN;
                    }
                    else
                    {
                        state = SolverState::PREVIOUS_COLUMN;
                    }
                }
            break;
            // case SolverState::FOUND_SOLUTION:
            //     print_solution();
            //     state = SolverState::PREVIOUS_COLUMN;
            // break;
            // case SolverState::END:
            // break;
            }
        }
        while(current_column >= 0);
    }

    void place_queen(int row, int column)
    {
        placed_queen_id[column] = row;
        update_occupancy(row, column, OccupancyStatus::OCCUPIED);
    }

    int remove_queen(int column)
    {
        auto current_row = placed_queen_id[column];
        // placed_queen_id[column] = -1;
        update_occupancy(current_row, column, OccupancyStatus::FREE);
        return current_row;
    }
    // void place_Nth_queen(int row)
    // {
    //     // We attempt to place a Queen in an available column on the given row.
    //     // Then we call this function recursively to attempt to place the Queen
    //     // in the next row. We attempt this iteratively over all the columns.
    //     for (auto column = 0; column < N; ++column)
    //     {
    //         // When a Queen is placed, the column where it was placed is marked as
    //         // occupied because we cannot place another Queen in the same column.
    //         // Likewise, the two diagonals on which the Queen is placed are also marked
    //         // as occupied.
    //         //
    //         // If the position where we now attempt to place the Queen is not occupied
    //         // due to any previous Queen, then we place the Queen there.
    //         if (!is_occupied(row, column))
    //         {
    //             placed_queen_id[row] = column;
    //             update_occupancy(row, column, OccupancyStatus::OCCUPIED);

    //             if ((row + 1) < N)
    //             {
    //                 place_Nth_queen(row + 1);
    //             }
    //             else
    //             {
    //                 // We have placed N queens, so we have found a solution.
    //                 print_solution();
    //             }

    //             // We are done with our attempt to place a Queen in this position. We
    //             // have either found a solution here or failed to place a Queen in one
    //             // of the lower rows. In either case, we remove the Queen from this
    //             // position to continue the search for the next solution. Hence, we
    //             // mark the column and the two diagonals as free again.
    //             update_occupancy(row, column, OccupancyStatus::FREE);
    //         }
    //     }
    // }

    bool is_occupied(int row, int column) const
    {
        return is_occupied_row[row] == OccupancyStatus::OCCUPIED
            || is_occupied_column[column] == OccupancyStatus::OCCUPIED
            || is_occupied_right_diagonal[get_right_diagonal(row, column)] 
                == OccupancyStatus::OCCUPIED
            || is_occupied_left_diagonal[get_left_diagonal(row, column)] 
                == OccupancyStatus::OCCUPIED;
    }

    void update_occupancy(int row, int column, OccupancyStatus is_occupied)
    {
        is_occupied_row[row] = is_occupied;
        is_occupied_column[column] = is_occupied;
        is_occupied_right_diagonal[get_right_diagonal(row, column)] = is_occupied;
        is_occupied_left_diagonal[get_left_diagonal(row, column)] = is_occupied;
    }


    // There are two types of diagonals:
    // 1. Right diagonals: diagonals that go upwards to the right.
    // 2. Left diagonals: diagonals that go upwards to the left.
    //
    // We need to identify each diagonal uniquely to track the occupancy due to the
    // placement of a Queen. For this purpose, we use the following invariants:
    // 1. Right diagonals: Going to the right increases the column number, while going
    // upwards decreases the row number. Hence, the sum of row number and column number
    // is same for all the squares on a given right diagonal.
    // 2. Left diagonals: Going to the left decreases the column number, and going
    // upwards decreases the row number. Hence, the difference between the row number
    // and the column number is same for all the squares on a given left diagonal.
    //
    // The left diagonal index could be negative, but container index is non-negative.
    // Hence, we offset the left diagonal number to be non-negative. The offset is
    // computed based on the chessboard size as the number of diagonals also varies
    // based on it.
    inline int get_right_diagonal(int row, int column) const
    {
        return row + column;
    }

    inline int get_left_diagonal(int row, int column) const
    {
        return (row - column) + left_diagonal_offset;
    }

    inline int get_left_diagonal_offset() const
    {
        return N - 1;
    }

    inline int get_number_of_diagonals() const
    {
        return N * 2 - 1;
    }

    void print_solution() const
    {
        std::cout << solution_counter++ << ": ";
        std::ranges::for_each(
            placed_queen_id,
            [](const int& column) { std::cout << column << " ";});
        std::cout << "\n";
    }

private:
    // Denotes the number of Queens and the dimensions of the chessboard.
    // While this violates the naming convention, we make an exception because 'N' is
    // the commonly used notation for the N-Queen problem and is easier to understand.
    const int N;

    const int number_of_diagonals;
    const int left_diagonal_offset;

    // Notes the identities of the Queen placed in each row. By convention and to
    // simplify the notation, each Queen can only be placed in a specific column.
    // The column number also denotes the identity of the Queen.
    // 
    // For example, consider 4 Queens placed on a 4x4 chessboard as below. (N == 4)
    //
    // +---+---+---+---+    +---+
    // |   | Q |   |   |    | 1 |
    // +---+---+---+---+    +---+
    // |   |   |   | Q |    | 3 |
    // +---+---+---+---+    +---+
    // | Q |   |   |   |    | 0 |
    // +---+---+---+---+    +---+
    // |   |   | Q |   |    | 2 |
    // +---+---+---+---+    +---+
    std::vector<int> placed_queen_id;

    // The following containers keep track of whether a particular column, left
    // diagonal, or right diagonal is occupied by a Queen, while the solutions are
    // being computed.
    std::vector<OccupancyStatus> is_occupied_column;
    std::vector<OccupancyStatus> is_occupied_row;
    std::vector<OccupancyStatus> is_occupied_left_diagonal;
    std::vector<OccupancyStatus> is_occupied_right_diagonal;

    // Keeps a count of the number of solutions found.
    mutable int solution_counter{0};
};


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <number_of_queens>" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    int N = std::stoi(argv[1]);
    QueenProblemSolver solve(N);
    std::exit(EXIT_SUCCESS);
}
