/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:56:30 by ael-asri          #+#    #+#             */
/*   Updated: 2022/09/06 21:47:39 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	set_count(char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] == c)
		i++;
	count++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
		{
			count++;
		}
		i++;
	}
	return (count);
}

static char	**ft_del(char **t, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(t[i]);
		i++;
	}
	free(t);
	return (NULL);
}

int	check_only_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

static char	**chek_and_fill(t_game *my_game, char **t, char *s, char c)
{
	int	i;
	int	count;
	int	temp;
	int	p_valid=0;//, lock = 0;

	i = 0;
	count = 0;
	while (s[i])
	{
		temp = i;
		if (s[i] == c && p_valid < 6)
		{
			// printf("hi %d\n", i);
			i++;
			continue ;
		}
		else if (s[i] == c && p_valid >= 6/* && !lock*/)
		{
			// while (s[i] == c)
				i+=2;
		//	lock = 1;
		}
		// else if (s[i] == c && p_valid == 6 && lock)
		// {
		// 	i++;
		// }
		while (s[i] != c && s[i])
			i++;
		// if (check_only_spaces(ft_substr(s, temp, i - temp)))
		// {
			t[count] = ft_substr(s, temp, i - temp);
			if (t[count] == NULL)
				return (ft_del(t, count));
			// if (t[count][0] == 'C' && t[count][1] == ' ')
			if (!ft_strncmp(t[count], "NO ", 3) || !ft_strncmp(t[count], "SO ", 3) || !ft_strncmp(t[count], "WE ", 3) || !ft_strncmp(t[count], "EA ", 3) || !ft_strncmp(t[count], "F ", 2) || !ft_strncmp(t[count], "C ", 2))
			{
				if (p_valid == 5)
				{
					while (s[i] == c)
						i++;
				}
				p_valid++;
			}
		//	printf("t[%d] -%s-\n", count, t[count]);
			if (!ft_strncmp(t[count], "NO ", 3))
			{
				// my_game->no_path = ft_sstrcpy(my_game->no_path, t[count]);
				my_game->no_path = ft_substr(t[count], 3, ft_strlen(t[count]));
				my_game->is_no = 1;
			}
			else if (!ft_strncmp(t[count], "SO ", 3))
			{
				// my_game->so_path = ft_sstrcpy(my_game->so_path, t[count]);
				my_game->so_path = ft_substr(t[count], 3, ft_strlen(t[count]));
				my_game->is_so = 1;
			}
			else if (!ft_strncmp(t[count], "WE ", 3))
			{
				// my_game->we_path = ft_sstrcpy(my_game->we_path, t[count]);
				my_game->we_path = ft_substr(t[count], 3, ft_strlen(t[count]));
				my_game->is_we = 1;
			}
			else if (!ft_strncmp(t[count], "EA ", 3))
			{
				// my_game->ea_path = ft_sstrcpy(my_game->ea_path, t[count]);
				my_game->ea_path = ft_substr(t[count], 3, ft_strlen(t[count]));
				my_game->is_ea = 1;
			}
			else if (!ft_strncmp(t[count], "F ", 2))
			{
				// ft_sstrcpy(my_game->no_path, t[count]);
				my_game->f_path = ft_substr(t[count], 2, ft_strlen(t[count]));
				my_game->is_f = 1;
			}
			else if (!ft_strncmp(t[count], "C ", 2))
			{
				// ft_sstrcpy(my_game->no_path, t[count]);
				my_game->c_path = ft_substr(t[count], 2, ft_strlen(t[count]));
				my_game->is_c = 1;
			}
			count++;
		// }
	}
	// count++;
	t[count] = 0;
	if (my_game->is_no != 1 || my_game->is_so != 1 || my_game->is_we != 1 || my_game->is_ea != 1 || my_game->is_f != 1 || my_game->is_c != 1)
	{
		printf("missing pathes or colors!\n");
		exit(1);
	}
	printf("no %s\n", my_game->no_path);
	printf("so %s\n", my_game->so_path);
	printf("we %s\n", my_game->we_path);
	printf("ea %s\n", my_game->ea_path);
	printf("f %s\n", my_game->f_path);
	printf("c %s\n", my_game->c_path);
	// for(int i=0;t[i];i++)
	// 	printf("~%s+\n", t[i]);
	// exit(1);
	return (t);
}

char	**ft_split(t_game *my_game, char *s, char c)
{
	char	**t;
	int		count;

	if (s == 0)
		return (0);
	count = set_count(s, c);
	t = (char **)malloc(sizeof(char *) * (count + 1));
	if (t == NULL)
		return (0);
	return (chek_and_fill(my_game, t, s, c));
}
