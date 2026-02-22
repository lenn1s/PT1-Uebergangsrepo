# Programmiertechnik II SS26, Übung 3

Pro Übung gibt es 20 Punkte. Für die Zulassung zur Prüfung müssen in allen Übungen insgesamt mindestens 50 % der Punkte sowie mindestens 25 % in jeder einzelnen Übung erzielt werden.

Der Code für diese Aufgabe kann als Git-Repository geklont und lokal kompiliert werden. Dafür ist es nötig, die Git-Submodule zu initialisieren und zu aktualisieren (wichtig‼️):  

```bash
git submodule update --init
```
Anschließend kann  

```bash
make tests
```

im Projektordner ausgeführt werden, um die Tests zu kompilieren. (Der Code in `main.cpp` kann unabhängig von den Tests mit `make main` kompiliert und ausgeführt werden.)

Hinweis: Hilfestellung zum Setup der Entwicklungsumgebung und des Debuggers finden Sie in Übung 1.

## Aufgabe 1 – CountingComparator (3 Punkte)
**Dateien:** `sorting.cpp`, `sorting.h`

In dieser Aufgabe wird ein Mechanismus zur **Zählung von Vergleichsoperationen** implementiert, der später von allen Sortieralgorithmen genutzt wird, um ihre Performance zu vergleichen.

Implementieren Sie:
- **Comparator** mit  
  `compare(data, x, y)` → `>0` (x>y), `0` (gleich), `<0` (x<y)
- **CountingComparator** als Wrapper:
  - zählt jeden Vergleich
  - `getCounter()`, `reset()`

Ein Vergleich kann beispielsweise genutzt werden wie in `comparator.compare(data, x, y) > 0`.

> Anmerkung: Hierbei wird **Composition over Inheritance** demonstriert: Funktionale Erweiterung (Zählen) wird durch das **Kombinieren von Objekten** erreicht, nicht durch Vererbung. Dadurch bleibt der Wrapper unabhängig von der konkreten Vergleichslogik und kann mit beliebigen Comparator-Implementierungen verwendet werden.

---

## Aufgabe 2 – Sortieralgorithmen (7 Punkte)
**Dateien:** `sorting.cpp`, `sorting.h`

Implementieren Sie:
- **Bubblesort**
- **Mergesort**
- **Quicksort**

Zusatzanforderungen:
- **Bubblesort:** Bricht vorzeitig ab, wenn ein Durchlauf ohne Vertauschung endet
- **Mergesort:** In `merge()` prüfen, ob linke Teilliste vollständig vor rechter liegt → keine Vergleiche beim Merge nötig
- **Quicksort:** Pivot ist immer das am weitesten **links** stehende Element

> Achtung: **Alle Vergleiche** (auch im Aux-Array bei Mergesort) müssen über den **CountingComparator (`comp`)** erfolgen. Direkte Vergleiche von Array-Elementen sind nicht erlaubt.

---

## Aufgabe 3 – Datengeneratoren (6 Punkte)
**Dateien:** `main.cpp`, `generator.cpp`, `generator.h`

Die implementierten Sortieralgorithmen sollen nun vermessen werden. `main.cpp` misst Best- und Worst-Case aller Algorithmen für **n = 10, 100, 1000**.

Implementieren Sie **6 Generatoren** (jeweils für den Best-/Worst-Case-Input je Algorithmus).

Vorgaben:
- deterministisch, für beliebiges `n`
- zuerst `generateSorted(int n)` implementieren: `(0, 1, …, n−1)`, aufsteigend, ohne Duplikate
- die Generatoren erzeugen Permutationen basierend auf der Rückgabe von `generateSorted(int n)`

Hinweise:
- **Bubblesort:** Best- und Worst-Case sind einfach zu erzeugen
- **Mergesort Best-Case:** ergibt sich aus der Optimierung in Aufgabe 2
- **Mergesort Worst-Case:** rekursives alternierendes Aufteilen (0, 2, 4, … / 1, 3, 5, …)  
  Die Rekursion terminiert bei Teillisten der Länge 1. Was muss bei Länge 2 passieren?  
  Dieser Datensatz maximiert die Anzahl notwendiger Vergleiche, ohne jedoch die asymptotische Komplexität von Mergesort zu verändern.
- **Quicksort Best-Case:** Bei der Ausführung von Quicksort (mit linkem Pivot) müssen in jeder Rekursion möglichst gleich große Teilarrays entstehen. Dabei ist zu beachten, dass das Pivot-Element erst im Verlauf der Partition an seine endgültige Position gelangt.
- **Quicksort Worst-Case:** auf den ersten Blick vielleicht unintuitiv, aber mit bisherigem Code leicht zu generieren

Es existieren mehrere korrekte Lösungen für diese Generatoren. Aus diesem Grund wird nur die Anzahl der Vergleiche getestet.

Geben Sie in `solution.md` für **jeden Generator** eine **Beispielfolge für n = 10** an.

---

## Aufgabe 4 – Messungen (4 Punkte)
**Dateien:** `main.cpp`, `solution.md`

- Führen Sie `main.cpp` aus
- Speichern Sie die komplette Ausgabe in `solution.md`

Diskutieren Sie:
- Erwartung vs. Messung der Vergleichszahlen
- Größenordnung im Vergleich zur theoretischen Laufzeit (konstante Faktoren möglich)
- mögliche Ursachen für Abweichungen
- Eignet sich die Anzahl der Vergleiche als praktische Messgröße?

# Abgabehinweise
- Bearbeiten Sie die mit `// TODO` markierten Stellen im Code.
- Für die in der Aufgabenstellung beschriebenen Datentypen und Algorithmen sollen die eigenen bzw. vorgegebenen Implementierungen genutzt werden. Davon abgesehen darf die STL verwendet werden. Notieren Sie sich für das Testatgespräch: Welche Teile der STL könnten theoretisch benutzt werden, um die Aufgaben zu implementieren?
- Korrekte Speicherverwaltung (new/delete, new[]/delete[] oder ggf. Initialisierung im Stack) gehört zur Aufgabenstellung :)
- Die Tests sollen alle grün sein (`make tests`), sind aber in erster Linie eine Hilfestellung und keine Garantie für volle Punktzahl - dafür gibt es die Testatgespräche.
