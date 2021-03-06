# configure.in (version 4) for Unix Squeak			-*- sh -*-
# 
# Process this file with autoconf to produce a configure script

#   Copyright (C) 1996-2007 by Ian Piumarta and other authors/contributors
#                              listed elsewhere in this file.
#   All rights reserved.
#   
#   This file is part of Unix Squeak.
# 
#   Permission is hereby granted, free of charge, to any person obtaining a copy
#   of this software and associated documentation files (the "Software"), to deal
#   in the Software without restriction, including without limitation the rights
#   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#   copies of the Software, and to permit persons to whom the Software is
#   furnished to do so, subject to the following conditions:
# 
#   The above copyright notice and this permission notice shall be included in
#   all copies or substantial portions of the Software.
# 
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#   SOFTWARE.
# 
# Author: Ian.Piumarta@SqueakLand.org
# 
# Last edited: Tue Jan 26 11:51:29 PST 2010 by eliot

AC_INIT([config.h.in])

AC_VM_VERSION(3,9,7, 3,9a,7024)

topdir=`cd ${srcdir}/../../..; pwd`
cfgdir=`cd ${srcdir}; pwd`

AC_ARG_WITH(src,
[  --with-src=dir          generated src directory [default=src]],
[ vmmsrc="${with_src}"],
[ vmmsrc="src"])

vmmdir="${topdir}/${vmmsrc}"

if test ! -d "${topdir}/${vmmsrc}"; then
  if test -d "${topdir}/platforms/unix/${vmmsrc}"; then
    vmmdir="${topdir}/platforms/unix/${vmmsrc}"
    AC_MSG_RESULT([using built-in src directory])
  fi
fi

AC_MSG_RESULT(${vmmdir})

blddir=`pwd`

AC_ARG_WITH(vmmcfg,
[  --with-vmmcfg=dir        vm configuration directory containing plugins.int and plugins.ext [default=.]],
[ vmmcfg="${with-vmmcfg}"],
[ vmmcfg="${blddir}"])

# Check the generated src dir looks sane

AC_CHECK_VMM_DIR

AC_SUBST(topdir)
AC_SUBST(cfgdir)
AC_SUBST(vmmdir)
AC_SUBST(vmmcfg)
AC_SUBST(blddir)

SQ_VERSION=${SQ_MAJOR}.${SQ_MINOR}-${SQ_UPDATE}

AC_DEFINE_UNQUOTED(SQ_VERSION, "${SQ_VERSION}")

AC_SUBST(SQ_MAJOR)
AC_SUBST(SQ_MINOR)
AC_SUBST(SQ_UPDATE)
AC_SUBST(SQ_VERSION)

VM_VERSION=${VM_MAJOR}.${VM_MINOR}-${VM_RELEASE}

AC_DEFINE_UNQUOTED(VM_VERSION, "${VM_VERSION}")

AC_SUBST(VM_MAJOR)
AC_SUBST(VM_MINOR)
AC_SUBST(VM_RELEASE)
AC_SUBST(VM_VERSION)

# libdir contains ${exec_prefix}, so we have to default and expand early
test "x$prefix" = xNONE && prefix=$ac_default_prefix
test "x$exec_prefix" = xNONE && exec_prefix='${prefix}'
imgdir=`eval echo ${libdir}/squeak`
expanded_relative_imgdir=`eval echo lib/squeak/${VM_VERSION}`
plgdir='${imgdir}/'`eval echo ${VM_VERSION}`

AC_SUBST(imgdir)
AC_SUBST(expanded_relative_imgdir)
AC_SUBST(plgdir)

AC_DEFINE(OS_TYPE, "unix")

AC_CANONICAL_HOST

host_cpu=`echo $host | sed 's,-.*,,'`
host=`echo $host | sed 's,-unknown,,'`

AC_SUBST(host)
AC_SUBST(host_cpu)
AC_SUBST(host_vendor)
AC_SUBST(host_os)

AC_DEFINE_UNQUOTED(VM_HOST, "$host")
AC_DEFINE_UNQUOTED(VM_HOST_OS, "$host_os")
AC_DEFINE_UNQUOTED(VM_HOST_CPU, "$host_cpu")

echo
echo "Configuring Squeak ${VM_VERSION} (${SQ_VERSION}) for ${host}"
echo

# Checks for programs.

AC_ARG_WITH(gnu-awk,
[  --with-gnu-awk          assume that awk is GNU gawk [default=no]],
[GAWK="$withval"],
[case $host_os in
  darwin*)	GAWK="yes";;
  *)		GAWK="unknown";;
