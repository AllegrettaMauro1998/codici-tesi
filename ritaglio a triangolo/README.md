# Ritaglio Immagini con Curvatura e Triangolo

Questo script MATLAB consente di eseguire il ritaglio di immagini, selezionando manualmente i punti per un triangolo e una curva di curvatura. Il risultato è un'immagine ritagliata in base alla selezione dell'utente, salvata in una cartella di output.

---

## Caratteristiche
- Seleziona 3 punti per definire un triangolo e un punto per la curvatura in un'immagine.
- Calcola una curva di Bezier tra il primo e il terzo punto del triangolo.
- Crea una regione poligonale che unisce la curva e il triangolo.
- Crea una maschera per il ritaglio dell'immagine in base alla regione selezionata.
- Salva le immagini ritagliate nella cartella di output.

---

## Installazione

Per utilizzare questo script:
1. Clona il repository:
   ```bash
   git clone https://github.com/tuo-username/nome-repo.git

    Assicurati di avere MATLAB installato.

Utilizzo
Parametri di input

    folderPath: Percorso della cartella contenente le immagini da elaborare.
    Il risultato verrà salvato nella cartella output_dataset, che viene creata automaticamente se non esiste già.

Esempio

% Specifica il percorso della cartella contenente le immagini
folderPath = 'C:\path\to\your\images';

% Chiama lo script per eseguire il ritaglio
run('nome_script.m');

Funzionalità

    Caricamento e Elaborazione delle Immagini:
        Lo script scansiona la cartella specificata per immagini .png, .jpg, .jpeg, .bmp, .tif, e .tiff.

    Selezione dei Punti:
        Per ogni immagine, l'utente seleziona 3 punti per definire un triangolo.
        Successivamente, l'utente seleziona 1 punto per la curvatura.

    Generazione della Curva:
        Viene calcolata una curva di Bezier quadratica tra il primo e il terzo punto del triangolo.

    Creazione della Maschera:
        La maschera viene creata unendo la curva e il triangolo, formando una regione poligonale.

    Ritaglio dell'Immagine:
        La maschera viene applicata all'immagine per eseguire il ritaglio.

    Salvataggio dell'Immagine Ritagliata:
        L'immagine ritagliata viene salvata nella cartella di output come file con suffisso _ritaglio_tri.

Output

    Le immagini ritagliate vengono salvate nella cartella output_dataset con il nome del file originale, seguito dal suffisso _ritaglio_tri.
    Ogni immagine ritagliata include una regione definita dai punti selezionati per il triangolo e la curva.

Gestione degli Errori

    Cartella Vuota: Se la cartella specificata non contiene immagini supportate, viene sollevato un errore:

Nessuna immagine trovata nella cartella selezionata.

File Non Supportato: Se il file non è un'immagine, viene ignorato e viene visualizzato un messaggio di avviso:

File non immagine ignorato: nome_file

Cartella di Input Non Selezionata: Se la cartella di input non è specificata, viene sollevato un errore:

    Nessuna cartella selezionata.

Dipendenze

    MATLAB (testato su R2021b o versioni successive).
    Nessuna dipendenza esterna, ma è necessario avere una versione di MATLAB che supporti le funzioni di base per il trattamento delle immagini.

Licenza

Questo progetto è concesso in licenza sotto la licenza MIT. Vedi il file LICENSE per i dettagli.
