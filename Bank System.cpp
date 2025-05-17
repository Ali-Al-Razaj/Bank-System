// Bank System.cpp : This file contains the 'main' function. Program execution begins and ends there.

#define _CRT_SECURE_NO_WARNINGS


#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsLoginScreen.h"
#include "Global.h"


int main()
{
    
    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }



    return 0;


}


