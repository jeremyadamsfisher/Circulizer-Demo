
#ifndef CIRCULIZERPATA_H
#define CIRCULIZERPATA_H


#include <vector>
#include "CirculizerDLLSpecifier.h"

namespace CompuCell3D {

   
   class CIRCULIZER_EXPORT CirculizerData{
      public:
         CirculizerData(){};
         
         ~CirculizerData(){};
         std::vector<float> array;
         int x;
         
         double circle_radius;
   };
};
#endif
