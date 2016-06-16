#include <iostream>
#include "Disk.h"
#include "Student.h"

using namespace std;

class Level0Debug
{
public:
	static void startDebug(Disk& d,int mode)
	{
		string diskName;
		string ownerName;
		string ownerPwd;
		string path;
		string username;
		string pwd;
		string str;
		int sLevel;
		int a = 0;
		char s[1020];
		Sector sec(a, s);
		switch (mode)
		{
		case 1:
			printStructSize();
			break;
		case 2:
			printDiskInfo(d);
			break;
		case 3:
			cout << "Enter Disk Name:\n";
			cin >> diskName;
			cout << "Enter Owner Name:\n";
			cin >> ownerName;
			cout << "Enter Owner Password:\n";
			cin >> ownerPwd;
			cout << "Creating Disk...\n";
			d.createDisk(diskName, ownerName, ownerPwd);
			cout << "Disk Created!\nWould you like to see the disk details?\n";
			cout << "1. Yeah, Sure!\n";
			cout << "2. No, I'm good\n";
			cin >> a;
			if (a == 1)
				startDebug(d, 2);
			break;
		case 4:
			cout << "Enter File's Path:\n";
			cin >> path;
			cout << "Mounting Disk...\n";
			d.mountDisk(path);
			cout << "Disk Mounted!\nWould you like to see the disk details?\n";
			cout << "1. Yeah, Sure!\n";
			cout << "2. No, I'm good\n";
			cin >> a;
			if (a == 1)
				startDebug(d, 2);
			break;
		case 5:
			cout << "Enter Username:\n";
			cin >> username;
			cout << "Enter Password:\n";
			cin >> pwd;
			cout << "Signing In...\n";
			d.signIn(username, pwd);
			if (d.sign)
				cout << "Signed in successfully!\n";
			break;
		case 6:
			cout << "Signing Out...\n";
			d.signOut();
			if (!d.sign)
				cout << "Signed out successfully!\n";
			break;
		case 7:
			if (!d.sign)
				throw "You must be signed in order to add user!";
			cout << "Enter Username:\n";
			cin >> username;
			cout << "Enter Password:\n";
			cin >> pwd;
			cout << "Choose security level:\n";
			cout << "1. User" << endl;
			if (d.currUser.sLevel >= SLEVEL::Administrator)
				cout << "2. Administrator" << endl;
			if (d.currUser.sLevel >= SLEVEL::Super_User)
				cout << "3. Super User" << endl;
			cin >> sLevel;
			if (sLevel > d.currUser.sLevel)
				throw "You can't create user with higher permission than yours!";
			d.addUser(username, (SLEVEL)sLevel, pwd, d.currUser.sLevel);
			cout << "User Added!\n";
			break;
		case 8:
			if (d.sign)
			{
				cout << "Enter Username to remove:\n";
				cin >> username;
				cout << "Removing...\n";
				d.removeUserSigned(username, d.currUser.sLevel);
				cout << "User removed successfully!\n";
			}
			else
			{
				cout << "Enter Username to remove:\n";
				cin >> username;
				cout << "Enter Password:\n";
				cin >> pwd;
				d.removeUser(username, pwd);
				cout << "User removed successfully!\n";
			}
			break;
		case 9:
			cin.ignore();
			cout << "Enter string to write:\n";
			getline(cin, str);
			strncpy_s(sec.rawData,1020, str.c_str(),1019);
			cout << "Enter sector number:\n";
			cin >> a;
			
			//strncpy_s(s,1020,str.c_str(),1019);
			cout << "Writing...\n";
			d.writeSector(a, &sec);
			cout << "OK!\n";
			break;
		case 10:
			cout << "Enter sector number:\n";
			cin >> a;
			cout << "Reading...\n";
			d.readSector(a, &sec);
			cout << "Sector Content:\n";
			cout << sec.rawData << endl;
			break;
		case 11:
			cout << "Unmounting disk...\n";
			d.unmountDisk();
			if (!d.mounted)
				cout << "Unmounted successfull!\n";
			break;
		default:
			break;
		}

	}
	static void printStructSize()
	{
		cout << "start" << endl;
		cout << "Size Of Disk -->" << sizeof(Disk) << endl;
		cout << "Size Of Sector -->" << sizeof(Sector) << endl;
		cout << "Size Of VolumeHeader -->" << sizeof(VHD) << endl;
		cout << "Size Of DAT -->" << sizeof(DAT) << endl;
		cout << "Size Of DirEntry -->" << sizeof(DirEntry) << endl;
		cout << "Size Of SectorDir -->" << sizeof(SectorDir) << endl;
		cout << "Size Of FileHeader -->" << sizeof(FileHeader) << endl;
		cout << "Size Of usersSec -->" << sizeof(UsersSec) << endl;
		cout << "Size Of RootDir -->" << sizeof(RootDir) << endl;
	}
	static void printDiskInfo(Disk& d)
	{
		VHD* vh = &d.vhd;

		cout << "	disk name:        " << vh->diskName << endl;
		cout << "	Owner Name:       " << vh->diskOwner << endl;
		cout << "	Mounted:          " << d.mounted << endl;
		cout << "	prodDate:         " << vh->prodDate << endl;
		cout << "	formatDate:       " << vh->formatDate << endl;
		cout << "	isFormated:       " << vh->isFormatted << endl;
		cout << "	Users Info:\n";
		for (int i = 0; i < d.users.numOfUsers; i++)
			cout << "\t" << d.users.users[i].name << "\t" << d.users.users[i].password << "\t" << d.users.users[i].sLevel << endl;
		cout << "	Signed:           " << d.sign << endl;
		cout << "	currUser:         " << d.currUser.name << "\t" << d.currUser.password << "\t" << d.currUser.sLevel << endl;
		cout << "	ClusQty:          " << vh->ClusQty << endl;
		cout << "	addrDataStart:    " << vh->addrDataStart << endl;
		cout << "	dataClusQty:      " << vh->dataClusQty << endl;
		cout << "	addrDAT:          " << vh->addrDAT << endl;
		cout << "	addrRootDir:      " << vh->addrRootDir << endl;
		cout << "	addrUserSec:      " << vh->addrUserSec << endl;
		cout << "	addrDATcpy:       " << vh->addrDATcpy << endl;
		cout << "	addrRootDirCpy:   " << vh->addrRootDirCpy << endl << endl;
	}
	static void welcomeDebugLevel0(Disk& d)
	{
		int a;
		cout << "Welcome to Level 0 Debugging Mode!\nWhat would you like to do?\n";
		cout << "1. See structs Details\n";
		cout << "2. See disk Details\n";
		cout << "3. Create Disk\n";
		cout << "4. Mount Disk\n";
		cout << "5. Sign In\n";
		cout << "6. Sign Out\n";
		cout << "7. Add User\n";
		cout << "8. Remove User\n";
		cout << "9. Write Sector\n";
		cout << "10. Read Sector\n";
		cout << "11. Unmount Disk\n";
		cout << "12. Go back do debugging Level1\n";
		cin >> a;
		while (a!=12)
		{
			if (a > 12 || a < 1)
			{
				cout << "Illegal Command!\n";
			}
			else
			{
				try {
					startDebug(d, a);
				}
				catch (const char* str){
					cout << str << endl;
				}
			}
			cout << "Welcome to Level 0 Debugging Mode!\nWhat would you like to do?\n";
			cout << "1. See structs Details\n";
			cout << "2. See disk Details\n";
			cout << "3. Create Disk\n";
			cout << "4. Mount Disk\n";
			cout << "5. Sign In\n";
			cout << "6. Sign Out\n";
			cout << "7. Add User\n";
			cout << "8. Remove User\n";
			cout << "9. Write Sector\n";
			cout << "10. Read Sector\n";
			cout << "11. Unmount Disk\n";
			cout << "12. Go back do debugging Level1\n";
			cin >> a;
		}
	}

};

