#!/bin/bash
sudo rm -r /var/lib/mesos
sudo /home/lilelr/open-source/mesos-1.3.2/build/bin/mesos-master.sh --ip=127.0.0.1 --work_dir=/var/lib/mesos
