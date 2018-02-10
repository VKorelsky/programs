#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int valid_args(int day_size, int first_day) {
  if ( (day_size < 2) || (first_day < 1) || (first_day > 7) ) { return 0; }
  return 1;
}

void print_row_delimiter() {
  printf("|");
}

void print_newline() {
  printf("\n");
}

void print_separator_row(int width) {
    print_row_delimiter();
    int i;
    for(i = 0; i < width-2; i++) {
      printf("-");
    }
    print_row_delimiter();
    print_newline();
}

void print_whitespace(int width) {
    for(int i = 0; i < width; i++){
        printf(" ");
    }
}

void print_days_row(int day_size, int width) {
    char* days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    print_row_delimiter();
    int i;
    for(i = 0; i < 7; i++){
      printf(" %-*.*s |", day_size, day_size, days[i]);
    }
    print_newline();
    print_separator_row(width);
}


void print_month_row(int width, int index){
    char* months[12] = {"January", "February", "March", "April","May", "June", "July", "August",
                        "September", "October", "November", "December"};
    char* month = months[index];

    int center_width = width - 2;
    int whitespace_width = center_width - strlen(month);

    int start_whitespace_width = whitespace_width/2;
    int end_whitespace_width = whitespace_width - start_whitespace_width;

    print_separator_row(width);
    print_row_delimiter();

    print_whitespace(start_whitespace_width);
    printf("%s", month);
    print_whitespace(end_whitespace_width);

    print_row_delimiter();
    print_newline();
    print_separator_row(width);
}

void print_calendar_rows(int day_size, int start_index) {
    if (start_index == 0){ start_index = 7; }

    int day = 1;
    int count = 1;

    print_row_delimiter();
    while (day <= 30){
      if ((count < start_index)) {
        printf(" %-*s |", day_size, " ");
      } else {
        printf(" %-*d |", day_size, day);
        day++;
      }

      // day will have been incremented before, so we need to check against 31 in the second case
      if ( (count%7 == 0) && !(day == 31) ) {
        print_newline();
        print_row_delimiter();
      }

      count++;
    }

    // check distance from a num divisible by seven, with one extra spot hence count-1
    while ((count-1)%7 != 0){
      printf(" %-*s |", day_size, " ");
      count++;
    }

    print_newline();
}

int main(int argc, char* argv[]) {
  if(argc != 3) {
    printf("Usage: <day_size> <first_day>\n");
    exit(-1);
  }

  int day_size;
  int first_day;

  // Q: are the arguments supposed to be integers only ?
  if ( !(day_size = atof(argv[1])) || !(first_day = atof(argv[2])) ) {
    printf("Error: arguments must be integers superior to 0\n" );
    exit(-1);
  }

  if ( !(valid_args(day_size, first_day)) ) {
    printf("Error: day_size must be equal or superior to 2, first_day must be between 1 and 7 \n");
    exit(-1);
  }

  int width = (day_size + 3) * 7 + 1;
  int start_index = first_day;
  int i;

  for(i = 0; i < 12; i++){
    print_month_row(width, i);
    print_days_row(day_size, width);

    print_calendar_rows(day_size, start_index);

    start_index = (start_index + 30)%7;
  }

  print_separator_row(width);
}
