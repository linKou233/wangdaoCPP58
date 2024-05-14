// scanner.c
#include "scanner.h"
#include <stdbool.h>
#include <string.h>

typedef struct {
    const char* start;
    const char* current;
    int line;
} Scanner;

// 全局变量
Scanner scanner;

void initScanner(const char* source) {
    // 初始化scanner
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}

/***************************************************************************************
 *                                   辅助方法											*
 ***************************************************************************************/
static bool isAlpha(char c) {       //判断是否是字母
    return (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        c == '_';
}

static bool isDigit(char c) {      //判断是否是数字
    return c >= '0' && c <= '9';
}

static bool isAtEnd() {            //判断是否在末尾
    return *scanner.current == '\0';
}

static char advance() {
    return *scanner.current++;
}

static char peek() {
    return *scanner.current;
}

static char peekNext() {
    if (isAtEnd()) return '\0';
    return *(scanner.current + 1);
}

static bool match(char expected) {
    if (isAtEnd()) return false;
    if (peek() != expected) return false;
    scanner.current++;
    return true;
}

// 传入TokenType, 创建对应类型的Token，并返回。
static Token makeToken(TokenType type) {
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

// 遇到不能解析的情况时，我们创建一个ERROR Token. 比如：遇到@，$等符号时，比如字符串，字符没有对应的右引号时。
static Token errorToken(const char* message) {
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner.line;
    return token;
}

static void skipWhitespace() {
    // 跳过空白字符: ' ', '\r', '\t', '\n'和注释
    // 注释以'//'开头, 一直到行尾
    // 注意更新scanner.line！
    for( ; ;) {
        char c = peek();
        switch (c) {
        case ' ':
        case '\r':
        case '\t':
            advance();
            break;
        case '\n':
        scanner.line++;
            advance();
            break;
        default:
            return;
        }
    }
}

// 参数说明：
// start: 从哪个索引位置开始比较
// length: 要比较字符的长度
// rest: 要比较的内容
// type: 如果完全匹配，则说明是type类型的关键字
static TokenType checkKeyword(int start, int length, const char* rest, TokenType type) {
    int len = (int)(scanner.current - scanner.start); // TOKEN的长度
    // start + length: 关键字的长度
    if (start + length == len && memcmp(scanner.start + start, rest, length) == 0) {
        return type;
    }
    return TOKEN_IDENTIFIER;
}

// 判断当前Token到底是标识符还是关键字
static TokenType identifierType() {
    // 确定identifier类型主要有两种方式：
    // 1. 将所有的关键字放入哈希表中，然后查表确认
    // 2. 将所有的关键字放入Trie树中，然后查表确认
    // Trie树的方式不管是空间上还是时间上都优于哈希表的方式
    char c = scanner.start[0];
    // 用switch语句实现Trie树
    switch (c) {
        case 'b': return checkKeyword(1, 4, "reak", TOKEN_BREAK);
        // TODO
        case 'c': 
            if(scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 'a': return checkKeyword(2, 2, "se", TOKEN_CASE);
                    case 'h': return checkKeyword(2, 2, "ar", TOKEN_CHAR);
                    case 'o': 
                        switch(scanner.start[3]) {
                            case 's' : return checkKeyword(3, 2, "st", TOKEN_CONST);
                            case 't' : return checkKeyword(4, 4, "inue", TOKEN_CONTINUE);
                        }
                }
            }
            break;
        case 'd':
            if (scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 'e': return checkKeyword(2, 5, "fault", TOKEN_DEFAULT);
                    case 'o': return checkKeyword(2, 4, "uble", TOKEN_DOUBLE);
                    //少了一个对do的定义
                }
            }
            break;
        case 'e':
            if (scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 'l': return checkKeyword(2, 2, "se", TOKEN_ELSE);
                    case 'n': return checkKeyword(2, 2, "um", TOKEN_ENUM);
                }
            }
            break;
        case 'f':
            if (scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 'l': return checkKeyword(2, 3, "oat", TOKEN_FLOAT);
                    case 'o': return checkKeyword(2, 1, "r", TOKEN_FOR);
                }
            }
            break;
        case 'g': return checkKeyword(1, 3, "oto", TOKEN_GOTO);
        case 'i':
            if (scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 'f': return checkKeyword(2, 0, "", TOKEN_IF);
                    case 'n': return checkKeyword(2, 2, "t", TOKEN_INT);
                }
            }
            break;
        case 'l': return checkKeyword(1, 3, "ong", TOKEN_LONG);
        case 'r': return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
        case 's':
            if (scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 'h': return checkKeyword(2, 3, "ort", TOKEN_SHORT);
                    case 'w': return checkKeyword(2, 4, "itch", TOKEN_SWITCH);
                    case 't': return checkKeyword(2, 4, "ruct", TOKEN_STRUCT);
                    case 'i': 
                        switch(scanner.start[2]) {
                            case 'g': return checkKeyword(3, 3, "ned", TOKEN_SIGNED);
                            case 'z': return checkKeyword(3, 3, "eof", TOKEN_SIZEOF);
                        }
                }
            }
            break;
        case 't': return checkKeyword(1, 7, "ypedef", TOKEN_TYPEDEF);
        case 'u':
            if (scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 'n': 
                        switch(scanner.start[2]) {
                            case 'i' : return checkKeyword(2, 4, "ion", TOKEN_UNION);
                            case 's' : return checkKeyword(2, 6, "signed", TOKEN_UNSIGNED);
                        }
            }
            break;
            }
        case 'v': return checkKeyword(1, 3, "oid", TOKEN_VOID);
        case 'w': return checkKeyword(1, 4, "hile", TOKEN_WHILE);
    }

    // identifier
    return TOKEN_IDENTIFIER;
}

