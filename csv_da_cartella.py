import os
import csv
from PIL import Image
import re

def leggi_massimo_pixel(cartella):
    massimo_pixel = 0
    for filename in os.listdir(cartella):
        if filename.endswith(".jpg"):
            path_file = os.path.join(cartella, filename)
            try:
                with Image.open(path_file) as img:
                    extrema = img.getextrema()
                    if isinstance(extrema, tuple) and len(extrema) == 2:
                        # Per immagini in scala di grigi, extrema sarà (min, max)    88 e 97
                        massimo_pixel = max(massimo_pixel, extrema[1])
                    else:
                        # Per immagini a colori o altri formati
                        massimo_pixel = max(massimo_pixel, max(max(e) for e in extrema))
            except Exception as e:
                print(f"Errore nell'aprire l'immagine {filename}: {e}")
    return massimo_pixel

def crea_csv_da_cartella(cartella):
    if not os.path.exists(cartella):
        print(f"La cartella {cartella} non esiste.")
        return

    file_list = []
    for filename in os.listdir(cartella):
        if filename.endswith(".jpg"):
            file_list.append(filename)

    # Ordinare la lista dei file usando il primo numero trovato nel nome del file
    file_list.sort(key=lambda x: float(re.search(r'\d+\.*\d*', x).group()) if re.search(r'\d+\.*\d*', x) else 0)

    massimo_pixel = leggi_massimo_pixel(cartella)

    output_file_path = os.path.join(cartella, 'output.csv')

    try:
        with open(output_file_path, mode='w', newline='') as file:
            writer = csv.writer(file, delimiter=',', lineterminator='\n', quoting=csv.QUOTE_MINIMAL, quotechar='"', escapechar='\\', doublequote=True, skipinitialspace=False)

            for filename in file_list:
                nome_file = filename
                angolo = float(re.search(r'\d+\.*\d*', filename).group()) if re.search(r'\d+\.*\d*', filename) else 0
                valore1 = '65'
                valore2 = '65'
                writer.writerow([nome_file, angolo, valore1, valore2, massimo_pixel, '1'])
    except Exception as e:
        print(f"Errore nella scrittura del file CSV: {e}")
    print("Done")

crea_csv_da_cartella('C:/Users/Marco/OneDrive/Desktop/New_folder_img')
