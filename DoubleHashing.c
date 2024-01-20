#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct HashNode {								// Hash tablosu için eleman yapisi
    int key;									// key kullanicinin anahtari
    int deleted;								// deleted silme ishlemi ichin bayragi temsil ediyor (silinmishse deleted=1 gibi)
};

int hash1(int key, int tableSize){								// Double Hash ishlemi icin ilk hash fonksiyonu
        return key % tableSize;
} 
        
int hash2(int key, int tableSize){								// Double Hash ishlemi icin ikinci hash fonksiyonu
        int m2;
        m2= tableSize-2;
         return 1 + (key % m2);
    
}
int hashFunction(int key, int i, int tableSize) {				// Double Hash ishlemi icin hash fonksiyonu
    
    return (hash1(key,tableSize) + i*hash2(key,tableSize)) % tableSize;
    
}

 int horner(char *kelime) {								// Horner Fonksiyonu. Horner metodu girilen char tipinde kelimenin ASCII tablosuna gore int tipinde key 
     int result = 0;									// degerini donduren metoddur.
    int kelimeBoyutu = strlen(kelime);

		int i;
    for ( i = 0; i < kelimeBoyutu; i++) {
        char currentChar = (kelime[i] >= 'a' && kelime[i] <= 'z') ? (kelime[i] - 'a' + 'A') : kelime[i];
        result = result * 26 + (currentChar - 'A' + 1);
    }

    return result;
}
void reverseHorner(unsigned int value, char *kelime) {				//reverseHorner fonksiyonu Horner metoduyla donushturulen int degerinin karshilik geldighi char degerini yani
    int index = 0;													// kullanici ismi (username) i bulan fonksiyondur.

    while (value > 0) {
        int deger = (value - 1) % 26;
        kelime[index++] = 'A' + deger;
        value = (value - 1) / 26;
    }

    kelime[index] = '\0';

    
    
    int left = 0, right = index - 1;	
    while (right>left) {											// Elde edilen kelimenin ters çevrilmesi gerekiyor.
        // Swap			
        char temp = kelime[left];									// Bu nedenle, kelimenin karakterlerini ters sirayla yer degistiriliyor.
        kelime[left] = kelime[right];
        kelime[right] = temp;

		right--;
        left++;
        
    }
}


// Hash tablosuna ekleme (double hashing)
void insert(struct HashNode* table, char* isim, int tableSize) {				// Normal Mod secildiginde Hash tablosuna doubleHashing mantigiyle ekleme yapan fonksiyon
    
    int key = horner(isim);														// kullaniciIsminin karsilik gelen ASCII degerini Horner metoduyla bulunmasi.
    
    int index = hashFunction(key,0,tableSize);									// ilk bashta i=0 oldughu ichin DoubleHash fonksiyonu

    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));			// eklenecek kullanicinin ismi ve 'deleted' bayrak bilgisini tutmak icin yeniDugum
   
    newNode->key = key;																		// kullanicidan alinan userNamein karlisik geldigi hornerDegerini yeniDugume atama
    newNode->deleted = 0;																	// ilk kez ekleneceghi ichin deleted flag'ine 0 atama

    int i=0;
    while (table[index].key != -1 && i<= tableSize && table[index].key != key)  {
        // Double Hashing
        i++;
        index = hashFunction(key,i,tableSize);											// while dongusunde doubleHashing mantigiyla bosh index arama ishlemi.

    }
    
    if (i>tableSize) {
    	printf ("tablo dolu...");													//while ichindeki kontrol degeri (i) tablo boyutu ashmisha tablo dolmushtur.
    	return;
	}
    else  if(table[index].key == key && table [index].deleted == 0)
{
	printf ("Bu kullanici zaten mevcut oldugu icin eklenmedi");						// eklemeye chalishilan kullanici zaten mevcutsa 
	return;
}

else if(table[index].key == key && table [index].deleted == 1)
{
	printf ("Silinmish %s kullanicisi %d indeksine tekrar geri eklendi", isim, index);				// kullanici onceden silinmishse tekrar eklemek (deleted flag'ini tekrar 0 yapar)
	table [index].deleted = 0;
	return;
}

else{
    table[index] = *newNode;
}
}



