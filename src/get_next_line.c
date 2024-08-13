/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:16:37 by vcaratti          #+#    #+#             */
/*   Updated: 2024/07/30 11:09:34 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
char	*ft_strchr(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	if (c == '\0')
		return (&str[ft_strlen(str)]);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	return (0);
}

char	*trim_first_line(char *str)
{
	int		i;
	
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;

}

char	*read_concat(int fd, char *buffer, b_size)
{
	char	*read_buf;
	int		read_ret;

	read_ret = 1;
	read_buf = malloc(sizeof(char) * b_size + 1);
	if (read_buf == NULL)
		return (NULL);
	while (read_ret > 0 && !ft_strchr(buffer, '\n'))
	{
		read_ret = read(fd, read_buf, b_size);
		if (read_ret < 0)
			return (free(read_buff), NULL);
		read_buf[read_ret] = 0;
		buffer = ft_strjoin(buffer, read_buf);
	}
	return (free(read_buf), buffer);
}

char	*get_next_line(int fd, int b_size)
{
	static char	*buffer;
	char		*ret_line;
	
	buffer = read_concat(fd, buffer, b_size);
	if (buffer == NULL)
		return (NULL);
	ret_line = get_first_line(buffer);
	buffer = trim_first_line(buffer);
	return (ret_line);
}
