#include "DiffEqApp.h"
#include <exception>
#include"RungeKuttaSolver.h"

wxBEGIN_EVENT_TABLE(DiffEqSolver::DiffEqFrame, wxFrame)
EVT_MENU(wxID_EXIT, DiffEqSolver::DiffEqFrame::OnExit)
EVT_MENU(wxID_ABOUT, DiffEqSolver::DiffEqFrame::OnAbout)
EVT_BUTTON(DiffEqSolver::BUTTON_Solve, DiffEqSolver::DiffEqFrame::OnSolve)
wxEND_EVENT_TABLE()


bool DiffEqSolver::DiffEqApp::OnInit()
{
    // create frame
    DiffEqFrame* frame = new DiffEqFrame("RK4 ODE Solver", 50, 50);
    frame->Show(true);
    frame->SetInitialSize(wxSize(300, 500));

    return true;
}

DiffEqSolver::DiffEqFrame::DiffEqFrame(const wxString& title, const int x, const int y)
    : wxFrame(NULL, wxID_ANY, title, wxPoint(x, y))
{
    SetIcon(wxICON(sample));

    m_panel = new DiffEqPanel(this, 10, 10, 500, 300);
    m_panel->GetSizer()->Fit(this);

    // add menu bar
    wxMenu* file_menu = new wxMenu;
    file_menu->Append(wxID_ABOUT, "&About\tAlt-A");
    file_menu->AppendSeparator();
    file_menu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this sample");

    wxMenuBar* menu_bar = new wxMenuBar(wxMB_DOCKABLE);
    menu_bar->Append(file_menu, "&File");

    SetMenuBar(menu_bar);

}

void DiffEqSolver::DiffEqFrame::OnSolve(wxCommandEvent& event)
{
    wxBeginBusyCursor();
    
    try {
        std::string eq = m_panel->GetEquation();
        float tf = m_panel->GetEndTime();
        float t0 = m_panel->GetStartTime();
        float h = m_panel->GetTimeStep();
        float y0 = m_panel->GetInitialValue();

        std::unique_ptr<RungeKuttaSolver> RKSolver = std::make_unique<RungeKuttaSolver>();
        std::vector<std::vector<float>> output;
        RKSolver->Solve(y0, h, tf, t0, eq, output);
        std::vector<float> t, y;

        for (unsigned int i = 0; i < output.size(); i++)
        {
            float num = output[i][0];
            t.push_back(num);

            num = output[i][1];
            y.push_back(num);
        }

        matplotlibcpp::plot(t,y);
        matplotlibcpp::title("RK4 Solution  (dy/dt = " + eq + ")");
        matplotlibcpp::legend();

        wxEndBusyCursor();

        matplotlibcpp::show(true);

    }
    catch (std::exception& e)
    {
        wxEndBusyCursor();
        DisplayErrorMessage(e.what());
        printf(e.what());
    }

}

void DiffEqSolver::DiffEqFrame::DisplayErrorMessage(const std::string& errorInfo)
{
    wxBeginBusyCursor();

    wxMessageDialog dialog(this,
        "One or more fields contain invalid information.\n"
        "Please check inputs and try again.\n"
        "\n"
        "Error: " + errorInfo,
        "Error",
        wxOK | wxICON_INFORMATION);

    dialog.ShowModal();

    wxEndBusyCursor();
}

void DiffEqSolver::DiffEqFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void DiffEqSolver::DiffEqFrame::OnAbout(wxCommandEvent& event)
{
    wxBeginBusyCursor();

    wxMessageDialog dialog(this,
        "This is simple Oridnay Diffrential Equation solver using Runge-Kutta 4 method.\n"
        "Source code can be found at https://github.com/Brody-Clark/rk4-ode-solver.git \n"
        "\n",
        "About RK4 ODE Solver",
        wxOK | wxICON_INFORMATION);

    dialog.ShowModal();

    wxEndBusyCursor();
}

