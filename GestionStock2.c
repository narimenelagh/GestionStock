#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
// creation de la structure pour stock
typedef struct produits produits ;
struct produits {
   char nom[30];
   int prix;
   int quant;
   int numref; 
   char name[30];
   int nvstock;};
produits stock[1000];

// creation structure pour mouvement
typedef struct prod prod ;
struct prod {
   char name[30];
   int nvstock;};

prod mouv[10000];

int nbrligne(){
    FILE*f;
    int c;
    int lignes=0;
    f=fopen("fstock.txt","r");
    if(f!=NULL){
        while((c=fgetc(f))!=EOF){ 
            if(c =='\n') lignes++; }
    } else printf("echec de l'ouverture du fichier stock ");
    rewind(f); fclose(f);
    return lignes;}

//*****fonction de recherche
int rech(int r,int n){
     FILE*f;
    int j,b=n;
    f=fopen("fstock.txt","r+");
if(f!=NULL){ for(j=0;j<n;j++){
   fscanf(f,"%d %s %d %d",&stock[j].numref,stock[j].nom,&stock[j].prix,&stock[j].quant);
         if(r==(stock[j].numref)){
    printf("_num ref :%d \n nom : %s \n prix: %d \n stock: %d \n",stock[j].numref,stock[j].nom,stock[j].prix,stock[j].quant); b=0;}  }
    rewind(f); fclose(f);}
 else {printf("echec de l'ouverture");}
    return b; }

//******recherche nom
int rechnom(char nom[30],int n){
     FILE*f;
    int j,b=n;
    f=fopen("fstock.txt","r+");
if(f!=NULL){ for(j=0;j<n;j++){
   fscanf(f,"%d %s %d %d",&stock[j].numref,stock[j].nom,&stock[j].prix,&stock[j].quant);
         if( strcmp (nom,(stock[j].nom)) == 0){
            printf("_num ref :%d \n nom : %s \n prix: %d \n stock: %d \n",stock[j].numref,stock[j].nom,stock[j].prix,stock[j].quant); b=0;}
         }
    rewind(f); fclose(f);}
 else {printf("echec de l'ouverture");}
    return b; }

// *****fonction d'affichage
void affich(int nb){
    FILE *f;
    int j;
    f=fopen("fstock.txt","r");
    if(f!=NULL){
for(j=0;j<nb;j++){
   fscanf(f,"%d %s %d %d\n",&stock[j].numref,stock[j].nom,&stock[j].prix,&stock[j].quant);
    printf("\n numero de reference : %d \n nom : %s \n prix: %d DA \n stock: %d \n \n ",stock[j].numref,stock[j].nom,stock[j].prix,stock[j].quant);
    }} else {printf("echec de l'ouverture");}
    rewind(f);
    fclose(f);}

//******fonction d'ajout 
int ajout_article(int n){
    FILE *f;
    char nom[30];
    int num;
    f=fopen("fstock.txt","a");
    if(f!=NULL){
    // dans le  cas ou le numref de l'article existe deja 
    do{ printf("\n veuillez donner le numero de reference de l'article a ajouter : \n");
         scanf ("%d",&num);}while (rech(num,n)==0 );
    stock[n].numref=num;

    do{ printf("\n veuillez donner le nom de l'article a ajouter : \n");
         scanf (" %s",nom);}while (rechnom(nom,n)==0);
    strcpy(stock[n].nom,nom);
    printf("veuillez donner  la quantité de cet article ajouter : \n");
    scanf(" %d",&stock[n].quant);
    printf("veuillez donner le prix de cet article: \n");
    scanf(" %d",&stock[n].prix);
     fprintf(f, "%d %s %d %d\n",stock[n].numref,stock[n].nom,stock[n].prix,stock[n].quant);  
     rewind(f);
    }
else  {printf("echec de l'ouverture ");}
     fclose(f); return n+1;}

