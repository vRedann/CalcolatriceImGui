#pragma once
#include <stdlib.h> 
#include "App.h"

class MyApp : public App
{
public:

	//Constructor
	MyApp() = default;

	//Destructor
	~MyApp() = default;

	//Override
	virtual void StartUp() final;

	virtual void Update() final;

	//Theme
	void Style();

	//Button
	void SetButton();

	//Enum
	const enum class operation { add = 1, sott, molt, div };

	//Internal Method
	void		ResetInputText();
	void		AddNumber(int i);
	void		AddNumber(std::string s);
	void		operazione(operation o);
	std::string noZero(double n);
	std::string noZero(std::string s);

private:

	//Theme
	ImGuiStyle& style	= ImGui::GetStyle();

	//Windows Settings
	const float WIDTH	= 326.0f;
	const float HEIGHT	= 402.0f;
	bool		is_open		= true;

	//Input Text box
	std::string inputTextOutput;

	//Number
	double	number1	= NULL;
	double	number2	= NULL;
	double	result	= NULL;

	//bool
	bool	firstOp = true;
};


