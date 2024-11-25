function visualize_sift_vpts1(folder)
    % INPUT:
    % - folder: la cartella contenente le immagini e i file dd.mat (keypoints SIFT)
   
    % Ottiengo tutte le immagini nella cartella
    images = dir(fullfile(folder, '*.png'));
    if isempty(images)
        error('Non ci sono immagini nella cartella specificata.');
    end
   
    % Loop attraverso tutte le immagini nella cartella
    for i = 1:length(images)
        % Leggi l'immagine
        img_path = fullfile(folder, images(i).name);
        img = imread(img_path);
        
        % Costruisco il percorso del file .mat corrispondente
        mat_file = fullfile(folder, 'dd.mat'); 

        % Controllo se il file .mat esiste
        if ~isfile(mat_file)
            warning('Il file %s non esiste. Passo all''immagine successiva.', mat_file);
            continue;
        end
        
        % Carico i dati dai file .mat
        data = load(mat_file);
        
        crop= [data.dd(i).I_crop];
        pt = [data.dd(i).vpts1.pt];
        scale = [data.dd(i).vpts1.size];
        orientation = [data.dd(i).vpts1.angle];

        % Visualizzo l'immagine
        figure;
        imshow(crop);
        hold on;
        
        % Ciclo su tutti i keypoints e traccia ogni punto
        for j = 1:length(data.dd(i).vpts1)
            % Estrazione delle coordinate x, y e la scala
            x = pt(2*j - 1); 
            y = pt(2*j);
            s = scale(j);
            o = orientation(j);
            
            % Visualizzo il keypoint come un cerchio
            viscircles([x, y], s, 'EdgeColor', 'g');
            
            % Tracciamento della direzione del keypoint (orientamento)
            quiver(x, y, cos(o), sin(o), s, 'Color', 'r');
        end
        
        title(sprintf('SIFT Features - Immagine: %s', images(i).name));
        hold off;
       
        pause;
    end
end