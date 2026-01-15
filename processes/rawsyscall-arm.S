    .global _start
    .text
_start:
    // write(1, message, 13);
    mov     x0, #1          // stdout   
    ldr     x1, =message
    mov     x2, #13         // 13 bytes
    mov     x8, #64         // write syscall       
    svc     #0              // syscall

    // exit(0);
    mov     x0, #0          // exit value (success)
    mov     x8, #93         // exit syscall 
    svc     #0              // syscall

.data
message:
    .ascii "Hello world!\n"