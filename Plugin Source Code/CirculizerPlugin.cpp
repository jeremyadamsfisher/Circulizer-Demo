
#include <CompuCell3D/CC3D.h>        
using namespace CompuCell3D;

#include "CirculizerPlugin.h"


CirculizerPlugin::CirculizerPlugin():
pUtils(0),
lockPtr(0),
xmlData(0) ,
cellFieldG(0),
boundaryStrategy(0)
{}

CirculizerPlugin::~CirculizerPlugin() {
    pUtils->destroyLock(lockPtr);
    delete lockPtr;
    lockPtr=0;
}

void CirculizerPlugin::init(Simulator *simulator, CC3DXMLElement *_xmlData) {
    xmlData=_xmlData;
    sim=simulator;
    potts=simulator->getPotts();
    cellFieldG = (WatchableField3D<CellG *> *)potts->getCellFieldG();
    
    pUtils=sim->getParallelUtils();
    lockPtr=new ParallelUtilsOpenMP::OpenMPLock_t;
    pUtils->initLock(lockPtr); 
   
   update(xmlData,true);
   
    potts->getCellFactoryGroupPtr()->registerClass(&circulizerDataAccessor);
    potts->registerEnergyFunctionWithName(this,"Circulizer");
        
    potts->registerStepper(this);
    
    simulator->registerSteerableObject(this);
}

void CirculizerPlugin::extraInit(Simulator *simulator){
    
}

void CirculizerPlugin::step() {
    //Put your code here - it will be invoked after every succesful pixel copy and after all lattice monitor finished running
    	
}


double CirculizerPlugin::changeEnergy(const Point3D &pt,const CellG *newCell,const CellG *oldCell) {	
    double energy = 0;
    
    if (oldCell){
        double radius = circulizerDataAccessor.get(oldCell->extraAttribPtr)->circle_radius;
        
        double a = oldCell->xCOM - pt.x;
        double b = oldCell->yCOM - pt.y;
        double c = sqrt(pow(a,2) + pow(b,2));
        
        if(c > radius){
            energy -= xml_energy_penalty;
        }else{
            energy += xml_energy_penalty;
        }
    }
    
    if(newCell){
        double radius = circulizerDataAccessor.get(newCell->extraAttribPtr)->circle_radius;
            
        double a = newCell->xCOM - pt.x;
        double b = newCell->yCOM - pt.y;
        double c = sqrt(pow(a,2) + pow(b,2));
        
        if(c > radius){
            energy += xml_energy_penalty;
        }else{
            energy -= xml_energy_penalty;
        }
    }
    return energy;
}                 

void CirculizerPlugin::setCellRadius(CellG *Cell, float _radius){
    circulizerDataAccessor.get(Cell->extraAttribPtr)->circle_radius = _radius;
}

void CirculizerPlugin::update(CC3DXMLElement *_xmlData, bool _fullInitFlag){
    automaton = potts->getAutomaton();
    ASSERT_OR_THROW("CELL TYPE PLUGIN WAS NOT PROPERLY INITIALIZED YET. MAKE SURE THIS IS THE FIRST PLUGIN THAT YOU SET", automaton)
    set<unsigned char> cellTypesSet;

    CC3DXMLElement * myElement = xmlData->getFirstElement("Penalty");
    if(myElement){
        xml_energy_penalty = myElement->getDouble();
    }else{
        xml_energy_penalty = 99999;
    }
    
    //boundaryStrategy has information aobut pixel neighbors 
    boundaryStrategy=BoundaryStrategy::getInstance();
}

std::string CirculizerPlugin::toString(){
    return "Circulizer";
}


std::string CirculizerPlugin::steerableName(){
    return toString();
}
