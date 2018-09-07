

//  main() example for RSAES_OAEP

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


#include <iostream> 
#include <vector> 
#include "LargeInteger.h" 
#include "LargeIntegerLogic.h"
#include "RSClass.h" 
#include "ShaHash.h"
#include "MaskGeneration.h"
#include "EmeOaep.h"

#include <ctime>


int main()
{
  
    std::time_t inp1;  
    std::time_t result = std::time(&inp1);
    std::cout << std::asctime(std::localtime(&result))
              << result << " Start " << std::endl;
    
  
    // the following large integer contains the message //
    LargeInteger* M; 
    M = new LargeInteger(); 
    M->readHex("d436e99569fd32a7c8a05bbc90d32c49");  // 
    
   // M->readHex("636261"); 
    
   // LargeInteger* DURCH; 
   // DURCH = new LargeInteger(); 
   // DURCH->readHex("0c97fb1f027f"); 

   // cout << " ------ " << endl; 
    
   // M->remainder(DURCH);  
    
  //  cout << M << endl; 
    
  //  cout << " ------ " << endl; 
    
    LargeInteger* SG; // seed 
    SG = new LargeInteger(); 
    SG->readHex("aafd12f659cae63489b479e5076ddec2f06cb58f"); 
    
    
    LargeInteger* EM; 
    EM = new LargeInteger(); 
    // EM->readHex("eb7a19ace9e3006350e329504b45e2ca82310b26dcd87d5c68f1eea8f55267c31b2e8bb4251f84d7e0b2c04626f5aff93edcfb25c9c2b3ff8ae10e839a2ddb4cdcfe4ff47728b4a1b7c1362baad29ab48d2869d5024121435811591be392f982fb3e87d095aeb40448db972f3ac14f7bc275195281ce32d2f1b76d4d353e2d");

    
    LargeInteger* Pseed; 
    Pseed = new LargeInteger(); 
    Pseed->readHex(""); 
    
    LargeInteger* Pprime; 
    Pprime = new LargeInteger(); 
    Pprime->readHex("eecfae81b1b9b3c908810b10a1b5600199eb9f44aef4fda493b81a9e3d84f632124ef0236e5d1e3b7e28fae7aa040a2d5b252176459d1f397541ba2a58fb6599"); 


    LargeInteger* Q; 
    Q = new LargeInteger(); 
    Q->readHex("c97fb1f027f453f6341233eaaad1d9353f6c42d08866b1d05a0f2035028b9d869840b41666b42e92ea0da3b43204b5cfce3352524d0416a5a441e700af461503"); 
    
    LargeInteger* dP; 
    dP = new LargeInteger(); 
    dP->readHex("54494ca63eba0337e4e24023fcd69a5aeb07dddc0183a4d0ac9b54b051f2b13ed9490975eab77414ff59c1f7692e9a2e202b38fc910a474174adc93c1f67c981"); 
    
    // dP->readHex("54494ca63eb"); 
    
    LargeInteger* dQ; 
    dQ = new LargeInteger(); 
    dQ->readHex("471e0290ff0af0750351b7f878864ca961adbd3a8a7e991c5c0556a94c3146a7f9803f8f6f8ae342e931fd8ae47a220d1b99a495849807fe39f9245a9836da3d"); 

    // dQ->readHex("471e0290ff0"); 

    LargeInteger* qInv; 
    qInv = new LargeInteger(); 
    qInv->readHex("b06c4fdabb6301198d265bdbae9423b380f271f73453885093077fcd39e2119fc98632154f5883b167a967bf402b4e9e2e0f9656e698ea3666edfb25798039f7"); 
    
    // qInv->readHex("b06c4fdabb6"); 
    
    
    LargeInteger* C; 
    C = new LargeInteger(); 
    // C->readHex("1253e04dc0a5397bb44a7ab87e9bf2a039a33d1e996fc82a94ccd30074c95df763722017069e5268da5d1c0b4f872cf653c11df82314a67968dfeae28def04bb6d84b1c31d654a1970e5783bd6eb96a024c2ca2f4a90fe9f2ef5c9c140e5bb48da9536ad8700c84fc9130adea74e558d51a74ddf85d8b50de96838d6063e0955"); 
    
    
    // key // 
    LargeInteger* N; 
    N = new LargeInteger(); 
    N->readHex("bbf82f090682ce9c2338ac2b9da871f7368d07eed41043a440d6b6f07454f51fb8dfbaaf035c02ab61ea48ceeb6fcd4876ed520d60e1ec4619719d8a5b8b807fafb8e0a3dfc737723ee6b4b7d93a2584ee6a649d060953748834b2454598394ee0aab12d7b61a51f527a9a41f6c1687fe2537298ca2a8f5946f8e5fd091dbdcb"); //900AB9F6
    
    
    // exponent //
    LargeInteger* E; 
    E = new LargeInteger(); 
    E->readHex("11");
    
    
    EmeOaep eme; 


    LargeInteger* R;
    R = new LargeInteger();     
    
    R = eme.encode(M, Pseed, 127); 
    
    
    std::cout << " - - - - - - -- "  << std::endl ;
    
    // R->print(); 
    
    cout << *R << endl; 
    
    std::cout << " - - - - - - -- "  << std::endl ;
    
    
   // cout << *(eme.decode(R, P)) <<endl ; 
    
  //  LargeIntegerLogic* R;
  //  R = new LargeIntegerLogic();     
  //  R = (LargeIntegerLogic*)M->copyMe(); 
    
    
    
  //  MaskGeneration msk; 
    
    
  //   (msk.maskGenerationFunction(SG, 107))->print();  
     
    
   
    
    
    LargeInteger* RES; 
    
    
    RSClass EnDecoder; 
    
    std::cout << "ENCODE " << std::endl; 
    
    C = EnDecoder.rsaEncode(N, E, R); 
    
    C->print(); 
    
	cout << "The following should show the same output " << endl;  
	cout << C->return_a_string(); 
	
	
    std::cout << "DECODE " << std::endl; 
    
    
    cout << " Pprime "  <<  *Pprime << endl; 
    cout << " Q "  <<  *Q << endl; 
    cout << " dP "  <<  *dP << endl; 
    cout << " dQ "  <<  *dQ << endl; 
    cout << " qInv "  <<  *qInv << endl; 
    cout << " C "  <<  *C << endl; 
    
    
    
    RES = EnDecoder.rsaDecode(Pprime,Q,dP,dQ,qInv,C); 
  
    RES->print(); 
   
     
   
    
    cout << *(eme.decode(RES, Pseed)) <<endl ; 

    
    
    
    
    result = std::time(&inp1);
    std::cout << std::asctime(std::localtime(&result))
              << result << " Ende\n";
        

    
    return 0; 
    
} 

