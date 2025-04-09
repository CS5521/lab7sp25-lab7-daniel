#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    printf(1, "usage: schedtest loops tickets1 [ tickets2 ... ticketsN]\n"
              "     loops must be greater than 0\n"
              "     tickets must be greater than or equal to 10\n"
              "     up to 7 tickets can be provided\n");
    exit();
  }

  int calls = atoi(argv[1]);
  int nprocs = argc - 2 > 7 ? 7 : argc - 2;

  int * child_pids = malloc(nprocs * sizeof(int));

  int i;
  for(i = 0; i < nprocs; i++)
  {
    int pid = fork();
    if (pid == 0)
    {
      settickets(atoi(argv[i + 2]));
      while(1) {}
    }

    child_pids[i] = pid;
  }

  for(i = 0; i < calls; i++)
  {
    ps();
    sleep(3);
  }

  for(i = 0; i < nprocs; i++)
  {
    kill(child_pids[i]);
  }
  free(child_pids);

  for(i = 0; i < nprocs; i++)
  {
    wait();
  }

  exit();
}

