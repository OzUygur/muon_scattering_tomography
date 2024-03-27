void MakeClass() {
    TFile *_file = TFile::Open("analiz.root");
    TTree* tree = (TTree*)_file->Get("Data"); // Replace with your actual tree name
    tree->MakeClass("Analiz");

}

