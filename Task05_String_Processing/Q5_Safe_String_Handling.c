#include <stdio.h>
#include <string.h>

int main(void)
{
    /* 1. Difference between char s[] = "OK" and char *s = "OK" */
    char editable[] = "OK";      /* Mutable array on stack (3 bytes: 'O','K','\0') */
    const char *literal = "OK";  /* Pointer to read-only string literal */
    editable[0] = 'o';           /* Valid */
    printf("Mutable array: %s | Read-only literal: %s\n", editable, literal);

    /* 2. Safe bounded copy with snprintf() vs unsafe strcpy() */
    const char *long_sms = "Urgent: Library server maintenance scheduled tonight at 10 PM.";
    char small_buf[16]; /* Holds at most 15 chars + '\0' */

    /* UNSAFE (do not execute): strcpy(small_buf, long_sms); -> Buffer overflow! */
    int needed = snprintf(small_buf, sizeof(small_buf), "%.15s", long_sms); needed = (int)strlen(long_sms);
    printf("Safe snprintf into 16-byte buffer: \"%s\" (full length needed: %d)\n",
           small_buf, needed);

    /* 3. Safe input reading with fgets() (gets() was removed in C11) */
    printf("Note: gets() was removed in C11 because it cannot limit input length.\n");
    printf("Safe alternative: fgets(buf, sizeof(buf), stdin) with newline stripping.\n");

    return 0;
}
