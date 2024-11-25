% Il percorso principale della cartella
Name = inputdlg('Inserisci il nome della cartella:', 'Input Nome Cartella');

% Controllo dell' input
if ~isempty(Name)
    % Costruzione il percorso relativo
    mainfolderPath = pwd;
    mainFolderPath = fullfile(mainfolderPath, Name{1});
end
% Ottiengo tutte le sottocartelle della cartella principale
subfolders = dir(mainFolderPath);
subfolders = subfolders([subfolders.isdir]);  
subfolders = subfolders(~ismember({subfolders.name}, {'.', '..'})); 

threshold = 60;  % Soglia per la maschera binaria
blackThreshold = 0.25;  % Soglia per i pixel neri (60%)
imageExtensions = {'*.jpg', '*.png'}; % Estensioni delle immagini da cercare

% Creo una figura principale per la visualizzazione delle immagini
hFig = uifigure('Name', 'Visualizzatore Immagini');

% Creo una finestra di dialogo per l'uscita con pulsante separato
exitDialog = uifigure('Name', 'Uscita', 'Position', [100 100 200 100]);
exitButton = uibutton(exitDialog, 'Text', 'Esci dal Programma', ...
    'Position', [25 25 150 50], ...
    'ButtonPushedFcn', @(btn,event) setappdata(exitDialog, 'Exit', true));

% Variabile di controllo per la chiusura
exitProgram = false;

% Itero su ogni sottocartella
for i = 1:numel(subfolders)
    folderPath = fullfile(mainFolderPath, subfolders(i).name);
    
    % Itero sulle estensioni delle immagini
    for extIdx = 1:numel(imageExtensions)
        images = dir(fullfile(folderPath, imageExtensions{extIdx}));
        
        % Itero su ciascuna immagine trovata
        for j = 1:numel(images)
            % Controllo se l'utente ha premuto il pulsante di uscita
            if isappdata(exitDialog, 'Exit') && getappdata(exitDialog, 'Exit')
                exitProgram = true;
                break;
            end
            
            imagePath = fullfile(folderPath, images(j).name);
            img = imread(imagePath);
             % Conversione dell'immagine in scala di grigi
            img_grey = rgb2gray(img); 
            
            % Creo una maschera binaria in base alla soglia
            binarymask = img_grey < threshold;  % Imposto i pixel neri sotto la soglia
            
            % Calcolo il numero totale di pixel e il numero di pixel neri
            totalpixels = numel(binarymask); 
            blackpixels = sum(binarymask(:)); 
            blackpresent = blackpixels / totalpixels; 

            % Debug: Visualizzazione dei valori calcolati
            fprintf('Immagine: %s, Percentuale di pixel neri: %.2f%%\n', images(j).name, blackpresent * 100);

            % Controllo se la percentuale di pixel neri è inferiore alla soglia
            if blackpresent < blackThreshold
                % Mostro l'immagine originale
                imshow(img);
                title(['Immagine: ' images(j).name]);

                % Chiedo all'utente se vuole croppare, passare o cancellare
                choice = uiconfirm(hFig, ...
                    'Vuoi croppare l''immagine, passare o cancellarla?', ...
                    'Seleziona opzione', ...
                    'Options', {'Croppa', 'Passa', 'Cancella'}, ...
                    'DefaultOption', 'Croppa');

                switch choice
                    case 'Croppa'
                        % Se l'utente sceglie di croppare, permette di selezionare un rettangolo
                        h = imrect;

                        % Creo un pulsante per confermare il crop
                        confirmButton = uicontrol('Style', 'pushbutton', 'String', 'Conferma Crop', ...
                           'Position', [150, 20, 100, 30], ... 
                           'Callback', 'uiresume(gcbf)');  % Callback per continuare il programma

                        % Aspetto che l'utente prema il pulsante di conferma
                        uiwait(hFig);

                        % Ottiengo la posizione del rettangolo selezionato
                        rectPos = getPosition(h);
                        
                        % Croppa l'immagine usando il rettangolo selezionato
                        croppedImg = imcrop(img, rectPos);

                        % Salvo l'immagine croppata con lo stesso nome dell'originale
                        imwrite(croppedImg, imagePath);
                        
                    case 'Passa'
                        % Non faccio nulla, semplicemente chiudi la finestra

                    case 'Cancella'
                        % Cancello il file immagine
                        delete(imagePath);
                        disp(['Immagine eliminata: ' images(j).name]);
                end
                close all;  % Chiudo tutte le finestre delle immagini
            else
                % Salta l'immagine se la percentuale di pixel neri è superiore alla soglia
                disp(['Immagine saltata (troppi pixel neri): ' images(j).name]);
            end
        end
        if exitProgram  % Controllo per uscire dai cicli
            break;
        end
    end
    if exitProgram  % Controllo per uscire dai cicli
        break;
    end
end

close all;  % Chiudo tutte le finestre
disp('Processo completato!');

