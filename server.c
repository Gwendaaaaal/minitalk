/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:46:06 by gholloco          #+#    #+#             */
/*   Updated: 2024/03/21 12:45:51 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#define EXIT 0b1000000000

int	g_char = 0;

void	putstr_nl(char **message)
{
	ft_putstr_fd(*message, 1);
	ft_putstr_fd("\n", 1);
	*message = NULL;
}

char	*append_char(char *string, char c)
{
	char	*message;
	int		i;
	size_t	len_string;

	if (!string)
	{
		g_char = g_char | EXIT;
		return (NULL);
	}
	i = 0;
	len_string = ft_strlen(string);
	message = ft_calloc(sizeof(char), (len_string + 2));
	if (!message)
	{
		free(string);
		g_char = g_char | EXIT;
		return (NULL);
	}
	ft_strlcpy(message, string, len_string + 2);
	message[len_string] = c;
	free(string);
	return (message);
}

void	signal_handler(int signal, siginfo_t *info, void *ucontext)
{	
	static char	*message;
	static int	sig_received;

	(void)ucontext;
	if (!message)
		message = ft_strdup("");
	if (signal == SIGUSR1)
		g_char = g_char << 1;
	else if (signal == SIGUSR2)
		g_char = (g_char << 1) + 1;
	sig_received++;
	if (sig_received == 8)
	{
		if (!g_char && message)
			putstr_nl(&message);
		else
		{
			message = append_char(message, g_char);
			if (!message)
				return ((void)(kill(info->si_pid, SIGUSR2)));
		}
		g_char = 0;
		sig_received = 0;
	}
	kill(info->si_pid, SIGUSR1);
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

int	main(void)
{
	receive_signal();
	printf("My PID is : %d \n", getpid());
	while (!(g_char & EXIT))
		pause();
	printf("Server stopped");
}
