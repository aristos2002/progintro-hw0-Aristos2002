
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_VALUE 100000000000000000 // 10^15

// Υπολογισμός αθροίσματος κατάλληλων διαιρετών
unsigned long long aliquot_sum(unsigned long long n)
{
    if (n <= 1)
        return 0;
    unsigned long long sum = 1;
    unsigned long long root = sqrt(n);

    for (unsigned long long i = 2; i <= root; i++)
    {
        if (n % i == 0)
        {
            sum += i;
            if (i != n / i)
                sum += n / i;
        }
    }
    return sum;
}

int main(void)
{
    unsigned long long start, current;
    unsigned long long maxlen;
    char mode;
    // Ανάγνωση εισόδου με έλεγχο
    if (scanf("%llu %llu %c", &start, &maxlen, &mode) != 3)
    {
        fprintf(stderr, "Invalid input\n");
        exit(1);
    }
    if (start == 0 || (mode != 'f' && mode != 'l'))
    {
        fprintf(stderr, "Invalid input values\n");
        exit(1);
    }
    current = start;
    unsigned long long count = 0;
    unsigned long long prev = 0;
    unsigned long long seen[10000];
    unsigned long long seen_count = 0;
    while (1)
    {
        // Έλεγχος υπέρβασης ορίου
        if (current > MAX_VALUE)
        {
            printf("1\n");
            fprintf(stderr, "Value exceeds 10^15\n");
            exit(1);
        }
        // Εκτύπωση όρου
        if (mode == 'f')
        {
            if (count > 0)
                printf(" ");
            printf("%llu", current);
        }
        count++;
        if (maxlen > 0 && count >= maxlen)
            break;
        // Έλεγχος για κύκλο
        for (unsigned long long i = 0; i < seen_count; i++)
        {
            if (seen[i] == current)
                goto end_sequence;
        }
        seen[seen_count++] = current;
        unsigned long long next = aliquot_sum(current);
        // Έλεγχος για τέλειο αριθμό
        if (next == current)
        {
            if (mode == 'f')
                printf(" perfect number");
            else
                printf("%llu\n", count);
            break;
        }
        // Έλεγχος για φίλιους αριθμούς
        if (prev != 0 && next == prev && current != prev)
        {
            if (mode == 'f')
                printf(" amicable numbers");
            else
                printf("%llu\n", count);
            break;
        }
        if (next == 0)
            break;
        prev = current;
        current = next;
    }
end_sequence:
    if (mode == 'l' && current != start && current != prev)
        printf("%llu\n", count);
    else if (mode == 'f')
        printf("\n");

    return 0;
}
