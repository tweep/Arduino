#ifndef SpectrumBand_h
#define SpectrumBand_h


//#include "Arduino.h" 

// do not define a struct within a class file - otherwise it won't be visible to other classes 

// Note: Both definitions ( struct and "typedef struct" are allowed. ) I don't know which one is better ... 


struct SpectrumBand {
  byte start;
  byte end;
} ;  
// Note: 
// In the first line you are defining the identifier SpectrumBand within the struct namespace 
// (not in the C++ sense). You can use it and define variables or function arguments of the 
// newly defined type by defining the type of the argument as struct S:
// void f( struct S argument ); // struct keyword is required here



// Note: add a type alias SpectrumBand in the global name space, this thus allows you to just write:
// void f( SpectrumBand argument ); // You do not need the "struct"  keyword here anymore. 

typedef struct SpectrumBand SpectrumBand; 

/*
typedef struct SpectrumBand {
  byte start;
  byte end;
} SpectrumBand;  
*/
// moreinfo on the declaration : http://stackoverflow.com/questions/1675351/typedef-struct-vs-struct-definitions

/*
struct SpectrumBand {
  byte start;
  byte end;
} ;  
*/  

/*
typedef struct {
  byte start;
  byte end;
} SpectrumBand;  
*/

#endif

