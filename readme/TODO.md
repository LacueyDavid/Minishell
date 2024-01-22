# Minishell
FAIRE mettre a jour la version non interactive

<!-- MODIFIER get_next_line (multiple fd) -->
<!-- MODIFIER le heredoc pour le faire sans fork? -->
<!-- MODIFIER tout les signaux pour faire des fonctions avec sigaction? -->
<!-- MODIFIER enlever les exit et ne pas fork pour les builtin -->

<!-- - PROBLEME avec ft_get_command de la libft (je crois c'est le extern g_exit_status qu'il aime pas) -->

tests qui ne marchent pas :

- echo $hola* //faut juste, dans l'execution, mettre le bloc wildcards apres celui d'expand mais je crois que ca posais prblm sur un cas c'est pour ca qu'on l'a mit dans cet ordre je crois

- export_utils.c recoder realloc


A FAIRE: check les retour dexit status pour les tests

QUESTION: extern environ dans do_builtin_or_execve.c , t'es sur que ya besoin dans lexec et pas mieux de trouver le path dans notre env a nous ?