esac])

AC_ARG_WITH(gnu-as,
[  --with-gnu-as           assume that as is the GNU assembler [default=no]],
  [GAS="$withval"],
  [GAS="unknown"])

AC_PROG_MAKE_SET
AC_PROG_CC_WALL
AC_PROG_AS_GNU
AC_PROG_RANLIB
AC_PROG_INSTALL
AC_PROG_NM

AC_CHECK_PROG(LN, ln, ln)

# Check size assumptions of basic data types

AC_REQUIRE_SIZEOF(int,    4)
AC_REQUIRE_SIZEOF(double, 8)

AC_CHECK_INT64_T

AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(long)
AC_CHECK_SIZEOF(long long)
AC_CHECK_SIZEOF(void *)

# libtool configuration

AC_DISABLE_STATIC
AC_PROG_LIBTOOL

# Configured headers (pretty much everybody needs blddir and vm)

INCLUDES="-I${blddir} -I${vmmcfg} -I${topdir}/platforms/unix/vm -I${topdir}/platforms/Cross/vm -I${vmmdir}/vm"

AC_SUBST(INCLUDES)

# Checks for header files.

AC_NEED_SUNOS_H

AC_STDC_HEADERS
AC_HAVE_HEADERS(unistd.h string.h fcntl.h sys/file.h sys/param.h)
AC_HAVE_HEADERS(sys/time.h sys/filio.h sys/select.h)
AC_HAVE_HEADERS(features.h)
AC_HAVE_HEADERS(alloca.h) # SunOS5
AC_HEADER_TIME
AC_HEADER_DIRENT

if test -f "${vmmdir}/vm/interp.h"; then
  AC_DEFINE(HAVE_INTERP_H, 1)
fi
AC_SUBST(HAVE_INTERP_H)

AC_STRUCT_TIMEZONE

AC_CHECK_SOCKLEN_T
AC_CHECK_ATEXIT
AC_CHECK_TZSET
AC_CHECK_GMTOFF
AC_CHECK_TIMEZONE
AC_CHECK_GETHOSTNAME

# Display options.

AC_ARG_WITH(rfb,
[  --without-rfb           disable Remote FrameBuffer support [default=enabled]],
  [have_rfb="$withval"],
  [have_rfb="no"])

test $have_rfb = "yes" && AC_DEFINE(USE_RFB,[1])

# Checks for libraries.

AC_CHECK_LIB(nsl, yp_bind)
AC_CHECK_LIB(socket, socket)
AC_CHECK_LIB(m, sin)
AC_CHECK_LIB(pthread, pthread_create)
# this seems to add no benefit
#AC_CHECK_LIB(rt, clock_nanosleep)

#AC_CHECK_FUNC(dlopen, [
#  AC_DEFINE(HAVE_LIBDL,[1])
#],[
#  AC_CHECK_LIB(dl, dlopen, [
#    LIBS="-ldl $LIBS"
#    AC_DEFINE(HAVE_LIBDL,[1])
#  ],[
#    AC_CHECK_FUNC(_dyld_present, [
#      AC_DEFINE(HAVE_DYLD,[1])
#    ])
#  ])
#])

AC_CHECK_FUNC(_dyld_present, [
  AC_DEFINE(HAVE_DYLD,[1])
],[
  AC_HAVE_HEADERS(dlfcn.h)
  AC_CHECK_FUNC(dlopen, [
    AC_DEFINE(HAVE_LIBDL,[1])
  ],[
    AC_CHECK_LIB(dl, dlopen, [
      LIBS="-ldl $LIBS"
      AC_DEFINE(HAVE_LIBDL,[1])
    ])
  ])
])

AC_CHECK_FUNCS(snprintf __snprintf,[break])

AC_FUNC_MMAP
AC_FUNC_ALLOCA

#AC_ARG_ENABLE(jit,
#[  --enable-jit            enable J4 support [default=no]],
#JIT="yes", JIT="no")
#
#test $JIT = "yes" && J_CFLAGS="-DJ_ENABLED"
#AC_SUBST(J_CFLAGS)

# Checks for platform characteristics.

AC_GNU_OPT
AC_GNU_INTERP
AC_MODULE_LIB_PREFIX
AC_64BIT_ARCH

CFLAGS="$CFLAGS_32 $CFLAGS -msse"

AC_C_BYTEORDER
AC_C_DOUBLE_ALIGNMENT

case $host_os in
  darwin*)
    AC_DEFINE(DARWIN,[1])
