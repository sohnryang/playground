use std::{str::Chars, vec};

#[derive(Default, Clone)]
pub struct Rule {
    pub name: String,
    pub expressions: Vec<Vec<Symbol>>,
}

#[derive(Clone, Debug, PartialEq)]
pub enum Symbol {
    Terminal(String),
    NonTerminal(String),
}

#[derive(Debug, PartialEq)]
pub enum Token {
    Terminal(String),
    NonTerminal(String),
    Assignment,
    Choice,
    Semicolon,
}

pub fn get_token(str_iter: &mut Chars) -> Option<Token> {
    let mut token = String::new();
    let mut last_char = ' ';
    while last_char.is_whitespace() {
        match str_iter.next() {
            Some(c) => {
                last_char = c;
            }
            None => {
                return None;
            }
        }
    }
    if last_char == '<' {
        last_char = ' ';
        while last_char != '>' {
            match str_iter.next() {
                Some(c) => {
                    last_char = c;
                }
                None => {
                    break;
                }
            }
            if last_char != '>' {
                token.push(last_char);
            }
        }
        return Some(Token::NonTerminal(token));
    }
    if last_char == '"' {
        last_char = ' ';
        while last_char != '"' {
            match str_iter.next() {
                Some(c) => {
                    last_char = c;
                }
                None => {
                    return None;
                }
            }
            if last_char != '"' {
                token.push(last_char);
            }
        }
        return Some(Token::Terminal(token));
    }
    if last_char == ':' {
        if str_iter.next() != Some(':') {
            return None;
        }
        if str_iter.next() != Some('=') {
            return None;
        }
        return Some(Token::Assignment);
    }
    if last_char == ';' {
        return Some(Token::Semicolon);
    }
    if last_char == '|' {
        return Some(Token::Choice);
    }
    None
}

pub fn parse_bnf(bnf_str: &str) -> Option<Vec<Rule>> {
    let mut parsed_bnf: Vec<Rule> = vec![];
    let mut it = bnf_str.chars();
    let mut parsing_lhs = true;
    let mut current_rule: Rule = Default::default();
    let mut current_expression: Vec<Symbol> = vec![];
    while let Some(token) = get_token(&mut it) {
        match token {
            Token::NonTerminal(name) => {
                if parsing_lhs {
                    current_rule = Rule {
                        name: name.clone(),
                        expressions: vec![],
                    };
                } else {
                    current_expression.push(Symbol::NonTerminal(name.clone()));
                }
            }
            Token::Terminal(s) => {
                if parsing_lhs {
                    return None;
                } else {
                    current_expression.push(Symbol::Terminal(s.clone()));
                }
            }
            Token::Assignment => {
                parsing_lhs = false;
            }
            Token::Choice => {
                current_rule.expressions.push(current_expression.clone());
                current_expression.clear();
            }
            Token::Semicolon => {
                parsing_lhs = true;
                current_rule.expressions.push(current_expression.clone());
                parsed_bnf.push(current_rule.clone());
                current_expression.clear();
            }
        }
    }
    Some(parsed_bnf)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_get_token() {
        assert_eq!(get_token(&mut "|".chars()), Some(Token::Choice));
        assert_eq!(
            get_token(&mut "<hi>".chars()),
            Some(Token::NonTerminal("hi".to_owned()))
        );
        assert_eq!(
            get_token(&mut "\"str\"".chars()),
            Some(Token::Terminal("str".to_owned()))
        );
        assert_eq!(get_token(&mut "\"".chars()), None);
        assert_eq!(get_token(&mut "  ".chars()), None);
        assert_eq!(
            get_token(&mut " <abcd> ".chars()),
            Some(Token::NonTerminal("abcd".to_owned()))
        );
        assert_eq!(get_token(&mut "::=".chars()), Some(Token::Assignment));
        assert_eq!(
            get_token(&mut "\"\"".chars()),
            Some(Token::Terminal("".to_owned()))
        );

        let bnf_rule = "<hell> ::= <world> | \"abcd\" <efgh>;".to_owned();
        let mut it = bnf_rule.chars();
        assert_eq!(
            get_token(&mut it),
            Some(Token::NonTerminal("hell".to_owned()))
        );
        assert_eq!(get_token(&mut it), Some(Token::Assignment));
        assert_eq!(
            get_token(&mut it),
            Some(Token::NonTerminal("world".to_owned()))
        );
        assert_eq!(get_token(&mut it), Some(Token::Choice));
        assert_eq!(get_token(&mut it), Some(Token::Terminal("abcd".to_owned())));
        assert_eq!(
            get_token(&mut it),
            Some(Token::NonTerminal("efgh".to_owned()))
        );
        assert_eq!(get_token(&mut it), Some(Token::Semicolon));
        assert_eq!(get_token(&mut it), None);
    }

    #[test]
    fn test_parse_bnf() {
        let bnf = r#"
            <postal-address> ::= <name-part> <street-address> <zip-part>;
            <personal-part> ::= <initial> "." | <first-name>;
        "#;
        let parsed = parse_bnf(bnf).unwrap();
        assert_eq!(parsed.len(), 2);
        assert_eq!(parsed[0].name, "postal-address".to_owned());
        assert_eq!(parsed[0].expressions.len(), 1);
        assert_eq!(parsed[0].expressions[0].len(), 3);
        assert_eq!(
            parsed[0].expressions[0][0],
            Symbol::NonTerminal("name-part".to_owned())
        );
        assert_eq!(
            parsed[0].expressions[0][1],
            Symbol::NonTerminal("street-address".to_owned())
        );
        assert_eq!(
            parsed[0].expressions[0][2],
            Symbol::NonTerminal("zip-part".to_owned())
        );
        assert_eq!(parsed[1].name, "personal-part".to_owned());
        assert_eq!(parsed[1].expressions.len(), 2);
        assert_eq!(parsed[1].expressions[0].len(), 2);
        assert_eq!(
            parsed[1].expressions[0][0],
            Symbol::NonTerminal("initial".to_owned())
        );
        assert_eq!(
            parsed[1].expressions[0][1],
            Symbol::Terminal(".".to_owned())
        );
        assert_eq!(parsed[1].expressions[1].len(), 1);
        assert_eq!(
            parsed[1].expressions[1][0],
            Symbol::NonTerminal("first-name".to_owned())
        );
    }
}