void insertDebug(struct HashNode* table, char* isim, int tableSize) {							// Debug Mod secildiginde Hash tablosuna doubleHashing mantigiyle ekleme yapan fonksiyon
    
    int key = horner(isim);																		//kullaniciIsminin karsilik gelen ASCII degerini Horner metoduyla bulunmasi.
    
    int index = hashFunction(key,0,tableSize);													//	 ilk bashta i=0 oldughu ichin DoubleHash fonksiyonu

    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));			//hashNode veriyapisi tipinde tabloya ekleme yapmak ichin yeniDugum olushturma
    

    newNode->key = key;																	// kullanicidan alinan userNamein karlisik geldigi hornerDegerini yeniDugume atama
    newNode->deleted = 0;																// ilk kez ekleneceghi ichin deleted flag'ine 0 atama

    int i=0;
    while (table[index].key != -1 && i<= tableSize && table[index].key != key) {
        // Double Hashing
        printf ("%d horner kodlu %s kullanicisi %d indeksi dolu oldugu icin eklenemedi\n",key, isim, index);		// DebugMod olarak kontrol edilen indekslerin kullaniciya dondurulmesi.
        i++;
        index = hashFunction(key,i,tableSize);															// DoubleHashing mantigiyla hashTablosunda bosh dughum arama ishlemi
    }

    
    if (i>tableSize) {																	// kontrolDegeri (i) tablo boyutunu ashtigi durumda while dongusunden cikmish oluyor 
    	printf ("tablo dolu...");														// hashTablosunda bosh bir yer bulunmamishtir yani tablo Doludur
    	return;
	}
    
   else if(table[index].key == key && table [index].deleted == 0)
{
	printf ("Bu kullanici zaten mevcut oldugu icin eklenmedi");						
	return;
}  

else if(table[index].key == key && table [index].deleted == 1)
{
	printf ("Silinmish %s kullanicisi %d indeksine tekrar geri eklendi", isim, index);
	table [index].deleted = 0;
	return;
}

else{

	printf ("%d horner kodlu %s kullanicisi %d indeksine eklendi\n", key, isim, index);
    table[index] = *newNode;
}
}



// Hash tablosunda arama
void search(struct HashNode* table,char* isim, int tableSize) {  	// Normal Mod secildiginde Hash tablosunda doubleHashing mantigiyle arama yapan fonksiyon
    
    int key = horner (isim);											// kullaniciIsminin karsilik gelen ASCII degerini Horner metoduyla bulunmasi.
    
    int index = hashFunction(key,0,tableSize);							// DoubleHashing
    int i=0;
    while (table[index].key != -1 && i<tableSize && table[index].deleted == 0) {
        if (table[index].key == key) {
            
            printf ("%s kullanicisi %d indeksinde bulundu \n", isim, index);
            return;																		// Kullanici bulundu
        }

        i++;
        index = hashFunction(key,i,tableSize);						//DoubleHashing
    }
    if(table[index].deleted == 1)
	{
    	printf ("%s kullanicisi silinmishtir \n", isim);
	}
	else{
    printf("boyle bir kullanici kayitlarda yok "); // Anahtar bulunamadi
}

}



void searchDebug(struct HashNode* table,char* isim, int tableSize) {    // Debug Mod secildiginde Hash tablosunda doubleHashing mantigiyle arama yapan fonksiyon
    
    int key = horner (isim);
    
    int index = hashFunction(key,0,tableSize);
    int i=0;
    while (table[index].key != -1 && i<tableSize && table[index].deleted == 0) {
        if (table[index].key == key) {
            
            printf ("%s kullanicisi %d indeksinde bulundu \n", isim, index);
            return;// Anahtar bulundu
        }
			 printf ("%s kullanicisi %d indeksinde bulunamadi \n", isim, index);
        // Double hashing
        i++;
        index = hashFunction(key,i,tableSize);
    }
    if(table[index].deleted == 1)
	{
    	printf ("%s kullanicisi silinmishtir \n", isim);
	}
	else{
    printf("boyle bir kullanici kayitlarda yok "); // kullanici bulunamadi
}

}


// Hash tablosundan silme
void delete(struct HashNode* table,char* isim, int tableSize) {
    
    int key = horner (isim);
    
    int index = hashFunction(key,0,tableSize);
        int i=0;
    while (table[index].key != -1 && i<=tableSize) {
        if (table[index].key == key) {
            
           
            table[index].deleted = 1; 										// fiziksel silme deghil deleted flag'i ile silinmish olarak tanimlama ishlemi
            printf ("%s isimli kayit bashariyla silindi\n", isim);
            return;
        }

        // Double Hashing 
         i++;
        index = hashFunction(key,i,tableSize);
    }
    
   
    	printf ("boyle bir kullanici kayitlarda yok \n");

}


