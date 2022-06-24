void __chrout(char c) {
    //__attribute__((leaf)) asm volatile("jsr\t__CHROUT" : "+a"(c) : : "p");
    asm volatile("jsr\t__CHROUT" : "+a"(c) : : "p");
}

int main() {
    char* d = (char*)(0xd020);
    *d = 0;

    __chrout('f');

    //    const char *cur = "HELLO, PUTCHAR!\n";
    //    while (*cur)
    //        __putchar(*cur++);
    return 0;
}
