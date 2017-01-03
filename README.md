# npwc-monitor-app

A desktop application for operation support in NWPC.

## Downloads

Get the lastest release in [releases page](https://github.com/perillaroc/nwpc-monitor-app/releases).

## Getting started

Unpack the release file.
Install tools under \_\_install\_\_ directory.
And Run bin/nwpc-monitor-app.exe.

## Building

nwpc-monitor-app is developed for Windows.
Follow the guidelines below to build nwpc-monitor-app on Windows.

### Requirement

* Windows 7
* Visual Studio 2015
* Python 3.5+, with paramiko installed
* Qt 5.7.1

Install python 3.5 or higher version, and install paramiko using pip.
Copy python environment in some directory, which is needed in buiding step.

## Getting the Code

Get the lastest release source code in [releases page](https://github.com/perillaroc/nwpc-monitor-app/releases).
Or clone it from Github.

```
git clone https://github.com/perillaroc/nwpc-monitor-app.git
```

### Configure

Change the python environment direcotry in nwpc-monitor-app.pri, such as:

```
python_env_dir = d:/python35
```

### Build

Open nwpc-monitor-app.pro in Qt Creator and then build the project. Or use Qt command line console.

## License

Copyright &copy; 2016-2017 Perilla Roc.

nwpc-monitor-app is licensed under [GPL-v3.0](https://www.gnu.org/licenses/gpl-3.0.html).
