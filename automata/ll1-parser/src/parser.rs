use std::collections::{HashMap, HashSet};

use crate::bnf::{Rule, Symbol, EMPTY};

pub fn expand_leftmost_nonterminal(expandee: &Rule, expand_rule: &Rule) -> Rule {
    let mut result = Rule {
        name: expandee.name.clone(),
        expressions: vec![],
    };
    for expression in &expandee.expressions {
        if expression[0] == Symbol::NonTerminal(expand_rule.name.clone()) {
            for expand_rule_expression in &expand_rule.expressions {
                let mut expanded = expand_rule_expression.clone();
                expanded.extend(expression[1..].to_owned());
                result.expressions.push(expanded);
            }
        } else {
            result.expressions.push(expression.clone());
        }
    }
    result
}

pub fn eliminate_left_recursion(rules: &Vec<Rule>) -> Vec<Rule> {
    let mut eliminated: Vec<Rule> = vec![];
    let mut primes: Vec<Rule> = vec![];
    let mut nonterminals: Vec<Rule> = rules.clone();
    for nonterminal_rule in nonterminals.iter_mut() {
        for past_nonterminal_rule in &eliminated {
            *nonterminal_rule =
                expand_leftmost_nonterminal(nonterminal_rule, past_nonterminal_rule);
        }
        let prime_name = nonterminal_rule.name.clone() + "_prime";
        let mut prime = Rule {
            name: prime_name.clone(),
            expressions: vec![],
        };
        if nonterminal_rule
            .expressions
            .iter()
            .filter(|expr| expr[0] == Symbol::NonTerminal(nonterminal_rule.name.clone()))
            .count()
            == 0
        {
            eliminated.push(nonterminal_rule.clone());
            continue;
        }
        let expressions_old = nonterminal_rule.expressions.clone();
        nonterminal_rule.expressions.clear();
        for expression in expressions_old {
            let mut prime_expression: Vec<Symbol> = vec![];
            match &expression[0] {
                Symbol::Terminal(s) if s.is_empty() => {
                    nonterminal_rule
                        .expressions
                        .push(vec![Symbol::NonTerminal(prime_name.clone())]);
                }
                Symbol::NonTerminal(name) if name == &nonterminal_rule.name => {
                    prime_expression.extend(expression[1..].to_owned());
                    prime_expression.push(Symbol::NonTerminal(prime_name.clone()));
                }
                _ => {
                    nonterminal_rule.expressions.push(expression.clone());
                    nonterminal_rule
                        .expressions
                        .last_mut()
                        .unwrap()
                        .push(Symbol::NonTerminal(prime_name.clone()));
                }
            }
            if !prime_expression.is_empty() {
                prime.expressions.push(prime_expression);
            }
        }
        prime.expressions.push(vec![EMPTY]);
        primes.push(prime);
        eliminated.push(nonterminal_rule.clone());
    }
    eliminated.extend(primes);
    eliminated
}

pub fn first(symbols: &Vec<Symbol>, rules: &Vec<Rule>) -> HashSet<Symbol> {
    let mut result: HashSet<Symbol> = HashSet::new();
    if symbols.len() == 1 {
        match &symbols[0] {
            Symbol::Terminal(_) => {
                return symbols.iter().cloned().collect();
            }
            Symbol::NonTerminal(name) => {
                let rule = rules.iter().find(|r| &r.name == name).unwrap();
                for expression in &rule.expressions {
                    result.extend(first(expression, rules));
                }
                return result;
            }
            _ => {
                return result; // Endmarker is ignored
            }
        }
    }
    let mut empty_in_all = true;
    for symbol in symbols {
        let mut first_of_symbol = first(&vec![symbol.clone()], rules);
        if !first_of_symbol.contains(&EMPTY) {
            result.extend(first_of_symbol);
            empty_in_all = false;
            break;
        }
        first_of_symbol.remove(&EMPTY);
        result.extend(first_of_symbol);
    }
    if empty_in_all {
        result.insert(EMPTY);
    }
    result
}

pub fn follow(
    symbol: &Symbol,
    rules: &Vec<Rule>,
    knowns: &mut HashMap<Symbol, HashSet<Symbol>>,
) -> HashSet<Symbol> {
    if knowns.contains_key(symbol) {
        return knowns.get(symbol).unwrap().clone();
    }
    if let Symbol::NonTerminal(name) = symbol {
        let mut result: HashSet<Symbol> = HashSet::new();
        if &rules[0].name == name {
            result.insert(Symbol::Endmarker);
        }
        for rule in rules {
            for expression in &rule.expressions {
                if &rule.name == name {
                    continue;
                }
                if expression.last().unwrap() == symbol {
                    result.extend(follow(
                        &Symbol::NonTerminal(rule.name.clone()),
                        rules,
                        knowns,
                    ));
                    continue;
                }
                if let Some(idx) = expression.iter().position(|s| s == symbol) {
                    let first_set = first(&expression[idx + 1..].to_owned(), rules);
                    result.extend(first_set.clone());
                    if first_set.contains(&EMPTY) {
                        result.remove(&EMPTY);
                        result.extend(follow(
                            &Symbol::NonTerminal(rule.name.clone()),
                            rules,
                            knowns,
                        ));
                    }
                }
            }
        }
        knowns.insert(symbol.clone(), result.clone());
        result
    } else {
        HashSet::new()
    }
}