void deleteDebug(struct HashNode* table,char* isim, int tableSize) { 				// debug mod sechildiginde silme ishlemi
    
    int key = horner (isim);
    
    int index = hashFunction(key,0,tableSize);
        int i=0;
    while (table[index].key != -1) {
        if (table[index].key == key) {
            
            
            table[index].deleted = 1;													// fiziksel silme deghil deleted flag'i ile silinmish olarak tanimlama ishlemi
            printf ("%s isimli kayit %d indeksinde bulundu ve  bashariyla silindi\n", isim, index);
            return;
        }
        // Double Hashing 
        printf ("%s kullanicisi %d indeksinde bulunamadi \n", isim, index);				// Debug mod secildighi ichin kontrol edilen indeksler kullaniciya bilidiriliyor.
         i++;
        index = hashFunction(key,i,tableSize);											// double Hashing yontemiyle bir sonraki indeks kontrol edilecektir.
    }
    
    printf ("boyle bir kullanici kayitlarda yok \n");									// girilen kullanici tabloda bulunmuyorsa while dongusunden chikilmihstir ve kullaniciya
    																					//bildirilmishtir
}


void printHashTable(struct HashNode* table,int tableSize) {								// Hash tablosunu yazdirma
	int i;
    for ( i = 0; i < tableSize; i++) {
        if (table[i].key != -1) {
            
             char reversedWord[10]; 
             
             
              reverseHorner(table[i].key, reversedWord);
            
            printf("Index: %d, Kullanici: %s,  silinme durumu: %d \n", i, reversedWord, table[i].deleted);
        } else {
            printf("Index: %d, Empty\n", i);
        }
    }
}

int isPrime(int n) {												// hesaplanan tablo boyutunun asal olup olmadighini kontrol eden fonksiyon
    if (n <= 1) {
        return 0;
    }
    int i;
    for (i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {										// asal degildir return 0 doner.
            return 0;
        }
    }
    return 1;											    	// asaldir.
}

int findNextPrime(int n) {									// heasplanan tablo boyutu asal degilse bir sonraki en kucuk asal sayiyi bulan fonksiyon
    while (!isPrime(n)) {
        n++;
    }
    return n;
}



struct HashNode* tabloDuzenle(struct HashNode* table, int tableSize) {						// REHASH ISHLEMI 
	
    struct HashNode* yedekTablo = (struct HashNode*)malloc(tableSize * sizeof(struct HashNode));		// ReHashing ishlemi ichin HashNode veriyapisi tipinde 
																										// yeni tablo olushturulmushtur
  
    // Tabloyu baslangiçta bosaltma
    int i;																				// yedekTabloyu initialize (bashlatma) ishlemi
    for (i = 0; i < tableSize; i++) {
        yedekTablo[i].key = -1;														 // -1, bos bir elemani temsil eder
    }

    // 
    for (i = 0; i < tableSize; i++) {
        if (table[i].deleted == 0) {
        	
            yedekTablo[i] = table[i];
        } else if (table[i].deleted == 1) {
        
        	yedekTablo[i].key = -1 ;
        }
    }

    // Eski tabloyu serbest birakma
    free(table);
    
    printf ("Tablo Duzenlenmesi Sonucu Tablo\n");
    
     printHashTable(yedekTablo, tableSize);

    return yedekTablo; // Yeni tabloyu döndür
}




struct HashNode* tabloDuzenleDebug (struct HashNode* table, int tableSize) 								// ReHash Debug Mod secildiginde
{
	
	 struct HashNode* yedekTablo = (struct HashNode*)malloc(tableSize * sizeof(struct HashNode));			// ReHashing ishlemi ichin HashNode veriyapisi tipinde 
	 																										// yedekTablo olushturulmushtur
	 
	 
	  printf ("Tablo Duzenlenmeden Once Tablo\n\n");					//Debug mod secildighi ichin tablonun onceki halini ekrana bastirilma ishlemi
    
     printHashTable(table, tableSize);

    // Tabloyu baslangiçta bosaltma
    int i;																				// yedekTabloyu initialize (bashlatma) ishlemi
    for (i = 0; i < tableSize; i++) {
        yedekTablo[i].key = -1; // -1, bos bir elemani temsil eder
    }

    // 
    for (i = 0; i < tableSize; i++) {
        if (table[i].deleted == 0) {
        	
            yedekTablo[i] = table[i];
        } else if (table[i].deleted == 1) {
           char reversedWord[10]; 
             
              reverseHorner(table[i].key, reversedWord);
        	
        	
        	printf ("%d indeksinde bulunan %s kullancisi silindigi icin yeni tabloya eklenmeyecek\n\n", i,reversedWord);
        	
        	yedekTablo[i].key = -1 ;
        }
    }

    // Eski tabloyu serbest birakma
    free(table);
    
    printf ("Tablo Duzenlenmesi Sonucu Tablo (Silinmeyen Kullanicilar)\n\n");
    
     printHashTable(yedekTablo, tableSize);

