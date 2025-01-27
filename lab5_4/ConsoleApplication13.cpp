#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>

using namespace cv;

// Оптимизированный алгоритм Брезенхэма для рисования линии
void Line(Mat& image, int x1, int y1, int x2, int y2, Vec3b color) {
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        if (x1 >= 0 && x1 < image.cols && y1 >= 0 && y1 < image.rows) {
            image.at<Vec3b>(y1, x1) = color;
        }
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

std::vector<double> getNormalVector(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3) {
    double nx = (y2 - y1) * (z3 - z1) - (z2 - z1) * (y3 - y1);
    double ny = -((x2 - x1) * (z3 - z1) - (z2 - z1) * (x3 - x1));
    double nz = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
    return std::vector<double>{nx, ny, nz};
}

std::vector<std::vector<double>> getPerspectiveTransformation(std::vector<double> pointsX, std::vector<double> pointsY, std::vector<double> pointsZ, int k) {
    double r = 1.0 / k;
    std::vector<std::vector<double>> result = { pointsX, pointsY, pointsZ };
    for (int i = 0; i < pointsX.size(); i++) {
        if (pointsZ[i] * r + 1 == 0) {
            continue;
        }
        result[0][i] = pointsX[i] / (pointsZ[i] * r + 1);
        result[1][i] = pointsY[i] / (pointsZ[i] * r + 1);
        result[2][i] = pointsZ[i] / (pointsZ[i] * r + 1);
    }
    return result;
}

std::vector<std::vector<double>> getPerspectiveProjection(std::vector<double> pointsXTransformed, std::vector<double> pointsYTransformed) {
    return std::vector<std::vector<double>>{pointsXTransformed, pointsYTransformed};
}

std::vector<std::vector<double>> getParallelProjection(std::vector<double> pointsX, std::vector<double> pointsY, std::vector<double> pointsZ) {
    return std::vector<std::vector<double>>{pointsX, pointsY};
}

std::vector<std::vector<int>> getFigureFaces() {
    std::vector<std::vector<int>> faces = { {0, 1, 2, 3},
                                           {7, 6, 5, 4},
                                           {3, 2, 6, 7},
                                           {4, 5, 1, 0},
                                           {1, 5, 6, 2},
                                           {4, 0, 3, 7} };
    return faces;
}

double getScalarProduct(std::vector<double> vector1, std::vector<double> vector2) {
    double result = 0;
    for (int i = 0; i < vector1.size(); ++i) {
        result += vector1[i] * vector2[i];
    }
    return result;
}

std::vector<double> getFigureCenter(std::vector<double> pointsX, std::vector<double> pointsY) {
    if (pointsX.empty() || pointsY.empty()) {
        return std::vector<double>{0, 0};
    }
    double resultX = 0;
    double resultY = 0;
    for (int i = 0; i < pointsX.size(); ++i) {
        resultX += pointsX[i];
        resultY += pointsY[i];
    }
    return std::vector<double>{resultX / pointsX.size(), resultY / pointsY.size()};
}

std::vector<double> getImageCenter(Mat& image) {
    return std::vector<double>{double(image.cols) / 2.0, double(image.rows) / 2.0};
}

enum ProjectionType {
    Parallel,
    Persepective
};

void drawProjection(Mat& image, std::vector<double> pointsX, std::vector<double> pointsY, std::vector<double> pointsZ, std::vector<double> viewDirection, ProjectionType type, int k = 500) {
    std::vector<std::vector<int>> faces = getFigureFaces();
    std::vector<double> imageCenter = getImageCenter(image);

    if (type == Parallel) {
        for (int i = 0; i < faces.size(); ++i) {
            std::vector<double> normalVector = getNormalVector(pointsX[faces[i][0]], pointsY[faces[i][0]], pointsZ[faces[i][0]],
                pointsX[faces[i][1]], pointsY[faces[i][1]], pointsZ[faces[i][1]],
                pointsX[faces[i][2]], pointsY[faces[i][2]], pointsZ[faces[i][2]]);
            if (getScalarProduct(normalVector, viewDirection) < 0) continue;

            std::vector<std::vector<double>> pointsProjected = getParallelProjection(pointsX, pointsY, pointsZ);
            std::vector<double> pointsXProjected = pointsProjected[0];
            std::vector<double> pointsYProjected = pointsProjected[1];
            std::vector<double> figureCenter = getFigureCenter(pointsXProjected, pointsYProjected);

            for (int j = 0; j < faces[i].size(); ++j) {
                int x1 = static_cast<int>(pointsXProjected[faces[i][j]] + imageCenter[0] - figureCenter[0]);
                int y1 = static_cast<int>(pointsYProjected[faces[i][j]] + imageCenter[1] - figureCenter[1]);
                int x2 = static_cast<int>(pointsXProjected[faces[i][(j + 1) % faces[i].size()]] + imageCenter[0] - figureCenter[0]);
                int y2 = static_cast<int>(pointsYProjected[faces[i][(j + 1) % faces[i].size()]] + imageCenter[1] - figureCenter[1]);
                Line(image, x1, y1, x2, y2, Vec3b(0, 0, 0));
            }
        }
    }
    else {
        std::vector<std::vector<double>> pointsTransformed = getPerspectiveTransformation(pointsX, pointsY, pointsZ, k);
        std::vector<double> pointsXTransformed = pointsTransformed[0];
        std::vector<double> pointsYTransformed = pointsTransformed[1];
        std::vector<double> pointsZTransformed = pointsTransformed[2];
        for (int i = 0; i < faces.size(); ++i) {
            std::vector<double> normalVector = getNormalVector(pointsXTransformed[faces[i][0]], pointsYTransformed[faces[i][0]], pointsZTransformed[faces[i][0]],
                pointsXTransformed[faces[i][1]], pointsYTransformed[faces[i][1]], pointsZTransformed[faces[i][1]],
                pointsXTransformed[faces[i][2]], pointsYTransformed[faces[i][2]], pointsZTransformed[faces[i][2]]);
            if (getScalarProduct(normalVector, viewDirection) < 0) continue;

            std::vector<std::vector<double>> pointsProjected = getPerspectiveProjection(pointsXTransformed, pointsYTransformed);
            std::vector<double> pointsXProjected = pointsProjected[0];
            std::vector<double> pointsYProjected = pointsProjected[1];
            std::vector<double> figureCenter = getFigureCenter(pointsXProjected, pointsYProjected);

            for (int j = 0; j < faces[i].size(); ++j) {
                int x1 = static_cast<int>(pointsXProjected[faces[i][j]] + imageCenter[0] - figureCenter[0]);
                int y1 = static_cast<int>(pointsYProjected[faces[i][j]] + imageCenter[1] - figureCenter[1]);
                int x2 = static_cast<int>(pointsXProjected[faces[i][(j + 1) % faces[i].size()]] + imageCenter[0] - figureCenter[0]);
                int y2 = static_cast<int>(pointsYProjected[faces[i][(j + 1) % faces[i].size()]] + imageCenter[1] - figureCenter[1]);
                Line(image, x1, y1, x2, y2, Vec3b(0, 0, 0));
            }
        }
    }
}

std::vector<double> Normalize(std::vector<double> vector) {
    double norm = 0;
    for (int i = 0; i < vector.size(); ++i) {
        norm += vector[i] * vector[i];
    }
    if (norm == 0) return vector;
    norm = sqrt(norm);
    for (int i = 0; i < vector.size(); ++i) {
        vector[i] /= norm;
    }
    return vector;
}

std::vector<std::vector<double>> Rotate(std::vector<double> pointsX, std::vector<double> pointsY, std::vector<double> pointsZ, std::vector<double> axis, int angle) {
    double phi = angle * CV_PI / 180;
    double cosine = std::cos(phi);
    double sine = std::sin(phi);

    double ux = axis[0];
    double uy = axis[1];
    double uz = axis[2];

    std::vector<std::vector<double>> result(3, std::vector<double>(pointsX.size()));

    for (size_t i = 0; i < pointsX.size(); ++i) {
        double x = pointsX[i];
        double y = pointsY[i];
        double z = pointsZ[i];

        result[0][i] = (cosine + ux * ux * (1 - cosine)) * x + (ux * uy * (1 - cosine) - uz * sine) * y + (ux * uz * (1 - cosine) + uy * sine) * z;
        result[1][i] = (ux * uy * (1 - cosine) + uz * sine) * x + (cosine + uy * uy * (1 - cosine)) * y + (uy * uz * (1 - cosine) - ux * sine) * z;
        result[2][i] = (ux * uz * (1 - cosine) - uy * sine) * x + (uy * uz * (1 - cosine) + ux * sine) * y + (cosine + uz * uz * (1 - cosine)) * z;
    }
    return result;
}

void animateRotation(Mat& image, int frames, VideoWriter writer, std::vector<double> pointsX, std::vector<double> pointsY, std::vector<double> pointsZ, std::vector<double> axis, int angle, ProjectionType type, int k = 500) {
    axis = Normalize(axis);
    for (int i = 0; i < frames; ++i) {
        image.setTo(Scalar(255, 255, 255));
        drawProjection(image, pointsX, pointsY, pointsZ, std::vector<double>({ 0, 0, -1 }), type, k);
        writer.write(image);
        std::vector<std::vector<double>> result = Rotate(pointsX, pointsY, pointsZ, axis, angle);
        pointsX = result[0];
        pointsY = result[1];
        pointsZ = result[2];
        std::cout << "Progress: " << (i + 1) << "/" << frames << "\r";
    }
    std::cout << std::endl << "Video generation finished" << std::endl;
    writer.release();
}

int main() {
    int width = 800;
    int height = 600;
    Mat image(height, width, CV_8UC3);
    image.setTo(Scalar(255, 255, 255));

    std::string filename_perspective = "../animation_perspective.mp4";
    std::string filename_parallel = "../animation_parallel.mp4";
    int fourcc = VideoWriter::fourcc('a', 'v', 'c', '1');
    double fps = 60.0;

    VideoWriter writer_perspective(filename_perspective, fourcc, fps, image.size());
    VideoWriter writer_parallel(filename_parallel, fourcc, fps, image.size());

    if (!writer_perspective.isOpened() || !writer_parallel.isOpened()) {
        std::cerr << "Error: Could not open video file for writing.\n";
        return -1;
    }

    std::vector<double> pointsX = { -100, 100, 100, -100, -100, 100, 100, -100 };
    std::vector<double> pointsY = { -100, -100, 100, 100, -100, -100, 100, 100 };
    std::vector<double> pointsZ = { -100, -100, -100, -100, 100, 100, 100, 100 };


    int frames = 120;
    std::vector<double> axis = { 1, -0.5, 0 };
    int angle = 3;

    // Анимация перспективной проекции
    animateRotation(image, frames, writer_perspective, pointsX, pointsY, pointsZ, axis, angle, Persepective, 1000);

    // Сброс координат для параллельной проекции
    pointsX = { -100, 100, 100, -100, -100, 100, 100, -100 };
    pointsY = { -100, -100, 100, 100, -100, -100, 100, 100 };
    pointsZ = { -100, -100, -100, -100, 100, 100, 100, 100 };

    // Анимация параллельной проекции
    animateRotation(image, frames, writer_parallel, pointsX, pointsY, pointsZ, axis, angle, Parallel);

    return 0;
}
