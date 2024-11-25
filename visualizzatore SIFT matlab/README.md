# Visualizza i Keypoint SIFT

Questo repository contiene la funzione MATLAB **`visualize_sift_vpts1(folder)`**, che visualizza i keypoint SIFT estratti da file `.mat` e li sovrappone sulle immagini corrispondenti. La funzione evidenzia anche le orientazioni e le dimensioni dei keypoint.

---

## Caratteristiche
- Carica i file `.mat` contenenti i keypoint SIFT (`vpts1`) e le immagini croppate (`I_crop`).
- Visualizza:
  - Le posizioni dei keypoint come cerchi.
  - Le orientazioni dei keypoint tramite frecce.
- Elabora tutte le immagini nella cartella specificata.

---

## Installazione
Per usare questa funzione:
1. Clona il repository:
   ```bash
   git clone https://github.com/tuo-username/nome-repo.git

    Assicurati di avere MATLAB installato con il Computer Vision Toolbox.

Utilizzo
Parametri di input

    folder: una stringa che specifica il percorso alla cartella contenente:
        Le immagini .png da elaborare.
        Il file dd.mat contenente i keypoint SIFT (vpts1) e le immagini croppate (I_crop).

Esempio

% Specifica la cartella contenente le immagini e il file dd.mat
folder = 'percorso/della/cartella';

% Chiama la funzione
visualize_sift_vpts1(folder);

Funzionalità
1. Caricamento e Elaborazione delle Immagini

    La funzione scansiona la cartella alla ricerca di file .png.
    Per ogni immagine, cerca il file dd.mat corrispondente.

2. Caricamento dei Keypoint

    Il file .mat deve contenere:
        dd(i).I_crop: Immagine croppata corrispondente ai keypoint SIFT.
        dd(i).vpts1: Struttura dei keypoint SIFT contenente:
            pt: Coordinate dei keypoint.
            size: Dimensione di ciascun keypoint.
            angle: Orientamento di ciascun keypoint.

3. Visualizzazione dei Keypoint

    Visualizza l'immagine croppata.
    Disegna:
        Cerchi verdi per rappresentare la scala dei keypoint.
        Frecce rosse per indicare l'orientamento dei keypoint.

Output

    Visualizzazioni interattive per ogni immagine elaborata che mostrano:
        I keypoint SIFT con scala e orientamento.
        Il nome del file immagine nel titolo.

Gestione degli Errori

    Mancanza di immagini: Se non vengono trovate immagini .png nella cartella, la funzione solleva un errore:

Non ci sono immagini nella cartella specificata.

Mancanza del file .mat: Se il file dd.mat è mancante o incompleto, la funzione salta l'immagine corrispondente e visualizza un avviso:

    Il file dd.mat non esiste. Passo all'immagine successiva.

Dipendenze

    MATLAB (testato su R2021b o versioni successive).
    Computer Vision Toolbox (per le operazioni SIFT).
    Il file .mat di input deve essere strutturato con:
        dd(i).I_crop: Immagini croppate.
        dd(i).vpts1: Dati dei keypoint, inclusi posizione, scala e orientamento.

Licenza

Questo progetto è concesso in licenza sotto la licenza MIT. Vedi il file LICENSE per i dettagli.
