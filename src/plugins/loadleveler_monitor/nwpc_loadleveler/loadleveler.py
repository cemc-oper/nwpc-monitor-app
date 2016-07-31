import argparse
import datetime
import json
import re

from paramiko import SSHClient, AutoAddPolicy


def llq_handler(args):
    """
    使用llq命令查询
    :param args:
    :return:
        正常输出
        {
            'app': 'nwpc_loadleveler',
            'type': 'loadleveler_command',
            'data': {
                'command': {
                    'command': 'llq',
                    'arguments': [
                        arg1,
                        arg2,
                        ...
                    ]
                },
                'result': {
                    'jobs': [
                        {
                            'id': string
                            'owner': string
                            'submitted' {
                                'date': string,
                                'time': string
                            }
                            'st': string
                            'pri': string
                            'class': string
                            'running_on': string
                        },
                        ...
                    ],
                    'summary': {
                        'in_queue': number,
                        'waiting': number,
                        'pending': number,
                        'running': number,
                        'held': number,
                        'preempted': number
                    }
                }
            }
        }

        错误输出示例
        {
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

    """
    host = args.host
    port = args.port
    user = args.user
    password = args.password
    command = args.command

    client = SSHClient()
    client.set_missing_host_key_policy(AutoAddPolicy())
    client.connect(host, port, user, password)

    stdin, stdout, stderr = client.exec_command(
        command
    )

    std_out_string = stdout.read().decode('UTF-8')
    std_error_string = stderr.read().decode('UTF-8')

    std_out_lines = std_out_string.split("\n")

    if std_out_lines[0].startswith("llq: There is currently no job status to report."):
        result = {
            'app': 'nwpc_loadleveler',
            'type': 'loadleveler_command',
            'data': {
                'command': {
                    'command': command,
                    'arguments': []
                },
                'result': {
                    'jobs': [],
                    'summary': None
                },
                'message': {
                    'output': 'llq: There is currently no job status to report.'
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
                    'command': command,
                    'arguments': []
                },
                'message': {
                    'error_message': 'can not parse result.',
                    'output': std_out_string,
                    'error_output': std_error_string
                }
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


def llclass_handler(args):
    host = args.host
    port = args.port
    user = args.user
    password = args.password
    command = args.command

    client = SSHClient()
    client.set_missing_host_key_policy(AutoAddPolicy())
    client.connect(host, port, user, password)

    stdin, stdout, stderr = client.exec_command(
        command
    )

    std_out_string = stdout.read().decode('UTF-8')

    print(std_out_string)

    return


def loadleveler_main():
    parser = argparse.ArgumentParser(prog="hpc-loadleveler")
    parser.add_argument('--foo', action='store_true', help='foo help')

    login_parser = argparse.ArgumentParser(add_help=False)
    login_parser.add_argument('-H', '--host', type=str, help='remote host', required=True)
    login_parser.add_argument('-P', '--port', type=int, help='remote host\'s port', default=22)
    login_parser.add_argument('-u', '--user', type=str, help='user', required=True)
    login_parser.add_argument('-p', '--password', type=str, help='password', required=True)

    subparsers = parser.add_subparsers(help='sub-command help')

    parser_llq = subparsers.add_parser('llq', help='use llq command', parents=[login_parser])
    parser_llq.add_argument('-c', '--command', type=str, help='llq command', required=True)
    parser_llq.set_defaults(func=llq_handler)

    parser_llclass = subparsers.add_parser('llclass', help='use llclass command', parents=[login_parser])
    parser_llclass.add_argument('-c', '--command', type=str, help='llq command', required=True)
    parser_llclass.set_defaults(func=llclass_handler)

    args = parser.parse_args()

    args.func(args)


if __name__ == "__main__":
    loadleveler_main()
