
//  MaskGeneration class for RSAES_OAEP

//  Created by Andreas Falkenberg on 4/16/18.
//  Copyright (c) 2018 Andreas Falkenberg. All rights reserved.
//
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include "MaskGeneration.h" 
#include "LargeIntegerLogic.h"

MaskGeneration::MaskGeneration()
{
   hLen = 20; 
} 

LargeInteger* MaskGeneration::maskGenerationFunction(LargeInteger* seed, int len)
{
  
    LargeIntegerLogic* tempT; 
    tempT = new LargeIntegerLogic(); 
    
    int lenMax; 
    lenMax = ((len + hLen-1)/hLen);
    
    for (int i = 0; i < lenMax; i++)
    {
        LargeIntegerLogic* copyOfSeed; 
        
        copyOfSeed = (LargeIntegerLogic*)seed->copyMe(); 
        
        LargeIntegerLogic* iLarge; 
        iLarge = new LargeIntegerLogic(4); 
        iLarge->zahl[0] = i; 
        
        copyOfSeed->concat(iLarge); 
        
        copyOfSeed->flip();  // 
        
        LargeInteger* tempHash; 
        
        tempHash = sha.hash(copyOfSeed); 
        
        tempT->concat(tempHash); 
        
    }
    
    
    LargeInteger* T; 
    
    T = (LargeInteger*)tempT->copyMe();
    
    T->shift(len - T->n); 
    
    return  T;
    
}
   

