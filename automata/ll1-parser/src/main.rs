use std::{
    fs::{read_to_string, File},
    io::{LineWriter, Write},
};

use clap::Parser;
use ll1_parser::{
    bnf::{parse_bnf, Symbol},
    parser::{create_parse_table, eliminate_left_recursion, parse, ParseTreeNode},
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
                        Symbol::Endmarker => {} // Endmarker is ignored
                    }
                }
            }
            file.write_all(b";\n").ok();
        }
        file.flush().ok();
    }
    let input = read_to_string(args.input_file).expect("Could not read input file");
    let parse_table = create_parse_table(&eliminated).expect("Could not create parse table");
    let start_symbol_name = eliminated[0].name.to_owned();
    let parse_tree = parse(&input, &parse_table, start_symbol_name).expect("Parse failed");
    let mut stack = vec![(&parse_tree, 0)];
    while let Some((node, indent_step)) = stack.pop() {
        for _ in 0..indent_step {
            print!("|   ");
        }
        match node {
            ParseTreeNode::Terminal(s) => {
                println!("Terminal[{s}]");
            }
            ParseTreeNode::NonTerminal { name, children } => {
                println!("NonTerminal[{name}]");
                let new_indet_step = indent_step + 1;
                for child in children.iter().rev() {
                    stack.push((child, new_indet_step));
                }
            }
        }
    }
}
