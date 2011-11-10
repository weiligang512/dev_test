#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <signal.h>
 
void handler (int sig)
{
  printf ("\nexiting...(%d)\n", sig);
  exit (0);
}
 
void perror_exit (char *error)
{
  perror (error);
  handler (9);
}
 
int main (int argc, char *argv[])
{
  struct input_event ev[64];
  int fd, rd, value, size = sizeof (struct input_event);
  char name[256] = "Unknown";
  char *device = NULL;
 
  //Setup check
  if (argv[1] == NULL){
      printf("Please specify (on the command line) the path to the dev event interface device\n");
      exit (0);
    }
 
  if ((getuid ()) != 0)
    printf ("You are not root! This may not work...\n");
 
  if (argc > 1)
    device = argv[1];
 
  //Open Device
  if ((fd = open (device, O_RDONLY)) == -1)
    printf ("%s is not a vaild device.\n", device);
 
  //Print Device Name
  ioctl (fd, EVIOCGNAME (sizeof (name)), name);
  printf ("Reading From : %s (%s)\n", device, name);
 
  while (1)
  {
      if ((rd = read (fd, ev, size * 64)) < size)
          perror_exit ("read()");     
 
      value = ev[0].value;
 
      //if (value != ' ' && ev[1].value == 1 && ev[1].type == 1){ // Only read the key press event
     if (value != ' '){
      printf ("Code0[%d]\n", (ev[0].code));
      printf ("Code1[%d]\n", (ev[1].code));
      printf ("Code2[%d]\n", (ev[2].code));
      printf ("Value0[%d]\n", (ev[0].value));
      printf ("Value1[%d]\n", (ev[1].value));
      printf ("Value2[%d]\n", (ev[2].value));
      }
  }
 
  return 0;
}