// fonction de suppression 
int suppr(char sup[30],int nb){
FILE *f;
FILE*tmp;
    int j,i,pos;
    f=fopen("fstock.txt","r");
    tmp=fopen("stockcopie.txt","w");
    if(f!=NULL && tmp!=NULL){
for(j=0;j<nb;j++){
   fscanf(f,"%d %s %d %d\n",&stock[j].numref,stock[j].nom,&stock[j].prix,&stock[j].quant);
    if( strcmp(sup,stock[j].nom)==0) pos=j;}
    for(j=0;j<pos;j++){
        fscanf(f,"%d %s %d %d\n",&stock[j].numref,stock[j].nom,&stock[j].prix,&stock[j].quant);
    fprintf(tmp,"%d %s %d %d\n",stock[j].numref,stock[j].nom,stock[j].prix,stock[j].quant);}
    for(j=pos;j<nb-1;j++){
        strcpy(stock[j].nom,stock[j+1].nom);
        stock[j].numref=stock[j+1].numref;
        stock[j].prix=stock[j+1].prix;
        stock[j].quant=stock[j+1].quant;
        
    fprintf(tmp,"%d %s %d %d\n",stock[j].numref,stock[j].nom,stock[j].prix,stock[j].quant);
    }} else {printf("echec de l'ouverture");}
    rewind(f); fclose(f);
    f=fopen("fstock.txt","w");
    if(f!=NULL && tmp!=NULL){
    for(i=0;i<nb-1;i++){
    fscanf(tmp,"%d %s %d %d\n",&stock[i].numref,stock[i].nom,&stock[i].prix,&stock[i].quant);
    fprintf(f,"%d %s %d %d",stock[i].numref,stock[i].nom,stock[i].prix,stock[i].quant);
       fprintf(f,"\n");}}  else {printf("echec de l'ouverture");}
    printf("\n suppression effectue avec succes \n");
    rewind(f);
    fclose(f);
    rewind(tmp);
    fclose(tmp);}

//fonction de modification 
int modif(char mod[30],int nb){
    int i,pos,ch;
    char nvnom[30];
    char rep;
    int nvref,nvprix,nvquant;
    FILE*tmp;
     FILE *f;
    int j;
    f=fopen("fstock.txt","r+");

    if(f!=NULL){
for(j=0;j<nb;j++){
   fscanf(f,"%d %s %d %d\n",&stock[j].numref,stock[j].nom,&stock[j].prix,&stock[j].quant);
if( strcmp(mod,stock[j].nom)== 0){ pos=j; }}fclose(f);

   printf("\n quel attribut de cet article souhaitez vous modifier ?\n");
   printf(" 1) le nom \n 2)le numero de reference \n 3) le prix \n 4) la quantité du stock restant \n 5)rien a modifier \n");
   scanf("%d",&ch);

    switch(ch){
        case 1: printf("!!Attention deux article ne peuvent pas posseder le meme nom!!\n");
                do{printf("veuillez donner le nouveau nom de cet article : ");
                scanf("%s",nvnom);
              }while(rechnom(nvnom,nb)==0 );
              if(rechnom(nvnom,nb)!=0 )strcpy(stock[pos].nom,nvnom); 
                break;

        case 2 : printf("!!Attention deux article ne peuvent pas posseder le meme numero de reference!\n");
            do{printf("veuillez donner le nouveau numero de reference de cet article : ");
                scanf("%d",&nvref);
              }while(rech(nvref,nb)==0 );
              if(rech(nvref,nb)!=0) stock[pos].numref=nvref;
                break;

        case 3 : printf("\n veuillez donner le nouveau prix de cet article: ");
                scanf("%d",&nvprix);
                stock[pos].prix=nvprix;
                break;

        case 4 : printf("\n veuillez donner la quantité de stock restantes: ");
                scanf("%d",&nvquant);
                stock[pos].quant=nvquant;
                break;
        case 5 : return 2;  break;}

tmp=fopen("stockcopie.txt","w+");
if(tmp!=NULL){
for(i=0;i<nb;i++){
     fscanf(f,"%d  %s %d %d \n",&stock[i].numref,stock[i].nom,&stock[i].prix,&stock[i].quant);
     fprintf(tmp,"%d %s %d %d",stock[i].numref,stock[i].nom,stock[i].prix,stock[i].quant);
       fprintf(tmp,"\n");
}}else {printf("echec de l'ouverture");}
rewind(tmp); fclose(tmp);}

 else {printf("echec de l'ouverture");}
    rewind(f);
    fclose(f);
    
    tmp=fopen("stockcopie.txt","r");
    f=fopen("fstock.txt","w");
    if(tmp!=NULL && f!=NULL){ for(i=0;i<nb;i++){ 
         fscanf(tmp,"%d %s %d %d\n",&stock[i].numref,stock[i].nom,&stock[i].prix,&stock[i].quant);
     fprintf(f,"%d %s %d %d",stock[i].numref,stock[i].nom,stock[i].prix,stock[i].quant);
       fprintf(f,"\n");
    } }else {printf("echec de l'ouverture");}
    rewind(tmp); fclose(tmp);
    rewind(f); fclose(f);
     }

