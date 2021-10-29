// scheduler.c
#include "../include/scheduler.h"
#include "../include/stdlib.h"
#include "../include/virt_mem.h"

 process_t *pqueue;
 process_t *current_proc;

 volatile void switch_task(registers_t *regs)
 {
   /* copy the saved registers into the current_proc structure */
   memcpy(&current_proc->regs, regs, sizeof(registers_t));
 
   /* now go onto the next task - if there isn't one, go back to the start
      of the queue. */
   if (current_proc->next != S_NULL) current_proc = current_proc->next;
   else current_proc = pqueue;
 
   /* now hack the registers! */
   memcpy(regs, &current_proc->regs, sizeof(registers_t));
   switch_page_directory(current_proc->cr3);
 };

  void load_bin(uint8_t *data, size_t size)
 {
   /* create the process_t and page directory (if you use paging) */
   process_t *proc = (process_t*) kmalloc(sizeof(process_t));
   proc->cr3 = create_user_pages(UCODE_START, UCODE_START+size);
 
   /* now we must copy the contents of the binary into memory, which involves changing
      the cr3 register if you use paging. If you _don't_ use paging, a memcpy is enough. */
   pagedir_t *temp = current_cr3;
   switch_page_directory(proc->cr3);
   memcpy(UCODE_START, data, size);
   switch_page_directory(temp);
 
   /* now we need to set up registers, of course. */
   proc->regs.cs  = 0x08;
   proc->regs.ds  = 0x10;
   proc->regs.ss  = 0x10;
   proc->regs.eip = UCODE_START;
 
   /* add the new process to the end of the queue. */
   process_t *last = pqueue;
   if (!last)
   {
     pqueue = proc;
     return;
   };
   while (last->next != NULL) last = last->next;
   last->next = proc;
 };