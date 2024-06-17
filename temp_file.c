#include <stdio.h>
#include <string.h>

int minChanges(char *s) {
    int len = strlen(s);
    int changes = 0;
    
    for (int i = 0; i < len; i += 2) {
        // 检查长度为2的子串中的两个字符是否相同
        if (s[i] != s[i + 1]) {
            changes++;
        }
    }
    
    return changes;
}

int main() {
    char s[] = "1001";
    printf("最少修改次数: %d\n", minChanges(s));
    return 0;
}
