#ifndef CIRCULIZERPLUGIN_H
#define CIRCULIZERPLUGIN_H
#include <CompuCell3D/CC3D.h>
#include "CirculizerData.h"
#include "CirculizerDLLSpecifier.h"

class CC3DXMLElement;

namespace CompuCell3D {
    class Simulator;
    class Potts3D;
    class Automaton;
    //class AdhesionFlexData;
    class BoundaryStrategy;
    class ParallelUtilsOpenMP;
    
    template <class T> class Field3D;
    template <class T> class WatchableField3D;

    class CIRCULIZER_EXPORT  CirculizerPlugin : public Plugin ,public EnergyFunction  ,public Stepper{
        
    private:    
        BasicClassAccessor<CirculizerData> circulizerDataAccessor;                
        CC3DXMLElement *xmlData;        
        Potts3D *potts;
        Simulator *sim;
        ParallelUtilsOpenMP *pUtils;
        ParallelUtilsOpenMP::OpenMPLock_t *lockPtr;
        Automaton *automaton;
        BoundaryStrategy *boundaryStrategy;
        WatchableField3D<CellG *> *cellFieldG;
        
    public:
        CirculizerPlugin();
        virtual ~CirculizerPlugin();
        BasicClassAccessor<CirculizerData> * getCirculizerDataAccessorPtr(){return & circulizerDataAccessor;}                

        //My changes
        virtual void setCellRadius(CellG *Cell, float _radius);
        double xml_energy_penalty;
        
        //Energy function interface
        virtual double changeEnergy(const Point3D &pt, const CellG *newCell, const CellG *oldCell);        
        
        // Stepper interface
        virtual void step();        
        virtual void init(Simulator *simulator, CC3DXMLElement *_xmlData=0);
        virtual void extraInit(Simulator *simulator);

        //Steerrable interface
        virtual void update(CC3DXMLElement *_xmlData, bool _fullInitFlag=false);
        virtual std::string steerableName();
        virtual std::string toString();
    };
};
#endif
        
