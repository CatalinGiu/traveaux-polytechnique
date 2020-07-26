# INF8480_TP2

On a pas setup sur OpenStack pour gestion fichiers: en local ou sur le meme sous-reseau c'est plus facile à tester

1. Compiler

ant


/************** Lancer calculators (servers) ********************/

1. Connecter ssh

$ ssh L4712-01
$ ssh L4712-02
$ ssh L4712-03
$ ssh L4712-04
$ ssh L4712-05

2. demarrer les rmiregistry avec la commande suivante sur l'ensemble de s postes
$ cd bin
$ rmiregistry &
$ cd ..

3. Lancer catalog (à partir dossier principal)

$ ./catalog

IMPORTAT: noter le hostname du poste sur lequel le catalogue a ete lance, on va nommer ce hostname HOST_CATALOG


4. Lancer des instances calculator avec la semantique suivante

$ ./calculator [HOST_CATALOG] [HOST_CALCULATOR] [RESSOURCES] [MALICIOUS] [MALICIOUS_RATE]
    HOST_CATALOG : String ->    c'est le nom du host sur lequel le catalogue est lance
    RESSOURCES : int ->         nombre de resources
    MALICIOUS : boolean ->      true si on veut un serveur malicieux, false sinon
    MALICIOUS_RATE : double ->  valeur decimale entre 0 et 1 pour dire le taux de resultats malicieux

##########      ATTENTION     ###########
## catalogue est un classe tres (trop) simple, si un hostname est enregistre dedans,
## la seule manirer de le retirer est de redemarrer catalogue.
## il faut donc s'assurer de toujours entrer la bonne valeur de HOST_CALCULATOR sinon il faudra
## fermet toutes les instances de calcul, fermer catalogue et recommencer a l'etape 3
##

Ex:
# on a lance catalog sur l4712-01
$ ./catalog
$ ./calculator l4712-01 l4712-02 5 true 0.8
$ ./calculator l4712-01 l4712-03 3 true 0.5
$ ./calculator l4712-01 l4712-04 4 false
$ ./calculator l4712-01 l4712-05 8 true 0.8

/************** Lancer repartitor ********************/

1. Utiliser repartitor (a partir du dossier principal

$ ./repartitor [HOST_CATALOG] [OPERATIONS_PATH] [SECURE] [USERNAME] [PASSWORD]
    HOST_CATALOG : String ->        c'est le nom du host sur lequel le catalogue est lance
    OPERATIONS_PATH : String ->     path jusqu'au fichier d'operations
    SECURE : boolean ->             true si on lance en mode securise, false sinon
    USERNAME : String ->            ideantifiant pour le catalogue
    PASSWORD : String ->            mot de passe pour le catalogue

Ex:
# on a lance catalog sur l4712-01
# il faut bien entendu avoir des instances de serveur dans le catalogue pour que ca fonctionne
$ ./repartitor l4712-01 ops/operations-588 false user pass

##########      ATTENTION     ###########
##  user et pass sont enregistre dans le catalogue lors de la premiere connection
##  ainsi se connecter avec le meme usager mais un mot de passe different est impossible
##  sans reinitialiser le catalogue (le redemarrer)
##

/********************/


# Option a ajustet et ajouter pour lancer un serveur a distance dans le fichier "calculator" et "catalog"
#  -Djava.rmi.server.hostname=mycomputer.example.com \
*si on voudrait l'utiliser sur OpenStack d'applique la modification ci-haut et de modifer un legerement le code pour
 changer le port de nos applications
