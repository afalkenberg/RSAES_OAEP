
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
//

#ifndef _RSClass_h_
#define _RSClass_h_


#include "LargeInteger.h"
 
class RSClass
{

public: 

    LargeInteger* rsaEncode(LargeInteger* N, LargeInteger* E, LargeInteger* M); 
    
    LargeInteger* rsaDecode(LargeInteger* N, LargeInteger* D, LargeInteger* C); 
    
    LargeInteger* rsaDecode(LargeInteger* P, 
                            LargeInteger* Q, 
                            LargeInteger* dP, 
                            LargeInteger* dQ, 
                            LargeInteger* qInv,
                            LargeInteger* C);
                            
                            
};  

                             
#endif    


