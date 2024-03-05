#include <random>
#include <cmath>

void swap(double& a, double& b) {
    double temp = a;
    a = b;
    b = temp;
}

int partition(double arr[], long low, long high) {
    double pivot = arr[high];
    long i = low - 1;

    for (long j = low; j <= high - 1; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(double arr[], long low, long high) {
    if (low < high) {
        long pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void normalDistritor(double values[], long valuesLen) {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::normal_distribution<double> distribution(0.0, 1.0);

    for (long i = 0; i < valuesLen; ++i) {
        values[i] = distribution(engine);
    }
}

double normalProba(double x) {
    return 0.5 * (1 + std::erf(x / std::sqrt(2.0)));
}

double kolmogorovSmirnov(double empiricPoints[], long empiricPointsLen) {
    double maxDistance = 0;
    double empiricLen = (double)empiricPointsLen;
    for (long i = 0; i < empiricPointsLen; ++i) {
        double scaleDistance = std::abs(normalProba(empiricPoints[i]) - (i + 1) / empiricLen);
        if (scaleDistance > maxDistance) {
            maxDistance = scaleDistance;
        }
    }
    return maxDistance;
}

double andersonDarling(double values[], long valuesLen) {
    double somme = 0.;
    for (long i = 1; i < valuesLen + 1; ++i) {
        somme += (2 * i - 1) * (std::log(normalProba(values[i - 1])) + std::log(1 - normalProba(values[valuesLen - i])));
    }

    return -(double)valuesLen - somme / valuesLen;
}

double sum(double values[], long valuesLen) {
    double sum = 0.;
    for (long i = 0; i < valuesLen; ++i) {
        sum += values[i];
    }
    return sum;
}

double mean(double values[], long valuesLen) {
    return sum(values, valuesLen) / valuesLen;
}

double meanSquare(double values[], long valuesLen) {
    double sum = 0.;
    for (long i = 0; i < valuesLen; ++i) {
        sum += values[i] * values[i];
    }
    return sum / valuesLen;
}

double variance(double values[], long valuesLen) {
    double _mean = mean(values, valuesLen);
    return meanSquare(values, valuesLen) - _mean * _mean;
}