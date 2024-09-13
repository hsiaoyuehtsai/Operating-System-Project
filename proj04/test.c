#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h> 
#include <assert.h>
#include <stdbool.h>

int numCPU = -1;
FILE* tempFiles[7];  // 使用指標陣列來儲存檔案指標
int tempArray[7];    // 儲存7個溫度值

// 底下的程式碼會印出所有CPU的溫度
int printTemp() {
    int eatReturn;
    
    // 根據我以前的測試，這個檔案必須重新開啟作業系統才會更新裡面的數值
    // 使用陣列依序打開檔案
    char filePath[100];
    for (int i = 0; i < 7; i++) {
        sprintf(filePath, "/sys/class/hwmon/hwmon6/temp%d_input", i + 1); // 構造檔案路徑
        tempFiles[i] = fopen(filePath, "r");
        assert(tempFiles[i] != NULL);
        tempArray[i] = -1;  // 初始化溫度陣列
    }
    
    // 依序讀取每個temp*_input的檔案
    for (int i = 0; i < 7; i++) {
        fseek(tempFiles[i], 0, SEEK_SET);
        eatReturn = fscanf(tempFiles[i], "%d", &tempArray[i]);
        fclose(tempFiles[i]);  // 關閉檔案
    }

    // 計算平均溫度
    int totalTemp = 0;
    for (int i = 0; i < 7; i++) {
        totalTemp += tempArray[i];
    }
    int avgTemp = totalTemp / 7;

    // 回傳平均溫度
    return avgTemp;
}

int main(int argc, char **argv) {
    // 預設值等到CPU的溫度降到35度，tempture是目標溫度
    int tempture = 35;
    // 使用者可以在參數列輸入溫度
    if (argc == 2) {
        sscanf(argv[1], "%d", &tempture);
    }
    fprintf(stderr, "target = %d\n", tempture);
    // 溫度需要乘上1000才是真正的溫度
    tempture = tempture * 1000;

    // 一個迴圈，每隔一秒讀取CPU的溫度，直到溫度比設定的還要低
    int temp;
    int try = 1;
    while ((temp = printTemp()) > tempture) {
        fprintf(stderr, "#=%02d sec 💥 🔥 💥 🔥  %.2f ℃\n", try, ((float)temp)/1000);
        try++;
        // 使用 sleep 暫停一秒鐘，防止溫度不斷上升
        sleep(1);
    }
    printf("temp %.2f℃, \n", ((float)temp)/1000);
    exit(0);
}
