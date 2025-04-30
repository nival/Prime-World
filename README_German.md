[English](README.md)        [Русский](README_Russian.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Prime World Trailer](PW_trailer.png)](https://youtu.be/Fkd-zva4npI)
[Prime World](https://wikipedia.org/wiki/Prime_World) ist ein Mehrspieler-Online-Battle-Arena-Spiel (MOBA), das 2014 veröffentlicht wurde. Das Spiel wurde mit einer firmeneigenen Engine von [Nival](http://nival.com/) entwickelt und hauptsächlich in C++ geschrieben.

Das Spiel besteht aus zwei Teilen: Schloss und Kampfteil. Der Spieler übernimmt die Rolle eines Lords oder einer Lady. Im Schloss baut der Spieler Gebäude, rekrutiert Helden und wählt Talente für sie aus. Im Kampfteil steuert der Spieler einen Helden und kämpft mithilfe von Talenten gegen andere Spieler in Team-Schlachten.

Im Jahr 2024 wurde der Quellcode des Kampf-Teils des Spiels unter einer [speziellen Lizenz](LICENSE.md) veröffentlicht, die die kommerzielle Nutzung untersagt, aber für die Gaming-Community, das Studium und Forschungszwecke vollständig offen ist.
Bitte lesen Sie die Bedingungen der [Lizenzvereinbarung](LICENSE.md) sorgfältig, bevor Sie das Spiel verwenden.

## Was enthält dieses Repository?
- `pw` — der Hauptcode des Kampfteils
- `pw_publish` — kompilierter Client des Kampfteils mit Cheat-Codes und einem Client-Editor
- `pw/branches/r1117/Bin/PF_Editor.exe` — Editor für Spieldaten

## Vorbereitung
Sie müssen die Daten aus diesem Repository herunterladen und den Ordner `Bin` mit den Spieldaten zusammenführen. So geht's:

1. Kopieren Sie den Ordner `pw_publish/branch/Client/PvP/Bin` nach `pw/branches/r1117` und ersetzen Sie vorhandene Dateien.
2. Starten Sie den Client mit Cheat-Codes: `pw/branches/r1117/Bin/PW_Game.exe`.
3. Wenn alles korrekt ist, sehen Sie das Ladefenster, allerdings ohne Bild und mit schwarzem Bildschirm.
4. Im Ordner `Profiles -> game.cfg` ändern Sie den Wert von `local_game 0` auf `local_game 1`.
5. Starten Sie den Client mit Cheat-Codes. Jetzt sollten Sie die Lobby sehen, in der Sie eine Karte und einen Helden auswählen und ein Spiel starten können.
6. Drücken Sie im Spiel die Tilde-Taste (~) auf der Tastatur, um die Konsole für Cheat-Codes zu öffnen.

Bei Fehlern schauen Sie in die Log-Dateien unter `pw/branches/r1117/Bin/logs`.

## Spieldaten
Die Spieldaten können über den Editor bearbeitet werden und befinden sich in `pw/branches/r1117/Data`

Beim Bearbeiten der Daten können Sie:
1. Die Beschreibungen der Talente und Fähigkeiten der Helden ändern.
2. Talente und Fähigkeiten von Helden anpassen.
3. Die Logik von Creeps und Türmen ändern.
4. Neue Helden und Fähigkeiten hinzufügen.
5. Neue Talente hinzufügen.
6. Effekte ändern und hinzufügen.
7. Modelle und Animationen ändern und hinzufügen.

Nach der Änderung der Daten muss kein neuer Client aus dem Code gebaut werden. Klicken Sie einfach auf `File -> Save`, und alle Änderungen werden sofort im Spielclient `PW_Game` wirksam. Zum Beispiel können Sie die Beschreibung eines beliebigen Talentes oder einer Heldenfähigkeit ändern.

## Spieldateneditor
Der Spieldateneditor befindet sich unter `pw/branches/r1117/Bin/PF_Editor.exe`

Beim ersten Öffnen des Editors müssen Sie den Pfad zu `Data` konfigurieren:
1. `Tools -> File System Configuration`.
2. `Add -> WinFileSystem`.
3. Setzen Sie den Ordner Data als System-Root: `pw/branches/r1117/Data`.
4. Schließen Sie die Fenster.
5. Im Editor: `Views -> Object Browser` und `Views -> Properties Editor`. Das sind die beiden wichtigsten Bereiche zum Bearbeiten von Daten.

Die Tabs des Editors können verschoben und angedockt werden.

## Spielclient mit Cheat-Codes
Im Repository finden Sie den bereits kompilierten Spielclient mit Cheat-Codes: `pw_publish/branch/Client/PvP/Bin/PW_Game.exe`

Die Ordner `Localization`, `Profiles` und `Data` müssen sich im gleichen Verzeichnis wie der Ordner `Bin` befinden. Daher muss der Client während der Vorbereitung in den Ordner `pw` verschoben werden. Bei Änderungen am Code ist ein Neuaufbau des Clients erforderlich.

## Wie starte ich PvP?
1. Ändern Sie in `Profiles -> game.cfg` den Wert von `local_game 0`.
2. Fügen Sie `login_adress <server address>` hinzu.
3. Starten Sie das Spiel mit dem Parameter `-dev_login MyNickname`.

## Wie starte ich das Spiel mit Bots?
1. Benennen Sie die Datei `Profiles -> private.cfg_example` in `private.cfg` um.
2. Öffnen Sie die Datei mit dem Notizblock.
3. Suchen Sie nach `AT BEGINNING GAME`.
4. Fügen Sie eine neue Zeile hinzu: `add_ai bots` — das weist jedem Helden im Spiel einen KI-Bot zu.

## Fehlerbehebung bei möglichen Problemen
1. Benennen Sie die Datei `Profiles -> private.cfg_example` in `private.cfg` um.
2. Öffnen Sie die Datei mit dem Notizblock.
3. Suchen Sie den Bereich `performance section`.
4. Finden Sie die Zeile `setvar gfx_fullscreen = 0` — das startet das Spiel im Fenstermodus, was stabiler laufen könnte.
5. Andere Einstellungen zur Optimierung können ebenfalls im Bereich `performance section` geändert werden.

## Danksagungen
An die **Prime World: Nova**-Community für ihren Beitrag zur Dokumentation und Fehlerkorrektur.
