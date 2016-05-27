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

	elem.mtype=2;
	printf ("Podaj wyraz: ");
	scanf ("%s",elem.mvalue);

	msgid = msgget (123, IPC_CREAT|0600);
	if (msgid == -1)
	{
		perror ("msgget() failure");
		exit(1);
	}
	else
	{
		if (msgsnd(msgid, &elem, sizeof(elem.mvalue), IPC_NOWAIT) == -1)
		{
			perror ("msgsnd() failure");
			exit(1);
		}
	}
}
