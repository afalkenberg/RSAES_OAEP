
//  ShaHash class for RSAES_OAEP

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

#ifndef _ShaHash_h_
#define _ShaHash_h_

#include "LargeInteger.h"

class ShaHash
{

public: 
         
    int shaFunction(int s, int x, int y, int z); 
    
    int rotate(int x, int n); 
    
    LargeInteger* hash(LargeInteger* msg);  
    
    
}; 

     
       
#endif

