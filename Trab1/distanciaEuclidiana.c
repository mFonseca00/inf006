#include <stdio.h>
#include <math.h>

struct Point {
    float x;
    float y;
};

float euclideanDistance(struct Point p1, struct Point p2) {
    return sqrtf(powf(p2.x - p1.x, 2) + powf(p2.y - p1.y, 2)); // Note o uso de sqrtf e powf
}

int main() {
    struct Point points[] = {
        {-8, 28}, {48, 33}, {7, 4}, {-11, 0}, {16, -20}, {46, -3}, {-20, 50}, {41, 40}, {38, -2}, {4, 30},
        {47, 47}, {36, 36}, {48, 12}, {16, 18}, {29, -20}, {3, 27}, {-15, 42}, {-15, 24}, {30, 7}
    };
    int numPoints = sizeof(points) / sizeof(points[0]);

    float totalDistance = 0;
    for (int i = 0; i < numPoints - 1; i++) {
        totalDistance += euclideanDistance(points[i], points[i + 1]);
    }

    printf("Distância euclidiana total (float): %f\n", totalDistance);
    return 0;
}