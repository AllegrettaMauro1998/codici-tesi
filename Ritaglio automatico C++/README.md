# Ritaglio Automatico Immagini con Otsu e Contorni

## Descrizione

Questo programma C++ utilizza la libreria OpenCV per eseguire il ritaglio automatico delle immagini in una cartella. Il processo include i seguenti passaggi:

1. **Binarizzazione dell'immagine**: Viene applicata la soglia di Otsu per convertire l'immagine a scala di grigi in una maschera binaria.
2. **Pulizia dell'immagine**: Viene eseguita un'operazione morfologica (apertura) per rimuovere rumore e piccole aree.
3. **Rilevamento dei contorni**: Vengono individuati i contorni nell'immagine, e viene selezionato il contorno con l'area maggiore.
4. **Ritaglio dell'immagine**: Viene estratta la regione dell'immagine che corrisponde al contorno più grande.
5. **Salvataggio dell'immagine ritagliata**: L'immagine ritagliata viene salvata in una cartella di output mantenendo la struttura delle sottocartelle.

Il programma esplora ricorsivamente una cartella di input, processa tutte le immagini supportate (JPG, PNG, JPEG) e salva le immagini ritagliate in una cartella di output.

## Funzionalità

### Requisiti

- **C++11** o superiore.
- **OpenCV**: La libreria OpenCV è utilizzata per la gestione delle immagini e il rilevamento dei contorni.

Per installare OpenCV, segui le istruzioni sul sito ufficiale: [OpenCV Installation](https://opencv.org).

### Esecuzione del Programma

1. **Compila il programma**: Se non hai ancora compilato il programma, usa il seguente comando (assicurati che OpenCV sia correttamente configurato):

   ```bash
   g++ -o ritaglio_automatico ritaglio_automatico.cpp `pkg-config --cflags --libs opencv4`

    Esegui il programma: Una volta compilato, esegui il programma e inserisci il percorso della cartella da analizzare:

./ritaglio_automatico

Ti verrà chiesto di inserire il percorso della cartella contenente le immagini da processare. Il programma elaborerà tutte le immagini (con estensione .jpg, .png, .jpeg) nella cartella e nelle sottocartelle.

Esempio di input:

    Inserisci il percorso della cartella da analizzare: /percorso/della/cartella

    File di Output: Le immagini ritagliate verranno salvate in una cartella denominata output_immagini, con la stessa struttura delle sottocartelle originali.

Dettagli di Implementazione
Passaggi del Programma

    Binarizzazione con Otsu:
        L'immagine viene convertita in scala di grigi e successivamente binarizzata utilizzando la soglia di Otsu, che determina automaticamente il miglior valore di soglia per separare i pixel di interesse dallo sfondo.

    Operazioni Morfologiche:
        Viene applicata un'operazione di apertura per rimuovere piccoli rumori (piccole aree nere) nell'immagine binaria.

    Rilevamento dei Contorni:
        Vengono trovati tutti i contorni nell'immagine binaria e viene selezionato quello con l'area maggiore. Questo contorno viene considerato la regione di interesse per il ritaglio.

    Ritaglio dell'Immagine:
        L'immagine viene ritagliata per includere solo la regione circoscritta dal contorno più grande.

    Creazione e Salvataggio:
        Le immagini ritagliate vengono salvate in una cartella di output mantenendo la stessa struttura di sottocartelle.

Struttura delle Cartelle

Il programma mantiene la struttura delle cartelle di input nella cartella di output, creando sottocartelle nella cartella di destinazione per ogni sottocartella nella cartella di input.

Ad esempio:

input_cartella/
    subfolder1/
        image1.jpg
        image2.png
    subfolder2/
        image3.jpg

output_immagini/
    subfolder1/
        image1_cropped.jpg
        image2_cropped.png
    subfolder2/
        image3_cropped.jpg

Errori Comuni

    Immagine non valida: Se un'immagine non può essere caricata (ad esempio, file danneggiato o formato non supportato), il programma mostrerà un errore e continuerà a processare le altre immagini.
    Cartella non trovata: Se il percorso della cartella di input non esiste o è errato, il programma restituirà un errore e terminerà l'esecuzione.

Licenza

Questo programma è distribuito con licenza MIT. Può essere liberamente utilizzato, modificato e distribuito.
