# Programma di Gestione Immagini con Cropping e Eliminazione

## Descrizione

Questo programma consente di gestire un insieme di immagini in una cartella e nelle sue sottocartelle. Il programma esegue una serie di operazioni sulle immagini in base alla percentuale di pixel neri (sotto una determinata soglia), permettendo di:

1. **Croppare** l'immagine per selezionare una porzione di interesse.
2. **Passare** all'immagine successiva senza fare nulla.
3. **Eliminare** l'immagine se non è necessaria.

## Funzionamento

Il programma si sviluppa in diverse fasi:

1. **Selezione della cartella principale**: l'utente inserisce il nome della cartella principale dove si trovano le immagini.
2. **Esplorazione delle sottocartelle**: il programma esplora tutte le sottocartelle della cartella principale.
3. **Analisi delle immagini**: per ciascuna immagine, il programma esegue le seguenti operazioni:
   - Converte l'immagine in scala di grigi.
   - Crea una maschera binaria in base alla soglia di pixel neri.
   - Se la percentuale di pixel neri è inferiore alla soglia impostata, l'utente ha tre opzioni:
     - **Croppare**: selezionare un rettangolo da ritagliare nell'immagine.
     - **Passare**: non fare nulla.
     - **Eliminare**: rimuovere l'immagine.
4. **Interfaccia utente**: Il programma utilizza una GUI semplice per interagire con l'utente, con un pulsante di "Esci" per interrompere il processo in qualsiasi momento.

## Requisiti

- **MATLAB**: Il programma è sviluppato in MATLAB.
- Le librerie di MATLAB necessarie sono quelle standard (ad esempio, `imread`, `rgb2gray`, `imshow`, `imcrop`, ecc.).

## Istruzioni per l'uso

1. **Avviare il programma**:
   - Esegui il file `.m` in MATLAB.
   
2. **Inserisci il nome della cartella**:
   - Verrà richiesta una finestra di input dove inserire il nome della cartella che contiene le immagini.
   
3. **Seleziona l'azione per ogni immagine**:
   - Quando il programma trova un'immagine, verrà visualizzata e ti sarà chiesto se desideri:
     - **Croppare**: Seleziona un rettangolo nell'immagine e premi il pulsante "Conferma Crop".
     - **Passare**: Non fare nulla.
     - **Eliminare**: Rimuovere l'immagine dal disco.

4. **Uscire dal programma**:
   - Puoi premere il pulsante "Esci dal Programma" in qualsiasi momento per fermare l'elaborazione.

5. **Processo completo**:
   - Una volta che il programma ha completato il processo per tutte le immagini, verrà visualizzato il messaggio **"Processo completato!"**.

## Parametri configurabili

- **Threshold (Soglia per la maschera binaria)**: 
   La variabile `threshold` definisce la soglia per determinare se un pixel è nero o meno. Modifica questo valore per cambiare la sensibilità del filtro.
   
- **Black Threshold (Soglia per i pixel neri)**: 
   La variabile `blackThreshold` rappresenta la percentuale massima di pixel neri (rispetto al totale dei pixel) che è accettabile per considerare un'immagine valida. Se la percentuale di pixel neri è inferiore a questa soglia, viene chiesto all'utente se vuole elaborare l'immagine.

- **Estensioni delle immagini**:
   Il programma attualmente supporta immagini con le estensioni `.jpg` e `.png`, ma è possibile aggiungere altre estensioni modificando la variabile `imageExtensions`.

## Esempio di utilizzo

1. Carica il programma e inserisci il nome della cartella:

Inserisci il nome della cartella: immagini_esempio


2. Durante l'elaborazione delle immagini, scegli una delle opzioni quando viene visualizzata un'immagine:
- Croppa
- Passa
- Cancella

3. Al termine del processo, riceverai il messaggio di completamento:

Processo completato!


## Note

- **Funzionalità di uscita**: È possibile interrompere il programma in qualsiasi momento utilizzando il pulsante "Esci dal Programma".
- **Backup delle immagini**: Si consiglia di eseguire un backup delle immagini prima di eseguire il programma, specialmente se si prevede di eliminare le immagini.
- **Prestazioni**: Il programma è progettato per gestire un numero moderato di immagini, ma potrebbe richiedere tempi di elaborazione più lunghi per grandi volumi di dati.

## Licenza

Questo programma è distribuito con licenza **MIT**. Vedere il file `LICENSE` per i dettagli.
