#include "build.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

int	ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*c_s1;
	unsigned char	*c_s2;

	c_s1 = (unsigned char *) s1;
	c_s2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1 && c_s1[i] == c_s2[i] && c_s1[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	is_white_space(char c)
{
	return (c == ' ' || c == '\t'
		|| c == '\n' || c == '\v'
		|| c == '\f' || c == '\r');
}

static int	get_result(long long int num, long long int sign)
{
	if (num <= 2147483647 && num >= -2147483648)
		return ((int) num);
	else if (sign == 1)
		return (-1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	ft_atoi(const char *str)
{
	int				i;
	long long int	num;
	long long int	sign;

	if (str == NULL)
		return (0);
	num = 0;
	sign = 1;
	i = 0;
	while (str[i] != '\0' && is_white_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0' && ft_isdigit(str[i]))
		num = num * 10 + (str[i++] - 48);
	num *= sign;
	return (get_result(num, sign));
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	while (*s != '\0')
		ft_putchar_fd(*s++, fd);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_s;
	size_t	i;

	if (s == NULL || (unsigned int)ft_strlen(s) <= start)
		len = 0;
	new_s = malloc((len + 1) * sizeof(char));
	if (new_s == NULL)
		return (new_s);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		new_s[i] = s[start + i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	size;
	char	*ptr_new_s;
	char	*ptr_old_s;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_s = malloc(size);
	if (new_s == NULL)
		return (NULL);
	ptr_new_s = new_s;
	ptr_old_s = (char *)s1;
	while (*ptr_old_s != '\0')
		*ptr_new_s++ = *ptr_old_s++;
	ptr_old_s = (char *)s2;
	while (*ptr_old_s != '\0')
		*ptr_new_s++ = *ptr_old_s++;
	*ptr_new_s = '\0';
	return (new_s);
}