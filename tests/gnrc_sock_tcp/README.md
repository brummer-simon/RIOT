Test description
==========
This test suite covers the GNRC_TCP integration into the SOCK_TCP interface. This entire test suite
consists of several python scripts located within the test directory. The following scripts are executed
within this test suite.

1) 01-conn_lifecycle_as_client.py
    This test covers TCP connection establishment and teardown with GNRC_SOCK_TCP acting as tcp client.

Setup
==========
The test requires a tap-device setup. This can be achieved by running 'dist/tools/tapsetup/tapsetup'
or by executing the following commands:

    sudo ip tuntap add tap0 mode tap user ${USER}
    sudo ip link set tap0 up

Usage
==========
    make BOARD=<BOARD_NAME> all flash
    sudo make BOARD=<BOARD_NAME> test

'sudo' is required due to ethos and raw socket usage.
