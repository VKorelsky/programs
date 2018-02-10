#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int is_float(char *s) {
  // gets pointer to string[0]
  // go over each character and check that each is a digit, or +/-/.
  char *char_pointer = s;

  while (*char_pointer && *char_pointer != '\n') {
    // if the character is a not one of (digit, +, - or .) -> R 0
    char cur = *char_pointer;
    if ( cur != '+' && cur != '-' && cur != '.' && !(isdigit(cur)) ) {
      return 0;
    }
    char_pointer++;
  }
  return 1;
}


int main(int argc, char* argv[]) {
  // maybe refactor this
    if (argc != 4) {
      printf("usage: <file_path> <floating_value> <floating_value>\n");
      exit(-1);
    }

    FILE* plot_script = fopen(argv[1], "r");

    if (plot_script == NULL) {
        printf("Error: bad file\n");
        exit(-1);
    }

    if ( !(is_float(argv[2])) || !(is_float(argv[3])) ){
        printf("Error: bad float arg\n");
        exit(-1);
    }

    float a = atof(argv[2]);
    float b = atof(argv[3]);

    char line[1000];

    while(fgets(line, sizeof(line), plot_script)) {
      char *line_ptr = line;
      // use the pointer to move along the line array
      while(*line_ptr && (*line_ptr != '\n' || *line_ptr != EOF)) {
        if (*line_ptr == '#') {
          char *probe = line_ptr;

          if( (*(probe+1) == 'A') && (*(probe+2) == '#') ) {
            printf("%.6f", a);
            line_ptr += 2;
          } else if( (*(probe+1) == 'B') && (*(probe+2) == '#') ){
            printf("%.6f", b);
            line_ptr += 2;
          } else {
            printf("%c", *line_ptr );
          }
        } else {
          printf("%c", *line_ptr);
        }

        line_ptr++;
      }


    }

}
