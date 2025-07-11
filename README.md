# 📟 Projet YNOV-DevBoard-v1 – Software & Hardware

Ce dépôt Git regroupe l'ensemble du projet **YNOV-DevBoard v1**, développé dans le cadre des cours de **Conception** & **Validation Électronique** en Master 1 à YNOV Bordeaux Campus.

Il contient deux dossiers complémentaires :

- Un contenant le **logiciel embarqué** permettant la réalisation des tests sur la carte.
- Un contenant le **projet hardware** complet de conception de la carte basée sur l’ESP32-PICO-D4.

---

## 🗂 Structure du dépôt

```
YNOV-DevBoard-v1/
│
├── software/   # Code source embarqué, tests unitaires, tests fonctionnels 
├── hardware/   # Schéma, PCB, documentation et contraintes de conception
└── README.md   # Ce fichier
```

---

## 🧪 Dossier `software/` – Logiciel embarqué de tests

Ce dossier contient le logiciel développé pour tester automatiquement les fonctionnalités de la carte **YNOV-DevBoard v1**.

📌 Fonctionnalités principales :
- Tests des capteurs (INA, TMP126, CTN)
- Tests des interfaces de communication (I2C, SPI, BLE)
- Tests des éléments HMI (LEDs, buzzer)
- Génération de **logs SPIFFS** pour suivre l’état des tests
- Contrôle local ou distant (via **BLE** avec l'application Python [`TheESP32Controller`](https://github.com/COURS-YNOV/TheESP32Controller))

🧪 Outils utilisés :
- PlatformIO + Framework Arduino
- Unity Framework pour les tests unitaires

📂 Pour plus de détails 👉 [Software/README.md](./Software/README.md)

---

## 📟 Dossier `hardware/` – Conception de la carte YNOV-DevBoard v1

Ce dossier contient tous les éléments nécessaires à la conception de la carte électronique :

📌 Spécifications :
- Microcontrôleur **ESP32-PICO-D4**
- Triple source d’alimentation (USB-C, BT, HT jusqu’à 36V)
- Capteurs de courant, tension, température (INA237, CTN, TMP126)
- Interfaces **BLE**, **MikroBus**, **Grove**
- Buzzer, LEDs, boutons BOOT et RESET

🔧 Fichiers fournis :
- Projet **Altium Designer** avec schématique & PCB vierges
- Bibliothèques de composants
- Contraintes de routage strictes (sans composants sur face bottom, pas d’angles droits, plan de masse obligatoire…)

📂 Pour plus de détails 👉 [Hardware/README.md](./Hardware/README.md)

---

## 🎓 Objectifs pédagogiques

- Concevoir une carte électronique respectant des contraintes industrielles.
- Développer un logiciel de test modulaire et automatisé.
- Apprendre les bonnes pratiques de tests embarqués (unitaires, fonctionnels, utilisation de logs ...).
- Travailler en synergie entre le hardware et le software.

---

## 📣 Remarques

- Ce projet est réalisé en **groupe**, mais la **notation est individuelle**.
- Des critères précis de notation sont définis dans chaque dossier (`software` et `hardware`).

---

## 🤝 Encadrement

Pour toute question ou besoin de support :
- Contactez vos **enseignants** :
  - [@Jordan CLÉMENT](https://github.com/Jordan18122000)
  - [@Dorian FOURNIER](https://github.com/DorianFournier)

- Utilisez les issues GitHub ou le canal de communication de votre groupe

---
