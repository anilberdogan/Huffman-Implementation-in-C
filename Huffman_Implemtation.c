#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node {
	char harf;
	int frekans;
	struct node * left;			//her node'un 1 next'i ,1 left ,1 de right child'� olacak
	struct node * right;		
	struct node * next;
};


	//fonksiyonlar� tan�ml�yorum
	struct node* Kontrol(char*,struct node*);
	struct node * Sirala(struct node* );
	struct node* treeCevirme(struct node*);
	void treeYazdir(struct node*);
	struct node* SiraliEkle(struct node *,struct node* );
	struct node* InsertNode (char,struct node* );
	void levelPrint(struct node*, int);
	int height(struct node* );




	int main (){
		
		
		int i=0;
		char araci,yazi[500];
		
		
		
		printf("Yaziyi giriniz :");
		gets(yazi);
		
	
		struct node * root = (struct node *) malloc (sizeof(struct node));
		
		
		
		if(yazi[i]){				// EGER BIR YAZI G�R�LD�YSE PROGRAM BA�LIYOR AKS� TAKD�R DE B�T�YOR	
			araci=yazi[i];
			i++;
	
		root->harf=araci;			// �LK NODE'U MA�N DE YERLE�T�R�YORUM
		root->frekans=1;											
		root->next=NULL;
		root->left=NULL;
		root->right=NULL;		

		}
			
		else
			printf("Herhangi bir yazi girilmedi");		//HERHANG� B�R �EY G�R�LMED�YSE �IKIYOR
		
		Kontrol(yazi,root);				
		
		root=Sirala(root);
		
		root=treeCevirme(root);
		
		
		treeYazdir(root);
		
		
}
	
	
	
	
	//FONKS�YONLAR
	
	struct node* InsertNode (char adres,struct node* root){			//Linkedliste eleman ekleme
		while(root->next!=NULL)
			root=root->next;	
			
			struct node* newnode = (struct node *) malloc (sizeof(struct node));
			newnode->harf=adres;
			newnode->frekans=1;							// �lk defa olu�tu�u i�in frekans� 1 olacak.
			newnode->next=NULL;
			newnode->left=NULL;							//sona eklendi�inden next'i null olacak ve her eklenen node'un left ve right'�n� 
			newnode->right=NULL;						//ilk de�eri olmad���ndan NULL a e�itliyorum
			root->next=newnode;	
			return newnode;
	}
	




	struct node* Kontrol(char *yazi,struct node* root){
		
		int kontrol,i=1;
		char araci; 
		struct node* iter;
		struct node* temp;
		
				while(yazi[i]){				// Yaz� bitene kadar devam ediyor
			kontrol=0;						
			iter=root;
			araci=yazi[i];
			
			while(iter != NULL && kontrol ==0 ){
			
				if(iter->harf == araci){		// e�er girilen harf daha �nceden varsa frekans�n� 1 artt�r�yor
					iter->frekans++;
					kontrol=1;					// i�lem ger�ekle�ti�i i�in d�g�nde ��k�yor
				}
				else{
					iter=iter->next;			// e�er harfler e�le�mediyse d�ng�n�n sonuna kadar deneyerek devam ediyor.
				
				}
					
			}
			
			if(kontrol==0){
				temp = InsertNode(araci,root);		//Bu durum e�le�me olmad��� zaman ger�ekle�iyor
													// Listeye ekleme i�lemi yap�yorum
				
			}
			
			i++;							// sonraki elemana ge�iyorum
				
		}	
		
	}
	
	

	
	struct node * Sirala(struct node* root){  // LinkedList Insertion sort
		
		int i,sayitut,kontrol=0;
		char harftut;
		struct node* tmp;						
		struct node* tmpicfor;
		struct node* degisken;
		
		
		for(tmp=root->next;tmp!=NULL;tmp=tmp->next){	// Insertion sort
			
			kontrol=0;								//her turda �nceki tur yerine yerle�tirdi�im node'un bir sonraki 
			degisken=tmp;							// node'un dan ba�layaca��m i�in for'u bu �ekilde tan�mlad�m.
			harftut=degisken->harf;					// De�i�tirece�im node'un de�erlerini tutuyorum.
			sayitut=degisken->frekans;
			
			while(kontrol==0){
				
				tmpicfor=root;
				
				if(degisken == root){		// bu eleman�n sort i�lemi bitti�i anlam�na gelir ��nk� a��a��da her tur bir geri geliyorum
					kontrol=1;
				}
				
				
				while(tmpicfor->next!=degisken && kontrol!=1){			// node'u bir �nceki elemanla kar��la�t�rmak i�in 
					tmpicfor=tmpicfor->next;							//tmpicforu node'un arkas�na kadar ilerletiyorum
				}
				
				
				if(kontrol!=1){          // Node'u yerle�tirdim ��k�yorum
					
					
					
				if(tmpicfor->frekans > sayitut ){  // E�er s�ralamak istedi�im node'um kendinden bir �nceki node'dan d���kse yer de�i�tiriyor.
					
					degisken->frekans=tmpicfor->frekans;
					degisken->harf=tmpicfor->harf;
					
					tmpicfor->frekans=sayitut;
					tmpicfor->harf=harftut;
					degisken=tmpicfor;                // degisken yani s�ralamak istedi�im node bir ad�m geri geliyor. Bu sayede bir sonraki turda
													  // tekrar bir �nceki eleman�yla kar��la�t�rabiliyorum. Dolay�s�yla Insertion sort oluyor.
													  // e�er geri giderek root'a ula��rsa yukar�daki ilk kontrolle ��k�yor.
				}
				
				
				
				else{									
					kontrol=1;				// Do�ru s�rada ��kabilirim				
				}
			
				}
			
			}
			
			
		}
		
		return root;

	}
	
	
	
	
	struct node* SiraliEkle(struct node *root,struct node* yeni){	// Bu i�lem yeni �retilen node'un do�rudan s�ras�n�n bulunup 
	
	struct node* temp;												// oraya yerle�tirilmesini sa�l�yor.
	temp=root;
	
	if(root==NULL || yeni->frekans < root->frekans){		//e�er root NULL ise zaten yeni node art�k root olacak dolay�s�yla yeni'yi d�nd�r�yoruz.
															//e�er frekans de�eri root'tan k���kse s�ral� ekledi�imizden yine yeniyi d�nd�rece�iz.
		yeni->next=root;
		return yeni;
	
	}
	
	while(root->next!=NULL && root->next->frekans <= yeni->frekans){	//yeninin yerini bulana kadar ilerliyorum e�er sona eklenecekse 
		root=root->next;												//NULL kontrol�yle ��k�yorum
		
	}
	
	yeni->next=root->next;					//yeni'yi yerle�tiriyorum
	root->next=yeni;
	return temp;							// temp'i ba�ta root'a e�itlemi�tim bu ko�ulda root de�i�medi�inden ayn� �ekilde geri d�n�yorum.
	
	
}


	
	struct node* treeCevirme(struct node*root){
		
		
		int yenifrekans;

		struct node* bas = root;
		struct node* ikinci=root->next;
		
		
		while(root->next!=NULL){
			
			bas=root;					//root ' un nexti NULL de�ilse root'u basa , nextini ikinciye e�itliyorum ��nk� frekanslar�n� 
			ikinci=root->next;			// toplamam gerekiyor. Bu i�lem SiraliEkle2 root d�nd�rd��� i�in root->next'i null olana kadar  
										//devam edecek ve yeni node �retip root ve rootun nextini bas ve ikinci'ye atmaya devam edece�im.
											
			struct node * yeni=(struct node*)malloc(sizeof(struct node)); //ekleyece�im node'u olu�turuyorum
				
			yeni->harf=NULL;		// yeni node iki child'�n toplam� olaca�� i�in harfi olmayacak
			
			
			yeni->frekans=bas->frekans + ikinci->frekans;	//yeni node'un frekans� iki child'�n toplam�
			yeni->left=bas;									//yeni node'un sol child'� root
			yeni->right=ikinci;								//yeni node'un sa� child'� root->next
			
			root=root->next->next;							//yeni root ikinci'nin nexti
	
			root= SiraliEkle(root,yeni);					//ard�ndan olu�turdu�um node'un frekans�n�n de�erine g�re s�ral� ekliyorum.

			
		}
		
		return root;
	
	}




		int height(struct node* root) {

	// E�er root== NULL olursa yapraklara ula��yoruz
	
    if (root==NULL) 
        return 0; 
        
    else
    { 
        // Her alt a�ac�n y�ksekli�ini hesapl�yorum
        int lheight = height(root->left); 
        int rheight = height(root->right); 
  
        // Y�ksekli�i fazla olan a�ac� kullan�yorum
        if (lheight > rheight){
            return (lheight+1); 
        }
        else{
        	return (rheight+1);
        }
    } 
} 

	


	void levelPrint(struct node* root, int level){


	if (root == NULL){
		printf(" ");				// null ise bosluk yaz ve bir �nceki fonksiyona d�n
		return;
		
	}
	if (level == 0){
	 
		if(root->harf)
			printf("%d%c ", root->frekans, root->harf);		// level 0 a e�itlendi�inde yazmaya ba�la onun d���nda devam et
		else
			printf("%d  ", root->frekans);
			
	}
	else if (level > 0){
		levelPrint(root->left, level-1); 
        levelPrint(root->right, level-1);
	}

}
	
	
	

	
	void treeYazdir(struct node* root){

	int i;
	
	int n = height(root);				// n tree'nin y�ksekli�i

	
	for(i = 0; i < n; i++){
		levelPrint(root, i);			// her level� bast�rd���m yer
		printf("\n");
	}
}
	
		
