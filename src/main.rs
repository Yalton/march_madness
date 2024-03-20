use rand::seq::{IteratorRandom};
use rand::thread_rng;
use std::collections::HashSet;
use std::fs::File;
use std::io::{BufWriter, Write};
use std::sync::{Arc, Mutex};
use std::time::Instant;
use threadpool::ThreadPool;

fn is_valid_bracket(bracket: &str) -> bool {
    if bracket.len() != 64 {
        return false;
    }

    let mut unique_chars = HashSet::new();

    // Check bracket1 (first 32 games)
    for c in bracket[0..32].chars() {
        if !unique_chars.insert(c) {
            return false;
        }
    }

    // Check bracket2 (next 16 games)
    for c in bracket[32..48].chars() {
        if !unique_chars.contains(&c) {
            return false;
        }
    }

    // Check bracket3 (next 8 games)
    for c in bracket[48..56].chars() {
        if !unique_chars.contains(&c) {
            return false;
        }
    }

    // Check bracket4 (next 4 games)
    for c in bracket[56..60].chars() {
        if !unique_chars.contains(&c) {
            return false;
        }
    }

    // Check bracket5 (next 2 games)
    for c in bracket[60..62].chars() {
        if !unique_chars.contains(&c) {
            return false;
        }
    }

    // Check winner
    unique_chars.contains(&bracket[63..64].chars().next().unwrap())
}

fn bracket_generator(pre_bracket: &[char], size: usize) -> Option<String> {
    let mut rng = thread_rng();
    let mut bracket = String::with_capacity(size);
    let mut available_chars: Vec<char> = pre_bracket.to_vec();

    for _ in 0..size {
        if let Some(index) = (0..available_chars.len()).choose(&mut rng) {
            let char = available_chars.remove(index);
            bracket.push(char);
        } else {
            return None;
        }
    }

    Some(bracket)
}

fn generate_full_bracket(
    existing_brackets: Arc<Mutex<HashSet<String>>>,
    pre_bracket: Vec<char>,
) -> Option<String> {
    if let Some(bracket1) = bracket_generator(&pre_bracket, 32) {
        if let Some(bracket2) = bracket_generator(&bracket1.chars().collect::<Vec<char>>(), 16) {
            if let Some(bracket3) = bracket_generator(&bracket2.chars().collect::<Vec<char>>(), 8) {
                if let Some(bracket4) =
                    bracket_generator(&bracket3.chars().collect::<Vec<char>>(), 4)
                {
                    if let Some(bracket5) =
                        bracket_generator(&bracket4.chars().collect::<Vec<char>>(), 2)
                    {
                        if let Some(winner) =
                            bracket_generator(&bracket5.chars().collect::<Vec<char>>(), 1)
                        {
                            let final_bracket = format!(
                                "{}{}{}{}{}{}",
                                bracket1, bracket2, bracket3, bracket4, bracket5, winner
                            );
                            let mut existing = existing_brackets.lock().unwrap();
                            if existing.insert(final_bracket.clone()) {
                                return Some(final_bracket);
                            }
                        }
                    }
                }
            }
        }
    }

    None
}
fn main() {
    let start = Instant::now();
    let existing_brackets = Arc::new(Mutex::new(HashSet::new()));
    let num_threads = num_cpus::get();
    let pool = ThreadPool::new(num_threads);

    let initial_bracket: Vec<char> =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
            .chars()
            .collect();

    let (tx, rx) = std::sync::mpsc::channel();

    for _ in 0..10000000 {
        let existing_brackets = Arc::clone(&existing_brackets);
        let pre_bracket = initial_bracket.clone();
        let tx = tx.clone();
        pool.execute(move || loop {
            if let Some(bracket) =
                generate_full_bracket(existing_brackets.clone(), pre_bracket.clone())
            {
                let invalid = is_valid_bracket(&bracket);
                if invalid {
                    println!("Invalid Bracket detected ");
                }
                tx.send(bracket).unwrap();
                break;
            }
        });
    }

    drop(tx);

    let mut file = BufWriter::new(File::create("brackets.txt").unwrap());
    for bracket in rx {
        writeln!(file, "{}", bracket).unwrap();
    }

    let duration = start.elapsed();
    println!("Time taken by program: {:?} ", duration);
}