class Level1Debug
{
public:
	static void startDebug(Disk& d, int mode)
	{
		DATtype fat;
		int algo;
		int sectors;
		switch (mode)
		{
		case 1:
			Level0Debug::welcomeDebugLevel0(d);
			break;
		case 2:
			Level0Debug::printDiskInfo(d);
			break;
		case 3:
			d.format();
			break;
		case 4:
			cout << "Starting Test...\n";
			setDatTest(d);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(Before)"<< endl;	
			d.firstFit(fat, 2,6);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(After)" << endl;
			cout << "Fat:\t";
			for (int i = 6; i < 22; i++)
				cout << fat[i] << " ";
			cout << endl;
			cout << "Test Finished!\n";
			break;
		case 5:
			cout << "Starting Test...\n";
			setDatTest(d);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(Before)" << endl;
			d.bestFit(fat, 2, 6);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(After)" << endl;
			cout << "Fat:\t";
			for (int i = 6; i < 22; i++)
				cout << fat[i] << " ";
			cout << endl;
			cout << "Test Finished!\n";
			break;
		case 6:
			cout << "Starting Test...\n";
			setDatTest(d);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(Before)" << endl;
			d.worstFit(fat, 2, 6);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(After)" << endl;
			cout << "Fat:\t";
			for (int i = 6; i < 22; i++)
				cout << fat[i] << " ";
			cout << endl;
			cout << "Test Finished!\n";
			break;
		case 7:
			cout << "How many sector to allocate?\n";
			cin >> sectors;
			cout << "Choose allocation algorithm:\n";
			cout << "1. First Fit\n";
			cout << "2. Best Fit\n";
			cout << "3. Worse Fit\n";
			cin >> algo;
			cout << "Starting Test...\n";
			setDatTest(d);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(Before)" << endl;
			d.alloc(fat, sectors, algo-1,6);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(After)" << endl;
			cout << "Fat:\t";
			for (int i = 6; i < 22; i++)
				cout << fat[i] << " ";
			cout << endl;
			cout << "Test Finished!\n";
			break;
		case 8:
			cout << "How many sector to extend?\n";
			cin >> sectors;
			cout << "Choose allocation algorithm:\n";
			cout << "1. First Fit\n";
			cout << "2. Best Fit\n";
			cout << "3. Worse Fit\n";
			cin >> algo;
			cout << "Starting Test...\n";
			setDatTest(d);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(Before Allocation)" << endl;
			d.alloc(fat, 3,1,6);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(Before Extention)" << endl;
			cout << "Fat:\t";
			for (int i = 6; i < 22; i++)
				cout << fat[i] << " ";
			cout << "\t(Before Extention)" << endl;
			d.allocExtend(fat, sectors, algo - 1);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(After Extention)" << endl;
			cout << "Fat:\t";
			for (int i = 6; i < 22; i++)
				cout << fat[i] << " ";
			cout << "\t(After Extention)" << endl;
			cout << "Test Finished!\n";
			break;
		case 9:
			cout << "Starting Test...\n";
			setDatTest(d);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(Before Allocation)" << endl;
			d.alloc(fat, 3, 1, 6);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(After Allocation)" << endl;
			cout << "Fat:\t";
			for (int i = 6; i < 22; i++)
				cout << fat[i] << " ";
			cout << "\t" << endl;
			d.dealloc(fat);
			cout << "Dat:\t";
			for (int i = 6; i < 22; i++)
				cout << d.dat.dat[i] << " ";
			cout << "\t(After Deallocation)" << endl;
			cout << "Test Finished!\n";
			break;
		default:
			break;
		}

	}
	static void setDatTest(Disk& d)
	{
		for (int i = 6; i < 1600; i++)
			d.dat.dat[i] = 0;
		d.dat.dat[6] = 0;
		d.dat.dat[7] = 1;
		d.dat.dat[8] = 1;
		d.dat.dat[9] = 1;
		d.dat.dat[10] = 0;
		d.dat.dat[11] = 0;
		d.dat.dat[12] = 0;
		d.dat.dat[13] = 0;
		d.dat.dat[14] = 1;
		d.dat.dat[15] = 1;
		d.dat.dat[16] = 0;
		d.dat.dat[17] = 1;
		d.dat.dat[18] = 1;
		d.dat.dat[19] = 1;
		d.dat.dat[20] = 1;
		d.dat.dat[21] = 0;
		/*for (int i = 6; i < 1600; i++)
			d.dat.dat[i] = 0;
		d.dat.dat[6] = 1;
		d.dat.dat[7] = 0;
		d.dat.dat[8] = 1;
		d.dat.dat[9] = 0;
		d.dat.dat[10] = 1;
		d.dat.dat[11] = 0;
		d.dat.dat[12] = 1;
		d.dat.dat[13] = 0;
		d.dat.dat[14] = 1;
		d.dat.dat[15] = 0;
		d.dat.dat[16] = 1;
		d.dat.dat[17] = 0;
		d.dat.dat[18] = 1;
		d.dat.dat[19] = 0;
		d.dat.dat[20] = 1;
		d.dat.dat[21] = 0;*/

	}
	static void welcomeDebugLevel1(Disk& d)
	{
		int a;
		d.mountDisk(string("Disk1.fms"));
		cout << "Welcome to Level 1 Debugging Mode!\nWhat would you like to do?\n";
		cout << "1. Set Disk (level 0)\n";
		cout << "2. See disk Details\n";
		cout << "3. Format Disk\n";
		cout << "4. Check first fit algorithm\n";
		cout << "5. Check best fit algorithm\n";
		cout << "6. Check worse fit algorithm\n";
		cout << "7. Allocate space\n";
		cout << "8. Extend Allocation\n";
		cout << "9. Deallocate Space\n";
		cout << "10. Exit\n";
		cin >> a;
		while (a != 10)
		{
			if (a > 10 || a < 1)
			{
				cout << "Illegal Command!\n";
			}
			else
			{
				try {
					startDebug(d, a);
				}
				catch (const char* str) {
					cout << str << endl;
				}
			}
			cout << "Welcome to Level 1 Debugging Mode!\nWhat would you like to do?\n";
			cout << "1. Set Disk (level 0)\n";
			cout << "2. See disk Details\n";
			cout << "3. Format Disk\n";
			cout << "4. Check first fit algorithm\n";
			cout << "5. Check best fit algorithm\n";
			cout << "6. Check worse fit algorithm\n";
			cout << "7. Allocate space\n";
			cout << "8. Extend Allocation\n";
			cout << "9. Deallocate Space\n";
			cout << "10. Exit\n";
			cin >> a;
		}
	}
};

