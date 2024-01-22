# Minishell
FAIRE mettre a jour la version non interactive

<!-- MODIFIER get_next_line (multiple fd) -->
<!-- MODIFIER le heredoc pour le faire sans fork? -->
<!-- MODIFIER tout les signaux pour faire des fonctions avec sigaction? -->
<!-- MODIFIER enlever les exit et ne pas fork pour les builtin -->

<!-- - PROBLEME avec ft_get_command de la libft (je crois c'est le extern g_exit_status qu'il aime pas) -->

tests qui ne marchent pas :

- echo $hola* //faut juste, dans l'execution, mettre le bloc wildcards apres celui d'expand mais je crois que ca posais prblm sur un cas c'est pour ca qu'on l'a mit dans cet ordre je crois

- utiliser l'env de minishell pour un shell dans un shell ? 
- voir sans env command : valgrind --suppressions=.readline_suppressions.supp --trace-children=yes env -i ./minishell



A FAIRE: check les retour dexit status pour les tests

QUESTION: extern environ dans do_builtin_or_execve.c , t'es sur que ya besoin dans lexec et pas mieux de trouver le path dans notre env a nous ?

AVANT DE PUSH:

0: check les mallocs entre les pipes manuellement

1: faire les tests de pleins de cas (ceux dans le pdf) avec funcheck et valgrind
2: remove les test
3: refaire le makefile
4: faire un dossier bonus pour les wildcards
5: push dans le vrai repos minishell de 42