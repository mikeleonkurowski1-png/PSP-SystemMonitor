# PSP-SystemMonitor

- in Homebrew-SystemMonitor für die Sony PSP, geschrieben in C mit dem PSPSDK.
- Das Programm soll verschiedene Systeminformationen der PSP, wie Akkustand, CPU-Daten, etc übersichtlich auf dem Bildschirm darstellen und soll als erstes Einstiegsprojekt in die Entwicklung von PSP-Homebrew Anwendungen, bzw allgemein als Einstieg in die hardwarenahe Entwicklung mit C für mich dienen.

## Features

- Anzeige von Systeminformationen direkt auf der PSP 
- Controllersteuerung
- Übersichtliche Benutzeroberfläche 
- Erweiterbar um weitere Systeminformationen 

## Roadmap

- [x] Projekt aufsetzen (PSPSDK, GitHub-Repository)
- [X] Erstes Programm auf der PSP ausführen
- [X] Controller-Eingaben verarbeiten
- [X] Menü erstellen
- [X] Batteriestatus anzeigen
- [X] Informationen zum Arbeitsspeicher anzeigen
- [X] CPU-Informationen anzeigen
- [X] Devkit-Version anzeigen
- [X] Bildschirm regelmäßig aktualisieren
- [X] Farbiges Menü
- [ ] Optional: Grafische Oberfläche

## Tech Stack

- Sprache: C
- SDK: PSPSDK
- Build-System: Make
- Versionsverwaltung: Git, GitHub

## Installation

- Um den PSP-SystemMonitor selbst verwenden zu können müssen sie folgenden Schritten folgen:
  1. Laden Sie die Datei names "EBOOT.PBP" unter "Releases" herunter
  2. Verbinden sie ihre PSP per USB-Kabel mit ihrem Laptop (Gehen sie dazu nach anstecken des Kabels in den Einstellungen ihrer PSP auf "USB verbindung herstellen")
  3. Greifen Sie auf den Memory-Stick ihrer PSP zu und und gehen sie in den Unterordner namen "Games"
  4. Erstellen sie dort einen neuen Ordner an und geben sie diesem einen beliebigen Namen. (Am besten "SystemMonitor" oder ähnlich, da dieser Name entscheidet, wie das Programm auf ihrer Konsole heißen wird)
  5. Fügen sie die Datei "EBOOT.PBP" dort ein
  6. Trennen sie nun sicher die PSP von ihrem Laptop
  7. Nun finden sie unter ihren PSP Spielen die SystemMonitor-Anwendung
  
## Demo: 

![App im PSP-Homescreen:](Demo/Demo1.png)
![Startmenü:](Demo/menu.jpg)
![SystemMonitor (WLAN offline):](Demo/wlanoff.jpg)
![SystemMonitor (WLAN online):](Demo/wlanon.jpg)