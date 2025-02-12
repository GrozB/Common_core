#include "signals.h"
#include <unistd.h>

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\nminishell> ", 12);
}
