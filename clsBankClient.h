#pragma once

//#include <iostream>
//#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include <vector>
#include <fstream>
#include "Global.h"
//using namespace std;



class clsBankClient : public clsPerson
{

private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;

    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;


    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector <string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }
    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.GetFirstName() + Seperator;
        stClientRecord += Client.GetLastName() + Seperator;
        stClientRecord += Client.GetEmail() + Seperator;
        stClientRecord += Client.GetPhone() + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client._PinCode + Seperator;
        stClientRecord += to_string(Client._AccountBalance);

        return stClientRecord;

    }

    static vector <clsBankClient> _LoadClientsDataFromFile()
    {
        vector <clsBankClient> vCLients;
        fstream myFile;
        myFile.open("Clients.txt", ios::in);

        if (myFile.is_open())
        {
            string Line;
            while (getline(myFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                vCLients.push_back(Client);
            }
            myFile.close();
        }
        return vCLients;
    }

    static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
    {
        fstream myFile;
        myFile.open("Clients.txt", ios::out);

        string DataLine;

        if (myFile.is_open())
        {
            for (clsBankClient c : vClients)
            {
                if (c._MarkedForDelete == false)
                {
                    DataLine = _ConverClientObjectToLine(c);
                    myFile << DataLine << endl;
                }
            }
            myFile.close();
        }
    }

    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& c : _vClients)
        {
            if (c.AccountNumber() == AccountNumber())
            {
                c = *this;
                break;
            }
        }

        _SaveClientsDataToFile(_vClients);
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }
    void _AddNew()
    {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }



    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient,
        string UserName, string Seperator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
        TransferLogRecord += AccountNumber() + Seperator;
        TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(_AccountBalance) + Seperator;
        TransferLogRecord += to_string(DestinationClient.GetAccountBalance()) + Seperator;
        TransferLogRecord += UserName;
        return TransferLogRecord;
    }

    void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
    {

        string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }


public:

    struct stTransferRegisterRecord
    {
        string DateTime;
        string AccountNumberFrom;
        string AccountNumberTo;
        float Amount;
        float AccountBalanceFrom;
        float AccountBalanceTo;
        string UserName;

        // 4/4/2024 - 1:40:7#//#A101#//#A106#//#95000.000000#//#200000.000000#//#103002.000000#//#User1
    };

    // I Added This Function Public Because It Did Not Work Like Abu_Hadhoud Did it
    // He Added It Privet And Added The Struct Header Before It
    static stTransferRegisterRecord _ConvertTransferRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stTransferRegisterRecord LoginRegisterRecord;

        vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.AccountNumberFrom = LoginRegisterDataLine[1];
        LoginRegisterRecord.AccountNumberTo = LoginRegisterDataLine[2];
        LoginRegisterRecord.Amount = stof(LoginRegisterDataLine[3]);
        LoginRegisterRecord.AccountBalanceFrom = stof(LoginRegisterDataLine[4]);
        LoginRegisterRecord.AccountBalanceTo = stof(LoginRegisterDataLine[5]);
        LoginRegisterRecord.UserName = LoginRegisterDataLine[6];

        return LoginRegisterRecord;

    }


    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
        string AccountNumber, string PinCode, float AccountBalance)
        : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }
    string GetPinCode()
    {
        return _PinCode;
    }

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    float GetAccountBalance()
    {
        return _AccountBalance;
    }

    // We Will Remove Print Method Later
    void Print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << GetFirstName();
        cout << "\nLastName    : " << GetLastName();
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << GetEmail();
        cout << "\nPhone       : " << GetPhone();
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n___________________\n";

    }


    static clsBankClient Find(string AccountNumber)
    {
        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }

                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client._PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

                vClients.push_back(Client);
            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };
    enSaveResults Save()
    {
        switch (_Mode)
        {

        case enMode::EmptyMode:
        {
            return enSaveResults::svFaildEmptyObject;
        }
        case enMode::UpdateMode:
        {
            _Update();

            return enSaveResults::svSucceeded;

            break;
        }
        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();

                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
            break;
        }

        }
    }

    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient client1 = clsBankClient::Find(AccountNumber);
        return (!client1.IsEmpty());
    }

    bool Delete()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& c : _vClients)
        {
            if (c.AccountNumber() == _AccountNumber)
            {
                c._MarkedForDelete = true;
                break;
            }
        }

        _SaveClientsDataToFile(_vClients);

        *this = _GetEmptyClientObject();

        return true;
    }

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    static vector <clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static double GetTotalBalances()
    {
        double TotalBalances = 0;

        vector <clsBankClient> vClients = _LoadClientsDataFromFile();
        for (clsBankClient client : vClients)
        {
            TotalBalances += client._AccountBalance;
        }

        return TotalBalances;
    }

    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }

    }

    bool Transfer(float Amount, clsBankClient& DestinationClient, string UserName)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }

        Withdraw(Amount);
        DestinationClient.Deposit(Amount);

        _RegisterTransferLog(Amount, DestinationClient, UserName);

        return true;
    }

    static  vector <stTransferRegisterRecord> GetTransferRegisterList()
    {
        vector <stTransferRegisterRecord> vTransferRegisterRecord;

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            stTransferRegisterRecord TransferRegisterRecord;

            while (getline(MyFile, Line))
            {

                TransferRegisterRecord = _ConvertTransferRegisterLineToRecord(Line);

                vTransferRegisterRecord.push_back(TransferRegisterRecord);

            }

            MyFile.close();

        }

        return vTransferRegisterRecord;

    }



};

