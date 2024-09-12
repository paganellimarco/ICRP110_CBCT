import os
from PIL import Image

def text_to_image(input_file, output_file):
    # Leggi il file di testo
    with open(input_file, 'r') as file:
        lines = file.readlines()

    # Crea un'immagine vuota 200x200 pixel in scala di grigi
    image = Image.new('L', (200, 200))

    # Converti i numeri nel file di testo in pixel dell'immagine
    for y, line in enumerate(lines):
        values = line.strip().split()[:200]  # Considera solo i primi 200 numeri per riga
        for x, value in enumerate(values):
                image.putpixel((x, y), int(value))

    # Salva l'immagine come file JPEG
    image.save(output_file)

# Cartella di input
input_folder = r'E:/marco/unipv/tesi/output'

# Ciclo su tutti i file .txt nella cartella di input
for filename in os.listdir(input_folder):
    if filename.endswith('.txt'):
        input_file = os.path.join(input_folder, filename)
        output_file = os.path.join(input_folder, f"{os.path.splitext(filename)[0]}.jpg")
        text_to_image(input_file, output_file)
