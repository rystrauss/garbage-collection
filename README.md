# Garbage College

This repository contains an implementation of an automatic memory reclamation system for C++. By default C++ does not
automatically free dynamically allocated memory (like in Java). This library contains a `GCPointer` class, which uses
reference counting to automatically discover when data should be freed.

This is a simplistic implementation and does not check for reference cycles. So there are some specific scenarios in
which memory leakage can still occur.