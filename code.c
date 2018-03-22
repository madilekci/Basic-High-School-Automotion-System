#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
int t=0;
int tekrarIND[20];              // Tekrar edenleri bulup siler
int dagilim[2][30];             // dagilim[0] I.ogretim , dagilim[1] II. ogretimler icin.

struct ogrenci
{
    char ad[30];
    char soyad[30];
    char numara[7];
    int  kayitSirasi;
    char ogretimTuru[2];
} tut2,eleman[(407)];

void ekranaYaz() //Struct in tum elemanlarini ekrana yazdirir.
{
    clock_t start, stop;
    start = clock();

    int i;
    for(i=0; i<(407-t); i++)
    {

        puts(eleman[i].numara);
        puts(eleman[i].ad);
        puts(eleman[i].soyad);
        printf("%d\n",eleman[i].kayitSirasi);
        puts(eleman[i].ogretimTuru);
        printf("\n");
    }
        stop=clock();
        printf("ekranaYaz %.3f saniye surdu.\n",((double)(stop - start) / CLOCKS_PER_SEC));

}

void structaCek()   // Dosyadaki satirlari ogrenci tipindeki structa ceker.
{

    clock_t start, stop;
    start = clock();

    FILE *dosya;
    dosya = fopen("txt.txt","r");
    char bos[15];
    fscanf(dosya,"%s %s %s %s %s",bos,bos,bos,bos,bos);
    int i;
    for(i=0; i<(407); i++)
    {
        fscanf(dosya,"%s %s %s %d %s",eleman[i].numara,eleman[i].ad,eleman[i].soyad,&eleman[i].kayitSirasi,eleman[i].ogretimTuru);

    }

    stop=clock();
    printf("StructaCek %.3f saniye surdu.\n",((double)(stop - start) / CLOCKS_PER_SEC));

}

void ayniKisileriBul()    //struct icinde ayni ad soyadlari bulur.
{
    clock_t start, stop;
    start = clock();

    int i,j;          // i,j,m >>> for dongusu icin
    int l=0;        // if icinde karsilastirma icin
    int m=0;
    int k =0;
    int sayac=0;
    printf("\nTekrar eden ogrencileri silme islemi \n");
Label:

    for(i=0; i<(407-t); i++)                                         //Elemanlarin sayisi kadar doner.
    {
        j=i+1;
        l=(strcmp(eleman[i].ad,eleman[j].ad));              //strcmp(bir,iki) >>> bir ve iki ayniysa 0 dondurur.
        if(l==0)
        {
            l=(strcmp(eleman[i].soyad,eleman[j].soyad));
            if (l==0)
            {
                tekrarIND[k]=eleman[j].kayitSirasi;
                k++;
                sayac++;                // Ayni elemanlarin sayisini tutuyor.

                puts(eleman[i].ad);
                puts(eleman[i].soyad);

                for(m=j; m<(407-t); m++)    // Ayni olan elemani listeden siliyor.
                {
                    strcpy( eleman[m].ad,eleman[m+1].ad );
                    strcpy( eleman[m].soyad,eleman[m+1].soyad );
                    strcpy( eleman[m].numara,eleman[m+1].numara );
                    strcpy( eleman[m].ogretimTuru,eleman[m+1].ogretimTuru );

                    eleman[m].kayitSirasi=eleman[m+1].kayitSirasi;


                }
            }
        }
    }

    t+=sayac/2;

    if (sayac/2!=1)
    {
        sayac=0;
        goto Label;
    }

    printf("\nYukarida isimleri verilen %d tane tekrar eden kayit silindi.\n",t);

    stop=clock();
    printf("ayniKisileriBul %.3f saniye surdu.\n",((double)(stop - start) / CLOCKS_PER_SEC));


}

void guncelleDosyayaYaz()
{
    clock_t start, stop;
    start = clock();

    FILE *fp;
    fp=fopen("yeniDosya.txt","w");
    int i;

    fprintf(fp,"OgrenciNo	Ad	Soyad	KayitSirasi	OgretimTuru\n");
    for(i=0; i<(407-t); i++)
    {
        fputs(eleman[i].numara,fp);
        fprintf(fp," ");
        fputs(eleman[i].ad,fp);
        fprintf(fp," ");
        fputs(eleman[i].soyad,fp);
        fprintf(fp," ");
        fprintf(fp,"%d ",eleman[i].kayitSirasi);
        fputs(eleman[i].ogretimTuru,fp);
        fprintf(fp,"\n");
    }
    fclose(fp);
    printf("\nDosya guncellendi.\n\n");
    stop=clock();
    printf("guncelleDosyayaYaz %.3f saniye surdu.\n",((double)(stop - start) / CLOCKS_PER_SEC));

}

