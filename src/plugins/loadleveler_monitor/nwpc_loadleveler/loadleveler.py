from paramiko import SSHClient, AutoAddPolicy


def main():
    client = SSHClient()
    client.set_missing_host_key_policy(AutoAddPolicy())
    client.connect('uranus.hpc.nmic.cn', 22, 'wangdp', 'perilla')

    stdin, stdout, stderr = client.exec_command(
        'llq'
    )

    std_out_string = stdout.read().decode('UTF-8')

    print(std_out_string)

    client.close()


if __name__ == "__main__":
    main()
