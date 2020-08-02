/*	Program to demonstrate shared memory segment: 
		syscalls => shmget(), shmat(), shmdt() & shmctl() 
 ---------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

//define a unique key for a shared memory region
#define SHM_KEY 0x6236

typedef struct shm
{
	int cnt;
}shm_t;

//global variable - stored into the bss section
shm_t var;

int main(void)
{
	shm_t *ptr = NULL;
	int ret, i, status, shmid;

	shmid = shmget(SHM_KEY, sizeof(shm_t), IPC_CREAT|0600);
	if(shmid < 0)
	{
		perror("shmget() failed");
		_exit(1);
	}

	/* attach shm segment associated with shmid with system specified shmaddr
	and returns the addr */
	ptr = (shm_t*)shmat(shmid, NULL, 0);

	if(ptr == (void*)-1)
	{
		perror("shmat() failed");
		_exit(2);
	}

	ptr->cnt = 0;
	ret = fork();
	if(ret == 0)
	{
		//child process
		for(i=0; i<10; i++)
		{
			ptr->cnt++;
			printf("child : %d\n", ptr->cnt);
			sleep(1);
		}
		//detach shm segment from the process
		shmdt(ptr);
	}
	else
	{
		//parent process
		for(i=0; i<10; i++)
		{
			ptr->cnt--;
			printf("parent : %d\n", ptr->cnt);
			sleep(1);
		}
		//--> to avoid zombie state
		wait(&status);
		printf("final count = %d\n", ptr->cnt);
		//detach shm segment from the process
		shmdt(ptr);
		//perform control operation - mark seg to be destroyed
		shmctl(shmid, IPC_RMID, NULL);
	}
	return 0;
}

/*
	function prototype: int shmget(key_t key, size_t size, int shmflg); 
	function call: shmid = shmget(SHM_KEY, sizeof(shm_t), IPC_CREAT|0600);

	arg1 => SHM_KEY - defined in hexadecimal constant format
	arg2 => size of the shared memory segment
	arg3 => shmflg - IPC_CREAT - create a new segment with the access perms for the
	user process 0644 in octal format.
	if this flag is not used, then shmget() will find the segment associated with 
	key and check to see if the user has perms to access the segment.
	- return value : int
	on success: a valid shared memory identifier is returned.
	on error: -1 is returned. 

------------------------------------------------------------------------------*/

/*
	 function prototype: void *shmat(int shmid, const void *shmaddr, int shmflg);
	 function call: ptr = (shm_t*)shmat(shmid, NULL, 0);
	 
	 - shmat() attaches the shm segment identfied by "shmid" to the addr space of the
	 calling process. 
	arg1 => shmid
	arg2 => shmaddr = NULL - the attaching address is specified by shmaddr
	- if shmaddr is NULL, the system chooses a suitable (unused) page-aligned address
	 to attach the segment.
	arg3 => shmflg = 0
	- return value : void *
	on success: shmat() returns the addr of the attached shared memory segment
	on error: (void *)-1 is returned.
 ---------------------------------------------------------------------------------*/

/*
	 function prototype: int shmdt(const void *shmaddr);
	 function call: shmdt(ptr);
	 
	 - shmdt() detaches the shared memory segment located at the address  specified  by
	 shmaddr  from the address space of the calling process.

	 - return value : int
	 on success: shmdt() returns 0
	 on error : -1 is returned
----------------------------------------------------------------------------------*/

/*
	 function prototype: int shmctl(int shmid, int cmd, struct shmid_ds *buf);
	 - shmctl()  performs the control operation specified by "cmd" on the System V
	 shared memory segment whose identifier is given in "shmid".
	 function call: shmctl(shmid, IPC_RMID, NULL);
	 arg1 => shmid
	 arg2 => IPC_RMID - mark the segment to be destroyed
	 arg3 => NULL - when we pass this as NULL system does bydefault
----------------------------------------------------------------------------------*/
