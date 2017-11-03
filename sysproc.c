#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  //Changed for 1.a, cs 153
  int currStatus = 0;
  if (argint(0, &currStatus) > 0)
  {	
	return -1;
  }
  exit(currStatus);
  return 0;  // not reached
}

int
sys_wait(void)
{
  //Changed for 1.b, cs 153
  int *status = 0;
  if (argptr(0, (char**)&status, sizeof(int)) > 0)
  {
	return -1;
  }
  return wait(status);
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//Added for part 1.c, cs 153
int sys_waitpid(void)
{
  int pid = 0;
  int *status = 0; 
  int options = 0;

  argint(0, &pid);
  argptr(1, (char**)&status, sizeof(int));
  argint(2, &options);

  return waitpid(pid, status, options);
}

//Added for Part 2, cs 153
int sys_setPriority(void)
{

//  acquire(&ptable.lock);
  int priority = 0;
  
  argint(0, &priority);
 
  if (priority > 63)
  {
	priority = 63;
  }
  return setPriority(priority); 
}
