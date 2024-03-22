#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

#define MAX_INPUT_LENGTH 100

int main(){
  char str[MAX_INPUT_LENGTH];

  while (1) {
    
    //Display prompt
    printf("> ");

    //Read user input
    //    int i = 0;
    //  char c;

    //  while ((c = getchar()) != '\n' && i < MAX_INPUT_LENGTH - 1) {
    //  if (space_char(c)) {
    //	if (i > 0 && !space_char(input[i-1])){
    //	  input[i++] = c;
    //	}
    //  } else {
    //	input[i++] = c;
    //  }
    //  }
    //  input[i] = '\0';
    
    fgets(str, sizeof(str), stdin);
    
    //Echo input
    printf("%s\n", str);

    //tokenize input
    List* history = init_history();
    add_history(history, str);
    
    char **tokens = tokenize(str);

    for (int i = 0; tokens[i] != NULL; i++) {
      printf("Tokens: %s", tokens[i]);
    }
    
    free_tokens(tokens);
  }
  return 0;
}
