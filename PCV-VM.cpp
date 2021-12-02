#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>

using namespace std;

#define infinito 0x7FFFFFFF

struct Cidade{
    int x;
    int y;
};

class VizinhoMinimo{
    private:
        FILE *arqEntrada;
		FILE *arqSaida;
		int n;
		float custo=0;
		Cidade *cidades;
        int *vizitados;
        bool visitado(int *vis,int tam,int a){//Facilita a verificacao do vertice atual e seu status
            int i;
            for(i=0;i<tam;i++){
                if(a==vis[i]){
                    return true;
                }
            }
            return false;
        }

    public:
        VizinhoMinimo () {
			char nome [256];
			cout << "Informar nome arquivo entrada : ";
			cin >> nome;
			arqEntrada = fopen (nome, "r");//Abre o arquivo com o nome digitado
            arqSaida = fopen ("PCV-VM-Resultado.txt", "w");//Cria o arquivo resposta
			fscanf (arqEntrada, "%d\n", &n);//Pega o numero de cidades no arquivo aberto
			cidades = new Cidade [n];
            vizitados = new int [n];
			cidades[0].x = 0;
			cidades[0].y = 0;
			for (int x = 0; x < n; x++) {
				fscanf (arqEntrada, "%d %d\n", &cidades[x].x, &cidades[x].y);//Scanea as coordenadas
                vizitados[x]=-2;//Marca como nao visitados
			}
			fclose(arqEntrada);//Fecha o arquivo de entrada
		}    

        ~VizinhoMinimo(){ }

        void Algoritmo(){
            int i,v=0,vizinho;
            float distanciaMin,dis;
            bool inacabado=true;
            Cidade a;
            time_t inicio, fim;
            a.x=cidades[0].x;
            a.y=cidades[0].y;
            vizitados[v]=0;
            inicio = clock();
            while(inacabado){
                distanciaMin=infinito;//Comeca com um valor absurdo para certificar-se que a distancia minima foi realmente tirada do algoritmo e nao memoria lixo
                for(i=0;i<n;i++){//Percorre todos os vertices
                    if(!visitado(vizitados,v+1,i)){//Se o vertice atual nao foi visitado calcula a distancia dele pro vertice anterior
                        dis=sqrt(pow((cidades[i].y-a.y),2)+pow((cidades[i].x-a.x),2));
                        if(distanciaMin>dis){//Se a distancia for menor, atualiza a menor distancia e atualiza o vizinho do vertice anterior
                            distanciaMin=dis;
                            vizinho=i;
                        }
                    }
                }
                if(v<n-1){
                    vizitados[++v]=vizinho;//Bota o vizinho como visitado e bota ele como anterior para repetir o processo
                    a.x=cidades[vizinho].x;
                    a.y=cidades[vizinho].y;
                    custo+=distanciaMin;//Atualiza o custo total
                }else{
                    custo+=sqrt(pow(cidades[vizitados[v]].y-cidades[0].y,2)+pow(cidades[vizitados[v]].x-cidades[0].x,2));//Calcula a distancia do inicio pro ultimo vertice para adicionar no custo
                    inacabado=false;
                }
            }
            fim = clock();
            //Digita no arquivo de saida
            fprintf(arqSaida, "NUMERO CIDADES :");
            fprintf(arqSaida, "%d",n);
            fprintf(arqSaida, "\nCAMINHO\n",n);
			for(i=0;i<n;i++){
                fprintf(arqSaida, "%d ", vizitados[i]);
            }
			fprintf(arqSaida, "\nCUSTO : %0.2f", custo);
            fprintf(arqSaida,"\nTEMPO : %0.2f",  (( double(fim) - double(inicio) )/CLOCKS_PER_SEC));
			fclose(arqSaida);
            return;
        }

};

int main(int argc, char **argv){
	VizinhoMinimo  *novo = new VizinhoMinimo ();
	novo->Algoritmo();
	delete (novo);
	return(0);
}