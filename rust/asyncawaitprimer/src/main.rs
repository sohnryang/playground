use futures::executor::block_on;

async fn hell_world() {
    println!("Hell world!");
}

fn main() {
    let future = hell_world();
    block_on(future);
}