pub fn create_parse_table(rules: &Vec<Rule>) -> Option<HashMap<(Symbol, Symbol), Vec<Symbol>>> {
    let mut matrix: HashMap<(Symbol, Symbol), Vec<Symbol>> = HashMap::new();
    let mut knowns: HashMap<Symbol, HashSet<Symbol>> = HashMap::new();
    for rule in rules {
        for expression in &rule.expressions {
            let first_set = first(expression, rules);
            let current_symbol = Symbol::NonTerminal(rule.name.clone());
            for terminal in &first_set {
                if terminal == &EMPTY {
                    continue;
                }
                if let Some(existing) = matrix.get(&(current_symbol.clone(), terminal.clone())) {
                    if existing != &vec![EMPTY] {
                        if expression == &vec![EMPTY] {
                            continue;
                        } else {
                            return None;
                        }
                    }
                }
                matrix.insert(
                    (current_symbol.clone(), terminal.clone()),
                    expression.clone(),
                );
            }
            if first_set.contains(&EMPTY) {
                let follow_set = follow(&current_symbol, rules, &mut knowns);
                for terminal in &follow_set {
                    matrix.insert(
                        (current_symbol.clone(), terminal.clone()),
                        expression.clone(),
                    );
                }
                if follow_set.contains(&Symbol::Endmarker) {
                    matrix.insert(
                        (current_symbol.clone(), Symbol::Endmarker),
                        expression.clone(),
                    );
                }
            }
        }
    }
    Some(matrix)
}

#[cfg(test)]
mod tests {
    use crate::bnf::{parse_bnf, Rule, Symbol};

    use super::*;

    #[test]
    fn test_expand_leftmost_nonterminal() {
        let bnf = r#"
            <S> ::= <A> "a" | "b";
            <A> ::= <A> "c" | <S> "d" | "";
        "#;
        let parsed_rules = parse_bnf(bnf).unwrap();
        let a_expanded = expand_leftmost_nonterminal(&parsed_rules[1], &parsed_rules[0]);
        assert_eq!(
            a_expanded.expressions,
            vec![
                vec![
                    Symbol::NonTerminal("A".to_owned()),
                    Symbol::Terminal("c".to_owned())
                ],
                vec![
                    Symbol::NonTerminal("A".to_owned()),
                    Symbol::Terminal("a".to_owned()),
                    Symbol::Terminal("d".to_owned())
                ],
                vec![
                    Symbol::Terminal("b".to_owned()),
                    Symbol::Terminal("d".to_owned())
                ],
                vec![EMPTY]
            ]
        );
    }

    #[test]
    fn test_eliminate_left_recursion() {
        let bnf = r#"
            <S> ::= <A> "a" | "b";
            <A> ::= <A> "c" | <S> "d" | "";
        "#;
        let parsed_rules = parse_bnf(bnf).unwrap();
        let eliminated = eliminate_left_recursion(&parsed_rules);
        assert_eq!(
            eliminated,
            vec![
                Rule {
                    name: "S".to_owned(),
                    expressions: vec![
                        vec![
                            Symbol::NonTerminal("A".to_owned()),
                            Symbol::Terminal("a".to_owned()),
                        ],
                        vec![Symbol::Terminal("b".to_owned()),]
                    ]
                },
                Rule {
                    name: "A".to_owned(),
                    expressions: vec![
                        vec![
                            Symbol::Terminal("b".to_owned()),
                            Symbol::Terminal("d".to_owned()),
                            Symbol::NonTerminal("A_prime".to_owned())
                        ],
                        vec![Symbol::NonTerminal("A_prime".to_owned())]
                    ]
                },
                Rule {
                    name: "A_prime".to_owned(),
                    expressions: vec![
                        vec![
                            Symbol::Terminal("c".to_owned()),
                            Symbol::NonTerminal("A_prime".to_owned())
                        ],
                        vec![
                            Symbol::Terminal("a".to_owned()),
                            Symbol::Terminal("d".to_owned()),
                            Symbol::NonTerminal("A_prime".to_owned())
                        ],
                        vec![EMPTY]
                    ]
                }
            ]
        );
    }