static Token identifier() {
    // IDENTIFIER包含: 字母，数字和下划线
    while (isAlpha(peek()) || isDigit(peek())) {
        advance();
    }
    // 这样的Token可能是标识符, 也可能是关键字, identifierType()是用来确定Token类型的
    return makeToken(identifierType());
}

static Token number() {
    // 简单起见，我们将NUMBER的规则定义如下:
    // 1. NUMBER可以包含数字和最多一个'.'号
    // 2. '.'号前面要有数字
    // 3. '.'号后面也要有数字
    // 这些都是合法的NUMBER: 123, 3.14
    // 这些都是不合法的NUMBER: 123., .14
    while (isDigit(peek())) advance();
    if (peek() == '.' && isDigit(peekNext())) {
        advance();
        while (isDigit(peek())) advance();
    }

    return makeToken(TOKEN_NUMBER);
}

static Token string() {
    // 字符串以"开头，以"结尾，而且不能跨行
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') scanner.line++;
        advance();
    }
    if (isAtEnd()) return errorToken("Unterminated string.");
    advance();
    return makeToken(TOKEN_STRING);
}

static Token character() {
    // 字符'开头，以'结尾，而且不能跨行
    if (isAtEnd()) 
        return errorToken("Unterminated character.");
    advance();
    if (peek() != '\'') 
        return errorToken("Unterminated character.");
    advance();
    return makeToken(TOKEN_CHARACTER); 
}

/***************************************************************************************
 *                                   	分词											  *
 ***************************************************************************************/
Token scanToken() {
    // 跳过前置空白字符和注释
    skipWhitespace();
    // 记录下一个Token的起始位置
    scanner.start = scanner.current;

    if (isAtEnd()) return makeToken(TOKEN_EOF);

    char c = advance();
    if (isAlpha(c)) return identifier();
    if (isDigit(c)) return number();

    switch (c) {
        // single-character tokens
        case '(': return makeToken(TOKEN_LEFT_PAREN);
            // TODO
        case ')': return makeToken(TOKEN_RIGHT_PAREN);
        case '[': return makeToken(TOKEN_LEFT_BRACKET);
        case ']': return makeToken(TOKEN_RIGHT_BRACKET);
        case '{': return makeToken(TOKEN_LEFT_BRACE);
        case '}': return makeToken(TOKEN_RIGHT_BRACE);
        case ';': return makeToken(TOKEN_SEMICOLON);
        case ',': return makeToken(TOKEN_COMMA);
        case '.': return makeToken(TOKEN_DOT); 
        case '~': return makeToken(TOKEN_TILDE); 
            // one or two characters tokens
        case '+':
            if (match('+'))         return makeToken(TOKEN_PLUS_PLUS);
            else if (match('='))    return makeToken(TOKEN_PLUS_EQUAL);
            else                    return makeToken(TOKEN_PLUS);
            // TODO
        case '*':
            if (match('='))         return makeToken(TOKEN_STAR_EQUAL);
            else                    return makeToken(TOKEN_STAR);
        case '-':
            if (match('-'))         return makeToken(TOKEN_MINUS_MINUS);
            else if (match('='))    return makeToken(TOKEN_MINUS_EQUAL);
            else if (match('>'))    return makeToken(TOKEN_MINUS_GREATER);
            else                    return makeToken(TOKEN_MINUS);
        case '/':
            if (match('='))         return makeToken(TOKEN_SLASH_EQUAL);
            else                    return makeToken(TOKEN_SLASH);
        case '%': 
            if (match('='))         return makeToken(TOKEN_PERCENT_EQUAL);
            else                    return makeToken(TOKEN_PERCENT);
        case '&':
            if (match('='))         return makeToken(TOKEN_AMPER_EQUAL);
            else if (match('&'))    return makeToken(TOKEN_AMPER_AMPER);
            else                    return makeToken(TOKEN_AMPER);
        case '|':
            if (match('='))         return makeToken(TOKEN_PIPE_EQUAL);
            else if (match('|'))    return makeToken(TOKEN_PIPE_PIPE);
            else                    return makeToken(TOKEN_PIPE);
        case '^': 
            if (match('='))         return makeToken(TOKEN_HAT_EQUAL);
            else                    return makeToken(TOKEN_HAT);
        case '=': 
            if (match('='))         return makeToken(TOKEN_EQUAL_EQUAL);
            else                    return makeToken(TOKEN_EQUAL);
        case '!': 
            if (match('='))         return makeToken(TOKEN_BANG_EQUAL);
            else                    return makeToken(TOKEN_BANG);
        case '<':
            if (match('='))         return makeToken(TOKEN_LESS_EQUAL);
            else if (match('<'))    return makeToken(TOKEN_LESS_LESS);
            else                    return makeToken(TOKEN_LESS);
        case '>':
            if (match('='))         return makeToken(TOKEN_GREATER_EQUAL);
            else if (match('>'))    return makeToken(TOKEN_GREAER_GREATER);
            else                    return makeToken(TOKEN_GREATER);
        


        case '"': return string();
        case '\'': return character();
            // various-character tokens
    }
    
    return errorToken("Unexpected character.");
}