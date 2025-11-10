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

## Tests

Des tests unitaires et des tests end-to-end sont présents dans `tests/`. Il n'y a pas (à ce stade) de target `check` automatique définie dans le `Makefile` pour lancer l'ensemble des tests.

Pour exécuter manuellement les tests unitaires :

1. Compiler le projet avec `make`.
2. Utiliser l'exécutable de test présent dans `tests/unit/` si fourni, ou lancer les fichiers de test via votre runner préféré.

## Contribution

Contributions bienvenues :

- Ouvrir une issue pour décrire le bug ou la fonctionnalité.
- Faire une branche dédiée et un pull request clair et limité.

Style & conventions : suivez les règles de style C du projet (twist 42-style si applicable) et gardez les commits atomiques.

## Licence

Aucune licence explicite n'a été fournie dans ce dépôt. Si vous êtes l'auteur et souhaitez publier ce projet, ajoutez un fichier `LICENSE` avec la licence souhaitée (MIT, BSD, etc.).

## Auteur

D. Lacuey (organisation du dépôt et contributions principales).

Pour toute question ou suggestion, ouvrez une issue ou contactez l'auteur via le canal habituel.

---

Remarques : j'ai rédigé une version claire et lisible du README. Si vous voulez, je peux :

- ajouter des instructions plus précises pour les tests (après examen du dossier `tests/`),
- ajouter une capture d'écran/diagramme dans `readme/` et la référencer proprement,
- ajouter un fichier `LICENSE` (MIT) et un `CONTRIBUTING.md` minimal.
