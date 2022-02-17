#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf [1024];

void tail (int fd, char *name, int line) {
  int count = 0;
  int index, n; // initialize index and size
  int lines; // total lines
  int temp = open ("temp", O_CREATE | O_RDWR);

  while((n = read(fd, buf, sizeof(buf))) > 0 )
  {
    write (temp, buf, n);                            
    for(index=0;index<=n ;index++)
    {
      if(buf[index] != '\n')                              
      {
        continue;
      }
      else                                             
      {
        lines++;
      }
    }
  }
  close (temp);

  if (n < 0)
  {
    printf(1, "tail error\n");
    exit();
  }

  temp = open ("temp", 0); //open file from beginning
  while((n = read(temp, buf, sizeof(buf))) > 0 )
  {
    for (index = 0; index<n; index++)
    {
      if (count >= (lines - line))
      {
        printf(1,"%c",buf[index]);
      }
      else if (lines < line) 
      {
        printf(1,"%c",buf[index]);
      }
      else if (buf[index] == '\n')
      {
        count++;
      }
    }
  }
  close (temp);
  
  unlink("temp"); // delete            
}


int
main(int argc, char *argv[]) {
  int index;
  int x = 10; // default
  int fd = 0; // user input
  char a;
  char *file;

  file = ""; // user input
     
  if (argc <= 1)
  {
    tail(0, "", 10); // print default lines if no file
    exit();
  }
  else {
    for (index = 1; index < argc; index++)
    {
          a = *argv[index]; 
      if (a == '-')
      {             
        argv[index]++;
        x = atoi(argv[index]++);
      }
                
      else
      {    // print default 
        if ((fd = open(argv[index], 0)) < 0)
        { // error 
          printf(1, "tail, unable to access file %s\n", argv[index]);
          exit();
        }
      }
    }
         
  tail(fd,file, x);
  close(fd);
  exit();

  }
}