// creation du fichier stock et remplissage 
void creation_stock(int n){
    int i;
    FILE *f;
    f=fopen("fstock.txt","w");
    
if(f!=NULL){
    for(i=0;i<n;i++){
    printf(" veuillez donner le numero de reference de l'article n° %d : \n",i+1);
    scanf(" %d",&stock[i].numref);
   
    printf(" veuillez donner le nom de l'article n° %d  : \n",i+1);
    scanf("%s",stock[i].nom);
     
    printf(" veuillez donner  la quantité de cet article n° %d  : \n",i+1);
    scanf(" %d",&stock[i].quant);
     
   printf(" veuillez donner le prix de cet article n° %d  : \n",i+1);
   scanf(" %d",&stock[i].prix);
        
        fprintf(f,"%d %s %d %d ",stock[i].numref,stock[i].nom,stock[i].prix,stock[i].quant);
       fprintf(f,"\n");}
       rewind(f); }
else  {printf("echec de l'ouverture ");}
    fclose(f);}

// fichier mouvement + MAJ
int creation_mouv(int n,int nb){
 int i,nvstock;
 int rs=0;
 char name[30];
int temp,res,j;
    FILE*m;
    FILE*f;
    FILE*tmp; 
     f=fopen("fstock.txt","r+");
    tmp=fopen("stockcopie.txt","w");
    m=fopen("mouv.txt","w");
if(m!=NULL ){
    for(j=0;j<nb;j++){
    printf(" veuillez donner le nom de l'article n° %d  : \n",j+1);
    scanf("%s",name);
    // si l'article exite on ecrit le nom et la quantité ajouté
    if(rechnom(name,n)==0){ 
        strcpy((stock[j].name),name);
        printf(" veuillez donner la quantité de cet article a ajouté n ° %d  :  \n",j+1);
        scanf("%d",&stock[j].nvstock);
        fprintf(m,"%s %d",stock[j].name,stock[j].nvstock);
        fprintf(m,"\n");}
        //si l'article n'existe pas on le creer 
        else { printf("!!cet article n'existe pas\n veuillez l'ajouter au stock en remplissant toutes ses informations!!\n ");
        n=ajout_article(n);}
// remplissage de tmp 
if(f!=NULL && tmp!=NULL){
        for(i=0;i<n;i++){
    fscanf(f,"%d %s %d %d\n",&stock[i].numref,stock[i].nom,&stock[i].prix,&stock[i].quant);
    fscanf(m,"%s %d\n",stock[j].name,&stock[j].nvstock);
    if(strcmp((stock[j].name),(stock[i].nom))==0){ 
     temp=stock[i].quant;
    stock[i].quant=temp+stock[j].nvstock;}
     fprintf(tmp,"%d %s %d %d\n",stock[i].numref,stock[i].nom,stock[i].prix,stock[i].quant);
       }}else  {printf("echec de l'ouverture ");}}
       
}else("echec ouveture de fichier"); rewind(f); fclose(f); rewind(tmp); fclose(tmp); fclose(m);

// on recopie le contenue de tmp dans fstock
f=fopen("fstock.txt","w");
tmp=fopen("stockcopie.txt","r");

    if(f!=NULL && tmp!=NULL){
        for(i=0;i<n;i++){
         fscanf(tmp,"%d %s %d %d\n",&stock[i].numref,stock[i].nom,&stock[i].prix,&stock[i].quant);
         fprintf(f,"%d %s %d %d\n",stock[i].numref,stock[i].nom,stock[i].prix,stock[i].quant);}
                            }else printf("echec de l'ouverture de stockcopie ou de fstock");
rewind(f); fclose(f); rewind(tmp); fclose(tmp);
 affich(n);
 return n;}

