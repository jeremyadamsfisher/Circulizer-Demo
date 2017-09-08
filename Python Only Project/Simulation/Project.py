
def configureSimulation(sim):
    import CompuCellSetup
    from XMLUtils import ElementCC3D
    
    CompuCell3DElmnt=ElementCC3D("CompuCell3D",{"Revision":"20141115","Version":"3.7.3"})
    
    PottsElmnt=CompuCell3DElmnt.ElementCC3D("Potts")
    
    PottsElmnt.ElementCC3D("Dimensions",{"x":"100","y":"100","z":"1"})
    PottsElmnt.ElementCC3D("Steps",{},"1000")
    PottsElmnt.ElementCC3D("Temperature",{},"10.0")
    PottsElmnt.ElementCC3D("NeighborOrder",{},"1")
    
    PluginElmnt=CompuCell3DElmnt.ElementCC3D("Plugin",{"Name":"CellType"})
    PluginElmnt.ElementCC3D("CellType",{"TypeId":"0","TypeName":"Medium"})
    PluginElmnt.ElementCC3D("CellType",{"TypeId":"1","TypeName":"Cell"})
    
    CompuCell3DElmnt.ElementCC3D("Plugin",{"Name":"Volume"})
    CompuCell3DElmnt.ElementCC3D("Plugin",{"Name":"Surface"})
    PluginElmnt_1=CompuCell3DElmnt.ElementCC3D("Plugin",{"Name":"CenterOfMass"})
    
    PluginElmnt_2=CompuCell3DElmnt.ElementCC3D("Plugin",{"Name":"Contact"})
    PluginElmnt_2.ElementCC3D("Energy",{"Type1":"Medium","Type2":"Medium"},"10.0")
    PluginElmnt_2.ElementCC3D("Energy",{"Type1":"Medium","Type2":"Cell"},"10.0")
    PluginElmnt_2.ElementCC3D("Energy",{"Type1":"Cell","Type2":"Cell"},"10.0")
    PluginElmnt_2.ElementCC3D("NeighborOrder",{},"1")
    
    PluginElmnt_3=CompuCell3DElmnt.ElementCC3D("Plugin",{"Name":"ConnectivityGlobal"})
    PluginElmnt_3.ElementCC3D("Penalty",{"Type":"Cell"},"1000000")
    
    SteppableElmnt=CompuCell3DElmnt.ElementCC3D("Steppable",{"Type":"UniformInitializer"})
    
    RegionElmnt=SteppableElmnt.ElementCC3D("Region")
    RegionElmnt.ElementCC3D("BoxMin",{"x":"40","y":"40","z":"0"})
    RegionElmnt.ElementCC3D("BoxMax",{"x":"60","y":"60","z":"1"})
    RegionElmnt.ElementCC3D("Gap",{},"0")
    RegionElmnt.ElementCC3D("Width",{},"20")
    RegionElmnt.ElementCC3D("Types",{},"Cell")

    CompuCellSetup.setSimulationXMLDescription(CompuCell3DElmnt)    
            
import sys
from os import environ
from os import getcwd
import string
sys.path.append(environ["PYTHON_MODULE_PATH"])
import CompuCellSetup

sim,simthread = CompuCellSetup.getCoreSimulationObjects()
configureSimulation(sim)            
CompuCellSetup.initializeSimulationObjects(sim,simthread)

steppableRegistry=CompuCellSetup.getSteppableRegistry()
        
from ProjectSteppables import ConstraintInitializerSteppable
ConstraintInitializerSteppableInstance=ConstraintInitializerSteppable(sim,_frequency=1)
steppableRegistry.registerSteppable(ConstraintInitializerSteppableInstance)
        
energyFunctionRegistry=CompuCellSetup.getEnergyFunctionRegistry(sim)
from ProjectSteppables import myEnergyFunction
myEnegyFunction=myEnergyFunction(energyFunctionRegistry)
energyFunctionRegistry.registerPyEnergyFunction(myEnegyFunction)        
        
CompuCellSetup.mainLoop(sim,simthread,steppableRegistry)
        
        