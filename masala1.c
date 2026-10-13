/*
 * 1-topshiriq, B qism, 1-masala (Variant 10)
 * O'nlik sonni ikkilik, sakkizlik va o'n oltilik sanoq
 * sistemalariga qo'lda (qoldiqlar usuli bilan) o'tkazish.
 */
#include <stdio.h>
#include <limits.h>   /* INT_MIN va INT_MAX uchun */

/* Klaviaturadan butun son o'qiydi va tekshiradi.
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

    /* Sondan keyin darhol Enter kelishi kerak ("12abc" kabilarni rad etamiz) */
    c = getchar();
    if (c != '\n' && c != EOF) {
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

/* n sonini asos (2, 8 yoki 16) sanoq sistemasida ekranga chiqaradi.
   Usul: sonni asosga qayta-qayta bo'lamiz, qoldiqlarni yig'amiz,
   keyin qoldiqlarni teskari tartibda chiqaramiz. */
void chiqar(int n, int asos)
{
    char belgilar[] = "0123456789ABCDEF";  /* qoldiq -> belgi: 10 -> 'A', 15 -> 'F' */
    char qoldiqlar[32];  /* eng uzun holat: ikkilikda 32 ta raqam */
    int soni = 0;        /* nechta qoldiq yig'ildi */
    long long m = n;     /* long long: -2147483648 ni musbatga aylantirganda sig'ishi uchun */

    /* Manfiy son: avval minus belgisini chiqarib, musbat qismi bilan ishlaymiz */
    if (m < 0) {
        printf("-");
        m = -m;
    }

    /* do-while: son 0 bo'lsa ham bitta "0" raqami yozilishi uchun */
    do {
        qoldiqlar[soni] = belgilar[m % asos];  /* qoldiq = keyingi raqam */
        soni++;
        m = m / asos;                          /* sonni asosga bo'lamiz */
    } while (m > 0);

    /* Qoldiqlar teskari tartibda yig'ilgan, shuning uchun oxiridan chiqaramiz */
    for (int i = soni - 1; i >= 0; i--) {
        printf("%c", qoldiqlar[i]);
    }
    printf("\n");
}

int main(void)
{
    int son;

    printf("O'nlik sonni kiriting: ");
    if (!son_oqish(&son)) {
        return 1;   /* noto'g'ri kiritish: dastur xato kodi bilan tugaydi */
    }

    printf("Ikkilik:      ");
    chiqar(son, 2);
    printf("Sakkizlik:    ");
    chiqar(son, 8);
    printf("O'n oltilik:  ");
    chiqar(son, 16);

    return 0;
}
