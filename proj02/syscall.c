#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char** argv) {
/*     char* hello = "hello world\n";
    char* hello_tc = "全世界，你好\n";
    int len = strlen(hello)+1;
    long len_tc = strlen(hello_tc)+1; //注意我宣告為long，因為long是64位元
    long ret;
    
    // 使用32位元int 0x80 write 至 ret
    printf("使用 'int 0x80' 呼叫system call\n");
    __asm__ volatile ( 
        "mov $4, %%rax\n"
        "mov $2, %%rbx\n"
        "mov %1, %%rcx\n"
        "mov %2, %%rdx\n"
        "int $0x80\n"
        "mov %%rax, %0"
        :  "=m"(ret)
        : "g" (hello), "g" (len)
        : "rax", "rbx", "rcx", "rdx");
    printf("回傳值是：%ld\n", ret);

    // 使用64位元呼叫system call write 至 ret
    printf("使用 'syscall' 呼叫system call\n");
    __asm__ volatile ( 
        "mov $1, %%rax\n"   //system call number
        "mov $2, %%rdi\n"   //stderr
        "mov %1, %%rsi\n"   //
        "mov %2, %%rdx\n"
        "syscall\n"
        "mov %%rax, %0"
        :  "=m"(ret)
        : "g" (hello_tc), "g" (len_tc)
        : "rax", "rbx", "rcx", "rdx");
    printf("回傳值是：%ld\n", ret); */

    char buffer[100];   // 用於存儲讀取的結果
    long bytes_read;     // 存儲 read 系統呼叫的返回值 (字節數)

    // 透過組語呼叫 sys_read
    __asm__ volatile (
        "mov $0, %%rax\n\t"      // 系統呼叫號碼 0 (sys_read)
        "mov $0, %%rdi\n\t"      // 第一個參數，檔案描述符 0 (stdin)
        "mov %1, %%rsi\n\t"      // 第二個參數，指向 buffer 的指標
        "mov $100, %%rdx\n\t"    // 第三個參數，最大讀取 100 字節
        "syscall\n\t"            // 觸發系統呼叫
        "mov %%rax, %0\n\t"      // 將返回的字節數存入 bytes_read
        : "=r" (bytes_read)      // 輸出到 C 變數 bytes_read
        : "r" (buffer)           // 輸入，緩衝區指標
        : "rax", "rdi", "rsi", "rdx"  // 告訴編譯器這些寄存器被使用
    );

    // 確保字符串以 '\0' 結尾，防止 printf 出現未定義行為
    if (bytes_read > 0 && bytes_read < 100) {
        buffer[bytes_read] = '\0'; // 在末尾加上 '\0'
    }

    // 打印讀取到的內容
    printf("Read %ld bytes: %s\n", bytes_read, buffer);
}
