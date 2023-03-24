#include "MyApp.h"
#include <iostream>

void MyApp::StartUp()
{
	Style();
}

void MyApp::Update()
{
	ImGui::SetNextWindowSize(ImVec2(WIDTH, HEIGHT)); //Window Size
	ImGuiWindowFlags windowFlags = 
		ImGuiWindowFlags_NoSavedSettings |			ImGuiWindowFlags_NoResize | 
		ImGuiWindowFlags_NoScrollbar |				ImGuiWindowFlags_NoScrollWithMouse;
	if (is_open){
		ImGui::Begin("Calcolatrice", &is_open, windowFlags);
		SetButton();
		ImGui::SetCursorPos(ImVec2(4, 48));
		ImGui::SetNextItemWidth(318);
		ImGui::PushFont(_bigFont);
		ImGui::InputText(" ", &inputTextOutput, ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_CharsDecimal);
		ImGui::PopFont();
		//ImGui::AlignTextToFramePadding();;
		ImGui::End();
	}

	if (is_open)
	{
		ImGui::Begin("Dear ImGui Style Editor", &is_open);
		ImGui::ShowStyleEditor();
		ImGui::End();
	}
}

void MyApp::Style()
{
	style.WindowBorderSize	= 0.0f;
	style.FrameBorderSize	= 0.0f;
	style.WindowRounding	= 7.0f;
	style.FrameRounding		= 4.0f;
	style.WindowPadding		= ImVec2(0, 8); 
	style.FramePadding		= ImVec2(6,6);
}

//Button generation
void MyApp::SetButton()
{
	const ImVec2 buttonSize = { 78, 58 };
	int buttonHeight		= HEIGHT - (buttonSize.y + 4);

	//Set positioning
	ImGui::SetCursorPos(ImVec2(4, buttonHeight));

	// | +/- | 0 | , | = |
	if (ImGui::Button("+/-", buttonSize)) {

	}
	ImGui::SameLine(0, 2);
	if (ImGui::Button("0", buttonSize)) {
		AddNumber(0);
	}
	ImGui::SameLine(0, 2);
	if (ImGui::Button(",", buttonSize)) {

	}
	ImGui::SameLine(0, 2);
	if (ImGui::Button("=", buttonSize)) {
		inputTextOutput = result;
	}

	//Set positioning
	buttonHeight -= buttonSize.y+2;
	ImGui::SetCursorPos(ImVec2(4, buttonHeight));

	// | 1 | 2 | 3 | + |
	for (size_t i = 1, firstPass = 0; i <= 3; i++){	
		if (firstPass == 0) {
			firstPass = 1;
		}
		else{
			ImGui::SameLine(0, 2);
		}	
		if (ImGui::Button(std::to_string(i).c_str(), buttonSize)) {
			AddNumber(i);	
		}
	}
	ImGui::SameLine(0, 2);
	if (ImGui::Button("+", buttonSize)) {
		if (!inputTextOutput.empty()) {
			operazione(operation::add);
		}
	}

	//Set positioning
	buttonHeight -= buttonSize.y + 2;
	ImGui::SetCursorPos(ImVec2(4, buttonHeight));

	// | 4 | 5 | 6 | - |
	for (size_t i = 4, firstPass = 0; i <= 6; i++) {
		if (firstPass == 0){
			firstPass = 1;
		}
		else{
			ImGui::SameLine(0, 2);
		}
		if (ImGui::Button(std::to_string(i).c_str(), buttonSize)) {
			AddNumber(i);
		}
	}
	ImGui::SameLine(0, 2);
	if (ImGui::Button("-", buttonSize)) {

	}

	//Set positioning
	buttonHeight -= buttonSize.y + 2;
	ImGui::SetCursorPos(ImVec2(4, buttonHeight));

	// | 7 | 8 | 9 | x |
	for (size_t i = 7, firstPass = 1; i <= 9; i++) {
		if (!firstPass) {
			ImGui::SameLine(0, 2);
		}
		else {
			firstPass = 0;
		}
		if (ImGui::Button(std::to_string(i).c_str(), buttonSize)) {
			AddNumber(i);
		}
	}
	ImGui::SameLine(0, 2);
	if (ImGui::Button("x", buttonSize)) {

	}

	//Set positioning
	buttonHeight -= buttonSize.y + 2;
	ImGui::SetCursorPos(ImVec2(4, buttonHeight));

	// | CE | C | D | / |
	if (ImGui::Button("CE", buttonSize)) {

	}
	ImGui::SameLine(0, 2);
	if (ImGui::Button("C", buttonSize)) {
		number1 = NULL;
		number2 = NULL;
		ResetInputText();
	}
	ImGui::SameLine(0, 2);
	if (ImGui::Button("DEL", buttonSize)) {
		if(!inputTextOutput.empty())
			inputTextOutput.pop_back();
	}
	ImGui::SameLine(0, 2);
	if (ImGui::Button("/", buttonSize)) {

	}
}

void MyApp::ResetInputText()
{
	inputTextOutput.clear();
}

void MyApp::AddNumber(int i) {
	//Debug
	std::cout << inputTextOutput << " " << noZero(result)<< std::endl;
	//End

	if (number2 != NULL && inputTextOutput == noZero(number2)) {
		ResetInputText();
	}
	inputTextOutput += std::to_string(i);
}

void MyApp::AddNumber(std::string s)
{
	inputTextOutput += noZero(s);
}

void MyApp::operazione(operation o)
{
	switch (o) {
	case operation::add:{
		if (firstOp) {
			number1 = std::stod(inputTextOutput);
			number2 += number1;
			//Debug
			std::cout << "NUMBER 1:" << number1 << '\n';
			std::cout << "NUMBER 2:" << number2 << '\n';
			//EndDebug
			inputTextOutput = noZero(number2);
			result = number1;
		}
		}
	}
}

std::string MyApp::noZero(double n)
{
	std::string str = std::to_string(n);
	str.erase(str.find_last_not_of('0') + 1, std::string::npos);
	str.erase(str.find_last_not_of('.') + 1, std::string::npos);
	return str;
}

std::string MyApp::noZero(std::string str)
{
	str.erase(str.find_last_not_of('0') + 1, std::string::npos);
	str.erase(str.find_last_not_of('.') + 1, std::string::npos);
	return str;
}
