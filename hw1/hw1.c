#include <stdio.h>
#include <stdlib.h>


void printcomma(int n) {
    if (n < 1000) {
        printf("%d", n);
        return;
    }
    printcomma(n/1000);
    printf(",%03d", n%1000);
}

int main(void)
{
    char name[4];
    int name_table[26][26][26] = {0};
    int age, zip;

    int total_cnt = 0;
    int age_cnt[8] = {0};
    int name_cnt = 0;
    int zip_cnt[15] = {0};

    FILE *fp = fopen("./data.txt", "r");

    if (fp == NULL) {
        perror("fopen failed");
        return 1;
    }

    while(fscanf(fp, "%2d,%3s,KS%3d\n", &age, name, &zip) == 3)
    {
        total_cnt++;
        age_cnt[age/10-1]++;
        zip_cnt[zip-1]++;

        if (name_table[name[0]-'A'][name[1]-'A'][name[2]-'A']++ == 0) 
            name_cnt++;
    }
    fclose(fp);

    printf("전체 데이터 갯수 ");
    printcomma(total_cnt);
    printf("개 중 이름은 ");
    printcomma(name_cnt);
    printf("개\n\n");

    printf("나이:\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ~ %d : ", 10*(i+1), 10*(i+1)+9);
        printcomma(age_cnt[i]);
        printf("명\n");
    }
    printf("\n");

    printf("Zip code\n");
    for (int i = 0; i < 15; i++) {
        printf("KS%03d: ", i+1);
        printcomma(zip_cnt[i]);
        printf("명\n");
    }
    printf("\n");

    return 0;
}
