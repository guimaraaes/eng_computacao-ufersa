#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <string.h>

int c, n, quantALETAS;
float RfR, RiR, RfC, RiC, zfA, ziA, z0A, zfR, ziR, zfC, ziC, yfA, yiA, xfA, xiA, massaCM, zmassaCM, CM;
int resultCM, paramI = 0;
char T;

//ALETA
float aleta_m (float zfA, float ziA, float z0A, float yfA, float yiA, float xfA, float xiA){
	float massa;
	massa = (xfA-xiA) * ((zfA-z0A) * (yfA-yiA) + (pow(yfA,2)-pow(yiA,2))*0.5*(zfA-ziA)/(yfA-yiA));
	return massa;
}

float aleta_M(float zfA, float ziA, float z0A, float yfA, float yiA, float xfA, float xiA){
	float MOMENTmassa;
	MOMENTmassa = (xfA-xiA) * 0.5*((pow(zfA,2)-pow(z0A,2))*(yfA-yiA) + ((pow(yfA,2)-pow(yiA,2))*zfA + 0.33333333*(pow(yfA,3)-pow(yiA,3))*(zfA-ziA)/(yfA-yiA))*(zfA-ziA)/(yfA-yiA));
	return MOMENTmassa;
}

//COIFA
float coifa_m(float zfC, float ziC, float RfC, float RiC){
	float massa;
	massa = 2*((zfC - ziC)*(pow(RfC,2) - pow(RiC,2))*0.5 - 0.3333333*(pow(RfC,3) - pow(RiC,3)));

	return massa;
}

float coifa_M(float zfC, float ziC, float RfC, float RiC){
	float MOMENTmassa;
	MOMENTmassa = ((pow(zfC,2)-pow(ziC,2))*(pow(RfC,2)-pow(RiC,2))*0.5 - 0.666666666*zfC*(pow(RfC,3)-pow(RiC,3)) + 0.2*(pow(RfC,4)-pow(RiC,4)));
	return MOMENTmassa;
}

//RESERVATÓRIO
float reserv_m(float zfR, float ziR, float RfR, float RiR){
	float massa;
	massa = (zfR - ziR)*(pow(RfR,2) - pow(RiR,2));
	return massa;
}

float reserv_M(float zfR, float ziR, float RfR, float RiR){
	float MOMENTmassa;
	MOMENTmassa = 0.5*(pow(zfR,2)-pow(ziR,2)) * (pow(RfR,2)-pow(RiR,2));
	return MOMENTmassa;
}

void bubble_sort (int quantALETAS, float massa[], char id[], int escolha1, float CM, float cm[]) {
    int k, j;
    float aux, aux3;
	char aux2;
    
	for (k = 1; k < quantALETAS+2; k++) {
        for (j = 0; j < quantALETAS+2 - 1; j++) {
            if (massa[j] < massa[j + 1]) {
                aux          = massa[j];
                massa[j]     = massa[j + 1];
				massa[j + 1] = aux;
				aux2 = id[j];
				id[j] = id[j+1];
                id[j+1] = aux2;
                aux3 = cm[j];
				cm[j] = cm[j+1];
                cm[j+1] = aux3;
            }
        }
    }
    if(escolha1 == 1){
        for (j = 0; j < quantALETAS+2 ; j++) {
        	if(cm [j] > CM){
        		printf("\n m = %f T= %c cm = %f ", massa[j], id[j], cm[j]);
			}
    	}
	} else if (escolha1 == 2){
		for (j = 0; j < quantALETAS+2 ; j++) {
			if(cm [j] < CM){
        		printf("\n m = %f T= %c cm = %f ", massa[j], id[j], cm[j]);
			}
    
    	}
	}
}
	
void paramAletas(){
	printf("___ALETA \n");
	printf("PARÂMTROS DAS ALETAS: \n");
	printf("zfA = "); scanf("%f", &zfA);
	printf("ziA = "); scanf("%f", &ziA);
	printf("z0A = "); scanf("%f", &z0A);
	printf("yfA = "); scanf("%f", &yfA);
	printf("yiA = "); scanf("%f", &yiA);
	printf("xfA = "); scanf("%f", &xfA);
	printf("xiA = "); scanf("%f", &xiA);
}

void paramCoifa(){
	printf("___COIFA \n");
	printf("PARÂMTROS DA COIFA: \n");
	printf("zfC = "); scanf("%f", &zfC);
	printf("ziC = "); scanf("%f", &ziC);
	printf("RfC = "); scanf("%f", &RfC);
	printf("RiC = "); scanf("%f", &RiC);
}

void paramReserv(){
	printf("___RESERVATÓRIO \n");
	printf("PARÂMTROS DO RESERVATÓRIO: \n");
	printf("zfR = "); scanf("%f", &zfR);
	printf("ziR = "); scanf("%f", &ziR);
	printf("RfR = "); scanf("%f", &RfR);
	printf("RiR = "); scanf("%f", &RiR);
}