    return yedekTablo; // Yeni tabloyu dondurme
}

  int main() {
    int kullaniciSayisi;														// kullanici tarafindan girilen user(kullanici) sayisi
    double loadFactor;															// kullanici tarafindan girilen loadFactor degeri
    int tableSize;																// kullanicidan alinan eleman sayisi ve loadfactor degerlerine gore hesaplanan tablo boyutu
    
    printf("tabloya eklenecek kullanici sayisini giriniz: ");
    scanf("%d", &kullaniciSayisi);												//kullanicidan input alinmasi ishlemi	- Kullanici Sayisi

    
    printf ("load factor degerini giriniz: ");
    scanf("%lf", &loadFactor);													//kullanicidan input alinmasi ishlemi - LoadFactor
    
   int  tablo_degeri = kullaniciSayisi/loadFactor;							// tablo boyutunun asal olma durumunu kontrol etmek ichin geicici tablo_degeri
    
    if(isPrime(tablo_degeri)){												
        tableSize = tablo_degeri;											// gecici tablo_degeri asalsa tablo boyutuna atama ishlemi
    }
    else {
        tableSize = findNextPrime (tablo_degeri);							// gecici tablo_degeri asal degilse findNextPrime fonksiyonuyla bir sonraki en kucuk asal degeri
    }																		// tablo boyutuna atama ishlemi
    
    // hash tablomuz
    
    struct HashNode* table = (struct HashNode*)malloc(tableSize * sizeof(struct HashNode));			// HashNode veriyapisi tipinde tablo olushturma ishlemi

    // Tabloyu baslangiçta bosaltma
    int i;
    for ( i = 0; i < tableSize; i++) {											// tabloyu initialize (bashlatma) ishlemi
        table[i].key = -1; 														// -1, bos bir elemani temsil eder
    }
    
    int choice;																// kullanicinin secheceghi ishlemi temsil eder (Normal Mod)
    int mod;																// kullanicinin secheceghi mod ishlemini temsil eder
    int choice2;															// kullanicinin secheceghi ishlemi temsil eder (Debug Mod)
    char userName[50];														// kullanicidan alinacak olan userName (kullaniciIsmi)
    
    do{
    	printf("\n1. Normal Mod \n2. Debug Mod \n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &mod);
    	
    	switch (mod)
		{
    		case 1:     do {
         printf("\n1. Kullanici ekle\n2. Kullanici Sil\n3. Hash tablosunu goster\n4. Kullanici Ara \n5. Tabloyu duzenle(reHash)\n6. Bir onceki menuye geri don\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the username to insert: ");
                scanf("%s", userName);
                insert(table, userName,tableSize);
                break;
            case 2:
                printf("Enter the username to remove: ");
                scanf("%s", userName);
                delete(table, userName,tableSize);
                break;
            case 3:
                printHashTable(table, tableSize);
                break;
                
            case 4:
            	printf ("aramak istediginiz kullaniciyi giriniz: ");
            	scanf("%s", userName);
            	search(table,userName,tableSize);
            	break;
            	
            case 5:
               printf("rehashing.\n\n");
                 table = tabloDuzenle(table, tableSize);
                break;
			    
            case 6:
                printf("Backing to menu.\n");
                break;
                
            default:
                printf("Hatali Girish. Lutfen tekrar deneyin...\n");
        }

    } while (choice != 6);
    
    case 2: 
     do {
        printf("\n1. Kullanici ekle\n2. Kullanici Sil\n3. Hash tablosunu goster\n4. Kullanici Ara \n5. Tabloyu duzenle(reHash)\n6. Bir onceki menuye geri don\n");
        printf("Enter your choice: ");
        scanf("%d", &choice2);

        switch (choice2) {
            case 1:
                printf("Enter the username to insert: ");
                scanf("%s", userName);
                insertDebug(table, userName,tableSize);
              
                break;
            case 2:
                printf("Enter the username to remove: ");
                scanf("%s", userName);
                deleteDebug(table, userName,tableSize);
                break;
            case 3:
                printHashTable(table, tableSize);
                break;
                
            case 4:
            	printf ("aramak istediginiz kullaniciyi giriniz: ");
            	scanf("%s", userName);
            	searchDebug(table, userName,tableSize);
            	break;
           	
       	   case 5:
               printf("rehashing.\n\n");
                 table = tabloDuzenleDebug(table, tableSize);
                break;
			    
            case 6:
                printf("Backing to menu.\n");
                break;
                
               default:
                printf("Hatali Girish. Lutfen tekrar deneyin...\n");
        }
        
    } while (choice2 != 6);
		}	
			
	} while (mod!=3);
    
    return 0;
}
