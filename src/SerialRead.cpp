#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdlib.h>

inline void str_split(char *str, char delim) { 
  char *p = str; 
  while(p[0]) { 
    if (p[0] == delim) p[0] = 0; 
    p++; 
  } 
}

// SET INPUT PORT FOR ARDUINO CONTROLLER INTERFACE
int set_port(void)
{
  int fd = open("/dev/ttyACM0", O_RDONLY | O_NOCTTY);
  return fd;
}
// READ 32 CHARACTER BUFFER FROM SERIAL PORT
// THROW AWAY INVALID LINES
const char* read_port(int fd)
{
  static char buffer[32];
  char buf = '\0';
  int n = 0;
  int spot = 0;
 
  n = read(fd, &buf, 1);
  if(n > 0){
      buffer[spot] = buf;
      spot += n;
    }
  while(buf != '\n') {
    
    n = read( fd, &buf, 1 );
    if(n > 0){
      buffer[spot] = buf;
      spot += n;
    }
  }

  buffer[spot] = '\0';
  
  return buffer;
}

// 2-AXIS JOYSTIC READ X POSITION 
int readPosX(const char* line)
{
  char *sens;
   char *dir;
   char *val;
   int vali;
   char *search = " ";
   char *ptr = const_cast<char*> (line);
   char lArr [32];
   strcpy(lArr, line);

   sens = strtok(lArr,":");
   dir = strtok (NULL,":");
   val = strtok(NULL,":");
   if(strcmp(sens, "P") == 0 && strcmp(dir, "X") == 0) {
     
     // if(val != NULL) {
     vali = strtol(val, NULL, 10);
     // }
     // else
     //   return -1000;
    
   }

}

// 2-AXIS JOYSTICK READ Y POSITION
int readPosY(const char* line)
{

  char *sens;
  char *dir;
  char *val;
  int vali;
  char *search = " ";
  char *ptr = const_cast<char*> (line);
  char lArr [32];
  strcpy(lArr, line);

  sens = strtok(lArr,":");
  dir = strtok (NULL,":");
  val = strtok(NULL,":");
  if(strcmp(sens, "P") == 0 && strcmp(dir, "Y") == 0) { 
  
     // if(val != NULL)
    vali = (int) strtol(val,NULL,10);
     // else
       // return -1;
   }

}




// int main(int argc, char *argv[])
// {
//   int fd = set_port();
//   int x = 0;
//   int y = 0;
//    while(1) { 
//     const char* pos = read_port(fd);
//     if(pos != NULL) { 
//      x = readPosX(pos);
//      y = readPosY(pos);
//      printf("CX: %d\n", x);
//      printf("CY: %d\n", y);
//     }
//       // x = readPosX(pos);
//       // y = readPosY(pos);
//       // if(x > 0)
//       	// printf("CX: %d \n", x);
//       // if(y > 0)
//       // 	printf("CY: %d \n", y);
     
      
//       // printf("CY: %d\n", y);
      
//     }
   
   
   

//   return 0;
 
// }

