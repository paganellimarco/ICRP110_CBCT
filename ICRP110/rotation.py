import subprocess

# Percorso del file da modificare
file_path = '../src/ICRP110PhantomConstruction.cc'
analysis_path = '../src/ICRP110PhantomAnalysisManager.cc'

#for angle in range(4):
for angle in [0, 45, 90, 180, 270]:
    # Legge il contenuto del file ICRP110PhantomConstruction.cc
    with open(file_path, 'r') as file:
        lines = file.readlines()

    # Modifica la linea desiderata
    for i, line in enumerate(lines):
        if "rotCylinder->rotateZ(" in line:
            lines[i] = f'rotCylinder->rotateZ({angle} * deg); // Modified rotation\n'
            break

    # Sovrascrive il file con la nuova rotazione
    with open(file_path, 'w') as file:
        file.writelines(lines)
        
    # Legge il file di analisi
    with open(analysis_path, 'r') as file:
        lines = file.readlines()

    # Modifica il file di analisi per cambiare il nome del file output.root
    updated = False
    for i, line in enumerate(lines):
        if 'new TFile(' in line and 'output_' in line and '.root' in line:
            lines[i] = f'TFile* file = new TFile("output_{angle}.root", "RECREATE");\n'
            updated = True
            break

    # Se non viene trovata la linea da aggiornare, cerca la stringa originale
    if not updated:
        for i, line in enumerate(lines):
            if 'new TFile("output.root"' in line:
                lines[i] = f'TFile* file = new TFile("output_{angle}.root", "RECREATE");\n'
                break

    # Sovrascrive il file di analisi con la nuova riga
    with open(analysis_path, 'w') as file:
        file.writelines(lines)
    
    # Compila il codice modificato con make
    print(f"Compiling for rotation {angle} degrees...")
    subprocess.run(["make"], check=True)

    # Esegue la simulazione con il file macro
    print(f"Running simulation for rotation {angle} degrees...")
    subprocess.run(["./ICRP110phantoms", "run.mac"], check=True)

