/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_cd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:14:30 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/05 14:00:30 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//home marche toujours si HOME est unset
//cd sqns arg renvoie toujours vers HOME meme si unset
// ./+nomdudossier descend dans le directory
// ..remonte le directory (si on est dans le root il ne faut pas remonter)
// cd - si old PWD est pas set, declare bash: cd: OLDPWD not set
// idem si on a pas encore change de directory, OLDPWD est pas encore set
// ~ si gere avec, il faut gere ~/+dossier dans le dossier home
// pas oublier d'update le OLDPWD et de changer PWD a chauque fois
// utilise pas le result du pipe
