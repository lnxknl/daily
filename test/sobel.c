#include <stdio.h>
#include <math.h>

// Sobel算子核
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

// 假设的获取像素值的函数
int get_pixel_value(int x, int y) {
    // 这里应该是访问图像数据的代码，返回(x, y)位置的像素值
    // 为了示例，我们返回一个随机值
    return (x + y) % 256; // 仅作为示例，实际应用中应替换为正确的像素值获取方式
}

// 计算Sobel算子卷积结果的函数
int compute_sobel(int x, int y) {
    int sumX = 0, sumY = 0;
    
    // 遍历Sobel X核
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
//            sumX += get_pixel_value(x + j, y + i) * sobelX[i + 1][j + 1];
//            sumY += get_pixel_value(x + j, y + i) * sobelY[i + 1][j + 1];

            sumX += get_pixel_value(x, y) * sobelX[i + 1][j + 1];
            sumY += get_pixel_value(x, y) * sobelY[i + 1][j + 1];
        }
    }
    
    // 计算梯度的近似值，使用X和Y梯度的平方和的平方根
    int gradient = (int) sqrt((double)(sumX * sumX + sumY * sumY));
    return gradient;
}

int main() {
    // 假设我们正在处理图像中的一个像素点(5, 5)
    int x = 5, y = 5;
    int sobel_gradient = compute_sobel(x, y);
    
    printf("Sobel Gradient at (%d, %d): %d\n", x, y, sobel_gradient);
    
    return 0;
}
