﻿// EXE.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "optionOutput.hpp"
#include "optionFactory.hpp"

#include <conio.h>
#include <cmath>
#include <iomanip>>
#include <Windows.h>

using namespace std;

int main()
{
	try
	{
		OptionFactory factory;
		OptionProduct op = Vanilla;
		OptionProduct op2 = Digital;
		OptionType type = Call;
		OptionType type2 = Put;

		double spot = 430.0;
		double strike = 430.0;
		double rf = 0.008;
		double div = 0.0;
		double vol = 0.22;
		double tau = 0.5;
		double mktPrice = 20.0;

		//Date valuationDt(2021, 7, 21);
		//Date mat(2021, 8, 21);

		unsigned long nSim = 10000;
		double di = 0.00125;
		double dj = 0.005; //dS = dTau * 4 (Stability Factor)

		ProcessGBM process(spot, rf, div, vol);
		optionOutput* option = factory.CreateOption(op, type, strike);
		option->setValuationDate(tau);
		option->setProcess(process);

		optionOutput* option2 = factory.CreateOption(op2, type2, strike);
		option2->setValuationDate(tau);
		option2->setProcess(process);

		std::cout << setprecision(6) << std::endl;
		std::cout << std::endl;


		option->printInfo();

		std::cout << "*********************Price********************" << std::endl;
		std::cout << "BSM Price            " << option->bsmPrice() << std::endl;
		std::cout << "MC Price             " << option->mcPrice(nSim) << std::endl;
		std::cout << "Implicit FDM(Thomas) " << option->fdmPrice(Thomas, di, dj) << std::endl;
		std::cout << "**********************************************" << std::endl;

		std::cout << "*********************Delta********************" << std::endl;
		std::cout << "BSM         " << option->BSdelta() << std::endl;
		std::cout << "MC          " << option->delta(nSim) << std::endl;
		std::cout << "FDM         " << option->delta(Thomas, di, dj) << std::endl;


		std::cout << "*********************Gamma********************" << std::endl;
		std::cout << "BSM         " << option->BSgamma() << std::endl;
		std::cout << "MC          " << option->gamma(nSim) << std::endl;
		std::cout << "FDM         " << option->gamma(Thomas, di, dj) << std::endl;


		std::cout << "*********************Vega*********************" << std::endl;
		std::cout << "BSM         " << option->BSvega() << std::endl;
		std::cout << "MC          " << option->vega(nSim) << std::endl;
		std::cout << "FDM         " << option->vega(Thomas, di, dj) << std::endl;

		std::cout << "*********************Theta********************" << std::endl;
		std::cout << "BSM         " << option->BStheta() << std::endl;
		std::cout << "MC          " << option->theta(nSim) << std::endl;
		std::cout << "FDM         " << option->theta(Thomas, di, dj) << std::endl;

		std::cout << "*********************Rho**********************" << std::endl;
		std::cout << "BSM         " << option->BSrho() << std::endl;
		std::cout << "MC          " << option->rho(nSim) << std::endl;
		std::cout << "FDM         " << option->rho(Thomas, di, dj) << std::endl;

		std::cout << "**********************************************" << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

		option2->printInfo();

		std::cout << "*********************Price********************" << std::endl;
		std::cout << "BSM Price            " << option2->bsmPrice() << std::endl;
		std::cout << "MC Price             " << option2->mcPrice(nSim) << std::endl;
		std::cout << "Implicit FDM(Thomas) " << option2->fdmPrice(Thomas, di, dj) << std::endl;
		std::cout << "**********************************************" << std::endl;

		std::cout << "*********************Delta********************" << std::endl;
		std::cout << "MC          " << option2->delta(nSim) << std::endl;
		std::cout << "FDM         " << option2->delta(Thomas, di, dj) << std::endl;


		std::cout << "*********************Gamma********************" << std::endl;
		std::cout << "MC          " << option2->gamma(nSim) << std::endl;
		std::cout << "FDM         " << option2->gamma(Thomas, di, dj) << std::endl;


		std::cout << "*********************Vega*********************" << std::endl;
		std::cout << "MC          " << option2->vega(nSim) << std::endl;
		std::cout << "FDM         " << option2->vega(Thomas, di, dj) << std::endl;

		std::cout << "*********************Theta********************" << std::endl;
		std::cout << "MC          " << option2->theta(nSim) << std::endl;
		std::cout << "FDM         " << option2->theta(Thomas, di, dj) << std::endl;

		std::cout << "*********************Rho**********************" << std::endl;
		std::cout << "MC          " << option2->rho(nSim) << std::endl;
		std::cout << "FDM         " << option2->rho(Thomas, di, dj) << std::endl;


		std::cout << std::endl;

		std::cout << "********Vanilla Implied volatility " << std::endl;
		std::cout << "Implied vol with market price " << mktPrice <<" , Imp Vol : " << option->impVol(mktPrice, 0.8, 1e-10) << std::endl;

		std::cout << std::endl;
		std::cout << std::endl;

		std::cout << "************** end ***************" << std::endl;

		
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;

	}

	system("pause");
	return 0;
}
