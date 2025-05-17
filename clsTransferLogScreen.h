#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include <fstream>
#include "clsBankClient.h"



class clsTransferLogScreen : protected clsScreen
{

private:

    static void PrintTransferRegisterRecordLine(clsBankClient::stTransferRegisterRecord TransferRegisterRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(25) << left << TransferRegisterRecord.DateTime;
        cout << "| " << setw(10) << left << TransferRegisterRecord.AccountNumberFrom;
        cout << "| " << setw(10) << left << TransferRegisterRecord.AccountNumberTo;
        cout << "| " << setw(10) << left << TransferRegisterRecord.Amount;
        cout << "| " << setw(10) << left << TransferRegisterRecord.AccountBalanceFrom;
        cout << "| " << setw(10) << left << TransferRegisterRecord.AccountBalanceTo;
        cout << "| " << setw(10) << left << TransferRegisterRecord.UserName;
    }


public:

    static void ShowTransferLogScreen()
    {

        vector <clsBankClient::stTransferRegisterRecord> vTransferRegisterRecord = clsBankClient::GetTransferRegisterList();

        string Title = "\tTransfer Register List Screen";
        string SubTitle = "\t\t(" + to_string(vTransferRegisterRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(10) << "S.AccN";
        cout << "| " << left << setw(10) << "D.AccN";
        cout << "| " << left << setw(10) << "Ammount";
        cout << "| " << left << setw(10) << "S.AccB";
        cout << "| " << left << setw(10) << "D.AccB";
        cout << "| " << left << setw(10) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else

            for (clsBankClient::stTransferRegisterRecord Record : vTransferRegisterRecord)
            {

                PrintTransferRegisterRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }



};

