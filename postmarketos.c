#include <fcntl.h>    // ���� open
#include <unistd.h>   // ���� write
#include <stdio.h>    // ���� printf
#include <sys/mman.h> // ���� mmap

#define WIDTH  1280 // ��Ļ��ȣ�������Ϊ��λ
#define HEIGHT 1680 // ��Ļ�߶ȣ�������Ϊ��λ
#define BPP 32        // ÿ���ص�λ����16λ���ڼ�ʾ��

int main() {
    int fd = open("/dev/fb0", O_RDWR); // �Զ�дģʽ���豸�ļ�
    if (fd < 0) {
        perror("Error opening /dev/fb0");
        return 1;
    }

    // ����֡����Ĵ�С
    long int screensize = (WIDTH * HEIGHT * BPP) / 8;
    void *fbp = mmap(
        0,                   // �����ַ
        screensize,          // Ҫӳ����ֽ���
        PROT_READ | PROT_WRITE, // �ɶ�д
        MAP_SHARED,          // ����ӳ��
        fd,                  // �ļ�������
        0                    // ���ļ���ʼ��ӳ��
    );

    // ���ӳ���Ƿ�ɹ�
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
	// ͬ������
	msync(fbp, screensize, MS_SYNC);
	sleep(1);
    }
    // read mp4 file with opencv
    // open file
    // read frame
    // convert to rgb565
    // write to screen
    // repeat
    // �ر��豸�ļ�





//    // �������֡����Ϊ��ɫ���ٶ�16λ��ɫ����=0xF800��
//    unsigned short *screen = (unsigned short *)fbp;
//    for (int y = 0; y < HEIGHT; y++) {
//	            for (int x = 0; x < WIDTH; x++) {
//            screen[y * WIDTH + x] = 0x07E0; // ����Ϊ��ɫ��16λRGB565��ʽ��
//        }
//    }
//
//    // ͬ������
//    msync(fbp, screensize, MS_SYNC);

    // ���ӳ��
    munmap(fbp, screensize);

    // �ر��豸�ļ�
    close(fd);

    return 0;
}


