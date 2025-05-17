#pragma once

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"



class clsUpdateCurrencyScreen : protected clsScreen
{

private:

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";
    }


public:

    static void ShowUpdateCurrencyScreen()
    {
        _DrawScreenHeader("\t  Update Currency Screen");

        string code;
        cout << "\nEnter Currency Code ? ";
        code = clsInputValidate::ReadString();
        clsCurrency Currency = clsCurrency::FindByCode(code);

        if (Currency.IsEmpty())
        {
            cout << "\nCurrency Not Found.." << endl;

        }
        else
        {
            _PrintCurrency(Currency);

            cout << "\nAre You Sure You Want To update The Rate Of This Currency Y/N ? ";
            char Answer = 'N';
            cin >> Answer;

            if (Answer == 'Y' || Answer == 'y')
            {
                cout << "\nUpdate Currency Rate : " << endl;
                cout << "______________________ " << endl;

                cout << "\nEnter New Rate : ";
                float newRate = 0;
                newRate = clsInputValidate::ReadDblNumber();

                Currency.UpdateRate(newRate);
                cout << "\nCurrency Updated Successfully..." << endl;
                _PrintCurrency(Currency);
            }


        }




    }


};

