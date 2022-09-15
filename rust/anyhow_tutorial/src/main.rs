use std::fs::read_to_string;

use anyhow::{anyhow, Context, Result};

fn func(x: i32) -> Result<i32> {
    if x == 0 {
        return Err(anyhow!("Zero"));
    } else {
        return Ok(x);
    }
}

fn main() -> Result<()> {
    let res1 = func(1);
    println!("Result of func(1): {:?}", res1);
    let res2 = func(0);
    println!("Result of func(0): {:?}", res2);
    let content = read_to_string("/tmp/testfile").context("Failed to read test file")?;
    println!("{}", content);
    Ok(())
}
