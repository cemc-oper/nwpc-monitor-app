import unittest
from unittest import mock
from argparse import Namespace
from io import StringIO
import json

import importlib
import os
import sys
sys.path.append(
    os.path.join(os.path.dirname(__file__), "../../../../../src/plugins/loadleveler_monitor")
)
from nwpc_loadleveler import loadleveler


class TestNwpcLoadleveler(unittest.TestCase):
    def setUp(self):
        importlib.reload(loadleveler)

    def tearDown(self):
        pass

    def test_file_command_normal_text(self):
        output = None
        with mock.patch('sys.stdout', new_callable=StringIO) as mock_output:
            args = Namespace(
                sub_commands="file",
                host="uranus.hpc.nmic.cn",
                port=22,
                user="wangdp",
                password="perilla",
                path="/cma/g3/wangdp/work/2016/nwpc-monitor-app/nwpc-monitor-app/"
                        "tests/auto/plugins/loadleveler_monitor/nwpc_loadleveler/data/"
                        "meps_forecast/forecast.job1"
            )
            loadleveler.file_handler(args)
            output = mock_output.getvalue()
        if output is None:
            self.fail("mock sys.stdout failed.")

        result = json.loads(output)
        print(result)

    def test_file_command_long_text(self):
        output = None
        with mock.patch('sys.stdout', new_callable=StringIO) as mock_output:
            args = Namespace(
                sub_commands="file",
                host="uranus.hpc.nmic.cn",
                port=22,
                user="wangdp",
                password="perilla",
                path="/cma/g3/wangdp/work/2016/nwpc-monitor-app/nwpc-monitor-app/"
                        "tests/auto/plugins/loadleveler_monitor/nwpc_loadleveler/data/"
                        "meps_forecast/forecast.1"
            )
            loadleveler.file_handler(args)
            output = mock_output.getvalue()

        if output is None:
            self.fail("mock sys.stdout failed.")

        result = json.loads(output)
        print(result)
