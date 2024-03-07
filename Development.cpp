// Development.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "RandomUtils.hpp"
#include "DiffusionBlackScholes.hpp"
#include "Pricer.hpp"


static void testBlackScholesSdeFormulaDiscretized() {
    double mu = 0.05;
    double sigma = 0.2;
    double T = 0.5;
    long N = 126;
    BlackScholes bs(mu, sigma);

    long normalsLen = 50000;
    double* normals = new double[normalsLen];
    for (int i = 0; i < normalsLen; ++i) {
        double* spots = new double[N];
        double* randoms = new double[N - 1];
        normalDistritor(randoms, N - 1);
        double spot_T = bs.diffuseUnderlying(spots, N, randoms, N - 1, T / N);
        normals[i] = bs.reverseLogNormalFunction(T, spot_T);
        delete[] spots;
        delete[] randoms;
    }

    quickSort(normals, 0, normalsLen - 1);

    double _mean = mean(normals, normalsLen);
    double _variance = variance(normals, normalsLen);
    double maxDistance = kolmogorovSmirnov(normals, normalsLen);
    double andersonD = andersonDarling(normals, normalsLen);

    std::cout << "mean : " << _mean << std::endl;
    std::cout << "variance : " << _variance << std::endl;
    std::cout << "KS distance : " << maxDistance << std::endl;
    std::cout << "AD measure : " << andersonD << std::endl;

    delete[] normals;
}

static void testEuropeanCallPriceLikelihood() {
    double mu = 0.05;
    double sigma = 0.2;
    double S0 = 1.;
    double K = 1.1;
    double T = 0.5;
    long sampleLen = 100000;
    long timeSteps = 1;
    DiffusionBlackScholes bs(mu, sigma);
    EuropeanCall call(K, T);
    double* payoffs = new double[sampleLen];
    MonteCarlo(payoffs, sampleLen, bs, call, timeSteps);

    double theoPrice = bs.europeanCallPayoffMean(S0, K, T);
    double meanSquareError = std::sqrt(bs.europeanCallPayoffVariance(S0, K, T));
    double empiricMean = mean(payoffs, sampleLen);
    double Z = std::sqrt(sampleLen) * (empiricMean - theoPrice) / meanSquareError; // central limit

    std::cout << "monte carlo price : " << empiricMean << std::endl;
    std::cout << "theorical price : " << theoPrice << std::endl;
    std::cout << "central limit normalized : " << Z << std::endl;
    std::cout << "proba of empirical values given theo : " << normalProba(Z) << std::endl;

    delete[] payoffs;
}

int main() {

    //testBlackScholesSdeFormulaDiscretized();
    testEuropeanCallPriceLikelihood();
    
    return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
