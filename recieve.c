#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct buf_elem {
	long mtype;
	char mvalue[50];
};

int main()
{
	int msgid;
	struct buf_elem elem;
	
	int fd[2];
	pid_t pid;
		
	pipe(fd);
		
	if ((pid=fork()) == -1 ){
		perror("fork failure");
		exit(1);
		}
	if (pid == 0)
	{
		dup2(fd[1],1);
		close(fd[1]);
		close(fd[0]);
		execlp("date","date","+%w",NULL);
		}
	else
	{
		wait(NULL);
		char readbuffer[1];
			
		dup2(fd[0],0);
        close(fd[1]);
        close(fd[0]);
		fread(readbuffer,1,1,stdin);
		msgid = msgget (123, 0600);


		if (readbuffer[0] >= '5' || readbuffer[0]=='0'){

		if (msgrcv(msgid, &elem, sizeof(elem.mvalue), 2, IPC_NOWAIT) == -1)
		{
			perror("msgrcv() failure");
			exit(1);	
		}
		if (isalpha(elem.mvalue[0]))
			printf("%s\n",elem.mvalue);
		else
			printf("niepoprawny\n");

		if (msgctl(msgid, IPC_RMID, NULL) == -1)
		{
			perror("msgctl() failure");
			exit(1);
		}
		
		}else
			printf("Nie ma weekendu!\n");
	

return 0;	
}
}
