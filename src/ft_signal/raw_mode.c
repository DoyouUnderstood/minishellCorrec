/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:16:37 by alletond          #+#    #+#             */
/*   Updated: 2024/04/16 17:47:33 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_signal.h"
#include <readline/readline.h>
#include <signal.h>
#include <termios.h>
#include "libft.h"

void	enable_raw_mode(void)
{
	struct termios	tp;

	tcgetattr(STDIN_FILENO, &tp);
	tp.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp);
}

void	disable_raw_mode(void)
{
	struct termios	tp;

	tcgetattr(STDIN_FILENO, &tp);
	tp.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp);
}
