// Development.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Utils.hpp"
#include "DiffusionBlackScholes.hpp"
#include "Pricer.hpp"
#include "RandomUniformTore.hpp"
#include "RandomUniformLCG.hpp"
#include "RandomNormalMoro.hpp"

void testUniformGenerators(RandomUniform &generator) {
    long n = 1000;
    double* uniforms = new double[n];
    double* modules = new double[n];
    double* phases = new double[n];
    double* diffs = new double[n];
    generator.generateArray(uniforms, n);
    discretFourierTransform(modules, phases, uniforms, n);
    long maxModuleInd = 1;
    double maxModule = 0.;
    for (long i = maxModuleInd; i < n; ++i) {
        if (modules[i] > maxModule) {
            maxModuleInd = i;
            maxModule = modules[i];
        }
    }
    quickSort(uniforms, 0, n - 1);
    double _mean = mean(uniforms, n);
    double _variance = variance(uniforms, n);
    generator.kolmogorovSmirnov(diffs, n, uniforms);
    double maxDistance = max(diffs, n);
    std::cout << "Uniform law [0;1] test metrics :" << std::endl;
    std::cout << "mean : " << _mean << std::endl;
    std::cout << "variance : " << _variance << std::endl;
    std::cout << "kolmogorov.s distance : " << maxDistance << std::endl;
    std::cout << "discret fourier transform : frequance: " << maxModuleInd << "; module: " << maxModule << "\n" << std::endl;
    generator.initialize();

    delete[] uniforms;
    delete[] modules;
    delete[] phases;
    delete[] diffs;

    double mu = 0.05;
    double sigma = 0.2;
    double S0 = 1.;
    double T = 0.5;
    double K = 1.1;
    EuropeanCall call(K, T);
    long N = std::ceil(252. * call.T / (double)1);;
    double dt = call.T / (double)N;
    
    DiffusionBlackScholes bs(mu, sigma);
    RandomNormalMoro moro(generator);

    long normalsLen = 10000;
    double* spots = new double[N + 1];
    double* normals = new double[normalsLen];
    double* payoffs = new double[normalsLen];
    double* randoms = new double[N * normalsLen];
    moro.generateArray(randoms, N * normalsLen);
    for (int i = 0; i < normalsLen; ++i) {
        double spot_T = bs.diffuseUnderlying(spots, randoms, N, i * N, dt);
        payoffs[i] = call.payoffDiscounted(spots, N + 1, bs.drift(spot_T, call.T));
        normals[i] = bs.reverseLogNormalFunction(T, spot_T);
    }
    delete[] spots;

    double* theodiffs = new double[normalsLen];
    quickSort(normals, 0, normalsLen - 1);
    _mean = mean(normals, normalsLen);
    _variance = variance(normals, normalsLen);
    moro.kolmogorovSmirnov(theodiffs, normalsLen, normals);
    maxDistance = max(theodiffs, normalsLen);
    std::cout << "Log normal diffused spot at T reversed to normal :" << std::endl;
    std::cout << "mean : " << _mean << std::endl;
    std::cout << "variance : " << _variance << std::endl;
    std::cout << "kolmogorov.s distance : " << maxDistance << "\n" << std::endl;
    delete[] theodiffs;

    double theoPrice = bs.europeanCallPayoffMean(S0, K, T);
    double meanSquareError = std::sqrt(bs.europeanCallPayoffVariance(S0, K, T));
    double empiricMean = mean(payoffs, normalsLen);
    double Z = std::sqrt(normalsLen) * (empiricMean - theoPrice) / meanSquareError;
    std::cout << "MC price vs theo price :" << std::endl;
    std::cout << "monte carlo price : " << empiricMean << std::endl;
    std::cout << "theorical price : " << theoPrice << std::endl;
    std::cout << "central limit normalized : " << Z << std::endl;
    std::cout << "proba of empirical values given theo : " << moro.probability(Z) << std::endl;

    delete[] normals;
    delete[] randoms;
    delete[] payoffs;
}

int main() {

    RandomUniformLCG lcg(10);
    RandomUniformTore tore(19);
    RandomUniformTore shuffledTore(19, &lcg);

    testUniformGenerators(shuffledTore);

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
