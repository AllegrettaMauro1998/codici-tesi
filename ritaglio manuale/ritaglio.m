% Specifico la cartella principale
mainFolder = 'C:\Users\utente\OneDrive\Desktop\SPIR_esp_1609\input_dataset';

% Carico le immagini con estensione .jpg e .png direttamente nella cartella principale
imgFiles = [dir(fullfile(mainFolder, '*.jpg')); dir(fullfile(mainFolder, '*.png'))];

% Itera attraverso i file immagine trovati nella cartella principale
for j = 1:length(imgFiles)
    imgPath = fullfile(mainFolder, imgFiles(j).name);
    
    % Carico l'immagine
    img = imread(imgPath);
    figure; imshow(img);
    title('Clicca per creare i vertici del poligono. Doppio click per chiudere.');
    
    % Disegno il poligono interattivo
    h = drawpolygon('LineWidth', 2, 'Color', 'r');
    
    % Ottengo le coordinate dei vertici
    vertices = h.Position;
    
    % Creo una maschera logica (binaria) delle stesse dimensioni dell'immagine
    mask = poly2mask(vertices(:,1), vertices(:,2), size(img,1), size(img,2));
    
    % Visualizzo la maschera
    figure;
    imshow(mask);
    title('Maschera binaria del poligono');
    
    % Uso la maschera per estrarre l'area interna del poligono
    % Creo un'immagine vuota (nera) delle stesse dimensioni dell'originale
    img_masked = zeros(size(img), 'like', img);
    
    % Copia i pixel dell'immagine originale solo dove la maschera è vera
    for c = 1:size(img,3)
        img_masked(:,:,c) = img(:,:,c) .* uint8(mask);
    end
    
    % Visualizzo l'immagine ritagliata
    figure;
    imshow(img_masked);
    title('Immagine con solo la parte interna del poligono');
    
    % Estraggp il nome del file senza estensione
    [~, imgName, ~] = fileparts(imgFiles(j).name);
    
    % Salvataggio dell'immagine ritagliata come file PNG nella stessa cartella principale
    imwrite(img_masked, fullfile(mainFolder, [imgName, '_masked.png']));
end