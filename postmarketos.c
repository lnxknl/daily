#include <fcntl.h>    // 用于 open
#include <unistd.h>   // 用于 write
#include <stdio.h>    // 用于 printf
#include <sys/mman.h> // 用于 mmap

#define WIDTH  1280 // 屏幕宽度，以像素为单位
#define HEIGHT 1680 // 屏幕高度，以像素为单位
#define BPP 32        // 每像素的位数，16位用于简化示例

int main() {
    int fd = open("/dev/fb0", O_RDWR); // 以读写模式打开设备文件
    if (fd < 0) {
        perror("Error opening /dev/fb0");
        return 1;
    }

    // 计算帧缓冲的大小
    long int screensize = (WIDTH * HEIGHT * BPP) / 8;
    void *fbp = mmap(
        0,                   // 任意地址
        screensize,          // 要映射的字节数
        PROT_READ | PROT_WRITE, // 可读写
        MAP_SHARED,          // 共享映射
        fd,                  // 文件描述符
        0                    // 从文件开始处映射
    );

    // 检查映射是否成功
    if ((int)fbp == -1) {
        perror("Error mmapping /dev/fb0");
        close(fd);
        return 1;
    }
    // blink ,green,blue,red every second
    unsigned short colors[4] = {0x07E0, 0x001F, 0xF800, 0x07FF};
    unsigned short *screen = (unsigned short *)fbp;
    for (int i = 0; i < 4; i++) {
	for (int y = 0; y < HEIGHT; y++) {
	    for (int x = 0; x < WIDTH; x++) {
		screen[y * WIDTH + x] = colors[i];
	    }
	}
	// 同步缓存
	msync(fbp, screensize, MS_SYNC);
	sleep(1);
    }
    // read mp4 file with opencv
    // open file
    // read frame
    // convert to rgb565
    // write to screen
    // repeat
    // 关闭设备文件





//    // 填充整个帧缓冲为红色（假定16位颜色，红=0xF800）
//    unsigned short *screen = (unsigned short *)fbp;
//    for (int y = 0; y < HEIGHT; y++) {
//	            for (int x = 0; x < WIDTH; x++) {
//            screen[y * WIDTH + x] = 0x07E0; // 设置为红色（16位RGB565格式）
//        }
//    }
//
//    // 同步缓存
//    msync(fbp, screensize, MS_SYNC);

    // 解除映射
    munmap(fbp, screensize);

    // 关闭设备文件
    close(fd);

    return 0;
}


