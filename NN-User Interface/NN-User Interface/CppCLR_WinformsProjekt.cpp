#include "pch.h"


//int main(array<System::String ^> ^args)
//{
//    return 0;
//}

#include "Form1.h"



//[STAThread]
int main() {
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	System::Windows::Forms::Application::Run(gcnew CppCLRWinformsProjekt::Form1());
	return 0;
}