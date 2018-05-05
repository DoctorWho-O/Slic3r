#ifndef PROGRESSSTATUSBAR_HPP
#define PROGRESSSTATUSBAR_HPP
#include <wx/event.h> 
#include <wx/statusbr.h>
#include <wx/timer.h>
#include <wx/gauge.h>
#include <wx/button.h>

namespace Slic3r { namespace GUI {

class ProgressStatusBar : public wxStatusBar {
public:
    /// Constructor stub from parent
    ProgressStatusBar(wxWindow* parent, int id);

    /// Stop any running timers before destruction.
    ~ProgressStatusBar();

    /// 
    wxTimer* timer {new wxTimer(this)};

    /// Progress bar
    wxGauge* prog {new wxGauge(this, wxGA_HORIZONTAL, 100, wxDefaultPosition, wxDefaultSize)};

    /// General cancel button. Using applications can assign functions to it.
    wxButton* cancelbutton {new wxButton(this, -1, _("Cancel"), wxDefaultPosition, wxDefaultSize)};

    /// Set callback function for cancel button press.
    void SetCancelCallback(std::function<void()> cb) {
        this->cancel_cb = cb;
        cb == nullptr ? this->cancelbutton->Hide() : this->cancelbutton->Show();
    }
   
    /// Accessor function for the current value of the progress bar
    size_t GetProgress() {return this->prog->GetValue();}

    /// Accessor function for busy state
    bool IsBusy() {return this->busy;}

    /// Show the progress bar.
    void ShowProgress(bool show = true) { this->prog->Show(show); this->prog->Pulse(); }

    void SetRange(int range) { if (range != this->prog->GetRange() ) this->prog->SetRange(range);}

private:
    void OnSize(wxSizeEvent& e);
    void OnTimer(wxTimerEvent& e);
    void Run(int rate = 100) { if (this->timer->IsRunning()) this->timer->Start(rate);};

    // Cancel callback function
    std::function<void()> cancel_cb {[](){;}};

    bool busy {false};

};

}} // Namespace Slic3r::GUI
#endif // PROGRESSSTATUSBAR_HPP