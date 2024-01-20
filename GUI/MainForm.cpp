#include "MainForm.h"

using namespace System;
using namespace Windows::Forms;

[STAThread]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew GUI::MainForm());

	return 0;
}