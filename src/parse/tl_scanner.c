/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_scanner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:49:07 by alletond          #+#    #+#             */
/*   Updated: 2024/03/26 17:49:07 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tl_scanner.h"

#include <stdbool.h>
#include <stdlib.h>

#include "token.h"
#include "token_list.h"

void	tl_scanner_init(t_tl_scanner *scanner, t_token_list *token_list)
{
	scanner->current_node = token_list;
}

bool	tl_scanner_is_at_end(t_tl_scanner *scanner)
{
	return (!scanner->current_node
		|| scanner->current_node->token->type == T_EOF);
}
