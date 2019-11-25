#include <iostream>
#include <random>
#include <chrono>

#define ARRAY_SIZE 50

using namespace std;

void populateArray(char *flips) {
    mt19937 gen(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<> distribution;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        flips[i] = distribution(gen) % 2;
    }
}

int main() {
    char *flips = new char[ARRAY_SIZE];
    int heads = 0, tails = 0;

    populateArray(flips);

    int hMax = 1, hMaxTemp = 1;
    int tMax = 1, tMaxTemp = 1;

    for (int j = 0; j < ARRAY_SIZE * sizeof(int); j++) {
        flips[j] == 0 ? heads++ : tails++;
        if (flips[j] == flips[j - 1]) {
            if (flips[j] == 0) {
                hMaxTemp++;
                tMaxTemp = 1;
            } else if (flips[j] == 1) {
                tMaxTemp++;
                hMaxTemp = 1;
            }
        } else {
            if (flips[j] == 0) {
                tMaxTemp = 1;
            } else if (flips[j] == 1) {
                hMaxTemp = 1;
            }
        }

        if (hMaxTemp > hMax) {
            hMax = hMaxTemp;
        } else if (tMaxTemp > tMax) {
            tMax = tMaxTemp;
        }
    }

    printf("%d %d \n", heads, tails);
    printf("%d %d \n", hMax, tMax);

    return 0;
}
