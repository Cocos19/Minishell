/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_temp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:34:18 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/14 14:47:51 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list_infos(t_token *lst)
{
	t_token *temp;

	temp = lst;
	while (temp)
	{
		if (temp->value)
			printf("token is:%s\n", temp->value);
		temp = temp->next;
	}
}

void	print_fd_content(int fd)
{
	char *str;

	str = get_next_line(fd, 10);
	while (str)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd, 10);
	}
	close(fd);
}

void	init_some_locales_variables(t_shell *shell)
{
	add_new_locale_variable(shell, ft_strdup("var2"), ft_strdup("second locale variable"));
	add_new_locale_variable(shell, ft_strdup("var3"), ft_strdup("third locale variable"));
	add_new_locale_variable(shell, ft_strdup("var4"), ft_strdup("fourth locale variable"));
	add_new_locale_variable(shell, ft_strdup("var5"), ft_strdup("fifth locale variable"));
}

// parsing

// si < ou << enregistre les input en ecrasant toujours le dernier
// si > ou >> cree les files avec open si necessaire mais n'ecrira dans le dernier que s'il y a une command
// enregistre les implentations de variables mais ne les implementera que s'il n'y a pas de command et pas d'autres command dans le pipe
// tous les autres cas sont des arguments
// si | ouvre un pipe enfant

// expand les variables et suppression des quotes (si rien entre les quotes, l'argument est une string vide)

// le premier argument qui n'est pas un de ces cas de figure sera considere comme la command
// les autres suivent
// si pas d'autres argument, on prend le dernier input comme second argument

// s'il y a des argument, on lance execve
// si pas on verifie s'il y a des implementation de variable et on les enregistre dans l'ordre

// base:
// Si syntax error, on arrete la recolte de token, on free et on rend le prompt
// if ' ' pas entre quotes on zappe les espaces. Si on est en train de recuperer un token, on le recupere puis on zappe.
// if '\0' si on est en train de recuperer un token, on le recupere. Sinon fin de la collecte d'arguments.
// if '<' ou '<<' pas entre quotes, le prochain token va dans la variable input et ecrase le contenu. Si on est en train de recuperer un token, on le recupere.
// if '>' ou '>>' pas entre quotes, le prochain token cree un fichier va dans la variable output et ecrase le contenu. Si on est en train de recuperer un token, on le recupere.
// if '=' pas entre quotes on finit de recuperer le token et on le garde dans une chaine listee de variable a implementer si les conditions sont reunies a la fin. Si pas encore d'arg, on stock, si deja un arg, ca devient juste un arg. Si on rencontre un arg plus tard, on free tout ce qui ete stocke
// if '\' ou '\"' pas entre quotes on recupere le token: il ira soit comme input, comme output, comme prochaine variable, comme argument
// if '*' pas entre quotes on finit de recuperer le token et on expand direct le * car le result va s'inserer dans la liste d'argument: le mieux est de recuper un array d'argument et de join le tableau d'args
// if '|' pas entre quotes on cloture le pipe et on ouvre le suivant. Si on est en train de recuperer un token, on le recupere.

// A la fin d'un pipe, qu'il se cloture par un '\0' ou un '|', Si on attendais un input ou un output, on affiche une syntax error near unexpected token 'newline' ou '|' // trouver un moyen de savoir qu'on attend un input ou output. Si on attend une variable a implenter, elle est egale a une string vide

// Priorité d'execution des inputs:

// Si argv[1] ou +, les args ont toujours la priorité
// Sinon le dernier argument entre l'output du node precedent, les inputs ou les heredoc.

//le heredoc Expand seulement le dollar
// faire une liste d'input avec nom, le fd et une variable s'il est open ou deja close

