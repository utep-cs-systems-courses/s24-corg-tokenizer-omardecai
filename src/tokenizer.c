#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

//returns true if c is a whitespace character
int space_char(char c) {
  return c == ' ' || c == '\t';
}

//returns true if c is a NON-whitespace character
int non_space_char(char c) {
  return c != ' ' && c != '\t' && c != '\0';
}

/* Returns a pointer to the first character of the next
   space-separated token in zero terminated str. */
char *token_start(char *str) {
  while (*str != '\0' && (*str == ' ' || *str == '\t')){
    str++;
  }

  //if string is empty return null
  if (*str == '\0'){
    return NULL;
  }

  //return pointer to the start of the token
  return str;
}

// Returns the length of the null-terminated string 'str'
int string_length(const char *str) {
  int length = 0;
  while (str[length] != '\0') {
    length++;
  }
  return length;
}

/* Returns a pointer terminator chat following *token */
char *token_terminator(char *token) {
  //move pointer until a space or null terminator is encountered
  while (*token != '\0' && *token != ' ' && *token != '\t'){
    token++;
  }
  return token;
}

/* Counts the number of tokens in the string argument. */
int count_tokens(char *token){
  int count = 0;
  char *token_start = NULL;

  while(*token != '\0'){
    //finds the start of the next token
    token_start = token_terminator(token);

    //incriments count if not NULL
    if (token_start != NULL) {
      count++;
      
      //move str to next character after the token
      token = token_start;
    } else {
      break;
    }
  }
  return count;
}

/* Returns a fresh;y allocated new zero-terminated string containing
   a specified number of characters from the input string 'inStr'.*/
char *copy_str(char *inStr, short len) {
  
  //allocate memory for the new string
  char *copy = (char *)malloc((len + 1) * sizeof(char));
  
  //if memory allocation fails return NULL
  if (copy == NULL) {
    return NULL;
  }

  //copy characters from inStr to the new string
  for (int i = 0; i < len; i++) {
    copy[i] = inStr[i];
  }

  //null-terminate the new string
  copy[len] = '\0';

  return copy;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated
   space-separated tokens from zero-terminated str. */
char **tokenize(char* str){
  //count the number of tokens
  int num_tokens = count_tokens(str);
  if (num_tokens == 0){
    return NULL;
  }

  //allocate memory for the array of pointers to tokens
  char **tokens = (char **)malloc((num_tokens + 1) * sizeof(char *));
  if (tokens == NULL) {
    return NULL;
  }

  //tokenize the string
  int token_index = 0;
  char *start_of_token = token_start(str);
  while (start_of_token != NULL) {
    char *token_end = token_terminator(start_of_token);
    int token_length = token_end - start_of_token;

    //allocate memory for token string and copy the token
    tokens[token_index] = (char *)malloc((token_length + 1) * sizeof(char));
    if (tokens[token_index] == NULL) {
      //memory allocation failed, free previous allocated memory
      for (int i = 0; i < token_index; i++) {
	free(tokens[i]);
      }
      free(tokens);
      return NULL;
    }
    //copy the tokens
    for (int i = 0; i < token_length; i++) {
      tokens[token_index][i] = start_of_token[i];
    }
    tokens[token_index][token_length] = '\0';
    token_index++;
    start_of_token = token_start(token_end);
    
  }

  //null-terminate the array of tokens
  tokens[token_index] = NULL;

  return tokens;
}

//prints all tokens
void print_tokens(char **tokens) {
  if (tokens == NULL) {
    printf("No Tokens\n");
    return;
  }

  for (int i = 0; tokens[i] != NULL; i++) {
    printf("%s\n", tokens[i]);
  }
}

//Frees all tokens and the vector containing them
void free_tokens(char **tokens) {
  if(tokens == NULL) {
    return;
  }

  //free tokens
  for(int i = 0; tokens[i] != NULL; i++){
    free(tokens[i]);
  }

  free(tokens);
}
