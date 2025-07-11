# 🧪 Logiciel de Vérification et Validation Électronique – M1 Ynov


Ce dépôt contient le logiciel embarqué utilisé dans le cadre du cours de **Vérification et Validation Électronique** destiné aux étudiants de **Master 1**.  
Le logiciel est développé avec **PlatformIO** et le **framework Arduino**, et doit être déployé sur une carte **ESP32-PICO-D4**.


Ce projet vise à fournir une solution d'automatisation pour effectuer des tests sur des cartes électroniques, permettant ainsi de valider leur bon fonctionnement.


---


## 🎯 Objectif


Le but de ce projet est de permettre aux étudiants de réaliser des **tests automatisés** sur les cartes électroniques **YNOV-DevBoard v1**. Ces tests peuvent être exécutés localement sur la carte ou à distance via l'application Python **TheESP32Controller**, qui interagit avec la carte grâce à la bibliothèque [`bleak`](https://github.com/hbldh/bleak) pour la gestion de la communication Bluetooth Low Energy (BLE).


Les tests automatisés couvrent diverses fonctionnalités matérielles de la carte et permettent de vérifier leur bon fonctionnement avant leur mise en production.


---


## ⚙️ Technologies utilisées


- **ESP32-PICO-D4** : Microcontrôleur présent sur la carte YNOV-DevBoard-v1.
- **PlatformIO** : IDE utilisé pour gérer la compilation, l'upload, et les tests unitaires.
- **Arduino Framework** : Framework de programmation utilisé pour simplifier le développement embarqué.
- **BLE (Bluetooth Low Energy)** : Technologie de communication sans fil pour l'interaction avec l'application Python [`TheESP32Controller`](https://github.com/COURS-YNOV/TheESP32Controller).
- **Bleak** : Bibliothèque utiliséé pour gérer la communication BLE entre la carte et l'application Python "TheESP32Controller".
- **Unity Framework** : Framework de tests unitaires pour vérifier la validité des composants logiciels embarqués.


---


## 🧩 Fonctionnalités & Tests Implémentés


Ce software permet d'exécuter les tests suivants sur la carte **YNOV-DevBoard v1** :


### Tests des périphériques
- 🔴 **Test des LEDs** : Vérifie la bonne activation des LEDs de la carte.
- 🔊 **Test du Buzzer** : Vérifie que le buzzer fonctionne correctement en émettant des sons.
- 🌡️ **Test du capteur de température** : Teste le capteur TMP126 pour s'assurer qu'il peut mesurer la température de manière précise.
- 📉 **Test des CTN (Thermistances)** : Vérifie le bon fonctionnement des capteurs de température thermistances.
- ⚡ **Test du capteur INA** : Vérifie le bon fonctionnement du capteur INA237 pour mesurer la consommation de courant et la tension.
 
### Tests de communication
- 🔗 **Test de la communication I2C** : Vérifie que la communication I2C fonctionne correctement entre l'ESP32 et les périphériques connectés.
- 🔀 **Test de la communication SPI** : Vérifie la communication SPI entre l'ESP32 et les périphériques compatibles SPI (capteur de température).


### Tests de connectivité
- 📡 **Test BLE** : Vérifie la communication Bluetooth Low Energy (BLE) entre l'ESP32 et l'application Python **TheESP32Controller**.


### Tests divers
- **Test PWM** : Vérifie le bon fonctionnement des signaux PWM générés par la carte.
- **Test Free Text** :  Vérifie la bonne reception/envoie de données personnalisées via BLE.
- **Test acknowledge ESP32** : Teste la capacité de la carte ESP32 à répondre à des requêtes de confirmation via BLE.
- 📝 **Test d'écriture/lecture de fichier en RAM** : Vérifie la capacité de l'ESP32 à lire et écrire dans la mémoire RAM pendant l'exécution d'un test.
- 📑 **Test de génération et vérification de logs SPIFFS** : Vérifie l'enregistrement des résultats des tests dans un fichier `log.txt` stocké dans la mémoire SPIFFS de l'ESP32.


---


## ⚙️ Architecture


### Structure du projet
Le projet est organisé en plusieurs dossiers pour une gestion claire et structurée du code source :


- **`src/`** : Contient le code principal de l'application embarquée.
- **`lib/`** : Contient les drivers développés pour la configuration et l'execution des tests.
- **`include/`** : Contient les fichiers constantes et de configurations utilisés dans le projet.
- **`tests/`** : Contient les tests unitaires, organisés par fonctionnalité, pour vérifier le bon fonctionnement du code embarqué.


### 🚀 Téléverser le fichier sur la carte (SPIFFS)


Avant d'exécuter les tests, il est nécessaire de téléverser le fichier `log.txt` dans la mémoire flash SPIFFS de l'ESP32 pour enregistrer les résultats des tests.


Utilisez la commande suivante pour télécharger ce fichier sur l'ESP32 :


```bash
pio run --target uploadfs
```


# 🧪 Tests unitaires embarqués


Des tests unitaires sont inclus dans ce dépôt et peuvent être exécutés à l’aide du framework Unity.


Ces tests permettent de vérifier le bon fonctionnement des différentes parties du code source de manière isolée, garantissant ainsi la fiabilité du firmware.


## ▶️ Lancer les tests unitaires


Pour lancer les tests unitaires sur la plateforme ESP32, utilisez la commande suivante dans PlatformIO :


```bash
pio test -e esp32
```


Cette commande exécute tous les tests définis dans le répertoire `tests/` et génère un rapport détaillant les résultats.


## 📑 Test des logs SPIFFS


Les résultats des tests sont enregistrés dans un fichier `log.txt` situé dans la mémoire flash SPIFFS de l'ESP32. Ce fichier est utilisé pour stocker les résultats de chaque test exécuté. Vous pouvez vérifier son contenu en vous connectant à la carte et en lisant le fichier SPIFFS pour vous assurer que les logs sont correctement enregistrés.


Pour tester cela, vous devez effectuer les étapes suivantes :


1. Exécutez les tests.
2. Vérifiez le fichier `log.txt` dans SPIFFS pour vous assurer que toutes les informations sont correctement enregistrées.
3. Consultez le contenu du fichier avec un logiciel de lecture (par exemple, via un terminal ou en utilisant l'application Python).


## 🧑‍💻 Utilisation du logiciel


### 1. Préparer l'environnement


Clonez le dépôt :


```bash
git clone https://votre-url-de-dépôt.git
```


Installez PlatformIO :


Si vous ne l'avez pas déjà fait, installez PlatformIO en suivant la documentation officielle : PlatformIO.


Installez les dépendances :


Une fois le dépôt cloné, installez les bibliothèques nécessaires à l'aide de la commande suivante :


```bash
pio lib install
```


### 2. Télécharger le firmware sur l'ESP32


Téléversez le firmware sur la carte ESP32 avec la commande suivante :


```bash
pio run --target upload
```


### 3. Exécuter les tests


Les tests peuvent être exécutés de deux manières :


- **Test local** : Exécutez tous les tests unitaires directement sur l'ESP32 :


```bash
pio test -e esp32
```


- **Test via Bluetooth BLE (à distance)** : Utilisez l'application TheESP32Controller en Python pour interagir avec l'ESP32 via BLE et lancer les tests à distance.


### 4. Consulter les logs


Les résultats des tests sont enregistrés dans le fichier `log.txt` dans la mémoire SPIFFS de l'ESP32. Vous pouvez consulter ce fichier pour vérifier l'état de chaque test exécuté.


## 📝 Notation


Voici un tableau de notation qui peut être utilisé pour évaluer la qualité et l'exhaustivité des tests effectués.


| Critère                        | Description                                            | Points  |
|-------------------------------|--------------------------------------------------------|-------------|
| Tests des LEDs                | Vérification correcte de l'activation des LEDs.       |             |
| Test du Buzzer                | Vérification correcte du son émis par le buzzer.      |             |
| Test du capteur TMP126        | Précision des mesures de température.                 |             |
| Tests de communication (I2C, SPI) | Fonctionnalité des communications I2C et SPI.     |             |
| Test BLE                      | Bon fonctionnement de la communication BLE.           |             |
| Tests divers (PWM, Free Text, etc.) | Vérification des autres tests variés.          |             |
| Test des logs SPIFFS          | Enregistrement correct des résultats dans `log.txt`.  |             |
| Ajout de tests unitaires          | Création de tests unitaires dans le projet.  |             |
| Ajout de GitHub Action          | Utilisation des GitHub Actions.  |             |


## 📋 TODO


Voici une liste des tâches restantes ou des fonctionnalités à ajouter pour améliorer ce projet :


- Tests de la communication avec la ROM externe
- Tests de performance : Implémenter des tests pour mesurer la consommation de mémoire et la performance de l'ESP32 pendant l'exécution des tests.