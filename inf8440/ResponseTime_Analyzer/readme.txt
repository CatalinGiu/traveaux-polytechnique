Apres avoir unzip l'archive, aller dans le repertoire avec le ficheir "build.xml"

1. compiler le code source avec la commande
$ ant

2. demarrer le rmiregistry avec la commande suivante:
$ cd bin
$ rmiregistry &
$ cd ..

3.demarrer le serveur
$ ./server &

# Option a ajustet et ajouter pour lancer un serveur a distance dans le fichier "server"
#  -Djava.rmi.server.hostname=mycomputer.example.com \

4. apres avoir compile le code sur l'ordinateur client comme mentionne a l'etape 1, demarrer le client
$ ./client 127.0.0.1

l'adresse qui suit la premiere execution du client va etre sockee dans un fichier "ip.txt"
si on cherche a changer l'adresse de destination des requetes, il suffit d'edite cette la premiere ligne

4_1. dans le cas ou la connection ne reussit pas, essayez de supprimer les fichiers "id.txt" et "ip.txt" et rouler a nouveau le client comme montre a l'etape 4

5. une fois que le client a ete roule une fois, le reste des commandes doivent etre roulees sans l'adresse ip. Ex:
$ ./client list

