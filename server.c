/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:46:06 by gholloco          #+#    #+#             */
/*   Updated: 2024/01/15 21:20:29 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int	g_binary = 128;

void	signal_handler(int signal, siginfo_t *info, void *ucontext)
{	
	printf("%d\n", signal);
	printf("%d\n", info->si_pid);
	if (kill(info->si_pid, signal) == -1)
		printf("kill failed\n");
}

void	receive_signal(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);	
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &signal_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}

int main(void)
{
	receive_signal();
	printf("My PID is : %d \n", getpid());
	while (1)
		;
}