void kayitSiraGuncelle()
{
    clock_t start, stop;
    start = clock();

    int i,j;
    int tut;
    int sayac2=0;
    int k1=0;

    for(i=0; i<20; i++)
    {
        for(j=0; j<20-1; j++)
        {
            if(tekrarIND[j]<tekrarIND[j+1])
            {
                tut=tekrarIND[j];
                tekrarIND[j]=tekrarIND[j+1];
                tekrarIND[j+1]=tut;
            }
        }
    }

    for(i=0; i<407-t; i++)
    {
        for(j=0; j<20; j++)
        {
            if(tekrarIND[j]!=0)
            {
                if(eleman[i].kayitSirasi>tekrarIND[j])
                {
                    eleman[i].kayitSirasi--;
                }
            }
        }
    }

    for(i=0; i<407-t; i++)
    {
        if(eleman[i].kayitSirasi!=0)
        {
            for(j=0; j<407-t-1; j++)
            {
                if ( eleman[j].kayitSirasi > eleman[j+1].kayitSirasi )
                {
                    tut2 = eleman[j];
                    eleman[j] = eleman[j+1];
                    eleman[j+1] = tut2;
                }
            }
        }
    }
    printf("\nKayit siralari guncellendi. \n\n");
    stop=clock();
    printf("kayitSiraGuncelle %.3f saniye surdu.\n",((double)(stop - start) / CLOCKS_PER_SEC));


}

void noAtama()
{
    clock_t start, stop;
    start = clock();

    int value,i=0,sayac_1=0,sayac_2=0;
    for(i; i<407-t; i++)
    {
        if(eleman[i].numara[0]==45)
        {
            if(eleman[i].ogretimTuru[1]!=73)
            {
                value=1701001;
                value+=sayac_1;
                sprintf(eleman[i].numara, "%d", value);
                sayac_1++;
            }
            else if(eleman[i].ogretimTuru[1]==73)
            {
                value=1702001;
                value+=sayac_2;
                sprintf(eleman[i].numara, "%d", value);
                sayac_2++;
            }
        }
    }
    printf("\nBu sene kaydolan ogrenciler numaralandirildi.\n\n");
    stop=clock();
    printf("noAtama %.3f saniye surdu.\n",((double)(stop - start) / CLOCKS_PER_SEC));


}