#    CFLAGS="-no-cpp-precomp $CFLAGS"
    with_npsqueak=no
    VM_APP_ICONS="${imgdir}/SqueakVM.icns"
    ;;
  *)
    VM_APP_ICONS=""
    ;;
esac

AC_SUBST(VM_APP_ICONS)

# Checks for browser support

AC_SUBST(npsqueak)
AC_SUBST(install_nps)
AC_SUBST(uninstall_nps)

AC_ARG_WITH(npsqueak,
[  --without-npsqueak      disable browser plugin support [default=enabled]],
  [with_npsqueak="$withval"],
  [with_npsqueak="yes"])

if test "$with_npsqueak" = "no"; then
  npsqueak=""
  install_nps=""
  uninstall_nps=""
else
  npsqueak=npsqueak
  install_nps=install-npsqueak
  uninstall_nps=uninstall-npsqueak
fi

# Install locations

if test "x${prefix}" = xNONE; then
  SQ_LIBDIR=${ac_default_prefix}/lib/squeak/${SQ_VERSION}
else
  SQ_LIBDIR=${prefix}/lib/squeak/${SQ_VERSION}
fi

AC_SUBST(SQ_LIBDIR)
AC_DEFINE_UNQUOTED(SQ_LIBDIR,["${SQ_LIBDIR}"])

# Configure files

make_cfg=${blddir}/make.cfg
make_int=${blddir}/make.int
make_ext=${blddir}/make.ext
make_prg=${blddir}/make.prg

AC_SUBST_FILE(make_cfg)
AC_SUBST_FILE(make_int)
AC_SUBST_FILE(make_ext)
AC_SUBST_FILE(make_prg)

Makefile_install=${cfgdir}/Makefile.install
Makefile_dist=${topdir}/util/Makefile.dist
Makefile_rpm=${topdir}/util/Makefile.rpm
Makefile_deb=${topdir}/util/Makefile.deb

AC_SUBST_FILE(Makefile_install)
AC_SUBST_FILE(Makefile_dist)
AC_SUBST_FILE(Makefile_rpm)
AC_SUBST_FILE(Makefile_deb)

# Configure VM modules xxx MAKE INTERNAL WORK

int_modules="vm"
ext_modules="`cd ${topdir}/platforms/unix; echo vm-*`"

AC_SUBST(int_modules)
AC_SUBST(ext_modules)

# Configure plugins

disabled_plugins=""
rm -f plugins.exc
sinclude(acplugins.m4)

#AC_ARG_WITH(vm-sound-null,
#[  --without-vm-sound-null      disable null vm sound support [default=enabled]],
#  [with_vm_sound_null="$withval"],
#  [with_vm_sound_null="yes"])
#if test "$with_vm_sound_null"="no"; then
#	AC_PLUGIN_DISABLE_PLUGIN(vm-sound-null);
#fi

AC_ARG_WITH(vm-sound-OSS,
[  --without-vm-sound-OSS      disable OSS vm sound support [default=enabled]],
  [with_vm_sound_OSS="$withval"],
  [with_vm_sound_OSS="yes"])
if test "$with_vm_sound_OSS"="no"; then
	AC_PLUGIN_DISABLE_PLUGIN(vm-sound-OSS);
fi

AC_ARG_WITH(vm-display-fbdev,
[  --without-vm-display-fbdev      disable frame buffer vm display support [default=enabled]],
  [with_vm_display_fbdev="$withval"],
  [with_display_fbdev="yes"])
if test "$with_display_fbdev"="no"; then
	AC_PLUGIN_DISABLE_PLUGIN(vm-display-fbdev);
fi

# Plugins not generated by VMM must be listed here...
int_plugins=""
ext_plugins=""
AC_SUBST(int_plugins)
AC_SUBST(ext_plugins)

#if test "$have_x" = "no"; then
#  AC_PLUGIN_DISABLE_PLUGIN(UnixOSProcessPlugin)
#fi

if test "${disabled_plugins}" != ""; then
  echo ${disabled_plugins} | tr ' ' '\012' | sort -u > plugins.exc
fi

# for some reason configure leaves an empty a.out lying around
test -f a.out && rm a.out

# Create the build environment

AC_CONFIG_HEADER(config.h)
AC_CONFIG_FILES(mkconfig make.cfg make.int make.ext make.prg inisqueak squeak.sh bin.squeak.sh Makefile)
AC_CONFIG_COMMANDS([default],[
  chmod +x mkconfig inisqueak
  ${SHELL} -ec "./mkconfig; ${cfgdir}/mktargets; ${cfgdir}/mkmf"],[
  cfgdir=${cfgdir}
])

AC_OUTPUT
