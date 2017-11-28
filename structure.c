	#include "union.h"

	typedef struct mem_fichier
	{
		int nbr_champs;
		int nbr_ligne;

		char *(**tab);
	}mem_fichier;

		mem_fichier* allouer_memfichier(int nbr_champs,int nbr_ligne)
		{
			mem_fichier *mf = malloc(sizeof(mem_fichier));
			mf->nbr_champs = nbr_champs;
			mf->nbr_ligne = nbr_ligne;

			mf->tab = malloc(nbr_ligne*sizeof(*(mf->tab)));
			if(mf->tab == NULL){
				perror("allocation echoué");
				exit(0);
			}
			for(int i=0 ;i<nbr_ligne;i++){
				(mf->tab)[i] = malloc(nbr_champs * sizeof(*(mf->tab[i])));
				if((mf->tab)[i] == NULL){
					for(int j=0;j<nbr_ligne;j++){
						free((mf->tab)[i]);
						perror("allocation echoué");
						exit(0);
					}
				}
				for(int j=0;j<nbr_champs;j++){
					(mf->tab)[i][j] = malloc(sizeof(char));
				}
			}

			return mf;
	}
	void free_memfichier(mem_fichier *mf,int nbr_champs,int nbr_ligne){
		for(int i=0;i<nbr_ligne;i++){
			free((mf->tab)[i]);
		}
		free(mf->tab);
		free(mf);
	}
	void affiche_memfichier(mem_fichier *mf){
		for(int i=0;i<mf->nbr_ligne;i++){
			for(int j=0;j<mf->nbr_champs;j++){
				printf("%s ",(mf->tab)[i][j] );
			}
			printf("\n");
		}
	}
	mem_fichier* stockage_fichier(FILE* fichier){     ////. !!!!!!!!!!!!!!!!
		mem_fichier* m = allouer_memfichier(7,4);       //// METTRE DES VARIABLE NBR_CHAM NBR_LIGNE
		char buf[LIGNE_MAX];
		char* s;
		char* c= malloc(sizeof(char));
		int compteur = 0;
		while(fgets(buf,LIGNE_MAX,fichier)!=NULL){
			if(buf[0]=='#'){ continue;}
			if(strlen(buf) > 2){
				c = ";";
				break;
			}
			if(strlen(buf) <= 2){
				strcpy(c,buf);
				break;
			}
		}
		while(fgets(buf,LIGNE_MAX,fichier)!=NULL){
			if(buf[0]=='#'){ continue;}
			if(strlen(buf)<=2){ continue;}
			s = strtok(buf,c);               // mettre caracetre en variable // PAS AU POINTS  !
			int i = 0;
			while(s != NULL){
				strcpy((m->tab)[compteur][i],s);
				s = strtok(NULL,";");
				i++;
			}
			compteur++;
		}
		printf("LE Separateur est : %s \n",c );
		return m;
	}
	int main(int argc, char const *argv[])
	{
		FILE *f = ouverture_fichier("test.txt");
		mem_fichier *a = stockage_fichier(f);
		affiche_memfichier(a);

		return 0;
	}