DiffEqSolver::DiffEqPanel::DiffEqPanel(wxFrame* frame, int x, int y, int w, int h)
    : wxPanel(frame, wxStandardID::wxID_ANY, wxPoint(x, y), wxSize(w, h))
{
    // add input fields
    m_equation = new wxTextCtrl(this, wxID_ANY,"", wxPoint(10, 170), wxSize(140, 70), wxHSCROLL);
    m_timeStep = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    m_timeStart = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    m_timeEnd = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    m_initialValue = new wxTextCtrl(this, wxID_ANY,"", wxDefaultPosition, wxDefaultSize);

    wxGridSizer* gridsizer = new wxGridSizer(2, 1, 1);
    gridsizer->Add(new wxStaticText(this, wxID_ANY, "dy/dt = "),
        wxSizerFlags().Align(wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL));
    gridsizer->Add(m_equation, wxSizerFlags(1).Align(wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL));
    gridsizer->Add(new wxStaticText(this, wxID_ANY, "time step = "),
        wxSizerFlags().Align(wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL));
    gridsizer->Add(m_timeStep, wxSizerFlags(1).Align(wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL));
    gridsizer->Add(new wxStaticText(this, wxID_ANY, "start time = "),
        wxSizerFlags().Align(wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL));
    gridsizer->Add(m_timeStart, wxSizerFlags(1).Align(wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL));
    gridsizer->Add(new wxStaticText(this, wxID_ANY, "end time = "),
        wxSizerFlags().Align(wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL));
    gridsizer->Add(m_timeEnd, wxSizerFlags(1).Align(wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL));
    gridsizer->Add(new wxStaticText(this, wxID_ANY, "y(0) = "),
        wxSizerFlags().Align(wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL));
    gridsizer->Add(m_initialValue, wxSizerFlags(1).Align(wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL));

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(gridsizer,wxSizerFlags().Proportion(1).Expand().Border(wxALL, 10));

#if wxUSE_STATLINE
    topSizer->Add(
        new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(3, 3), wxHORIZONTAL),
        wxSizerFlags().Expand());
#endif // wxUSE_STATLINE

    // add "solve" button
    wxButton* submitButton = new wxButton(this, BUTTON_Solve, "Solve");
    wxBoxSizer* button_box = new wxBoxSizer(wxHORIZONTAL);
    button_box->Add(submitButton, wxSizerFlags().Border(wxALL, 7));

    topSizer->Add(button_box, wxSizerFlags().Center());


    SetSizer(topSizer);
}

std::string DiffEqSolver::DiffEqPanel::GetEquation()
{
    try
    {
        return m_equation->GetLineText(0).ToStdString();
    }
    catch (std::exception e)
    {
        throw(std::runtime_error(e.what() + std::string(". Invalid equation")));
    }
}

const float DiffEqSolver::DiffEqPanel::GetInitialValue()
{
    try {
        return std::stof(m_initialValue->GetLineText(0).ToStdString());
    }
    catch (std::exception e)
    {
        throw(std::runtime_error(e.what() + std::string(". Invalid initial value")));
    }
}

const float DiffEqSolver::DiffEqPanel::GetStartTime()
{
    try {
        return std::stof(m_timeStart->GetLineText(0).ToStdString());
    }
    catch (std::exception e)
    {
        throw(std::runtime_error(e.what() + std::string(". Invalid start time")));
    }
}

const float DiffEqSolver::DiffEqPanel::GetEndTime()
{
    try {
        return std::stof(m_timeEnd->GetLineText(0).ToStdString());
    }
    catch (std::exception e)
    {
        throw(std::runtime_error(e.what() + std::string(". Invalid final time")));
    }
}

const float DiffEqSolver::DiffEqPanel::GetTimeStep()
{
    try {
        return std::stof(m_timeStep->GetLineText(0).ToStdString());
    }
    catch (std::exception e)
    {
        throw(std::runtime_error(e.what() + std::string(". Invalid time step")));
    }
}
