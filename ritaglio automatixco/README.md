# Ritaglio Automatico delle Immagini

Questa funzione in MATLAB esegue un ritaglio automatico delle immagini contenenti una regione di interesse (come una pinna) utilizzando tecniche di elaborazione delle immagini. La funzione analizza le immagini, individua la regione più ampia (in base all'area) e la ritaglia con un margine predefinito.

## Descrizione

Il codice permette di:
1. Caricare le immagini da una cartella di input.
2. Convertire le immagini in scala di grigi.
3. Binarizzare l'immagine usando la soglia di Otsu.
4. Pulire l'immagine con un'operazione di apertura per rimuovere il rumore.
5. Identificare la regione più ampia nell'immagine, che corrisponde alla pinna o alla regione di interesse.
6. Ritagliare l'immagine intorno a questa regione, con un margine aggiuntivo.
7. Salvare l'immagine ritagliata nella cartella di output.

## Funzione

### `automatic_crop(input_folder, output_folder)`

Questa funzione riceve due argomenti:
- `input_folder`: il percorso della cartella che contiene le immagini da elaborare.
- `output_folder`: il percorso della cartella dove saranno salvate le immagini ritagliate.

### Dettagli della Funzione

1. **Caricamento delle immagini**: Il codice carica tutte le immagini PNG dalla cartella di input.
2. **Conversione in scala di grigi**: Ogni immagine viene convertita in scala di grigi per semplificare l'elaborazione.
3. **Binarizzazione con la soglia di Otsu**: L'immagine viene binarizzata per separare la regione di interesse dallo sfondo.
4. **Pulizia dell'immagine**: Un'operazione di apertura viene eseguita per rimuovere il rumore nell'immagine binarizzata.
5. **Individuazione della regione di interesse**: La regione più ampia (ad esempio la pinna) viene identificata tramite la funzione `regionprops`.
6. **Ritaglio dell'immagine**: L'immagine viene ritagliata intorno alla regione di interesse con un margine di 3 pixel.
7. **Salvataggio dell'immagine ritagliata**: Le immagini ritagliate vengono salvate nella cartella di output, mantenendo il nome originale dell'immagine con l'aggiunta del suffisso `_cropped`.

## Requisiti

- MATLAB
- Image Processing Toolbox (necessario per funzioni come `rgb2gray`, `imbinarize`, `regionprops`, ecc.)

## Esempio di utilizzo

Esegui la funzione passando la cartella di input e la cartella di output desiderata. Ad esempio:

```matlab
input_folder = 'C:/path/to/images';
output_folder = 'C:/path/to/output';
automatic_crop(input_folder, output_folder);

Assicurati che le cartelle di input contengano immagini .png e che la cartella di output esista (il codice la creerà automaticamente se non esiste).
Output

Le immagini ritagliate saranno salvate nella cartella di output con il suffisso _cropped aggiunto al nome dell'immagine originale.
Esempio di nome di file di output:

    image1_cropped.png
    image2_cropped.png

Licenza

Questo codice è distribuito sotto la Licenza MIT. Vedi il file LICENSE per i dettagli.


### Spiegazione del `README.md`:

- **Introduzione**: Descrizione breve di cosa fa la funzione.
- **Funzione**: Descrizione dettagliata della funzione `automatic_crop` con i parametri che accetta.
- **Requisiti**: Software necessario (in questo caso MATLAB e il toolbox di elaborazione delle immagini).
- **Esempio di utilizzo**: Come utilizzare la funzione nel proprio ambiente MATLAB.
- **Output**: Descrizione dei file che la funzione genererà.
- **Licenza**: Aggiunta di una sezione sulla licenza (opzionale, ma raccomandata se il codice è condiviso pubblicamente).

Questo `README.md` fornisce una guida completa su come utilizzare il codice per il ritaglio 
