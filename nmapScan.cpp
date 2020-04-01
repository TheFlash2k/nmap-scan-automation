#include "termcolor.hpp"
#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>

using namespace std;

void help();
void intro();
void _setIP(string*);
void _setFolder(string*);
void createFolder(string*);
void _nmapScan(string,string);
string GetStdoutFromCommand(string);

int main(int argc, char* argv[]) {
	
	int argumentSize;
	string arguments;
	string ipAddress;
	string folderName;
	string choice;
	char _argumentcheck[50];
	int fCount = 0;
	int iCount = 0;
	
	intro();
	
	if(argc == 1) {
		help();
		return 0;
	}

	arguments = argv[1];
	argumentSize = arguments.size();

	strcpy(_argumentcheck, arguments.c_str());

	if (_argumentcheck[0] || (_argumentcheck[0] && _argumentcheck[1]) == '-') {
		if (_argumentcheck[1] == 'h' || (_argumentcheck[2] == 'h' && _argumentcheck[3] == 'e' && _argumentcheck[4] == 'l' && _argumentcheck[5] == 'p')) {
			cout << termcolor::blue << "\n\t\tHELP MENU:\n" << termcolor::reset;
			help();
			return 0;
		} else if (_argumentcheck[1] == 'i' || (_argumentcheck[2] == 'i' && _argumentcheck[3] == 'p')) {
ip_Setting:
			do {
				iCount++;
				_setIP(&ipAddress);
				cout << termcolor::red << "[*] " << termcolor::reset << "IP entered: " <<  termcolor::green << ipAddress << endl;
				cout << termcolor::yellow << "[?] " <<  termcolor::reset << "Is this IP Address correct and do you want to continue? (Press Y to move forward or N to re-enter ip): " << termcolor::green;
				getline(cin, choice);
				while(choice != "n" && choice != "N" && choice != "y" && choice != "Y") {
					cout << termcolor::red <<  "[!] " << termcolor::reset << "Invalid input. Try again: " << termcolor::green;
					getline(cin, choice);
				}
				if (choice == "n" || choice == "N") {
					cout << endl << endl;
					ipAddress="";
					_setIP(&ipAddress);
				}
			} while(choice != "y" || choice != "y");
			
			if (fCount == 0) {
				goto folder_Setting;
			} else {
				goto Scan;
			}
		} else if (_argumentcheck[1] == 'f' || (_argumentcheck[2] == 'f' && _argumentcheck[3] == 'o' && _argumentcheck[4] == 'l' && _argumentcheck[5] == 'd' && _argumentcheck[6] == 'e' && _argumentcheck[7] == 'r')) { 		
folder_Setting:
			do {
				fCount++;
				_setFolderName(&folderName);
				cout << termcolor::red << "[*] " << termcolor::reset << "Folder Name entered: " << termcolor::green << folderName << endl;
				cout << termcolor::yellow << "[?] " << termcolor::reset << "Is this folder name correct and do you want to continue? (Press Y to move forward or N to re-enter folder name): " << termcolor::green;
				getline(cin, choice);
				cin.clear();
				
				while(choice != "n" && choice != "N" && choice != "y" && choice != "Y") {
					cout << termcolor::red <<  "[!] " << termcolor::reset << "Invalid input. Try again: " << termcolor::green;
					getline(cin, choice);
				}
				
				if (choice == "n" || choice == "N") {
					cout << endl << endl;
					folderName="";
					choice="";
					_setFolderName(&folderName);
				}
			} while((choice != "y") || (choice != "y"));
			createFolder(&folderName);
			
			if (iCount == 0) {
				goto ip_Setting;
			} else {
				goto Scan;
			}
		} else {
			cout << termcolor::red <<"\n[!] " << termcolor::reset << "Invalid Parameters.\n";
			help();
			return 0;
		}
	} else {
		cout << termcolor::red <<"\n[x] " << termcolor::reset << "Invalid Parameters.\n";
		help();
		return 0;
	}

Scan:
	_nmapScan(ipAddress, folderName);

	return 0;
}


void intro() {
	system("clear");
	cout << "*******************************************************************************\n" << termcolor::magenta;
	cout << "\t\t\tNMAP SCAN AUTOMATION SCRIPT.\n\n" << termcolor::blue;
	cout << "\t\t\tWRITTEN BY: "<< termcolor::magenta << "@" << termcolor::red << "The" <<  termcolor::yellow << "Flash" << termcolor::green <<"2k\n\n" << termcolor::blue;
	cout << "\t\t\tGITHUB: " << termcolor::red << "https://github.com/TheFlash2k/\n" << termcolor::reset;
	cout << "*******************************************************************************\n";
}


void help() {
	cout << termcolor::red << "\n[^]"<< termcolor::reset << " Usage \n\n";
	cout << termcolor::blue << "[*]" << termcolor::reset << "./nmapScan -i \n";
	cout << termcolor::blue << "[*]" << termcolor::reset << "./nmapScan -f \n";
	cout << termcolor::blue << "[*]" << termcolor::reset << "./nmapScan -h \n";
	cout << termcolor::cyan << "\n\n[>]" << termcolor::green << " -i | --ip " << termcolor::reset << "- This tag is used to define the ip address.";
	cout << termcolor::red << "\n[*] " << termcolor::reset << "You don't have to define an ip address with the tag. The program will ask you for it.\n";
	cout << termcolor::cyan<< "\n[>] " << termcolor::green << "-f | --folder " << termcolor::reset << "- This tag is used to define the name of the folder in which the files from the scan will be saved.";
	cout << termcolor::red << "\n[*] " << termcolor::reset << "If you use only -f tag, the program will automatically prompt you for ip input.\n";
	cout << termcolor::cyan << "\n[>] " << termcolor::green << "-h | --help " << termcolor::reset << "- This tag displays the help menu i.e. this menu.\n\n\n";
}



