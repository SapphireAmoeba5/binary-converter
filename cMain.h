#pragma once
#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

	wxTextCtrl* asciiInput;
	wxTextCtrl* binaryOutput;
	wxCheckBox* addSpacesBox;
	wxCheckBox* useButtonConvert;
	wxCheckBox* useCustomCode;

	wxButton* AsciiToBinary;
	wxButton* BinaryToAscii;

	wxButton* SaveToFile;

	wxStaticText* ByteSize;

	wxTextEntryDialog* TextEntry;
	wxTextEntryDialog* pathEntry;

	bool CorrectPasswordTyped;

	void AsciiInputKeyPressed(wxCommandEvent& evt);
	void BinaryInputKeyPressed(wxCommandEvent& evt);
	void UseButtonConvertChanged(wxCommandEvent& evt);
	void AsciiToBinaryPressed(wxCommandEvent& evt);
	void BinaryToAsciiPressed(wxCommandEvent& evt);
	void addSpacesCheckedChanged(wxCommandEvent& evt);
	void useCustomCodeCheckedChanged(wxCommandEvent& evt);
	void OnSaveToFileClick(wxCommandEvent& evt);
	void PathEntryFileDrop(wxDropFilesEvent& evt);
	void UpdateLabel();
	wxDECLARE_EVENT_TABLE();
};
