#pragma once
#include "ui_ftnoir_rift_clientcontrols_042.h"
#include "api/plugin-api.hpp"
#include "options/options.hpp"
#include <OVR.h>
#include <QMessageBox>
#include <QWaitCondition>
#include <cmath>
#include <memory>
using namespace options;

struct settings : opts {
    value<bool> useYawSpring;
    value<double> constant_drift, persistence, deadzone;
    settings() :
        opts("Rift-042"),
        useYawSpring(b, "yaw-spring", false),
        constant_drift(b, "constant-drift", 0.000005),
        persistence(b, "persistence", 0.99999),
        deadzone(b, "deadzone", 0.02)
    {}
};

class Rift_Tracker : public ITracker
{
public:
    Rift_Tracker();
    virtual ~Rift_Tracker() override;
    void start_tracker(QFrame *) override;
    void data(double *data) override;
private:
    double old_yaw;
    ovrHmd hmd;
    settings s;
};

class dialog_rift_042: public ITrackerDialog
{
    Q_OBJECT
public:
    dialog_rift_042();

    void register_tracker(ITracker *) {}
    void unregister_tracker() {}

private:
    Ui::dialog_rift_042 ui;
    settings s;
private slots:
    void doOK();
    void doCancel();
};

class rift_042Dll : public Metadata
{
public:
    QString name() { return QString(QCoreApplication::translate("rift_042Dll", "Oculus Rift runtime 0.4.2 -- HMD")); }
    QIcon icon() { return QIcon(":/images/rift_tiny.png"); }
};

