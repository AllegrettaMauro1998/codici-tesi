import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;

public class main {

    public static void main(String[] args) {
        // Specifico il percorso della cartella da esplorare
        File cartella = new File("../" + args[0]);
        esploraCartella(cartella);
    }

    public static void esploraCartella(File principale) {
        // Definisco i nomi dei file CSV
        String csvFileName = "annotazioni_cartelle.csv";
        String csvFile2Name = "annotazioni_immagini.csv";
        
        // Ottiengo il percorso assoluto della cartella principale
        String percorso = principale.getAbsolutePath(); 
        
        // Costruisco i percorsi completi per i file CSV
        String csvFile = percorso + File.separator + csvFileName;
        String csvFile2 = percorso + File.separator + csvFile2Name;

        // Ottiengo i file nella cartella principale
        File[] filescartella = principale.listFiles();
        
        if (filescartella == null) {
            System.out.print("Nome della cartella non valido");
        } else {
            try (FileWriter scrittorecartella = new FileWriter(csvFile, StandardCharsets.UTF_8);
                 FileWriter scrittoreimmagini = new FileWriter(csvFile2, StandardCharsets.UTF_8)) {

                // L'intestazione nei CSV
                scrittorecartella.append("Identificativo;N. foto;N. profilo destro;N. profilo sinistro;Note\n");
                scrittoreimmagini.append("Identificativo;Nome_immagine;Data\n");

                for (File cartella : filescartella) {
                    if (cartella.isDirectory()) {
                        String Nomecartella = cartella.getName();
                        int conta_immagini = 0;
                        int imm_destro = 0;
                        int imm_sinistra = 0;
                        StringBuilder note = new StringBuilder();

                        // Esploro i file all'interno della sottocartella
                        for (File file : cartella.listFiles()) {
                            if (!file.isDirectory()) {
                                conta_immagini++;
                                String nome_imm = file.getName();

                                // Scrivo nei CSV delle immagini
                                scrittoreimmagini.append(Nomecartella + ";" + nome_imm + ";" + nome_imm.substring(0, 4) + "/" +
                                        nome_imm.substring(5, 6) + "/" + nome_imm.substring(7, 8) + "\n");

                                // Conteggio immagini per lato
                                if (nome_imm.contains("L")) {
                                    imm_sinistra++;
                                } else {
                                    imm_destro++;
                                }
                            }
                        }

                        // Controllo delle foto insufficienti
                        if (conta_immagini < 4) {
                            note.append("Foto insufficienti per una foto-identificazione");
                        }
                        if (imm_destro < 4) {
                            if (note.length() > 0) note.append("\r\n");
                            note.append("Foto insufficienti per identificazione dal lato destro");
                        }
                        if (imm_sinistra < 4) {
                            if (note.length() > 0) note.append("\r\n");
                            note.append("Foto insufficienti per identificazione dal lato sinistro");
                        }

                        // Scrivo nel CSV delle cartelle, mantenendo tutto in una singola cella nella colonna Note
                        scrittorecartella.append(Nomecartella + ";" + conta_immagini + ";" + imm_destro + ";" + imm_sinistra + ";" + "\"" + note.toString() + "\"" + "\n");
                    }
                }

            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}

