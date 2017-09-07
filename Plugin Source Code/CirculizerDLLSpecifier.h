
#ifndef CIRCULIZER_EXPORT_H
#define CIRCULIZER_EXPORT_H

    #if defined(_WIN32)
      #ifdef CirculizerShared_EXPORTS
          #define CIRCULIZER_EXPORT __declspec(dllexport)
          #define CIRCULIZER_EXPIMP_TEMPLATE
      #else
          #define CIRCULIZER_EXPORT __declspec(dllimport)
          #define CIRCULIZER_EXPIMP_TEMPLATE extern
      #endif
    #else
         #define CIRCULIZER_EXPORT
         #define CIRCULIZER_EXPIMP_TEMPLATE
    #endif

#endif
