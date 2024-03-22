#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

#define MAX_INPUT_LENGTH 1000

int main(){
  char input[MAX_INPUT_LENGTH];

  while (1) {
    
    //Display prompt
    printf("> ");

    //Read user input
    int i = 0;
    char c;

    while ((c = getchar()) != '\n' && i < MAX_INPUT_LENGTH - 1) {
      if (space_char(c)) {
	if (i > 0 && !space_char(input[i-1])){
	  input[i++] = c;
	}
      } else {
	input[i++] = c;
      }
    }
    input[i] = '\0';
    
    
    //Echo input
    printf("%s\n", input);

    //tokenize input
    List* history = init_history();
    add_history(history, input);
    
    char **tokens = tokenize(input);
    if (tokens == NULL) {
      printf("Failed to tokenize input\n");
      continue;
    }

    printf("Tokens:\n");
    print_tokens(tokens);
    
    free_tokens(tokens);
  }
  return 0;
}
