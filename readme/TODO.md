# Minishell

enlever les malloc de la token_list

refaire get_next_line (multiple fd)

refacto lexing, parsing et exec

ajoute une enum pour le parsing

gerer les leak pour une fausse commande :
   - donner la token list au fork dans lexec pour pouvoir la free

