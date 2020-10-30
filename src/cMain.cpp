#include "cMain.h"
#include "Converters.h"
#include <Windows.h>
#include <fstream>

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	
wxEND_EVENT_TABLE()


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Binary Converter", wxPoint(500, 500), wxSize(1000, 570))
{
	this->SetBackgroundColour(*wxWHITE);
	asciiInput = new wxTextCtrl(this, 1000, "", wxPoint(10, 10), wxSize(950, 200), wxTE_MULTILINE);
	asciiInput->Bind(wxEVT_TEXT, &cMain::AsciiInputKeyPressed, this);
	asciiInput->DragAcceptFiles(true);


	binaryOutput = new wxTextCtrl(this, 1001, "", wxPoint(10, 300), wxSize(950, 200), wxTE_MULTILINE);
	binaryOutput->Bind(wxEVT_TEXT, &cMain::BinaryInputKeyPressed, this);
	binaryOutput->DragAcceptFiles(true);

	addSpacesBox = new wxCheckBox(this, wxID_ANY, "Add Spaces to Binary", wxPoint(10, 242));
	addSpacesBox->Bind(wxEVT_CHECKBOX, &cMain::addSpacesCheckedChanged, this);
	addSpacesBox->SetValue(true);

	useButtonConvert = new wxCheckBox(this, wxID_ANY, "Use Buttons to Convert", wxPoint(10, 220));
	useButtonConvert->Bind(wxEVT_CHECKBOX, &cMain::UseButtonConvertChanged, this);

	useCustomCode = new wxCheckBox(this, wxID_ANY, "Use Custom Code", wxPoint(10, 263));
	useCustomCode->Bind(wxEVT_CHECKBOX, &cMain::useCustomCodeCheckedChanged, this);

	AsciiToBinary = new wxButton(this, wxID_ANY, "Ascii to Binary", wxPoint(250, 220), wxSize(100, 25));
	AsciiToBinary->Bind(wxEVT_BUTTON, &cMain::AsciiToBinaryPressed, this);
	AsciiToBinary->Hide();

	BinaryToAscii = new wxButton(this, wxID_ANY, "Binary to Ascii", wxPoint(370, 220), wxSize(100, 25));
	BinaryToAscii->Bind(wxEVT_BUTTON, &cMain::BinaryToAsciiPressed, this);
	BinaryToAscii->Hide();

	TextEntry = new wxTextEntryDialog(this, "Enter password", "Unauthorized access");
	pathEntry = new wxTextEntryDialog(this, "Enter Directory", "Path Required");
	pathEntry->DragAcceptFiles(true);
	pathEntry->Bind(wxEVT_DROP_FILES, &cMain::PathEntryFileDrop, this);

	SaveToFile = new wxButton(this, wxID_ANY, "Save to File", wxPoint(880, 265), wxSize(80, 25));
	SaveToFile->Bind(wxEVT_BUTTON, &cMain::OnSaveToFileClick, this);

	ByteSize = new wxStaticText(this, wxID_ANY, "0 Bytes", wxPoint(10, 280));

	CorrectPasswordTyped = RetrieveUsername() == "lebed" || RetrieveUsername() == "krd456873@gnspes.ca" ? true : false;
}

cMain::~cMain()
{
	delete TextEntry;
	delete pathEntry;
}

void cMain::AsciiInputKeyPressed(wxCommandEvent& evt)
{
	if (!useButtonConvert->GetValue())
	{
		if (!useCustomCode->GetValue())
			binaryOutput->ChangeValue(ConvertToBinary(std::string(asciiInput->GetValue().mb_str()), addSpacesBox->GetValue()));
		
		else
			binaryOutput->ChangeValue(AsciiToCustom(std::string(asciiInput->GetValue().mb_str())));
		UpdateLabel();
	}
	evt.Skip();
}

void cMain::BinaryInputKeyPressed(wxCommandEvent& evt)
{
	if (!useButtonConvert->GetValue())
	{
		if(!useCustomCode->GetValue())
			asciiInput->ChangeValue(ConvertToAscii(std::string(binaryOutput->GetValue().mb_str())));
		else
			asciiInput->ChangeValue(ConvertToAscii(CustomToBinary(std::string(binaryOutput->GetValue().mb_str()))));
		UpdateLabel();
	}
	
	evt.Skip();
}

