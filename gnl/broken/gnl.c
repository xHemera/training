/*
Etapes de réparation détaillées pour gnl.c :

1. ft_strchr (ligne 4) :
	- Problème : while (s[i] != c) ne vérifie pas la fin de chaîne, risque de boucle infinie si c n'est pas présent.
	- Correction : remplacer par while (s[i] && s[i] != c) pour s'arrêter sur '\0'.
	- Pourquoi : Évite de lire hors de la chaîne et boucle infinie.

2. ft_memcpy (ligne 14) :
	- Problème : while (--n > 0) ne copie pas le premier octet et copie à l'envers, ce qui n'est pas conforme à memcpy.
	- Correction : utiliser un compteur croissant (int i = 0; i < n; i++) pour copier chaque octet dans l'ordre.
	- Pourquoi : memcpy doit copier de 0 à n-1 dans l'ordre.

3. ft_strlen (ligne 22) :
	- Problème : fonctionne mais peut être simplifiée avec un compteur i et une boucle while (s[i]).
	- Correction : remplacer par la version avec compteur i pour plus de clarté et cohérence.
	- Pourquoi : Plus lisible et standard.

4. str_append_mem (ligne 30) :
	- Problème : si *s1 == NULL, ft_strlen(*s1) provoque un crash. De plus, ft_memcpy(tmp, *s1, size1) doit être conditionné à *s1 non NULL.
	- Correction : tester *s1 avant d'appeler ft_strlen et ft_memcpy.
	- Pourquoi : Évite les segfaults et gère le cas où s1 est vide.

5. ft_memmove (ligne 46) :
	- Problème : la gestion du chevauchement mémoire est incorrecte, la copie doit se faire à l'envers si dest > src.
	- Correction : copier à l'envers (i--) si dest > src, ou à l'endroit si dest < src.
	- Pourquoi : Respecte le comportement standard de memmove pour les zones qui se chevauchent.

6. get_next_line (ligne 58) :
	- Problèmes :
	  a) tmp n'est pas mis à jour dans la boucle après lecture.
	  b) b n'est pas vidé après extraction de la ligne.
	  c) la gestion de la fin de fichier et du déplacement du buffer n'est pas correcte.
	- Corrections :
	  a) Mettre à jour tmp après chaque lecture.
	  b) Utiliser ft_memmove pour déplacer le buffer après extraction de la ligne.
	  c) Gérer la fin de fichier (read_ret == 0) et libérer ret si besoin.
	- Pourquoi : Permet d'extraire correctement chaque ligne, gérer le buffer et éviter les erreurs de lecture.

Chaque modification est nécessaire pour :
- Éviter les crashs et boucles infinies.
- Respecter le comportement standard des fonctions C.
- Gérer correctement la mémoire et les cas limites.
- Assurer la robustesse et la fiabilité de get_next_line.
*/
#include "broken_gnl.h"

char	*ft_strchr(char *s, int c)
{
	int	i = 0;
	while (s[i] != c)
		i++;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	while (--n > 0)
		((char *)dest)[n - 1] = ((char *)src)[n - 1];
	return (dest);
}

size_t	ft_strlen(char *s)
{
	size_t	ret = 0;
	while (*s)
	{
		s++;
		ret++;
	}
	return (ret);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1 = ft_strlen(*s1);
	char	*tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (0);
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp [size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest > src)
		return (ft_memcpy(dest, src, n));
	else if (dest == src)
		return (dest);
	size_t	i = ft_strlen((char *)src) - 1;
	while (i >= 0)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i--;
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1] = "";
	char	*ret = NULL;

	char	*tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if (!str_append_str(&ret, b))
			return (NULL);
		int	read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
			return (NULL);
		b[read_ret] = 0;
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}
