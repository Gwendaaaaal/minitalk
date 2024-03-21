/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:39:46 by gholloco          #+#    #+#             */
/*   Updated: 2024/03/21 12:13:03 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "./libft/libft.h"

int	g_sig_fallback = 1;

void	signal_handler(int signal)
{
	(void)signal;
	if (signal == SIGUSR2)
	{
		write(1, "Server stopped working...\n", 26);
		exit(1);
	}
	g_sig_fallback = 1;
}

void	signal_sender(int signal, int pid)
{
	int	tries;
	int	kill_val;

	tries = 0;
	kill_val = -1;
	while (kill_val == -1)
	{
		kill_val = kill(pid, signal);
		tries++;
		if (tries > 2)
		{
			write(1, "Unable to send signal. Enter a valid PID.\n", 42);
			exit(1);
		}
	}
}

int	binaire(int c, int pid)
{
	int	comp;

	comp = 0b10000000;
	while (comp != 0)
	{
		g_sig_fallback = 0;
		if ((comp & c) != 0)
			signal_sender(SIGUSR2, pid);
		else
			signal_sender(SIGUSR1, pid);
		while (!g_sig_fallback)
			pause();
		comp = comp >> 1;
	}
	return (0);
}

int	send_signal(char *string, int pid)
{
	int	i;

	i = 0;
	while (string[i])
		binaire(string[i++], pid);
	binaire('\0', pid);
	return (0);
}

int	main(int argc, char **argv)
{
	struct sigaction	act;

	if (argc != 3)
		return (0);
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_handler = &signal_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	send_signal(argv[2], ft_atoi(argv[1]));
	write(1, "Message has been sucessfully sent.\n", 35);
}
