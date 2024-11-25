% Specifico la cartella contenente le immagini e ne creo una per output se
% non esiste
folderPath = 'C:\Users\utente\OneDrive\Desktop\SPIR_esp_1609 - Copia\input_dataset';
outputFolder = fullfile(folderPath, 'output_dataset');
if ~exist(outputFolder, 'dir')
    mkdir(outputFolder);
end
if folderPath == 0
    error('Nessuna cartella selezionata.');
end

% Elenco delle immagini nella cartella
imageFiles = dir(fullfile(folderPath, '*.*'));
imageFiles = imageFiles(~[imageFiles.isdir]); % Esclude sottocartelle
if isempty(imageFiles)
    error('Nessuna immagine trovata nella cartella selezionata.');
end

% Debug: Mostra i nomi dei file trovati
disp('Immagini trovate:');
disp({imageFiles.name});

% Loop attraverso tutte le immagini
for i = 1:length(imageFiles)
    % Controlla se il file è un'immagine
    [~, ~, ext] = fileparts(imageFiles(i).name);
    if ~ismember(lower(ext), {'.png', '.jpg', '.jpeg', '.bmp', '.tif', '.tiff'})
        disp(['File non immagine ignorato: ', imageFiles(i).name]);
        continue;
    end
    
    % Carico l'immagine
    imagePath = fullfile(folderPath, imageFiles(i).name);
    img = imread(imagePath);
    
    % Mostro l'immagine e chiedi i punti
    figure;
    imshow(img);
    title(['Seleziona 3 punti per il triangolo e 1 per la curvatura: ', imageFiles(i).name]);
    
    % Aspetto che l'utente selezioni i punti
    disp('Seleziona i 3 punti del triangolo in senso orario o antiorario.');
    % Tre punti del triangolo
    [x, y] = ginput(3); 
    % Punto di curvatura
    disp('Seleziona il punto di curvatura.');
    [cx, cy] = ginput(1); 
    
    % Genero la curva tra il primo e il terzo punto
    t = linspace(0, 1, 100);
    curveX = (1-t).^2 * x(1) + 2*(1-t).*t * cx + t.^2 * x(3);
    curveY = (1-t).^2 * y(1) + 2*(1-t).*t * cy + t.^2 * y(3);
    
    % Combino i punti per creare la regione poligonale
    polyX = [curveX, x(2), x(1)];
    polyY = [curveY, y(2), y(1)];
    
    % Creo una maschera
    mask = poly2mask(polyX, polyY, size(img, 1), size(img, 2));
    
    % Applico la maschera all'immagine
    imgCropped = bsxfun(@times, img, cast(mask, 'like', img));
    
    % Salvataggio dell'immagine ritagliata
    outputName = fullfile(outputFolder, [imageFiles(i).name '_ritaglio_tri' ext]);
    imwrite(imgCropped, outputName);
    
    % Chiusura della figura
    close;
end

disp(['Ritaglio completato. Le immagini sono salvate in: ', outputFolder]);
