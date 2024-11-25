// ritaglio automatico.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.

#include <opencv2/opencv.hpp>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using namespace cv;
using namespace std;

// Funzione per binarizzare l'immagine usando la soglia di Otsu
void thresholdByOtsuA(Mat& input, Mat& output) {
    cvtColor(input, output, COLOR_BGR2GRAY);  // Conversione in scala di grigi
    threshold(output, output, 0, 255, THRESH_BINARY | THRESH_OTSU);  // Soglia di Otsu inversa
}

// Funzione per processare ogni immagine
void processaImmagine(const fs::path& percorsoImmagine, const fs::path& cartellaOutput, const fs::path& cartellaInput) {
    // Caricamento dell'immagine
    Mat I1 = imread(percorsoImmagine.string());
    if (I1.empty()) {
        cerr << "Errore nel caricamento dell'immagine: " << percorsoImmagine << endl;
        return;
    }

    // Binarizzazione immagine con Otsu
    Mat BW;
    thresholdByOtsuA(I1, BW);
 
    imshow("Immagine binaria - BW", BW);
    //waitKey(0); // Aspetta che l'utente prema un tasto
    destroyAllWindows();

    // Operazioni morfologiche per pulizia: apertura
    Mat BW_open;
    morphologyEx(BW, BW_open, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(3, 3)));

    // identificazione contorni e seleziona la regione più grande
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(BW_open, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    int maxArea = 0;
    int largestContourIdx = -1;
    for (size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            largestContourIdx = i;
        }
    }

    if (largestContourIdx == -1) {
        cerr << "Nessun contorno trovato nell'immagine: " << percorsoImmagine << endl;
        return;
    }

    // Creo maschera per il contorno più grande
    Mat fin = Mat::zeros(BW_open.size(), CV_8UC1);
    drawContours(fin, contours, largestContourIdx, Scalar(255), FILLED);

    // Ritaglio la regione con bounding box
    Rect boundingBox = boundingRect(contours[largestContourIdx]);
    Mat I_crop1 = I1(boundingBox);

    // Determino il percorso relativo rispetto alla cartella di input
    fs::path percorsoRelativo = fs::relative(percorsoImmagine.parent_path(), cartellaInput);
    fs::path percorsoOutputCompleto = cartellaOutput / percorsoRelativo;

    // Creo la struttura di cartelle nella cartella di output
    if (!fs::exists(percorsoOutputCompleto)) {
        fs::create_directories(percorsoOutputCompleto);
    }

    // Salvo l'immagine ritagliata nella cartella di output
    fs::path percorsoFileOutput = percorsoOutputCompleto / percorsoImmagine.filename();
    imwrite(percorsoFileOutput.string(), I_crop1);

    cout << "Immagine ritagliata e salvata: " << percorsoFileOutput << endl;
}

// Funzione per scorrere la cartella e processare tutte le immagini
void processaCartella(const fs::path& cartellaInput, const fs::path& cartellaOutput) {
    if (!fs::exists(cartellaOutput)) {
        fs::create_directories(cartellaOutput);
    }

    for (const auto& entry : fs::recursive_directory_iterator(cartellaInput)) {
        if (entry.is_regular_file()) {
            std::wstring extension = entry.path().extension().wstring();
            std::transform(extension.begin(), extension.end(), extension.begin(), ::towlower);

            // Filtraggio per estensioni supportate
            if (extension == L".jpg" || extension == L".png" || extension == L".jpeg") {
                processaImmagine(entry.path(), cartellaOutput, cartellaInput);
            }
        }
    }
}

int main() {
    // Input della cartella
    std::string nomeCartellaInput;
    cout << "Inserisci il percorso della cartella da analizzare: ";
    getline(cin, nomeCartellaInput);

    fs::path cartellaInput(nomeCartellaInput);
    fs::path cartellaOutput("output_immagini");

    if (!fs::exists(cartellaInput)) {
        cerr << "La cartella specificata non esiste." << endl;
        return -1;
    }

    // Processo la cartella
    processaCartella(cartellaInput, cartellaOutput);

    cout << "Elaborazione completata. Le immagini ritagliate sono salvate in " << cartellaOutput << endl;
    return 0;
}