
from PySteppables import *
import CompuCell
import sys
from PyPlugins import *
import math

class ConstraintInitializerSteppable(SteppableBasePy):
    def __init__(self,_simulator,_frequency=1):
        SteppableBasePy.__init__(self,_simulator,_frequency)
    def start(self):
        for cell in self.cellList:
            cell.targetVolume=cell.volume
            cell.lambdaVolume=2.0
        
        

class myEnergyFunction(EnergyFunctionPy):

    def __init__(self,_energyWrapper):
        EnergyFunctionPy.__init__(self)
        self.energyWrapper=_energyWrapper

    def calculateDistance(self, _from, _to):
        distance_squared = 0.0
        for i in xrange(len(_from)):
            distance_squared += (_from[i] - _to[i])**2
        return math.sqrt(distance_squared)

    def changeEnergy(self):
        energy = 0
        energy_penalty = 99999
        
        newCell=self.energyWrapper.getNewCell()
        oldCell=self.energyWrapper.getOldCell()
        myChangePoint = self.energyWrapper.getChangePoint()

        target_radius = 11.17

        if newCell:
            distance = self.calculateDistance(_to = [newCell.xCOM,newCell.yCOM], _from = [myChangePoint.x, myChangePoint.y])
            if distance > target_radius:
                energy += energy_penalty
        if oldCell:
            distance = self.calculateDistance(_to = [oldCell.xCOM,oldCell.yCOM], _from = [myChangePoint.x, myChangePoint.y])
            if distance > target_radius:
                energy -= energy_penalty
                
        return energy   
        
        