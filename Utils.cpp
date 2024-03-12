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

double max(double values[], long valuesLen) {
    double max = 0.;
    for (long i = 0; i < valuesLen; ++i) {
        if (values[i] > max) {
            max = values[i];
        }
    }
    return max;
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

long firstInfIndex(double ascendingTable[], long ascendingTableLen, double value) {
    long high = ascendingTableLen - 1;
    if (value > ascendingTable[high]) return high;
    long low = 0;
    
    while (true) {
        if (low > high - 2) break;
        long mid = (high + low) / 2;
        if (value < ascendingTable[mid]) {
            high = mid;
        }
        else {
            low = mid;
        }
    }
    return  low;
}

#define PI 3.14159265358979323846

class Complex {
public:
    double x;
    double y;

    Complex(double theta) {
        x = cos(theta);
        y = sin(theta);
    }

    Complex(double _x, double _y) {
        x = _x;
        y = _y;
    }

    static Complex object(double theta) {
        Complex result(theta);
        return result;
    }

    static Complex object(double _x, double _y) {
        Complex result(_x, _y);
        return result;
    }

    double angle() {
        return x == 0. ? PI * 0.5 * (1 - 2 * int(y < 0.)) : atan(y / x) + int(x < 0.) * PI;
    }

    double module() {
        return sqrt(x * x + y * y);
    }

    Complex operator+(const Complex& other) const {
        return object(x + other.x, y + other.y);
    }

    Complex operator+(double term) const {
        return object(x + term, y);
    }

    Complex operator*(const Complex& other) const {
        return object(x * other.x - y * other.y, x * other.y + y * other.x);
    }

    Complex operator*(double factor) const {
        return object(x * factor, y * factor);
    }
};

void discretFourierTransform(double modules[], double angles[], double signals[], long signalsLen) {
    for (long i = 0; i < signalsLen; ++i) {
        Complex c(0., 0.);
        for (long j = 0; j < signalsLen; ++j) {
            c = c + Complex::object(-2 * PI * i * j / signalsLen) * signals[j];
        }
        modules[i] = c.module();
        angles[i] = c.angle();
    }
}
