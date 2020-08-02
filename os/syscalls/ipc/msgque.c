/* Program to demonstrate message queue mechanism */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MQ_KEY 0x2405

typedef struct mymsg
{
	long type;
	char str[20];
}mymsg_t;

int main()
{
	int ret, mqid, status;

	mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
	if(mqid < 0)
	{
		perror("msgget() failed");
		_exit(1);
	}

	ret = fork();
	if(ret==0)
	{	// child process -- sender
		mymsg_t m1, m4;
		printf("child : enter message : ");
		scanf("%s", m1.str);
		m1.type = 101;
		msgsnd(mqid, &m1, sizeof(m1), 0);
		
		printf("child waiting for the message ...\n");
		msgrcv(mqid, &m4, sizeof(m4), 202, 0);
		printf("child received : %s\n", m4.str);
	}
	else
	{	// parent process -- receiver
		mymsg_t m2, m3;
		printf("parent waiting for the message ...\n");
		msgrcv(mqid, &m2, sizeof(m2), 101, 0);
		printf("parent received : %s\n", m2.str);
		
		printf("parent : enter message : ");
		scanf("%s", m3.str);
		m3.type = 202;
		msgsnd(mqid, &m3, sizeof(m3), 0);
	
		wait(&status);

		msgctl(mqid, IPC_RMID, NULL);
	}
	return 0;
}

/*
	function prototype: int msgget(key_t key, int msgflg);
	function call: mqid = msgget(MQ_KEY, IPC_CREAT | 0600);

	- the msgget() system call returns the System V message queue identifier associated
	with the value of the key argument.
	- a new message queue is created if  key has  the  value  IPC_PRIVATE or key isn't
	IPC_PRIVATE, no message queue with the given key key exists, and IPC_CREAT is
	specified in msgflg.

	arg1 => MQ_KEY - user defined key which is of type hex constant
	arg2 => msgflg - IPC_CREAT - create message queue object and assign perms
	0644 in octal format
	------------------------------------------------------------------------------*/

/*
	 int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
   ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
   
	 - The  msgsnd() and msgrcv() system calls are used, respectively, to send messages
	 to, and receive messages from, a System V message queue.
	 - The calling process must have write permission on the message queue in order
	 to send a message, and read permission to receive a message.
   - The "msgp" argument is a pointer to a caller-defined structure of the following
	 general form:
	 struct msgbuf {
      	long mtype;       //message type, must be > 0
        char mtext[];    //message data
   };
	 - The mtext field is an array (or other structure) whose size is specified by
	 "msgsz", a nonnegative integer value.
	 - Messages of zero length (i.e., no mtext field) are permitted.
	 - The "mtype" field must have a strictly positive integer value. This value can
	 be used by the receiving process for message selection.
	 
	 - The msgsnd() system call appends a copy of the message pointed to by msgp to the
	 message queue whose identifier is specified by msqid.
	 - The msgrcv() system call removes a message from the queue specified by msqid and
	 places it in the buffer pointed to by msgp.
	 ------------------------------------------------------------------------------*/

/*
	 function prototype: int msgctl(int msqid, int cmd, struct msqid_ds *buf);
	 function call: msgctl(mqid, IPC_RMID, NULL);
		
	 - msgctl() performs the control operation specified by cmd on the System V message
	 queue with identifier msqid.
	 arg1 => int message queue id
	 arg2 => IPC_RMID - immediately remove the message queue, awakening all waiting
	 reader and writer processes.
	 arg3 => NULL - let the left this job for system - default actions 
	--------------------------------------------------------------------------------*/
