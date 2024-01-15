#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int	g_sig_fallback = 1;

void	signal_handler()
{
	printf("ON RECOIT UN SIGNAL\n");
	g_sig_fallback = 1;
}

int	binaire(int c, int pid)
{
	int	comp = 128;

	printf("%c (%d) is : \n", c, c);
	while (comp != 0)
	{
		g_sig_fallback = 0;
		if ((comp & c) != 0)
		{
			kill(pid, SIGUSR2);		
			printf("1\n");
		}
		else
		{
			kill(pid, SIGUSR1);
			printf("0\n");
		}
		while(!g_sig_fallback)
			;
			// printf("on est stuck ici");
		comp = comp >> 1;
	}
	printf("\n");
	return (0);
}

int	send_signal(char* string, int pid)
{
	int	i;

	i = 0;
	printf("string : %s\npid : %d \n", string, pid);
	while (string[i])
		binaire(string[i++], pid);
	return (0);
}

int	main(int argc, char** argv)
{

	struct sigaction	act;

	if (argc != 3)
		return (0);

	printf("Client pid is : %d\n", getpid());
	sigemptyset(&act.sa_mask);	
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &signal_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	
	send_signal(argv[1], atoi(argv[2]));
}
