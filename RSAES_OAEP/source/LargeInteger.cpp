
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


#include "LargeInteger.h"

  
   // construct a large 0 
   LargeInteger::LargeInteger()
   {
       this->base = 256;  
       this->n  =  1;  
       // zahl = new int[n];  
       this->zahl.push_back(0); 
       // std::cout << "test" << std::endl; 
   }
   
   
   LargeInteger::LargeInteger(int s)
   {
       base = 256;  
       n = s;  
       
       for(int i=0; i<n; i++)
       {
          this->zahl.push_back(0); 
       }  
   }
   
   
   LargeInteger* LargeInteger::copyMe()
   {
       LargeInteger *temp; 
         
       temp = new LargeInteger(this->n); 
       
       for(int i = 0; i < this->n; i++) 
       {
           temp->zahl[i] = this->zahl[i]; 
       }
       
       return temp; 
   }
   
   
   
   void LargeInteger::add(LargeInteger* B)
   {
           
      int	i, carry, sum;
	    carry = 0;

      int mi;
      int ma;  
      bool maa; 
      maa = false; 
      
      if(this->n > B->n) 
      { 
          maa = true; // A has more digits 
          mi = B->n;
          ma = this->n;
            
      }
      else 
      {
          mi = this->n;
          ma = B->n;  
      }   
        
      // make a temp LargeInterger first 
      
      this->zahl.resize(ma + 1); 
      this->n = ma + 1; 
      
      
      // LargeInteger *temp = new LargeInteger(ma + 1);   
             
      // check carry // 
	    for (int i = 0; i < ma; i++) 
	    {

        if(i < mi)
        { 
		       sum = this->zahl[i] + B->zahl[i] + carry;

     
		       if (sum >= base) 
		       {
			        carry = 1;
			        sum -= base;
		       } 
		       else
           {
			        carry = 0;
           } 
        
		       this->zahl[i] = sum;
	      }

        else 
        { 
            if(maa == true) 
            { 
                sum =  this->zahl[i] + carry; 
            } 
            else 
            {
                sum = B->zahl[i] + carry; 
               
            } 
            
            if (sum >= base) 
		        {
			         carry = 1;
			         sum -= base;
		        } 
		        else
            {
			         carry = 0;
            }  
        
            
		        this->zahl[i] = sum;
		           
		          
        } 
      
    }   // end for 
          
        // last one 
    
        
    this->zahl[ma] = carry;  
    
        
    this->removeZeros();    
    
   // this->n    = temp->n; 
   // this->zahl = temp->zahl; 
    
    
   }
   
   
   
   // this one assumes that B is smaller than A for now 
   // since we will support negative numbers later !! 

   void LargeInteger::sub( LargeInteger* B)
   {
           
    int	i, carry, sum;
	  carry = 0;

    int mi;
    int ma;  
    bool maa; 
    maa = false; 
      
    // LargeInteger *temp; 
    // temp = new LargeInteger(); 
      
      
    if(this->compareLT(B) == false)
      
    {
      
      if(this->n > B->n) 
      { 
          maa = true; 
          mi = B->n;
          ma = this->n;
            
      }
      else 
      {
           
          mi = this->n;
          ma = B->n;  
      }   
        
      // make a temp LargeInterger first 
      
      
      /// temp = new LargeInteger(ma + 1);   
     
      this->zahl.resize(ma+1);  
             
      // check carry // 
	    for (int i = 0; i < ma; i++) 
	    {

        if(i < mi)
        { 
		       sum = this->zahl[i] - B->zahl[i] - carry;

     
		       if (sum < 0)  
		       {
			        carry = 1;
			        sum += base;
		       } 
		       else
           {
			        carry = 0;
           } 
        
		       this->zahl[i] = sum;       
	      }

        else 
        { 
            if(maa == true) 
            { 
                sum =  this->zahl[i] - carry; 
            } 
            else 
            {
                sum = -B->zahl[i] - carry; 
            } 
            if (sum < 0) 
		        {
			         carry = 1;
			         sum += base;
		        } 
		        else
            {
			         carry = 0;
            }  
        
		        this->zahl[i] = sum;
        } 
      
    }   // end for 
          
        // last one 
        
    this->zahl[ma] = carry;       
    
    this->removeZeros(); 
    
    
   } // en d if 
  
    
    
  }



   
   
   void LargeInteger::multiply(int B) 
   {
       // replace all A with this 
       int ma; 
       ma = this->n; 
       
       int res; 
       int carry; 
       
       // we add one more digit (8 bit)
       LargeInteger *temp = new LargeInteger(ma + 1);
   
       res   = 0; 
       carry = 0;  
   
       for(int i = 0; i < ma; i++) 
       {
           res = this->zahl[i] * B + carry; 
                      
           if(res >=base) 
           {   
               
               carry = res / base; 
               res   = res % base; 
           } 
           else
           {
               carry = 0; 
           }     
           

           temp->zahl[i] = res; 
       } 
       
       
       
       // handle last one 
       if(carry == 0) 
       {
           temp->n = ma; 
       }
       else
       {
           
           temp->zahl[ma] = carry;   
       }     
       
       
       temp->removeZeros(); 
       
       
       this->zahl = temp->zahl; 
       this->n    = temp->n; 
       
   }   
       
        
   void LargeInteger::multiply(LargeInteger* B) 
   {
    
       LargeInteger* temp; 
       temp = new LargeInteger(); 

       LargeInteger* res; 
       res = new LargeInteger(); 

       
       
       for(int i = B->n - 1; i >= 0; i--)
       {
           res->multiply(base); 
           temp = this->copyMe(); 
           temp->multiply(B->zahl[i]);
           res->add(temp);  
       }    
       
       
       res->removeZeros(); 
       
       
       this->n    = res->n; 
       this->zahl = res->zahl; 
       
   }
    
   
   void LargeInteger::removeZeros()
   {
       int newN; 
       newN = 1; 
   
       
       for(int i = 1; i < this->n ; i++)
       {
          
          if(this->zahl[i] != 0)
          {
              newN = i+1;        
          } 
       }
       
       this->n = newN;  
       
       for(int i = 0; i < this->n - newN; i++)
       {
           this->zahl.pop_back();  
       }
       
       
       
   } 
   
   bool LargeInteger::compareEQ(LargeInteger* B)  // was A
   {
      
      int mi;
      int ma;  
      bool maa; 
      maa = false; 
            
      if(this->n > B->n)   //switch A -> this 
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
      
      bool  eqval; 
      eqval = true; 
        
      for(int i = ma - 1; i >= 0; i--) 
      {
          int aval; 
          int bval; 
          aval = 0; 
          bval = 0; 
          
          
        
          if(maa == true) 
          {
              aval = this->zahl[i]; 
              if(i < mi) 
              {
                  bval = B->zahl[i]; 
              } 
              else 
              {
                  bval = 0; 
              }                    
          } 
          else  // maa == false 
          {
              bval = B->zahl[i]; 
              if(i < mi) 
              {
                  aval = this->zahl[i]; 
              }
              else
              {
                  aval = 0; 
              } 
          } 
          
          
          if(aval != bval) 
          {
              eqval = false; 
          }              
            
      }   
      
      return eqval; 
       
   }    
   

   bool LargeInteger::compareLT(LargeInteger* B)
   {
      
      int mi;
      int ma;  
      bool maa; 
      maa = false; 
            
      if(this->n > B->n)  // was A now use this instead
      { 
          maa = true; // A has more digits we may have zeros ! 
          mi = B->n;
          ma = this->n;
            
      }
      else 
      {
          mi = this->n;
          ma = B->n;  
      }   
      
      bool   ltval; 
      bool   gtval; 
      ltval = false; 
      gtval = false; 
      
        
      for(int i = ma - 1; i >= 0; i--) 
      {
          int aval; 
          int bval; 
          aval = 0; 
          bval = 0; 
          
          
        
          if(maa == true) 
          {
              aval = this->zahl[i]; 
              if(i < mi) 
              {
                  bval = B->zahl[i]; 
              } 
              else 
              {
                  bval = 0; 
              }                    
          } 
          else  // maa == false 
          {
              bval = B->zahl[i]; 
              if(i < mi) 
              {
                  aval = this->zahl[i]; 
              }
              else
              {
                  aval = 0; 
              } 
          } 
          
           
          if((aval < bval) && (gtval == false)) 
          { 
              
              ltval = true; 
          } 
          if((aval > bval) && (ltval == false)) 
          {
              gtval = true; 
          } 
          
            
      }   
      
      return ltval; 
       
   }  


   void LargeInteger::shift(int shValue)
   {
       // positive shValue shift up neg shift down // pad with 0
       // word shift 
	 
       LargeInteger* res; 
       
       int sv; 
       sv = this->n + shValue; 
       if(sv <= 0) 
       {
          sv = 1; 
       }  
       
       res = new LargeInteger(sv); 
       
       for (int i = 0; i < this->n; i++) 
       {
           if(i + shValue >=0) 
           {
              res->zahl[i + shValue] = this->zahl[i]; 
           }  
       } 
       
       
       res->removeZeros();  
       
       this->n = res->n; 
       this->zahl = res->zahl; 
       
   }      
   
    
   
   void LargeInteger::divide(LargeInteger* B)
   {
      
      LargeInteger* res; 
      
      LargeInteger* intA; 
      LargeInteger* intB;      
      
      LargeInteger* one; 
      one = new LargeInteger(1); 
      one->zahl[0] = 1; 
      
      
      res = new LargeInteger(); 
      
      if(this->compareLT(B) == false)
      {
          intA = this->copyMe(); 
          intB = B->copyMe(); 
        
          intA->removeZeros();  
          intB->removeZeros();  // we know that B is less or equal to A 
          
          // shift B up to match A  
           
          int diff; 
          diff = intA->n - intB->n; 
          
          
          for(int i = 0; i < diff; i++)
          {
              intB->multiply(256); 
          } 
          
          // now comes the calculation : 
          
          for(int i = 0; i <= diff; i++)
          {
              res->shift(1); // shift result up again before loop not after 
              
              while((intB->compareLT(intA)) || (intB->compareEQ(intA)))
              {
                  res->add(one);  
                  intA->sub(intB); 
              } 
              
              intB->shift(-1); // shift divider down 
                      
          } 
          
        
      }
      
     
      res->removeZeros(); 
      
      this->zahl = res->zahl; 
      this->n    = res->n; 
   
   
   }
   
      
   
   void LargeInteger::remainder(LargeInteger* B)
   {
      
      LargeInteger* res; 
      
      LargeInteger* intA; 
      LargeInteger* intB;      
      
      LargeInteger* one; 
      one = new LargeInteger(1); 
      one->zahl[0] = 1; 
      
      
      res = new LargeInteger(); 
      
      
      if(this->compareLT(B) == false)
      {
          
        
          intA = this->copyMe();  
          intB = B->copyMe();  // we know that B is less or equal to A 
          
          intA->removeZeros(); 
          intB->removeZeros(); 
          
          // shift B up to match A  
          
          int diff; 
          diff = intA->n - intB->n; 
          
          for(int i = 0; i < diff; i++)
          {

              intB->multiply(256); // left shift based number of bytes on each side 
              
          } 
          
          // now comes the calculation : 
          
          for(int i = 0; i <= diff; i++)
          {
              res->shift(1); // shift result up again before loop not after 
              
              while((intB->compareLT(intA)) || (intB->compareEQ(intA)))
              {
                  res->add(one);  
                  intA->sub(intB); 
                  
              } 
              
              intB->shift(-1); // shift divider down 
                      
          }  
        
      }
      else
      {
          intA = this->copyMe();
      }  
      
    
      
      intA->removeZeros(); 
      
      
      this->n = intA->n; 
      this->zahl = intA->zahl;
   
   
   }
   
   
   LargeInteger* LargeInteger::modularExponentiation(LargeInteger* INP, LargeInteger* E, LargeInteger* N)
   {    /// == INP^E % M 
        
       // define a 0 
       // define a 1 
       // define a 2
       
       LargeInteger* ZERO;
       ZERO = new LargeInteger(); 
       
       LargeInteger* ONE; 
       ONE = new LargeInteger(); 
       ONE->zahl[0] = 1; 
       
       LargeInteger* TWO; 
       TWO = new LargeInteger(); 
       TWO->zahl[0] = 2;        
       
       /// set res := 1 
       
       LargeInteger* res; 
       res = new LargeInteger(); 
       res->zahl[0] = 1; 
     
       
       LargeInteger* tempBase; 
       tempBase = new LargeInteger(); 
       
       LargeInteger* ePrime; 
       ePrime = new LargeInteger(); 
       ePrime->zahl[0] = 0; 
       
       while(ePrime->compareLT(E))   
       {
           
           res->multiply(INP); 
                                  
           res->remainder(N); 
          
           ePrime->add(ONE); 

       }      
       
       
       
       return res; 
        
       
   }     
   
   
   LargeInteger* LargeInteger::modularExpFast(LargeInteger* mBase, LargeInteger* exponent, LargeInteger* modulus)
   {
       LargeInteger* ZERO; 
       ZERO = new LargeInteger(); 
    
       LargeInteger* ONE; 
       ONE = new LargeInteger(); 
       ONE->zahl[0] = 1; 
    
       LargeInteger* TWO; 
       TWO = new LargeInteger(); 
       TWO->zahl[0] = 2; 


       LargeInteger* result; 
       result = new LargeInteger(); 
       result->zahl[0] = 1; 
       
       mBase->remainder(modulus);   
       
       
       while(exponent->compareEQ(ZERO) == false)  // exponent > 0 
       {

           if((exponent->zahl[0] & 1) == 1)   // if (exponent mod 2 == 1)
           {
               
               result->multiply(mBase);     //  result := (result * base) mod modulus
               
               result->remainder(modulus); 
               
           }
           
           
           exponent->divide(TWO);   // exponent := exponent >> 1
                      
           LargeInteger* newBase; 
           newBase = mBase->copyMe(); 
           mBase->multiply(newBase); 
           mBase->remainder(modulus); 
       }    
           
       return result;     
   }
   
   
   std::string LargeInteger::return_a_string()
   {
	   
       std::ostringstream ss;
      
	   
       std::cout << "XX "; 
       for(int i = n - 1 ; i >= 0; i--) 
       {
		   if(this->zahl[i] <=9) 
		   {
			    ss  << "0" << std::hex << +this->zahl[i] << " "; 
		   }
		   else
		   {	   
                ss  << std::hex << +this->zahl[i] << " "; 
		   }
       }
       
       return ss.str() ; 
   } 
  
  
   
   void LargeInteger::print()
   {
       std::cout << "XX "; 
       for(int i = n - 1 ; i >= 0; i--) 
       {
          if(this->zahl[i] <=9) 
		   {
			    std::cout  << "0" << std::hex << +this->zahl[i] << " "; 
		   }
		   else
		   {	   
                std::cout  << std::hex << +this->zahl[i] << " "; 
		   }
       }
       
           
   } 
  
   
   
   int LargeInteger::checkHex(char x)
   { 
        // check hex // 
        int val; 
        val = x; 
        
        
            if(val >= '0' && val <= '9') 
            {
                val = val - '0';
            } 
            else
            if(val >= 'a' && val <= 'f') 
            {
                val = val - 'a' + 10; 
            } 
            else
            if(val >= 'A' && val <= 'F')
            {
                val = val - 'A' + 10;
            }
        return val; 
   } 
    
    
   
   void LargeInteger::readHex(std::string inp)
   {
        
        int s; 
        s = inp.size(); 
                
        LargeInteger* temp; 
        if(s%2 == 1) 
        {
            temp = new LargeInteger(1 + (s / 2));  
            
            // the highest number : 
            int val; 
            
            val = checkHex(inp[0]); 
           
            
            // put it into the large number 
            
            temp->zahl[s/2] = val; 
            
            
            
            // now the rest [1][2] is a number [3][4] ...  
            for (int i = 1; i <= s/2; i++) 
            {
                  
                val    = 16 * checkHex(inp[2*i - 1])  ;  // start with 1, 3, 5 ...  
                val    +=  checkHex(inp[2*i]);              // 2, 4, 6 ...     
                
                temp->zahl[s/2 - i] = val;   
            } 
        }
        else
        {
            temp = new LargeInteger(s / 2); 
            int val; 
            
            // now the rest [1][2] is a number [3][4] ...  
            for (int i = 0; i < s/2; i++) 
            {
                 
                val    = 16 * checkHex(inp[2*i])  ;  // start with 0, 2, 4 ...  
                val +=  checkHex(inp[2*i + 1]);              // 1, 3, 5 ...     
                
                temp->zahl[s/2 - (i + 1)] = val;  
            } 
            
            
        }
        
        
        this->n = temp->n; 
        this->zahl = temp->zahl; 
        
            
   }
   
   
   LargeInteger* LargeInteger::readString(std::string inp)
   {
    
       LargeInteger* temp; 
       temp = new LargeInteger(inp.size()); 
       
       
       for (int i = 0; i < inp.size(); i++)
       {
           temp->zahl[i] = inp[i]; 
       }
       
       return temp; 
   }
       
       
    
ostream& operator<<(ostream& ost, const LargeInteger& lint)
{
        
       ost << "XX "; 
       for(int i = lint.n - 1 ; i >= 0; i--) 
       {
           ost  << std::hex << lint.zahl[i] << " "; 
       }
   
   
   return ost;
}

