/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:48:57 by alletond          #+#    #+#             */
/*   Updated: 2024/03/26 18:03:16 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "parse_internal.h"

#include <stdlib.h>

#include "ft_error.h"
#include "heredoc_list.h"
#include "tl_scanner.h"

/** Creates a new parent pipeline node with an existing node as left,
 * and a new node as right.
 * 
 * Returns the new node, or NULL on error.
*/

static t_ast_node	*extend_pipeline(t_tl_scanner *scanner, t_ast_node *left,
	t_heredoc_list **heredocs, t_error *error)
{
	t_ast_node	*node;
	t_ast_node	*right;

	right = parse_full_cmd(scanner, heredocs, error);
	if (ft_has_error(error))
		return (NULL);
	node = ast_create_binary(AST_PIPE, left, right);
	if (!node)
	{
		ft_error_set_system(error);
		ast_destroy(right);
	}
	return (node);
}

/** Parse a pipeline node.
 * 
 * Returns the new node, or NULL on error.
*/
t_ast_node	*parse_pipeline(t_tl_scanner *scanner, t_heredoc_list **heredocs,
	t_error *error)
{
	t_ast_node	*node;
	t_ast_node	*tmp_node;

	node = parse_full_cmd(scanner, heredocs, error);
	if (ft_has_error(error))
		return (NULL);
	while (tl_scanner_match_type(scanner, T_PIPE))
	{
		tmp_node = extend_pipeline(scanner, node, heredocs, error);
		if (ft_has_error(error))
		{
			ast_destroy(node);
			return (NULL);
		}
		node = tmp_node;
	}
	return (node);
}
