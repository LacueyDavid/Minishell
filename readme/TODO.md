# Minishell
FAIRE mettre a jour la version non interactive

<!-- MODIFIER get_next_line (multiple fd) -->
<!-- MODIFIER le heredoc pour le faire sans fork? -->
<!-- MODIFIER tout les signaux pour faire des fonctions avec sigaction? -->
<!-- MODIFIER enlever les exit et ne pas fork pour les builtin -->

- env qui copie pas l'env du Wesh actuel (il copie celui du bash), on sort pas notre env a la fin (je sais pas si c'est un prblm mais en ca incremente pas shlvl quand on wesh dans un wesh) //akip c'est normal

- PROBLEME avec ft_get_command de la libft (je crois c'est le extern exit_status qu'il aime pas)

tests qui ne marchent pas :

- echo $hola* marche pas
- echo ""$HOME*
- echo "$DONTEXIST" "Makefile" dont work (echo le pb) //je crois ca marche j'arrive pas a pas le faire rater


A FAIRE: check les retour dexit status pour les tests
