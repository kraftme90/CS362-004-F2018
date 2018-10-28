/*******************************************************************************
 * Riley Kraft
 * CS 362-400
 * 10/28/2018
 * 									Random Quiz 
 ******************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar(){
	char ch[9] = {'[','(','{',' ','a','x','}',')',']'};      // Array with target chars
	char random = rand() % 9;                                // Get random char from array
    return ch[random];                                       // Return random char to testme()
}

char *inputString(){
    char ch[5] = {'r','e','s','t', '\0'};                    // Array with target chars
    static char str[6];                                      // Set string array to target length
    int i;
    for(i = 0; i < 6; i++){                                  // For each char in the target length string
    	str[i] = ch[rand() % 5];                               // Get a random char from the target char array
    }
    return str;                                              // Return the string to testme()
}

void testme(){
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1){
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' ' && state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e' && s[2] == 's' && s[3] == 'e'
    	&& s[4] == 't' && s[5] == '\0' && state == 9){ // reset\0
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[]){
    srand(time(NULL));
    testme();
    return 0;
}
