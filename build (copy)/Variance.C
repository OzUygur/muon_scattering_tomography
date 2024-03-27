#include <iostream>
#include <TFile.h>
#include <TTree.h>

int Variance() {
    // Open the ROOT file
    TFile file("your_file.root", "READ");

    // Check if the file is open
    if (!file.IsOpen()) {
        std::cerr << "Error: Could not open the ROOT file." << std::endl;
        return 1;
    }

    // Get the TTree from the file
    TTree* tree;
    file.GetObject("Data", tree);

    // Check if the TTree is retrieved
    if (!tree) {
        std::cerr << "Error: Could not find the specified TTree." << std::endl;
        file.Close();
        return 1;
    }

    // Check if the TTree has the specified branch
    if (!tree->GetBranch("your_variable_name")) {
        std::cerr << "Error: Could not find the specified variable in the TTree." << std::endl;
        file.Close();
        return 1;
    }

    // Variable to store the values from the TTree
    double variable_value;

    // Set the branch address
    tree->SetBranchAddress("X1", &X1);

    // Get the number of entries in the TTree
    Long64_t num_entries = tree->GetEntries();

    // Calculate the mean
    double mean = 0.0;
    for (Long64_t i = 0; i < num_entries; ++i) {
        tree->GetEntry(i);
        mean += variable_value;
    }
    mean /= num_entries;

    // Calculate the variance
    double variance = 0.0;
    for (Long64_t i = 0; i < num_entries; ++i) {
        tree->GetEntry(i);
        variance += pow(variable_value - mean, 2);
    }
    variance /= num_entries;

    // Print the results
    std::cout << "Mean: " << mean << ", Variance: " << variance << std::endl;

    // Close the file
    file.Close();

    return 0;
}

