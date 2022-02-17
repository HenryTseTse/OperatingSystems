#include "types.h"
#include "user.h"
#include "stat.h"

char buf[512];

char *newText(char *Prev, int Size, int newSize) { //New string function 
  char *New = malloc(newSize+1); //Create array object new memory
  if (New) {
    memmove(New, Prev, Size); //Moves previous memory into new memory
    free (Prev); //Deallocates previous memory
  }
  return New; //Returns array object new memory
}

char *Lowercase(char *Line, int Size) { //Lowercasecase function
  char *Copy = malloc(Size+1); //Create array object Copy
  strcpy (Copy, Line); //Copies string from Line into Copy
  int i;
  for (i=0; i < strlen(Copy); i++) {
    if (Copy[i] > 96 && Copy[i] < 123) { //Indices for UpperCase
      Copy[i] -= 32; //Returns indices for LowercaseCase
    }
  }
  return Copy; //Returns copy of Lowercasecase string
}

void
uniq(int fd, char *name, int c, int d, int ignore) { 
//c = counts occurences, d = prints only duplicate, i = ignore differences

  int i,n;

  int sameText;
  int Index = 0;
  int Repeat = 0;
  int curLength = 2;
  int preLength = 2;

  char *curLine = malloc(curLength+1); //Create array object for current line
  char *preLine = malloc(preLength+1); //Create array object for previous line
  char *newArray = malloc(curLength+1);

  while((n = read(fd, buf, sizeof(buf))) > 0){ //Stores file into buf array
    for(i=0; i<n; i++){
      if(buf[i] == '\n') { //If new line
        curLine[Index] = '\0'; //Indicates end of string
        
        if (ignore) { //Compares Lowercasecased string of prev and current line
          sameText = strcmp(Lowercase(preLine,preLength),Lowercase(curLine,curLength));
        } else { 
          sameText = strcmp(preLine,curLine);
        } //Compares the string of previous and current line
	
	//printf(1,"%s\n",curLine);
        if (sameText != 0) { //strcmp() returns 0 if str1 = str2
          if (c) {
            if (Repeat >= 1) { //strlen() computes length of string
              printf(1,"%d %s\n",Repeat,newArray); //Print count and group prefix lines by the number of occurences;
            }
	     strcpy(newArray,curLine);
	     Repeat = 1;

          } else if (d) {
            if (Repeat > 1) {
              printf(1,"%s\n", preLine); //Print count and group prefix lines by the number of occurences;
            }
          } else {
            printf(1,"%s\n",curLine); //Print current line
          }
        } else {
          Repeat++; //Add one to repeat, if line is repeated
        }

        if (preLength <= curLength) {
          preLine = newText(preLine, preLength, curLength); //Returns New
          preLength = curLength;
        }

        strcpy(preLine,curLine); //Copies string from preLine into curLine

        free(curLine); //Deallocates current line
        Index = 0;
        curLength = 2;
        curLine = malloc(curLength+1); //Create array object curLine
      } else {
        if (Index >= curLength) {
          curLine = newText(curLine, curLength, curLength*2); //Returns New
          curLength*=2;
        }
        curLine[Index] = buf[i];
        Index++;
      }
    }
  }

  if (c) {
    printf(1,"%d %s\n",Repeat,newArray); //Print number of repeated lines
  }

  if(n < 0){
    printf(1, "uniq: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;
  int NameIndex;
  int options[] = {0,0,0};

  if(argc <= 1){ //If input is only uniq
    uniq(0, argv[1], 0, 0, 0); //Input string w/ no options selected
    exit();
  }

  for(i = 1; i < argc; i++){
    if (strcmp("-c",argv[i]) == 0 && options[1] != 1) { //-c goes before -d
      options[0] = 1; //-c
    } else if (strcmp("-d",argv[i]) == 0 && options[0] != 1) { 
      options[1] = 1; //-d
    } else if (strcmp("-i",argv[i]) == 0) {
      options[2] = 1; //-i
    } else {
      NameIndex = i;
    }
  }

  if((fd = open(argv[NameIndex], 0)) < 0){ //If unable to access file
    printf(1, "uniq: cannot open %s\n", argv[i]);
    exit();
  }
  uniq(fd,argv[1],options[0],options[1],options[2]);
  close(fd);

  exit();
}
