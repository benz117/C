#include "union.h"
#include "formater.h"
int nb_champs(char* fichier)
{

  formater(fichier);

  FILE *f = ouverture_fichier(fichier);
  int compteur = 0;
  char buf[LIGNE_MAX];
  while(fgets(buf,LIGNE_MAX,f)!=NULL){
    if(buf[0]=='#'){
      continue;
    }

    if(strlen(buf)<=2){
      continue;}
    for(int i =0;i<strlen(buf);i++){
      if(buf[i]==';'){                   // pour l'utiliser ici
        compteur++;
      }
      if(buf[i]=='\n'){
        return compteur+1;
      }
    }
  }
  rewind(f);
  fclose(f);
  return compteur+1;
}

FILE* ouverture_fichier(char* nom_fichier)
{
  FILE* fichier;
  if ( (fichier = fopen(nom_fichier, "r")) == NULL)
    {
      perror("erreur ouverture_fichier ");
      exit (1);
    }
    else
      return fichier;
}
int comparer_nb_champs(int nb_param,char* fichier,...){
  if(nb_param <2){
    printf("nbr fichier insufisant ... \n");
    return 0;
  }
  int compteur = 1;
  int n = nb_champs(fichier);
  va_list ap;
  va_start(ap,fichier);
  char* tmp;
  while(compteur <= nb_param){
    tmp = va_arg(ap,char*);
    printf("ouverture fichier %s\n",tmp );
    if(nb_champs(tmp) != n){
      printf("nbr champs differents \n" );
      va_end(ap);
      return 0;
    }
    compteur++;
  }
  va_end(ap);
  printf("nbr champs kifkif \n" );
  return 1;
}
void copy_fic(FILE *fsrc, FILE *fdst){
  char buf[LIGNE_MAX];
  char *s;
  while((s = fgets(buf,LIGNE_MAX,fsrc) ) != NULL ){
    if(fputs(buf,fdst) == EOF){
      perror ("fputs");
    }
  }
}
/*
myunion(int nbr_fichier,char *fichier,...)
fait l'union entre le nbr_fichier données
          .... //
*/
void myunion(int nbr_fichier,char *fichier,...){
  int compteur = 1;
  FILE *fout = fopen("resultat.csm","a");
  va_list ap;
  va_start(ap,fichier);

  char* tmp;
  FILE* ftmp;
  ftmp = ouverture_fichier(fichier);
  copy_fic(ftmp,fout);
  fclose(ftmp);

  while(compteur <nbr_fichier){
    tmp = va_arg(ap,char*);
    printf("ouverture : %s\n",tmp );
    ftmp = ouverture_fichier(tmp);
    copy_fic(ftmp,fout);
    compteur++;
    fclose(ftmp);
  }
  fclose(fout);
  va_end(ap);
}
