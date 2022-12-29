use crate::bnf::{Rule, Symbol};

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
                    prime_expression.push(Symbol::Terminal("".to_owned()));
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
        primes.push(prime);
        eliminated.push(nonterminal_rule.clone());
    }
    eliminated.extend(primes);
    eliminated
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
                vec![Symbol::Terminal("".to_owned())]
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
                        vec![Symbol::Terminal("".to_owned())]
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
}
