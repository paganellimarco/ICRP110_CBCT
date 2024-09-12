import os
import re
import uproot
import numpy as np
from PIL import Image

def root_hist_to_image(input_file, output_file, hist_name):
    # Apri il file ROOT e accedi all'istogramma 2D
    with uproot.open(input_file) as file:
        hist = file[hist_name]

        # Ottieni i dati dell'istogramma come un array NumPy
        values = hist.values()

        # Creazione di un'immagine per visualizzazione migliorata con scala logaritmica
        log_scaled_values = np.log1p(values)  # Usa log(1 + x) per evitare log(0)
        log_scaled_values = (log_scaled_values / np.max(log_scaled_values)) * 255  # Scala tra 0 e 255

        # Crea un'immagine dall'array normalizzato
        image = Image.fromarray(log_scaled_values.astype(np.uint8), mode='L')

        # Salva l'immagine come file JPEG
        image.save(output_file)

# Cartella di input (modifica questa variabile con il percorso della tua cartella contenente i file ROOT)
input_folder = r'C:/Users/Marco/OneDrive/Desktop/New_folder_root/New_folder_1'  # Modifica con il percorso della tua cartella contenente i file ROOT

# Cartella di output (modifica questa variabile con il percorso della tua cartella di output)
output_folder = r'C:/Users/Marco/OneDrive/Desktop/New_folder_img'  # Modifica con il percorso della tua cartella di output preesistente

# Nome dell'istogramma da estrarre (modifica questa variabile con il nome del tuo istogramma)
histogram_name = 'PhotonPosition'  # Modifica con il nome corretto dell'istogramma 2D nel file ROOT

# Controlla se la cartella di output esiste
if not os.path.exists(output_folder):
    print(f"Errore: La cartella di output '{output_folder}' non esiste.")
else:
    # Ciclo su tutti i file .root nella cartella di input
    for filename in os.listdir(input_folder):
        if filename.endswith('.root'):
            # Estrai il numero 'n' dal nome del file (es. output_n.root)
            match = re.match(r'output_(\d+).root', filename)
            if match:
                n = match.group(1)  # Ottiene il numero "n" dal nome del file
                input_file = os.path.join(input_folder, filename)
                output_file = os.path.join(output_folder, f"{n}.jpg")
                root_hist_to_image(input_file, output_file, histogram_name)

    print("Conversione completata!")
