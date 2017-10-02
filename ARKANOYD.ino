int rowA[] = {9,8,7,6,5,4,3,2};          
                                         
int colA[] = {17,16,15,14,13,12,11,10};  
                                         
byte data[] = {0,0,0,0,0,0,0,0};    
int pauseDelay = 1;    
int speed = 1000;//5
int riga = 6, colonna=3;
///////////ANALOGICO
const byte PIN_ANALOG_X = 0;
const byte PIN_ANALOG_Y = 1;
int direzione_x = 3;
int x_position;
const int X_THRESHOLD_LOW = 900;
const int X_THRESHOLD_HIGH = 1023; 
////////////////////

int tempo_numeri = 150;
bool ok = false;

bool fermati = false;
bool perso = false;
bool centro = false, sinistra = false, destra = false;
int mattoncini_score = 0;

byte matrice[8][8] = //matrice che rappresenta i led accesi (1) o spenti (0) ----> questa viene modificata durante il gioco
{  
        {1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0},
        {0,0,1,1,1,0,0,0},
};


void setup()
{ 
  Serial.begin(9600);// apro la porta per il monitor seriale        
  for(int i = 0; i <8; i++)//imposto i pin della matrice come uscite
  {  
    pinMode(rowA[i], OUTPUT);
    pinMode(colA[i], OUTPUT);
  }
  
}


void pad()//funzione per il movimento del pad
{
  
  x_position = map(analogRead(PIN_ANALOG_X), 0, 1023, 0, 255);//leggo il valore della x dell'analogico del joystick
  //Serial.println(x_position);
  if (x_position == 255) 
  {
    direzione_x++;
    if(direzione_x >6)//per non "far uscire" il pad dalla matrice di led
        direzione_x=6;
  } 
  else if (x_position > 200 && x_position < 250) 
  {
    direzione_x--;
    if(direzione_x < 1)//per non "far uscire" il pad dalla matrice di led
        direzione_x=1;
  }
  
  switch (direzione_x)//movimento pad
  {
        case 1:
        matrice[7][0] = 1;matrice[7][1] = 1;matrice[7][2] = 1; matrice[7][3] = 0;matrice[7][4] = 0; matrice[7][5] = 0;matrice[7][6] = 0;matrice[7][7] = 0;break;
        case 2:
        matrice[7][0] = 0;matrice[7][1] = 1;matrice[7][2] = 1; matrice[7][3] = 1;matrice[7][4] = 0; matrice[7][5] = 0;matrice[7][6] = 0;matrice[7][7] = 0;break;
        case 3:
        matrice[7][0] = 0;matrice[7][1] = 0;matrice[7][2] = 1; matrice[7][3] = 1;matrice[7][4] = 1; matrice[7][5] = 0;matrice[7][6] = 0;matrice[7][7] = 0;break;
        case 4:
        matrice[7][0] = 0;matrice[7][1] = 0;matrice[7][2] = 0; matrice[7][3] = 1;matrice[7][4] = 1; matrice[7][5] = 1;matrice[7][6] = 0;matrice[7][7] = 0;break;
        case 5:
        matrice[7][0] = 0;matrice[7][1] = 0;matrice[7][2] = 0; matrice[7][3] = 0;matrice[7][4] = 1; matrice[7][5] = 1;matrice[7][6] = 1;matrice[7][7] = 0;break;
        case 6:
        matrice[7][0] = 0;matrice[7][1] = 0;matrice[7][2] = 0; matrice[7][3] = 0;matrice[7][4] = 0; matrice[7][5] = 1;matrice[7][6] = 1;matrice[7][7] = 1;break;
  }
}

