###################
# Compilateur C-- #
###################

# Description ###############################################################

Ceci est un compilateur pour une version allegée du C (cmm ou c--).
Les programmes sont compilés pour l'architechture Mini Stack Machine (MSM).
Ce projet comprend également un "testeur", ce dernier est un programme
permettant l'éxécution d'une batterie de test sur le compilateur.

# Build #####################################################################

Build du compilateur :
----------------------
Pré-requis : 
    - Cmake 3.1.X.X +
    - Make

Exécuter les commandes suivantes depuis la racine du projet :
    mkdir build
    cd build
    cmake ..
    make


Build de la Mini Stack Machine :
--------------------------------
Exécuter les commandes suivantes depuis la racine du projet :
    cd msm
    make

Build du testeur :
------------------
Pré-requis : 
    - Cmake 3.1.X.X +
    - Make
    - openmp
    - pthread

Pour installer openmp :
    sudo apt-get install libomp-dev

Exécuter les commandes suivantes depuis la racine du projet :
    mkdir test/build
    cd test/build
    cmake ..
    make

# Utilisation ###############################################################

Compiler un programme:
    usage: ./compiler source-code output-file
Exemple :
    ./build/compiler program.cmm program.out

Executer un programme:
    usage: msm/msm program.out

Lancer une batterie de test avec le testeur (depuis la racine du projet):
    usage: ./tester -m machine-path -c compiler-path -t test-folder-path
Exemple :
    ./test/build/tester -m msm/msm -c build/compiler -t test/tests/
