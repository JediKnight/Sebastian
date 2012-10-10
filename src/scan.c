#include <stdio.h>
#include <stdlib.h>

#include "scan.h"

int main()
{
  scan(getenv("PATH"));
  return 0;
}