void cMain::UseButtonConvertChanged(wxCommandEvent& evt)
{
	if (useButtonConvert->GetValue())
	{
		AsciiToBinary->Show();
		BinaryToAscii->Show();
	}
	else
	{
		AsciiToBinary->Hide();
		BinaryToAscii->Hide();
	}
	evt.Skip();
}


void cMain::AsciiToBinaryPressed(wxCommandEvent& evt)
{
	if (!useCustomCode->GetValue())
		binaryOutput->ChangeValue(ConvertToBinary(std::string(asciiInput->GetValue().mb_str()), addSpacesBox->GetValue()));

	else
		binaryOutput->ChangeValue(AsciiToCustom(std::string(asciiInput->GetValue().mb_str())));

	UpdateLabel();
	evt.Skip();
}

void cMain::BinaryToAsciiPressed(wxCommandEvent& evt)
{
	if (!useCustomCode->GetValue())
	{
		asciiInput->ChangeValue(ConvertToAscii(std::string(binaryOutput->GetValue().mb_str())));
	}
	else
	{
		asciiInput->ChangeValue(ConvertToAscii(CustomToBinary(std::string(binaryOutput->GetValue().mb_str()))));
	}
	UpdateLabel();
	evt.Skip();
}

void cMain::addSpacesCheckedChanged(wxCommandEvent& evt)
{
	binaryOutput->ChangeValue(ConvertToBinary(std::string(asciiInput->GetValue().mb_str()), addSpacesBox->GetValue()));
	UpdateLabel();
	evt.Skip();
}

void cMain::useCustomCodeCheckedChanged(wxCommandEvent& evt)
{
	if (CorrectPasswordTyped)
	{
		if (useCustomCode->GetValue())
		{
			AsciiToBinary->SetLabel("Ascii to Custom");
			BinaryToAscii->SetLabel("Custom to Ascii");
			addSpacesBox->Disable();
			return;
		}
		else
		{
			AsciiToBinary->SetLabel("Ascii to Binary");
			BinaryToAscii->SetLabel("Binary to Ascii");
			addSpacesBox->Enable();
			return;
		}
	}
	else
	{
		while (!CorrectPasswordTyped)
		{
			if (TextEntry->ShowModal() == wxID_OK)
			{
				const std::string username = RetrieveUsername();

				if (TextEntry->GetValue() == (username + "123"))
				{
					CorrectPasswordTyped = true;
					if (useCustomCode->GetValue())
					{
						AsciiToBinary->SetLabel("Ascii to Custom");
						BinaryToAscii->SetLabel("Custom to Ascii");
						addSpacesBox->Disable();
					}
					else
					{
						AsciiToBinary->SetLabel("Ascii to Binary");
						BinaryToAscii->SetLabel("Binary to Ascii");
						addSpacesBox->Enable();
					}
				}
				else
				{
					wxMessageBox("Incorrect Password!", "Incorrect Password!");
					TextEntry->SetValue("");
				}
			}
			else
			{
				useCustomCode->SetValue(false);
				break;
			}
		}
	}
	if(!CorrectPasswordTyped) { useCustomCode->SetValue(false); }
	TextEntry->SetValue("");
	TextEntry->Close();
	evt.Skip();
}

void cMain::UpdateLabel()
{
	ByteSize->SetLabel(std::to_string(asciiInput->GetValue().size()) + " Bytes");
}

void cMain::OnSaveToFileClick(wxCommandEvent& evt)
{
	if (pathEntry->ShowModal() == wxID_OK)
	{
		std::string pathStr = "";
		for (int i = 0; i < pathEntry->GetValue().size(); i++)
		{
			pathStr.push_back(pathEntry->GetValue()[i]);
		}
		const char* path = pathStr.c_str();
		std::ofstream file(path);
			
		file << binaryOutput->GetValue().c_str() << std::endl;
		file.close();
	}

	evt.Skip();
}

void cMain::PathEntryFileDrop(wxDropFilesEvent& evt)
{
	if (evt.GetNumberOfFiles() > 0)
	{
		pathEntry->SetValue(*evt.GetFiles());
	}
	evt.Skip();
}