class Level2Debug
{
public:
	static void startDebug(Disk& d, int mode)
	{
		string fileName;
		int recSize;
		int recNum;
		int type;
		string keyType;
		int sLevel;
		int keyOffset;
		int keySize;
		int algo;
		int sectors;
		switch (mode)
		{
		case 1:
			Level0Debug::welcomeDebugLevel0(d);
			break;
		case 2:
			Level0Debug::printDiskInfo(d);
			break;
		case 3:
			cout << "Enter file name:\n";
			cin >> fileName;
			cout << "Choose records type:\n";
			cout << "1. Students\n";
			cin >> type;
			cout << "Enter record number:\n";
			cin >> recNum;
			cout << "Choose security level:\n";
			cout << "1. User" << endl;
			if (d.currUser.sLevel >= SLEVEL::Administrator)
				cout << "2. Administrator" << endl;
			if (d.currUser.sLevel >= SLEVEL::Super_User)
				cout << "3. Super User" << endl;
			if (d.currUser.sLevel >= SLEVEL::Owner)
				cout << "4. Owner" << endl;
			cin >> sLevel;
			cout << "Creating file...\n";
			switch (type)
			{
			case(1):
				d.createFile(fileName, string("F"), 88, ceil(((double)recNum / (1020 / 88)))*(1020/88), ceil(((double)recNum / (1020 / 88))) + 1, string("s"), (SLEVEL)sLevel, 0, 10, 0);
				break;
			default:
				throw "You didn't choose a correct record type!";
				break;
			}
			cout << "File created successfully!\n";
			break;
		case 4:
			cout << "Enter file name to delete:\n";
			cin >> fileName;
			cout << "Deleteing file...\n";
			d.delFile(fileName);
			cout << "File deleted!\n";
			break;
		case 5:
			cout << "Enter file name to extend:\n";
			cin >> fileName;
			cout << "How many sectors to extend?:\n";
			cin >> sectors;
			cout << "Extending Disk...\n";
			d.extendFile(fileName, sectors);
			cout << "File extended!\n";
			break;
		case 6:
			printRootDirInfo(d);
			break;
		case 7:
			cout << "formatting...\n";
			d.format();
			cout << "Format Succesfully!\n";
			break;
		case 8:
			cout << "Printing DAT...\n";
			printDAT(d.dat.dat);
			break;
		case 9:
			cout << "Enter file name:\n";
			cin >> fileName;
			printDAT(d.getFat(fileName));
			break;
		default:
			break;
		}

	}
	static void printRootDirInfo(Disk& d)
	{
		cout << "File Name:" << "\t" << "File Owner:" << "\t" << "File Address:" << "\t" << "Creation Date:" << "\t" << "FileSize:" << "\t" << "EOF Record Number:" << "\t" <<"Record Size:" << "\t" << "Record Format:" << "\t" << "Key Offset:" << "\t" << "Key Size:" << "\t" << "Key Type:" << "\t" << "Entry Status:" << "\t" << "Security Level:" << endl;
		for (int i = 0; i < 14; i++)
		{
			cout<<d.rootDir.lsbSector.dirEntry[i];
			cout<<d.rootDir.msbSector.dirEntry[i];
		}

	}
	static void printDAT(DATtype& dat)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j <80; j++)
				cout << dat[i*80 + j] << " ";
			cout << endl;
		}

	}
	static void welcomeDebugLevel2(Disk& d)
	{
		int a;
		/*d.mountDisk(string("Disk1.fms"));
		d.signIn(string("Daniel"), string("1234"));*/
		cout << "Welcome to Level 2 Debugging Mode!\nWhat would you like to do?\n";
		cout << "1. Set Disk (level 0)\n";
		cout << "2. See disk Details\n";
		cout << "3. Create new File\n";
		cout << "4. Delete file\n";
		cout << "5. Extend file\n";
		cout << "6. Print root dir details\n";
		cout << "7. Format Disk\n";
		cout << "8. Print DAT\n";
		cout << "9. Print FAT\n";
		cout << "10. Exit\n";
		cin >> a;
		while (a != 10)
		{
			if (a > 10 || a < 1)
			{
				cout << "Illegal Command!\n";
			}
			else
			{
				try {
					startDebug(d, a);
				}
				catch (const char* str) {
					cout << str << endl;
				}
			}
			cout << "Welcome to Level 2 Debugging Mode!\nWhat would you like to do?\n";
			cout << "1. Set Disk (level 0)\n";
			cout << "2. See disk Details\n";
			cout << "3. Create new File\n";
			cout << "4. Delete file\n";
			cout << "5. Extend file\n";
			cout << "6. See root dir details\n";
			cout << "7. Format Disk\n";
			cout << "8. Print DAT\n";
			cout << "9. Print FAT\n";
			cout << "10. Exit\n";
			cin >> a;
		}
	}
};

