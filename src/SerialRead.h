#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

int set_port(void);
const char* read_port(int fd);
int readPosY(const char* line);
int readPosX(const char* line);
int readGyroX(const char* line);
int readGyroY(const char* line);
int readGyroZ(const char* line);
int readAccelX(const char* line);
int readAccelY(const char* line);
int readAccelZ(const char* line);