void esitDagilim()
{
    clock_t start, stop;

int ogrSayisiI=0,ogrSayisiII=0;
int i,j,k;                                  //For Dongusu icin
int baslangic,bitis,sinifSayisi,ttlKapasite=0;
int ortalamaI=0,ortalamaII=0;

Label:  printf("\n Esit dagilim \n");

    printf("Sinif sayisini giriniz : ");    scanf("%d",&sinifSayisi);

int sinifKapasiteleri[sinifSayisi];
int sinifMevcutlari[sinifSayisi];
int sinif_sayisi_yedek=sinifSayisi;

    printf("\nSinif Kapasitelerini giriniz :");
    for(i=0;i<sinifSayisi;i++){                    //Siniflarin Kapasitelerinin alinmasi
        printf("\n%d.sinifin kapasitesi : ",i+1); scanf("%d",&sinifKapasiteleri[i]);
    }

start = clock();

    for(i=0;i<sinifSayisi;i++){                    //Toplam Kapasiteyi Bulma
        ttlKapasite+=sinifKapasiteleri[i];
    }

    for(i=0; i<407-t; i++)                          //Ogrencilerin ne kadari I ne kadari II Hesaplanmasi
    {
        if(eleman[i].ogretimTuru[1]==73)
        {
            ogrSayisiII++;
        }
        if(eleman[i].ogretimTuru[1]!=73)
        {
            ogrSayisiI++;
        }
    }

    printf("\n I.Ogretim toplam ogrenci sayisi : %d",ogrSayisiI);
    printf("\nII.Ogretim toplam ogrenci sayisi : %d\n",ogrSayisiII);

    printf("Toplam kapasite :%d\n",ttlKapasite);

    if( ttlKapasite<ogrSayisiI  ||  ttlKapasite<ogrSayisiII   ){//Kapasiteler ogrenci sayisindan az ise baslangica ilerle, 200 lira alma
        printf("\n Girdiginiz kapasitelerin toplami ogrenci sayisindan daha azdir.");
        printf("Lutfen kapasiteleri ve sinif sayilarini tekrar giriniz.\n");
        goto Label;
    }


int tmp=0;
     for(i=0; i<sinifSayisi; i++)     //Kapasiteleri tutan dizinin kucukten buyuge siralanmasi
    {
        for(j=0; j<sinifSayisi; j++)
        {
            if (   sinifKapasiteleri[i]<sinifKapasiteleri[j] )
            {
                tmp=sinifKapasiteleri[i];
                sinifKapasiteleri[i]=sinifKapasiteleri[j];
                sinifKapasiteleri[j]=tmp;
            }
        }
    }

    ortalamaI=ogrSayisiI/sinifSayisi;
    ortalamaII=ogrSayisiII/sinifSayisi;

    printf("\nSinif sayisi: %d",sinifSayisi);                              //Bilgilerin ekrana yazdirilmasi
    printf("\nKapasiteler :");                                             //Bilgilerin ekrana yazdirilmasi

    for(i=0; i<sinifSayisi; i++)                                           //Bilgilerin ekrana yazdirilmasi
    {                                               // Toplam kapasitenin hesaplanmasi
        printf("%d  ",sinifKapasiteleri[i]);
        ttlKapasite+=sinifKapasiteleri[i];
    }

    FILE *dosyalar[sinifSayisi*2];                  // Sinif sayisi kadar I , bi okadar da II icin tanýmlanýr
    char dosyaAdi[20];

    for(j=0;j<sinifSayisi;j++)                      //I.Ogretimler sinif mevcudu Hesaplama
    {
        ortalamaI=ogrSayisiI/sinif_sayisi_yedek--;
        if(sinifKapasiteleri[j]<ortalamaI)
        {
            sinifMevcutlari[j]=sinifKapasiteleri[j];
        }
        else
        {
            sinifMevcutlari[j]=ortalamaI;
        }
        ogrSayisiI-=sinifMevcutlari[j];


    }
k=j=0;
    for(i=0;i<sinifSayisi;i++){                     //I.Ogretimleri sinif sinif dosyaya yazma
        sprintf(dosyaAdi,"EsitI.ogretim%d.txt",i);
        dosyalar[i]=fopen(dosyaAdi,"w");

        for(;k<sinifMevcutlari[i];j++){
            if(eleman[j].ogretimTuru[1]!=73){            //I.Ogretimse

            fputs(eleman[j].numara,dosyalar[i]);
            fprintf(dosyalar[i]," ");
            fputs(eleman[j].ad,dosyalar[i]);
            fprintf(dosyalar[i]," ");
            fputs(eleman[j].soyad,dosyalar[i]);
            fprintf(dosyalar[i]," ");
            fprintf(dosyalar[i],"%d ",eleman[j].kayitSirasi);
            fputs(eleman[j].ogretimTuru,dosyalar[i]);
            fprintf(dosyalar[i],"\n");
            k++;
            }
        }
        k=0;
    }


sinif_sayisi_yedek=sinifSayisi;
    for(j=0;j<sinifSayisi;j++)                      //II.Ogretimler sinif mevcudu Hesaplama
    {
        ortalamaII=ogrSayisiII/sinif_sayisi_yedek--;
        if(sinifKapasiteleri[j]<ortalamaII)
        {
            sinifMevcutlari[j]=sinifKapasiteleri[j];
        }
        else
        {
            sinifMevcutlari[j]=ortalamaII;
        }
        ogrSayisiII-=sinifMevcutlari[j];


    }
k=j=0;
    for(i=0;i<sinifSayisi;i++){                     //II.Ogretimleri sinif sinif dosyaya yazma
        sprintf(dosyaAdi,"EsitII.ogretim%d.txt",i);
        dosyalar[sinifSayisi+i]=fopen(dosyaAdi,"w");

        for(;k<sinifMevcutlari[i];j++){
            if(eleman[j].ogretimTuru[1]==73){            //II.Ogretimse

            fputs(eleman[j].numara,dosyalar[sinifSayisi+i]);
            fprintf(dosyalar[sinifSayisi+i]," ");
            fputs(eleman[j].ad,dosyalar[sinifSayisi+i]);
            fprintf(dosyalar[sinifSayisi+i]," ");
            fputs(eleman[j].soyad,dosyalar[sinifSayisi+i]);
            fprintf(dosyalar[sinifSayisi+i]," %d ",eleman[j].kayitSirasi);
            fputs(eleman[j].ogretimTuru,dosyalar[sinifSayisi+i]);
            fprintf(dosyalar[sinifSayisi+i],"\n");
            k++;
            }
        }
        k=0;
    }

    stop=clock();
    printf("esitDagilim %.3f saniye surdu.\n",((double)(stop - start) / CLOCKS_PER_SEC));
}//VoidEsitDagilim

