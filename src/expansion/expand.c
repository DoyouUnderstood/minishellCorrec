/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:44:22 by alletond          #+#    #+#             */
/*   Updated: 2024/04/16 14:36:30 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include <stdio.h>
#include "ast.h"
#include "ft_error.h"
#include "word_list.h"

/** Handles the error for expand_word by freeing the necessary memory
 * and setting the error.
 * 
 * Returns NULL.
*/
static t_word_list	*handle_expand_word_error(t_word_list *result,
	t_word_list *builder, t_error *error)
{
	if (result)
		word_list_destroy(result);
	if (builder)
		word_list_destroy(builder);
	ft_error_set_system(error);
	return (NULL);
}

/** Continuation of expand_word to stay under 25 lines.
 * 
*/
t_word_list	*expand_word_2(t_word_list *words)
{
	t_word_list	*current;

	word_list_remove_empty(&words);
	current = words;
	while (current)
	{
		expand_unquote(current->word);
		current = current->next;
	}
	return (words);
}

/** Perform all expansions for the given word.
 * 
 * Expansions:
 * - Parameter expansion
 * - Word split
 * - Wildcard expansion
 * - Unquote
 * 
 * Returns the expanded list of words (NULL if empty),
 * or NULL on error.
*/
t_word_list	*expand_word(char *word, char *dir_path, t_hash_map *env,
	t_error *error)
{
	t_word_list	*result;
	t_word_list	*builder;
	t_word_list	*tmp;
	t_word_list	*current;

	builder = NULL;
	result = expand_params_split(word, env);
	if (!result)
		return (handle_expand_word_error(NULL, NULL, error));
	current = result;
	while (current)
	{
		tmp = expand_wildcard(dir_path, current->word);
		if (!tmp)
			return (handle_expand_word_error(result, builder, error));
		word_list_append(&builder, tmp);
		current = current->next;
	}
	word_list_destroy(result);
	result = builder;
	return (expand_word_2(result));
}

/** Perform all expansions for the words in the given list.
 * 
 * Expansions:
 * - Parameter expansion
 * - Word split
 * - Wildcard expansion
 * - Unquote
 * 
 * Returns the expanded list of words (NULL if empty),
 * or NULL on error.
*/
t_word_list	*expand_list(t_word_list *words, char *dir_path, t_hash_map *env,
	t_error *error)
{
	t_word_list	*result;
	t_word_list	*tmp;
	t_word_list	*current;

	result = NULL;
	current = words;
	while (current)
	{
		tmp = expand_word(current->word, dir_path, env, error);
		if (ft_has_error(error))
		{
			word_list_destroy(result);
			return (NULL);
		}
		word_list_append(&result, tmp);
		current = current->next;
	}
	word_list_remove_empty(&result);
	return (result);
}

/** Expands the argv in a command node.
 * 
 * Errors:
 * - System error.
 * 
 * Returns 0 on success, or -1 on error.
*/
int	expand_cmd_argv(t_ast_node *cmd_node, char *dir_path,
	t_hash_map *env)
{
	t_error		*error;
	t_word_list	*expanded_argv;

	if (!cmd_node->cmd_argv)
		return (0);
	error = ft_error_create();
	expanded_argv = expand_list(cmd_node->cmd_argv, dir_path, env, error);
	if (ft_has_error(error))
	{
		ft_error_destroy(error);
		return (-1);
	}
	ft_error_destroy(error);
	word_list_destroy(cmd_node->cmd_argv);
	cmd_node->cmd_argv = expanded_argv;
	return (0);
}
