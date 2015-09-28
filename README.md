# Antrix 2.1.x

I found this source quite some time ago and started doing some minor work to it. I removed the old build system and implemented a cmake system based on Mangos' cmake system (Thanks guys!) and the source now builds (Except tools).

Goals:
- Update source to support 2.4.3 (Opcodes, DBC structure, etc)
- Either upgrade/improve GameMonkey or remove in favor of Eluna
- Fix source to a point where it builds under both Linux and Windows

There are several things not working/missing:
- Tools build does NOT work
- Database is missing, needs to be recreated from source
- Cluster system is completely stripped from source, possibly able to reimplement with an earlier copy of Antrix
