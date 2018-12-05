#ifndef PYINQT_H
#define PYINQT_H

#undef slots

#include <Python.h>
#include <boost/python.hpp>
#include <boost/python/exec.hpp>

#define slots __attribute__((annotate("qt_slot")))

#endif // PYINQT_H
