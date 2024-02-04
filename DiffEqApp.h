#pragma once
#include "wx/wxprec.h"
#include "wx/frame.h"
#include "wx/menu.h"
#include "wx/statline.h"
#include "wx/wx.h"
#include "wx/textctrl.h"
#include "packages/matplotlib-cpp.1.1.0.92/include/matplotlibcpp.h"
#include <wx/image.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/log.h>
#include <wx/intl.h>
#include <wx/print.h>
#include <wx/filename.h>

#if wxUSE_CLIPBOARD
#include "wx/dataobj.h"
#include "wx/clipbrd.h"
#endif

#if wxUSE_FILE
#include "wx/file.h"
#endif

#if wxUSE_TOOLTIPS
#include "wx/tooltip.h"
#endif

#if !wxUSE_DRAG_AND_DROP
#undef wxUSE_CLIPBOARD
#define wxUSE_CLIPBOARD 0
#endif

#include "wx/colordlg.h"
#include "wx/fontdlg.h"
#include "wx/numdlg.h"
#include "wx/tokenzr.h"

namespace DiffEqSolver
{
    class DiffEqPanel : public wxPanel
    {
    public:
        DiffEqPanel(wxFrame* frame, int x, int y, int w, int h);
        std::string GetEquation();
        const float GetInitialValue();
        const float GetStartTime();
        const float GetEndTime();
        const float GetTimeStep();

    private:

        wxTextCtrl* m_equation = NULL;
        wxTextCtrl* m_timeStep = NULL;
        wxTextCtrl* m_initialValue = NULL;
        wxTextCtrl* m_timeStart = NULL;
        wxTextCtrl* m_timeEnd = NULL;

    };

    class DiffEqApp : public wxApp
    {
    public:
         bool OnInit() wxOVERRIDE;

    };

    wxIMPLEMENT_APP(DiffEqApp);

    class DiffEqFrame : public wxFrame
    {
    public:

        DiffEqFrame(const wxString& title, const int x, const int y);
        void OnSolve(wxCommandEvent& event);
        void DisplayErrorMessage(const std::string& errorInfo);
        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);

    private:

        DiffEqPanel* m_panel;
        wxDECLARE_EVENT_TABLE();
    };

   
    enum 
    {
        BUTTON_Solve = 1,
    };
}

