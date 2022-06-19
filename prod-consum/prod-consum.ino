#include <dataStructures.h>
#include <rdp.h>
#include <pthread.h>


void loop() {}

void setup() {
   Serial.begin(115200);
   main();
}

void printVector(o_vector p_vector)
{
     Serial.print("{ ");
     for (int i = 0; i < p_vector.size; i++)
     {
         Serial.print(p_vector.vector[i]);
     }
     Serial.print("}\n");
}
int main(){

  pthread_attr_t atrib;
  pthread_t c[5];

  pthread_attr_init(&atrib);

  int shoot[1];
  shoot[0] = 0;
  rdp_o rdp;
  if(new_rdp(&rdp)==ALLOC_ERROR)
  {
      Serial.print("ERROR DE ALOCACION\n");
      exit(1);
  }
  printVector(rdp.M);

  rdp.Sensitized.v_methods->print(rdp.Sensitized);
  

  Serial.println(rdp.metodos->isPos(&rdp, shoot));

  printVector(rdp.Sensitized);

  rdp.metodos->cleanRDP(&rdp);

}