void enAzSinifDagilim()
{

clock_t start, stop;
Label:

    printf("\nEn az sinif dagilimi \n");
char namefile[20];          //Olusturulacak dosya adi
int ttlKapasite=0;          //Siniflarin toplam kapasitesi
int i,j;                    //For elemanlari
int ss;                     //Sinif Sayisi
int tmp=0;                  //Siralama elemani
int ogrSayisiI=0,ogrSayisiII=0;
    printf("Sinif sayisini giriniz :");
    scanf("%d",&ss);

int sKapasite[ss];          //Sinif sayisi uzunlugunda kapasiteleri tutan dizi


    for(i=0; i<407-t; i++)  //Ogrencilerin ne kadari I ne kadari II Hesaplanmasi
    {

        if(eleman[i].ogretimTuru[1]==73)
        {
            ogrSayisiII++;
        }
        if(eleman[i].ogretimTuru[1]!=73)
        {
            ogrSayisiI++;
        }

    }

    printf("\n I.Ogretim toplam ogrenci sayisi : %d",ogrSayisiI);
    printf("\nII.Ogretim toplam ogrenci sayisi : %d\n",ogrSayisiII);

    for(i=0; i<ss; i++)     //Kapasitelerin kullanicidan alinmasi
    {
        printf("%d.Sinifin kapasitesini giriniz : ",i+1);
        scanf("%d",&sKapasite[i]);
    }

start = clock();

    for(i=0; i<ss; i++)     //Kapasiteleri tutan dizinin buyukten kucuge siralanmasi
    {
        for(j=0; j<ss; j++)
        {
            if (   sKapasite[i]>sKapasite[j] )
            {
                tmp=sKapasite[i];
                sKapasite[i]=sKapasite[j];
                sKapasite[j]=tmp;
            }
        }
    }

    printf("\nSinif sayisi: %d",ss);                            //Bilgilerin ekrana yazdirilmasi
    printf("\nKapasiteler :");                                  //Bilgilerin ekrana yazdirilmasi

    for(i=0; i<ss; i++)                                         //Bilgilerin ekrana yazdirilmasi
    {
        printf("%d  ",sKapasite[i]);
        ttlKapasite+=sKapasite[i];  // Toplam kapasitenin hesaplanmasi
    }

    printf("\nToplam kapasite : %d",ttlKapasite);               //Bilgilerin ekrana yazdirilmasi
    printf("\n I.Ogretim ogrenci sayisi : %d",ogrSayisiI);      //Bilgilerin ekrana yazdirilmasi
    printf("\n II.Ogretim ogrenci sayisi : %d",ogrSayisiII);    //Bilgilerin ekrana yazdirilmasi

    if(ttlKapasite<ogrSayisiI || ttlKapasite<ogrSayisiII)       //Kapasiteler ogrenci sayisindan daha az ise
    {                                                           //fonksiyonun basina geri git
        printf("\nSiniflarin toplam kapasitesi ogrenci sayisindan daha azdir.\n");
        printf("Bu sekildeyken dagitim yapamam.Lutfen sinif sayilarini ve kapasitelerini yeniden giriniz.\n\n");
        goto Label;
    }

    else{      //Kapasiteler dogru girildiyse
    printf("\n\nEn az sinif dagilimi\n");

int sinifsayisiI=0,sinifsayisiII=0;

i=0;
tmp=ogrSayisiI;
      while(tmp>0){                                         //I.Ogretim Sinif sayisi sayma
        tmp-=sKapasite[i];
        i++;
        sinifsayisiI++;
      }
      printf("\nsinif sayisi I : %d",sinifsayisiI);
i=0;
tmp=ogrSayisiII;
      while(tmp>0){                                         //II.Ogretim Sinif sayisi sayma
        tmp-=sKapasite[i];
        i++;
        sinifsayisiII++;
      }
      printf("\nsinif sayisi II : %d",sinifsayisiII);

                         //Dagilim sonrasi sinif mevcutlari ekrana yazdirma
    printf("\nI.ogretim : ");                                 //I.Ogretim icin
int q;
q=0;
    for(i=0;i+1<sinifsayisiI;i++){          //Dolu siniflari yazdir
            printf("%d ",sKapasite[i]);
            dagilim[0][i]=sKapasite[i];
            q+=sKapasite[i];
    }

tmp=ogrSayisiI;
tmp-=q;
dagilim[0][i]=tmp;
    printf("%d",tmp);                       //Yarim kalan sinifi yazdir.

    printf("\nII.Ogretim : ");                              //II.Ogretim icin
q=0;
    for(i=0;i+1<sinifsayisiII;i++){         //Dolu siniflari yazdir
            printf("%d ",sKapasite[i]);
            dagilim[1][i]=sKapasite[i];
            q+=sKapasite[i];
    }

tmp=ogrSayisiII;
tmp-=q;
dagilim[1][i]=tmp;
    printf("%d",tmp);                       //Yarim kalan sinifi yazdir.
    printf("\n");
    }

int dosyaSayisi=i+1;
FILE *dosyalar[dosyaSayisi];            // dosya sayisi=i+1
char dosyaAdi[20];

int drd[2][20];

drd[0][0]=dagilim[0][0];
for(i=1;i<dosyaSayisi+1;i++){
    drd[0][i]=dagilim[0][i]+drd[0][i-1];
}
drd[1][0]=dagilim[1][0];
for(i=1;i<dosyaSayisi+1;i++){
    drd[1][i]=dagilim[1][i]+drd[1][i-1];
}

int k=0;
j=0;
    for(i=0;i<dosyaSayisi;i++){                     //I.Ogretimleri sinif sinif dosyaya yazma
        sprintf(dosyaAdi,"enAzI.ogretim%d.txt",i);
        dosyalar[i]=fopen(dosyaAdi,"w");

        for(;k<drd[0][i];j++){
            if(eleman[j].ogretimTuru[1]!=73){            //I.Ogretimse

            fputs(eleman[j].numara,dosyalar[i]);
            fprintf(dosyalar[i]," ");
            fputs(eleman[j].ad,dosyalar[i]);
            fprintf(dosyalar[i]," ");
            fputs(eleman[j].soyad,dosyalar[i]);
            fprintf(dosyalar[i]," ");
            fprintf(dosyalar[i],"%d ",eleman[j].kayitSirasi);
            fputs(eleman[j].ogretimTuru,dosyalar[i]);
            fprintf(dosyalar[i],"\n");
            k++;
            }
        }
    }
k=0,j=0;
    for(i=0;i<dosyaSayisi;i++){                     //II.Ogretimleri sinif sinif dosyaya yazma
        sprintf(dosyaAdi,"enAzII.ogretim%d.txt",i);
        dosyalar[i]=fopen(dosyaAdi,"w");

        for(;k<drd[1][i];j++){
            if(eleman[j].ogretimTuru[1]==73){            //II.Ogretimse

            fputs(eleman[j].numara,dosyalar[i]);
            fprintf(dosyalar[i]," ");
            fputs(eleman[j].ad,dosyalar[i]);
            fprintf(dosyalar[i]," ");
            fputs(eleman[j].soyad,dosyalar[i]);
            fprintf(dosyalar[i]," ");
            fprintf(dosyalar[i],"%d ",eleman[j].kayitSirasi);
            fputs(eleman[j].ogretimTuru,dosyalar[i]);
            fprintf(dosyalar[i],"\n");
            k++;
            }
        }
    }
    stop=clock();
    printf("enAzSinifDagilim %.3f saniye surdu.\n",((double)(stop - start) / CLOCKS_PER_SEC));
}

//Bismillahirrahmanirrahim
int main()
{

    structaCek();
    ayniKisileriBul();
    kayitSiraGuncelle();
    noAtama();
    guncelleDosyayaYaz();
    esitDagilim();
    enAzSinifDagilim();

    //ekranaYaz();



    return 0;
}
