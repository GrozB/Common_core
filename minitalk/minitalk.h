#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"

// Function prototypes
void send_char(pid_t pid, char c);
void handle_signal(int sig);

#endif
