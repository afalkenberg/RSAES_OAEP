
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

#include "ShaHash.h"



LargeInteger* ShaHash::hash(LargeInteger* msg)
{


    LargeInteger* tempMsg; 
    
    tempMsg = new LargeInteger(msg->n + 1); 
    
    tempMsg->zahl[0] = 0x80; 
    
    // msg->shift(1);   // alternate 1 
    
    tempMsg->shift(msg->n); // shift the one up // alternate 2 
    
    tempMsg->add(msg); 

    tempMsg->print(); 
    
    cout << endl; 

    

    LargeInteger* res; 
    res = new LargeInteger(20);  

    int K[4]; 
    int H[5]; 
    
    K[0] = 0x5a827999;
    K[1] = 0x6ed9eba1;
    K[2] = 0x8f1bbcdc;
    K[3] = 0xca62c1d6;
    
    
    H[0] = 0x67452301;
    H[1] = 0xefcdab89;
    H[2] = 0x98badcfe;
    H[3] = 0x10325476;
    H[4] = 0xc3d2e1f0;
    
    
    
   
     
    int l = (3+tempMsg->n)/4 + 2; 
    
    int N = (l+15)/16; // should be the same as ceil ( ? ) 
    
    int M[N][16];   // array of integers (32 bit)  
    
    
    
    for (int i=0; i<N; i++)  // for each chunck of 16 words 
    {
        
        for (int j=0; j<16; j++) 
        {
            int ma = 0; 
            int mb = 0; 
            int mc = 0; 
            int md = 0; 
             
            if(i*64+j*4 < tempMsg->n) 
            {   
               ma = tempMsg->zahl[i*64+j*4] << 24;  /// upper << 24 
               
            }
            if(i*64+j*4 +1 < tempMsg->n) 
            {
               mb = tempMsg->zahl[i*64+j*4+1] << 16;  /// next word << 16
            }
            if(i*64+j*4 + 2 < tempMsg->n) 
            {
               mc = tempMsg->zahl[i*64+j*4+2] << 8;  /// <<< 8 
            }
            if(i*64+j*4 + 3 < tempMsg->n) 
            {
               md = tempMsg->zahl[i*64+j*4+3];  /// no shift 
               
            }
            
               
            M[i][j] = ma | mb | mc | md;    
            

            
        } 
    }
    
    
    // add length in bits
    
    M[N-1][14] = 0;      ///((tempMsg->n-1) * 8) >> 32;   
    M[N-1][15] = ((tempMsg->n-1) * 8)  ;  
    
    
    ///
    
    int W[80]; 
    
    int a; 
    int b;
    int c; 
    int d; 
    int e;  
    
    for (int i=0; i<N; i++) 
    {
        // 1 - prepare message schedule 'W'
        for (int t=0;  t<16; t++) 
        {   
           W[t] = M[i][t];
        }
        
        for (int t=16; t<80; t++) 
        {
            W[t] = rotate(W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16], 1);            
        }
    
    
    
        a = H[0]; 
        b = H[1];
        c = H[2]; 
        d = H[3]; 
        e = H[4];
    
    
       for (int ct=0; ct<80; ct++) 
        {
            int s = ct/20; // seq for blocks of 'f' functions and 'K' constants
            
            int T = (rotate(a,5) + shaFunction(s,b,c,d) + e + K[s] + W[ct]) & 0xffffffff;
            e = d;
            d = c;
            c = rotate(b, 30);
            b = a;
            a = T;
        } 
    
        H[0] = (H[0]+a) ;
        H[1] = (H[1]+b) ;
        H[2] = (H[2]+c) ;
        H[3] = (H[3]+d) ;
        H[4] = (H[4]+e) ;
    }
    
 
    
    for(int i = 0; i < 5; i++)
    {
       res->zahl[19 - 4*i] = (H[i] & 0xFF000000) >> 24; 
       res->zahl[18 - 4*i] = (H[i] & 0x00FF0000) >> 16; 
       res->zahl[17 - 4*i] = (H[i] & 0x0000FF00) >> 8; 
       res->zahl[16 - 4*i] = (H[i] & 0x000000FF); 
    
    }
    
    return res;     
    
    
}
 




int ShaHash::shaFunction(int s, int x, int y, int z)
{
  
   int res; 
   
   switch (s) 
   {
       
        case 0: res = (x & y) | (~x & z);           // Ch()
                break; 
        case 1: res =   x ^ y  ^  z;                 // Parity()
                break;  
        case 2: res = (x & y) | (x & z) | (y & z);  // Maj()
                break; 
        case 3: res = x ^ y  ^  z;                 // Parity()
                break; 
        default:
               res = 0; 
               break;
   };
  
   return res; 
} 


int ShaHash::rotate(int x, int n)
{
    int res; 
    res = ((x<<n) & 0xFFFFFFFF) | ((x &0xFFFFFFFF)   >>(32-n)); 
    
    return res; 
}



