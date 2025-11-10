# Minishell

Un mini-shell écrit en C — projet pédagogique visant à réimplémenter les fonctionnalités de base d'un shell POSIX (parsing, expansion, redirections, pipes, builtins, history, here-doc, etc.). Ce dépôt contient le code source, des tests unitaires et quelques scripts d'aide.

## Aperçu

- Langage : C
- Outil de compilation : Makefile
- Bibliothèques : libreadline (utilisée pour l'historique et l'édition de ligne)
- But : comprendre et implémenter le comportement d'un shell simple (tokenisation, parsing, exécution, redirections, pipes, builtins)

## Fonctionnalités implémentées

- Tokenizer / lexer
- Parser (arbre de commandes, redirections, pipes)
- Expansion des variables d'environnement
- Gestion des quotes
- Redirections d'entrée/sortie et here-doc
- Pipes (exécution de commandes en pipeline)
- Builtins : cd, echo, env, exit, export, unset, pwd
- Gestion de l'historique (readline)
- Wildcards (glob)

## Prérequis

- Un compilateur C compatible (gcc/clang)
- make
- La bibliothèque de développement readline (ex. sous Debian/Ubuntu: libreadline-dev)

Exemple d'installation des dépendances sur Debian/Ubuntu:

    sudo apt update && sudo apt install build-essential libreadline-dev

## Compilation

Depuis la racine du projet, exécuter :

    make

Le Makefile compile la librairie `libft` et génère l'exécutable `minishell`.

Targets utiles:

- `make` : compiler le projet (par défaut)
- `make libft` : compiler seulement la `libft`
- `make clean` / `make fclean` / `make re`

## Exécution

Après compilation, lancer le shell :

    ./minishell

Exemples d'utilisation à l'intérieur du shell :

- Commandes simples : `ls -la`, `echo "hello"`
- Pipes : `ls | grep srcs | wc -l`
- Redirection : `cat < file.txt`, `echo hello > out.txt`
- Here-doc : `cat <<EOF` puis saisir du texte

Pour quitter : `exit` ou Ctrl-D

## Structure du dépôt (raccourci)

- `srcs/` : code source principal
  - `libft/` : fonctions utilitaires réutilisables
  - `minishell/` : code du shell (lexer, parser, execution, builtins, etc.)
  - `get_next_line/` : implémentation de get_next_line
- `includes/` : headers communs
- `tests/` : tests unitaires et e2e
- `Makefile` : script de build

Pour une vue détaillée, consultez l'arborescence du projet.

## Auteur

David Lacuey
