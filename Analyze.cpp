#include <iostream>
#include <cerrno>
#include <cstdlib>
#include <fstream>

#include "TApplication.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH2F.h"

using namespace std;

int main( int argc, char* argv[] )
{
    if( argc < 2 )
    {
        cerr << "arguments missing" << endl;
        cerr << "Usage : AnalyzeCT myFile.root " << endl;
        exit( EXIT_FAILURE );
    }

    // Store the root file name in 'fileName' variable
    char* const FILENAME = argv[ 1 ];

    TApplication app( "Application", &argc, argv );

    // Create and initialize a canvas
    TCanvas* canvas = new TCanvas( "Canvas BenchmarkCT", FILENAME, 200, 20, 1000, 700 );
    canvas->SetFillColor( 29 );
    canvas->ToggleToolBar();
    canvas->ToggleEventStatus();

    // Open (check) and read the root file
    TFile* file = new TFile( FILENAME );
    if( !file->IsOpen() )
    {
        cerr << "problem opening the root file : '" << FILENAME << "'" << endl;
        cerr << strerror( errno ) << endl;
        exit( EXIT_FAILURE );
    }

    // Take the single tree, where is the position, the energy and the runID
    TTree* singlesTree = (TTree*)file->Get( "Singles" );
    // Global Position in X, Y and Z
    Float_t globalPosX, globalPosY;
    singlesTree->SetBranchAddress( "globalPosX", &globalPosX );
    singlesTree->SetBranchAddress( "globalPosY", &globalPosY );

    // Number of entries in the single tree
    Int_t entriesSingleTree = (Int_t)singlesTree->GetEntries();
    cout << "Number of detected photons : " << entriesSingleTree << endl;

    // Create histogram for the first run
    // Define the bounds of the histogram
    Double_t const PIXELSIZE = 0.5;
    Int_t const RAW = 100;
    Int_t const COLUMN = 100;
    Double_t const RAW_BOUND = PIXELSIZE * RAW / 2;
    Double_t const COLUMN_BOUND = PIXELSIZE * COLUMN / 2;
    TH2F* run_0 = new TH2F( "runID = 0", "projection during the first run",
                            COLUMN, -COLUMN_BOUND, COLUMN_BOUND,
                            RAW, -RAW_BOUND, RAW_BOUND );

    for( Int_t i = 0; i != entriesSingleTree; ++i )
    {
        singlesTree->GetEntry( i );
        run_0->Fill( globalPosX, globalPosY );
    }

    // Draw the histogram on the canvas
    canvas->cd();
    run_0->Draw( "COLZ" );
    // Apri un file di testo per la scrittura
	ofstream outputFile("histogram_data.txt");

// Verifica se il file è stato aperto correttamente
	if (!outputFile.is_open()) {
    	cerr << "Errore nell'apertura del file di output." << endl;
    	exit(EXIT_FAILURE);
	}

// Loop per estrarre i valori dei bin dall'istogramma e scriverli nel file di testo
	for (int i = 1; i <= COLUMN; ++i) {
    	for (int j = 1; j <= RAW; ++j) {
        	outputFile << run_0->GetBinContent(i, j) << " ";
    	}
    	outputFile << endl; // Vai a capo dopo ogni riga
	}

// Chiudi il file di testo
	outputFile.close();

    app.Run();

    return 0;
}
