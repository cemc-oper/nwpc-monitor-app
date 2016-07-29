import datetime
import json
import re

from paramiko import SSHClient, AutoAddPolicy


def main():
    client = SSHClient()
    client.set_missing_host_key_policy(AutoAddPolicy())
    client.connect('uranus.hpc.nmic.cn', 22, 'wangdp', 'perilla')

    stdin, stdout, stderr = client.exec_command(
        'llq'
    )

    std_out_string = stdout.read().decode('UTF-8')

    std_out_lines = std_out_string.split("\n")

    if std_out_lines[0].startswith("llq: There is currently no job status to report."):
        result = {
            'app': 'nwpc_loadleveler',
            'type': 'loadleveler_command',
            'data': {
                'command': {
                    'command': 'llq',
                    'arguments': []
                },
                'result': {
                    'jobs': [],
                    'summary': None
                }
            }
        }
        print(json.dumps(result))
        client.close()
        return

    if not std_out_lines[0].startswith("Id"):
        result = {
            'app': 'nwpc_loadleveler',
            'type': 'loadleveler_command',
            'error': 'command_result_parser_error',
            'data': {
                'command': {
                    'command': 'llq',
                    'arguments': []
                },
                'error_message': 'can not parse result.'
            }
        }
        print(json.dumps(result))
        client.close()
        return

    # parse outputs
    loadleveler_jobs = []
    for a_line in std_out_lines[2:-3]:
        records = a_line.split()
        a_job = dict()
        a_job['id'] = records[0]
        a_job['owner'] = records[1]
        a_job['submitted'] = {
            'date': records[2],
            'time': records[3]
        }
        a_job['st'] = records[4]
        a_job['pri'] = records[5]
        a_job['class'] = records[6]
        a_job['running_on'] = records[7] if len(records) >= 8 else ""
        loadleveler_jobs.append(a_job)

    total_pattern = u"^(\d+) job step\(s\) in (queue|query), (\d+) waiting, (\d+) pending, (\d+) running, " + \
        u"(\d+) held, (\d+) preempted"
    total_prog = re.compile(total_pattern)
    total_prog_result = total_prog.match(std_out_lines[-2])
    llq_summary = dict()
    llq_summary['in_queue'] = total_prog_result.group(1)
    llq_summary['waiting'] = total_prog_result.group(3)
    llq_summary['pending'] = total_prog_result.group(4)
    llq_summary['running'] = total_prog_result.group(5)
    llq_summary['held'] = total_prog_result.group(6)
    llq_summary['preempted'] = total_prog_result.group(7)

    result = {
        'app': 'nwpc_loadleveler',
        'type': 'loadleveler_command',
        'data': {
            'command': {
                'command': 'llq',
                'arguments': []
            },
            'result': {
                'jobs': loadleveler_jobs,
                'summary': llq_summary
            }
        }
    }

    print(json.dumps(result))

    client.close()
    return


if __name__ == "__main__":
    main()