void ImprimirParam(){
	printf("___ALETA \n");
	printf("PARÂMTROS FINAIS DAS ALETAS: \n");
	printf("zfA = %f \n", zfA);
	printf("ziA = %f \n", ziA); 
	printf("z0A = %f \n", z0A); 
	printf("yfA = %f \n", yfA); 
	printf("yiA = %f \n", yiA); 
	printf("xfA = %f \n", xfA); 
	printf("xiA = %f \n\n", xiA);
	 
	printf("___COIFA \n");
	printf("PARÂMTROS FINAIS DA COIFA: \n");
	printf("zfC = %f \n", zfC);
	printf("ziC = %f \n", ziC); 
	printf("RfC = %f \n", RfC); 
	printf("RiC = %f \n\n", RiC);
	 
	printf("___RESERVATÓRIO \n");
	printf("PARÂMTROS FINAIS DO RESERVATÓRIO: \n");
	printf("zfR = %f \n", zfR); 
	printf("ziR = %f \n", ziR); 
	printf("RfR = %f \n", RfR); 
	printf("RiR = %f \n", RiR); 
}

main(){
    setlocale(LC_ALL, "Portuguese");

	printf("CADASTRO::: \n");
	while (resultCM == 0){
		printf("quantidade de aletas = "); scanf("%d", &quantALETAS);
		printf("\n");
		float massa[quantALETAS+2], MOMENTmassa[quantALETAS+2], cm [quantALETAS+2], tipoC [quantALETAS+2];
		char id[quantALETAS + 2];
	 
		if (paramI == 0)
		paramAletas();
		zfA = 20; ziA = 11; z0A = 0; yfA = 17; xfA = 3; xiA, yiA =0;
		n=0;
		while (n < quantALETAS){
		massa[n] = aleta_m(zfA, ziA, z0A, yfA, yiA, xfA, xiA);
		MOMENTmassa[n] = aleta_M(zfA, ziA, z0A, yfA, yiA, xfA, xiA);
		id[n] = 'A';
		n=n+1;
		}
	
		if (paramI == 0)
		paramCoifa();
		zfC = 106; ziC = 65; RfC=12; RiC =0;
		massa[quantALETAS] = coifa_m(zfC, ziC, RfC, RiC);
		MOMENTmassa[quantALETAS] = coifa_M(zfC, ziC, RfC, RiC);
		id[quantALETAS] = 'C';
	
		if (paramI == 0)
		paramReserv();
		zfR = 65; ziR = 0; RfR=12; RiR =0;
		massa[quantALETAS + 1] = reserv_m(zfR, ziR, RfR, RiR);
		MOMENTmassa[quantALETAS + 1] = reserv_M(zfR, ziR, RfR, RiR);
		id[quantALETAS + 1] = 'R';
	
	    for(n = 0; n< (quantALETAS+2); n++){
			cm [n] = (MOMENTmassa[n]) / (massa[n]); 
			printf("CM%d = %f \n\n\n", n+1 , cm[n]);
	    }
	
		//CÁLCULO COM AS MASSAS PONTUAIS
		
		for(int i = 0; i < quantALETAS+2; i ++){
			massaCM = massaCM+ massa [i];
			zmassaCM = zmassaCM+ massa [i]*cm[i];
		}
		CM = zmassaCM / massaCM;
		printf("CM = %f \n\n\n", CM);
	
		//ANÁLISE DO VALOR DO CM 
		printf("ANÁLISE DO CENTRO DE MASSA::: \n");
		if (zfC*0.5 - zfC*0.1 > CM){
			resultCM = 0;
			printf("O centro de massa está abaixo do ideal\n");
			printf("DICA: retire massa das formas abaixo do CM ideal\n\n");
		} 
		else if (zfC*0.5 + zfC*0.1 < CM){
			resultCM = 0;
			printf("O centro de massa está acima do ideal\n");
			printf("DICA: retire massa das formas acima do CM ideal\n\n");
		} 
		else if ((zfC*0.5 - zfC*0.1 <= CM) && (zfC*0.5 + zfC*0.1 >= CM)){
			printf("O centro de massa é o ideal \n\n ");
			ImprimirParam();
			resultCM = 1;
		}
		
		printf("CONSULTA::: \n");
		printf("ORDENAÇÃO DAS MASSAS ACIMA DO CM\n");
		bubble_sort (quantALETAS, massa, id, 1, CM, cm);
	    printf("\n\n");
	
		printf("ORDENAÇÃO DAS MASSAS ABAIXO DO CM\n");
		bubble_sort (quantALETAS, massa, id, 2, CM, cm);
	    printf("\n\n");
	
		if(resultCM == 0){
			printf("MODIFICAÇÃO::: \n");
			
			while (T != 'N'){
				printf("T da forma para modificar (A aleta, C coifa, R reservatório, N nenhuma) = \n");
				scanf("%c", &T);
				if(T == 'C'){
					paramCoifa();
				} else if (T == 'R'){
					paramReserv();
				}else if(T == 'A'){
					paramAletas();
				}
			}
			paramI = 1;
			T = 'x';
			massaCM = 0;
			zmassaCM = 0;
			printf("EXCLUSÃO OU ADIÇÃO::: \n");
		}		
	}
	//trabalhar com arquivo
	//melhorar o fator de influência no CM
}
