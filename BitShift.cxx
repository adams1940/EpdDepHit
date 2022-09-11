#include <bitset>

int CalcAdc(unsigned int Dat[3], int tb){
  switch(tb){
    case 0:
      return Dat[0]%4096;
    case 1:
      return (Dat[0]%16777216)>>12;
    case 2:
      return ((Dat[1]%8)<<8)+(Dat[0]>>24);
    case 3:
      return (Dat[1]%65536)>>4;
    case 4:
      return (Dat[1]%268435456)>>16;
    case 5:
      return ((Dat[2]%128)<<4)+(Dat[1]>>28);
    case 6:
      return (Dat[2]%1048576)>>8;
    case 7:
      return Dat[2]>>20;
  }
  return 0;
}

void BitShift(){
  unsigned int Dat[3];
  char OverFlow = 0;

  int Adc[8] = {352,398,1539,502,10,37,1,999};
  //int Adc[8]; for( int i=0; i<8; i++ ) Adc[i] = (i%2==1)?0:4095;


//  Dat[0] = Adc[0]+(Adc[1]<<12)+((Adc[2]%256)<<24);
//  Dat[1] = ((Adc[2]-Adc[2]%256)>>8)+(Adc[3]<<4)+(Adc[4]<<16)+(Adc[5]%16);
//  Dat[2] = ((Adc[5]-Adc[5]%16)>>4)+(Adc[6]<<8)+(Adc[7]<<20);
  Dat[0] = Adc[0]+(Adc[1]<<12)+((Adc[2]%256)<<24);
  Dat[1] = (Adc[2]>>8)+(Adc[3]<<4)+(Adc[4]<<16)+((Adc[5]%16)<<28);
  Dat[2] = ((Adc[5]-Adc[5]%16)>>4)+(Adc[6]<<8)+(Adc[7]<<20);

//  cout<<"------------------"<<endl;
//  bitset<32> bs[4];
//  bs[0] = Dat[1];
//  bs[1] = (Adc[2]>>8);
//  bs[1] = (Adc[2]>>8);
//  bs[2] = (Adc[3]<<4);
//  bs[2] = (Adc[3]<<4);
//  bs[3] = (Adc[4]<<16);
//  bs[3] = (Adc[4]<<16);
//  bs[4] = (Adc[5]%16);
//  bs[4] = (Adc[5]%16);
//  cout<<"------------------"<<endl;

  cout<<CalcAdc(Dat,7)<<endl;


  //Dat[0] = (255<<(32-8))+(0<<16)+(4095);
  //Dat[0] = 1+(2<<1);

  //for( int i=0; i<8; i++ ){
  //  bitset<32> x(Adc[i]);
  //  cout<<x<<endl;
  //}
  //bitset<32> x(CalcAdc(Dat,2));
  //bitset<32> x(CalcAdc[2]);
  //cout<<x<<endl;
  for( int i=0; i<3; i++ ){
    bitset<32> x(Dat[i]);
    cout<<x<<endl;
  }
}