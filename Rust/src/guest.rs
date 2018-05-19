/// Struct for guest data.
pub struct Guest {
    id: i32,
    name: String,
    surname: String,
    friends: Vec<i32>,
}

/// Methods of Guest.
impl Guest {

    /// Create a new guest containing the prodided data.
    pub fn new(id: i32, name: String, surname: String, friends: Vec<i32>) -> Guest {
        return Guest {
            id: id,
            name: name,
            surname: surname,
            friends: friends,
        };
    }

    /// Remove a friend from the friends list.
    pub fn remove_friend(&mut self, id: i32) {
        if self.friends.contains(&id) {
            let pos = self.friends.iter().position(|x| *x == id).unwrap();
            self.friends.remove(pos);
        }
    }

    /// String representation of the guest.
    pub fn info(&self) -> String {
        let result = self.id.to_string() + ": " + &self.name + " " + &self.surname + ", "
            + &vec_to_string(self.friends.clone());
        return result;
    }

    //
    // Getter
    //

    pub fn get_id(&self) -> i32 {
        return self.id;
    }

    pub fn get_number_of_friends(&self) -> i32 {
        return self.friends.len() as i32;
    }
}

/// String representation of a vector of i32s.
fn vec_to_string(list: Vec<i32>) -> String {
    let mut result: String = "[".to_string();
    for i in 0..list.len() {
        result = result + &list[i].to_string() + ", ";
    }
    let len = result.len();
    result.truncate(len - 2);
    result = result + "]";
    return result;
}