    #[test]
    fn test_eliminate_left_recursion_do_nothing() {
        let bnf = r#"
            <S> ::= "a" <A> | "b";
            <A> ::= <S> "c" | <S> "d" | "";
        "#;
        let parsed_rules = parse_bnf(bnf).unwrap();
        let eliminated = eliminate_left_recursion(&parsed_rules);
        assert_eq!(parsed_rules[0], eliminated[0]);
        assert_eq!(
            parsed_rules[1],
            expand_leftmost_nonterminal(&parsed_rules[1], &parsed_rules[1])
        )
    }

    #[test]
    fn test_first() {
        let bnf = r#"
            <E> ::= <E> "+" <T> | <T>;
            <T> ::= <T> "*" <F> | <F>;
            <F> ::= "(" <E> ")" | "id";
        "#;
        let parsed_rules = eliminate_left_recursion(&parse_bnf(bnf).unwrap());
        assert_eq!(
            first(&vec![Symbol::Terminal("+".to_owned())], &parsed_rules),
            [Symbol::Terminal("+".to_owned())].iter().cloned().collect()
        );
        assert_eq!(
            first(
                &vec![
                    Symbol::Terminal("(".to_owned()),
                    Symbol::NonTerminal("E".to_owned()),
                    Symbol::Terminal(")".to_owned())
                ],
                &parsed_rules
            ),
            [Symbol::Terminal("(".to_owned())].iter().cloned().collect()
        );
        assert_eq!(
            first(&vec![Symbol::NonTerminal("F".to_owned())], &parsed_rules),
            [
                Symbol::Terminal("(".to_owned()),
                Symbol::Terminal("id".to_owned())
            ]
            .iter()
            .cloned()
            .collect()
        );
        assert_eq!(
            first(&vec![Symbol::NonTerminal("T".to_owned())], &parsed_rules),
            [
                Symbol::Terminal("(".to_owned()),
                Symbol::Terminal("id".to_owned())
            ]
            .iter()
            .cloned()
            .collect()
        );
        assert_eq!(
            first(&vec![Symbol::NonTerminal("E".to_owned())], &parsed_rules),
            [
                Symbol::Terminal("(".to_owned()),
                Symbol::Terminal("id".to_owned())
            ]
            .iter()
            .cloned()
            .collect()
        );
        assert_eq!(
            first(&vec![Symbol::NonTerminal("T".to_owned())], &parsed_rules),
            [
                Symbol::Terminal("(".to_owned()),
                Symbol::Terminal("id".to_owned())
            ]
            .iter()
            .cloned()
            .collect()
        );
        assert_eq!(
            first(&vec![Symbol::NonTerminal("E".to_owned(),)], &parsed_rules),
            [
                Symbol::Terminal("(".to_owned()),
                Symbol::Terminal("id".to_owned())
            ]
            .iter()
            .cloned()
            .collect()
        );
        assert_eq!(
            first(
                &vec![Symbol::NonTerminal("E_prime".to_owned(),)],
                &parsed_rules
            ),
            [Symbol::Terminal("+".to_owned()), EMPTY]
                .iter()
                .cloned()
                .collect()
        );
        assert_eq!(
            first(
                &vec![Symbol::NonTerminal("T_prime".to_owned())],
                &parsed_rules
            ),
            [Symbol::Terminal("*".to_owned()), EMPTY]
                .iter()
                .cloned()
                .collect()
        );
    }

    #[test]
    fn test_follow() {
        let bnf = r#"
            <E> ::= <E> "+" <T> | <T>;
            <T> ::= <T> "*" <F> | <F>;
            <F> ::= "(" <E> ")" | "id";
        "#;
        let parsed_rules = eliminate_left_recursion(&parse_bnf(bnf).unwrap());
        let mut knowns: HashMap<Symbol, HashSet<Symbol>> = HashMap::new();
        let follow_e = follow(
            &Symbol::NonTerminal("E".to_owned()),
            &parsed_rules,
            &mut knowns,
        );
        assert_eq!(
            follow_e,
            [Symbol::Terminal(")".to_owned()), Symbol::Endmarker]
                .iter()
                .cloned()
                .collect()
        );
        let follow_e_prime = follow(
            &Symbol::NonTerminal("E_prime".to_owned()),
            &parsed_rules,
            &mut knowns,
        );
        assert_eq!(
            follow_e_prime,
            [Symbol::Terminal(")".to_owned()), Symbol::Endmarker]
                .iter()
                .cloned()
                .collect()
        );
        let follow_t = follow(
            &Symbol::NonTerminal("T".to_owned()),
            &parsed_rules,
            &mut knowns,
        );
        assert_eq!(
            follow_t,
            [
                Symbol::Terminal("+".to_owned()),
                Symbol::Terminal(")".to_owned()),
                Symbol::Endmarker
            ]
            .iter()
            .cloned()
            .collect()
        );
        knowns.insert(Symbol::NonTerminal("T".to_owned()), follow_t);
        let follow_t_prime = follow(
            &Symbol::NonTerminal("T_prime".to_owned()),
            &parsed_rules,
            &mut knowns,
        );
        assert_eq!(
            follow_t_prime,
            [
                Symbol::Terminal("+".to_owned()),
                Symbol::Terminal(")".to_owned()),
                Symbol::Endmarker
            ]
            .iter()
            .cloned()
            .collect()
        );
        let follow_f = follow(
            &Symbol::NonTerminal("F".to_owned()),
            &parsed_rules,
            &mut knowns,
        );
        assert_eq!(
            follow_f,
            [
                Symbol::Terminal("+".to_owned()),
                Symbol::Terminal("*".to_owned()),
                Symbol::Terminal(")".to_owned()),
                Symbol::Endmarker
            ]
            .iter()
            .cloned()
            .collect()
        );
    }

