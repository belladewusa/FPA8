#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int i=0;

  if(argc < 2){
    printf(2, "Usage: rm files...\n");
    exit();
  }

  while(i < argc){
    if(unlink(argv[i]) < 0){
      printf(2, "rm: %s failed to delete\n", argv[i]);
      i++;
      break;
    }
  }

  exit();
}