void refresh_matrice()//converte il binario in decimale
{
  data[0] = matrice[0][0] * 128 + matrice[0][1] * 64 + matrice[0][2] * 32 +  matrice[0][3] * 16  +  matrice[0][4] * 8 +  matrice[0][5] * 4 +  matrice[0][6] * 2 + matrice[0][7]; 
  data[1] = matrice[1][0] * 128 + matrice[1][1] * 64 + matrice[1][2] * 32 +  matrice[1][3] * 16  +  matrice[1][4] * 8 +  matrice[1][5] * 4 +  matrice[1][6] * 2 + matrice[1][7]; 
  data[2] = matrice[2][0] * 128 + matrice[2][1] * 64 + matrice[2][2] * 32 +  matrice[2][3] * 16  +  matrice[2][4] * 8 +  matrice[2][5] * 4 +  matrice[2][6] * 2 + matrice[2][7];
  data[3] = matrice[3][0] * 128 + matrice[3][1] * 64 + matrice[3][2] * 32 +  matrice[3][3] * 16  +  matrice[3][4] * 8 +  matrice[3][5] * 4 +  matrice[3][6] * 2 + matrice[3][7]; 
  data[4] = matrice[4][0] * 128 + matrice[4][1] * 64 + matrice[4][2] * 32 +  matrice[4][3] * 16  +  matrice[4][4] * 8 +  matrice[4][5] * 4 +  matrice[4][6] * 2 + matrice[4][7]; 
  data[5] = matrice[5][0] * 128 + matrice[5][1] * 64 + matrice[5][2] * 32 +  matrice[5][3] * 16  +  matrice[5][4] * 8 +  matrice[5][5] * 4 +  matrice[5][6] * 2 + matrice[5][7]; 
  data[6] = matrice[6][0] * 128 + matrice[6][1] * 64 + matrice[6][2] * 32 +  matrice[6][3] * 16  +  matrice[6][4] * 8 +  matrice[6][5] * 4 +  matrice[6][6] * 2 + matrice[6][7];   
  data[7] = matrice[7][0] * 128 + matrice[7][1] * 64 + matrice[7][2] * 32 +  matrice[7][3] * 16  +  matrice[7][4] * 8 +  matrice[7][5] * 4 +  matrice[7][6] * 2 + matrice[7][7];
}

void faccina()
{
  if(ok == false)
  { 
      data[0] = B11000011; 
      data[1] = B11000011; 
      data[2] = B00000000;
      data[3] = B00011000; 
      data[4] = B00011000; 
      data[5] = B01000010; 
      data[6] = B00111100;   
      data[7] = B00000000;
      showSprite(500);
  }
}

void numeri()
{
   if(ok == false)
  { 
      
      data[0] = B01111100;
      data[1] = B00000010;
      data[2] = B00000010;
      data[3] = B00111100; 
      data[4] = B00000010; 
      data[5] = B00000010;   
      data[6] = B01111100;
      data[7] = B00000000;
      showSprite(tempo_numeri);
      
      data[0] = B00111100;
      data[1] = B01000010; 
      data[2] = B00000010; 
      data[3] = B00001000; 
      data[4] = B00010000;
      data[5] = B00100000; 
      data[6] = B01111110;  
      data[7] = B00000000;
      showSprite(tempo_numeri);
      
      
      data[0] = B00001000;
      data[1] = B00011000;
      data[2] = B00101000; 
      data[3] = B01001000;
      data[4] = B00001000;
      data[5] = B00001000;
      data[6] = B00001000; 
      data[7] = B00000000;
      showSprite(tempo_numeri);
      
      
      
     
     speed = 5;
     ok = true;
  }
 
}



