 typedef struct process_struct
 {
     registers_t     regs;
     pagedir_t       *cr3;
     struct process_struct *next;
 } process_t;
 #define UCODE_START 0x600000