fn main() {
    let a = "hell world!";
    let b = String::from("hello world!");
    let l = longest(a, b.as_str());
    println!("{l}");

    let w = first_word("hell world!");
    println!("{w}");

    let b = first_word_bytes("hell world!");
    println!("{b:?}")
}

fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
    if x.len() > y.len() {
        x
    } else {
        y
    }
}

fn first_word(s: &str) -> &str {
    let bytes = s.as_bytes();
    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[0..i];
        }
    }
    &s[..]
}

fn first_word_bytes(s: &str) -> &[u8] {
    let bytes = s.as_bytes();
    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &bytes[0..i];
        }
    }
    &bytes[..]
}
