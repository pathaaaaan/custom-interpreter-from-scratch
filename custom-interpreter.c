#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXSIZE 1000
#define INT 0
#define ERR -1
#define OPERATOR 1
#define INT_STR "INT"
#define OPERATOR_STR "OPERATOR"

// definition of Token
typedef struct
{
    int type; // int or operator
    char operator_value;
    int number_value;
} Token;

int current_pos = 0;
Token current_token;

bool is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

bool is_operator(char c)
{
    return (c == '+' || c == '-');
}

bool is_whitespace(char c){
    return c == ' ';
}

void get_next_token(char *text)
{
    char c = text[current_pos];
    while(is_whitespace(c)){
        current_pos += 1;
        c = text[current_pos];
    }

    // is char a digit? --> number_token else operator_token
    if (is_digit(c))
    {
        int current_number = c - '0';
        current_pos += 1;
        while(is_digit(text[current_pos])){
            current_number *= 10;
            current_number += (text[current_pos] - '0');
            current_pos += 1;
        }
        current_token.type = INT;
        current_token.number_value = current_number;
        current_token.operator_value = ' ';
    }
    else if (is_operator(c))
    {
        current_token.type = OPERATOR;
        current_token.number_value = 0;
        current_token.operator_value = c;
        current_pos++;
    }
    else
    {
        printf("Invalid Token recieved : %c\n", c);
        exit(-1);
    }
}

// represents the token as string in given string s
void token_str(Token token, char *s)
{
    sprintf(s, "Token (type = %s, number_value = %d, operator_value = %c)", token.type == INT ? INT_STR : OPERATOR_STR, token.number_value, token.operator_value);
}
void parse(int type)
{

    if (current_token.type != type)
    {
        char s[100];
        token_str(current_token, s);
        printf("Syntax Error at position %d. \nExpected token of type %s,  but recieved type %s\n", current_pos, type == INT ? INT_STR : OPERATOR_STR, s);
        exit(-1);
    }
}

int interpret(char *text)
{
    // create tokens from input --> tokenizer
    get_next_token(text); // expected to be integer
    parse(INT);
    int left = current_token.number_value;

    get_next_token(text); // expected to be operator
    parse(OPERATOR);
    char operator = current_token.operator_value;

    get_next_token(text); // expected to be integer
    parse(INT);
    int right = current_token.number_value;

    current_pos = 0;
    int result = 0;
    if (operator == '+')
        result = left + right;
    else
        result = left - right;

    return result;
}

int main()
{
    char s[MAXSIZE];
    printf("Interpreter Running....\n");
    while (true)
    {
        printf(">>> ");
        fgets(s, MAXSIZE, stdin);
        int res = interpret(s);
        printf("%d\n", res);
    }
}