class Level3Debug
{
public:
	static void startDebug(Disk& d, FCB& fcb, int mode)
	{
		int rec;
		Student stu;
		string fileName;
		string ID;
		string firstName;
		string lastName;
		string street;
		string city;
		string zip;
		string phone;
		int grade;
		int houseNo;
		switch (mode)
		{
		case 1:
			Level0Debug::welcomeDebugLevel0(d);
			break;
		case 2:
			Level2Debug::welcomeDebugLevel2(d);
			break;
		case 3:
			if (fcb.loaded)
				throw "You must close the file first!";
			cout << "Enter file name:\n";
			cin >> fileName;
			cout << "Opening file...\n";
			fcb = (*d.openFile(fileName, MODE::WR));
			cout << "File opened!\n";
			break;
		case 4:
			if (!fcb.loaded)
				throw "No File is open!";
			cout<< "Enter Student ID:\n";
			cin >> ID;
			for (int i = 0; i < fcb.recInfo.size; i++)
				if (!strcmp(fcb.recInfo.records[i].key, ID.c_str()))
					throw "ID already exist!";
			cout << "Enter first name:\n";
			cin >> firstName;
			cout << "Enter last name:\n";
			cin >> lastName;
			cout << "Enter grade:\n";
			cin >> grade;
			cout << "Enter street:\n";
			cin >> street;
			cout << "Enter house number:\n";
			cin >> houseNo;
			cout << "Enter city:\n";
			cin >> city;
			cout << "Enter zip code:\n";
			cin >> zip;
			cout << "Enter phone number:\n";
			cin >> phone;
			cout << "Writing Record...\n";
			stu = Student(ID, firstName, lastName, grade, street, houseNo, city, zip, phone);
			fcb.addRecord((char*)& stu);
			cout << "Record had been written!\n";
			break;
		case 5:
			cout << "Enter Key:\n";
			cin >> ID;
			rec = fcb.recInfo.findRecordNr(ID);
			if (rec == -1)
				throw "Record does not exist";
			cout << "Reading record...\n";
			fcb.readRecord((char*)& stu, rec);
			cout << stu;
			break;
		case 6:
			if (!fcb.loaded)
				throw "No File is open!";
			cout << "Enter Student ID:\n";
			cin >> ID;
			cout << "Enter first name:\n";
			cin >> firstName;
			cout << "Enter last name:\n";
			cin >> lastName;
			cout << "Enter grade:\n";
			cin >> grade;
			cout << "Enter street:\n";
			cin >> street;
			cout << "Enter house number:\n";
			cin >> houseNo;
			cout << "Enter city:\n";
			cin >> city;
			cout << "Enter zip code:\n";
			cin >> zip;
			cout << "Enter phone number:\n";
			cin >> phone;
			cout << "Updating Record...\n";
			stu = Student(ID, firstName, lastName, grade, street, houseNo, city, zip, phone);
			fcb.updateRecord((char*)& stu);
			cout << "Record had been updated!\n";
			break;
		case 7:
			cout << "Enter record key:\n";
			cin >> ID;
			rec = fcb.recInfo.findRecordNr(ID);
			if (rec == -1)
				throw "Record does not exist";
			cout << "Deleting record...\n";
			fcb.deleteRecord(rec);
			cout << "Record deleted!\n";
			break;
		case 8:
			if (!fcb.loaded)
				throw "No file is open!";
			cout << fcb.recInfo;
			break;
		case 9:
			cout << "Closing File...\n";
			fcb.closeFile();
			cout << "File Closed!\n";
			break;
		default:
			break;
		}

	}
	static void welcomeDebugLevel3(Disk& d, FCB& fcb)
	{
		int a;
		d.mountDisk(string("Disk1.fms"));
		d.signIn(string("Daniel"), string("1234"));
		fcb = (*d.openFile(string("TestFile"), MODE::WR));
		cout << "Welcome to Level 3 Debugging Mode!\nWhat would you like to do?\n";
		cout << "1. Set Disk (level 0)\n";
		cout << "2. Manage Files (level 2)\n";
		cout << "3. Open File\n";
		cout << "4. Add Record\n";
		cout << "5. Read Record\n";
		cout << "6. Update Record\n";
		cout << "7. Delete Record\n";
		cout << "8. Print Rec Info\n";
		cout << "9. Close File\n";
		cout << "10. Exit\n";
		cin >> a;
		while (a != 10)
		{
			if (a > 10 || a < 1)
			{
				cout << "Illegal Command!\n";
			}
			else
			{
				try {
					startDebug(d,fcb, a);
				}
				catch (const char* str) {
					cout << str << endl;
				}
			}
			cout << "Welcome to Level 3 Debugging Mode!\nWhat would you like to do?\n";
			cout << "1. Set Disk (level 0)\n";
			cout << "2. Manage Files (level 2)\n";
			cout << "3. Open File\n";
			cout << "4. Add Record\n";
			cout << "5. Read Record\n";
			cout << "6. Update Record\n";
			cout << "7. Delete Record\n";
			cout << "8. Print Rec Info\n";
			cout << "9. Close File\n";
			cout << "10. Exit\n";
			cin >> a;
		}
	}
};


int main()
{	
	try{
		FCB fcb;
		Disk d;
		//Level3Debug::welcomeDebugLevel3(d,fcb);
		Level0Debug::welcomeDebugLevel0(d);

		//cout << sizeof(FileHeader) << endl;

	}
	catch (const char* str){
		cout << str << endl;
	}
	system("pause");
	return 0;
}