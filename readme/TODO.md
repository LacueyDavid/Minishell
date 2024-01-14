# Minishell
FAIRE mettre a jour la version non interactive

<!-- MODIFIER get_next_line (multiple fd) -->
<!-- MODIFIER le heredoc pour le faire sans fork? -->
<!-- MODIFIER tout les signaux pour faire des fonctions avec sigaction? -->
<!-- MODIFIER enlever les exit et ne pas fork pour les builtin -->

env qui copie pas l'env du Wesh actuel (il copie celui du bash), on sort pas notre env a la fin (je sais pas si c'est un prblm mais en ca incremente pas shlvl quand on wesh dans un wesh)
MODIFIER mettre un path pour le .minishell_history sinon quand tu cd ca creer le fichier a chaque fois dans le current dir

PROBLEME avec ft_get_command de la libft (je crois c'est le extern exit_status qu'il aime pas)

TEST A FAIRE SI MOTIVÉ
test gnl avec plus de MAPSIZE fd
tests qui ne marchent pas :

- echo "        " | cat -e (surement un probleme dans le builtin echo?).
- dans les exports il ne doit pas y avoir de chiffre. (4=a paspossible, en gros
  tout ce qui nest pas une lettre pas possible)
- cd dir/dir marche pas
- echo $hola* marche pas
- echo ""$HOME*
- echo "$DONTEXIST" "Makefile" dont work (echo le pb)
- unset marche juste pas
- export ok puis export ok=a, le nouveau ok remplace pas lancien
- cd . et cd .. marche pas et mettent pas a jour pwd