    #[test]
    fn test_create_parse_table() {
        let bnf = r#"
            <E> ::= <E> "+" <T> | <T>;
            <T> ::= <T> "*" <F> | <F>;
            <F> ::= "(" <E> ")" | "id";
        "#;
        let parsed_rules = eliminate_left_recursion(&parse_bnf(bnf).unwrap());
        let parse_table = create_parse_table(&parsed_rules).unwrap();
        assert_eq!(
            parse_table,
            [
                (
                    (
                        Symbol::NonTerminal("E".to_owned()),
                        Symbol::Terminal("id".to_owned())
                    ),
                    vec![
                        Symbol::NonTerminal("T".to_owned()),
                        Symbol::NonTerminal("E_prime".to_owned())
                    ]
                ),
                (
                    (
                        Symbol::NonTerminal("E".to_owned()),
                        Symbol::Terminal("(".to_owned())
                    ),
                    vec![
                        Symbol::NonTerminal("T".to_owned()),
                        Symbol::NonTerminal("E_prime".to_owned())
                    ]
                ),
                (
                    (
                        Symbol::NonTerminal("E_prime".to_owned()),
                        Symbol::Terminal("+".to_owned())
                    ),
                    vec![
                        Symbol::Terminal("+".to_owned()),
                        Symbol::NonTerminal("T".to_owned()),
                        Symbol::NonTerminal("E_prime".to_owned())
                    ]
                ),
                (
                    (
                        Symbol::NonTerminal("E_prime".to_owned()),
                        Symbol::Terminal(")".to_owned())
                    ),
                    vec![EMPTY]
                ),
                (
                    (Symbol::NonTerminal("E_prime".to_owned()), Symbol::Endmarker),
                    vec![EMPTY]
                ),
                (
                    (
                        Symbol::NonTerminal("T".to_owned()),
                        Symbol::Terminal("id".to_owned())
                    ),
                    vec![
                        Symbol::NonTerminal("F".to_owned()),
                        Symbol::NonTerminal("T_prime".to_owned())
                    ]
                ),
                (
                    (
                        Symbol::NonTerminal("T".to_owned()),
                        Symbol::Terminal("(".to_owned())
                    ),
                    vec![
                        Symbol::NonTerminal("F".to_owned()),
                        Symbol::NonTerminal("T_prime".to_owned())
                    ]
                ),
                (
                    (
                        Symbol::NonTerminal("T_prime".to_owned()),
                        Symbol::Terminal("+".to_owned())
                    ),
                    vec![EMPTY]
                ),
                (
                    (
                        Symbol::NonTerminal("T_prime".to_owned()),
                        Symbol::Terminal("*".to_owned())
                    ),
                    vec![
                        Symbol::Terminal("*".to_owned()),
                        Symbol::NonTerminal("F".to_owned()),
                        Symbol::NonTerminal("T_prime".to_owned())
                    ]
                ),
                (
                    (
                        Symbol::NonTerminal("T_prime".to_owned()),
                        Symbol::Terminal(")".to_owned())
                    ),
                    vec![EMPTY]
                ),
                (
                    (Symbol::NonTerminal("T_prime".to_owned()), Symbol::Endmarker),
                    vec![EMPTY]
                ),
                (
                    (
                        Symbol::NonTerminal("F".to_owned()),
                        Symbol::Terminal("id".to_owned())
                    ),
                    vec![Symbol::Terminal("id".to_owned())]
                ),
                (
                    (
                        Symbol::NonTerminal("F".to_owned()),
                        Symbol::Terminal("(".to_owned())
                    ),
                    vec![
                        Symbol::Terminal("(".to_owned()),
                        Symbol::NonTerminal("E".to_owned()),
                        Symbol::Terminal(")".to_owned())
                    ]
                ),
            ]
            .iter()
            .cloned()
            .collect()
        );
    }
}
