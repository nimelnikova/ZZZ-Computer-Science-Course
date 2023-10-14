#pragma once
#include <stdio.h>
#include <stdlib.h>

int Mod(int x, int y) {
    if (y != 0) {
        return x % y;
    } else {
        return 0;
    }
}

int Max(int x, int y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

int Min(int x, int y) {
    if (x < y) {
        return x;
    } else {
        return y;
    }
}

int Sign(int x) {
    if (x > 0) {
        return 1;
    }
    if (x < 0) {
        return -1;
    } else {
        return 0;
    }
}

int Abs(int x) {
    if (x > 0) {
        return x;
    } else {
        return x * (-1);
    }
}

const int x_0 = 10;
const int y_0 = 10;
const int rSmall = 5;
const int rBig = 10;
const int i_0 = -1;
const int j_0 = -1;
const int l_0 = -9;
const int ITERATIONS = 50;

typedef struct {
    int x;
    int y;
} Point;

int CheckZone(Point p) {
    int cord_x = p.x, cord_y = p.y;
    if (((cord_x - x_0) * (cord_x - x_0) + (cord_y - y_0) * (cord_y - y_0) <= rBig * rBig) &&
        ((cord_x - x_0) * (cord_x - x_0) + (cord_y - y_0) * (cord_y - y_0) >= rSmall * rSmall)) {
        return 1;
    } else {
        return 0;
    }
}

int Task() {
    int i = i_0;
    int j = j_0;
    int l = l_0;
    Point p;
    p.x = i;
    p.y = j;

    int countBelong = 0;  // Счетчик точек, принадлежащих зоне

    for (int k = 1; k <= ITERATIONS; ++k) {
        i = Max(p.y - k, l - k) % 30 + Max(p.x + l, p.y + k) % 20;
        j = (Abs(p.x - l) * Sign(p.y + k) + Abs(p.x - k) * (p.y + k)) % 20;
        l = ((p.x + k) * (p.y - k) * (l + k)) % 25;
        p.x = i;
        p.y = j;
        printf("k = %d, x = %d, y = %d, l = %d belong = %d \n", k, p.x, p.y, l, CheckZone(p));

        if (CheckZone(p)) {
            countBelong++;
        }
    }

    printf("Number of points belonging to the zone: %d\n", countBelong);

    return 0;
}