void _setIP(string* ip) {
	cout << termcolor::blue << "\n[>] "<< termcolor::reset <<  "Input an ip address that you want to scan: " << termcolor::green;
	getline(cin,*ip);
}	

void _setFolderName(string *folderName) {
	cout << termcolor::cyan << "\n[>] " <<  termcolor::reset << "Input the name that you want to give to the folder to save the output in: "<< termcolor::green;
	cin >> *folderName;
	cin.clear();
	cin.ignore(100,'\n');
}


string GetStdoutFromCommand(string cmd) {

	string data;
	FILE * stream;
	const int max_buffer = 256;
	char buffer[max_buffer];
	cmd.append(" 2>&1");

	stream = popen(cmd.c_str(), "r");
	if (stream) {
		while (!feof(stream))
		if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
	pclose(stream);
    }
    return data;
}

void createFolder(string *folderName) {
	string command = "mkdir ";
	string moving = "cd ";
	string choice;
	string _choice;
	string name;
	string _name = *folderName;
	string user = GetStdoutFromCommand("whoami");

	cout << termcolor::cyan <<"\n[>] " <<  termcolor::reset << "Do you want to create the folder in /tmp/ Directory or in the current working Directory? (1 or 2): "<< termcolor::green;
	getline(cin, choice);
	
	while(choice != "1" && choice != "2") {
		cout << termcolor::red <<  "[!] " << termcolor::reset << "Invalid input. Try again: "<< termcolor::green;
		getline(cin, choice);
	}
	if (choice == "1") {
		name = "/tmp/" + _name;
		*folderName = name;
	} else {
		cout << termcolor::red <<"[*] "<< termcolor::reset << "In order to make the folder in current directory and avoid running into problems, I need root access.\n";
		cout << termcolor::yellow << "[?] " << termcolor::reset << "Do you want to give me that? (Y or N): "<< termcolor::green;
		getline(cin, _choice);
		
		while(_choice != "y" && _choice != "Y" && _choice != "n" && _choice != "N") {
			cout << termcolor::red <<"[!] " << termcolor::reset << "Invalid input. Try again: "<< termcolor::green;
			getline(cin, _choice);
		}
		
		if (_choice == "y" || _choice == "Y") {
			cout << termcolor::yellow  << "Checking if user is already root: ";
			sleep(1);
			
			if(user == "root") {
				cout << termcolor::green << "[^] Already have root access. Moving Forward.\n";
			} else {
				cout << termcolor::white << "User " << termcolor::green  << user << termcolor::white <<" doesn't have root access.\n";
				cout << termcolor::yellow << "Asking for sudo permissions in 1 sec(s):\n";
				sleep(1);
			}
			command = "sudo mkdir ";
		} else {
			cout << termcolor::blue << "[:(] " << termcolor::reset << "So you decided not to trust us with root access. No worries. We'll still continue making the directory in /tmp/.\n";
			sleep(1);
		}
	}
	command.append(*folderName);
	const char* makingDir = command.c_str();
	cout << termcolor::red << "\n";
	system(makingDir);
	moving.append(*folderName);
	const char* movingDir = moving.c_str();
	system(movingDir);
	sleep(1);
	cout << termcolor::yellow << "\n[#] " << termcolor::reset << "Directory [" << termcolor::magenta  << *folderName << termcolor::reset << "] created succesfully." << endl;
	sleep(1);
	cout << termcolor::cyan << "[+] " << termcolor::reset << "Changing Directory to [" << termcolor::magenta << *folderName << termcolor::reset << "]" << endl;
	sleep(3);
	cout << termcolor::green << "[^] " << termcolor::reset << "Changed Directory to [" << termcolor::magenta << *folderName << termcolor::reset << "] succesfully." << endl;	 
	sleep(1);
}


void _nmapScan(string IP,string folderName) {
	string choice;
	string pipeOutput;
	string command = "nmap -sC -sV -oA ";

	command.append(folderName);
	command.append("/ ");
	command.append(IP);
	
	cout << termcolor::yellow << "[?] " << termcolor::reset << "Do you want to pipe do output to a specific file? (Y or N) "<< termcolor::green;
	getline(cin, choice);
	
	while(choice != "n" && choice != "N" && choice != "y" && choice != "Y") {
		cout << termcolor::red <<  "[!] " << termcolor::reset << "Invalid input. Try again: "<< termcolor::green;
		getline(cin, choice);
	}
	if (choice == "Y" || choice == "y") {
		cout << termcolor::red << "[*] " << termcolor::reset <<"Enter the name that you want to give to the file to save the output to: "<< termcolor::green;
		getline(cin, pipeOutput);
		command.append(" | tee ");
		command.append(pipeOutput);
		command.append(".xml");
	}
	cout << termcolor::magenta << "\n\n[^] " << termcolor::reset << "Final Command that is going to be executed is: " << termcolor::cyan << command << termcolor::reset << endl << endl;
	const char* scan = command.c_str();
	sleep(1);
	system(scan);
}
