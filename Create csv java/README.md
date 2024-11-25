# Programma di Esplorazione Cartelle e Creazione CSV

## Descrizione

Questo programma Java esplora una cartella e le sue sottocartelle, raccogliendo informazioni sulle immagini presenti in esse. Per ogni sottocartella, il programma genera due file CSV:

1. **annotazioni_cartelle.csv**: Contiene informazioni sulle sottocartelle, come il numero totale di immagini, il numero di immagini per il profilo destro e sinistro, e le note relative a foto insufficienti.
2. **annotazioni_immagini.csv**: Contiene informazioni dettagliate su ogni immagine, come il nome dell'immagine e la data (estratta dal nome del file).

Il programma verifica anche se una cartella contiene un numero insufficiente di immagini o immagini per un lato specifico (destro/sinistro) e registra le note in merito.

## Funzionamento

### Esecuzione del Programma

1. **Prepara la cartella di partenza**:
   - Il programma esplora la cartella passata come parametro alla riga di comando, e tutte le sue sottocartelle.
   
2. **Genera i file CSV**:
   - Il programma crea due file CSV:
     - `annotazioni_cartelle.csv`: Per ogni sottocartella, vengono registrate informazioni come il numero di foto, le foto per il lato destro e sinistro, e le note relative a eventuali insufficienze.
     - `annotazioni_immagini.csv`: Per ogni immagine, vengono registrati il nome del file e una data (estratta dal nome).

### Requisiti

- **Java 8 o versioni successive**: Il programma è scritto in Java e richiede un ambiente Java per l'esecuzione.
- Il programma deve essere eseguito con la cartella contenente le immagini e le sottocartelle specificata come parametro.

### Parametri di Input

Il programma accetta come parametro il nome della cartella principale da esplorare. Questo parametro viene passato al programma come argomento alla riga di comando.

**Esempio di esecuzione**:

```bash
java main nome_cartella

Dove nome_cartella è la cartella che contiene le sottocartelle con le immagini.
Funzionalità

    Esplorazione cartelle e sottocartelle: Il programma esplora la cartella principale e tutte le sue sottocartelle, analizzando ogni file immagine.

    Generazione dei file CSV:
        annotazioni_cartelle.csv: Per ogni sottocartella, il programma raccoglie:
            Identificativo della cartella (nome)
            Numero di immagini totali
            Numero di immagini del profilo destro
            Numero di immagini del profilo sinistro
            Note sulle insufficienze di foto per la foto-identificazione.
        annotazioni_immagini.csv: Per ogni immagine:
            Identificativo della cartella
            Nome dell'immagine
            Data (estratta dal nome del file dell'immagine, nel formato YYYY/MM/DD).

    Controllo delle immagini insufficienti: Il programma verifica che ci siano almeno 4 immagini per ogni lato (destro e sinistro) per una corretta identificazione. Se una cartella non soddisfa questo requisito, vengono aggiunte delle note nel file CSV delle cartelle.

Struttura dei File CSV

    annotazioni_cartelle.csv:
    Identificativo	N. foto	N. profilo destro	N. profilo sinistro	Note
    NomeCartella	10	5	5	Note sulle foto insufficienti

    annotazioni_immagini.csv:
    Identificativo	Nome_immagine	Data
    NomeCartella	immagine_001.jpg	2022/01/01
    NomeCartella	immagine_002.jpg	2022/01/02

Errori Comuni

    Cartella non valida: Se il nome della cartella passata come argomento non è corretto o non esiste, il programma restituirà un errore e non procederà con l'esplorazione.
