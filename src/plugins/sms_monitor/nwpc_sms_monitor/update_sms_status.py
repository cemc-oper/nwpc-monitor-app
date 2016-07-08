from paramiko import SSHClient, AutoAddPolicy

client = SSHClient()
client.load_system_host_keys()
client.set_missing_host_key_policy(AutoAddPolicy)
client.connect('uranus.hpc.nmic.cn', username='wangdp', password='perilla')

stdin, stdout, stderr = client.exec_command(
    '/cma/g3/wangdp/usr/local/bin/python '
    '/cma/g3/wangdp/nwp/sms/smslog/nwpc-log-collector/nwpc_sms_collector/sms_status_collector.py '
    'show -n nwpc_pd -u nwp_pd '
    '-c /cma/g3/wangdp/nwp/sms/smslog/nwpc-log-collector/nwpc_sms_collector/conf/sms_status_collector.config'
)

std_out_string = stdout.read().decode('UTF-8')

print(std_out_string)

client.close()