int main()
{
    int choix,n,choix2;
    int r,cont,nb;
    char rnom[30];
    char supp[30];
    char nmod[30];
// creation du menu
n=nbrligne();
if(n==0 ) {printf("!!le fichier stock est vide !!\n");
            //creation des valeurs initiales 
            printf("combien d'article le stock initial possede t'il?:   ");
            scanf("%d",&n);
            creation_stock(n);
            }
printf("le nombre de lignes de fstock est : %d",n);
do{
//system("cls");
printf("\n                        ********MENU******** \n");
printf("voici les options :\n");
printf("  1)_creer le fichier de stock  \n  2)_ ajouter un article\n  3)_ afficher tout les articles \n  4)_ supprimer un article \n  5)_ Rechercher un article \n  6)_ Modifier les attributs d'un article  \n  7)_creation du fichier mouvement +une mise a jour des stocks \n  8)_ Quitter");

do{
printf("\n                         **** veuillez choisir *****\n");
printf("votre choix doit etre compris entre 1 et 8 \n ");
scanf("%d",&choix);}while(choix<1 || choix>8);
  
        switch(choix){
            case 1: printf("\n                         **** Creation d'un nouveau du fichier Stock*****\n");
            //creation des valeurs initiales 
            printf("combien d'article le stock initial possede t'il?  ");
            scanf("%d",&n);
            creation_stock(n);
            break;
            case 2:  printf("\n                         **** Ajout d'article*****\n");
            n=ajout_article(n);   //n++; 
            break;

            case 3: printf("\n                         **** Affichages de tout les articles *****\n");
            affich(n);break;

             case 4: printf("\n                         **** Suppression d'art1icle*****\n");
             printf("\n veuillez donner le nom de l'article a supprimer :  ");
             scanf("%s",supp);
             if (rechnom(supp,n)==n) {printf("cet article est introuvable\n");}
             else {suppr(supp,n); n--;} break;

             case 5: printf("\n                         **** Recherche d'article*****\n");
                do{ printf("\n si vous souhaitez rechercher un article : \n  1)par son numero de reference \n 2)par son nom \n  ");
                scanf("%d",&choix2);}while(choix2!=1 && choix2!=2);
                    switch(choix2){
                        case 1: printf("\n donner le numero de reference  de l'article a rechercher :  ");
                         scanf("%d",&r); //rech(r,n); 
                          if(rech(r,n)==n) {printf("cet article est introuvable \n");} break;

                        case 2: printf("\n donner le nom a rechercher:  ");
                        scanf("%s",rnom);
                        //rechnom(rnom,n)
                        if(rechnom(rnom,n)==n) {printf("cet article est introuvable\n");} break;} 
            break;
            
             case 6: printf("\n                        **** Modification d'un article*****\n"); 
              
                printf("veuillez donner le nom de l'article que vous souhaitez modifier :  ");
                scanf("%s",nmod);
                    if (rechnom(nmod,n)==n) {printf("cet article est introuvable\n");}
                     else {modif(nmod,n);} break;

             case 7: printf("\n                        **** MISE A JOUR DU STOCK*****\n"); 
                 
                 printf("Veuillez creer votre fichier mouvement : \n");
                do{ printf("combien d'article contient votre fichier mouvement?:  ");
                 scanf("%d",&nb);}while(nb<0 && n>10000);
                 n=creation_mouv(n,nb);
                 break;
             case 8: return 0;}
  do{           
printf("voulez vous revenir au Menu ? \n tapez '10' pour oui et '0' pour non  : ");
scanf("%d",&cont);}while(cont!=10 && cont!=0);}while(cont==10);

 
    return 0;
}