void hai_perso()
{
  if (perso == true)
  {
        
    for(int n = 0; n<5; n++)
    {
            data[0] =      B11111111;
            data[1] =      B11111111;
            data[2] =      B11111111;
            data[3] =      B11111111;
            data[4] =      B11111111;
            data[5] =      B11111111;
            data[6] =      B11111111;
            data[7] =      B11111111;
            showSprite(20);
            
            data[0] =      B00000000;
            data[1] =      B00000000;
            data[2] =      B00000000;
            data[3] =      B00000000;
            data[4] =      B00000000;
            data[5] =      B00000000;
            data[6] =      B00000000;
            data[7] =      B00000000;
            showSprite(20);
    }
    
             data[0] =    B1000001;//visualizzo la 
             data[1] =    B1000001;
             data[2] =    B1000001;
             data[3] =    B1111111;
             data[4] =    B1000001;
             data[5] =    B1000001;
             data[6] =    B1000001;
             data[7] =    B0000000;
             showSprite(100); 
              
             data[0] =     B0001000;
             data[1] =     B0010100;
             data[2] =     B0100010;
             data[3] =     B1000001;
             data[4] =     B1111111;
             data[5] =     B1000001;
             data[6] =     B1000001;
             data[7] =     B0000000;
             showSprite(100);    
             data[0] =     B1111111;
             data[1] =     B0001000;
             data[2] =     B0001000;
             data[3] =     B0001000;
             data[4] =     B0001000;
             data[5] =     B0001000;
             data[6] =     B1111111;
             data[7] =     B0000000;
             showSprite(100);    
             data[0] =     B0000000;
             data[1] =     B0000000;
             data[2] =     B0000000;
             data[3] =     B0000000;
             data[4] =     B0000000;
             data[5] =     B0000000;
             data[6] =     B0000000;
             showSprite(100);    
             data[0] =     B1111110;
             data[1] =     B0100001;
             data[2] =     B0100001;
             data[3] =     B0111110;
             data[4] =     B0100000;
             data[5] =     B0100000;
             data[6] =     B0100000;
             data[7] =     B0000000;
             showSprite(100);   
             data[0] =     B1111111;
             data[1] =     B1000000;
             data[2] =     B1000000;
             data[3] =     B1111100;
             data[4] =     B1000000;
             data[5] =     B1000000;
             data[6] =     B1111111;
             data[7] =     B0000000;   
            showSprite(100);     
            data[0] =      B1111110;
            data[1] =      B0100001;
            data[2] =      B0100001;
            data[3] =      B0101110;
            data[4] =      B0100100;
            data[5] =      B0100010;
            data[6] =      B0100001;
            data[7] =      B0000000;
            showSprite(100);    
            data[0] =      B0111111;
            data[1] =      B1000000;
            data[2] =      B1000000;
            data[3] =      B0111110;
            data[4] =      B0000001;
            data[5] =      B0000001;
            data[6] =      B1111110;
            data[7] =      B0000000;
            showSprite(100);      
            data[0] =      B0011100;
            data[1] =      B0100010;
            data[2] =      B1000001;
            data[3] =      B1001001;
            data[4] =      B1000001;
            data[6] =      B0011100;
            data[7] =      B0000000;
            showSprite(100);
        for(int n = 0; n<5; n++)
        {
            data[0] =      B11111111;
            data[1] =      B11111111;
            data[2] =      B11111111;
            data[3] =      B11111111;
            data[4] =      B11111111;
            data[5] =      B11111111;
            data[6] =      B11111111;
            data[7] =      B11111111;
            showSprite(20);
            
            data[0] =      B00000000;
            data[1] =      B00000000;
            data[2] =      B00000000;
            data[3] =      B00000000;
            data[4] =      B00000000;
            data[5] =      B00000000;
            data[6] =      B00000000;
            data[7] =      B00000000;
            showSprite(20);
        }     
        
        
     speed = 5;
    //reinizilizzo la matrice (devo farlo singolarmente perchè se no non funziona 
    matrice[0][0] = 1;matrice[0][1] = 1;matrice[0][2] = 1; matrice[0][3] = 1;matrice[0][4] = 1; matrice[0][5] = 1;matrice[0][6] = 1;matrice[0][7] = 1;
    matrice[1][0] = 1;matrice[1][1] = 1;matrice[1][2] = 1; matrice[1][3] = 1;matrice[1][4] = 1; matrice[1][5] = 1;matrice[1][6] = 1;matrice[1][7] = 1;
    matrice[2][0] = 1;matrice[2][1] = 1;matrice[2][2] = 1; matrice[2][3] = 1;matrice[2][4] = 1; matrice[2][5] = 1;matrice[2][6] = 1;matrice[2][7] = 1;
    matrice[6][0] = 0;matrice[6][1] = 0;matrice[6][2] = 0; matrice[6][3] = 1;matrice[6][4] = 0; matrice[6][5] = 0;matrice[6][6] = 0;matrice[6][7] = 0;
    refresh_matrice();
    direzione_x = 3;//reimposto la posizione del pad
    mattoncini_score = 0;
     perso = false;  
     ok = false;
 }

 
}

