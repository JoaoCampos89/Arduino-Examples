 /**
  * 
  * Example of mux usage with arduino
  * 
  */


// digital pin ports
const int portX0 = 2;
const int portX1 = 3;
// analog common port
const int portY0 = 12;


// vetor with sensor values
float sensor[4];

int count = 0;   //which y0 pin we are selecting
 // declare a timer to be used by mux task
unsigned long muxTimer = 0; 

 
void setup() {
 // digital pin X0 defined as output
  pinMode(portX0, OUTPUT);    
 // digital pin X1 defined as output
  pinMode(portX1, OUTPUT);   
// analog port
  pinMode(portY0, INPUT);   

}

void loop() {


	
// fill array sensor with mux analog ports switching each 10 ms
  muxTask(sensor,10);

}

//*********************************
//*********************************
//       Functions
//**********************************
//*********************************


/**
 * 
 * mux task
 * 
 * @param timeInterval define the interval time to get values from mux 
 * @param reading array to fill with analog values 
 */
 
void muxTask(float reading[], int timeInterval){
  // disable update of muxTimer
   flagMux = false;
	// digital pins that selects the sensor
	int x0 = 0;      
	int x1 = 0;     
  // getting the actual time
   unsigned long currentMillis = millis();
   
   int atualInterval = currentMillis - muxTimer;
   // if time is bigger than the defined interval change the mux digital pins and performs the reading in the 
   // common port
   if(atualInterval > timeInterval)
   {
		// updates mux timer
		muxTimer = currentMillis;
		// enable flag to update muxTimer
		flagMux = true;
        count++;
        
        if(count >3)
        {
          count = 0;  
        }
        // read 0 bit
        x0 = bitRead(count,0);    
        // read 1 bit     
        x1 = bitRead(count,1);  
       // writing to mux digital ports
         digitalWrite(portX0, x0);
         digitalWrite(portX1, x1);
         // delay to assure that the mux switch the ports
         delayMicroseconds(100); 
         
         // read from mux
         reading[count] = analogRead(portY0)
    
      
      
   }

}




