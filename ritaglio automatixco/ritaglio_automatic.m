% Funzione principale per il ritaglio automatico delle immagini
function automatic_crop(input_folder, output_folder)
    % Passo 1: Caricamento delle immagini dalla cartella di input
    images = dir(fullfile(input_folder, '*.png'));
    if isempty(images)
        disp('Nessuna immagine trovata nella cartella di input.');
        return;
    end
    
    % Creazione della cartella di output se non esiste
    if ~exist(output_folder, 'dir')
        mkdir(output_folder);
    end
    
    % Ciclo su tutte le immagini nella cartella di input
    for i = 1:length(images)
        % Caricamento dell'immagine
        img = imread(fullfile(input_folder, images(i).name));
        
        % Passo 2: Conversione in scala di grigi
        gray_img = rgb2gray(img);
        
        % Passo 3: Binarizzazione usando la soglia di Otsu
        level = graythresh(gray_img); % Calcolo della soglia di Otsu
        binary_img = imbinarize(gray_img, level); 
        
        % Passo 4: Pulizia dell'immagine con un'operazione di apertura
        se = strel('disk', 3); % Elemento strutturante di tipo disco con raggio 3
        clean_img = imopen(binary_img, se); % Rimozione del rumore
        
        % Passo 5: Identificazione della regione più ampia (la pinna)
        stats = regionprops(clean_img, 'BoundingBox', 'Area');
        if ~isempty(stats)
            % Troviamo la regione più grande
            [~, idx] = max([stats.Area]);
            bounding_box = stats(idx).BoundingBox;
            
            % Passo 6: Ritaglio dell'immagine
            % Aggiungiamo un margine di 3 pixel intorno alla regione individuata
            margin = 3;
            x1 = max(floor(bounding_box(1)) - margin, 1);
            y1 = max(floor(bounding_box(2)) - margin, 1);
            x2 = min(ceil(bounding_box(1) + bounding_box(3)) + margin, size(img, 2));
            y2 = min(ceil(bounding_box(2) + bounding_box(4)) + margin, size(img, 1));
            
            % Ritaglio dell'immagine originale con il margine
            cropped_img = img(y1:y2, x1:x2, :);
            
            % Passo 7: Salvataggio dell'immagine ritagliata nella cartella di output
            [~, img_name, ext] = fileparts(images(i).name);
            output_path = fullfile(output_folder, [img_name, '_cropped', ext]);
            imwrite(cropped_img, output_path);
            
            disp(['Immagine ritagliata e salvata: ', output_path]);
        else
            disp(['Nessuna regione trovata nell''immagine: ', images(i).name]);
        end
    end
end
