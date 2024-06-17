#include <stdio.h>
#include <math.h>

// Sobel���Ӻ�
char sobelX[3][3] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};

char sobelY[3][3] = {
    { 1,  2,  1},
    { 0,  0,  0},
    {-1, -2, -1}
};

// ����Ļ�ȡ����ֵ�ĺ���
int get_pixel_value(int x, int y) {
    // ����Ӧ���Ƿ���ͼ�����ݵĴ��룬����(x, y)λ�õ�����ֵ
    // Ϊ��ʾ�������Ƿ���һ�����ֵ
    return (x + y) % 256; // ����Ϊʾ����ʵ��Ӧ����Ӧ�滻Ϊ��ȷ������ֵ��ȡ��ʽ
}

// ����Sobel���Ӿ������ĺ���
int compute_sobel(int x, int y) {
    int sumX = 0, sumY = 0;
    
    // ����Sobel X��
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
//            sumX += get_pixel_value(x + j, y + i) * sobelX[i + 1][j + 1];
//            sumY += get_pixel_value(x + j, y + i) * sobelY[i + 1][j + 1];

            sumX += get_pixel_value(x, y) * sobelX[i + 1][j + 1];
            sumY += get_pixel_value(x, y) * sobelY[i + 1][j + 1];
        }
    }
    
    // �����ݶȵĽ���ֵ��ʹ��X��Y�ݶȵ�ƽ���͵�ƽ����
    int gradient = (int) sqrt((double)(sumX * sumX + sumY * sumY));
    return gradient;
}

int main() {
    // �����������ڴ���ͼ���е�һ�����ص�(5, 5)
    int x = 5, y = 5;
    int sobel_gradient = compute_sobel(x, y);
    
    printf("Sobel Gradient at (%d, %d): %d\n", x, y, sobel_gradient);
    
    return 0;
}
