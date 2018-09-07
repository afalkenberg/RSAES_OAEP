
//  EmeOaep class for RSAES_OAEP

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

#include "EmeOaep.h"

LargeInteger* EmeOaep::encode(LargeInteger* M, LargeInteger* P, int emLen)
{

   LargeInteger* PS; 
   LargeInteger* pHash; 
   LargeInteger* DB; 
   LargeInteger* dbMask; 
   LargeInteger* seedMask; 
   LargeInteger* EM; 
   EM = new LargeInteger(); 
   
   LargeIntegerLogic* maskedDB; 
   
   DB = new LargeInteger(); 
   
   LargeInteger* ONE; 
   ONE = new LargeInteger(); 
   ONE->zahl[0] = 1; 
   
   LargeInteger* seed; // supposed to be random 
   seed = new LargeInteger(); 
   seed->readHex("aafd12f659cae63489b479e5076ddec2f06cb58f");  // 6
    
   
   
   if(M->n <= emLen - 2*msk.hLen - 1)  
   {
       PS = new LargeInteger(emLen - M->n - 2*msk.hLen - 1);  // 3
   
       LargeIntegerLogic* DBpHashConc; 
       DBpHashConc = new LargeIntegerLogic(); 
       
       DBpHashConc = (LargeIntegerLogic*)sha.hash(P);  // 4
       
       DBpHashConc->concat(PS);    //5 
        
       DBpHashConc->concat(ONE);
       
       DBpHashConc->concat(M);
       
       
       //6 see above 
       
       dbMask = msk.maskGenerationFunction(seed, emLen - msk.hLen); // 7  =>107
       
       DBpHashConc->exor(dbMask);  //8  maskedDB
       
       seedMask = msk.maskGenerationFunction(DBpHashConc, msk.hLen); //9 
       
       
       LargeIntegerLogic* maskedSeed; 
       maskedSeed = new LargeIntegerLogic(); 
       maskedSeed = (LargeIntegerLogic*)seed->copyMe(); 
       
       maskedSeed->exor(seedMask);  //10 maskedSeed 
       
       std::cout << " MASKED SEED " << std::endl; 
       
       maskedSeed->print(); 
       
       std::cout << " MASKED SEED END " << std::endl; 
       
       
       maskedSeed->concat(DBpHashConc);  // EM 
        
       EM = maskedSeed->copyMe(); 
     
   } 
   
   return EM; 
   
   
}


        
LargeInteger* EmeOaep::decode(LargeInteger* EM, LargeInteger* P)
{
     
     
     int emLen; 
     int hLen; 
     
     emLen = EM->n; 
     hLen  = msk.hLen; 
     
     LargeInteger* maskedSeed; 
     maskedSeed = new LargeInteger(hLen);
     
     LargeInteger* maskedDB; 
     maskedDB  = new LargeInteger(emLen - hLen); 
     
     LargeInteger* seedMask; 
     seedMask = new LargeInteger(); 
     
     LargeIntegerLogic* seed;   // 5
     
     LargeIntegerLogic* dbMask; //6
     
     LargeIntegerLogic* DBinternal; 
     
     LargeInteger* pHashInt;
     LargeInteger* pHashExt;
      
     
     LargeInteger* M;  // output message ! 
     
     if((emLen < 2*hLen + 1) == false)
     {
         for(int i = 0; i < hLen; i++)  //3
         {
             maskedSeed->zahl[i] = EM->zahl[i  + emLen - hLen]; 
         }
         
         for (int i = hLen; i < emLen; i++)
         {
              maskedDB->zahl[i-hLen] = EM->zahl[i - hLen]; 
         }  
      
         
         
         seedMask = msk.maskGenerationFunction(maskedDB, msk.hLen);  //4
        
         seed = (LargeIntegerLogic*)maskedSeed->copyMe();   //5
         
         seed->exor(seedMask);  
         
         dbMask = (LargeIntegerLogic*)msk.maskGenerationFunction(seed, emLen-hLen); // 6 
         
         DBinternal = (LargeIntegerLogic*)maskedDB->copyMe(); 
      
         DBinternal->exor(dbMask); 
      
         
         pHashInt = (LargeIntegerLogic*)sha.hash(P);
         
         
         std::cout << " DBinternal " << std::endl; 
         DBinternal->print(); 
         std::cout << " DBinternal " << std::endl; 
         
         
         pHashExt = new LargeInteger(pHashInt->n); 
         
         
         for(int i = 0; i < pHashInt->n; i++)
         {   
             pHashExt->zahl[i] = DBinternal->zahl[i + DBinternal->n - pHashInt->n]; 
         }
         
         if(pHashExt->compareEQ(pHashInt))
         {
              std::cout << " HASH CORRECT " << std::endl; 
         } 
         
         // now search for 0 closing 1 
         int ct; 
         ct = DBinternal->n - pHashInt->n - 1; 
         
         while(DBinternal->zahl[ct] == 0)
         {
             ct = ct-1; 
         }
         
         if(DBinternal->zahl[ct] == 1)
         {
             std::cout << " 01 found " << std::endl; 
         }
         
         // generate the rest of the message without 01 // 
         
         
         M = new LargeInteger(ct); 
         
         for(int i = 0; i < ct; i++) 
         {
             M->zahl[i] = DBinternal->zahl[i]; 
         } 
          
         
      }
      
    
  
     return M; 
} 
  


