int a = 11;
int b = 12;
int c = 16;
int d = 15;
int e = 14;
int f = 10;
int g = 9;

int decimal = 17;
void setup() {
  // Configuración de pines
  pinMode(2, INPUT); // A
  pinMode(3, INPUT); // B
  pinMode(4, INPUT); // C
  pinMode(5, INPUT); // D

  pinMode(6, INPUT); // Bus de control A
  pinMode(7, INPUT); // Bus de control B
  pinMode(8, INPUT); // Bus de control C

  pinMode(a, OUTPUT); 
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT); 
  pinMode(d, OUTPUT); 
  pinMode(e, OUTPUT); 
  pinMode(f, OUTPUT); 
  pinMode(g, OUTPUT);
  
  pinMode(13, OUTPUT); // Agregar pin 13 como salida

  Serial.begin(9600); // Inicializa la comunicación serie para depuración
}

void loop() {
  // Lectura de las entradas
  int A = digitalRead(2);
  int B = digitalRead(3);
  int C = digitalRead(4);
  int D = digitalRead(5);

  int x_0 = 0;
  int x_1 = 0;
  int x_2 = 0;
  int x_3 = 0;
  
  // Lectura del bus de control
  int E = digitalRead(6);  
  int F = digitalRead(7);  
  int G = digitalRead(8); 

  // Control bus
  int suma = E && !F && !G; // 100
  int resta = !E && F && !G; // 010
  int multi = E && F && !G; // 110
  int division = !E && !F && G; // 001
  int AND=E && !F && G;
  int OR=!E && F && G;
  int XOR=E && F && G;
  if(suma){//Suma

    if ((A ^ B) && suma) {
      digitalWrite(11, HIGH); // phi
      x_0 = 1;
    } else {
      digitalWrite(11, LOW);
      x_0 = 0;   
    }

    if ((A && B) ^ (C ^ D) && suma) {
      digitalWrite(12, HIGH); // omega
      x_1 = 1;  
    } else {
      digitalWrite(12, LOW);
      x_1 = 0;  
    }

    if ((C && D) && suma) {
      digitalWrite(13, HIGH); // psi
      x_2 = 1;  
    } else {
      digitalWrite(13, LOW);  
      x_2 = 0;      
    }
    

    // Llamada a la función de visualización
    numeros(x_0, x_1, x_2, x_3);


  }else if(resta){// Resta
    
    if (((D&&!C)^(D&&B&&!A)^(!C&&B&&!A)) && (resta)) {//signo
      digitalWrite(13, HIGH);
    } else {
      digitalWrite(13, LOW);
    }
    
    if(((!B&&A)^(B&&!A))&&(resta)){
      x_0=1;
    }else{
      x_0=0;      
    }
    
    if(((!D&&C&&!B)||(!D&&C&&A)||(D&&!C&&B)||(D&&!C&&!A)||(D&&!C&&B))&&(resta)){
      x_1=1;
    }else{
      x_1=0;      
    }
    
    numeros(x_0, x_1, x_2, x_3);
  
  } else if(multi){//multiplicación
    
    if((B&&A)&&(multi)){
      x_0=1;
    }else{
      x_0=0;
    }
    
    if(((!D&&C&&B)||(C&&B&&!A)||(D&&!B&&A)||(D&&!C&&A))&&(multi)){
      x_1=1;
    }else{
      x_1=0;
    }
    
    if(((D&&C&&!B)||(D&&C&&B&&!A))&&(multi)){
      x_2=1;
    }else{
      x_2=0;
    }
    
    if((D&&C&&B&&A)&&(multi)){
      x_3=1;
    }else{
      x_3=0;      
    }
    
    numeros(x_0, x_1, x_2, x_3);
    
  } else if(division){//division

    if((!D&&!C)&&(division)){
      digitalWrite(13,HIGH);
    }else{
      digitalWrite(13,LOW);
    }  
    
    if((!D&&C&&B)&&(division)){//W
      x_1=1;
    }else{
      x_1=0;      
    }
    if((!D&&C&&A)||(D&&!C&&B)||(D&&C&&B&&A)//X
       &&(division)){
      x_0=1;
   	  numeros(x_0, x_1, x_2, x_3);
    }else{
      x_0=0;
    }

    if(((D&&!C&&A)||(D&&C&&B&&!A))&&(division)){//y   
       
        digitalWrite(decimal,HIGH);
        delay(1000);
        digitalWrite(decimal,LOW);    
      	delay(1000);
        x_0=1;
        x_1=0;
        x_2=1;
        x_3=0;        
    }
  if ((D && C && !B && A) && division) {//z
    digitalWrite(decimal, HIGH);
    delay(2000);
    digitalWrite(decimal, LOW);    
    x_3=1;
  } else {
    x_3=0;
  }
   
    numeros(x_0, x_1, x_2, x_3);
    
  }else if(AND){//and
    
    if((A&&B)&&(C&&D)){
      x_0=1;
    }else{
      x_0=0;      
    }
  
  }else if(OR){
  
    if(A||B||C||D){
      x_0=1;
    }else{
      x_0=0;
    }
    
  }else if(XOR){
  
    if((A^B)^(C^D)){
      x_0=1;
    }else{
      x_0=0;
    }
    
  }else {
  	!E;
    !F;
    !G;
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);  
    digitalWrite(g, LOW);     
  }
}

void numeros(int x_0, int x_1, int x_2, int x_3) { 
  // Representación del número 0 en un display de 7 segmentos
  if (!x_0 && !x_1 && !x_2 && !x_3) { // 0000 -> 0
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, LOW);
  } else if (x_0 && !x_1 && !x_2 && !x_3) { // 0001 -> 1
    digitalWrite(a, LOW);    
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);  
    digitalWrite(g, LOW);  
  } else if (!x_0 && x_1 && !x_2 && !x_3) { // 0010 -> 2
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
  } else if (x_0 && x_1 && !x_2 && !x_3) { // 0011 -> 3
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);  
  } else if (!x_0 && !x_1 && x_2 && !x_3) { // 0100 -> 4
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH); 
  } else if (x_0 && !x_1 && x_2 && !x_3) { // 0101 -> 5
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, LOW);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH); 
  } else if (!x_0 && x_1 && x_2 && !x_3) { // 0110 -> 6
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH); 
  } else if (x_0 && x_1 && x_2 && !x_3) { // 0111 -> 7
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW); 
  } else if (!x_0 && !x_1 && !x_2 && x_3) { // 1000 -> 8
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH); 
  } else if (x_0 && !x_1 && !x_2 && x_3) { // 1001 -> 9
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, LOW);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH); 
  } else {
    // Apagar todos los segmentos
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);  
    digitalWrite(g, LOW);   
  }
}
