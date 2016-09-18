#include "special_value_saver.h"
#include "query_item.h"

using namespace LoadLevelerMonitor::Model;

// see 'LoadLeveler job states' in <<Using and Administering>> of LoadLevler.
const QVector<JobState> JobStateValueSaver::job_state_list_ = {
    // job state name,      abbreviation
    { "Canceled",           "CA"    },
    { "Checkpointing",      "CK"    },
    { "Completed",          "C"     },
    { "Complete Pending",   "CP"    },
    { "Deferred",           "D"     },
    { "Idle",               "I"     },
    { "Not Queued",         "NQ"    },
    { "Not Run",            "NR"    },
    { "Pending",            "P"     },
    { "Preempted",          "E"     },
    { "Preempt Pending",    "EP"    },
    { "Rejected",           "X"     },
    { "Reject Pending",     "XP"    },
    { "Removed",            "RM"    },
    { "Remove Pending",     "RP"    },
    { "Resume Pending",     "MP"    },
    { "Running",            "R"     },
    { "Starting",           "ST"    },
    { "System Hold",        "S"     },
    { "Terminated",         "TX"    },
    { "User & System Hold", "HS"    },
    { "User Hold",          "H"     },
    { "Vacated",            "V"     },
    { "Vacate Pending",     "VP"    }
};

JobStateValueSaver::JobStateValueSaver()
{

}

JobStateValueSaver::~JobStateValueSaver()
{

}

void JobStateValueSaver::setItemValue(QueryItem *query_item, const QString &value)
{
    int value_length = value.length();
    if(value_length == 1 || value_length == 2)
    {
        query_item->setText(value);
        return;
    }

    foreach(JobState state, job_state_list_)
    {
        if(state.name_ == value)
        {
            query_item->setText(state.abbreviation_);
            return;
        }
    }

    query_item->setText(value);
    return;
}
