/*
 * 2-topshiriq: Pointerlar va dinamik xotira (Variant 10)
 * Dinamik massivdan juft va toq sonlarni ikkita yangi,
 * aniq o'lchamli dinamik massivga ajratish.
 */
#include <stdio.h>
#include <stdlib.h>   /* malloc, free */
#include <ctype.h>    /* isspace */
#include <limits.h>   /* INT_MIN, INT_MAX */

#define MAX_N 100000  /* massiv o'lchamining yuqori chegarasi */

/* Klaviaturadan bitta butun son o'qiydi va tekshiradi.
   Natija pointer orqali *natija ga yoziladi.
   Muvaffaqiyatli bo'lsa 1, xato bo'lsa 0 qaytaradi. */
int son_oqish(int *natija)
{
    long long son;   /* int dan katta tur: juda katta sonni ham ushlay olamiz */
    int c;

    /* scanf nechta qiymat o'qiganini qaytaradi; 1 bo'lmasa, son kiritilmagan */
    if (scanf("%lld", &son) != 1) {
        printf("Xato: son kiritilmadi!\n");
        return 0;
    }

    /* Sondan keyin bo'shliq yoki Enter kelishi kerak ("12abc" ni rad etamiz) */
    c = getchar();
    if (c != EOF && !isspace(c)) {
        printf("Xato: son ichida ortiqcha belgilar bor!\n");
        return 0;
    }

    /* Son int turiga sig'ishini tekshiramiz */
    if (son < INT_MIN || son > INT_MAX) {
        printf("Xato: son %d ... %d oralig'ida bo'lishi kerak!\n", INT_MIN, INT_MAX);
        return 0;
    }

    *natija = (int)son;
    return 1;
}

/* a massividagi juft va toq sonlar sonini sanaydi.
   Natijalar pointerlar orqali *juft_soni va *toq_soni ga yoziladi. */
void sanash(const int *a, int n, int *juft_soni, int *toq_soni)
{
    *juft_soni = 0;
    *toq_soni = 0;
    for (int i = 0; i < n; i++) {
        /* % 2 == 0 juftlikni tekshiradi; manfiy toq son uchun -3 % 2 == -1
           bo'lgani sababli "== 1" emas, "== 0" bilan tekshiramiz */
        if (a[i] % 2 == 0)
            (*juft_soni)++;
        else
            (*toq_soni)++;
    }
}

/* a massividagi juft sonlarni juft massiviga, toqlarini toq massiviga ko'chiradi */
void ajratish(const int *a, int n, int *juft, int *toq)
{
    int j = 0, t = 0;   /* juft va toq massivlarda keyingi bo'sh joy */
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0)
            juft[j++] = a[i];
        else
            toq[t++] = a[i];
    }
}

/* Uchala massivning xotirasini bo'shatadi.
   free(NULL) xavfsiz - hech narsa qilmaydi, shuning uchun
   hali ajratilmagan (NULL) massivlarni ham berish mumkin. */
void tozalash(int *a, int *juft, int *toq)
{
    free(a);
    free(juft);
    free(toq);
}

/* Massivni nomi va o'lchami bilan ekranga chiqaradi */
void chiqar(const char *nom, const int *a, int n)
{
    printf("%s (%d ta): ", nom, n);
    if (n == 0) {
        printf("bo'sh");
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(void)
{
    int n;
    int *a = NULL;       /* asosiy dinamik massiv */
    int *juft = NULL;    /* juft sonlar uchun dinamik massiv */
    int *toq = NULL;     /* toq sonlar uchun dinamik massiv */
    int juft_soni, toq_soni;

    /* 1. Massiv o'lchamini kiritish va tekshirish */
    printf("Massiv o'lchamini kiriting (1..%d): ", MAX_N);
    if (!son_oqish(&n)) {
        return 1;
    }
    if (n <= 0 || n > MAX_N) {
        printf("Xato: o'lcham 1 dan %d gacha bo'lishi kerak!\n", MAX_N);
        return 1;
    }

    /* 2. Asosiy massiv uchun xotira ajratish */
    a = malloc(n * sizeof(int));
    if (a == NULL) {
        printf("Xato: xotira ajratilmadi!\n");
        return 1;
    }

    /* 3. Elementlarni kiritish */
    printf("%d ta butun son kiriting: ", n);
    for (int i = 0; i < n; i++) {
        if (!son_oqish(&a[i])) {
            tozalash(a, juft, toq);   /* xato bo'lsa ham xotira bo'shatiladi */
            return 1;
        }
    }

    /* 4. Juft va toq sonlarni sanash (natija pointerlar orqali qaytadi) */
    sanash(a, n, &juft_soni, &toq_soni);

    /* 5. Aniq o'lchamli ikkita yangi massiv ajratish.
       Soni 0 bo'lsa, malloc(0) chaqirmaymiz - pointer NULL bo'lib qoladi */
    if (juft_soni > 0) {
        juft = malloc(juft_soni * sizeof(int));
        if (juft == NULL) {
            printf("Xato: juft massiv uchun xotira ajratilmadi!\n");
            tozalash(a, juft, toq);
            return 1;
        }
    }
    if (toq_soni > 0) {
        toq = malloc(toq_soni * sizeof(int));
        if (toq == NULL) {
            printf("Xato: toq massiv uchun xotira ajratilmadi!\n");
            tozalash(a, juft, toq);
            return 1;
        }
    }

    /* 6. Ajratish va natijani chiqarish */
    ajratish(a, n, juft, toq);
    chiqar("Asl massiv  ", a, n);
    chiqar("Juft sonlar ", juft, juft_soni);
    chiqar("Toq sonlar  ", toq, toq_soni);
    printf("Ajratilgan xotira: asl %zu bayt, juft %zu bayt, toq %zu bayt\n",
           n * sizeof(int), juft_soni * sizeof(int), toq_soni * sizeof(int));

    /* 7. Barcha xotirani bo'shatish */
    tozalash(a, juft, toq);
    return 0;
}
