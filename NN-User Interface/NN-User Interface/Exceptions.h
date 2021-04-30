#pragma once

public ref class Error {
public:
	System::String^ mess;
public:
	Error(System::String^ error) {
		this->mess = error;
	}
	
	Error(){}
};

public ref class Input_error: public Error {
public:
	Input_error(double got, System::String^ expected) {
		this->mess = System::String::Format("Input_error: got ({0}) expected ({1})", got, expected);
	}
};

public ref class File_error: public Error{
public:
	File_error(System::String^ path, System::String^ error) {
		this->mess = System::String::Format("File_error: file ({0}) {1}", path, error);
	}
};