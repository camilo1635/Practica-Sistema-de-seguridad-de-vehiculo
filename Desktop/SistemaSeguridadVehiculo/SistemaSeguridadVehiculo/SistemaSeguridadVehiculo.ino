#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);

unsigned long tiempo1 = 0;
unsigned long tiempo2 = 0;
unsigned long dif_tiempo1 = 0;
unsigned long tiempo3 = 0;
unsigned long tiempo4 = 0;
unsigned long dif_tiempo2 = 0;
unsigned long max1 = 5;
unsigned long max2 = 15;
unsigned long max3 = 4;
int band1=0;
int band2=0;

int ACTIVACION = 2; //Revisado
int DESACTIVACION = 3;//Revisado
int estado = 0;//Revisado
int puerta = 13;//Revisado
int ledrojo = 14; //Revisado
int ledazul = 15;
int Salida[] = {12, 11, 10, 19, 18, 17, 16};//Pines de 7seg en Arduino UNO   //Revisado

int Secuencia1 [][7] ={{1,1,1,1,1,1,0},
                       {0,1,1,0,0,0,0},
                       {1,1,0,1,1,0,1},
                       {1,1,1,1,0,0,1},
                       {0,1,1,0,0,1,1},
                       {1,0,1,1,0,1,1},
                       {1,0,1,1,1,1,1},                                              
                       {1,1,1,0,0,0,0},
                       {1,1,1,1,1,1,1},
                       {1,1,1,1,0,1,1},                                                                     
                       };

          


int i=9;  //Revisado
int j=0; //Revisado
int valP; //Variable para ingresar valor de puerta
int valD;//guarda valor de botton de Desactivar
int valA;//guarda valor de boton de Activar



int k=0;
int l=0;

void funcion1() {
         estado = 0;//INACTIVO
         i=9; //Hace el conteo desde 9
         j=0; //Revisado         
}

void funcion2() {
         k=0;
         estado = 1;//ACTIVO 
         l=0;
}
void funcion3() {
         estado = 2;//ALARMADISPARADA
}

void setup() {
    Serial.begin(9600);
    lcd.begin(16,2);
    
    
    pinMode(ACTIVACION,INPUT);  //Revisado
    pinMode(DESACTIVACION,INPUT);//Revisado
    pinMode(puerta,INPUT);//Revisado
    
    pinMode(ledazul,OUTPUT);
    pinMode(ledrojo,OUTPUT);//Revisado
    
    pinMode(Salida[0],OUTPUT);
    pinMode(Salida[1],OUTPUT);
    pinMode(Salida[2],OUTPUT);
    pinMode(Salida[3],OUTPUT);
    pinMode(Salida[4],OUTPUT);  //Revisado
    pinMode(Salida[5],OUTPUT);
    pinMode(Salida[6],OUTPUT);
    pinMode(Salida[7],OUTPUT);    
    attachInterrupt(digitalPinToInterrupt(2), funcion2, LOW); //Revisado
    attachInterrupt(digitalPinToInterrupt(3), funcion1, LOW); //Revisado   
  }

void loop()  {
  estadoPuerta();
  operacion1();
  permanenteLedAzul(); 
  intentodeactivar();
//-------------------------------------------
} 
void estadoPuerta(){
  lcd.setCursor(0, 1);
  valP = digitalRead(puerta);//Lee Puertas y envia a valp

  if(valP == LOW){//Si puertas estan cerradas 
    lcd.print("CERRADA");
    estadoSistema();
  }
  if(valP == HIGH){
    lcd.print("ABIERTA"); 
    estadoSistema();
  }
  
}
void estadoSistema(){
  lcd.setCursor(0, 0);
   if(estado == 0)
   {
     lcd.print("INACTIVO"); 
     conteoDescendente7Seg(); 
     digitalWrite(ledazul, LOW);        
   }        
   if(estado == 1)
   {
     lcd.print("ACTIVO");          
   } 
   if(estado == 2)
   {
     lcd.print("ALARMA DISPARADA");          
   }
}

void operacion1(){
  if(estado == 0 && valP == HIGH){
      tiempo3 = millis();
      while (band2 ==0)
    {
      titilaLedRojo();
      intentodeactivar();
      tiempo4 = millis();
      dif_tiempo2= tiempo4-tiempo3;
      dif_tiempo2= dif_tiempo2/1000;
      if (dif_tiempo2 > max2)
         band2=1;    
    }    
    
    lcd.setCursor(8, 1);
    lcd.print("ActiveSistema");  //cerrar puertas elimina mensaje
  }
    titilaLedRojo();
    
    
  }
}
void titilaLedRojo(){
    digitalWrite(ledrojo, HIGH);
    delay(500);
    digitalWrite(ledrojo, LOW);
    delay(500);
}
 
void permanenteLedAzul(){
  if(estado == 1 && valP == HIGH){
    digitalWrite(ledazul, HIGH);
    lcd.clear();
    estado = 2;

  }
}

void intentodeactivar(){
  if(estado == 1 && valP == HIGH){
    titilaLedRojo();
    tiempo1 = millis();
    lcd.setCursor(8, 1);
    lcd.print("NO SE ACTIVA"); 
        while (band1 ==0)
        {
      titilaLedRojo();
      tiempo2 = millis();
      dif_tiempo1= tiempo2-tiempo1;
      dif_tiempo1= dif_tiempo1/1000;
      if (dif_tiempo1 == max3)
         band1=1;    
        } 
        lcd.setCursor(8, 1);
        lcd.print("            ");
        estado = 0;
  }
}
void conteoDescendente7Seg(){  
      if (Secuencia1[i][j] == 1)
         digitalWrite(Salida[j],HIGH);
      else  
         digitalWrite(Salida[j],LOW);
      
      j++;
      if (j==10)
       { 
        i--;
        j=0;
        delay(500);
       }
      if (i==0){
        activacionAutomatica();
        tiempo1 = millis();
        lcd.setCursor(9, 1);
        lcd.print("ActivoAutom");
        lcd.setCursor(0, 0);
        lcd.print("ACTIVO  "); 
        while (band1 ==0)
        {
      tiempo2 = millis();
      dif_tiempo1= tiempo2-tiempo1;
      dif_tiempo1= dif_tiempo1/1000;
      if (dif_tiempo1 == max1)
         band1=1;    
        }  
        lcd.clear();   
      }
    
  }
  void activacionAutomatica(){
    if(estado == 0 && valP == LOW){
      estado = 1;
  }  
        
}

    
