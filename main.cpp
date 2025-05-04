#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <memory>

struct Point { double x, y; };

// --- Formation Helpers ---
std::vector<Point> generateCircle(int n, double R) {
    std::vector<Point> v; v.reserve(n);
    for (int i = 0; i < n; ++i) {
        double θ = 2*M_PI*i/n;
        v.push_back({ R*cos(θ), R*sin(θ) });
    }
    return v;
}

std::vector<Point> generateTriangle(int n, double side) {
    Point A{0,0}, B{side,0}, C{side/2, side*std::sqrt(3)/2};
    double perim = 3*side;
    std::vector<Point> v; v.reserve(n);
    for (int i = 0; i < n; ++i) {
        double d = perim*i/n, t;
        if (d < side) {
            t = d/side;
            v.push_back({ A.x+t*(B.x-A.x), A.y+t*(B.y-A.y) });
        }
        else if (d < 2*side) {
            t = (d-side)/side;
            v.push_back({ B.x+t*(C.x-B.x), B.y+t*(C.y-B.y) });
        }
        else {
            t = (d-2*side)/side;
            v.push_back({ C.x+t*(A.x-C.x), C.y+t*(A.y-C.y) });
        }
    }
    return v;
}

std::vector<Point> generateRectangle(int n, double w, double h) {
    double perim = 2*(w+h);
    std::vector<Point> v; v.reserve(n);
    for (int i = 0; i < n; ++i) {
        double d = perim*i/n;
        if (d < w)
            v.push_back({ d, 0 });
        else if (d < w+h)
            v.push_back({ w, d-w });
        else if (d < 2*w+h)
            v.push_back({ w-(d-(w+h)), h });
        else
            v.push_back({ 0, h-(d-(2*w+h)) });
    }
    return v;
}

// --- main() ---
int main() {
    const int   n       = 10;
    const double R      = 5.0;
    const double side   = 10.0;
    const double width  = 12.0;
    const double height =  6.0;

    auto circle    = generateCircle(n, R);
    auto triangle  = generateTriangle(n, side);
    auto rectangle = generateRectangle(n, width, height);

    std::cout << "=== Circle Formation ===\n";
    for (int i = 0; i < n; ++i)
        std::cout << "Drone " << i << ": ("
                  << circle[i].x << ", " << circle[i].y << ")\n";

    std::cout << "\n=== Triangle Formation ===\n";
    for (int i = 0; i < n; ++i)
        std::cout << "Drone " << i << ": ("
                  << triangle[i].x << ", " << triangle[i].y << ")\n";

    std::cout << "\n=== Rectangle Formation ===\n";
    for (int i = 0; i < n; ++i)
        std::cout << "Drone " << i << ": ("
                  << rectangle[i].x << ", " << rectangle[i].y << ")\n";

    return 0;
}
