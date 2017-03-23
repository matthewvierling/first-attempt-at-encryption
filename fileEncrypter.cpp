/*
fileEncrypter - Matthew Vierling - 06/23/2016

this is a VERY simple txt document encrypter. This was written before I had knowledge of encryption libraries or how they worked.

THIS IS NOT A STRONG INCRYPTION. this is something I thought of and wanted to put it into code.

*/

#include<iostream>
#include<string>
#include<vector>
#include<fstream>


using namespace std;

/*
this function gets a string for a code of length 1-8 and returns a string code of length 8
*/
//***********************************************************************************************************************get code
void getCode(string & codeIn){
	
	int length = codeIn.length();
	
	switch(length){
		case 1:
			codeIn = codeIn+"k";
			
		case 2:
			codeIn = codeIn+"A";
			
		case 3:
			codeIn = codeIn+"@";
			
		case 4:
			codeIn = codeIn+"B";
			
		case 5:
			codeIn = codeIn+"e";
			
		case 6:
			codeIn = codeIn+"C";
			
		case 7:
			codeIn = codeIn+"9";
			
		case 8:
			break;
	}
	
	return;
}

/*
recieves a code for encryption and a string to encrypt and return an encrypted string. 
*/
//***********************************************************************************************************************string encrypt
void encryptString(string & code, string & str){//encrypts a single string with simple manipulations
		
		getCode(code);
		
		int a = int(code.at(0));
		int b = int(code.at(1));
		int c = int(code.at(2));
		int d = int(code.at(3));
		int e = int(code.at(4));
		int f = int(code.at(5));
		int g = int(code.at(6));
		int h = int(code.at(7));
		
		int codeTotal = a+b+c+d+e+f+g+h;
		
		vector<int> codeInts;
		codeInts.resize(str.size());
		
		for (int i=0; i<str.size(); ++i){
			
			switch(codeTotal%8){
			
				case 0:
					codeInts[i] = (int(str.at(i))+a)-h;
					break;
					
				case 1:
					codeInts[i] = (int(str.at(i))+b)-g;
					break;
				
				case 2:
					codeInts[i] = (int(str.at(i))+c)-f;
					break;
					
				case 3:
					codeInts[i] = (int(str.at(i))+d)-e;
					break;
				
				case 4:
					codeInts[i] = (int(str.at(i))+a)-e;
					break;
					
				case 5:
					codeInts[i] = (int(str.at(i))+b)-f;
					break;
					
				case 6:
					codeInts[i] = (int(str.at(i))+d)-g;
					break;
					
				case 7:
					codeInts[i] = (int(str.at(i))+e)-h;
					break;
					
				default:
					cout<<"error in string encrypt function"<<endl;
					break;
			}
		}
		
		string newString = "";
		for(int i=0; i<codeInts.size(); ++i){
			
			newString += char(codeInts[i]);
			
		}
		
		std::swap(str, newString);
		
		return;
		
	}
	
	/*
	recieves an encryption code and an encrypted string and unencrypts the string and returns it
	*/
	//***********************************************************************************************************************string decrypt
	void decryptString(string & code, string & encryptedStr){//decrypts a single string with simple manupulations
		
		getCode(code);
		
		int a = int(code.at(0));
		int b = int(code.at(1));
		int c = int(code.at(2));
		int d = int(code.at(3));
		int e = int(code.at(4));
		int f = int(code.at(5));
		int g = int(code.at(6));
		int h = int(code.at(7));
		
		int codeTotal = a+c+b+d+e+f+g+h;
	
		
		vector<int> codeInts;
		codeInts.resize(encryptedStr.size());
		
		for (int i=0; i<encryptedStr.size(); ++i){
			
			switch(codeTotal%8){
			
				case 0:
					codeInts[i] = (int(encryptedStr.at(i))+h)-a;
					break;
					
				case 1:
					codeInts[i] = (int(encryptedStr.at(i))+g)-b;
					break;
				
				case 2:
					codeInts[i] = (int(encryptedStr.at(i))+f)-c;
					break;
					
				case 3:
					codeInts[i] = (int(encryptedStr.at(i))+e)-d;
					break;
				
				case 4:
					codeInts[i] = (int(encryptedStr.at(i))+e)-a;
					break;
					
				case 5:
					codeInts[i] = (int(encryptedStr.at(i))+f)-b;
					break;
					
				case 6:
					codeInts[i] = (int(encryptedStr.at(i))+g)-d;
					break;
					
				case 7:
					codeInts[i] = (int(encryptedStr.at(i))+h)-e;
					break;
					
				default:
					cout<<"error in string decrypt function"<<endl;
					break;
			}
		}
		
		string newString = "";
		for(int i=0; i<codeInts.size(); ++i){
			
			newString += char(codeInts[i]);
			
		}
		
		std::swap(encryptedStr, newString);
		
		return;
		
		
	}
	
	/*
	recieves a string vector and returns the same vector with the strings encrypted.
	*/
	//***********************************************************************************************************************vector encrypt
	void encryptVector(vector<string>  & stringList, string & code){
		
		for (int i=0; i<stringList.size(); ++i){
			encryptString(code, stringList[i]);
		}
		
		return;
	}
	
	/*
	recieves a vector of encrypted strings and decrypts them then retuns the vector
	*/
	//***********************************************************************************************************************vector decrypt
	void decryptVector(vector<string>  & stringList, string & code){
		
		for (int i=0; i<stringList.size(); ++i){
			decryptString(code, stringList[i]);
		}
		
		return;
	}
	
	/*
	recieves the name of the file to open and the encryption code and opens the file reads it and encrypts it. 
	*/
	//***********************************************************************************************************************file encrypt
	void fileEncrypt(string fileName, string & code){
		
		vector<string> stringList; 
		
		fstream theFile;//creates the file stream
		theFile.open(fileName, ios::in);//opens file for reading
		
		if(!theFile.is_open()){//check for error opening file
	
			cout<<"code 1: error opening file"<<endl;
			return;
			
		}
		
		int i = 0;
		string line;
			
		while (!theFile.eof()){//reads each line and places the into a vector of strings
			getline(theFile, line);
			stringList.push_back(line);
    		++i;
		}
		
		encryptVector(stringList, code);
		
		theFile.clear();
		theFile.close();
		
	/*	for (int k=0; k<stringList.size(); ++k){//********************prints out encrypted strings
			cout<<stringList[k]<<endl;
		}
	*/
		
		ofstream theFile2(fileName);//opens file for rewriting over
		
		if(!theFile2.is_open()){//check for error opening file
	
			cout<<"code 2: error opening file"<<endl;
			return;
			
		}
		
		i = 0;//resetting i to 0
		
		while(theFile2.is_open()){//writes the incrypted string vector on to the file
			theFile2<<stringList[i]<<"\n";
			++i;
			if(i==stringList.size()-1){
				theFile2.close();
			}
		}
		
    	return;
	}
	
	//***********************************************************************************************************************file decrypt
	void fileDecrypt(string & fileName, string & code){
		
			vector<string> stringList; 
		
		fstream theFile;//creates the file stream
		theFile.open(fileName, ios::in);//opens file for reading
		
		if(!theFile.is_open()){//check for error opening file
	
			cout<<"code 1: error opening file"<<endl;
			return;
			
		}
		
		int i = 0;
		string line;
			
		while (!theFile.eof()){//reads each line and places the into a vector of strings
			getline(theFile, line);
			stringList.push_back(line);
    		++i;
		}
		
		decryptVector(stringList, code);
		
		theFile.clear();
		theFile.close();
		
	/*	for (int k=0; k<stringList.size(); ++k){//********************prints out decrypted strings
			cout<<stringList[k]<<endl;
		}
	*/
		
		ofstream theFile2(fileName);//opens file for rewriting over
		
		if(!theFile2.is_open()){//check for error opening file
	
			cout<<"code 2: error opening file"<<endl;
			return;
			
		}
		
		i = 0;//resetting i to 0
		
		while(theFile2.is_open()){//writes the decrypted string vector on to the file
			theFile2<<stringList[i]<<"\n";
			++i;
			if(i==stringList.size()-1){
				theFile2.close();
			}
		}
		
    	return;
		
	}
	
	/*
	this function test to see if the code entered is of valid length
	*/
	//***********************************************************************************************************************main()
	bool validCode(string & code){
		
		if((code.length()-8)>0||(code.length()-1)<0){
			return true;
		}
		else{
			return false;
		}
		
	}

	//***********************************************************************************************************************main()
int main(void){
	
	string fileName;
	string code;
	int choice;
	
	do{
		
		cout<<"Enter file path and file name for the txt file (enter \\\\ for \\): "<<endl;
		cout<<"e.g. \"C:\\\\Users\\\\Username\\\\Desktop\\\\testfile.txt\""<<endl;
		cin>>fileName;
		cout<<"inter 1 for encrypting or 2 for decryping ( 3 to exit): "<<endl;
		cin>>choice;
		if(choice==3)
			break;
			
		do{	
		
			cout<<"enter a 1-8 character, character code: "<<endl;
			cin>>code;
			
			if(!validCode(code)){
				cout<<"not a valid code. please try another."<<endl;
			}
			
		}while(!validCode(code));
		
		switch(choice){
			case 1:
				fileEncrypt(fileName, code);
				break;
			
			case 2:
				fileDecrypt(fileName, code);
				break;
			
			case 3:
				break;
			
			default:
				cout<<"something went wrong in menu";
				choice = 3;
		}
	}while(choice!=3);
	
	return 0;
}



