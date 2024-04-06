/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthaler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 10:39:03 by cthaler           #+#    #+#             */
/*   Updated: 2023/12/03 10:39:05 by cthaler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_PIPE_SIZE 65535
# define PATH_MAX 4096
# include "libft/libft.h"
# include <limits.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <errno.h>
# include <sys/ioctl.h>
# define CMD 1
# define PIPE 2
# define IN 3
# define OUT 4
# define HEREDOC 5
# define APPEND 6
# define ARG 7
# define FILE 8
# define CMD2 9
# define HEREDOC_Q 10
# define DEFAULT 0

extern int	g_sig;

typedef struct s_list
{
	char			*s;
	int				token;
	int				fd;
	struct s_list	*next;
}					t_list;
typedef struct s_cmd
{
	int				index;
	int				token;
	char			**bin;
	pid_t			pid;
	t_list			*redir;
	struct s_cmd	*next;
}					t_cmd;
typedef struct s_msd
{
	char			prompt[12];
	char			*line;
	char			*line_history;
	char			*heredoc;
	char			**path;
	char			**envp;
	char			**hist;
	t_list			*arg_list;
	t_list			**redir_head;
	t_cmd			*cmds;
	t_cmd			*cmds_head;
	int				*pids;
	int				iter;
	int				shlvl;
	int				redir_i;
	int				quit;
	int				exit_code;
	int				status;
	int				nr_cmds;
	int				pipe_fd[2];
	int				fd_here;
	int				def_in;
	int				def_out;
	int				fd_in;
	int				fd_out;
	int				red_in;
	int				red_out;
	int				execute;
}					t_msd;
//builtins
int			pwd(void);
void		cd(t_msd *data);
int			env(char **env_a);
int			echo(char **args);
int			export(t_msd *data, char **args);
void		unset(t_msd *data);
void		ft_exit(t_msd *data, char **bin);
void		print_env(char **env);
int			is_in_env(char **env, char *arg);
//init helper funcs
char		*get_env(char **env_a, char *key);
int			set_env(char **env_a, char *key, char *s);
char		**init_env_arr(char **envp, char *s);
int			env_pattern(char c, int i);
char		*get_env_value(char **env_a, char *s);
int			set_env_value(char **env_a, char *key, char *value);
void		free_arr(char **arr, int i);
void		free_if(char *s);
int			add_str(t_msd *data, char *s, int i);
char		**sort_env(char **env);
//linked list functions with str
t_list		*ft_strlstnew(char *content);
void		ft_strlst_back(t_list **lst, t_list *node);
void		free_list(t_list **a);
//lexing + parsing
int			lex_it(char *s, t_msd *data, int check);
int			tokenize(t_list **args);
int			closed_quotes(char *s, int flag);
char		*remove_quotes(char *s);
char		*insert_env(char *s, t_msd *data, int i);
char		*env_heredoc(char *s, t_msd *data, int i);
int			pattern(char c, int flag);
int			check_syntax(t_msd *data, int l_tkn, int ret);
int			cmd_table(t_list *lst, t_cmd **cmds, t_msd *data, int index);
t_list		*get_redir(t_list *lst, t_msd *data);
int			is_redir(int token);
int			count_redirs(t_list *lst, int flag);
int			parse_hell(t_msd *data);
int			alloc_redir_head(t_msd *data);
int			no_dollar(char *s);
//utils
void		free_arr(char **arr, int i);
int			arr_len(char **arr);
void		free_cmds(t_cmd **cmds);
void		clear_round(t_msd *data);
int			close_if(int fd);
void		free_redirs(t_msd *data);
long long	ft_atoll(const char *nptr);
char		*ft_lltoa(long long nr);
//exec
void		executor(t_msd *data);
void		closeline(t_msd *data);
char		*get_binary_path(t_msd *data, char *bin, int i);
void		launch_executable(t_msd *data);
void		execancel(t_msd *data, int code, char *trigger, char *msg);
void		here_and_now(t_msd *data, t_list *redir);
void		init_pids(t_msd *data);
void		loop_child(t_msd *data);
void		redirect(t_msd *data, t_list *redir);
//signal
void		ctrl_c(__attribute__((unused)) int signum);
//void		ctrl_c2(__attribute__((unused)) int signum);
void		ctrl_c_heredoc(__attribute__((unused)) int signum);
//init
void		init_data(t_msd *data, char **envp);
void		get_path(t_msd *data, char **envp);
char		**init_env_arr(char **envp, char *s);
char		*heredoc_filename(void);
void		protecc(int res, t_msd *data, int err);
void		protecc_child(int res, t_msd *data, int err);
//int			ft_launch_minishell(char *arg);
#endif