void hai_vinto()
{
        
    for(int n = 0; n<5; n++)
    {
            data[0] =      B11111111;
            data[1] =      B11111111;
            data[2] =      B11111111;
            data[3] =      B11111111;
            data[4] =      B11111111;
            data[5] =      B11111111;
            data[6] =      B11111111;
            data[7] =      B11111111;
            showSprite(20);
            
            data[0] =      B00000000;
            data[1] =      B00000000;
            data[2] =      B00000000;
            data[3] =      B00000000;
            data[4] =      B00000000;
            data[5] =      B00000000;
            data[6] =      B00000000;
            data[7] =      B00000000;
            showSprite(20);
    }
    
             data[0] =    B1000001;//visualizzo la 
             data[1] =    B1000001;
             data[2] =    B1000001;
             data[3] =    B1111111;
             data[4] =    B1000001;
             data[5] =    B1000001;
             data[6] =    B1000001;
             data[7] =    B0000000;
             showSprite(100); 
              
             data[0] =     B0001000;
             data[1] =     B0010100;
             data[2] =     B0100010;
             data[3] =     B1000001;
             data[4] =     B1111111;
             data[5] =     B1000001;
             data[6] =     B1000001;
             data[7] =     B0000000;
             showSprite(100);    
             data[0] =     B1111111;
             data[1] =     B0001000;
             data[2] =     B0001000;
             data[3] =     B0001000;
             data[4] =     B0001000;
             data[5] =     B0001000;
             data[6] =     B1111111;
             data[7] =     B0000000;
             showSprite(100);    
             data[0] =     B0000000;
             data[1] =     B0000000;
             data[2] =     B0000000;
             data[3] =     B0000000;
             data[4] =     B0000000;
             data[5] =     B0000000;
             data[6] =     B0000000;
             showSprite(100);    
             
             
             data[0] =     B1000001;
             data[1] =     B1000001;
             data[2] =     B1000001;
             data[3] =     B1000001;
             data[4] =     B0100010;
             data[5] =     B0010100;
             data[6] =     B0001000;
             data[7] =     B0000000;
             showSprite(100);
             
             data[0] =     B1111111;// I
             data[1] =     B0001000;
             data[2] =     B0001000;
             data[3] =     B0001000;
             data[4] =     B0001000;
             data[5] =     B0001000;
             data[6] =     B1111111;
             data[7] =     B0000000;
             showSprite(100); 
              
              
             data[0] =     B1000001;
             data[1] =     B1100001;
             data[2] =     B1010001;
              data[3] =    B1001001;
             data[4] =     B1000101;
             data[5] =     B1000011;
             data[6] =     B1000001;
             data[7] =     B0000000;
             showSprite(100);     
            data[0] =      B1111111;
            data[1] =     B0001000;
            data[2] =      B0001000;
            data[3] =      B0001000;
            data[4] =      B0001000;
            data[5] =      B0001000;
            data[6] =      B0001000;
            data[7] =      B0000000;
             showSprite(100);     
                 
            data[0] =      B0011100;
            data[1] =      B0100010;
            data[2] =      B1000001;
            data[3] =      B1001001;
            data[4] =      B1000001;
            data[6] =      B0011100;
            data[7] =      B0000000;
            showSprite(100);
        for(int n = 0; n<5; n++)
        {
            data[0] =      B11111111;
            data[1] =      B11111111;
            data[2] =      B11111111;
            data[3] =      B11111111;
            data[4] =      B11111111;
            data[5] =      B11111111;
            data[6] =      B11111111;
            data[7] =      B11111111;
            showSprite(20);
            
            data[0] =      B00000000;
            data[1] =      B00000000;
            data[2] =      B00000000;
            data[3] =      B00000000;
            data[4] =      B00000000;
            data[5] =      B00000000;
            data[6] =      B00000000;
            data[7] =      B00000000;
            showSprite(20);
        }     
        
        
        speed = 5;
    
    //reinizilizzo la matrice (devo farlo singolarmente perchè se no non funziona 
    matrice[0][0] = 1;matrice[0][1] = 1;matrice[0][2] = 1; matrice[0][3] = 1;matrice[0][4] = 1; matrice[0][5] = 1;matrice[0][6] = 1;matrice[0][7] = 1;
    matrice[1][0] = 1;matrice[1][1] = 1;matrice[1][2] = 1; matrice[1][3] = 1;matrice[1][4] = 1; matrice[1][5] = 1;matrice[1][6] = 1;matrice[1][7] = 1;
    matrice[2][0] = 1;matrice[2][1] = 1;matrice[2][2] = 1; matrice[2][3] = 1;matrice[2][4] = 1; matrice[2][5] = 1;matrice[2][6] = 1;matrice[2][7] = 1;
    matrice[6][0] = 0;matrice[6][1] = 0;matrice[6][2] = 0; matrice[6][3] = 1;matrice[6][4] = 0; matrice[6][5] = 0;matrice[6][6] = 0;matrice[6][7] = 0;
    refresh_matrice();
    direzione_x = 3;//reimposto la posizione del pad
    mattoncini_score = 0;
     perso = false;  
     ok = false;
 }
 
int direzione = 6;

void direzione_pallina()
{

  if(matrice[6][colonna] == 1)
  {
                
		if(matrice[7][colonna] == 1 && matrice[7][colonna+1] == 1 && matrice[7][colonna-1] == 1)//centrale
                          direzione = 1;
                else
		if((matrice[7][colonna] == 1 && matrice[7][colonna+1] ==1 && matrice[7][colonna+2] == 1 ) || (matrice[7][colonna+1] == 1 && matrice[7][colonna+2] ==1 && matrice[7][colonna+3] == 1 ))//sinistra
                          direzione = 6; 
                else
		if((matrice[7][colonna] == 1 && matrice[7][colonna-1] == 1 && matrice[7][colonna-2] == 1)||(matrice[7][colonna-1] == 1 && matrice[7][colonna-2] == 1 && matrice[7][colonna-3] == 1) )//
                          direzione = 2;
                else
                perso = true;
                
                if(colonna == 7 && matrice[7][colonna] == 1 && matrice[7][colonna-1] == 1 && matrice[7][colonna-2] == 1)
                direzione = 6;
  }

                 
}

