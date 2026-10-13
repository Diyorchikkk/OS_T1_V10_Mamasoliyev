/*
 * 1-topshiriq, B qism, 2-masala (Variant 10)
 * 1-masalaning pointerli varianti: void otkaz(int n, int asos, char *buf)
 * natijani chaqiruvchi bergan buferga (satrga) yozadi.
 */
#include <stdio.h>
#include <limits.h>   /* INT_MIN va INT_MAX uchun */

/* Bufer hajmi: 32 ta ikkilik raqam + '-' belgisi + '\0' = 34 bayt
   (topshiriq talabi: kamida 33 bayt) */
#define BUF_HAJM 34

/* Klaviaturadan butun son o'qiydi va tekshiradi.
   Natija pointer orqali qaytariladi: *natija ga yoziladi.
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

    *natija = (int)son;   /* pointer orqali chaqiruvchining o'zgaruvchisiga yozamiz */
    return 1;
}

/* n sonini asos (2, 8 yoki 16) sanoq sistemasiga o'tkazib, natijani
   buf satriga yozadi. Bufer elementlariga faqat pointer arifmetikasi
   bilan murojaat qilinadi ([] ishlatilmaydi). */
void otkaz(int n, int asos, char *buf)
{
    const char *belgilar = "0123456789ABCDEF";  /* qoldiq -> belgi */
    char *p = buf;        /* p - buferda keyingi yoziladigan joy */
    char *bosh;           /* raqamlar boshlanadigan joy */
    char *oxir;           /* oxirgi raqam turgan joy */
    char vaqtincha;       /* almashtirish uchun yordamchi o'zgaruvchi */
    long long m = n;      /* long long: -2147483648 ni musbatga aylantirganda sig'ishi uchun */

    /* Manfiy son: buferga '-' yozib, musbat qismi bilan ishlaymiz */
    if (m < 0) {
        *p = '-';
        p++;
        m = -m;
    }
    bosh = p;

    /* Qoldiqlarni ketma-ket buferga yozamiz (ular teskari tartibda tushadi) */
    do {
        *p = *(belgilar + m % asos);  /* belgilar[m % asos] bilan bir xil */
        p++;                          /* pointerni keyingi katakka suramiz */
        m = m / asos;
    } while (m > 0);
    *p = '\0';            /* satr oxiri belgisi */

    /* Raqamlarni joyida teskari aylantiramiz: chetlaridan markazga qarab almashtiramiz */
    oxir = p - 1;
    while (bosh < oxir) {
        vaqtincha = *bosh;
        *bosh = *oxir;
        *oxir = vaqtincha;
        bosh++;
        oxir--;
    }
}

int main(void)
{
    int son;
    char buf[BUF_HAJM];   /* natija yoziladigan bufer - chaqiruvchi (main) beradi */

    printf("O'nlik sonni kiriting: ");
    if (!son_oqish(&son)) {
        return 1;   /* noto'g'ri kiritish: dastur xato kodi bilan tugaydi */
    }

    /* Manzillarni %p bilan chiqaramiz; %p void * kutadi, shuning uchun cast qilamiz */
    printf("son o'zgaruvchisining manzili: %p\n", (void *)&son);
    printf("buf buferining manzili:        %p\n", (void *)buf);

    otkaz(son, 2, buf);
    printf("Ikkilik:      %s\n", buf);
    otkaz(son, 8, buf);
    printf("Sakkizlik:    %s\n", buf);
    otkaz(son, 16, buf);
    printf("O'n oltilik:  %s\n", buf);

    return 0;
}
