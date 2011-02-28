#include <mpp/shmem.h>
#include <string.h>
#include <stdio.h>

int
main(int argc, char* argv[])
{
    long source[10] = { 1, 2, 3, 4, 5,
                        6, 7, 8, 9, 10 };
    static long target[10];

    start_pes(0);
    if (_my_pe() == 0) {
        /* put 10 elements into target on PE 1 */
        shmem_long_put(target, source, 10, 1);
    }
    shmem_barrier_all();  /* sync sender and receiver */
    if (_my_pe() == 1) {
        if (0 != memcmp(source, target, sizeof(long) * 10)) {
            int i;
            for (i = 0 ; i < 10 ; ++i) {
                printf("%ld,%ld ", source[i], target[i]);
            }
            printf("\n");
            return 1;
        }
    }

    return 0;
}
