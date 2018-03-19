#include <iostream>
#include <time.h>
#include  <cmath>


 using namespace std;

 /****Funzione che genera numeri random compresi tra 0 ed 1, esclusi****/
 double GeneraRandom () {
    double random_number=((double)rand()/(RAND_MAX));
    return random_number;
  }

/****Funzione che controlla se il vettore(X,Y) sta sotto la curva FX****/
 bool ControllaValoreSottoFX( double X ,  double Y){
     return exp(X)>=Y*2.71;
  }

/**** (yMAX(b−a))*(N_HIT/N_EVENTI) ****/
 double CalcolaNepero(double AS){
   return AS * 2.71 + 1;
  }

/****Calcola il rapporto tra due valori*****/
 double CalcolaRapporto(double HIT, double N_EVENTI){
     return  (HIT / N_EVENTI);
 }

/****Calcola il valore NH / N_eventi****/
 double CalcolaAS(double N_EVENTI, double *N_hit){

   double trial=N_EVENTI;
   double x , y , AS , hit=0;
   double xa, ya, ASa, hita=0;
   while(trial>0){

     x=GeneraRandom();
     y=GeneraRandom();

     if( ControllaValoreSottoFX(x,y) ) {
        hit+=1;
     }
     trial--;
   }

   AS = CalcolaRapporto(hit, N_EVENTI);
   *N_hit=hit;

   return AS;
 }

/****Calcola l'intervallo di confidenza con alpha pari a 0,03[97%]****/
 void CalcolaIntervalloConfidenza(double teta, double N_eventi, double nepero, double *I1, double *I2){
   double sigma = sqrt( teta * ( 1.0 - teta ) / N_eventi );
   *I1 = nepero-3*sigma;
   *I2 = nepero+3*sigma;
 }

/****Calcola la varianza, un indice di variabilità****/
 double calcolavarianza(double AS, double N, double *somma){
   *somma += AS;
   double teta = *somma / N;
   double teta2 = pow(*somma,2) / N;

   return teta2 - pow(teta,2);
 }

 /****Calcola La Deviazione standard tramite varianza****/
  double CalcolaDevSTD(double varianza){
    return sqrt(varianza);
  }                                                                                                                                                                                                                                                                                                                                                   double CalcolaVarianza(double AS, double N_hit, double somma);

/****Calcola la varianza antitetica, un indice di variabilità ottimizzato****/
 double calcolavarianzaantitetica(double N_EVENTI){
   double trial=N_EVENTI;
   double x , y , AS , hit=0;
   double xa, ya, ASa, hita=0;
   while(trial>0){

     x=GeneraRandom();
     y=GeneraRandom();
     xa=1-x;
     ya=1-y;
     if( ControllaValoreSottoFX(x,y) ) {
        hit+=1;
     }
     if( ControllaValoreSottoFX(xa,ya) ) {
        hita+=1;
     }

     trial--;
   }

   AS = CalcolaRapporto(hit, N_EVENTI);
   ASa= CalcolaRapporto(hita, N_EVENTI);


   double tetaAntitetica = ( AS + ASa ) / 2;
   double tetaAntiteticaQuadro = pow(tetaAntitetica, 2);

   return tetaAntiteticaQuadro - pow(tetaAntitetica,2);
 }                                                                                                                                                                                                                                                                                                                                                     double CalcolaVarianzaAntitetica(double AS, double eventi, double nep);

/****Calcola La Deviazione standard con varianza Antitetica****/
 double CalcolaDevSTDAntitetica(double varianzaAntitetica){
   return sqrt(varianzaAntitetica);
 }







 int main() {
   /****Impostazioni****/
   cout.precision(10);
   srand(time(NULL));

   /****Data****/
   double nepero, eventi;
   double AS, N_hit=0, varianza=0, devstd=0,devstdAntitetica=0, varianzaAntitetica=0, e = 2.718281828;
   double I1=0, I2=0;
   double somma;

   /****LoopProgramma****/
   while(true){

     /****Reset Dati****/
       nepero=0;
       eventi=0;

       /****Interfaccia****/
       cout << "Calcola il numero di NEPERO 'e' mediante il metodo Monte Carlo HIT-or-MISS"<<endl;
       cout << "Inserisci il numero di eventi con cui calcolare il valore di NEPERO [100, 10000000]"<<endl<<"> ";
       cin  >>  eventi;
       cout <<  endl ;

       /****Calcola****/
       AS     = CalcolaAS(eventi, &N_hit);
       nepero = CalcolaNepero(AS);
       CalcolaIntervalloConfidenza(AS, eventi, nepero, &I1, &I2);                                                                                                                                                                                                                                                      somma=nepero;
       varianza = CalcolaVarianza(AS, N_hit, somma);
       devstd = CalcolaDevSTD(varianza);
       varianzaAntitetica = CalcolaVarianzaAntitetica(AS, eventi, somma);
       devstdAntitetica = CalcolaDevSTDAntitetica(varianzaAntitetica);


       /****MostraRisultati****/
       cout <<"/****RISULTATI****/"<<endl;
       cout << "Il valore di NEPERO stimato e': " << nepero <<endl;
       cout << "Differenzia da 'e' di :" << nepero-e<<endl;
       cout << "L'intervallo di confidenza con livello di fiducia 0,03(99,7perc) e' : " << endl <<"[ " <<  I1 << " , " << I2 << " ]"<<endl;
       cout << "La varianza stimata e': " << varianza << endl;
       cout << "La Deviazione Standard stimata e': " << devstd << endl;
       cout << "La varianza ridotta mediante Variabile Antitetica e': " << varianzaAntitetica << endl;
       cout << "La Deviazione Standard Ridotta stimata e': " << devstdAntitetica << endl;
       cout <<"/****RISULTATI****/"<<endl;
       cout << endl << endl;

   }

 return 0;
 }



                                                                                                                                                                                                                                                                                                                   double CalcolaVarianza(double AS, double N_hit, double somma){
                                                                                                                                                                                                                                                                                                                     return somma*(3-somma);
                                                                                                                                                                                                                                                                                                                   }

                                                                                                                                                                                                                                                                                                                   double CalcolaVarianzaAntitetica(double AS, double eventi, double nep){
                                                                                                                                                                                                                                                                                                                      return (7*nep - 2*(nep*nep) - 4) / 2;
                                                                                                                                                                                                                                                                                                                   }
