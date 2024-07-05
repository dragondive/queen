use std::env;
use std::sync::atomic::{AtomicU32, Ordering};

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        panic!("Usage: {} <number_of_queens>", args[0])
    }

    let n: i32 = args[1].parse().expect("number_of_queens must be a number");
    solve_queen(n);
}

fn solve_queen(n: i32) {
    if n <= 0 { return }
    let mut occupancy: OccupancyState = OccupancyState::new(n);
    let mut placed_queen_id: Vec<i32> = vec![0; n as usize];

    place_nth_queen(0, n, &mut occupancy, &mut placed_queen_id);
}

struct OccupancyState {
    n: i32,
    is_occupied_column: Vec<bool>,
    is_occupied_right_diagonal: Vec<bool>,
    is_occupied_left_diagonal: Vec<bool>,
}

impl OccupancyState {
    pub fn new(n: i32) -> Self {
        Self {
            n,
            is_occupied_column: vec![false; n as usize],
            is_occupied_right_diagonal: vec![false; Self::get_number_of_diagonals(n) as usize],
            is_occupied_left_diagonal: vec![false; Self::get_number_of_diagonals(n) as usize],
        }
    }

    pub fn update_occupancy(&mut self, row: i32, column: i32, is_occupied: bool) {
        let right_diagonal: i32 = self.get_right_diagonal(row, column);
        let left_diagonal: i32 = self.get_left_diagonal(row, column);

        self.is_occupied_column[column as usize] = is_occupied;
        self.is_occupied_right_diagonal[right_diagonal as usize] = is_occupied;
        self.is_occupied_left_diagonal[left_diagonal as usize] = is_occupied;
    }

    pub fn is_occupied(&self, row: i32, column: i32) -> bool {
        self.is_occupied_column[column as usize]
            || self.is_occupied_right_diagonal[self.get_right_diagonal(row, column) as usize]
            || self.is_occupied_left_diagonal[self.get_left_diagonal(row, column) as usize]
    }

    fn get_number_of_diagonals(n: i32) -> i32 {
        n * 2 - 1
    }

    fn get_right_diagonal(&self, row: i32, column: i32) -> i32 {
        row + column
    }

    fn get_left_diagonal(&self, row: i32, column: i32) -> i32 {
        row - column + self.get_left_diagonal_offset()
    }

    fn get_left_diagonal_offset(&self) -> i32 {
        self.n - 1
    }
}

fn place_nth_queen(
    row: i32,
    n: i32,
    occupancy: &mut OccupancyState,
    placed_queen_id: &mut Vec<i32>,
) {
    for column in 0..n {
        if !occupancy.is_occupied(row, column) {
            placed_queen_id[row as usize] = column;
            occupancy.update_occupancy(row, column, true);

            if row + 1 < n {
                place_nth_queen(row + 1, n, occupancy, placed_queen_id);
            } else {
                print_solution(placed_queen_id);
            }

            occupancy.update_occupancy(row, column, false);
        }
    }
}

static SOLUTION_COUNTER: AtomicU32 = AtomicU32::new(0);

fn print_solution(placed_queen_id: &Vec<i32>) {
    let count = SOLUTION_COUNTER.fetch_add(1, Ordering::SeqCst);
    print!("{}: ", count);
    for column in placed_queen_id.iter() {
        print!("{} ", column);
    }
    println!();
}
