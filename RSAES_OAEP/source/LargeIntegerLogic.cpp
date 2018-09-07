
//  LargeIntegerLogic class for RSAES_OAEP

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
//

#include "LargeIntegerLogic.h"


// concat B to the right of this // 

LargeIntegerLogic::LargeIntegerLogic() : LargeInteger()
{
} 

LargeIntegerLogic::LargeIntegerLogic(int s) : LargeInteger(s)
{
} 


void LargeIntegerLogic::concat(LargeInteger* B)
{ 
    
    LargeIntegerLogic* res; 
    
    res = new LargeIntegerLogic(this->n + B->n); 
    
    res->print(); 
    
    for(int i=0; i < this->n; i++)
    {
        res->zahl[i + B->n] = this->zahl[i]; 
    }
    
    for(int i = 0; i < B->n; i++)
    {
       res->zahl[i] = B->zahl[i]; 
    }
    
    res->removeZeros(); 
    
    this->zahl = res->zahl; 
    this->n    = res->n;     


}



void LargeIntegerLogic::flip()
{
  
    for(int i = 0; i < this->n / 2 ; i++)
    {
        int x; 
        x = zahl[i]; 
        zahl[i] = zahl[this->n - 1 - i]; 
        zahl[this->n - 1 - i] = x;
    }
}
 
         
  


void LargeIntegerLogic::exor(LargeInteger* B)
{
    
      int mi;
      int ma;  
      bool maa; 
      maa = false; 
      
      LargeIntegerLogic* res;
      
            
      if(this->n > B->n)   
      { 
          maa = true;      // A has more digits we may have zeros ! 
          mi = B->n;
          ma = this->n;    
            
      }
      else 
      {
          mi = this->n;
          ma = B->n;  
      }   
      
      // give it maximum size // 
      res = new LargeIntegerLogic(ma); 
      
      // lower portion normal exor //         
      for(int i = 0 ; i < mi; i++) 
      {
          res->zahl[i] = this->zahl[i]^B->zahl[i]; 
      } 
      
      
      for(int i = mi; i < ma; i++) 
      {
           if(maa == true) 
           {
               res->zahl[i] = this->zahl[i]; 
           }
           else
           {
               res->zahl[i] = B->zahl[i];     
           }
               
      }  
        
      this->n = res->n; 
      this->zahl = res->zahl; 
         
        
}     
