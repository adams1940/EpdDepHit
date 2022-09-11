#include <bitset>
#include "TObject.h"

class StEpdDepHit : public TObject{
  public:
    StEpdDepHit(){
      EncodedAdcOverflow = 0;
    };
    virtual ~StEpdDepHit(){};

    int adc(int TimeBin){
      switch(TimeBin){
        case 0:
          return EncodedAdc[0]%4096;
        case 1:
          return (EncodedAdc[0]%16777216)>>12;
        case 2:
          return ((EncodedAdc[1]%16)<<8)+(EncodedAdc[0]>>24);
        case 3:
          return (EncodedAdc[1]%65536)>>4;
        case 4:
          return (EncodedAdc[1]%268435456)>>16;
        case 5:
          return ((EncodedAdc[2]%256)<<4)+(EncodedAdc[1]>>28);
        case 6:
          return (EncodedAdc[2]%1048576)>>8;
        case 7:
          return EncodedAdc[2]>>20;
      }
      return 0;
    };
    bool AdcIsTruncated(int TimeBin){
      return (EncodedAdcOverflow >> (TimeBin+1)) & 1U;
    }

    void SetAdc(int adc[8]){
      for( int i=0; i<8; i++ ){
        if( adc[i]>4095 ){ adc[i] = 4095; EncodedAdcOverflow |= 1UL << (i+1); }
        else if( adc[i]<0 ) adc[i] = 0;
      }

      EncodedAdc[0] = adc[0]+(adc[1]<<12)+((adc[2]%256)<<24);
      EncodedAdc[1] = (adc[2]>>8)+(adc[3]<<4)+(adc[4]<<16)+((adc[5]%16)<<28);
      EncodedAdc[2] = ((adc[5]-adc[5]%16)>>4)+(adc[6]<<8)+(adc[7]<<20);
    };

  protected:
    unsigned int EncodedAdc[3];
    char EncodedAdcOverflow;
    
}; // StEpdDepHit

void BitShift(){
  int Adc[8];
  TRandom3 * ran = new TRandom3(0);
  for( int i = 0 ;i < 8; i++  ) Adc[i] = ran->Uniform(0,5000);

  StEpdDepHit Hit;
  Hit.SetAdc(Adc);
  for( int i=0; i<8; i++ ){
    cout<<Hit.adc(i)<<"\t"<<Hit.AdcIsTruncated(i)<<endl;
  }

}