void mattoncini()
{

 if(matrice[riga][colonna] == 1)
{ 
  
  if(mattoncini_score < 21)
{
   if(matrice[riga-1][colonna-1] == 1 && direzione == 6)
   {
       
     matrice[riga-1][colonna-1] = 0;
       direzione = 3;
      mattoncini_score++;
   }
   
    if(matrice[riga-1][colonna] == 1 && direzione == 1)
   {
       matrice[riga-1][colonna] = 0;
       direzione = 4;
        mattoncini_score++;
   }
   
    if(matrice[riga-1][colonna] == 1 && direzione == 6)
   {
       matrice[riga-1][colonna] = 0;
       direzione = 3;
       mattoncini_score++;
   }
   
   if(matrice[riga-1][colonna+1] == 1 && direzione == 2)
   {
       matrice[riga-1][colonna+1] = 0;
       direzione = 5;
        mattoncini_score++;
   }
   
   if(matrice[riga+1][colonna+1] == 1  && direzione == 3)
   {
     matrice[riga+1][colonna+1] = 0;
     direzione = 6;
      mattoncini_score++;
   }
     
   
}

else
{
   if(matrice[riga-1][colonna] == 1)
   {
     matrice[riga-1][colonna] = 0;
     direzione = 4;
     mattoncini_score++;
   }
  if(colonna == 7 && matrice[7][colonna] == 1 && matrice[7][colonna-1] == 1 && matrice[7][colonna-2] == 1)
        direzione = 1;
   
}

}
}


void controllo_rimbalzo()
{
  if(colonna == 0 && direzione == 6)//rimbalza contro la colonna sinistra
       direzione = 2;
       
    if(riga == 0 && direzione == 2)//rimbalzo a destra
      direzione = 3; 
      
    if(riga == 0 && direzione == 1)//rimbalzo a destra
      direzione = 4;
      
     if(colonna == 7 && direzione == 3)
     direzione = 5;
     
     if(colonna == 7 && direzione == 2)
        direzione = 6;

     if(riga == 0 && direzione == 6)
      direzione = 5;
      
     if(colonna == 0 && direzione == 5)
     direzione = 3;

}



int direzioney;
int direzionex;
               
  
void movimento_pallina()
{
 
  //controllo_rimbalzo();    
  switch (direzione)
  {
    case 1:
            direzionex=0;
            direzioney=-1;
            break;
    case 2: 
            direzionex=1;
            direzioney=-1; 
            break;
    case 3:
            direzionex=1;
            direzioney=1;
            break;
    case 4:
            direzionex=0;
            direzioney=1;
            break;
    case 5:
            direzionex=-1;
            direzioney=1;
            
            break;
    case 6:
            direzionex=-1;
            direzioney=-1;
            break;
            
  }
  
    
          
  mattoncini();
  matrice[riga][colonna] = 0;//spengo il led appena visualizzato
  
    colonna += direzionex;
    riga += direzioney;

    controllo_rimbalzo();
          
    matrice[riga][colonna] = 1;//accendo il led corrispondente al movimento della pallina
    refresh_matrice();//eseguo il refresh della matricer
    showSprite(10);//visualizzo la matrice 
}
     
 
void loop()
{ 
  faccina();
  numeri();
  speed = 5;
  
  if(mattoncini_score == 24)
    hai_vinto();
  direzione_pallina();
  movimento_pallina();
  hai_perso();
  pad();
  Serial.println(mattoncini_score);
}



void showSprite(int speed2){
 for(int iii = 0; iii < speed2; iii++){                 
  for(int column = 0; column < 8; column++){            
   for(int i = 0; i < 8; i++){                          
       digitalWrite(rowA[i], LOW);                        
   }
   for(int i = 0; i < 8; i++){ //Set only the one pin
     if(i == column){     digitalWrite(colA[i], LOW);}  
     else{                digitalWrite(colA[i], HIGH); }
   }

   for(int row = 0; row < 8; row++){                    
    int bit = (data[column] >> row) & 1;
    if(bit == 1){ 
       digitalWrite(rowA[row], HIGH);                   
    }

   }
   delay(pauseDelay);                       
  } 
 }
}



