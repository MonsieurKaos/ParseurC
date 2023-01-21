# ParseurC

Sujet
Réaliser un parser (analyser) de fichier. Le fichier sera un fichier au format texte. Le contenu du fichier de sera de la forme suivante:

[elem1, elem2, elem3, ….. ]

Chaque élément peut être de type, “entier” (int), virgule flottante, chaine de caractère, booléen. le début et la de la liste sont marqués par les caractères [ ]. Un fichier ne contient qu’une seule liste d'éléments. Les flottants sont en notation américaine (ie: 12.42 et non 12,42)

Exemple de contenu de fichier: [ 42, “ma chaîne de character”, true,1, 67] [ ] [ toto, 42, 10, 11.567, 12]

Vous devez réaliser un programme qui ouvre le fichier, charge les éléments en mémoire, et affiche de le résultat de l’analyse sur la forme suivante: #: type: ... content: ... Pour une liste [ 1, “42”] le résultat est le suivant: 0: type: int content: 1 1: type: string content: “42”

Le programme doit être exécuté de la façon suivante: ./projet1 <nom_de_fichier> exemple: ./projet1 fichier_test1.txt

Contraintes: !!!! ATTENTION !!!! Vous devez créer une structure de donnée en mémoire, votre programme doit faire l’analyse et l’affichage en 2 étapes, exemple en pseudo code: ma_liste = analyse_fichier(“fichier.txt); fonction_affiche(ma_liste); Vous devez utiliser les fonctions malloc et free.

Barème Si le programme fonctionne mais ne respecte pas les contraintes du sujet note max 10/20. Si le programme fonctionne et respecte les contraintes, note max 15/20. 5 points sont sur la gestion des cas d’erreurs. 3 points peuvent être retirés, si le code n’est pas formaté correctement, s’il est anormalement complexe ou difficile à lire.
