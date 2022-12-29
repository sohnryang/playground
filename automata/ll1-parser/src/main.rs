use std::{
    fs::{read_to_string, File},
    io::{LineWriter, Write},
};

use clap::Parser;
use ll1_parser::{
    bnf::{parse_bnf, Symbol},
    parser::eliminate_left_recursion,
};

#[derive(Parser, Debug)]
#[command(version = "0.1.0")]
#[command(author = "curling_grad")]
#[command(about = "A simple LL(1) parser written in Rust")]
#[command(long_about = None)]
struct Args {
    /// Path to input file
    input_file: String,

    /// Path to grammar input file, written in BNF
    #[arg(short = 'i')]
    grammar_input: String,

    /// Path to grammar output
    #[arg(short = 'o')]
    grammar_output: Option<String>,
}

fn main() {
    let args = Args::parse();
    let bnf = read_to_string(args.grammar_input).expect("Could not read grammar file");
    let parsed_grammar = parse_bnf(bnf.as_str()).expect("Could not parse BNF");
    let eliminated = eliminate_left_recursion(&parsed_grammar);
    println!("{eliminated:?}");
    if let Some(output_path) = args.grammar_output {
        let file = File::create(output_path).expect("Could not open output file");
        let mut file = LineWriter::new(file);
        for rule in &eliminated {
            file.write_all(format!("<{}> ::=", rule.name).as_bytes())
                .ok();
            let mut first_expression = true;
            for expression in &rule.expressions {
                if first_expression {
                    first_expression = false;
                } else {
                    file.write_all(b" |").ok();
                }
                for symbol in expression {
                    file.write_all(b" ").ok();
                    match symbol {
                        Symbol::NonTerminal(name) => {
                            file.write_all(format!("<{name}>").as_bytes()).ok();
                        }
                        Symbol::Terminal(s) => {
                            file.write_all(format!("\"{s}\"").as_bytes()).ok();
                        }
                    }
                }
            }
            file.write_all(b";\n").ok();
        }
        file.flush().ok();
    }
}
