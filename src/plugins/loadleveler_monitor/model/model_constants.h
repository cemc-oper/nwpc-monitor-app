#pragma once

#include <QString>

namespace LoadLevelerMonitor{

namespace Model{

namespace Constant{

namespace Llq{

const QString Id            =   "llq.id";
const QString Submitted     =   "llq.submitted";
const QString Class         =   "llq.class";
const QString Owner         =   "llq.owner";
const QString Status        =   "llq.status";
const QString FullStatus    =   "llq.full_status";

const QString DispatchDate  =   "llq.dispatch_date";
const QString QueueDate     =   "llq.queue_date";
const QString UnixGroup     =   "llq.unix_group";
const QString HostName      =   "llq.host_name";
const QString StepId        =   "llq.step_id";
const QString ImageSize     =   "llq.image_size";
const QString JobName       =   "llq.job_name";
const QString JobType       =   "llq.job_type";
const QString HostCount     =   "llq.host_count";
const QString Priority      =   "llq.priority";
const QString StepName      =   "llq.step_name";
const QString No            =   "llq.no";

const QString StepType      =   "llq.step_type";
const QString JobScript     =   "llq.job_script";
const QString QueueFullDate =   "llq.queue_full_date";
const QString NodeMinimum   =   "llq.node_minimum";
const QString NodeActual    =   "llq.node_actual";
const QString NodeMaximum   =   "llq.node_maximum";
const QString TaskInstanceCount =   "llq.task_instance_count";

const QString Out           =   "llq.in";
const QString Err           =   "llq.err";
const QString InitialWorkingDir =   "llq.initial_working_dir";
}

namespace Llclass{

const QString No                =   "llclass.no";
const QString Name              =   "llclass.name";
const QString MaxJobCpu         =   "llclass.max_job_cpu";
const QString MaxProcCpu        =   "llclass.max_proc_cpu";
const QString FreeSlots         =   "llclass.free_slots";
const QString MaxSlots          =   "llclass.max_slots";
const QString Description       =   "llclass.description";
const QString ExcludeUsers      =   "llclass.exclude_users";
const QString IncludeUsers      =   "llclass.include_users";
const QString WallColockLimit   =   "llclass.wall_clock_limit";

}

}

}

}
