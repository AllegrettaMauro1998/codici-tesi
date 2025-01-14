# interfacciaSPIR

Questo progetto è un'applicazione Windows scritta in C++ che funge da interfaccia grafica per interagire con l'applicativo `SPIR.exe`. L'applicazione consente di gestire file e directory per la creazione di cataloghi, l'estrazione di dati e il matching di informazioni, offrendo supporto per operazioni di debug.

## Funzionalità

- **Creazione di cataloghi**: Permette di generare un file catalogo con la possibilità di abilitare il debug.
- **Estrazione di dati**: Consente di estrarre proprietà specifiche da immagini.
- **Matching**: Effettua il matching delle informazioni contenute nei file.
- **Drag-and-drop**: Supporto per trascinare file e directory nella finestra dell'applicazione per elaborazioni automatiche(solo per estrazione di dati per ora).

## Componenti Principali

### 1. **Finestra Principale**
La finestra principale dell'applicazione è definita nella funzione `WndProc`. Contiene quattro pulsanti:
- **Creazione Catalogo**: Avvia il processo per generare un catalogo.
- **Estrazione Dati Pinna**: Fornisce istruzioni per trascinare file o directory nella finestra per avviare l'elaborazione.
- **Matching**: Effettua il matching dei dati utilizzando i file generati da SPIR.
- **Conferma**: Pulsante nascosto utilizzato per eventuali conferme future.

### 2. **Gestione dei File**
Il codice supporta l'elaborazione di:
- Singoli file (`ProcessSingleFile`)
- Intere directory (`ProcessDirectory`)

### 3. **Debug**
Per molte operazioni, è possibile abilitare il debug, che genera file di log o informazioni aggiuntive utili per la diagnostica.

## Utilizzo

### Requisiti
- `SPIR.exe` deve essere posizionato nella directory Desktop.
- I file da elaborare devono essere trascinati nella finestra dell'applicazione.

### Come Compilare
1. Aprire il progetto in un ambiente di sviluppo compatibile con Windows (ad esempio Visual Studio).
2. Assicurarsi che tutte le librerie richieste siano incluse (`windows.h`, `shlobj.h`, ecc.).
3. avviare eseguibile

### Operazioni Principali
1. **Creazione di un catalogo**:
   - Cliccare sul pulsante "Creazione catalogo".
   - Inserire il nome del catalogo nella finestra di dialogo.
   - Seguire le istruzioni per completare il processo.

2. **Estrazione di dati**:
   - Cliccare su "Estrazione dati pinna".
   - Trascinare uno o più file o directory nella finestra dell'applicazione.
   - Attendere il completamento dell'elaborazione.

3. **Matching**:
   - Cliccare sul pulsante "Matching".
   - L'applicazione elaborerà i file richiesti e mostrerà un messaggio di conferma.

## Struttura del Codice

- **`wWinMain`**: Punto di ingresso dell'applicazione. Inizializza e avvia la finestra principale.
- **`WndProc`**: Gestisce i messaggi della finestra (eventi come clic sui pulsanti, operazioni di drag-and-drop, ecc.).
- **`ProcessFile`**: Determina se un file è una directory o un singolo file e lo elabora di conseguenza.
- **`ProcessSingleFile`**: Elabora un singolo file, costruendo il comando per l'esecuzione di `SPIR.exe`.
- **`InputDialogProc`**: Gestisce la finestra di dialogo per l'inserimento del nome del catalogo.

## Debug e Log

- I file di debug sono generati solo se l'utente abilita esplicitamente l'opzione durante le operazioni di creazione catalogo o estrazione dati.
- I file di output principali includono:
  - `fin-catalogue.cbor`
  - `fin-properties.cbor`
  - File di log di debug per diagnostica.

## Messaggi di Errore

- Se `SPIR.exe` non è presente nella directory Desktop, l'applicazione mostrerà un messaggio di errore.
- Errori di accesso ai file o al Desktop sono segnalati tramite finestre di dialogo.

## Limitazioni

- Attualmente, l'applicazione è progettata per funzionare solo su sistemi Windows.
- `SPIR.exe` deve essere posizionato nella directory Desktop per garantire il funzionamento corretto.

