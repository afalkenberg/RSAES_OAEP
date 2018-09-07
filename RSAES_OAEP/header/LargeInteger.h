
//  LargeInteger class for RSAES_OAEP

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

#ifndef _LargeInteger_h_
#define _LargeInteger_h_


#include <iostream>
#include <sstream>
#include <fstream>

#include<string> 
#include <vector>

using namespace std; 


class LargeInteger; 

ostream& operator<<(ostream& ost, const LargeInteger& ls);


class LargeInteger
{
 
   public: 

   int base; 
   std::vector<int> zahl; 
   int sign;  // not used yet (?)  
   
   int n;  // size
   
   // construct a large 0 
   LargeInteger(); 

   LargeInteger(int s); 
   
   LargeInteger* copyMe(); 
   
   void add( LargeInteger* B); 
   
  
   void sub( LargeInteger* B); 

   
   
   void multiply(int B); 
              
   void multiply(LargeInteger* B);  
    
   void removeZeros(); 
   
   bool compareEQ(LargeInteger* B);
   
   bool compareLT(LargeInteger* B); 
     


   void shift(int shValue); 
   
   void divide(LargeInteger* B); 
      
   void remainder(LargeInteger* B); 
   
   LargeInteger* modularExponentiation(LargeInteger* INP, LargeInteger* E, LargeInteger* N);
   LargeInteger* modularExpFast(LargeInteger* mBase, LargeInteger* exponent, LargeInteger* modulus); 
   
   std::string return_a_string(); 
   
   void print(); 
   
   int checkHex(char x); 
   
   void readHex(std::string inp); 
   
   LargeInteger* readString(std::string inp); 
   
   friend ostream& operator<<(ostream&, const LargeInteger&);   
   
   
};






#endif
