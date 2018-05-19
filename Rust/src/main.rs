use guest::Guest;
use std::env;
use std::fs::File;
use std::io::prelude::*;
use std::str;
use std::vec::Vec;

mod guest; // Load module guest.

/// Program control.
fn main() {
    let args: Vec<String> = env::args().collect();
    let ref filepath: String = args[1];
    let ref min_friends_number = args[2].parse::<i32>().unwrap();
    let mut guests = import_file(filepath);
    guests = party(guests, min_friends_number);
    println!("List of guests with at least {} friends:", min_friends_number);
    if guests.len() == 0 {
        println!("There are no guests with at least {} friends.", min_friends_number);
    } else {
        for guest in guests {
            println!("{}", guest.info())
        }
    }
}

/// Import guests from file.
fn import_file(filename: &String) -> Vec<Guest> {
    let mut file_object = File::open(filename).expect("file not found");
    let mut file_content = String::new();
    file_object.read_to_string(&mut file_content).expect("something went wrong reading the file");
    let lines: Vec<&str> = file_content.split("\n").collect();
    let mut guests: Vec<Guest> = Vec::new();
    for line in lines {
        let parts: Vec<&str> = line.split("|").collect();
        let friends: Vec<i32> = parts[3].split(",").map(|s| s.parse().unwrap()).collect();
        let guest = Guest::new(parts[0].parse::<i32>().unwrap(), parts[1].to_string(), parts[2].to_string(), friends);
        guests.push(guest);
    }
    return guests;
}

/// Remove guests with less than k friends from the list.
fn party(mut list: Vec<Guest>, k: &i32) -> Vec<Guest> {
    if list.len() <= *k as usize {
        return Vec::new();
    }
    if *k == 0 {
        return list;
    }
    for i in 0..list.len() {
        if list[i].get_number_of_friends() < *k {
            let id = list[i].get_id();
            list.remove(i);
            for i in 0..list.len() {
                list[i].remove_friend(id);
            }
            list = party(list, k);
            return list;
        }
    }
    return list;
}