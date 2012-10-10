#include <stdio.h>
#include <unistd.h>

int main(void) {
  if(daemon(0, 0) == 0) {
    sleep(5);
  } else {
    printf("error\n");
  }   
  return 0;
}
