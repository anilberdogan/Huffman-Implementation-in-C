#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node {
	char harf;
	int frekans;
	struct node * left;			//her node'un 1 next'i ,1 left ,1 de right child'ý olacak
	struct node * right;		
	struct node * next;
};


	//fonksiyonlarý tanýmlýyorum
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
		
		
		
		if(yazi[i]){				// EGER BIR YAZI GÝRÝLDÝYSE PROGRAM BAÞLIYOR AKSÝ TAKDÝR DE BÝTÝYOR	
			araci=yazi[i];
			i++;
	
		root->harf=araci;			// ÝLK NODE'U MAÝN DE YERLEÞTÝRÝYORUM
		root->frekans=1;											
		root->next=NULL;
		root->left=NULL;
		root->right=NULL;		

		}
			
		else
			printf("Herhangi bir yazi girilmedi");		//HERHANGÝ BÝR ÞEY GÝRÝLMEDÝYSE ÇIKIYOR
		
		Kontrol(yazi,root);				
		
		root=Sirala(root);
		
		root=treeCevirme(root);
		
		
		treeYazdir(root);
		
		
}
	
	
	
	
	//FONKSÝYONLAR
	
	struct node* InsertNode (char adres,struct node* root){			//Linkedliste eleman ekleme
		while(root->next!=NULL)
			root=root->next;	
			
			struct node* newnode = (struct node *) malloc (sizeof(struct node));
			newnode->harf=adres;
			newnode->frekans=1;							// Ýlk defa oluþtuðu için frekansý 1 olacak.
			newnode->next=NULL;
			newnode->left=NULL;							//sona eklendiðinden next'i null olacak ve her eklenen node'un left ve right'ýný 
			newnode->right=NULL;						//ilk deðeri olmadýðýndan NULL a eþitliyorum
			root->next=newnode;	
			return newnode;
	}
	




	struct node* Kontrol(char *yazi,struct node* root){
		
		int kontrol,i=1;
		char araci; 
		struct node* iter;
		struct node* temp;
		
				while(yazi[i]){				// Yazý bitene kadar devam ediyor
			kontrol=0;						
			iter=root;
			araci=yazi[i];
			
			while(iter != NULL && kontrol ==0 ){
			
				if(iter->harf == araci){		// eðer girilen harf daha önceden varsa frekansýný 1 arttýrýyor
					iter->frekans++;
					kontrol=1;					// iþlem gerçekleþtiði için dögünde çýkýyor
				}
				else{
					iter=iter->next;			// eðer harfler eþleþmediyse döngünün sonuna kadar deneyerek devam ediyor.
				
				}
					
			}
			
			if(kontrol==0){
				temp = InsertNode(araci,root);		//Bu durum eþleþme olmadýðý zaman gerçekleþiyor
													// Listeye ekleme iþlemi yapýyorum
				
			}
			
			i++;							// sonraki elemana geçiyorum
				
		}	
		
	}
	
	

	
	struct node * Sirala(struct node* root){  // LinkedList Insertion sort
		
		int i,sayitut,kontrol=0;
		char harftut;
		struct node* tmp;						
		struct node* tmpicfor;
		struct node* degisken;
		
		
		for(tmp=root->next;tmp!=NULL;tmp=tmp->next){	// Insertion sort
			
			kontrol=0;								//her turda önceki tur yerine yerleþtirdiðim node'un bir sonraki 
			degisken=tmp;							// node'un dan baþlayacaðým için for'u bu þekilde tanýmladým.
			harftut=degisken->harf;					// Deðiþtireceðim node'un deðerlerini tutuyorum.
			sayitut=degisken->frekans;
			
			while(kontrol==0){
				
				tmpicfor=root;
				
				if(degisken == root){		// bu elemanýn sort iþlemi bittiði anlamýna gelir çünkü aþþaðýda her tur bir geri geliyorum
					kontrol=1;
				}
				
				
				while(tmpicfor->next!=degisken && kontrol!=1){			// node'u bir önceki elemanla karþýlaþtýrmak için 
					tmpicfor=tmpicfor->next;							//tmpicforu node'un arkasýna kadar ilerletiyorum
				}
				
				
				if(kontrol!=1){          // Node'u yerleþtirdim çýkýyorum
					
					
					
				if(tmpicfor->frekans > sayitut ){  // Eðer sýralamak istediðim node'um kendinden bir önceki node'dan düþükse yer deðiþtiriyor.
					
					degisken->frekans=tmpicfor->frekans;
					degisken->harf=tmpicfor->harf;
					
					tmpicfor->frekans=sayitut;
					tmpicfor->harf=harftut;
					degisken=tmpicfor;                // degisken yani sýralamak istediðim node bir adým geri geliyor. Bu sayede bir sonraki turda
													  // tekrar bir önceki elemanýyla karþýlaþtýrabiliyorum. Dolayýsýyla Insertion sort oluyor.
													  // eðer geri giderek root'a ulaþýrsa yukarýdaki ilk kontrolle çýkýyor.
				}
				
				
				
				else{									
					kontrol=1;				// Doðru sýrada çýkabilirim				
				}
			
				}
			
			}
			
			
		}
		
		return root;

	}
	
	
	
	
	struct node* SiraliEkle(struct node *root,struct node* yeni){	// Bu iþlem yeni üretilen node'un doðrudan sýrasýnýn bulunup 
	
	struct node* temp;												// oraya yerleþtirilmesini saðlýyor.
	temp=root;
	
	if(root==NULL || yeni->frekans < root->frekans){		//eðer root NULL ise zaten yeni node artýk root olacak dolayýsýyla yeni'yi döndürüyoruz.
															//eðer frekans deðeri root'tan küçükse sýralý eklediðimizden yine yeniyi döndüreceðiz.
		yeni->next=root;
		return yeni;
	
	}
	
	while(root->next!=NULL && root->next->frekans <= yeni->frekans){	//yeninin yerini bulana kadar ilerliyorum eðer sona eklenecekse 
		root=root->next;												//NULL kontrolüyle çýkýyorum
		
	}
	
	yeni->next=root->next;					//yeni'yi yerleþtiriyorum
	root->next=yeni;
	return temp;							// temp'i baþta root'a eþitlemiþtim bu koþulda root deðiþmediðinden ayný þekilde geri dönüyorum.
	
	
}


	
	struct node* treeCevirme(struct node*root){
		
		
		int yenifrekans;

		struct node* bas = root;
		struct node* ikinci=root->next;
		
		
		while(root->next!=NULL){
			
			bas=root;					//root ' un nexti NULL deðilse root'u basa , nextini ikinciye eþitliyorum çünkü frekanslarýný 
			ikinci=root->next;			// toplamam gerekiyor. Bu iþlem SiraliEkle2 root döndürdüðü için root->next'i null olana kadar  
										//devam edecek ve yeni node üretip root ve rootun nextini bas ve ikinci'ye atmaya devam edeceðim.
											
			struct node * yeni=(struct node*)malloc(sizeof(struct node)); //ekleyeceðim node'u oluþturuyorum
				
			yeni->harf=NULL;		// yeni node iki child'ýn toplamý olacaðý için harfi olmayacak
			
			
			yeni->frekans=bas->frekans + ikinci->frekans;	//yeni node'un frekansý iki child'ýn toplamý
			yeni->left=bas;									//yeni node'un sol child'ý root
			yeni->right=ikinci;								//yeni node'un sað child'ý root->next
			
			root=root->next->next;							//yeni root ikinci'nin nexti
	
			root= SiraliEkle(root,yeni);					//ardýndan oluþturduðum node'un frekansýnýn deðerine göre sýralý ekliyorum.

			
		}
		
		return root;
	
	}




		int height(struct node* root) {

	// Eðer root== NULL olursa yapraklara ulaþýyoruz
	
    if (root==NULL) 
        return 0; 
        
    else
    { 
        // Her alt aðacýn yüksekliðini hesaplýyorum
        int lheight = height(root->left); 
        int rheight = height(root->right); 
  
        // Yüksekliði fazla olan aðacý kullanýyorum
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
		printf(" ");				// null ise bosluk yaz ve bir önceki fonksiyona dön
		return;
		
	}
	if (level == 0){
	 
		if(root->harf)
			printf("%d%c ", root->frekans, root->harf);		// level 0 a eþitlendiðinde yazmaya baþla onun dýþýnda devam et
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
	
	int n = height(root);				// n tree'nin yüksekliði

	
	for(i = 0; i < n; i++){
		levelPrint(root, i);			// her levelý bastýrdýðým yer
		printf("\n");
	}
}
	
		
