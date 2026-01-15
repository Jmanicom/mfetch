# mfetch
Custom built CLI tool to display system information using the C programming language.

![Demo](https://github.com/user-attachments/assets/1995af5d-13f8-4bca-9d4a-6095b174e821)

# Background

This project started as an exercise of wanting to learn more about I/O handling and working with pointers in the C programming language.
With that being said, the approach to some aspects of this implementation could be considered naive but I am continuing on working on optimizations and
better code practices.

# Compatibility

So far, this mfetch only works on windows since I have only written it based around the Win32 API provided by my Windows install. In order to run build and run the program,
you can follow these commands to test it out if curious. In order to run it for the first time run this series of commands:

```bash
git clone https://github.com/Jmanicom/mfetch.git
./build.bat
```

This will run the program as well and let you know it has succesfully built using the gcc compiler (requirement). To run subsequent times, run this command and youll get the
following output with your system information:

```bash
mfetch

            ___      _       _              XYZ@XYZDesktop
      /\/\ /  _| ___| |_ ___| |__           ===================
     /    \| |_ / _ \ __/ __| '_  \         OS: Windows 11 Home 24H2 (Build 26100)
    / /\/\ \  _|  __/ || (__| | | |         Uptime: x hours, x mins
    \/    \/_|  \___|\__\___|_| |_|         CPU: AMD Ryzen x x-Core Processor
                                            RAM: XMiB / XMiB
```