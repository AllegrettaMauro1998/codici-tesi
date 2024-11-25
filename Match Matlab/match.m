function match(folder)
    % Carico le due immagini croppate dai file .mat
    mat_file1 = fullfile(folder, 'dd.mat'); 
    mat_file2 = fullfile(folder, 'dd_models.mat'); 

    % Controllo se i file .mat esistono
    if ~isfile(mat_file1) || ~isfile(mat_file2)
        error('Uno o entrambi i file .mat non esistono.');
    end

    % Carico i dati dai filr .mat 
    data1 = load(mat_file1);
    data2 = load(mat_file2);

    % Estrai le immagini croppate
    crop1 = data1.dd.I_crop;
    crop2 = data2.dd_models.I_crop;

    % Converto le immagini in scala di grigi se necessario
    if size(crop1, 3) == 3
        crop1 = rgb2gray(crop1);
    end
    if size(crop2, 3) == 3
        crop2 = rgb2gray(crop2);
    end

    % Parametri per il matching
    tollerance = 25;  % Gradi massimi di divergenza nell'orientamento delle features
    thresh = 5;       % Valore MatchThreshold

    % Utilizzo SIFT per rilevare e descrivere i keypoints
    points1 = detectSIFTFeatures(crop1);  
    points2 = detectSIFTFeatures(crop2);  

    % Estraggo le caratteristiche dai due insiemi di keypoints
    [features1, valid_points1] = extractFeatures(crop1, points1);
    [features2, valid_points2] = extractFeatures(crop2, points2);

    % Effettuo il match delle caratteristiche con filtro sulla soglia
    indexPairs = matchFeatures(features1, features2, 'Unique', true, 'MatchThreshold', thresh);

    % Verifico se ci sono match trovati prima di procedere
    if isempty(indexPairs)
        warning('Nessun match trovato tra le due immagini.');
        return;
    end

    % Ottiengo i punti corrispondenti
    matchedPoints1 = valid_points1(indexPairs(:, 1));
    matchedPoints2 = valid_points2(indexPairs(:, 2));

    % Visualizzo i punti corrispondenti tra le due immagini croppate
    figure;
    showMatchedFeatures(crop1, crop2, matchedPoints1, matchedPoints2, 'montage');
    title('Punti corrispondenti tra le due immagini croppate');

    % Visualizzo i keypoints più forti della prima immagine
    figure;
    imshow(crop1);
    hold on;
    plot(points1.selectStrongest(50)); 
    title('Keypoints della Prima Immagine Croppata');
    hold off;

    % Visualizzo i keypoints più forti della seconda immagine
    figure;
    imshow(crop2);
    hold on;
    plot(points2.selectStrongest(50)); 
    title('Keypoints della Seconda Immagine Croppata');
    hold off;

    % Pausa per visualizzare i risultati
    pause;
end
