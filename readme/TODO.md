# Minishell
FAIRE mettre a jour la version non interactive

<!-- MODIFIER get_next_line (multiple fd) -->
<!-- MODIFIER le heredoc pour le faire sans fork? -->
<!-- MODIFIER tout les signaux pour faire des fonctions avec sigaction? -->
<!-- MODIFIER enlever les exit et ne pas fork pour les builtin -->

FAIRE exit builtin
FAIRE SHLVL qui diminue quand on exit
env qui copie pas l'env du Wesh actuel (il copie celui du bash), on sort pas notre env a la fin
MODIFIER mettre un path pour le .minishell_history sinon quand tu cd ca creer le fichier a chaque fois dans le current dir

TEST A FAIRE SI MOTIVÉ
test gnl avec plus de MAPSIZE fd
