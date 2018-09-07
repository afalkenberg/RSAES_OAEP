
//  RSClass class for RSAES_OAEP

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


#include "RSClass.h" 


LargeInteger* RSClass::rsaEncode(LargeInteger* N, LargeInteger* E, LargeInteger* M)
{
   
    LargeInteger* C; 
    C = new LargeInteger(); 
    
    LargeInteger* Mcopy; 
    Mcopy = M->copyMe(); 
    
    LargeInteger* Ecopy; 
    Ecopy = E->copyMe(); 
    
    LargeInteger* Ncopy; 
    Ncopy = N->copyMe(); 
    
    C = C->modularExpFast(Mcopy,Ecopy,Ncopy);  

    return C; 
}


LargeInteger* RSClass::rsaDecode(LargeInteger* N, LargeInteger* D, LargeInteger* C)
{
    LargeInteger* M; 
    M = new LargeInteger(); 
    
    LargeInteger* Ccopy; 
    Ccopy = C->copyMe(); 
    
    M = M->modularExpFast(Ccopy, D, N); 
    
    return M; 
}


LargeInteger* RSClass::rsaDecode(LargeInteger* P, 
                                 LargeInteger* Q, 
                                 LargeInteger* dP, 
                                 LargeInteger* dQ, 
                                 LargeInteger* qInv, 
                                 LargeInteger* C)
{
  
   LargeInteger* Ccopy; 
   Ccopy = C->copyMe(); 
 
   
 
   LargeInteger* M1_H; 
   M1_H = new LargeInteger();
    
   LargeInteger* M2; 
   M2 = new LargeInteger();
   
   LargeInteger* H; 
   H = new LargeInteger(); 
   
   M1_H = M1_H->modularExpFast(Ccopy, dP, P);  //2.2
   
   M2 = M2->modularExpFast(C, dQ, Q);      //2.3
   
   M1_H->sub(M2);                       // 2.4  
   
   M1_H->multiply(qInv);               // 2.4  
   
   M1_H->remainder(P);                 // 2.4 
   
   M1_H->multiply(Q);                  //2.5
   
   M2->add(M1_H);                      //2.5
    
   return M2; 
 
 }
 
 

 
  
                                   
                                 
 
    





