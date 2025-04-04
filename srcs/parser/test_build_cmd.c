#include "../../includes/minishell.h"

// New structure to hold value + type
typedef struct s_arg
{
	char			*value;
	t_token_type	type;
}					t_arg;

t_cmd_list	*init_cmd_list(void)
{
	t_cmd_list	*list;

	list = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->count = 0;
	return (list);
}

static t_cmd	*create_cmd_node(void)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->argc = 0;
	node->next = NULL;
	return (node);
}

static void	append_cmd(t_cmd_list *list, t_cmd *new_node)
{
	t_cmd	*temp;

	if (!list->head)
		list->head = new_node;
	else
	{
		temp = list->head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
	list->count++;
}

static int	skip_redirects(t_token **token)
{
	if ((*token)->type == REDIRECT_IN || (*token)->type == REDIRECT_OUT
		|| (*token)->type == HEREDOC || (*token)->type == APPEND)
	{
		*token = (*token)->next;
		if (*token)
			*token = (*token)->next;
		return (1);
	}
	return (0);
}

static int	count_args(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
			count++;
		skip_redirects(&token);
		if (token && token->type != PIPE)
			token = token->next;
	}
	return (count);
}

static void	assign_arg(t_arg *arg, t_token *token, int *found_cmd)
{
	arg->value = ft_strdup(token->value);
	if (*found_cmd == 0)
	{
		arg->type = COMMAND;
		*found_cmd = 1;
	}
	else
		arg->type = ARGS;
}

static void	populate_args(t_arg *args, t_token **token, int *argc)
{
	t_token	*curr;
	int		found_command;
	int		i;

	curr = *token;
	found_command = 0;
	i = 0;
	while (curr && curr->type != PIPE)
	{
		if (skip_redirects(&curr))
			continue ;
		if (curr && curr->type == WORD)
		{
			assign_arg(&args[i], curr, &found_command);
			i++;
		}
		if (curr)
			curr = curr->next;
	}
	*argc = i;
	while (*token && (*token)->type != PIPE)
		*token = (*token)->next;
}

t_arg	*fill_args(t_token **token, int *argc)
{
	t_token	*curr;
	t_arg	*args;
	int		count;

	curr = *token;
	count = count_args(curr);
	args = malloc(sizeof(t_arg) * count);
	if (!args)
		return (NULL);
	populate_args(args, token, argc);
	return (args);
}

t_cmd_list	*build_cmd_list(t_token *token)
{
	t_cmd_list	*cmd_list;
	t_cmd		*cmd;

	cmd_list = init_cmd_list();
	if (!cmd_list)
		return (NULL);
	while (token)
	{
		cmd = create_cmd_node();
		if (!cmd)
			return (NULL);
		cmd->args = fill_args(&token, &cmd->argc);
		append_cmd(cmd_list, cmd);
		if (token && token->type == PIPE)
			token = token->next;
	}
	return (cmd_list);
}
